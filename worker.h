#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <string>
#include <vector>
#include "datetime.h"
#include "purchasable.h"
#include "show.h"

using namespace std;

class Worker
{
private:
    string first_name;
    string second_name;
    int id;
    static unsigned int count;
    //vector<string> working_days; -> days in which worker is doing his/her job
    //int working_hours;           -> amount of hour the worker is working in a week
    int salary;
    int hours_worked_this_month;
    bool on_leave;

public:
    // getters
    int get_id() const {return id;};
    string get_first_name() const {return first_name;};
    string get_second_name() const {return second_name;};
    int get_salary() const {return salary;};
    bool is_on_leave() const {return on_leave;};
    //vector<string> get_working_days() const {return working_days;};
    //int get_working_hours() const {return working_hours;};
    int get_hours_worked() const {return hours_worked_this_month;};

    // setters
    void set_id(int new_id);
    void set_name(const string & new_first_name, const string & new_second_name);
    void set_salary(int new_salary);
    //void set_workdays(string days[]);
    //void set_working_hours(int hours);

    Worker();
    Worker(const string & first_name, const string & second_name, int salary);
    virtual ~Worker();
    void go_on_leave() {on_leave = true;};
    void update_hours_worked_this_month(int hours);
    void reset_hours_worked_this_month() {hours_worked_this_month = 0;};
};

class TicketSeller: public Worker
{
private:
    int tickets_sold = 0;
    vector<Show*> shows;   // events that this sellers can sell tickets to

public:
    TicketSeller();
    TicketSeller(const string & first_name, const string & second_name, int salary, vector<Show*>);
    TicketSeller(const string & first_name, const string & second_name, int salary);

    // getters
    int get_tickets_sold() const {return tickets_sold;};
    vector<Show*> get_shows() {return shows;};

    // setter
    void set_shows(vector<Show*>);

    void reset_tickets_sold() {tickets_sold = 0;};

    string sell_ticket(Show* show, int amount=1);

    // enable and disable selling tickets for an event
    void add_show(Show*);
    void add_shows(vector<Show*> shows);
    void remove_show(Show*);
};

class SnackSeller: public Worker
{
private:
    int snacks_sold = 0;
    vector<Snack*> types_of_snacks;
public:
    SnackSeller();
    SnackSeller(const string & first_name, const string & second_name, int salary, vector<Snack*> snacks);
    SnackSeller(const string & first_name, const string & second_name, int salary);

    // getters
    int get_snacks_sold() const {return snacks_sold;};
    vector<Snack*> get_types_of_snacks() {return types_of_snacks;};

    // setter
    void set_types_of_snacks_sold(vector<Snack*> types_of_snacks);

    void reset_snacks_sold() {snacks_sold = 0;};

    void sell_snack(Snack* snack, int amount=1);

    // enable and disable selling certain type of snack
    void add_snack(Snack* new_snack);
    void remove_snack(Snack* snack);

};

#endif
