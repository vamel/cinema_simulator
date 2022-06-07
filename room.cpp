#include <iostream>
#include "room.h"

using namespace std;

// Room

Room::Room() : room_number(0), status("Open") {}

Room::Room(int room_num, string status) : room_number(room_num), status(status) {}

int Room::get_room_number() const {
    return room_number;
}

string Room::get_status() const {
    return status;
}

vector<string> Room::get_status_options() {
    return status_options;
}

void Room::set_room_number(int new_num) {
    string mssg = "Room number must be > 0";
    if (room_number < 0) throw mssg;
    else this->room_number = room_number;
}

void Room::set_status(string new_status) {
    string msg = "Incorrect status. [Allowed: Open, Closed]";
    if (find(status_options.begin(), status_options.end(), status) != status_options.end()) {
        status = new_status;
    }
    else {
        throw msg;
    }
}

void Room::close_room() {
    status = "Closed";
}

void Room::open_room() {
    status = "Open";
}


ScreeningRoom::ScreeningRoom(int room_number, string status, int rows, int seats)
{
    set_room_number(room_number);
    set_status(status);
    set_rows(rows);
    set_seats(seats);
}

ScreeningRoom::ScreeningRoom()
{
    set_room_number(0);
    set_status("Open");
    set_rows(0);
    set_seats(0);
}


int ScreeningRoom::get_rows() const
{
    return rows;
}

int ScreeningRoom::get_seats() const
{
    return seats;
}

void ScreeningRoom::set_rows(int rows)
{
    string mssg = "Number of rows must be > 0";
    if (rows < 0) throw mssg;
    else this->rows = rows;
}

void ScreeningRoom::set_seats(int seats)
{
    string mssg = "Number of seats must be > 0";
    if (seats < 0) throw mssg;
    else this->seats = seats;
}