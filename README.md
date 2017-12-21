"# TicTacToeAndP2Pchat" 

Client-server Tic Tac Toe game with P2P chat

The functionality of the platform are:

login:
1. New user can register to the system with a username and password
2. Existing user can login to the system with his username and password
3. The system remember all the user and passwords even if the
server is shutdown and restarted.

Matching:

4. User can see the other users which are online and available to play with him.
5. A user can send a request to start a game to another user
6. The platform enable a user to automatically start a game with a random available user.
7. A user may accept or reject a game request if he was not the one who sent the request or asked the platform to automatically do it for him.

Game play:

8. After a matching of two players is done the system enable the game app to send messages from one user to the other.
9. Exchanging the messages between the game apps is performed in P2P using UDP protocol.
10. The game app can end the game and declare its result: user 1 won, user 2 won, draw, game cancelled. And the score for each user: for example winner: user 1, score 1: 20, score 2: 10
11. After the game a user is able to see the scoreboard and his position in it. The scoreboard is ordered the users according to their

Non functionality:
1. The system is a hybrid P2P system with central directory.
2. The communication with the central directory iis performed using TCP.
3. The game messages during a game is transmitted P2P using UDP.
4. The password stored at the server on a file.
5. The password will be saved as a hash instead of plain text.

"# TicTacToeAndP2Pchat" 
