#include <iostream>
#include <algorithm>
#include "worker.h"

using namespace std;

// string days_in_a_week[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

// WORKER
unsigned int Worker::count = 0;

Worker::Worker(const string & first_name, const string & second_name, int salary): first_name(first_name), second_name(second_name),
                                                            salary(salary)
{
    id = count;
    ++count;
    this->on_leave = false;
    this->hours_worked_this_month = 0;
}

Worker::Worker(): first_name("None"), second_name("None"), salary(0)
{
    id = count;
    ++count;
    this->on_leave = false;
    this->hours_worked_this_month = 0;
}

void Worker::set_id(int new_id)
{
    id = new_id;
}

void Worker::set_name(const string &new_first_name, const string &new_second_name)
{
    first_name = new_first_name;
    second_name = new_second_name;
}

void Worker::set_salary(int new_salary)
{
    salary = new_salary;
}

void Worker::update_hours_worked_this_month(int hours)
{
    hours_worked_this_month += hours;
}

Worker::~Worker() {}


// TICKET SELLER
TicketSeller::TicketSeller():Worker() {}

TicketSeller::TicketSeller(const string &first_name, const string &second_name, int salary, vector<Show*> shows):Worker(
            first_name, second_name, salary)
{
    shows = move(shows);
}

TicketSeller::TicketSeller(const string &first_name, const string &second_name, int salary):Worker(first_name, second_name, salary) {}

void TicketSeller::set_shows(vector<Show*> shows)
{
    shows = move(shows);
}

string TicketSeller::sell_ticket(Show *show, int amount)
{
    string tickets = " ticket ";
    if (amount > 1) tickets = " tickets ";
    tickets_sold += amount;
    string msg = " " + this->get_first_name() + " " + this->get_second_name() + " sold " +
            to_string(amount) + tickets + "for a " + show->type + "(Show ID: " +
            to_string(show->get_id()) + "). (Show: " + show->get_show()->get_title() + ")";
    return msg;
}

void TicketSeller::add_show(Show* show)
{
    shows.push_back(show);
}

void TicketSeller::add_shows(vector<Show*> new_shows)
{
    shows.insert(shows.end(), new_shows.begin(), new_shows.end());
}

void TicketSeller::remove_show(Show* show)
{
    int pos = -1;
    for (unsigned int i=0; i < shows.size(); i++)
    {
        if (show == shows[i])
        {
            pos = i;
            break;
        }
    }
    if (pos == -1)
    {
        cout << "No movie found.\n";
    }
    else
    {
        shows.erase(shows.begin()+pos);
        cout << "Movie removed.\n";
    }
}

// SNACK SELLER
SnackSeller::SnackSeller():Worker() {}

SnackSeller::SnackSeller(const string &first_name, const string &second_name, int salary):Worker(first_name, second_name, salary) {}

SnackSeller::SnackSeller(const string &first_name, const string &second_name, int salary, vector<Snack *> snacks)
{
    types_of_snacks = move(snacks);
}

void SnackSeller::set_types_of_snacks_sold(vector<Snack*> snacks)
{
    types_of_snacks = move(snacks);
}

void SnackSeller::sell_snack(Snack *snack, int amount)
{
    if (find(types_of_snacks.begin(), types_of_snacks.end(), snack) != types_of_snacks.end())
    {
        if (amount == 1)
        {
            cout << "Sold 1 snack.\n";
            ++snacks_sold;
        }
        else
        {
            cout << "Sold " << amount << " snacks.\n";
            snacks_sold += amount;
        }
    }
    else
    {
        cout << "Can't sell this snack.\n";
    }
}

void SnackSeller::add_snack(Snack* new_snack)
{
    types_of_snacks.push_back(new_snack);
}

void SnackSeller::remove_snack(Snack* snack)
{
    int pos = -1;
    for (unsigned int i=0; i < types_of_snacks.size(); i++)
    {
        if (snack == types_of_snacks[i])
        {
            pos = i;
            break;
        }
    }
    if (pos == -1)
    {
        cout << "Snack not found.\n";
    }
    else
    {
        types_of_snacks.erase(types_of_snacks.begin()+pos);
        cout << "Snack removed.\n";
    }
}
