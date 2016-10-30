#include <iostream>

#include "GameTree.h"
#include "Graph.h"
#include "GameState.h"
#include "Dynamic1DArray.h"
#include "Dynamic2DArray.h"
#include <time.h>

using namespace std;

void Play2PlayerGame() // test for playing two player game , hotseat version.
{
	Graph<int>* graffiti = new Graph<int>();
	srand(time(NULL)); // random seed for the rand() , else it gives the same number every time.
	int turn = 1; // this is the turn counter.

				  // generate six starting vertices for graph , for a hexagon.  graffiti->InsertVertex(int , bool):  int is value of vertex , bool is just a flag for displaying error messages.  
	graffiti->BuildGameGraph();

	/*graffiti->InsertVertex(1, false) ;
	graffiti->InsertVertex(2, false) ;
	graffiti->InsertVertex(3, false) ;
	graffiti->InsertVertex(4, false) ;
	graffiti->InsertVertex(5, false) ;
	graffiti->InsertVertex(6, false) ;*/

	GameState* gameBoard = new GameState(NULL, graffiti, 15); // store graph in game board

	bool isPlayerOne = false; // this is the device for taking turns.

							  // std::cout << "\nseed: " << rand() << " \n" ;

	if (rand() % 2 == 1) // picks a player to start.
	{
		isPlayerOne = true;
	}

	int currentPlayer = -99999 ; // just a place holder value.
	int playerInput  = - 99999 ;

	while (true)
	{
		std::cout << "    Enter 1 for you to start, 2 for the AI to start, or 0 for random start. \n\n" ;
		cin >> playerInput ;

		if (playerInput == 0)
		{
			break ;
		}

		else if (playerInput == 1) 
		{
			isPlayerOne = true ;
			break ;
		}

		else if (playerInput == 2) 
		{
			isPlayerOne = false ;
			break ;
		}

		else std::cout << "    Invalid input, please try again. \n\n" ;
	}

	while (true)
	{
		int startVertex = 0;
		int endVertex = 0;
		char ui;

		// player 1 is human player.
		// player 2 is AI.

		if (isPlayerOne == true) currentPlayer = 1;
		else currentPlayer = 2;

		std::cout << "/**************************************** BELOW IS TURN " << turn << " **************************************************/ \n\n";

		std::cout << "[+] CURRENT GAME BOARD: \n\n";

		gameBoard->GameBoard()->Print(); // displays the gameboard on the command line. 
		cout << endl;

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

		// gameBoard->Expand(currentPlayer, currentPlayer, turn, true) ; // this shows all the possible moves.  doesn't actually do anything else.

		if (currentPlayer == 1)
		{
			cout << "[+] It's your turn. \n\n";

			do // for the love of god , enter an integer.  
			{
				cout << "    Enter starting vertex:  " << endl;
				std::cout << " \n        ";
				cin >> startVertex;
				std::cout << " \n";
				cout << "    Enter ending vertex:  " << endl << endl << "        ";
				cin >> endVertex;
				std::cout << " \n";

				// if (startVertex == endVertex) std::cout << "    You cannot insert between duplicate edges.\n"; // this is just the error message.  logical implementation is in "Graph.h".
			} 
			while (!gameBoard->GameBoard()->InsertEdge(startVertex, endVertex, currentPlayer, true));// makes move.
		}

		else 

		{
			cout << "[+] It's the AI's turn. \n\n"; // AI MAKES 

			GameState* aiBoard = new GameState(NULL, graffiti->Copy(), 15); // copies the current gamestate for ai to make calculations.
			GameTree* aiTree = new GameTree(aiBoard->Copy()); // game tree of the current board.
			aiTree->BuildTree(turn, 1, currentPlayer, false);
			aiBoard = aiTree->BestMove(currentPlayer);

			// find difference between the two aiBoard and gameBoard.

			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					if (startVertex == 0)
					{
						if (gameBoard->GameBoard()->edges->GetValue(i, j) != aiBoard->GameBoard()->edges->GetValue(i, j))
						{
							startVertex = i;
							endVertex = j;

							break;
						}
					}
				}
			}

			gameBoard->GameBoard()->InsertEdge(startVertex + 1, endVertex + 1, currentPlayer, false);

			delete aiTree;
			delete aiBoard;
		}

		isPlayerOne = !isPlayerOne; // switches players.  this really should be moved to the end , but would break alot of functions.

		std::cout << "[+] MOVE SELECTED: \n\n";
		gameBoard->GameBoard()->Print(); // prints the board that you moves.

										 // int numOps = 0;

		if (graffiti->TriangleDetected(currentPlayer)) // lose condition.
		{
			if (currentPlayer == 1) std::cout << "[-] YOU HAVE LOST THE GAME BY CREATING A TRIANGLE!  GAME EXITING! \n\n";
			else std::cout << "[-] YOU BEAT THE AI!  CONGRATULATIONS!  GAME EXITING! \n\n";

			break;
		}

		cout << endl;

		gameBoard->GetChildren()->Clear();

		std::cout << "/**************************************** ABOVE IS TURN " << turn << " **************************************************/ \n\n";

		turn++;
	}
}

int main(void)
{
	cout << " \n"
		<< "/***********************************************************************************************************/\n"
		<< "/*                                       welcome to the hexagon game!                                      */\n"
		<< "/***********************************************************************************************************/\n"
		<< " \n" ;

	/*Graph<int>* g = new Graph<int>();
	g->BuildGameGraph();
	GameState* gs = new GameState(NULL, g->Copy(), 15);
	GameTree* gt = new GameTree(gs->Copy());
	gt->BuildTree(1, 4, 1, false);
	gt->BestMove(1);
	gt->BFPrint();*/

	// How many graphs can safely be stored?

	/*Graph<int>* g = new Graph<int>();
	g->BuildGameGraph();
	Dynamic1DArray<GameState*>* gs = new Dynamic1DArray<GameState*>(NULL);
	for (int i = 0; i < 100000; i++)
	gs->Add(new GameState(NULL, g->Copy()));
	gs->Clear();
	delete gs;
	gs = new Dynamic1DArray<GameState*>(NULL);
	for (int i = 0; i < 100000; i++)
	gs->Add(new GameState(NULL, g->Copy()));
	gs->Clear();
	delete gs;
	gs = new Dynamic1DArray<GameState*>(NULL);
	for (int i = 0; i < 100000; i++)
	gs->Add(new GameState(NULL, g->Copy()));
	gs->Clear();
	delete gs;*/



















	/*
	// Initialize depth bounds for search tree.  DO NOT DELETE!!!!! ========================================================
	Dynamic1DArray<int>* depthBounds = new Dynamic1DArray<int>(-1, 15) ; // depth bound list , iterates through this list.
	depthBounds->Add(3);
	depthBounds->Add(3);
	depthBounds->Add(3);
	depthBounds->Add(3);
	depthBounds->Add(4);
	depthBounds->Add(4);
	depthBounds->Add(4);
	depthBounds->Add(4);
	depthBounds->Add(5);
	depthBounds->Add(5);
	depthBounds->Add(6);
	depthBounds->Add(6);
	depthBounds->Add(6);
	depthBounds->Add(6);
	depthBounds->Add(6);
	// =====================================================================================================================
	Graph<int>* g = new Graph<int>(); // the starting game state.
	g->BuildGameGraph(); // 6 vertices.
	GameState* gs = new GameState(NULL, g->Copy(), 15) ; // copies the game state.
	GameTree* gt; // this is for the AI , for calculations.
	int player = 1 ;
	for (int i = 0; i < 15; i++) // makes 15 random moves.
	{
	gs->GameBoard()->Print();
	cout << "Winner:  " << (gs->GameBoard()->TriangleDetected(1) ? "Player 2" : (gs->GameBoard()->TriangleDetected(2) ? "Player 1" : "NIL")) << endl << endl;
	gt = new GameTree(gs->Copy());
	gt->BuildTree(i + 1, depthBounds->GetValue(i), player, false); // this is the "random heuristic".
	gs = gt->BestMove() ; // this makes the move.
	delete gt; // if not placed , memory leaks.
	if (gs != NULL) // change player.
	{
	player = (player == 1 ? 2 : 1);
	}
	else
	break;
	}
	*/











	Play2PlayerGame();

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
	cin.get();

	return 0;
}