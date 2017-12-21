/*
 * TicTacToe.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: user
 */

#include "ServerTicTacToe.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>




ServerTicTacToe::ServerTicTacToe(TCPSocket* socket1,TCPSocket* socket2){

	user1Socket = socket1;
	user2Socket = socket2;
    int i, j;
    for (int i =0;i<3;i++){
    		for (int j=0;j<3;j++){
    			mat[i][j]='-';
    		}
    	}
}

int ServerTicTacToe::startGame(){

	int count=0;
	string str_x,str_y;
	char chr_x,chr_y;
	int x,y;
	int ni;
	char nc;

	while (count < 9){


		cout<<endl<<"stage"<< count<<endl;
		str_x = readMsg(user1Socket);
		str_y = readMsg(user1Socket);

		chr_x=str_x[0];
		chr_y=str_y[0];


		x = chr_x - '0';
		y = chr_y - '0';
		cout<<"X play: "<<x<<" "<<y<<endl;
		ni = input('X', x, y);

		if (ni == 0)
		{
			writeMsg(user2Socket, str_x);
			writeMsg(user2Socket, str_y);
			count++;

		}
		if (count >=5)
				{
					nc = check();
					if (nc == 'f'){
						cout<<"No decision"<<endl;
						writeCommand(user1Socket, CONTINUE_GAME);
						writeCommand(user2Socket, CONTINUE_GAME);
						continue;
					}
					else if ('X' == nc)
					{
						cout<<"X won"<<endl;
						writeCommand(user1Socket, YOU_WON);
						writeCommand(user2Socket, YOU_LOST);
						return 1;
						break;
					}
					else if ('O' == nc)
					{
						cout<<"Y won"<<endl;
						writeCommand(user2Socket, YOU_WON);
						writeCommand(user1Socket, YOU_LOST);
						return 2;
						break;
					}
				}

		if(count == 9){break;}

		cout<<endl<<"stage"<< count<<endl;
		str_x = readMsg(user2Socket);
		str_y = readMsg(user2Socket);

		chr_x=str_x[0];
		chr_y=str_y[0];


		x = chr_x - '0';
		y = chr_y - '0';
		cout<<"Y play: "<<x<<" "<<y<<endl;

		ni = input('O', x, y);

		if (ni == 0)
		{
			writeMsg(user1Socket, str_x);
			writeMsg(user1Socket, str_y);
			count ++;
		}

		if (count >=6)
		{
			nc = check();
			if (nc == 'f'){
				cout<<"No decision"<<endl;
				writeCommand(user1Socket, CONTINUE_GAME);
				writeCommand(user2Socket, CONTINUE_GAME);
				continue;
			}
			else if ('X' == nc)
			{
				cout<<"X won"<<endl;
				writeCommand(user1Socket, YOU_WON);
				writeCommand(user2Socket, YOU_LOST);
				return 1;
				break;
			}
			else if ('O' == nc)
			{
				cout<<"Y won"<<endl;
				writeCommand(user2Socket, YOU_WON);
				writeCommand(user1Socket, YOU_LOST);
				return 2;
				break;
			}
		}

	}
	if (nc == 'f'){
		cout<<endl<<"Game ends in a draw."<<endl;
		writeCommand(user1Socket, EVEN);
		writeCommand(user2Socket, EVEN);
		return 0;

	}
		cout<<"Game over"<<endl;
		return 0;
}

int ServerTicTacToe::input(char choice, int x, int y)
{
	if (x >= 0 && x <= 2 && y >= 0 && y<= 2)
		if (mat[x][y] == '-')
		{
			mat[x][y] = choice;
			return 0;
		}
		else
		{
			cout<<endl<<"Co-ordinates "<<x<<" "<<y<<" are already used!"<<endl;
			return 1;
		}
	else
	{
		cout<<"\nInvalid Co-ordinates!"<<endl;
		return 1;
	}

}

char ServerTicTacToe::check()
{
	int i, j;
	char temp;

	for (j=0; j<3; j++)
	{
		if (mat[0][j] != '-')
		{
			temp = mat[0][j];
			if (j == 0)
			{
				if (mat[0][1] == temp)
					if (mat[0][2] == temp)
						return temp;
				if (mat[1][0] == temp)
					if (mat[2][0] == temp)
						return temp;
				if (mat[1][1] == temp)
					if (mat[2][2] == temp)
						return temp;
			}
			else if (j == 1)
			{
				if (mat[1][1] == temp)
					if (mat[2][1] == temp)
						return temp;
			}
			else
			{
				if (mat[1][2] == temp)
					if (mat[2][2] == temp)
						return temp;
			}
		}
	}
	for (i=1; i<3; i++)
	{
		if (mat[i][0] != '-')
		{
			temp = mat[i][0];
			if (i == 1)
			{
				if (mat[1][1] == temp)
					if (mat[1][2] == temp)
						return temp;
			}
			else
			{
				if (mat[2][1] == temp)
					if (mat[2][2] == temp)
						return temp;
				if (mat[1][1] == temp)
					if (mat[0][2] == temp)
						return temp;
			}
		}
	}

	return 'f';

}


void ServerTicTacToe::display()
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

ServerTicTacToe::~ServerTicTacToe(){}



