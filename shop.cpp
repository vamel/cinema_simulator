#include "shop.h"

using namespace std;

TicketBooth::TicketBooth(int room_num, string stat, Worker* worker, vector<Show*>):Room(room_num, stat), worker(worker) {shows = move(shows);}
TicketBooth::TicketBooth(int room_num, string stat, Worker* worker): Room(room_num, stat), worker(worker) {}
TicketBooth::TicketBooth() : Room() {
    TicketSeller* default_ticket_seller;
    worker = default_ticket_seller;
}

const Worker* TicketBooth::get_worker() const {
    return worker;
}

int TicketBooth::get_tickets_sold() const{
    return tickets_sold;
}

vector<Show*> TicketBooth::get_shows() {
    return shows;
}

void TicketBooth::set_worker(Worker* new_worker) {
    worker = new_worker;
}

void TicketBooth::set_shows(vector<Show*> shows)
{
    shows = move(shows);
}

void TicketBooth::reset_tickets_sold() { 
    tickets_sold = 0; 
}

string TicketBooth::sell_ticket(Show* show, int amount){
    string tickets = " ticket ";
    if (amount > 1) tickets = " tickets ";
    tickets_sold += amount;
    string msg = " " + worker->get_first_name() + " " + worker->get_second_name() + " sold " +
        to_string(amount) + tickets + "for a " + show->type + "(Show ID: " +
        to_string(show->get_id()) + "). (Show: " + show->get_show()->get_title() + ")." +
        "Ticket sold in ticket booth number " + to_string(room_number) + ".";
    return msg;
}

void TicketBooth::add_show(Show* show){
    shows.push_back(show);
}

void TicketBooth::add_shows(vector<Show*> new_shows){
    shows.insert(shows.end(), new_shows.begin(), new_shows.end());
}

void TicketBooth::remove_show(Show* show){
    int pos = -1;
    for (unsigned int i = 0; i < shows.size(); i++){
        if (show == shows[i]){
            pos = i;
            break;
        }
    }
    if (pos == -1){
        cout << "No movie found.\n";
    }
    else{
        shows.erase(shows.begin() + pos);
        cout << "Movie removed.\n";
    }
}

ostream& operator<<(ostream& os, TicketBooth& ticketbooth) {
    os << "Ticket booth no. " << ticketbooth.room_number << endl;
    os << "Status: " << ticketbooth.status << endl;
    os << "Employee: " << ticketbooth.worker->get_first_name() << endl;
    return os;
}


SnackShop::SnackShop(int room_num, string stat, Worker* worker, vector<Snack*> snacks):Room(room_num, status), worker(worker) { 
    types_of_snacks = move(snacks); 
}
SnackShop::SnackShop(int room_num, string stat, Worker* worker):Room(room_num, stat), worker(worker) {}
SnackShop::SnackShop(): Room() {
    SnackSeller* default_snack_seller;
    worker = default_snack_seller;
}

const Worker* SnackShop::get_worker() const {
    return worker;
}

int SnackShop::get_snacks_sold() const {
    return snacks_sold;
}

vector<Snack*> SnackShop::get_types_of_snacks() {
    return types_of_snacks;
}

void SnackShop::set_worker(Worker* new_worker) {
    this->worker = new_worker;
}

void SnackShop::set_types_of_snacks_sold(vector<Snack*> snacks){
    types_of_snacks = move(snacks);
}
void SnackShop::reset_snacks_sold() {
    snacks_sold = 0;
}

void SnackShop::sell_snack(Snack* snack, int amount){
    if (find(types_of_snacks.begin(), types_of_snacks.end(), snack) != types_of_snacks.end()){
        if (amount == 1){
            cout << "Sold 1 snack.\n";
            ++snacks_sold;
        }
        else{
            cout << "Sold " << amount << " snacks.\n";
            snacks_sold += amount;
        }
    }
    else{
        cout << "Can't sell snack.\n";
    }
}

void SnackShop::add_snack(Snack* new_snack){
    types_of_snacks.push_back(new_snack);
}

void SnackShop::remove_snack(Snack* snack){
    int pos = -1;
    for (unsigned int i = 0; i < types_of_snacks.size(); i++){
        if (snack == types_of_snacks[i]){
            pos = i;
            break;
        }
    }
    if (pos == -1){
        cout << "Snack not found.\n";
    }
    else{
        types_of_snacks.erase(types_of_snacks.begin() + pos);
        cout << "Snack removed.\n";
    }
}

ostream& operator<<(ostream& os, SnackShop& snackshop) {
    os << "Snack shop no. " << snackshop.room_number << endl;
    os << "Status: " << snackshop.status << endl;
    os << "Employee: " << snackshop.worker->get_first_name() << endl;
    return os;
}
