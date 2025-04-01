#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>

struct Time {
	int hours;
	int minutes;
};

inline int in_minutes(const Time& t) {
	return t.hours * 60 + t.minutes;
}

inline bool operator<(const Time& t1, const Time& t2) {
	return in_minutes(t1) < in_minutes(t2);
}

inline std::ostream& operator<<(std::ostream& os, const Time& t) {
	return os << std::setw(2) << std::setfill('0') << t.hours << ':'
		<< std::setw(2) << std::setfill('0') << t.minutes;
}

Time parse_time(std::istream&);

#endif