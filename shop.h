#ifndef SHOP_H
#define SHOP_H

#include "worker.h"
#include "room.h"

using namespace std;

class TicketBooth : public Room {
private:
    Worker* worker;
    int tickets_sold = 0;
    vector<Show*> shows;
public:
    TicketBooth(int room_num, string stat, Worker* worker, vector<Show*>);
    TicketBooth(int room_num, string stat, Worker* worker);
    TicketBooth();

    const Worker* get_worker() const;
    int get_tickets_sold() const;
    vector<Show*> get_shows();

    void set_worker(Worker* new_worker);
    void set_shows(vector<Show*> shows);

    void reset_tickets_sold();
    string sell_ticket(Show* show, int amount = 1);

    void add_show(Show*);
    void add_shows(vector<Show*> shows);
    void remove_show(Show*);

    friend ostream& operator<<(ostream& os, TicketBooth& ticketbooth);
};

class SnackShop : public Room {
private:
    Worker* worker;
    int snacks_sold = 0;
    vector<Snack*> types_of_snacks;
public:
    SnackShop(int room_num, string stat, Worker* worker, vector<Snack*> snacks);
    SnackShop(int room_num, string stat, Worker* worker);
    SnackShop();

    const Worker* get_worker() const;
    int get_snacks_sold() const;
    vector<Snack*> get_types_of_snacks();

    void set_worker(Worker* new_worker);
    void set_types_of_snacks_sold(vector<Snack*> types_of_snacks);

    void reset_snacks_sold();
    void sell_snack(Snack* snack, int amount = 1);
    void add_snack(Snack* new_snack);
    void remove_snack(Snack* snack);

    friend ostream& operator<<(ostream& os, SnackShop& snackshop);

};

#endif
