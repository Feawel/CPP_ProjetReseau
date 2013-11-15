/*
 * lieu.h
 *
 *  Created on: 4 nov. 2013
 *      Author: MOULIN
 */

#ifndef LIEU_H_
#define LIEU_H_

class Location {

public:
	Location();
	Location(unsigned int userNumber);
	unsigned int getUserNumber() const;
	void setUserNumber(unsigned int userNumber);

private:
	unsigned int userNumber;
};

#endif /* LIEU_H_ */
