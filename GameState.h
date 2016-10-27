// This is a node containing the current game state and pointers to "next" nodes.  State space
// = O(((5 + 4 + 3 + 2 + 1) - CurrentMove)!) = O((15 - CurrentMove)!)

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include "Graph.h"

class GameState
{
	private:

	GameState* parent ; // points the parent gamestate that created this game state.
	Graph<int>* currentGameBoard ; // this is the current board of this board.
	int utilityFcn ; // the heuristic value.
	
	// Contains depth flag to determine significance of win and loss?

	Dynamic1DArray<GameState*>* children ; // all the children of this board.  assume max of 15 , not too sure.

	// Add flags as necessary...

	int GetUtility(Graph<int>* GameBoard, int winWeight, int lossWeight) // this is the heuristic function.
	{
		int utility = 0;

		// TODO:  Add method to determine the correct utility function.

		/********************************************************************
		*	h(n)	= ['Personal Winning Factors'] - ['Losing Factors']
		*			= [Available Move] + N * [Win] - M * [Loss]
		*
		*	N and M are weighted values.  Note that if there is a sequence 
		*	with many wins, the CPU should consider this as a better path
		*	than one with many losses, even if the supposed number of 
		*	available moves is the same.
		*	
		*	Minimax requires that "the computer should make the move which 
		*	leaves its opponent capable of doing the least damage."  Thus,
		*	the only thing to consider would be total number of available
		*	moves.
		*	
		********************************************************************/

		// How to compute...  Look at potential child nodes and determine utility
		// of each.

		// Do some stuff.

		return utility;
	}

	public:

	GameState(GameState* Parent, Graph<int>* GameBoard)
	{
		parent = Parent ;
		currentGameBoard = GameBoard ;
		children = new Dynamic1DArray<GameState*>(NULL) ;
		utilityFcn = GetUtility(currentGameBoard, 1, 1;
	}

	~GameState()
	{
		delete currentGameBoard ;
	}

	// Accessors/Mutators
	Graph<int>* GameBoard() { return currentGameBoard; };

	void Expand(int currentPlayer)
	{
		// next two lines are redundant , will fix later.
		
		int nextPlayer = 2 ;
		if (currentPlayer == 1) nextPlayer = 1 ;

		int move_count = 0 ;

		Graph<int>* copyGameBoard[30] ; // make 15 boards.  15 because that is the max amount of moves at any given time.

		// I made deep copy functions.
		for (int k = 0 ; k < 30 ; k++) copyGameBoard[k] = currentGameBoard->Copy(); // initialize all 15 boards.

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

		for (int i = 0 ; i < currentGameBoard->vertices->Length() ; i++) // this generates the moves.
		{
			for (int j = 0 ; j < currentGameBoard->vertices->Length() ; j++)
			{
				if((j_array[j] == 0 || i_array[i] == 0) && i != j)
				{
					if (copyGameBoard[move_count]->InsertEdge(i + 1 , j + 1 , nextPlayer , false)) 
					{
						move_count++ ;
						j_array[i] = 1 ;
						i_array[j] = 1 ;
					}
				}
			}
		}

		std::cout << "[+] POSSIBLE GAME BOARDS: \n\n" ;

		for (int i = 0 ; i < move_count ; i++) // this prints the possible boards.
		{
			std::cout << "   -------------------------------------------\n" ;
			std::cout << "          [" << i + 1 << "]: " ;

			// int numOps = 0;

			if (copyGameBoard[i]->TriangleDetected(currentPlayer)) std::cout << "TRIANGLE DETECTED. \n\n" ;
			else std::cout << "triangle not detected. \n\n" ;

			copyGameBoard[i]->Print() ;
		}

		// Graph<int> nextGameBoard = copyGameBoard ;

		// nextGameBoard.Print() ;
	}

	Dynamic1DArray<GameState*>* GetChildren() { return children ; } ;
} ;

#endif