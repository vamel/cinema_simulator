#ifndef PURCHASABLE_H
#define PURCHASABLE_H

#include <iostream>
#include <vector>
#include "show.h"

using namespace std;

class Purchasable
{
    private:
        string name; // name of the item e.g. movie ticket, cola...
        double first_price; // first price of the item
        double discount_price; // price after discount
        static vector <string> discount_types;
        static vector <int> discount_values;
    protected:
        static int find_in_discount_types(string discount_value);
    public:
        Purchasable();
        Purchasable(string name, double first_price);
        string get_name() const;
        double get_first_price() const;
        double get_discount_price() const;

        void set_name(string name);
        void set_first_price(double first_price);
        void set_discount_price(double discount_price);
        static void add_discount(string type, int discount);

        virtual void apply_discount(string discount_type);
        virtual void print() const = 0;
        virtual ~Purchasable() {};
};

class Ticket: public Purchasable
{
    private:
        Show show;
        int row;
        int seat;
    public:
        Ticket();
        Ticket(MovieScreening &movie_screening, int row, int seat, string name, double first_price, string discount_type);
        virtual void print() const;
};

class Snack: public Purchasable
{
    public:
        Snack();
        Snack(string name, double first_price, string discount_type);
        virtual void print() const;
};

#endif