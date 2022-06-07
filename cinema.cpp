#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <sstream>
#include "purchasable.h"
#include "shop.h"
#include "json.hpp"
#include "datetime.h"
#include "playable.h"
#include "cinema.h"

using namespace std;
using json = nlohmann::json;

Cinema::Cinema(string name, DateTime start_datetime): name(name), start_datetime(start_datetime)
{
    cout << "Movie Theatre Simulation" << endl;
    cout << "Name: " << name << endl;
    cout << "Start Date: " << start_datetime << endl;
    load_shows_from_file(); // load all shows from json file to vector of movies
    load_screening_rooms_from_file(); // load all screening rooms from json file to vector of sreening rooms
    load_snacks_from_file();
    load_workers_from_file();
    generate_ticket_booths(5);
    generate_snack_shops(5);
    this -> log_filename = get_log_filename();
}

Cinema::~Cinema()
{
    for (auto& movie: movies) delete movie;
    for (auto& concert: concerts) delete concert;
    for (auto& meeting: meetings) delete meeting;
    for (auto& screening_room: screening_rooms) delete screening_room;
    for (auto& snack: snacks) delete snack;
    for (auto& ticket_seller: ticket_sellers) delete ticket_seller;
    for (auto& snack_seller: snack_sellers) delete snack_seller;
}

void Cinema::load_shows_from_file()
{   // loading all movies, concerts and meetings from files
    ifstream ifs("data files/movies.json");
    json jf = json::parse(ifs);
    for (const auto &element : jf)
    {
        Movie* film_ptr = new Movie;
        from_json(element, *film_ptr);
        movies.push_back(film_ptr);
    }
    ifstream con("data files/concerts.json");
    json co = json::parse(con);
    for (const auto &element : co)
    {
        Concert* concert_ptr = new Concert;
        from_json(element, *concert_ptr);
        concerts.push_back(concert_ptr);
    }
    ifstream meet("data files/meetings.json");
    json mt = json::parse(meet);
    for (const auto &element : mt)
    {
        Meeting* meeting_ptr = new Meeting;
        from_json(element, *meeting_ptr);
        meetings.push_back(meeting_ptr);
    }
}

void Cinema::load_screening_rooms_from_file()
{   // loading all screening rooms from json file
    ifstream ifs("data files/screening_rooms.json");
    json jf = json::parse(ifs);
    for (const auto &element : jf)
    {
        ScreeningRoom* screening_room_ptr = new ScreeningRoom;
        from_json(element, *screening_room_ptr);
        screening_rooms.push_back(screening_room_ptr);
    }
}

void Cinema::load_snacks_from_file()
{   // loading all snacks from json file
    ifstream ifs("data files/snacks.json");
    json jf = json::parse(ifs);
    for (const auto &element : jf)
    {
        Snack* snack_ptr = new Snack(element["name"], element["first_price"], "Normal");
        snacks.push_back(snack_ptr);
    }
}

void Cinema::load_workers_from_file()
{   // generate new workers for the simulation
    ifstream ifs("data files/workers.json");
    json jf = json::parse(ifs);
    for (const auto &element : jf)
    {
        if (element["position"] == "ticket seller")
        {
            TicketSeller* ticket_seller_ptr = new TicketSeller(element["first_name"], element["second_name"], element["salary"]);
            ticket_sellers.push_back(ticket_seller_ptr);
        }
        else if (element["position"] == "snack seller")
        {
            SnackSeller* snack_seller_ptr = new SnackSeller(element["first_name"], element["second_name"], element["salary"]);
            snack_sellers.push_back(snack_seller_ptr);
        }
    }
}

void Cinema::generate_ticket_booths(int amount)
{
    // generate new ticket booths for the simulation
    vector <TicketSeller*> ticket_sellers_copy = ticket_sellers;
    for (int i=0; i<amount; i++)
    {
        int ticket_seller_index = generate_rand_number(0, ticket_sellers_copy.size()-1);
        TicketBooth* ticket_booth_ptr = new TicketBooth(i+1, "Open", ticket_sellers_copy[ticket_seller_index]);
        ticket_booth_ptr->add_shows(shows);
        ticket_booths.push_back(ticket_booth_ptr);
        ticket_sellers_copy.erase(ticket_sellers_copy.begin() + ticket_seller_index);
    }
}

void Cinema::generate_snack_shops(int amount)
{
    // generate new snacks shops for the simulation
    vector <SnackSeller*> snack_sellers_copy = snack_sellers;
    for (int i=0; i<amount; i++)
    {
        int snack_seller_index = generate_rand_number(0, snack_sellers_copy.size()-1);
        SnackShop* snack_shop_ptr = new SnackShop(i+1, "Open", snack_sellers_copy[snack_seller_index]);
        snack_shops.push_back(snack_shop_ptr);
        snack_sellers_copy.erase(snack_sellers_copy.begin() + snack_seller_index);
    }
}

void Cinema::create_new_repertoire(DateTime datetime, vector <string> &messages)
{   // creating a new repertoire
    if (datetime > repertoire.get_end_datetime())
    {
        repertoire = Repertoire("Someone", datetime, screening_rooms);
        // tutaj na razie dla każdego repertuaru tworzymy 3 seanse, które zawsze będą w tych samych dniach
        // (pierwszy seans w dniu startu tego repertuaru, drugi dzień później i trzeci 2 dni później)
        DateTime dt1 = datetime;
        DateTime dt2 = datetime;
        DateTime dt3 = datetime;
        dt1.add_days(0);
        dt2.add_days(1);
        dt3.add_days(2);
        create_show(dt1);
        create_show(dt2);
        create_show(dt3);
        messages.push_back(" New repertoire has been created for next " + to_string(repertoire.get_days_duration()) + " days.");
    }
}

void Cinema::create_show(DateTime start_datetime)
{
    short show_type = generate_rand_number(1, 10);    // choose played show's type
    Show* show_ptr;
    if (show_type == 1)                 // 10% for a concert
    {
        show_ptr = new Show(concerts[generate_rand_number(0, concerts.size()-1)], *screening_rooms[generate_rand_number(0, screening_rooms.size()-1)], start_datetime);
        show_ptr->type = "concert ";
    }
    else if (show_type == 2)            // 10% for a meet&greet
    {
        show_ptr = new Show(meetings[generate_rand_number(0, meetings.size()-1)], *screening_rooms[generate_rand_number(0, screening_rooms.size()-1)], start_datetime);
        show_ptr->type = "meet&greet ";
    }
    else                                // 80% for a movie, because that's what cinemas show most of the time
    {
        show_ptr = new Show(movies[generate_rand_number(0, movies.size()-1)], *screening_rooms[generate_rand_number(0, screening_rooms.size()-1)], start_datetime);
        show_ptr->type = "movie screening ";
    }
    shows.push_back(show_ptr);
    repertoire.add_show(show_ptr); // adding show to the repertoire
}

int Cinema::free_seats(const vector <vector <bool>> &seats)
{   // return number of available seats in screening room
    int count = 0;
    for (const auto &row: seats)
    {
        for (const auto &seat: row)
        {
            if (seat == false) count++;
        }
    }
    return count;
}

bool Cinema::buy_tickets(Show &show, int number)
{   // buy given number of ticket to given movie screening
    // return true if ticket have been bought, false if not
    vector <vector<bool>> seats = show.get_seats();
    if (free_seats(seats) < number) return false;
    int bought_tickets = 0;
    for (unsigned int i=0; i<seats.size(); i++)
    {
        for (unsigned int j=0; j<seats[0].size(); j++)
        {
            if (seats[i][j] == false)
            {
                show.buy_seat(i, j);
                bought_tickets++;
                if (bought_tickets==number) return true;
            }
        }
    }
    return true;
}

void Cinema::buy_tickets_simulation(DateTime datetime, vector <string> &messages)
{
    // datetime argument is current date in the simulation - it is used only to print message
    int ticket_number = generate_rand_number(1, 4); // number of tickets to be bought
    if (repertoire.get_available_show_hours().empty()) return; // if there are no available movie screenings to buy ticket to, end function
    Show* show_ptr = repertoire.get_available_show_hours()[generate_rand_number(0, repertoire.get_available_show_hours().size()-1)]; // get random movie_screening to buy tickets from it
    TicketBooth* ticket_booth_ptr = ticket_booths[(generate_rand_number(0, ticket_booths.size() - 1))]; // get a shop that will sell ticket(s) for this show
    string message = "";
    if (buy_tickets(*show_ptr, ticket_number)) // if there are enough available seats, buy ticket
    {
        message += ticket_booth_ptr->sell_ticket(show_ptr, ticket_number);
    }
    else
    {
        message += " Someone tried to buy " + to_string(ticket_number) + " tickets to " + show_ptr->type + "(Show ID: " + to_string(show_ptr->get_id()) + ") but there were no available seats. (Show: " + show_ptr->get_show()->get_title() + ")";
    }
    messages.push_back(message);
}

void Cinema::buy_snacks_simulation(DateTime datetime, vector <string> &messages)
{
    Snack* snack_ptr = snacks[generate_rand_number(0,snacks.size()-1)];
    SnackShop* snack_shop_ptr = snack_shops[(generate_rand_number(0, snack_shops.size() - 1))];
    string message = " " + snack_shop_ptr->get_worker()->get_first_name() + " " + snack_shop_ptr->get_worker()->get_second_name() + " sold " + snack_ptr->get_name() + " in shop " + to_string(snack_shop_ptr->get_room_number());
    messages.push_back(message);
}

void Cinema::update_show_status(DateTime datetime, vector <string> &messages)
{
    if (repertoire.get_taken_rooms_numbers().size() == 0) return; // if there are no available shows to buy ticket to, end function
    for (unsigned int i=0; i<repertoire.get_taken_rooms_numbers().size(); i++)
    {
        int room = repertoire.get_taken_rooms_numbers()[i];
        for (unsigned int j=0; j<repertoire.get_show_hours()[room].size(); j++)
        {
            Show* show_ptr = repertoire.get_show_hours()[room][j];
            if (show_ptr->get_status() == "Yet to start")
            {
                if (show_ptr->get_start_datetime() <= datetime)
                {
                    show_ptr->set_status("Ongoing");
                    string message = " Show " + to_string(show_ptr->get_id()) + " (\"" + show_ptr->get_show()->get_title() + "\")" + " has started.";
                    messages.push_back(message);
                }
            }
            if (show_ptr->get_status() == "Ongoing")
            {
                if (show_ptr->get_end_datetime() <= datetime)
                {
                    show_ptr->set_status("Ended");
                    string message = " Show " + to_string(show_ptr->get_id()) + " (\"" + show_ptr->get_show()->get_title() + "\")" + " has ended.";
                    messages.push_back(message);
                }
            }
        }
    }
}

void Cinema::program_in_loop(DateTime datetime)
{   // this code will be run in main simulation loop
    // add here more functions which are supposed to be run in the loop
    vector <string> messages = {}; // vector of all messages created by events

    //------------------- SIMULATION EVENTS -------------------//
    create_new_repertoire(datetime, messages); // create new repertoire if current repertoire has ended <- MUST be first
    update_show_status(datetime, messages); // update show statuses to "Started" or "Ended"
    if (get_probability_of_event(60)) buy_tickets_simulation(datetime, messages); // buy ticket to random available movie screening (60% of the times)
    if (get_probability_of_event(40)) buy_snacks_simulation(datetime, messages); 
    // add new event here

    //---------------------------------------------------------//

    // printing all messages
    cout << datetime;
    write_log_to_file(datetime.to_str());
    if (messages.size() == 0) 
    {
        cout << endl;
        write_log_to_file("\n");
    }
    else
    {
        for (unsigned int i=0; i<messages.size(); i++)
        {
            cout << messages[i] << endl;
            write_log_to_file(messages[i]);
            write_log_to_file("\n");
            if (i != messages.size()-1)
            {
                cout << datetime;
                write_log_to_file(datetime.to_str());
            }
        }
    }
}
 
void Cinema::write_log_to_file(string message)
{
    ofstream LogFile;
    LogFile.open(log_filename, ios_base::app);
    LogFile << message;
    LogFile.close();
}

string Cinema::get_log_filename()
{
    auto time_now = std::chrono::system_clock::now();

    time_t time = std::chrono::system_clock::to_time_t(time_now);

    string ctime = std::ctime(&time);

    string day = ctime.substr(8,2);
    string month = ctime.substr(4,3);
    string year = ctime.substr(20,4);
    string hours = ctime.substr(11,2);
    string minutes = ctime.substr(14,2);
    string seconds = ctime.substr(17,2);

    string datetime = day + month + year + hours + minutes + seconds;

    string log_file_name = "logs/" + datetime + ".txt";

    return log_file_name;
}

int Cinema::generate_rand_number(int min, int max)
{   // generate random number from range (min, max)
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

bool Cinema::get_probability_of_event(unsigned int probability_percent)
{
    if (probability_percent == 0) throw "Probability must be greater than 0!";
    else if (probability_percent > 100) throw "Probability must be less or equal 100!";
    else
    {
        unsigned int generated_number = generate_rand_number(0,100);
        if (generated_number <= probability_percent) return true;
        else return false;
    }
}

void Cinema::start_simulation(int simulation_iterations, int add_minutes, int loop_time)
{
    int simulation_iterations_sum = 0;
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end-start;
    while (true)
    {
        start = chrono::high_resolution_clock::now();
        end = chrono::high_resolution_clock::now();
        elapsed = end - start;
        while (elapsed.count() < loop_time)
        {
            end = chrono::high_resolution_clock::now();
            elapsed = end - start;
        }
        start_datetime.add_minutes(add_minutes);
        // this code will be run every loop_time seconds
        program_in_loop(start_datetime);

        simulation_iterations_sum ++;
        if (simulation_iterations_sum >= simulation_iterations) break;
    }
    cout << "Simulation has succesfully ended. :)";
}
