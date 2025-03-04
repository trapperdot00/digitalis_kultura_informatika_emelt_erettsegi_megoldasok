#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

struct Date {
	int month;
	int day;
};

std::istream& operator>>(std::istream& is, Date& d) {
	return is >> d.month >> d.day;
}

struct Data {
	Date first;
	Date last;
	std::string initials;
	std::string theme;
};

std::istream& operator>>(std::istream& is, Data& d) {
	return is >> d.first >> d.last >> d.initials >> d.theme;
}

std::vector<Data> read_file(const std::string& filename) {
	std::vector<Data> data;
	std::ifstream is{filename};
	for (Data d; is >> d; )
		data.push_back(std::move(d));
	return data;
}

void feladat2(const std::vector<Data>& data) {
	std::cout << "2. feladat\n"
		<< "Az adatsorok száma: "
		<< data.size()
		<< '\n'
		<< "Az először rögzített tábor témája: "
		<< data.front().theme
		<< "\nAz utoljára rögzített tábor témája: "
		<< data.back().theme
		<< '\n';
}

void feladat3(const std::vector<Data>& data) {
	std::cout << "3. feladat\n";
	bool found = false;
	for (const Data& d : data) {
		if (d.theme == "zenei") {
			std::cout << "Zenei tábor kezdődik "
				<< d.first.month
				<< ". hó "
				<< d.first.day
				<< ". napján.\n";
			found = true;
		}
	}
	if (!found)
		std::cout << "Nem volt zenei tábor.\n";
}

void feladat4(const std::vector<Data>& data) {
	std::vector<size_t> counts;
	for (const Data& d : data) {
		counts.push_back(d.initials.size());
	}
	std::vector<size_t>::const_iterator max_it =
		std::max_element(counts.cbegin(), counts.cend());
	std::cout << "Legnépszerűbbek:\n";
	for (std::vector<size_t>::const_iterator it = max_it;
			it != counts.cend(); ++it) {
		if (*max_it == *it) {
			size_t index = std::distance(counts.cbegin(), it);
			const Data& d = data[index];
			std::cout << d.first.month
				<< ' '
				<< d.first.day
				<< ' '
				<< d.theme
				<< '\n';
		}
	}
}

int sorszam(int month, int day) {
	if (month == 6)
		return day - 16 + 1;
	if (month == 7)
		return 30 - 16 + day + 1;
	if (month == 8)
		return 30 + 31 - 16 + day + 1;
	return -1;
}

void feladat6(const std::vector<Data>& data) {
	std::cout << "6. feladat\n";
	std::cout << "hó: ";
	int month = 0;
	std::cin >> month;
	std::cout << "nap: ";
	int day = 0;
	std::cin >> day;
	int given_time = sorszam(month, day);
	size_t count = std::count_if(
		data.cbegin(),
		data.cend(),
		[given_time](const Data& d) {
			int first = sorszam(d.first.month, d.first.day);
			int last = sorszam(d.last.month, d.last.day);
			return first <= given_time && given_time <= last;
		}
	);
	std::cout << "Ekkor éppen "
		<< count
		<< " tábor tart.\n";
}

void feladat7(const std::string& filename, const std::vector<Data>& data) {
	std::ofstream os{filename};
	std::cout << "7. feladat\n";
	std::cout << "Adja meg egy tanuló betűjelét: ";
	char initial = 0;
	std::cin >> initial;
	std::vector<Data> select;
	for (const Data& d : data)
		if (d.initials.find(initial) != std::string::npos)
			select.push_back(d);
	std::sort(select.begin(),
		select.end(),
		[](const Data& a, const Data& b) {
			int a_time = sorszam(a.first.month, a.first.day);
			int b_time = sorszam(b.first.month, b.first.day);
			return a_time < b_time;
		}
	);
	bool first = true;
	bool can_go = true;
	Date prev_end;
	for (const Data& d : select) {
		if (first)
			first = false;
		else if (can_go) {
			int prev_end_time = sorszam(prev_end.month, prev_end.day);
			int curr_beg_time = sorszam(d.first.month, d.first.day);
			if (prev_end_time >= curr_beg_time)
				can_go = false;
		}
		os << d.first.month
			<< '.'
			<< d.first.day
			<< '-'
			<< d.last.month
			<< '.'
			<< d.last.day
			<< ". "
			<< d.theme
			<< '\n';
		prev_end = d.last;
	}
	if (!can_go)
		std::cout << "Nem mehet el mindegyik táborba.\n";
}

int main() {
	const std::string infilename = "../taborok.txt";
	const std::string outfilename = "../egytanulo.txt";

	// 1. feladat
	const std::vector<Data> data = read_file(infilename);

	feladat2(data);
	feladat3(data);
	feladat4(data);
	feladat6(data);
	feladat7(outfilename, data);
}
