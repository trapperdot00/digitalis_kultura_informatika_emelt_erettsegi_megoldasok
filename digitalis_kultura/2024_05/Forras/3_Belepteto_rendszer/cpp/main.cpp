#include "Data.h"

#include <algorithm>
#include <set>

std::vector<Data>::const_iterator find_first_action
(const std::vector<Data>& vec, Data::Action a) {
	for (std::vector<Data>::const_iterator it = vec.cbegin();
		it != vec.cend(); ++it) {
		if (it->action == a)
			return it;
	}
	return vec.end();
}
std::vector<Data>::const_reverse_iterator find_last_action
(const std::vector<Data>& vec, Data::Action a) {
	for (std::vector<Data>::const_reverse_iterator it = vec.crbegin();
		it != vec.crend(); ++it) {
		if (it->action == a)
			return it;
	}
	return vec.crend();
}

size_t count_action_for_unique_people(std::vector<Data> vec, Data::Action a) {
	std::sort(vec.begin(), vec.end(), [](const Data& a, const Data& b)
		{return a.id < b.id; });
	size_t count = 0;
	std::string prev = "";
	for (size_t i = 0; i < vec.size(); ++i) {
		const Data& d = vec[i];
		if (d.action == a && prev != d.id) {
			++count;
			prev = d.id;
		}
	}
	return count;
}

void feladat2(const std::vector<Data>& vec) {
	std::cout << "2. feladat\n";
	auto it1 = find_first_action(vec, Data::Enter);
	if (it1 != vec.end()) {
		std::cout << "Az elsõ tanuló "
			<< it1->time << "-kor lépett be a fõkapun.\n";
	} else
		std::cout << "Nem történt belépés\n";
	auto it2 = find_last_action(vec, Data::Exit);
	if (it2 != vec.crend())
		std::cout << "Az utolsó tanuló " << it2->time << "-kor lépett ki a fõkapun.\n";
	else
		std::cout << "Nem történt kilépés\n";
}

void feladat3(const std::vector<Data>& vec, const std::string& filename) {
	std::ofstream os{ filename };
	if (!os)
		throw std::runtime_error{"cant open outputfile"};
	auto begin = std::find_if(vec.cbegin(), vec.cend(),
		[](const Data& d) { return Time{7, 50} < d.time; });
	auto end = std::find_if(begin, vec.cend(),
		[](const Data& d) { return Time{8, 15} < d.time; });

	for (auto it = begin; it != end; ++it) {
		if (it->action == Data::Enter)
			os << it->time << ' ' << it->id << '\n';
	}
}

size_t feladat4(const std::vector<Data>& vec) {
	std::cout << "4. feladat\n";
	size_t i = count_action_for_unique_people(vec, Data::Lunch);
	std::cout << "A menzán aznap " << i << " tanuló ebédelt.\n";
	return i;
}

size_t feladat5(const std::vector<Data>& vec, size_t j) {
	std::cout << "5. feladat\n";
	size_t i = count_action_for_unique_people(vec, Data::Library);
	std::cout << "Aznap " << i << " tanuló kölcsönzött a könyvtárban.\n";
	if (i < j)
		std::cout << "Nem voltak többen, mint a menzán.\n";
	else if (i == j)
		std::cout << "Ugyanannyian voltak mint a menzán.\n";
	else
		std::cout << "Többen voltak, mint a menzán.\n";
	return i;
}

bool is_first_enter(const std::vector<Data>& vec, std::vector<Data>::const_iterator it) {
	for (std::vector<Data>::const_iterator it1 = vec.cbegin();
		it1 != it; ++it1) {
		if (it1->action == Data::Enter)
			return false;
	}
	return true;
}
bool exited_on_break(const std::vector<Data>& vec, std::vector<Data>::const_iterator it) {
	for (const Data& d : vec) {
		if (Time{ 10, 45 } < d.time && d.time < Time{ 10, 50 } && d.action == Data::Exit)
			return true;
	}
	return false;
}

size_t count_actions(const std::vector<Data>& vec, const std::string& id, Data::Action a) {
	size_t count = 0;
	for (const Data& d : vec) {
		if (d.id == id && d.action == a) {
			++count;
		}
	}
	return count;
}

void feladat6(const std::vector<Data>& vec) {
	std::cout << "6. feladat\n"
		<< "Az érintett tanulók:\n";

	auto begin = std::find_if(vec.cbegin(), vec.cend(),
		[](const Data& d) { return Time{ 10, 50 } < d.time; });
	auto end = std::find_if(begin, vec.cend(),
		[](const Data& d) { return Time{ 10, 59 } < d.time; });

	for (auto it = begin; it != end; ++it) {
		size_t enter_count = count_actions(vec, it->id, Data::Enter);
		size_t exit_count = count_actions(vec, it->id, Data::Exit);
		if (exit_count != enter_count) {
			std::cout << it->id << ' ';
		}
	}
	std::cout << '\n';
}

std::vector<Data>::const_iterator
first_enter(const std::vector<Data>& vec, const std::string& id) {
	for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
		if (it->id == id && it->action == Data::Enter)
			return it;
	}
	return vec.cend();
}
std::vector<Data>::const_reverse_iterator
last_exit(const std::vector<Data>& vec, const std::string& id) {
	for (auto it = vec.crbegin(); it != vec.crend(); ++it) {
		if (it->id == id && it->action == Data::Exit)
			return it;
	}
	return vec.crend();
}

void feladat7(const std::vector<Data>& vec) {
	std::cout << "7. feladat\n";
	std::cout << "Egy tanuló azonosítója=";
	std::string id;
	if (std::cin >> id) {
		auto enter = first_enter(vec, id);
		if (enter != vec.cend()) {
			auto exit = last_exit(vec, id);
			int time = in_minutes(exit->time) - in_minutes(enter->time);
			int hours = time / 60;
			int minutes = time % 60;
			std::cout << "A tanuló érkezése és távozása között "
				<< hours << " óra "
				<< minutes << " perc telt el.\n";
		} else
			std::cout << "Ilyen azonosítójú tanuló aznap nem volt az iskolában.\n";
	}
}

// 1 es 10 legkevesebbet bent toltott diak
void feladat8(const std::vector<Data>& vec) {
	std::cout << "8. feladat\n";
	
}

int main() {
	//setlocale(LC_ALL, "");
	std::string filename{ "../bedat.txt" };
	std::vector<Data> contents = read_file(filename);
	feladat2(contents);
	feladat3(contents, "kesok.txt");
	feladat5(contents, feladat4(contents));
	feladat6(contents);
	feladat7(contents);
	feladat8(contents);
}
