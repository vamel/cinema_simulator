#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include "json.hpp"
#include "cinema.h"
#include "datetime.h"

using namespace std;
using json = nlohmann::json;

vector<int> read_launch_params(string file_name)
{
    int length = file_name.length();
    if (length <= 5) throw ".json file is needed";
    if (file_name[length-1] != 'n' || file_name[length-2] != 'o' || file_name[length-3] != 's' || file_name[length-4] != 'j' || file_name[length-5] != '.') throw ".json file is needed";
    else
    {
        ifstream ifs(file_name);
        if (!ifs.good()) throw "Coud not open this file";
        json jf = json::parse(ifs);
        vector<int> params = {};
        params.push_back(jf["start_datetime"]["year"]);
        params.push_back(jf["start_datetime"]["month"]);
        params.push_back(jf["start_datetime"]["day"]);
        params.push_back(jf["start_datetime"]["hours"]);
        params.push_back(jf["start_datetime"]["minutes"]);
        params.push_back(jf["add_minutes"]);
        params.push_back(jf["loop_time"]);
        params.push_back(jf["simulation_time"]);
        return params;
    }
}

void simulation(string start_params_file_name)
{
    vector<int> params;
    try
    {
        params = read_launch_params(start_params_file_name);
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    DateTime date = DateTime(params[0], params[1], params[2], params[3], params[4]); // data startu symulacji
    int add_minutes = params[5]; // o ile minut będziemy przesuwali się do przodu przy jednej pętli
    int loop_time = params[6]; // ile sekund trwa jedna pętla
    int simulation_time = params[7]; // ile iteracji pętli ma trwać symulacja
    // z takimi danymi co 5 sekund przesuwamy się o 10 minut do przodu, symulacja będzie trwała 10 iteracji minut czyli 50 sekund
    Cinema kino("Cinema City", date);
    kino.start_simulation(simulation_time, add_minutes, loop_time);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "File name is needed (.json)";
        return -1;
    }
    else if (argc > 2)
    {
        cout << "You passed to many arguments. Only one is needed - file name (.json)";
        return -1;
    }
    else 
    {
        simulation(argv[1]);
    }
    return 0;
}