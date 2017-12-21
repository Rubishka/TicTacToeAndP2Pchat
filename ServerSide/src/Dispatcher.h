

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Common.h"
#include "User.h"
#include "ServerTicTacToe.h"




	class Dispatcher : public MThread {

	public:

	pthread_mutex_t users_map_mutex;
	map<string,User*> users_map;//Holds connected users by name
	map<string,User*>::iterator users_iter;
	map<string,User*>::size_type users_map_size;
	//map<string,User> users_map2;

	vector<string> all_users_infile_vector; //Holds the users names in a "txt" file.


	map<string,string> in_session_with; // Map that holds pair of users that have a connection(session)
	map<string,string>::iterator in_session_with_iter;
	vector<TCPSocket*> users_vector;
	MultipleTCPSocketsListener* listener;
	bool status;
	ServerTicTacToe* gameManager;


public:
	Dispatcher(vector<string> names);

	void add_user(TCPSocket* peer,string name);
	void add_user_to_vector(string name);
	void open_session(User* user); //change TCPSocket* to User*
	void close_session(User* user);
	void list_users(User* user);//send connected users to client
	void user_exit(User* user);
	void list_all_users(User* user); //send all users to client
	void printUsers();//print all connected users
	void ptintSessions();
	void list_users_score(User* user);

	void start_game(User* user);
	void start_random_game(User* user);

	bool checkUser(string name);

	void close();

	void run();



	virtual ~Dispatcher();
};

#endif /* DISPATCHER_H_ */
