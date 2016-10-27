#include <iostream>
#include "GameState.h"

using namespace std ;

void Play2PlayerGame() // test for playing two player game , hotseat version.
{
	Graph<int>* graffiti = new Graph<int>() ; // starting graph.
	srand(time(NULL)) ; // random seed for the rand() , else it give sthe same number every time.

	// Generate 6 starting vertices for graph , for a hexagon.  graffiti->InsertVertex(int , bool):  int is value of vertex , bool is just a flag for displaying error messages.  

	graffiti->InsertVertex(1, false) ;
	graffiti->InsertVertex(2, false) ;
	graffiti->InsertVertex(3, false) ;
	graffiti->InsertVertex(4, false) ;
	graffiti->InsertVertex(5, false) ;
	graffiti->InsertVertex(6, false) ;

	GameState* gameBoard = new GameState(NULL, graffiti) ; // store graph in game board

	bool isPlayerOne = false ;

	// std::cout << "\nseed: " << rand() << " \n" ;

	if (rand() % 2 == 1)
	{
		isPlayerOne = true ; 
	}

	int currentPlayer = -99999 ;

	// start game!

	while (true) 
	{
		int startVertex ;
		int endVertex ;
		char ui ;

		if (isPlayerOne == true) currentPlayer = 1 ;
		else currentPlayer = 2 ;

		gameBoard->GameBoard()->Print() ; // displays the gameboard on the command line. 

		cout << endl ;

		cout << "[+] It's player " << currentPlayer << "'s turn.  Do you want to quit yet?  (y) or (n)" << endl << endl << "        " ;
		cin >> ui ;

		while (ui != 'y' && ui != 'n')
		{
			cout << "\n    I'm sorry.  I didn't get that.  Please enter (y) to quit and (n) to keep playing:  " << endl << endl << "        " ;
			cin >> ui ;
		}

		std::cout << " \n" ;

		if (ui == 'y')
			break ;

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

		isPlayerOne = !isPlayerOne ;

		cout << endl;
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