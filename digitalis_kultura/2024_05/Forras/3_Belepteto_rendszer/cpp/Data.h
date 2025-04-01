#ifndef DATA_H
#define DATA_H

#include "Time.h"

#include <string>
#include <vector>
#include <fstream>

struct Data {
	enum Action {
		Enter = 1, Exit, Lunch, Library
	};

	std::string id;
	Time time;
	Action action;
};

std::vector<Data> read_file(const std::string&);
std::istream& parse_data(std::istream&, Data&);

#endif