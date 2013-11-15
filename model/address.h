/*
 * address.h
 *
 *  Created on: 15 nov. 2013
 *      Author: MOULIN
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <iostream>

class Address {

public:
	Address();
	Address(unsigned int part1, unsigned int part2, unsigned int part3,
			unsigned int part4, unsigned int prefixSize);
	void display(std::ostream &flux) const;

private:
	unsigned int prefixSize;
	unsigned int part1;
	unsigned int part2;
	unsigned int part3;
	unsigned int part4;
};
std::ostream &operator<<(std::ostream &flux, Address const& address);
#endif /* ADDRESS_H_ */
