#ifndef CINEMA_H
#define CINEMA_H

#include <iostream>
#include <vector>
#include <fstream>
#include "purchasable.h"
#include "json.hpp"
#include "datetime.h"
#include "shop.h"
#include "Repertoire.h"

using namespace std;

class Cinema
{
private:
    string name;
    DateTime start_datetime;
    vector <Movie*> movies;
    vector <Concert*> concerts;
    vector <Meeting*> meetings;
    vector <ScreeningRoom*> screening_rooms;
    vector <Snack*> snacks;
    vector <Show*> shows;
    vector <TicketSeller*> ticket_sellers;
    vector <TicketBooth*> ticket_booths;
    vector <SnackSeller*> snack_sellers;
    vector <SnackShop*> snack_shops;
    Repertoire repertoire; // current repertoire
    string log_filename;

    void load_shows_from_file();
    void load_screening_rooms_from_file();
    void load_snacks_from_file();
    void load_workers_from_file();

    void create_show(DateTime start_datetime);
    int free_seats(const vector <vector <bool>> &seats);
    bool buy_tickets(Show &show, int number);
    void buy_tickets_simulation(DateTime datetime, vector <string> &messages);
    void buy_snacks_simulation(DateTime datetime, vector <string> &messages);
    void create_new_repertoire(DateTime datetime, vector <string> &messages);
    void update_show_status(DateTime datetime, vector <string> &messages);
    void generate_ticket_booths(int amount);
    void generate_snack_shops(int amount);
    int generate_rand_number(int min, int max);
    bool get_probability_of_event(unsigned int probability_percent);
    void program_in_loop(DateTime datetime);
    void write_log_to_file(string message);
    string get_log_filename();

public:
    Cinema(string name, DateTime start_datetime);
    ~Cinema();
    void start_simulation(int simulation_iterations, int add_minutes, int loop_time);

};

#endif
