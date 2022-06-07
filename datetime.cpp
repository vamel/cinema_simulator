#include <iostream>
#include "datetime.h"

using namespace std;

DateTime::DateTime(): year(1000), month(1), day(1), hours(0), minutes(0)
{

}

DateTime::DateTime(unsigned int year, unsigned int month, unsigned int day, unsigned int hours, unsigned int minutes)
{
    this -> year = year;
    if (month > 12) throw "Month must be from range (1,12).";
    else this -> month = month;
    if (day > days_in_months[month-1]) throw "Wrong number of days in month.";
    else this -> day = day;
    if (hours > 23) throw "Hour must be from range (0,23).";
    else this -> hours = hours;
    if (minutes > 59) throw "Minutes must be from range (0,59).";
    else this -> minutes = minutes;
}

DateTime::DateTime(const DateTime &datetime): year(datetime.year), month(datetime.month), day(datetime.day), hours(datetime.hours), minutes(datetime.minutes)
{

}

ostream& operator << (ostream &output, const DateTime &datetime)
{
    auto make_string = [](int date_element)
    {
        string str_element = to_string(date_element);
        if (date_element < 10)
        {
            str_element.push_back(str_element[0]);
            str_element[0] = '0';
        }
        return str_element;
    };
    
    output << datetime.year << "-" << make_string(datetime.month) << "-" << make_string(datetime.day) << " " << make_string(datetime.hours) << ":" << make_string(datetime.minutes);
    return output;
}

bool DateTime::operator == (const DateTime &datetime)
{
    if (year != datetime.year) return false;
    if (month != datetime.month) return false;
    if (day != datetime.day) return false;
    if (hours != datetime.hours) return false;
    if (minutes != datetime.minutes) return false;
    return true;
}

bool DateTime::operator != (const DateTime &datetime)
{
    if (year == datetime.year &&
        month == datetime.month &&
        day == datetime.day &&
        hours == datetime.hours &&
        minutes == datetime.minutes) return false;
    return true;
}

bool DateTime::operator < (const DateTime &datetime)
{
    if (year == datetime.year)
    {
        if (month == datetime.month)
        {
            if (day == datetime.day)
            {
                if (hours == datetime.hours)
                {
                    if (minutes == datetime.minutes) return false;
                    else if (minutes < datetime.minutes) return true;
                    return false;
                }
                else
                {
                    if (hours < datetime.hours) return true;
                    return false;
                }
            }
            else
            {
                if (day < datetime.day) return true;
                return false;
            }
        }
        else
        {
            if (month < datetime.month) return true;
            return false;
        }
    }
    else
    {
        if (year < datetime.year) return true;
        return false;
    }
}

bool DateTime::operator <= (const DateTime &datetime)
{
    if (*this < datetime || *this == datetime) return true;
    return false;
}

bool DateTime::operator > (const DateTime &datetime)
{
    if (year == datetime.year)
    {
        if (month == datetime.month)
        {
            if (day == datetime.day)
            {
                if (hours == datetime.hours)
                {
                    if (minutes == datetime.minutes) return false;
                    else if (minutes > datetime.minutes) return true;
                    return false;
                }
                else
                {
                    if (hours > datetime.hours) return true;
                    return false;
                }
            }
            else
            {
                if (day > datetime.day) return true;
                return false;
            }
        }
        else
        {
            if (month > datetime.month) return true;
            return false;
        }
    }
    else
    {
        if (year > datetime.year) return true;
        return false;
    }
}

bool DateTime::operator >= (const DateTime &datetime)
{
    if (*this > datetime || *this == datetime) return true;
    return false;
}

DateTime& DateTime::operator = (const DateTime &datetime)
{
    year = datetime.year;
    month = datetime.month;
    day = datetime.day;
    hours = datetime.hours;
    minutes = datetime.minutes;
    return *this;
}

void DateTime::add_minutes(unsigned int add_mins)
{
    minutes += add_mins;
    if (minutes >= 60)
    {
        hours += minutes/60;
        minutes = 0 + minutes%60;
    }
    if (hours >= 24)
    {
        hours = 0 + hours%24;
        add_days(1);
    }
}

void DateTime::add_days(unsigned int add_days)
{
    day += add_days;

    while (day > days_in_months[month-1])
    {
        day -= days_in_months[month-1];
        month++;
        if (month > 12)
        {
            month = 1;
            year ++;
        }
    }
}

string DateTime::to_str()
{
    auto make_string = [](int date_element)
    {
        string str_element = to_string(date_element);
        if (date_element < 10)
        {
            str_element.push_back(str_element[0]);
            str_element[0] = '0';
        }
        return str_element;
    };
    string result = to_string(year);
    result += "-" + make_string(month) + "-" + make_string(day) + " " + make_string(hours) + ":" + make_string(minutes);
    return result;
}
