#include "Alignment.hpp"

int main(int argc, char* argv[]) {
	if (argc != 3 && argc != 6 && argc != 7) {
		std::cerr << "wrong input";
		exit(1);
	}
	std::string a1{};
	std::string a2{};
	std::string gaps{};
	Alignment obj(argv[1], argv[2]);
	if (argc == 3) {
		
		obj.compute(3, -1, -2, false);
	}
	else if (argc == 6)  {
		obj.compute(std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]));
		
	}
	else {
		bool value{};
		if (std::string(argv[6]) == "true") value = true;
		else value = false;
		obj.compute(std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]), value);
	}
	
	
	obj.getAlignment(a1, gaps, a2);
	std::cout <<"\n"<< a1 << "\n" << gaps << "\n" << a2 << "\n";
	std::cout << "score:" << obj.getScore();
}