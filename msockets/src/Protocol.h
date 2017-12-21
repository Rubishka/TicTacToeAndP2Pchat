
#ifndef TCPMESSENGERPROTOCOL_H_
#define TCPMESSENGERPROTOCOL_H_



using namespace std;

#define SERVER_PORT 3346

#define CLOSE_SESSION_WITH_USER 	1
#define OPEN_SESSION_WITH_USER 		2
#define EXIT						3
#define SEND_MSG_TO_PEER			4
#define SESSION_REFUSED				5
#define SESSION_ESTABLISHED			6
#define LOGIN						7
#define SIGNUP 						8
#define START_GAME_WITH_USER		9
#define START_NEW_GAME				10
#define PLAY						11
#define YOU_WON						12
#define YOU_LOST					13
#define EVEN						14

#define GET_ALL_USERS				15
#define ENTER_USERNAME				16
#define ENTER_PASSWORD				17
#define CONFIRM_USER 				18 //login was accomplished
#define LOGIN_DENIED 				19
#define USERNAME_TAKEN 				20
#define BAD_COMMAND 				21
#define ENTER_USER_NAME 			22	 //"Enter user name: "
#define INCOMIMG_SESSION 			23 	//"Incoming session from: "
#define OPEN_SESSION_ERROR 			24 	//"Username not found "
#define CLOSE_SESSION_ERROR 		25 	//"You are not in session "
#define OPEN_CONNECTION_ERROR 		26 	//"You have an open connection"
#define CONTINUE_GAME				27

#define GET_ALL_USERS_SCORE			28
#define ALL_USERS_LIST_SCORE 		29

#define SESSION_ENDED 				30
#define START_GAME_WITH_RANDOM_USER 31
#define OPEN_SESSION_ERROR2			33 //"You have an open session"
#define CONNECTION_ERROR 			34 //"You don't have any open connections"
#define BYE_BYE_MSG 				36
#define TARGET_IP_AND_PORT 			41
#define LOGIN_OR_SIGNUP 			42 //now the client can sign up or login
#define USERS_LIST 					43
#define ALL_USERS_LIST 				49
#define GET_ALL_CONNECTED_USERS		50
#define CLOSE_CONNECTION			51

#define TEST_PEER_NAME "test"
#define SESSION_REFUSED_MSG "Connection to peer refused, peer might be busy or disconnected, try again later"


#endif /* TCPMESSENGERPROTOCOL_H_ */
