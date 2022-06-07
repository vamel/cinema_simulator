#include <iostream>
#include <vector>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include "show.h"

using namespace std;

unsigned int Show::obj_count=0;

Show::Show()
{   // constructor
    set_id();
    Movie movie_default;
    ScreeningRoom screening_room_default;
    screening_room = screening_room_default;
    start_datetime = DateTime();
    init_seats();
    end_datetime = start_datetime;
}

Show::Show(Playable* show, ScreeningRoom screening_room, const DateTime &start_datetime): screening_room(screening_room), start_datetime(start_datetime)
{   // constructor
    try
    {
        init_seats();
        playable = show;
        end_datetime = start_datetime;
        end_datetime.add_minutes(show->get_length());
        set_id();
    }
    catch(const string& mssg)
    {
        cerr << mssg << endl;
    }
}

Show::Show(const Show &obj)
{
    set_id();
    screening_room = obj.screening_room;
    start_datetime = obj.start_datetime;
    end_datetime = obj.end_datetime;
    status = obj.status;
    taken_seats = obj.taken_seats;
    seats = obj.seats;
}

Show::~Show()
{

}

void Show::init_seats()
{   // create vector of rows of seats filled with zeros (false)
    seats = {};
    for (int i=0; i<screening_room.get_rows(); i++)
    {
        vector <bool> row = {};
        for (int j=0; j<screening_room.get_seats(); j++)
        {
            row.push_back(0);
        }
        seats.push_back(row);
    }
}

void Show::if_changes_allowed()
{
    string mssg = "The Movie Screening is ongoing or ended. You can not change any parameters.";
    if (get_status() != "Yet to start") throw mssg; // if status != Yet to start, throw exception
}

// SETTERS

void Show::set_status(const string &status)
{
    string mssg = "Wrong status! (Allowed status: Yet to start, Ongoing, Ended)";
    int statuses_size = sizeof(statuses)/sizeof(statuses[0]);
    auto itr = find(statuses, statuses + statuses_size, status);

    if (itr != end(statuses)) this -> status = status;
    else throw mssg;
}

void Show::set_id()
{
    id = obj_count;
    obj_count++;
}

void Show::set_screening_room(const ScreeningRoom &screening_room)
{
    if_changes_allowed();
    this -> screening_room = screening_room;
}

void Show::set_start_datetime(const DateTime &start_datetime)
{
    this -> start_datetime = start_datetime;
}

void Show::set_end_datetime(const DateTime &end_datetime)
{
    this -> end_datetime = end_datetime;
}

void Show::set_seat_availability(int row_number, int seat_number, bool availability)
{
    if_changes_allowed();
    seats[row_number][seat_number] = availability;
    if (availability) taken_seats++;
    else taken_seats--;
}

bool Show::check_seat_availability(int row_number, int seat_number)
{
    // Check given seat availability, return true if it's taken and false it's available
    // Throw exception if seat does not exist
    string error_mssg = "This seat does not exist! (Row " +  to_string(row_number) + " Seat " + to_string(seat_number) + ")";

    if (check_seat_exist(row_number, seat_number))
    {
        return seats[row_number][seat_number];
    }
    else throw error_mssg;
}

bool Show::buy_seat(int row_number, int seat_number)
{
    if (check_seat_exist(row_number, seat_number) && !check_seat_availability(row_number, seat_number))
    {
        set_seat_availability(row_number, seat_number, 1);
        return true;
    }
    else return false;
}

bool Show::sell_seat(int row_number, int seat_number)
{
    if (check_seat_exist(row_number, seat_number) && check_seat_availability(row_number, seat_number))
    {
        set_seat_availability(row_number, seat_number, 0);
        return true;
    }
    else return false;
}

bool Show::check_seat_exist(int row_number, int seat_number)
{
    // Return false exception if given seat does not exist
    if (row_number < 0 || row_number > screening_room.get_rows() || seat_number < 0 || seat_number > screening_room.get_seats()) return false;
    return true;
}


// MOVIESCREENING METHODS

MovieScreening::MovieScreening(): Show()
{
    Movie movie_default;
    movie = movie_default;
}

MovieScreening::MovieScreening(Movie* movie, ScreeningRoom screening_room, const DateTime &start_datetime): Show(movie, screening_room, start_datetime)
{   // constructor
    try
    {
        init_seats();
        set_end_datetime(start_datetime);
        get_end_datetime().add_minutes(movie->get_length());
        set_id();
    }
    catch(const string& mssg)
    {
        cerr << mssg << endl;
    }
}

MovieScreening::MovieScreening(const MovieScreening &obj): Show(obj)
{
    movie = obj.movie;
}


// CONCERTSHOW METHODS
ConcertShow::ConcertShow(): Show()
{
    Concert concert_default = Concert();
    concert = concert_default;
}

ConcertShow::ConcertShow(Concert* concert_show, ScreeningRoom screening_room, const DateTime &start_datetime): Show(concert_show, screening_room, start_datetime)
{
    try
    {
        init_seats();
        set_end_datetime(start_datetime);
        get_end_datetime().add_minutes(concert_show->get_length());
        set_id();
    }
    catch(const string& mssg)
    {
        cerr << mssg << endl;
    }
}

ConcertShow::ConcertShow(const ConcertShow &obj): Show(obj)
{
    concert = obj.concert;
}


// MEETGREET METHODS
MeetGreet::MeetGreet(): Show()
{
    Meeting meeting_default;
    meeting = meeting_default;
}

MeetGreet::MeetGreet(Meeting* meeting, ScreeningRoom screening_room, const DateTime &start_datetime): Show(meeting, screening_room, start_datetime)
{
    try
    {
        init_seats();
        set_end_datetime(start_datetime);
        get_end_datetime().add_minutes(meeting->get_length());
        set_id();
    }
    catch(const string& mssg)
    {
        cerr << mssg << endl;
    }
}

MeetGreet::MeetGreet(const MeetGreet &obj): Show(obj)
{
    meeting = obj.meeting;
}
