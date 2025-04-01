#include <set>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Data {
	std::string lplate;
	int hour;
	int minute;
	int speed;
};

Data parse_line(std::string s) {
	std::istringstream is{s};
	Data d;
	is >> d.lplate >> d.hour >> d.minute >> d.speed;
	return d;
}

std::vector<Data> read_data(std::istream& is) {
	std::vector<Data> data;
	for (std::string line; std::getline(is, line); ) {
		data.push_back(parse_line(line));
	}
	return data;
}

std::vector<Data> read_data(const std::string& path) {
	std::ifstream is{path};
	return read_data(is);
}

const Data& feladat2(const std::vector<Data>& d) {
	return d[d.size() - 1];
}

std::vector<Data> find_lplate(const std::vector<Data>& d,
							  const std::string& lplate) {
	std::vector<Data> data;
	for (const Data& e : d) {
		if (e.lplate == lplate)
			data.push_back(e);
	}
	return data;
}

std::vector<Data> feladat4(const std::vector<Data>& d) {
	std::cout << "Kerem adja meg az orat: ";
	int h = 0;
	std::cin >> h;
	std::cout << "Kerem adja meg a percet: ";
	int m = 0;
	std::cin >> m;
	std::vector<Data> data;
	for (const Data& e : d) {
		if (e.hour == h && e.minute == m)
			data.push_back(e);
	}
	return data;
}

std::pair<int, std::vector<std::string>> feladat5(const std::vector<Data>& d) {
	auto max_speed_e = std::max_element(
			d.cbegin(),
		   	d.cend(),
		   	[](Data a, Data b) {
				return a.speed < b.speed;
			}
	);
	std::vector<std::string> vec;
	for (auto it = max_speed_e; it != d.cend(); ++it) {
		if (it->speed == max_speed_e->speed)
			vec.push_back(it->lplate);
	}
	return std::make_pair(max_speed_e->speed, vec);
}

std::vector<Data> feladat6(const std::vector<Data>& d) {
	std::cout << "Kerem, adja meg a rendszamot: ";
	std::string plate;
	std::cin >> plate;
	std::vector<Data> vec;
	for (const Data& e : d)
		if (e.lplate == plate)
			vec.push_back(e);
	return vec;
}

struct outData {
	std::string lplate;
	int beghour;
	int begmin;
	int endhour;
	int endmin;
};

std::vector<outData> feladat7(const std::vector<Data>& d) {
	std::vector<outData> vec;
	std::set<std::string> used_plates;
	for (const Data& data : d) {
		auto it = used_plates.find(data.lplate);
		if (it == used_plates.cend()) {
			auto last = std::find_if(d.crbegin(),
					d.crend(),
					[data](const Data& dat) { return data.lplate == dat.lplate; }
			);
			vec.push_back(
				outData {
					data.lplate,
					data.hour,
					data.minute,
					last->hour,
					last->minute
				}
			);
		}
		used_plates.insert(data.lplate);
	}
	return vec;
}

int main() {
	const std::string path{"../jeladas.txt"};
	std::vector<Data> data = read_data(path);

	const Data& d2 = feladat2(data);
	std::cout << "2. feladat:\n"
		<< "Az utolso jeladas idopontja "
		<< d2.hour << ":" << d2.minute
		<< ", a jarmu rendszama "
		<< d2.lplate << '\n';
	
	std::vector<Data> d3 = find_lplate(data, data[0].lplate);
	std::cout << "3. feladat:\n"
		<< "Az elso jarmu: "
		<< d3[0].lplate
		<< "\nJeladasainak idopontjai:";
	for (const Data& d : d3)
		std::cout << ' ' << d.hour << ':' << d.minute;
	std::cout << '\n';

	std::cout << "4. feladat:\n";
	std::vector<Data> d4 = feladat4(data);
	std::cout << "A jeladasok szama: " << d4.size() << '\n';

	std::cout << "5. feladat:\n";
	auto [d5s, d5p] = feladat5(data);
	std::cout << "A legnagyobb sebesseg km/h: " << d5s
		<< "\nA jarmuvek:";
	for (const std::string& p : d5p)
		std::cout << ' ' << p;
	std::cout << '\n';

	std::cout << "6. feladat:\n";
	std::vector<Data> d6 = feladat6(data);
	double d6r = 0.0;
	for (size_t i = 0; i < d6.size(); ++i) {
		const Data& d = d6[i];
		if (!i)
			std::cout << d.hour << ':' << d.minute << ' '
				<< std::fixed << std::setprecision(1) << d6r << " km\n";
		else {
			const Data& p = d6[i - 1];
			int curr_min = d.hour * 60 + d.minute;
			int prev_min = p.hour * 60 + p.minute;
			int min = curr_min - prev_min;
			d6r += min * p.speed / 60.0;
			std::cout << d.hour << ':' << d.minute << ' '
				<< std::fixed << std::setprecision(1) << d6r << " km\n";
		}
	}
	
	std::ofstream os{"ido.txt"};
	std::vector<outData> d7 = feladat7(data);
	for (const outData& d : d7)
		os << d.lplate << ' '
			<< d.beghour << ' '
			<< d.begmin << ' ' 
			<< d.endhour << ' '
			<< d.endmin << '\n';
}
