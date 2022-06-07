#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include "Repertoire.h"

using namespace std;

int Repertoire::count = 0;

Repertoire::Repertoire(const string &repertoire_author, DateTime start_datetime, vector <ScreeningRoom*> screening_rooms): author(repertoire_author)
{
    this -> start_datetime = start_datetime;
    this -> approval_datetime = start_datetime;
    id_number = count;
    ++count;
    set_repertoire_end();
    init_screening_hours(screening_rooms);
}

Repertoire::Repertoire(): author("None")
{
    this -> start_datetime = DateTime();
    this -> approval_datetime = DateTime();
    id_number = count;
    set_repertoire_end();
    init_screening_hours({});
    ++count;
}

Repertoire::Repertoire(const Repertoire & repertoire) // copying constructor
{
    id_number = count;
    ++count;
    this->author = repertoire.author;
    this->approval_datetime = repertoire.approval_datetime;
    this->start_datetime = repertoire.start_datetime;
    this->end_datetime = repertoire.end_datetime;
    this->screening_hours = repertoire.screening_hours;
}


// getters
string Repertoire::get_author() const
{
    return author;
}

int Repertoire::get_id_number() const
{
    return id_number;
}

DateTime Repertoire::get_start_datetime() const
{
    return start_datetime;
}

DateTime Repertoire::get_end_datetime() const
{
    return end_datetime;
}

DateTime Repertoire::get_approval_datetime() const
{
    return approval_datetime;
}

int Repertoire::get_days_duration() const
{
    return days_duration;
}

map<int, vector<Show*>> Repertoire::get_show_hours() const
{
    return screening_hours;
}

vector<Show*> Repertoire::get_available_show_hours() const
{   // return vector of all movie screenings which you can buy tickets to
    vector<Show*> shows = {};
    for (auto const& x : screening_hours)
    {
        if (x.second.size() > 0)
        {
            for (auto const ms : x.second)
            {
                if (ms->get_status() == "Yet to start") shows.push_back(ms);
            }
        }
    }
    return shows;
}

vector <int> Repertoire::get_taken_rooms_numbers()
{   // returns list of room nubers which have any movie screenings in it
    vector <int> rooms_numbers = {};
    for(map<int, vector<Show*>>::iterator it = screening_hours.begin(); it != screening_hours.end(); ++it)
    {
        if (it->second.size() != 0)
        {
            rooms_numbers.push_back(it->first);
        }
    }
    return rooms_numbers;
}

// setters
void Repertoire::set_author(string new_author)
{
    author = new_author;
}

void Repertoire::set_approval_datetime(DateTime datetime)
{
    this -> approval_datetime = datetime;
}

void Repertoire::set_repertoire_start(DateTime start_datetime) // method very similar to set_approval_date()
{
    this -> start_datetime = start_datetime;
}

void Repertoire::set_repertoire_end() // method that sets repertoire's end date after being given start date
{
    end_datetime = start_datetime;
    end_datetime.add_days(days_duration);
}

void Repertoire::init_screening_hours(vector <ScreeningRoom*> screening_rooms)
{
    for (auto& screening_room: screening_rooms)
    {
        screening_hours[screening_room->get_room_number()] = {};
    }
}

bool Repertoire::add_show(Show* show)     // method that takes movie screening
{
    int room = show->get_screening_room().get_room_number();
    DateTime show_start = show->get_start_datetime();
    DateTime show_end = show->get_end_datetime();

    // check if movie screening starts within repertoire date range
    if (start_datetime > show_start || show_start > end_datetime)
    {
        cout << "Invalid start time (Not in repertoire duration).\n"; // if show's start time is not set between
        return false; // repertoire's start and end time, return false
    }
    if (screening_hours[room].size() == 0)
    {
        screening_hours[room].push_back(show);
        return true;
    }
    else
    {
        if (screening_hours[room][0]->get_start_datetime() >= show_end)
        {
            screening_hours[room].insert(screening_hours[room].begin(), show);
            return true;
        }
        for (unsigned int i=0; i<screening_hours[room].size()-1; i++)
        {
            if (screening_hours[room][i]->get_end_datetime() <= show_start && screening_hours[room][i+1]->get_start_datetime() >= show_end)
            {
                screening_hours[room].insert(screening_hours[room].begin()+i+1, show);
                return true;
            }
        }
        if (screening_hours[room][screening_hours[room].size()-1]->get_end_datetime() <= show_start)
        {
            screening_hours[room].push_back(show);
            return true;
        }
    }
    cout << "Failed to add show" << endl;
    return false;
}

Repertoire::~Repertoire()       // destructor
{

}

bool Repertoire::operator==(const Repertoire& repertoire) const     // overload == operator
{
    // to check if two repertoires are the same, we want to check their authors, id numbers, start and end dates
    string author1 = this->get_author();
    string author2 = repertoire.get_author();
    int id1 = this->get_id_number();
    int id2 = repertoire.get_id_number();
    DateTime date_start1 = this->get_start_datetime();
    DateTime date_start2 = repertoire.get_start_datetime();
    DateTime end_date1 = this->get_end_datetime();
    DateTime end_date2 = repertoire.get_end_datetime();
    if (author1 == author2 && id1 == id2 && date_start1 == date_start2 && end_date1 == end_date2) return true;
    else return false;
}

bool Repertoire::operator!=(const Repertoire& repertoire) const     // overload != operator
{
    string author1 = this->get_author();
    string author2 = repertoire.get_author();
    int id1 = this->get_id_number();
    int id2 = repertoire.get_id_number();
    DateTime date_start1 = this->get_start_datetime();
    DateTime date_start2 = repertoire.get_start_datetime();
    DateTime end_date1 = this->get_end_datetime();
    DateTime end_date2 = repertoire.get_end_datetime();
    if (author1 != author2 || id1 != id2 || date_start1 != date_start2 || end_date1 != end_date2) return true;
    else return false;
}

Repertoire& Repertoire::operator=(const Repertoire &rep)        // overload assignment operator
{
    author = rep.author;
    start_datetime = rep.start_datetime;
    end_datetime = rep.end_datetime;
    approval_datetime = rep.approval_datetime;
    id_number = rep.id_number;
    screening_hours = rep.screening_hours;
    return *this;
}

ostream &operator<<(ostream &os, Repertoire &repertoire)  // overload output
{
    /*
    // print a repertoire and show movies with their screening hours, repertoire author, start, end and approval dates
    // show screening rooms and id number of repertoire
    os << "This is our repertoire. It is valid from " << repertoire.get_start_datetime();
    os << " to " << repertoire.get_end_datetime() << endl;
    os << "Below are listed movies and their screening hours." << endl;
    vector<string> movie_titles = repertoire.get_movie_titles();
    vector<DateTime> screening_hours = repertoire.get_screening_hours();
    vector<int> screening_rooms = repertoire.get_screening_rooms();
    int len = movie_titles.size();
    if (len == 0) cout << "No movies in our repertoire" << endl;    // special case if no movies in repertoire
    else
    {
        for (int i = 0; i < len; i++)       // loop that shows movies and their screening hours
        {
            os << movie_titles[i] << " : ";
            int length = screening_hours[i].size();
            for (int k = 0; k < length - 1; k++) {
                os << screening_hours[i][k] << ", ";
            }
            os << screening_hours[i][length - 1] << endl;
        }
        os << "You can watch these movies in screening rooms: ";
        int room_amount = screening_rooms.size();
        for (int l = 0; l < room_amount - 1; l++)     // loop that shows screening rooms
        {
            os << screening_rooms[l] << ", ";
        }
        os << screening_rooms[room_amount - 1] << endl;
    }
    os << "Have a nice seance!" << endl;
    // printing author, id number and approval date if they were declared
    if (repertoire.get_author() != "None")  os << "Repertoire author: " << repertoire.get_author() << endl;
    if (repertoire.get_id_number() != -1) os << "Repertoire's id number: " << repertoire.get_id_number() << endl;
    os << "Repertoire's approval time: " << repertoire.get_approval_datetime() << endl;
    */
    return os;
}
