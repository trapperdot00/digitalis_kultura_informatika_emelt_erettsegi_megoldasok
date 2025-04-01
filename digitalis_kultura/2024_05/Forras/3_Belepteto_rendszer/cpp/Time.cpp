#include "Time.h"

Time parse_time(std::istream& is) {
	int hh = 0;
	if (!(is >> hh))
		throw std::runtime_error{"hh"};
	char delim = 0;
	if (!is.get(delim) || delim != ':')
		throw std::runtime_error{ "no delim" };
	int mm = 0;
	if (!(is >> mm))
		throw std::runtime_error{ "mm" };
	return Time{ hh, mm };
}