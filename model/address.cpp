/*
 * address.cpp
 *
 *  Created on: 15 nov. 2013
 *      Author: MOULIN
 */

#include "address.h"

using namespace std;

Address::Address() :
		part1(0), part2(0), part3(0), part4(0), prefixSize(0) {

}

Address::Address(unsigned int part1, unsigned int part2, unsigned int part3,
		unsigned int part4, unsigned int prefixSize) :
		part1(part1), part2(part2), part3(part3), part4(part4), prefixSize(
				prefixSize) {

}

void Address::display(ostream &flux) const {
	flux << part1 << "." << part2 << "." << part3 << "." << part4 << "/"
			<< prefixSize;
}

ostream &operator<<(ostream &flux, Address const& address) {
	address.display(flux);
	return flux;
}
