#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"

using namespace std;

class Room {
protected:
    int room_number;
    vector<string> status_options = { "Open", "Closed" };
    string status;
public:
    Room();
    Room(int room_number, string status);
    virtual ~Room() {};

    int get_room_number() const;
    string get_status() const;
    vector<string> get_status_options();

    void set_room_number(int number);
    void set_status(string new_status);

    void close_room();
    void open_room();
};


class ScreeningRoom :public Room
{
private:
    int rows; // number of rows of seats in the room
    int seats; // number of seats in each row

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ScreeningRoom, room_number, rows, seats);
    ScreeningRoom(int room_number, string status, int rows, int seats); // constructor
    ScreeningRoom();

    // getters
    int get_rows() const;
    int get_seats() const;

    //setters
    void set_rows(int rows);
    void set_seats(int seats);
};

#endif