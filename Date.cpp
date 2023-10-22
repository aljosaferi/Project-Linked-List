#include "Date.h"
#include <iostream>
#include <ctime>
#include <chrono>

#pragma warning(disable : 4996)

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.getDay() << '.' << date.getMonth() << '.' << date.getYear();
    return os;
}

Date::Date() : day(20), month(9), year(2003) {

}

Date::Date(unsigned int day, unsigned int month, unsigned int year) : day(day), month(month), year(year) {}

unsigned int Date::getDay() const {
    return day;
}

void Date::setDay(unsigned int day) {
    Date::day = day;
}

unsigned int Date::getMonth() const {
    return month;
}

void Date::setMonth(unsigned int month) {
    Date::month = month;
}

unsigned int Date::getYear() const {
    return year;
}

void Date::setYear(unsigned int year) {
    Date::year = year;
}

std::string Date::toString() const {
    return std::to_string(day) + ". " + std::to_string(month) + ". " + std::to_string(year);
}

Date Date::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return { (unsigned int)ltm->tm_mday, (unsigned int)(1 + ltm->tm_mon), (unsigned int)(1900 + ltm->tm_year) };
}

unsigned int Date::daysSinceEpoch(const Date& date) { /* Rata Die day one is 0001-01-01 */
    unsigned int d = date.day;
    unsigned int m = date.month;
    unsigned int y = date.year;
    if (m < 3)
        y--, m += 12;
    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}

int Date::getDifferenceDays(const Date& date1, const Date& date2) {
    return daysSinceEpoch(date1) - daysSinceEpoch(date2);
}

bool Date::operator==(const Date& other) const {
    if (this == &other) {
        return true;
    }
    if (this->day == other.getDay() && this->month == other.getMonth() && this->year == other.getYear()) {
        return true;
    }
    return false;
}

Date& Date::operator++() { //prefix
    int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int month = this->month - 1;
    if (this->day == months[month]) {
        this->day = 1;
        this->month++;
        if (this->month == 13) {
            this->month = 1;
            this->year++;
        }
    }
    else {
        this->day++;
    }
    return *this;
}
Date Date::operator++(int dummy) { //postfix
    Date temp(*this);
    ++(*this);
    return temp;
}

bool Date::operator<(const Date& other) const {
    if (getDifferenceDays(*this, other) < 0) {
        return true;
    }
    if (*this == other) {
        return false;
    }

    return false;
}
bool Date::operator>(const Date& other) const {
    if (other < *this) {
        return true;
    }
    if (*this == other) {
        return false;
    }
    //TODO
    return false;
}
