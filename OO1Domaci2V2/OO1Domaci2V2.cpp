#include <iostream>
#include "Knjiga.h"
#include "Biblioteka.h"

/*
* Sto puta sam pisao ovo std::string(40,'*') sto prakticno
* kreira string duzine 40 u kome su samo zvezdice.
* To sam koristio da razdvajam ispis da bude citkiji
* Postoje overloadi operatora << za ostream i za funkciju koja
* uzima i vraca ostream kao argument. Tako da sam to iskoristio
* kako bih olaksao ispis. Sada za razdvajanje mogu da koristim
* samo std::cout << seprarate, slicno kao za std::cout <<std::endl,
* jer je std::endl takodje funkcija
*/
std::ostream& separator(std::ostream& os) {
	return os << std::string(40, '*') << '\n';
}

int main()
{
	Knjiga k1("Put oko sveta za 80 dana", "Zil Vern");
	Knjiga k2("Hobit", "D. R. R. Tolkin");
	Knjiga k3("Orlovi rano lete", "Branko Copic");
	Knjiga k4("Na Drini cuprija", "Ivo Andric");
	Knjiga k5("Koreni", "Dobrica Cosic");
	Knjiga k6("Starac i more", "Ernest Hemingvej");

	std::cout << k1 << '\n';
	std::cout << k2 << '\n';
	std::cout << k3 << '\n';
	std::cout << k4 << '\n';
	std::cout << k5 << '\n';
	std::cout << k6 << '\n';

	std::cout << separator;


	Biblioteka b1("Narodna biblioteka Srbije", 5);
	b1 += k1;
	Biblioteka b2("Gradska biblioteka Beograd", 4);
	(b2 += k1) += k2;
	Biblioteka b3("Univerzitetska biblioteka", 10);
	b3 += k4;
	b3 += k5;
	b3 += k6;

	std::cout << b1 << separator;
	std::cout << b2 << separator;
	std::cout << b3 << separator;
	std::cout << "Prazna biblioteka: " << std::endl;
	std::cout << Biblioteka("temp", 100) << separator;

	std::cout << b1.getBookById(6) << '\n';
	if (b1.getBookById(10) == nullptr) {
		std::cout << "Knjiga sa ovim id-em ne postoji u ovoj biblioteci\n";
	}

	std::cout << *b2.getBookById(8) << '\n';
	if (b2.getBookById(2) == nullptr) {
		std::cout << "Knjiga sa ovim id-em ne postoji u ovoj biblioteci\n";
	}

	std::cout << *b3.getBookById(10) << '\n';
	if (b3.getBookById(15) == nullptr) {
		std::cout << "Knjiga sa ovim id-em ne postoji u ovoj biblioteci\n";
	}
	std::cout << separator;
	std::cout << "Test copy constructor:\n";
	Biblioteka b4 = b2;
	std::cout << b4 << separator;

	std::cout << "Test move constructor:\n";
	Biblioteka b5 = std::move(b3);
	std::cout << b3 << separator;
	std::cout << b5 << separator << separator;

	std::cout << "Test copy assignment:\n";
	b3 = b5;
	std::cout << b3 << separator;
	std::cout << b5 << separator << separator;

	std::cout << "Test move assignment:\n";
	b3 = std::move(b5);
	std::cout << b3 << separator;
	std::cout << b5 << separator << separator;

	std::cout << "Test overfilling\n";
	Biblioteka bx("Poslednja biblioteka", 2);
	bx += k1;
	bx += k2;
	bx += k3;
	std::cout << bx;
	bx += k4;
	std::cout << bx;
	std::cout << separator;
}