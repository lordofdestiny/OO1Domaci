#include <iostream>
#include <vector>
#include "Skup.h"
#include "Rec.h"

int main()
{
	Skup s("abcd");
	Rec word1 = "skrt";
	Rec word2 = "vrt";
	std::cout << std::boolalpha << (word1 ^ word2) << std::endl;
}
