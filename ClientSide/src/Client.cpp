

#include "Client.h"

#include "Protocol.h"



const string MSG_FROM_SERVER =  "Got msg from server: ";
const string EXIT_SESSION = "to exit current session enter cs\n";

void print_instructions();

int main() {

	string command,username,password;
	string ip,peerUsr,msg,gameUsr;
	Client client;

	cout << "Welcome to Tic-Tac-Toe and messenger\nPlease enter a command by the following:" << endl;


	print_instructions();

	//waiting for commands from cli
	do
	{
	if (client.isInGame==false){
			command.clear();
			cin >> command;

		if (command == "c") //connect to server
		{
			cin >> ip;
			if (client.connectToServer(ip,SERVER_PORT) == false)
			{
				cout << "Could not connect to sever" <<  endl;
			}
			else
			{
				client.isConnectedToServer = true;
			}
			continue;
		}
		else if (command == "login") //login to server
		{
			cin >> username;
			cin >> password;
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<  endl;
				continue;
			}
			else if(client.isLoggedIn==false)
			{
				client.login(username,password);
				sleep(5);
			}
			else
				cout<<"You are already logged in"<<endl;
		}
		else if (command == "register") //signup to server
		{
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<endl;
				continue;
			}
			cin >> username;
			cin >> password;
			client.signup(username,password);
		}
		else if (command == "lu") //list all users from server
		{
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<  endl;
				continue;
			}
			client.getUsers();
		}
		else if (command == "lus") //list all users score server
		{
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<  endl;
				continue;
			}
			client.getUserScore();
		}
		else if (command == "lcu") //list all connected users
		{
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<  endl;
				continue;
			}
			client.listAllUsers();
		}

		else if (command == "o") //open a session with a user
		{
			cin>>peerUsr;
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<  endl;
				continue;
			}
			else if(client.isInSession==true )
			{
				cout << "ERROR - already in session with other user" <<EXIT_SESSION<<  endl;
				continue;
			}
			else
			{
				client.openSession(username,peerUsr);
			}
		}
		else if (command == "g") //start game with other users
		{

			cin>>gameUsr;
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<  endl;
				continue;
			}
			else if(client.isInSession==false )
			{
				cout << "ERROR - please open a session with other user first" <<EXIT_SESSION<<  endl;
				continue;
			}
			else
			{
				client.startGame(username,gameUsr);
			}

		}
		else if (command == "go") //start game with other users
		{

			cin>>gameUsr;
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<  endl;
				continue;
			}
			else if(client.isInSession==false )
			{
				cout << "ERROR - please open a session with other user first" <<EXIT_SESSION<<  endl;
				continue;
			}
			else
			{
				client.startGame(username);
			}

		}

		else if (command == "cs") //close the current session
		{
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<  endl;
				continue;
			}
			client.closeSession();

		}

		else if (command == "s") //send a msg to user in session
		{
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<  endl;
				continue;
			}

			else if(client.isInSession == true){
				getline(std::cin,msg);
				if(msg.size()>0 && msg[0]==' ')
					msg.erase(0,1);
				client.sendMsgToSession(msg);
			}
			else
				cout<<"error"<<endl;
		}
		else if (command == "l") //print your connection status
		{
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<  endl;
				continue;
			}
			else{
				if (client.sessionStatus())
					cout << "You are connected to " <<client.getName()<< endl;
				else
					cout << "Your are connected only to the server" <<  endl;
			}

		}
		else if (command == "d") //disconnect from server
		{
			if (client.isConnectedToServer == false)
			{
				cout << "ERROR - You are not connected to a server" <<  endl;
				continue;
			}
			cout<<"Disconnecting Server..."<<endl;
			client.disconnectFromServer();
		}

		else if (command == "x")//close app
		{
			client.close();
		}
		else if (command == "p")
		{
			print_instructions();
		}

		else
		{
			cout << "Bad command!" << endl;
		}



	}else{sleep(3);}
	}
	while(command != "x");

	return 0;
}



void print_instructions()
{
	cout << endl;
	cout << "c <ip> - connect to server" << endl;
	cout << "login <username> <password> - Login to server" << endl;
	cout << "register <username> <password> - Signup to server" <<  endl;
	cout << "lu - Print all users from server" << endl;
	cout << "lcu - Print all connected users from server" << endl;
	cout << "lus - print all users score" << endl;

	cout << "o <username> - Open a session with a user" << endl;
	cout << "g <username> - Start a new game with a user" << endl;
	cout<<  "go  - start game with random user"<<endl;
	cout << "cs - close the current session" << endl;
	cout << "s <message> - send a message to session user" << endl;
	cout << "l - print connection status" << endl;
	cout << "d - disconnect from server" << endl;
	cout << "p - print instructions" << endl;
	cout << "x - close app" << endl;
	cout << endl;
}


Client::Client()
{

	server_sock = NULL;
	udp_sock = NULL;
	game=NULL;
	connectionStatus = false;
	isLoggedIn = false;
	isInSession = false;
	isConnectedToServer = false;
}

void Client::getUserScore(){
	writeCommand(server_sock,GET_ALL_USERS_SCORE);
}

//get all users names from file
void Client::getUsers()
{
	writeCommand(server_sock,GET_ALL_USERS);
}
bool Client::connectToServer(string ip,int port)
{
	server_sock = new TCPSocket(ip,port);
	if (server_sock->getSocketFid() < 0)//socket construction failed
	{
		return false;
	}
	else
	{
		connectionStatus = true;
		this->start();
	}
	return true;
}
void Client::login(string name,string pass)
{
	writeCommand(server_sock,LOGIN);
	writeMsg(server_sock,name);
	writeMsg(server_sock,pass);

}
void Client::signup(string name,string pass)
{
	writeCommand(server_sock,SIGNUP);
	writeMsg(server_sock,name);
	writeMsg(server_sock,pass);
}


void Client::sendMsgToServer(string msg)
{
	writeMsg(server_sock,msg);
}
void Client::disconnectFromServer()
{
	connectionStatus = false;
	isInSession = false;
	isConnectedToServer = false;
	isLoggedIn=false;

	session_partner.Clean();
	writeCommand(server_sock,EXIT);
	server_sock->cclose();

}
//get all connected users
void Client::listAllUsers()
{
	writeCommand(server_sock,GET_ALL_CONNECTED_USERS);
}

void Client::openSession(string userName, string peerUsr)
{
	writeCommand(server_sock,OPEN_SESSION_WITH_USER);
	writeMsg(server_sock,userName);
	writeMsg(server_sock,peerUsr);
}

void Client::startGame(string userName, string gameUsr)
{
	 if (session_partner.name != gameUsr){
		cout << "ERROR - You have to start a game with the same user who you had open a session with" <<  endl;
	 }else{

	writeCommand(server_sock, START_GAME_WITH_USER);
	writeMsg(server_sock,userName);
	writeMsg(server_sock,gameUsr);
	 }
}

void Client::startGame(string userName)
{

	writeCommand(server_sock, START_GAME_WITH_RANDOM_USER);
	writeMsg(server_sock,userName);

}

void Client::closeSession()
{
	if(isInSession)
	{

			writeCommand(server_sock,CLOSE_SESSION_WITH_USER);

			isInSession= false;
			cout<<"session has ended"<<endl;

	}
	else
	{
		cout << "You don't have an open session" <<  endl;
	}
}


void Client::sendMsgToSession(string msg)
{
	if (isInSession == true)
	{

			udp_sock->sendTo("[" + client_name + "]" +  msg,session_partner.ip,session_partner.port);
	}
	else
	{
		cout << "You don't have an open session" <<  endl;
	}
}
void Client::gotIpAndPort()
{
	string msg,name;
	string port;
	char delim = ':';
	bool foundDelim = false;
	name = readMsg(server_sock);
	msg = readMsg(server_sock); //msg is ip & port
	session_partner.Clean();//clean the partner data
	session_partner.name=name;
	for (unsigned int i=0 ; i < msg.length() ; i++)
	{
		if (msg[i] != delim)
		{
			if (foundDelim == false)
				session_partner.ip += msg[i];
			else
				port += msg[i];
		}
		else
		{
			foundDelim = true;
		}
	}
	session_partner.port = atoi(port.c_str());//atoi-string to int
	cout << "You are now in session with ->" <<session_partner.name<< "(" +  msg + ")" << endl;
	isInSession = true;

}
//when logged in,construct udp socket and listen to incoming messages
void Client::loggedIn()
{

	string ip_and_port;
	string ip,port;
	char delim = ':';
	bool foundDelim = false;
	int int_port;

	client_name = readMsg(server_sock);
	ip_and_port = readMsg(server_sock);

	isLoggedIn = true;

	for (unsigned int i=0 ; i < ip_and_port.length() ; i++)
	{
		if (ip_and_port[i] != delim)
		{
			if (foundDelim == false)
				ip += ip_and_port[i];
			else
				port += ip_and_port[i];
		}
		else
		{
			foundDelim = true;
		}
	}

	int_port = atoi(port.c_str());
	udp_sock = new Peer2Peer(int_port);

}
bool Client::ConnectionStatus()
{
	return connectionStatus;
}
bool Client::sessionStatus()
{
	return isInSession;
}

void Client::run()
{
	int command;
	string username;
	string pass;
	string ip_and_port;
	string msg;

	while (connectionStatus)
	{
		command = readCommand(server_sock);

		if (!command)
			continue;

		switch(command)
		{
		case START_NEW_GAME:
			cout << MSG_FROM_SERVER + "Game ready" << endl;
			isInGame=true;
			game = new TicTacToe(server_sock);
			game->startGame();
			isInGame= false;
			 print_instructions();
			break;
		case YOU_WON:
			cout<<endl<<"Congrats! You have won!!!"<<endl;
			isInGame=false;
			break;
		case YOU_LOST:
			cout<<endl<<"You loose."<<endl;
			isInGame=false;
			break;
		case EVEN:
			cout<<endl<<"Game ends in a draw."<<endl;
			isInGame=false;
			break;
		case LOGIN_OR_SIGNUP://sign up or login complited succesfully
			cout << "Connection established\nLogin or register to establish a session" <<  endl;
			break;
		case LOGIN_DENIED:
			cout << MSG_FROM_SERVER + "Bad username or password" << endl;
			break;
		case USERNAME_TAKEN:
			cout <<  MSG_FROM_SERVER + "The username you entered is already taken" << endl;
			break;
		case ALL_USERS_LIST:
			gotAllUsers();
			break;
		case ALL_USERS_LIST_SCORE:
			gotAllUsersScore();
			break;
		case CONFIRM_USER:
			cout << MSG_FROM_SERVER + "You are now logged in" << endl;
			loggedIn();
			break;
		case BAD_COMMAND:
			cout << MSG_FROM_SERVER +  "You need to login/register first" <<  endl;
			break;
		case INCOMIMG_SESSION:
			gotIncomingSession();
			break;
		case OPEN_SESSION_ERROR:
			cout << MSG_FROM_SERVER + "Error opening session " << endl;
			isInSession=false;
			break;
		case CLOSE_SESSION_ERROR:
			cout << MSG_FROM_SERVER + "You are not in session" << endl;
			isInSession=false;
			break;
		case OPEN_CONNECTION_ERROR:
			cout << MSG_FROM_SERVER + "The user is already in session \nTry again Later..." << endl;
			break;
		case SESSION_ENDED:
			cout << MSG_FROM_SERVER + "Session has ended" << endl;
			isInSession = false;
			break;
		case OPEN_SESSION_ERROR2:
			cout << MSG_FROM_SERVER + "You have an open session" << endl;
			break;
		case CONNECTION_ERROR:
			cout << MSG_FROM_SERVER + "You don't have any open connections" << endl;
			break;
		case USERS_LIST://all the users in file
			gotUsersList();
			break;
		case TARGET_IP_AND_PORT:
			gotIpAndPort();
			break;
		case BYE_BYE_MSG:
			cout << MSG_FROM_SERVER + "Bye Bye" << endl;
			break;
		//default:
			//cout << " Got UNKNOWN command from server" << endl;
		}
	}
}
//now connected to some session
void Client::gotIncomingSession()
{
	string ip_and_port;
	string ip,port,name;
	int int_port;
	char delim = ':';
	bool found = false;

	name = readMsg(server_sock);
	ip_and_port = readMsg(server_sock);
	cout << MSG_FROM_SERVER + "You have an incoming session from: " + name + "(" + ip_and_port + "), use 's <message>' to send a msg" <<endl;
	isInSession = true;

	//add details to session partner
	for (unsigned int i = 0 ; i < ip_and_port.length() ; i++)
	{
		if (ip_and_port[i] != delim)
		{
			if (found == false)
				ip += ip_and_port[i];
			else
				port += ip_and_port[i];
		}
		else
		{
			found = true;
		}
	}
	int_port = atoi(port.c_str());
	session_partner.name = name;
	session_partner.ip = ip;
	session_partner.port = int_port;
}

//all the users in file
void Client::gotUsersList()
{
	int usersCount;
	string userName;

	usersCount = readCommand(server_sock); //size of list
	for (int i=0 ; i<usersCount ; i++)
	{
		userName = readMsg(server_sock);
		cout << "User #" << i+1 << ": " << userName << endl;
	}
}

//receiving the names of users in file
void Client::gotAllUsers()
{
	int size;
	string name;
	size = readCommand(server_sock);

	cout << "*** ALL USERS ***" << endl;

	for (int i=0 ; i < size ; i++)
	{
		name = readMsg(server_sock);
		cout << "User #" << i+1 << ": " << name << endl;
	}
}

void Client::gotAllUsersScore(){
	int size;
	string name;
	int score;

	size = readCommand(server_sock);
	cout << "*** ALL USERS SCORE***" << endl;

	for (int i=0 ; i < size ; i++)
	{
		name = readMsg(server_sock);
		score  = readCommand(server_sock);
		cout   << name <<"	"<< "score: "<< score<< endl;
	}
}

void Client::closeConnection()
{

		connectionStatus = false;
		isInSession = false;
		isConnectedToServer = false;
		isLoggedIn=false;
		session_partner.Clean();
		server_sock->cclose();


}
void Client::close()
{
	if(isConnectedToServer==true)
		disconnectFromServer();
}

string Client::getName()
{

		return session_partner.name;
}
Client::~Client()
{
	if(server_sock!=NULL)
     	close();
}
