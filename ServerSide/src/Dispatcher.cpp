

#include "Dispatcher.h"
//#include "Protocol.h"

pthread_mutex_t login_dispatcher_mutex = PTHREAD_MUTEX_INITIALIZER;

Dispatcher::Dispatcher(vector<string> names)
{
	listener = NULL;
	users_map_mutex = PTHREAD_MUTEX_INITIALIZER;
	users_map_size = 0;
	status = false;
	all_users_infile_vector = names;
}
void Dispatcher::add_user_to_vector(string name)
{
	all_users_infile_vector.push_back(name);
}
void Dispatcher::add_user(TCPSocket* peer,string name)
{
	if (pthread_mutex_lock(&login_dispatcher_mutex)!=0)
	{
		printf("Error locking mutex");
		exit(1);
	}
	User* user = new User;

	user->socket = peer;
	user->name = name;
	user->connectionStatus = false;
	user->connectedToUser = NULL;


	cout << user->name << " is now connected" << endl;

	users_map[name] = user;
	users_vector.push_back(peer);

	if (status == false)
	{
		status = true;
		this->start();
	}
	if (pthread_mutex_unlock(&login_dispatcher_mutex)!=0)
	{
		printf("Error unlocking mutex");
		exit(1);
	}
}

void Dispatcher::run()
{
	int command;

	while (status == true)
	{
		User* current_user = new User();
		listener = new MultipleTCPSocketsListener();
		listener->addSockets(users_vector);
		TCPSocket* temp_sock = listener->listenToSocket(2);
		delete(listener);

		if (temp_sock != NULL)
		{
			command = readCommand(temp_sock);
			current_user->socket = temp_sock; //Initialize the socket field
		}
		else
			continue;

		if (command == 0)
		{
			cout<<"problem"<<endl;
			continue;
		}
		else if (command == OPEN_SESSION_WITH_USER) //get the user`s IP & port
		{
			open_session(current_user);
		}
		else if (command == CLOSE_SESSION_WITH_USER)
		{
			close_session(current_user);
		}
		else if (command == START_GAME_WITH_USER) //get the user`s IP & port
		{
			start_game(current_user);
		}
		else if (command == EXIT) //user is exiting
		{
			user_exit(current_user);
		}
		else if (command == GET_ALL_USERS) //all names from file
		{
			list_all_users(current_user);
		}

		else if (command == GET_ALL_CONNECTED_USERS) //send back to the user a list of all connected users
		{
			list_users(current_user);
		}
		else if (command == GET_ALL_USERS_SCORE) //send to the user a list of all connected users score
		{
			list_users_score(current_user);
		}

		else if (command == START_GAME_WITH_RANDOM_USER) //send to the user a list of all connected users score
		{
			start_random_game(current_user);
		}

	}
}


void Dispatcher::open_session(User* user)
{
	string userName,peerUsr,user_ip_and_port,target_ip_and_port;
	User* target;
	string with;
	User* _user;


	userName = readMsg(user->socket); // our name
	peerUsr = readMsg(user->socket);//The user name of the target user

	for (users_iter = users_map.begin() ; users_iter != users_map.end() ; users_iter++)
	{
		_user = users_iter->second;
		if (_user->socket == user->socket)
		{//if there is a match between the connected user to one of the users in the map->
		//initialize _user and break
			break;
		}
	}
	target = users_map[peerUsr];
	if (target->name!= peerUsr)
	{
		writeCommand(user->socket,OPEN_SESSION_ERROR);
		return ;
	}
	if ((_user->connectionStatus == false)&&(target->connectionStatus==false))
	{
		if ((users_map.find(peerUsr)!=users_map.end())&& (userName.compare(peerUsr)!=0)) //target user was found
		{

			target_ip_and_port = target->socket->destIpAndPort();

			writeCommand(user->socket,TARGET_IP_AND_PORT);
			writeMsg(user->socket,target->name);
			writeMsg(user->socket,target_ip_and_port);
			user_ip_and_port = user->socket->destIpAndPort();

			writeCommand(target->socket,INCOMIMG_SESSION);
			writeMsg(target->socket,_user->name);
			writeMsg(target->socket,user_ip_and_port);
			target->connectionStatus = true;
			target->connectedToUser = _user;
			_user->connectionStatus = true;

			in_session_with[_user->name] = target->name; //for connection monitoring
		}
		else
		{
			writeCommand(user->socket,OPEN_SESSION_ERROR);
		}
	}
	else
	{
		writeCommand(user->socket,OPEN_CONNECTION_ERROR);
	}

}

void Dispatcher::list_all_users(User* user)
{
	writeCommand(user->socket,ALL_USERS_LIST);
	writeCommand(user->socket,all_users_infile_vector.size());

	for (unsigned int i=0 ; i < all_users_infile_vector.size() ; i++)
	{
		writeMsg(user->socket,all_users_infile_vector[i]);
	}
}


void Dispatcher::close_session(User* user )
{
	string partner;
	User* _user;
	bool first = false;
	bool second = false;


	for (users_iter = users_map.begin() ; users_iter != users_map.end() ; users_iter++)
	{
		_user = users_iter->second;
		if (_user->socket == user->socket)
		{//if there is a match between the connected user to one of the users in the map->
		//initialize _user and break
			break;
		}
	}

	//check if user is in session

	for (in_session_with_iter = in_session_with.begin() ; in_session_with_iter != in_session_with.end() ; in_session_with_iter++)
	{
		if (in_session_with_iter->first == _user->name) //user has an open session that he started
		{
			partner = in_session_with_iter->second;
			first = true;
		}
		else if (in_session_with_iter->second == _user->name) //user has an open session that he DIDNT started
		{
			partner = in_session_with_iter->first;
			second = true;
		}
	}

	if (first == true || second == true)
	{
		writeCommand((users_map[partner])->socket,SESSION_ENDED);
		users_map[partner]->connectionStatus = false;
		users_map[partner]->connectedToUser = NULL;
		users_map[_user->name]->connectionStatus = false;
		users_map[_user->name]->connectedToUser = NULL;
		if (first == true)
		{
			in_session_with.erase(_user->name);
		}
		else if (second == true)
		{
			in_session_with.erase(partner);
		}
	}
	else
	{
		writeCommand(_user->socket,CLOSE_SESSION_ERROR);
	}

}

void Dispatcher::start_random_game(User* user){


	string userName,peerUsr,rivalUsr;
		User* target;
		User* curent;
		string with;
		bool found=false;
		int winner;

		userName = readMsg(user->socket); // our name
		curent= users_map[userName];

		for (users_iter = users_map.begin() ; users_iter != users_map.end() ; users_iter++)
			{
			if (! users_iter->first.compare(userName)){
				target=users_iter->second;
				found=true;
				break;
			}

			}
		if (found){
			writeCommand(curent->socket,START_NEW_GAME);
			writeMsg(curent->socket,target->name);
			writeMsg(curent->socket,"X");

			writeCommand(target->socket,START_NEW_GAME);
			writeMsg(target->socket,curent->name);
			writeMsg(target->socket,"O");


			gameManager= new ServerTicTacToe(curent->socket, target->socket);
			winner = gameManager->startGame();
			if (winner==1){
				users_map[userName]->score++;
			}else if(winner==2){
				users_map[rivalUsr]->score++;
			}

			}else{
				cout<<"no user connected"<<endl;
			}

		}


void Dispatcher::start_game(User* user){


	string userName,peerUsr,rivalUsr;
		User* target;
		string with;
		int winner;

		userName = readMsg(user->socket); // our name
		rivalUsr = readMsg(user->socket);//The user name of the target user
		cout << "Start new game between " << userName << " and " <<  rivalUsr<<endl;


		target = users_map[rivalUsr];
		if (target->name!= rivalUsr)
		{
			writeCommand(user->socket,OPEN_SESSION_ERROR);
			return ;
		}

				if ((users_map.find(rivalUsr)!=users_map.end())&& (userName.compare(rivalUsr)!=0)) //target user was found
				{


					writeCommand(user->socket,START_NEW_GAME);
					writeMsg(user->socket,rivalUsr);
					writeMsg(user->socket,"X");

					writeCommand(target->socket,START_NEW_GAME);
					writeMsg(target->socket,user->name);
					writeMsg(target->socket,"O");


					gameManager= new ServerTicTacToe(user->socket, target->socket);
					winner = gameManager->startGame();
					if (winner==1){
						users_map[userName]->score++;
					}else if(winner==2){
						users_map[rivalUsr]->score++;
					}

				}
				else
				{
					writeCommand(user->socket,OPEN_SESSION_ERROR);//TODO
				}



}

void Dispatcher::user_exit(User* user)
{
	string name;
	User* _user;

	for (users_iter = users_map.begin() ; users_iter != users_map.end() ; users_iter++)
	{
		_user = users_iter->second;
		if (_user->socket == user->socket)
		{
			break;
		}
	}

	if (_user->connectionStatus == true)
	{
			close_session(_user);

	}

	writeCommand(_user->socket,BYE_BYE_MSG);


	//remove user from map
	cout << _user->name << " has disconnected" << endl;
	users_map.erase(_user->name);


}

void Dispatcher::list_users(User* user)
{
	string user_name;
	writeCommand(user->socket,USERS_LIST);
	writeCommand(user->socket,users_map.size());
	for (users_iter = users_map.begin() ; users_iter != users_map.end() ; users_iter++)
	{
		user_name = users_iter->first;
		writeMsg(user->socket,user_name);
	}
}

void Dispatcher::list_users_score(User* user)
{
	string user_name;
	int user_score;
	char chr_score;
	string str_score;
	writeCommand(user->socket,ALL_USERS_LIST_SCORE);
	writeCommand(user->socket,users_map.size());

	for (users_iter = users_map.begin() ; users_iter != users_map.end() ; users_iter++)
	{
		user_name = users_iter->first;
		writeMsg(user->socket,user_name);
		cout   << user_name <<"	"<< "score: "<< users_iter->second->score<< endl;

		str_score=users_iter->second->score+" ";
		writeCommand(user->socket,users_iter->second->score);

	}
}


void Dispatcher::printUsers()
{
	if (pthread_mutex_lock(&users_map_mutex)!=0)
	{
		printf("Error locking mutex");
		exit(1);
	}

	if (users_map.empty() == true)
	{
		cout <<"There are no connected users" << endl;
	}
	else
	{
		for (users_iter = users_map.begin() ; users_iter != users_map.end() ; users_iter++)
		{
			cout << "Connected user: " << users_iter->first << endl;
		}
	}
	if (pthread_mutex_unlock(&users_map_mutex)!=0)
	{
		printf("Error unlocking mutex");
		exit(1);
	}

	/*
	if (users_map.size() > 0)
	{
		cout << "Users:" <<  endl;
		for (users_iter = users_map.begin() ; users_iter != users_map.end() ; users_iter++)
		{
			cout << users_iter->first << endl;
		}
	}
	else
	{
		cout << "There are no logged in users" << endl;
	}
	 */
}
void Dispatcher::ptintSessions()
{
	if (in_session_with.size() != 0)
	{
		cout << "Sessions:" << endl;
		for (in_session_with_iter = in_session_with.begin() ; in_session_with_iter != in_session_with.end() ; in_session_with_iter++)
		{
			cout << in_session_with_iter->first;
			cout << " is in session with ";
			cout << in_session_with_iter->second << endl;
		}
	}
	else
	{
		cout << "There are no active sessions at the moment" << endl;
	}
}

bool Dispatcher::checkUser(string name)
{
	return users_map.find(name) != users_map.end();//if there are no such name return the iterator::end
}

void Dispatcher::close()
{
	User* _user;
	status = false;
	for (users_iter = users_map.begin() ; users_iter != users_map.end() ; users_iter++)
	{
		_user = users_iter->second;
		cout << users_iter->first << endl;
	}
	if (listener!=NULL)
	{
		delete(listener);
	}


}

Dispatcher::~Dispatcher() {

}

