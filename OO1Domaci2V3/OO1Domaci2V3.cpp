#include <iostream>
#include <vector>
#include "Skup.h"
#include "Rec.h"

int main()
{
	Rec word1 = "kamen", word2 = "motka";
	std::cout << std::boolalpha;
	std::cout << word1 << " ^ " << word2 << " = " << (word1 ^ word2) << std::endl;
	Rec word3 = "stena";
	Rec word4;
	std::cin >> word4;
	std::cout << word3 << " ^ " << word4 << " = " << (word3 ^ word4) << std::endl;
}
