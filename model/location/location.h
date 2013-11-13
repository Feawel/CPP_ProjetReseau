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
	Location(int userNumber);
	int getUserNumber() const;
	void setUserNumber(int userNumber);

private:
	int userNumber;
};

#endif /* LIEU_H_ */
