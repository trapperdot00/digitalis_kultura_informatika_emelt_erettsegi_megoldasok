#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <array>

struct Order {
	int day = 0;
	std::string city;
	int quantity = 0;
};

using List = std::vector<Order>;

std::istream& operator>>(std::istream& is, Order& o) {
	int day = 0;
	std::string city;
	int quantity = 0;
	if (is >> day >> city >> quantity)
		o = Order{day, city, quantity};
	return is;
}

std::vector<Order> feladat1(const std::string& filename) {
	std::ifstream is{filename};
	List datalist;
	for (Order o; is >> o; )
		datalist.push_back(std::move(o));
	return datalist;
}

void feladat2(const List& datalist) {
	std::cout << "2. feladat:\n"
		<< "A rendelések száma: "
		<< datalist.size() << '\n';
}

List::const_iterator find_day(const List& datalist, int day) {
	for (List::const_iterator it = datalist.cbegin(); it != datalist.cend(); ++it) {
		if (it->day == day)
			return it;
	}
	return datalist.cend();
}

List::const_iterator find_different_day(List::const_iterator b, List::const_iterator e) {
	for (List::const_iterator it = b; it != e; ++it) {
		if (it->day != b->day)
			return it;
	}
	return e;
}

void feladat3(const List& datalist) {
	std::cout << "3. feladat:\n"
		<< "Kérem, adjon meg egy napot: ";
	int day = 0;
	std::cin >> day;
	auto begin = find_day(datalist, day);
	auto end = find_different_day(begin, datalist.cend());
	int order_count = std::distance(begin, end);
	std::cout << "A rendelések száma az adott napon: "
		<< order_count
		<< '\n';
}

void feladat4(const List& datalist) {
	std::cout << "4. feladat:\n";
	size_t count = 0;
	int prev = 0;
	for (const Order& o : datalist) {
		if (o.city == "NR") {
			if (prev < o.day)
				count += o.day - prev - 1;
			prev = o.day;
		}
	}
	if (prev != 30)
		count += 30 - prev;
	if (count)
		std::cout << count
			<< " nap nem volt a reklámban nem érintett városból rendelés\n";
	else
		std::cout << "Minden nap volt rendelés a reklámban nem érintett városból\n";
}

void feladat5(const List& datalist) {
	std::cout << "5. feladat:\n";
	auto it = std::max_element(
		datalist.cbegin(),
		datalist.cend(),
		[](const Order& a, const Order& b) {
			return a.quantity < b.quantity;
		}
	);
	std::cout << "A legnagyobb darabszám: "
		<< it->quantity
		<< ", a rendelés napja: "
		<< it->day
		<< '\n';
}

int osszes(const std::string& city, int day, const List& datalist) {
	int sum = 0;
	for (const Order& o : datalist)
		if (o.city == city && o.day == day)
			++sum;
	return sum;
}

void feladat7(const List& datalist) {
	std::cout << "7. feladat:\n"
		<< "A rendelt termékek darabszáma a 21. napon PL: "
		<< osszes("PL", 21, datalist)
		<< " TV: "
		<< osszes("TV", 21, datalist)
		<< " NR: "
		<< osszes("NR", 21, datalist)
		<< '\n';
}

void feladat8(const List& datalist, const std::string& filename) {
	std::cout << "8. feladat:\n";
	std::ofstream os{filename};
	std::cout << "Napok\t1..10\t11..20\t21..30\n";
	os << "Napok\t1..10\t11..20\t21..30\n";
	const std::array<std::string, 3> cities = {
		"PL", "TV", "NR"
	};
	for (size_t i = 0; i < cities.size(); ++i) {
		std::cout << cities[i];
		os << cities[i];
		for (int j = 0; j < 3; ++j) {
			int sum = 0;
			for (int k = 0; k < 10; ++k)
				sum += osszes(cities[i], j * 10 + k + 1, datalist);
			std::cout << '\t' << sum;
			os << '\t' << sum;
		}
		std::cout << '\n';
		os << '\n';
	}
}

int main() {
	const std::string infilename = "../rendel.txt";
	const std::string outfilename = "kampany.txt";
	const List datalist = feladat1(infilename);

	feladat2(datalist);
	feladat3(datalist);
	feladat4(datalist);
	feladat5(datalist);
	feladat7(datalist);
	feladat8(datalist, outfilename);
}
