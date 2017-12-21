/*

 * TicTacToe.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: user
 */
#include "TicTacToe.h"


TicTacToe::TicTacToe(TCPSocket* sock){
	server_sock=sock;
	running = false;
	playerTurn=false;
	for (int i =0;i<3;i++){
		for (int j=0;j<3;j++){
			mat[i][j]='-';
		}
	}


}

int TicTacToe::startGame(){
	string userName;
	string temp;
	 char sign,rivalSign;
	 string str_x, str_y;
	 char chr_x,chr_y;
	int ni;
	int inp;
	int x,y;
	int sendX, sendY;
	char choice;
	string rivalChoice;
	int count=0;
	string test;
	int command;


	userName = readMsg(server_sock);
	temp = readMsg(server_sock);
	sign=temp[0];
	cout<< "You play as: "<< sign << "\n against:"<< userName<<endl;

	if (sign == 'X')
	{
		inp = 2;

		cout<<userName<<" will play first."<<endl<<endl;
		rivalSign='O';

	}
	else
	{
		inp = 1;

		cout<<"You will play first."<<endl<<endl;
		rivalSign='X';

	}

	cout<<endl<<"Starting Game..."<<endl;
	sleep(3);
	display();

	while (count < 9)
		{
			//memset(&co_ordinates_buffer, 0, sizeof(co_ordinates_buffer));

			if (inp % 2 != 0 )
			{
				cout<<endl<<userName<<"'s turn. Please wait..."<<endl;

 				str_x = readMsg(server_sock);
				str_y = readMsg(server_sock);

				chr_x=str_x[0];
				chr_y=str_y[0];


				x = chr_x - '0';
				y = chr_y - '0';
				ni = input(rivalSign, x, y);
				if (ni == 0)
				{
					inp ++;
					count ++;

					cout<<endl<<userName<<" has played. Updating Matrix..."<<endl;
				}
			}
			else
			{
				cout<<endl<<"Your turn. Enter co-ordinates separated by a space : "<<endl;
				cin.clear();
				cin.ignore(10000, '\n');
				cin>>str_x>>str_y;
				cout<< "You choice "<< str_x<<" and "<<str_y<<endl;
				chr_x=str_x[0];
				chr_y=str_y[0];

				x = chr_x - '0';
				y = chr_y - '0';

				ni = input(sign, x, y);

				if (ni == 0)
				{
					inp ++;
					count ++;
					writeMsg(server_sock, str_x);
					writeMsg(server_sock, str_y);

					cout<<endl<<"Updating Matrix..."<<endl;
				}
			}

			sleep(2);
			system("clear");
			display();

			if (count >=5)
			{
				command = readCommand(server_sock);
				switch(command)
				{
				case YOU_WON:
					cout<<endl<<"Congrats! You have won!!!"<<endl<<userName<<" lost."<<endl;
					return 1;
					break;
				case YOU_LOST:
					cout<<endl<<"You loose."<<endl;
					return 1;
					break;
				case EVEN:
					cout<<endl<<"Game ends in a draw."<<endl;
					break;
				case CONTINUE_GAME:
					cout<<endl<<"No decision - continue."<<endl;
					break;
				default:
					break;
			}

		}

	}
	cout<<endl<<"Thank You for playing Tic-tac-Toe"<<endl;

}

void TicTacToe::play(){

	cout<<"play??"<<endl;
}


void TicTacToe::display()
{

	int i, j;
	system("clear");
	cout<<"\nWelcome to the Tic-Tac-Toe Game!\n\nGrid Co-ordinates : "<<endl<<endl;

    for (i=0; i<3; i++)
	{
		cout<<"\t";
	    for (j=0; j<3; j++)
			cout<<i<<" "<<j<<"    ";
		cout<<endl;
	}

	cout<<"\nThe Tic-Tac-Toe board : "<<endl<<endl;
	for (i=0; i<3; i++)
	{
		cout<<"\t";
	    for (j=0; j<3; j++)
		    cout<<" "<<mat[i][j]<<"     ";
		cout<<endl;
	}
}

int TicTacToe::input(char choice, int x, int y)
{
	if (x >= 0 && x <= 2 && y >= 0 && y<= 2)
		if (mat[x][y] == '-')
		{
			mat[x][y] = choice;
			return 0;
		}
		else
		{
			cout<<endl<<"Co-ordinates "<<x<<" "<<y<<" are already used!"<<endl<<"Press ENTER to continue..."<<endl;
			do{}
			while(cin.get() != '\n');
			return 1;
		}
	else
	{
		cout<<"\nInvalid Co-ordinates!"<<endl<<"Press ENTER to continue..."<<endl;
		do{}
		while(cin.get() != '\n');
		return 1;
	}

}

int TicTacToe::endGame(){
}

