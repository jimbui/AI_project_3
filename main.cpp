#include <iostream>

#include "GameState.h"
#include <time.h>

using namespace std ;

void Play2PlayerGame() // test for playing two player game , hotseat version.
{
	Graph<int>* graffiti = new Graph<int>() ; 
	srand(time(NULL)) ; // random seed for the rand() , else it gives the same number every time.
	int turn = 1 ; // this is the turn counter.

	// generate six starting vertices for graph , for a hexagon.  graffiti->InsertVertex(int , bool):  int is value of vertex , bool is just a flag for displaying error messages.  
	graffiti->BuildGameGraph();

	/*graffiti->InsertVertex(1, false) ;
	graffiti->InsertVertex(2, false) ;
	graffiti->InsertVertex(3, false) ;
	graffiti->InsertVertex(4, false) ;
	graffiti->InsertVertex(5, false) ;
	graffiti->InsertVertex(6, false) ;*/

	GameState* gameBoard = new GameState(NULL, graffiti) ; // store graph in game board

	bool isPlayerOne = false ; // this is the device for taking turns.

	// std::cout << "\nseed: " << rand() << " \n" ;

	if (rand() % 2 == 1) // picks a player to start.
	{
		isPlayerOne = true ; 
	}

	int currentPlayer = -99999 ; // just a place holder value.

	// start game!

	while (true) 
	{
		int startVertex ;
		int endVertex ;
		char ui ;

		if (isPlayerOne == true) currentPlayer = 1 ;
		else currentPlayer = 2 ;

		std::cout << "/**************************************** BELOW IS TURN " << turn << " **************************************************/ \n\n" ;

		std::cout << "[+] CURRENT GAME BOARD: \n\n" ;

		gameBoard->GameBoard()->Print() ; // displays the gameboard on the command line. 
		cout << endl ;

		/*

		// i commented this out because it was a pain to keep hitting no.

		cout << "[+] It's player " << currentPlayer << "'s turn.  Do you want to quit yet?  (y) or (n).  Resistance is futile." << endl << endl << "        " ;
		cin >> ui ;

		while (ui != 'y' && ui != 'n')
		{
			cout << "\n    I'm sorry.  I didn't get that.  Please enter (y) to quit and (n) to keep playing:  " << endl << endl << "        " ;
			cin >> ui ;
		}

		std::cout << " \n" ;

		if (ui == 'y')
			break ;

		*/

		gameBoard->Expand(currentPlayer) ; // this shows all the possible moves.

		cout << "[+] It's player " << currentPlayer << "'s turn. \n\n" ;

		do // for the love of god , enter an integer.  
		{
			cout << "    Enter starting vertex:  " << endl ;
			std::cout << " \n        " ;
			cin >> startVertex ;
			std::cout << " \n" ;
			cout << "    Enter ending vertex:  " << endl << endl << "        " ;
			cin >> endVertex ;
			std::cout << " \n" ;

			if (startVertex == endVertex) std::cout << "    You cannot insert between duplicate edges.\n" ; // this is just the error message.  logical implementation is in "Graph.h".
		} 
		while (!gameBoard->GameBoard()->InsertEdge(startVertex, endVertex, currentPlayer, true));

		isPlayerOne = !isPlayerOne ; // switches players.  this really should be moved to the end , but would break alot of functions.

		std::cout << "[+] MOVE SELECTED: \n\n" ;
		gameBoard->GameBoard()->Print() ; // prints the board that you moves.

		// int numOps = 0;

		if (graffiti->TriangleDetected(currentPlayer)) // lose condition.
		{
			std::cout << "[-] PLAYER " << currentPlayer << " HAS LOST THE GAME BY CREATING A TRIANGLE!  GAME EXITING! \n\n" ;
			break ;
		}

		cout << endl;

		std::cout << "/**************************************** ABOVE IS TURN " << turn << " **************************************************/ \n\n" ;

		turn++ ;
	}
}

int main(void)
{
	cout << " \n" 
		 << "/***********************************************************************************************************/\n"      
         << "/*                                       welcome to the hexagon game!                                      */\n" 
         << "/***********************************************************************************************************/\n"
		 << " \n" ;

	Play2PlayerGame() ;

	// Graph<int>* g = new Graph<int>();

	// g->BuildGameGraph();

	// Graph<int>* h = g->Copy();

	// Create another test graph.

	/*Graph<int>* graffiti = new Graph<int>();

	graffiti->BuildGameGraph();

	graffiti->InsertEdge(1, 2, 2, false);
	graffiti->InsertEdge(2, 3, 2, false);
	graffiti->InsertEdge(3, 4, 2, false);
	graffiti->InsertEdge(4, 5, 2, false);
	graffiti->InsertEdge(5, 6, 2, false);
	graffiti->InsertEdge(5, 1, 1, false);
	graffiti->InsertEdge(5, 2, 1, false);

	graffiti->Print();

	int opCount = 0;

	cout << "Triangle Detected:  " << (graffiti->TriangleDetected(2, opCount) ? "Yes" : "No") << endl;
	cout << "Number of Operations:  " << opCount << endl;*/

	// Create test graph...
	/*Graph<int>* graffiti = new Graph<int>();

	graffiti->Print();
	cout << endl;

	graffiti->InsertVertex(20, false);
	graffiti->InsertVertex(30, false);

	graffiti->Print();
	cout << endl;

	graffiti->InsertEdge(20, 30, 5, false);

	graffiti->Print();
	cout << endl;*/

	// Create test game state
	/*GameState* gs = new GameState(NULL, graffiti);

	gs->GetChildren()->Add(gs);
	gs->GetChildren()->GetValue(0)->GetChildren()->Add(gs);

	cout << "Number of children:  " << gs->GetChildren()->Length() << endl;*/

	cin.get();

	return 0;
}