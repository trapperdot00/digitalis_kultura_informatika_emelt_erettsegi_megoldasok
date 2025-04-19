#include <functional>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Point {
	double x;
	double y;
};

std::istream& operator>>(std::istream& is, Point& p) {
	return is >> p.x >> p.y;
}

struct Data {
	Point pos;
	double radius;
	std::string name;
};

std::istream& operator>>(std::istream& is, Data& d) {
	is >> d.pos >> d.radius;
	std::getline(is, d.name);
	d.name = d.name.substr(1);
	return is;
}

using container = std::vector<Data>;

container read_file(const std::string& fname) {
	std::vector<Data> v;
	std::ifstream is{fname};
	for (Data d; is >> d; ) {
		v.push_back(d);
	}
	return v;
}

void feladat2(const container& c) {
	std::cout << "2. feladat\nA kraterek szama: " << c.size() << '\n';
}

void feladat3(const container& c) {
	std::cout << "3. feladat\n";
	std::cout << "Kerem egy krater nevet: ";
	std::string name;
	if (std::getline(std::cin, name)) {
		auto it = std::find_if(
				c.cbegin(),
				c.cend(),
				[&name](const container::value_type& e) {
					return name == e.name;
				}
		);
		if (it != c.cend())
			std::cout << "A(z) "
				<< name
				<< " kozeppontja X="
				<< it->pos.x
				<< " Y="
				<< it->pos.y
				<< " sugara R="
				<< it->radius
				<< ".\n";
		else
			std::cout << "Nincs ilyen nevu krater.\n";
	}
}

void feladat4(const container& c) {
	std::cout << "4. feladat\n";
	auto it = std::max_element(
		c.cbegin(),
		c.cend(),
		[](const Data& d1, const Data& d2) {
			return d1.radius < d2.radius;
		}
	);
	if (it != c.cend())
		std::cout << "A legnagyobb krater neve es sugara: "
			<< it->name
			<< ' '
			<< it->radius
			<< '\n';
}

double tavolsag(Point p1, Point p2) {
	return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

void feladat6(const container& c) {
	std::cout << "6. feladat\n";
	std::cout << "Kerem egy krater nevet: ";
	std::string name;
	bool first = true;
	if (std::getline(std::cin, name)) {
		auto curr = std::find_if(
			c.cbegin(),
			c.cend(),
			[&name](const Data& d) {
				return d.name == name;
			}
		);
		if (curr != c.cend()) {
			for (const Data& d : c) {
				double tav = tavolsag(curr->pos, d.pos);
				if (tav > d.radius + curr->radius) {
					if (first) {
						std::cout << "Nincs kozos resze:";
						first = false;
					} else
						std::cout << ',';
					std::cout << ' ' << d.name;
				}
			}
		}
	}
	if (!first)
		std::cout << '.';
	std::cout << "\n";
}

void feladat7(const container& c) {
	std::cout << "7. feladat\n";
	for (const Data& d1 : c) {
		for (const Data& d2 : c) {
			double tav = tavolsag(d1.pos, d2.pos);
			if (d1.radius < d2.radius) {
				if (tav < (d2.radius - d1.radius))
					std::cout << "A(z) "
						<< d2.name
						<< " krater tartalmazza a(z) "
						<< d1.name
						<< " kratert.\n";
			} else if (tav < (d1.radius - d2.radius)) {
				std::cout << "A(z) "
					<< d1.name
					<< " krater tartalmazza a(z) "
					<< d2.name
					<< " kratert.\n";
			}
		}
	}
}

int main() {
	const std::string infile{"../felszin_tpont.txt"};
	container data = read_file(infile);

	std::vector<std::function<void(const container&)>> functions = {
		feladat2, feladat3, feladat4, feladat6, feladat7
	};
	for (const auto& f : functions)
		f(data);
}
