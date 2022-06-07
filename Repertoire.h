#ifndef REPERTOIRE_H
#define REPERTOIRE_H
#include <string>
#include <vector>
#include <map>
#include "datetime.h"
#include "show.h"

using namespace std;

class Repertoire
{
private:
    // private attributes of Repertoire class
    int id_number;
    static int count;
    string author;
    DateTime approval_datetime;
    DateTime start_datetime;
    DateTime end_datetime;
    int days_duration = 7; // how many days will repertoire last

//    map<int, vector<MovieScreening*>> screening_hours;
    map<int, vector<Show*>> screening_hours;

    void set_repertoire_end();
    void init_screening_hours(vector <ScreeningRoom*> screening_rooms);

public:
    Repertoire(const string &repertoire_author, DateTime start_datetime, vector <ScreeningRoom*> screening_rooms);  // constructor
    Repertoire();                                  // default constructor
    Repertoire(const Repertoire & repertoire);     // copying constructor
    ~Repertoire();                                 // destructor

    // setters
    void set_author(string new_author);
    void set_approval_datetime(DateTime datetime);
    void set_repertoire_start(DateTime datetime);

    // methods that add a movie to the repertoire without overwriting it
//    bool add_movie_screening(MovieScreening* movie_screening);
    bool add_show(Show* show);

    // getters
    int get_id_number() const;
    string get_author() const;
    DateTime get_approval_datetime() const;
    DateTime get_start_datetime() const;
    DateTime get_end_datetime() const;
    int get_days_duration() const;
//    map<int, vector<MovieScreening*>> get_screening_hours() const;
//    vector<MovieScreening*> get_available_screening_hours() const;
    map<int, vector<Show*>> get_show_hours() const;
    vector<Show*> get_available_show_hours() const;

    vector <int> get_taken_rooms_numbers();

    bool operator==(const Repertoire& repertoire) const;    // overload == operator
    bool operator!=(const Repertoire& repertoire) const;    // overload != operator
    Repertoire& operator=(const Repertoire &repertoire);    // overload = operator
    friend ostream &operator<<(ostream &os, Repertoire &repertoire);    // overload output operator

};

#endif
