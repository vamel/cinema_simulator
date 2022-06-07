#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>

using namespace std;

class DateTime
{
    private:
        unsigned int year;
        unsigned int month;
        unsigned int day;
        unsigned int hours;
        unsigned int minutes;

        unsigned int days_in_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    public:
        DateTime();
        DateTime(unsigned int year, unsigned int month, unsigned int day, unsigned int hours, unsigned int minutes);
        DateTime(const DateTime &datetime);

        friend ostream& operator << (ostream &output, const DateTime &datetime);
        bool operator == (const DateTime &datetime);
        bool operator != (const DateTime &datetime);
        bool operator < (const DateTime &datetime);
        bool operator <= (const DateTime &datetime);
        bool operator > (const DateTime &datetime);
        bool operator >= (const DateTime &datetime);
        DateTime& operator = (const DateTime &datetime);

        void add_minutes(unsigned int add_min);
        void add_days(unsigned int add_day);

        string to_str();
};

#endif