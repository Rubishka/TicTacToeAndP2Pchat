

#include "Common.h"
#include "Peer2Peer.h"
#include "TicTacToe.h"


typedef struct
{
public:
	string name;
	string ip;
	int port;
	void Clean()
	{
		name.clear();
		ip.clear();
		port = 0;
	}
}Partner;

class Client : public MThread
{
public:
	string client_name;
	string password;
	TCPSocket* server_sock;
	Peer2Peer* udp_sock;
	TicTacToe* game;

	Partner session_partner;
	bool connectionStatus;//true-if the connection to the server succeeded,false-if not
	bool isInSession;
	bool isLoggedIn;//if the client is logged in
	bool isConnectedToServer;//if connected to the server right now
	 bool isInGame=false;


	Client();
	void run();//waiting for commands from server
	void gotIncomingSession();
	bool connectToServer(string ip,int port); //connect to server with tcp
	void sendMsgToServer(string msg);
	void login(string name,string pass);
	void signup(string name,string pass);
	void listAllUsers();
	void getUsers();//get all users names from file
	void gotAllUsers();
	void getUserScore();
	void gotAllUsersScore();
	void startGame(string userName);
	void gotUsersList(); //connected users
	void disconnectFromServer();
	void openSession(string userName, string peerUsr); //udp
	void closeSession();
	void sendMsgToSession(string msg);
	void gotIpAndPort();
	void loggedIn();
	bool ConnectionStatus();
	bool sessionStatus();
	bool chartoomStatus();
	void closeConnection();
	string getName();
	void close();

	void startGame(string userName, string gameUsr);

	~Client();

};

