#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <cstddef>
#include <map>
#include <algorithm>
#include <numeric>

struct Data {
	size_t num1;
	size_t num2;
	char color;
};

std::istream& operator>>(std::istream& is, Data& d) {
	return is >> d.num1 >> d.num2 >> d.color;
}

std::ostream& operator<<(std::ostream& os, const Data& d) {
	return os << d.num1 << ' ' << d.num2 << ' ' << d.color;
}

using Container = std::vector<Data>;

std::pair<size_t, Container> read_file(const std::string& filename) {
	std::ifstream is{filename};
	size_t count = 0;
	is >> count;
	Container vec;
	for (Data d; is >> d; )
		vec.push_back(std::move(d));
	return std::make_pair(count, vec);
}

void insert_or_increment(std::map<size_t, size_t>& m, size_t i) {
	if (const auto it = m.find(i); it != m.cend())
		++it->second;
	else
		m.insert(std::make_pair(i, 1));
}

std::map<size_t, size_t> count_offers(size_t count, const Container& vec) {
	std::map<size_t, size_t> offers;
	for (size_t i = 0; i < vec.size(); ++i) {
		const Data& d = vec[i];
		if (d.num1 <= d.num2) {
			for (size_t box = d.num1; box <= d.num2; ++box) {
				insert_or_increment(offers, box);
			}
		}
		else {
			for (size_t box = d.num1; box <= count; ++box) {
				insert_or_increment(offers, box);
			}
			for (size_t box = 1; box <= d.num2; ++box) {
				insert_or_increment(offers, box);
			}
		}
	}
	return offers;
}

std::string get_colors(size_t count, const Container& vec, size_t box) {
	std::string colors;
	for (size_t i = 0; i < vec.size(); ++i) {
		const Data& d = vec[i];
		if (d.num1 <= d.num2) {
			if (d.num1 <= box && box <= d.num2)
				colors += d.color;
		} else {
			if ((d.num1 <= box && box <= count) || (1 <= box && box <= d.num2))
				colors += d.color;
		}
	}
	return colors;
}

void feladat2(const Container& vec) {
	std::cout << "2. feladat\n"
		<< "A felajánlások száma: "
		<< vec.size()
		<< "\n\n";
}

void feladat3(const Container& vec) {
	std::cout << "3. feladat\n"
		<< "A bejárat mindkét oldalán ültetők:";
	for (size_t i = 0; i < vec.size(); ++i) {
		const Data& d = vec[i];
		if (d.num1 > d.num2)
			std::cout << ' ' << i+1;
	}
	std::cout << "\n\n";
}

void feladat4(size_t count, const Container& vec, const std::map<size_t, size_t>& offers) {
	std::cout << "4. feladat\n"
		<< "Adja meg az ágyás sorszámát! ";
	size_t num = 0;
	std::cin >> num;
	const auto offers_for_num = offers.find(num);
	if (offers_for_num == offers.cend()) {
		std::cout << "A felajánlók száma: 0\n"
			<< "Ezt az ágyást nem ültetik be.\n";
	} else {
		std::cout << "A felajánlók száma: "
			<< offers_for_num->second
			<< '\n';
		std::string colors_for_num = get_colors(count, vec, num);
		std::cout << "A virágágyás színe, ha csak az első ültet: "
			<< colors_for_num[0]
			<< '\n';

		std::sort(colors_for_num.begin(), colors_for_num.end());
		auto end_unique = std::unique(colors_for_num.begin(), colors_for_num.end());
		colors_for_num.erase(end_unique, colors_for_num.end());

		std::cout << "A virágágyás színei:";
		for (char c : colors_for_num)
			std::cout << ' ' << c;
		std::cout << '\n';
	}
	std::cout << '\n';
}

void feladat5(size_t count, const std::map<size_t, size_t>& offers) {
	std::cout << "5. feladat\n";
	if (offers.size() == count)
		std::cout << "Minden ágyás beültetésére van jelentkező.\n";
	else {
		size_t offer_count = std::accumulate(
			offers.begin(),
			offers.end(),
			size_t{},
			[](size_t value, const std::map<size_t, size_t>::value_type& p)
			{ return value += p.second; }
		);
		if (offer_count >= count)
			std::cout << "Átszervezéssel megoldható a beültetés.\n";
		else
			std::cout << "A beültetés nem oldható meg.\n";
	}
}

void feladat6(const std::string& filename, size_t count, const Container& vec) {
	std::ofstream os{filename};
	std::map<size_t, std::pair<size_t , char>> plant_color;
	for (size_t i = 0; i < vec.size(); ++i) {
		const Data& d = vec[i];
		if (d.num1 <= d.num2) {
			for (size_t num = d.num1; num <= d.num2; ++num)
				plant_color.insert(std::make_pair(num, std::make_pair(i, d.color)));
		} else {
			for (size_t num = d.num1; num <= count; ++num)
				plant_color.insert(std::make_pair(num, std::make_pair(i, d.color)));
			for (size_t num = 1; num <= d.num2; ++num)
				plant_color.insert(std::make_pair(num, std::make_pair(i, d.color)));
		}
	}
	for (size_t i = 1; i <= count; ++i) {
		if (const auto it = plant_color.find(i); it != plant_color.cend())
			os << it->second.second << ' ' << it->second.first + 1 << '\n';
		else
			os << "# 0\n";
	}
}

int main() {
	const std::string infilename{"../felajanlas.txt"};
	const std::string outfilename{"../szinek.txt"};
	const auto [count, data] = read_file(infilename);
	const std::map<size_t, size_t> offers = count_offers(count, data);

	feladat2(data);
	feladat3(data);
	feladat4(count, data, offers);
	feladat5(count, offers);
	feladat6(outfilename, count, data);
}
