#include <iostream>
#include "Time.h"

const int Time::MaxHours = 24;
const int Time::MaxMinutes = 60;
const int Time::MaxSeconds = 60;

unsigned int Time::getHours() const{
	return hours;
}

unsigned int Time::getMinutes() const {
	return minutes;
}

unsigned int Time::getSeconds() const {
	return seconds;
}

Time::Time() : hours(0), minutes(0), seconds(0) {}

Time::Time(unsigned int hours, unsigned int minutes, unsigned int seconds) {
	if (isTimeValid(hours, minutes, seconds) == 0) {
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
}

std::string Time::toString() const {
	std::string stringHours;
	std::string stringMinutes;
	std::string stringSeconds;

	if (hours < 10) {
		stringHours = "0" + std::to_string(hours);
	}
	else {
		stringHours = std::to_string(hours);
	}
	if (minutes < 10) {
		stringMinutes = "0" + std::to_string(minutes);
	}
	else {
		stringMinutes = std::to_string(minutes);
	}
	if (seconds < 10) {
		stringSeconds = "0" + std::to_string(seconds);
	}
	else {
		stringSeconds = std::to_string(seconds);
	}
	return stringHours + ":" + stringMinutes + ":" + stringSeconds;
}

bool Time::isTimeValid(unsigned int hours, unsigned int minutes, unsigned int seconds) {
	if (hours < MaxHours && minutes < MaxMinutes && seconds < MaxSeconds) {
		return true;
	}
	else {
		return false;
	}
}

Time Time::parse(const std::string& time) {
	std::string substrHours = time.substr(0, 2);
	unsigned int intSubstrHours = stoi(substrHours);
	std::string substrMinutes = time.substr(3, 2);
	unsigned int intSubstrMinutes = stoi(substrMinutes);
	std::string substrSeconds = time.substr(6, 2);
	unsigned int intSubstrSeconds = stoi(substrSeconds);
	return Time(intSubstrHours, intSubstrMinutes, intSubstrSeconds);
}

int Time::diffSeconds(const Time* time1, const Time* time2) {
	int time1Seconds = (time1->hours) * 3600 + (time1->minutes) * 60 + time1->seconds;
	int time2Seconds = (time2->hours) * 3600 + (time2->minutes) * 60 + time2->seconds;
	return time1Seconds - time2Seconds;
}



