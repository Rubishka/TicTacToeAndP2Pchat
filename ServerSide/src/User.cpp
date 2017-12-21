

#include "User.h"

User::User() {
	socket = NULL;
	connectionStatus = false;
	connectedToUser = NULL;
	score=0;

}

User::~User() {
	// TODO Auto-generated destructor stub
}
