#ifndef UNTITLED1_SHOW_H
#define UNTITLED1_SHOW_H

#include <iostream>
#include <vector>
#include <string>
#include "datetime.h"
#include "room.h"
//#include "screening_room.h"
#include "playable.h"

class Show
{
//public:
private:
    ScreeningRoom screening_room; // Screening Room object
    string status = "Yet to start"; // status of screening
    static unsigned int obj_count;
    unsigned int id;
    string statuses[3] = {"Yet to start", "Ongoing", "Ended"}; // array of available statuses
    DateTime start_datetime;
    DateTime end_datetime;
    Playable* playable;

protected:
    int taken_seats=0; // number of taken seats in room
    vector <vector <bool>> seats; // availability of each seat in a room

    void init_seats(); // create vector seats with given number of rows and seats
    void if_changes_allowed(); // check if status allows to make any changes to object
    bool check_seat_exist(int row_number, int seat_number); //checks if seat exist in this room

public:
    string type;
    Show(); // default constructor
    Show(Playable* show, ScreeningRoom screening_room, const DateTime &start_datetime); // constructor
    Show(const Show &obj); // copy constructor
    virtual ~Show();    //virtual destuctor
    //setters
    void set_id();
    void set_screening_room(const ScreeningRoom &screening_room);
    void set_seat_availability(int row_number, int seat_number, bool availability);
    void set_status(const string &status);
    void set_start_datetime(const DateTime &start_datetime);
    void set_end_datetime(const DateTime &end_datetime);
    const Playable* get_show() const {return playable;};        // get the thing we are going to play

    //getters
    unsigned int get_id() const {return id;};
    const ScreeningRoom &get_screening_room() const {return screening_room;};
    DateTime get_start_datetime() const {return start_datetime;};
    DateTime get_end_datetime() const {return end_datetime;};
    string get_status() const {return status;};
    int get_taken_seats() const {return taken_seats;};
    vector <vector <bool>> get_seats() const {return seats;};

    bool check_seat_availability(int row_number, int seat_number); // checks availability of seat
    bool buy_seat(int row_number, int seat_number);
    bool sell_seat(int row_number, int seat_number);
};

// CLASS MOVIESCREENING
class MovieScreening: public Show
{
private:
    Movie movie; // Movie object

public:
    MovieScreening();
    MovieScreening(Movie* movie, ScreeningRoom screening_room, const DateTime &start_datetime); // constructor
    MovieScreening(const MovieScreening &obj); // copy constructor
};

// CLASS CONCERTSHOW
class ConcertShow: public Show
{
private:
    Concert concert;    // Concert object

public:
    ConcertShow();
    ConcertShow(Concert* concert, ScreeningRoom screening_room, const DateTime &start_datetime); // constructor
    ConcertShow(const ConcertShow &obj); // copy constructor
};


// CLASS MEETGREET
class MeetGreet: public Show
{
private:
    Meeting meeting;  // Meeting object

public:
    MeetGreet();
    MeetGreet(Meeting* meeting, ScreeningRoom screening_room, const DateTime &start_datetime); // constructor
    MeetGreet(const MeetGreet &obj); // copy constructor
};
#endif
