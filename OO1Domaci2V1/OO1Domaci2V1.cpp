#include <iostream>
#include "Cvet.h"
#include "Buket.h"
#include "Cvecara.h"

int main()
{
	Cvet gerber("Gerber", 70, 120);
	Cvet ruza("Ruza", 90, 180);
	Cvet karanfil("Karanfil", 50, 120);
	Cvet cvetic("Cvetic", 10, 11);
	Cvet test("Ruza", 230, 500);

	std::cout << (ruza == test ? "Ruza je ista kao test cvet\n" : "Ova dva cveta nisu ista!\n");
	std::cout << std::string(30, '-') << '\n';	

	Buket bouquet1;
	bouquet1.addFlower(gerber);
	bouquet1.addFlower(karanfil);
	bouquet1.addFlower(karanfil);

	Buket bouquet2 = bouquet1;
	bouquet2.addFlower(ruza);
	bouquet2.addFlower(ruza);

	Buket bouquet3;
	bouquet3.addFlower(ruza);
	bouquet3.addFlower(ruza);
	bouquet3.addFlower(ruza);

	Buket bouquet4;
	bouquet4.addFlower(cvetic);
	bouquet4.addFlower(cvetic);
	bouquet4.addFlower(cvetic);

	std::cout << (bouquet1 > bouquet2 ? "Prvi" : "Drugi") << " buket je skuplji!\n";
	std::cout << std::string(30, '-') << '\n';

	std::cout << "Buketi:\n";
	std::cout << bouquet1 << '\n';
	std::cout << bouquet2 << '\n';
	std::cout << bouquet3 << '\n';
	std::cout << bouquet4 << '\n';
	std::cout << std::string(30, '-') << '\n';

	Cvecara cvecara;
	cvecara.addBouquet(bouquet1);
	cvecara.addBouquet(bouquet2);
	cvecara.addBouquet(bouquet3);
	if (!cvecara.addBouquet(bouquet4)) {
		std::cout << "Buket nije dodat jer ne ispunjava uslov!\n";
		std::cout << "Procenat: " << bouquet4.getPercentEarnings() << "%\n";
	}
	if (cvecara.sellBouquet(1)) {
		std::cout << "Uspesno prodat buket sa indeksom!\n";
	}
	if (!cvecara.sellBouquet(10)) {
		std::cout << "Neuspelo prodat buket, los indeks!\n";
	}
	/*Proveri sto su svi buketi 0 dinara*/
	std::cout << "Cvecara:\n";
	std::cout << cvecara << std::endl;
}