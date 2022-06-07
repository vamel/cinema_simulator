#include <iostream>
#include <vector>
#include "purchasable.h"

using namespace std;

// PURCHASABLE

vector <string> Purchasable::discount_types = {"Adult", "Child", "Senior", "Student", "Normal", "Weekends", "Tuesdays"};
vector <int> Purchasable::discount_values = {0, 40, 50, 30, 0, 10, 25};

Purchasable::Purchasable(): name("No Name"), first_price(0), discount_price(0) {}

Purchasable::Purchasable(string name, double first_price): name(name), first_price(first_price) {}

int Purchasable::find_in_discount_types(string discount_value)
{   // find string in array, return it's position or -1 if not found
    for (unsigned int i=0; i<discount_types.size(); i++)
    {
        if (discount_types[i] == discount_value) return i;
    }
    return -1;
}

void Purchasable::add_discount(string type, int value)
{
    if (find_in_discount_types(type) == -1)
    {
        discount_types.push_back(type);
        discount_values.push_back(value);
    }
    else throw "This discount type already exist! (" + type + ")";
}

string Purchasable::get_name() const
{
    return name;
}

double Purchasable::get_first_price() const
{
    return first_price;
}

double Purchasable::get_discount_price() const
{
    return discount_price;
}

void Purchasable::set_name(string name)
{
    this -> name = name;
}

void Purchasable::set_first_price(double first_price)
{
    this -> first_price = first_price;
}

void Purchasable::set_discount_price(double discount_price)
{
    this -> discount_price = discount_price;
}

void Purchasable::apply_discount(string discount_type)
{
    string mssg = "This discount does not exist! (" + discount_type + ")";
    if (find_in_discount_types(discount_type) != -1)
    {
        set_discount_price(get_first_price() * (100 - discount_values[find_in_discount_types(discount_type)]) / 100);
    }
    else throw mssg;
}

// TICKET

Ticket::Ticket(): Purchasable(), row(0), seat(0)
{
    MovieScreening movie_screening;
    this -> show = movie_screening;
    set_first_price(0);
    set_discount_price(0);
}

Ticket::Ticket(MovieScreening &movie_screening, int row, int seat, string name, double first_price, string discount_type): Purchasable(name, first_price), show(show)
{
    if (movie_screening.buy_seat(row, seat))
    {
        this -> row = row;
        this -> seat = seat;
        apply_discount(discount_type);
    }
    else throw (string)"You can't buy this ticket - the seat is already taken!";
}

void Ticket::print() const
{
    cout << get_name() << endl;
    cout << show.get_show()->get_title() << endl;
    cout << "Row " << row << " Seat " << seat << endl;
    cout << "Price: " << get_discount_price() << " PLN" << endl;
}

// SNACK

Snack::Snack(): Purchasable()
{
    set_first_price(0);
    set_discount_price(0);
}

Snack::Snack(string name, double first_price, string discount_type): Purchasable(name, first_price)
{
    apply_discount(discount_type);
}

void Snack::print() const
{
    cout << get_name() << endl;
    cout << "Price: " << get_discount_price() << " PLN" << endl;
}
