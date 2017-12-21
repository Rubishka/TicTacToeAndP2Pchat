

#ifndef USER_H_
#define USER_H_

#include "Common.h"


class User {

public:
	TCPSocket* socket;
	string name;
	bool connectionStatus;
	User* connectedToUser;
	int score;


public:
	User();
	virtual ~User();
};

#endif /* USER_H_ */
