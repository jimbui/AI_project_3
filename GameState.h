// This is a node containing the current game state and pointers to "next" nodes.  State space
// = O(((5 + 4 + 3 + 2 + 1) - CurrentMove)!) = O((15 - CurrentMove)!)

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include "Graph.h"
// #include "DynamicGraphArray.h"

class GameState
{
private:

	GameState* parent ; // points the parent gamestate that created this game state.
	Graph<int>* currentGameBoard ; // this is the current board of this board.
	int utilityFcn ; // the heuristic value.
	
	// Contains depth flag to determine significance of win and loss?

	Dynamic1DArray<GameState*>* children ; // all the children of this board.  assume max of 15 , not too sure.

	// Add flags as necessary...
public:
	GameState(GameState* Parent, Graph<int>* GameBoard, int numMovesRemaining)
	{
		parent = Parent ;
		currentGameBoard = GameBoard ;
		children = new Dynamic1DArray<GameState*>(NULL, numMovesRemaining);
		utilityFcn = -1000;  // GetUtility(currentGameBoard, 1, 1);
	}

	~GameState()
	{
		delete currentGameBoard;
		// delete children;
	}

	// Deep copy ... use this to add to tree
	GameState* Copy()
	{
		GameState* copiedGameState = new GameState(parent, currentGameBoard->Copy(), children->Length());

		copiedGameState->children = children->Copy();
		copiedGameState->utilityFcn = utilityFcn;

		return copiedGameState;
	}

	// Deep copy ... use this to get the next state
	GameState* CopyWithoutLinks()
	{
		return new GameState(NULL, currentGameBoard->Copy(), 0);
	}

	// Accessors/Mutators
	Graph<int>* GameBoard() { return currentGameBoard; };

	int Utility() const { return utilityFcn; };

	void SetUtility(int winWeight, int lossWeight, int startingPlayer, int currentPlayer) // this is the heuristic function.
	{
		utilityFcn = 0;

		// Do not expand if move is a win or loss.
		if (currentGameBoard->TriangleDetected(currentPlayer))
		{
			if (currentPlayer == startingPlayer)
			{
				utilityFcn = -5;
				return;
			}
			else
			{
				utilityFcn = 5;
				return;
			}
		}

		// TODO:  Add method to determine the correct utility function.

		/********************************************************************************************************
		*	h(n)	= ['Personal Winning Factors'] - ['Losing Factors']
		*
		*			   C - M * num_losses - total_moves;	final node is maxnode --> Next move is done by user.
		*			= {N * num_wins + total_moves;			final node is minnode --> Next move is done by CPU.
		*
		*	N and M are weighted values, and C is a constant.  Note that
		*	if there is a sequence with many wins, the CPU should consider
		*	this as a better path
		*	than one with many losses, even if the supposed number of
		*	available moves is the same.
		*
		*	Minimax requires that "the computer should make the move which
		*	leaves its opponent capable of doing the least damage."  Thus,
		*	the only thing to consider would be total number of available
		*	moves.
		********************************************************************************************************/

		// How to compute...  Look at potential child nodes and determine utility
		// based on # wins / # losses and the list length.

		// Do some stuff.

		int nextPlayer = (currentPlayer == 2 ? 1 : 2);
		int move_count = 0;

		bool sideOfMove = (nextPlayer == startingPlayer);  // Stores whether current move is on opposing side (0) or same side (1).

		Graph<int>* copyGameBoard = currentGameBoard->Copy(); // make 1 boards.  15 because that is the max amount of moves at any given time.

									   // I made deep copy functions.
		// for (int k = 0; k < 15; k++) 
		// copyGameBoard[k] = currentGameBoard->Copy(); // initialize all 15 boards.

		int i_array[6 /*currentGameBoard->vertices->Length()*/] = { 0 , 0 , 0 , 0 , 0 , 0 };
		int j_array[6 /*currentGameBoard->vertices->Length()*/] = { 0 , 0 , 0 , 0 , 0 , 0 };

		for (int i = 0; i < currentGameBoard->vertices->Length(); i++) // this generates the moves.
		{
			for (int j = 0; j < currentGameBoard->vertices->Length(); j++)
			{
				if ((j_array[j] == 0 || i_array[i] == 0) && i != j)
				{
					if (copyGameBoard->InsertEdge(i + 1, j + 1, nextPlayer, false))
					{
						bool triangleDetected = copyGameBoard->TriangleDetected(nextPlayer);

						move_count++;
						j_array[i] = 1;
						i_array[j] = 1;

						if (sideOfMove) // Basic U(n):  If the move is a CPU move and results in loss, decrement utility; else increment because a move is available.
							utilityFcn += (triangleDetected ? -2 : 1);
						else // Basic U(n):  If the move is a human move and results in a win, increment utility; else decrement because the human has more options.
							utilityFcn += (triangleDetected ? 2 : -1);

						// Revert to previous state (to save memory)
						copyGameBoard->RemoveEdge(i + 1, j + 1, false);
					}
				}
			}
		}

		

		//for (int i = 0; i < move_count; i++) // this prints the possible boards.
		//{
		//	// bool triangleDetected = copyGameBoard[i]->TriangleDetected(nextPlayer);

		//	//if (showOutput)
		//	//{
		//	//	std::cout << "   -------------------------------------------\n";
		//	//	std::cout << "          [" << i + 1 << "]: ";

		//	//	// int numOps = 0;

		//	//	if (triangleDetected) std::cout << "TRIANGLE DETECTED. \n\n";
		//	//	else std::cout << "triangle not detected. \n\n";

		//	//	copyGameBoard[i]->Print();
		//	//}
		//}

		/*for (int i = 0; i < 15; i++)
			delete copyGameBoard[i];

		delete copyGameBoard;*/

		// return utility;
	}

	void Expand(int startingPlayer, int currentPlayer, int totalMovesRemaining, bool showOutput)
	{
		// Do not expand if move is a win or loss.
		if (currentGameBoard->TriangleDetected(currentPlayer))
			return;

		// next two lines are redundant , will fix later.
		
		int nextPlayer = (currentPlayer == 2 ? 1 : 2) ;
		// if (currentPlayer == 1) nextPlayer = 1 ;

		int move_count = 0 ;

		Graph<int>* copyGameBoard; // make 15 boards.  15 because that is the max amount of moves at any given time.

		// I made deep copy functions.
		/*for (int k = 0 ; k < totalMovesRemaining; k++)*/ copyGameBoard = currentGameBoard->Copy(); // initialize all 1 boards.

		// 1 BOARD GENERATED INITIALLY TO SAVE MEMORY!!!!!!!!!

		//for (int k = 0 ; k < 30 ; k++) // deep copy of edges and vertices from current board to each board.
		//{
		//	copyGameBoard[k]->InsertVertex(1, false) ;
		//	copyGameBoard[k]->InsertVertex(2, false) ;
		//	copyGameBoard[k]->InsertVertex(3, false) ;
		//	copyGameBoard[k]->InsertVertex(4, false) ;
		//	copyGameBoard[k]->InsertVertex(5, false) ;
		//	copyGameBoard[k]->InsertVertex(6, false) ;

		//	for (int i = 0 ; i < currentGameBoard->vertices->Length() ; i++) 
		//	{
		//		for (int j = 0 ; j < currentGameBoard->vertices->Length() ; j++)
		//		{
		//			copyGameBoard[k]->InsertEdge(i + 1 , j + 1, currentGameBoard->edges->GetValue(i , j) , false) ;
		//		}
		//	}
		//}

		// to avoid repeats.

		int i_array[6 /*currentGameBoard->vertices->Length()*/] = {0 , 0 , 0 , 0 , 0 , 0} ;
		int j_array[6 /*currentGameBoard->vertices->Length()*/] = {0 , 0 , 0 , 0 , 0 , 0} ;

		if (showOutput)
			std::cout << "[+] POSSIBLE GAME BOARDS: \n\n";

		for (int i = 0 ; i < currentGameBoard->vertices->Length() ; i++) // this generates the moves.
		{
			for (int j = 0 ; j < currentGameBoard->vertices->Length() ; j++)
			{
				if((j_array[j] == 0 || i_array[i] == 0) && i != j)
				{
					if (copyGameBoard->InsertEdge(i + 1 , j + 1 , nextPlayer , false)) 
					{
						move_count++ ;
						j_array[i] = 1 ;
						i_array[j] = 1 ;

						bool triangleDetected = copyGameBoard->TriangleDetected(nextPlayer);

						if (showOutput)
						{
							std::cout << "   -------------------------------------------\n";
							std::cout << "          [" << i + 1 << "]: ";

							// int numOps = 0;

							if (triangleDetected) std::cout << "TRIANGLE DETECTED. \n\n";
							else std::cout << "triangle not detected. \n\n";

							copyGameBoard->Print();
						}

						if (!triangleDetected || nextPlayer != currentPlayer)
							children->Add(new GameState(this, copyGameBoard->Copy(), totalMovesRemaining));

						copyGameBoard->RemoveEdge(i + 1, j + 1, false);
					}
				}
			}
		}

		//for (int i = 0 ; i < move_count ; i++) // this prints the possible boards.
		//{
		//	// bool triangleDetected = copyGameBoard[i]->TriangleDetected(nextPlayer);  // Changed currentPlayer to nextPlayer so that the 
		//																				// Next player's move would be one checked for triangle
		//	
		//	/*else
		//		delete copyGameBoard[i];*/
		//}

		// Graph<int> nextGameBoard = copyGameBoard ;

		// nextGameBoard.Print() ;
	}

	Dynamic1DArray<GameState*>* GetChildren() { return children ; } ;
} ;

#endif