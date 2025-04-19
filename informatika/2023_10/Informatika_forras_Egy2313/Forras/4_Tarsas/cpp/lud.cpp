#include <sstream>
#include <map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> read_string(const std::string& fname) {
	std::ifstream is{fname};
	std::vector<std::string> sv;
	for (std::string s; std::getline(is, s); )
		sv.push_back(std::move(s));
	return sv;
}

std::vector<int> read_vector(const std::string& fname) {
	std::ifstream is{fname};
	std::vector<int> v;
	for (int i; is >> i; )
		v.push_back(i);
	return v;
}

void feladat2(const std::vector<std::string>& o, const std::vector<int>& d) {
	std::cout << "2. feladat\n"
		<< "A dobasok szama: "
		<< d.size()
		<< "\nAz osvenyek szama: "
		<< o.size()
		<< '\n';
}

void feladat3(const std::vector<std::string>& v) {
	std::cout << "3. feladat\n";
	auto it = std::max_element(
		v.cbegin(),
		v.cend(),
		[](const std::string& s1, const std::string& s2) {
			return s1.size() < s2.size();
		}
	);
	size_t n = std::distance(v.begin(), it);
	std::cout << "Az egyik leghosszabb a(z) "
		<< n + 1
		<< ". osveny, hossza: "
		<< (v.begin() + n)->size()
		<< '\n';
}

std::pair<int, int> feladat4() {
	std::cout << "4. feladat\n"
		"Adja meg egy osveny sorszamat! ";
	int osv_n = 0;
	std::cin >> osv_n;
	std::cout << "Adja meg a jatekosok szamat! ";
	int jat_n = 0;
	std::cin >> jat_n;
	return std::make_pair(osv_n, jat_n);
}

void feladat5(const std::vector<std::string>& o, int osv_n) {
	std::map<char, size_t> cnt;
	const std::string& osv = o[osv_n - 1];
	std::istringstream is{osv};
	for (char c{}; is >> c; ) {
		if (auto it = cnt.find(c); it != cnt.end()) {
			++cnt[c];
		} else {
			cnt[c] = 1;
		}
	}
	for (auto it = cnt.cbegin(); it != cnt.cend(); ++it) {
		std::cout << it->first
			<< ": "
			<< it->second
			<< " darab\n";
	}
}

void feladat6(const std::vector<std::string>& o, int n) {
	const std::string fname = "kulonleges.txt";
	const std::string& osv = o[n-1];
	std::ofstream os{fname};
	for (size_t i = 0; i < osv.size(); ++i)
		if (osv[i] != 'M') {
			os << i + 1 << ' ';
		}
}

int main() {
	const std::string osvenyek_f = "../osvenyek.txt";
	const std::string dobasok_f = "../dobasok.txt";

	std::vector<std::string> osvenyek = read_string(osvenyek_f);
	std::vector<int> dobasok = read_vector(dobasok_f);

	feladat2(osvenyek, dobasok);
	feladat3(osvenyek);
	auto [osv_n, jatekos_n] = feladat4();
	feladat5(osvenyek, osv_n);
	feladat6(osvenyek, osv_n);
}
