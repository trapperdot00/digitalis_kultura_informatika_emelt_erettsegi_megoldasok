#include "Data.h"

std::istream& parse_data(std::istream& is, Data& d) {
	std::string id;
	if (!(is >> id))
		return is;
	Time t = parse_time(is);
	int action = 0;
	if (!(is >> action))
		return is;
	d = Data{ id, t, static_cast<Data::Action>(action) };
	return is;
}

std::vector<Data> read_file(const std::string& filename) {
	std::ifstream is{ filename };
	if (!is)
		throw std::runtime_error{ "cant open file" };
	std::vector<Data> vec;
	for (Data d; is; ) {
		if (parse_data(is, d))
			vec.push_back(std::move(d));
	}
	return vec;
}