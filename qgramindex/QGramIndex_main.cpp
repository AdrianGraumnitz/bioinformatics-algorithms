#include <iostream>
#include <fstream>
#include "QGramIndex.hpp"


int main(int argc, char* argv[]) {
	if (argc != 3) throw std::invalid_argument("You dont give the right number of arguments");
	std::string file{ argv[1] };
	std::string query{ argv[2] };
	uint8_t q{ static_cast<uint8_t>(query.size()) };
	
	std::string lin{};
	std::string text{};
	std::ifstream path(file);
	while (std::getline(path, lin)) {
		text += lin;
	}

	QGramIndex obj(text, q);
	std::vector <uint32_t> hits{};
	for (uint32_t i : obj.getHits(obj.hash(query)))  hits.push_back(i);
	std::cout << query << ": ";
	for (uint32_t i : hits) std::cout << i << " ";
}