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
	

	Dynamic1DArray<GameState*>* children ; // all the children of this board.  assume max of 15 , not too sure.

	// Add flags as necessary...

	int GetUtility(Graph<int>* GameBoard) // this is the heuristic function.
	{
		int utility = 0;

		// TODO:  Add method to determine the correct utility function.

		return utility;
	}

	public:

	GameState(GameState* Parent, Graph<int>* GameBoard)
	{
		parent = Parent ;
		currentGameBoard = GameBoard ;
		children = new Dynamic1DArray<GameState*>(NULL) ;
		utilityFcn = GetUtility(currentGameBoard) ;
	}

	~GameState()
	{
		delete currentGameBoard ;
	}

	// Accessors/Mutators
	Graph<int>* GameBoard() { return currentGameBoard; };

	void Expand()
	{
		// TODO:  Make child nodes according to legal moves.  Since directed graph from previous project is used,
		// be sure to insert 2 edges:  1 going to and one coming from.
		Graph<int> copyGameBoard ;
		std::cout << "[+] POSSIBLE GAME BOARDS: \n\n" ;

		copyGameBoard.InsertVertex(1, false) ;
		copyGameBoard.InsertVertex(2, false) ;
		copyGameBoard.InsertVertex(3, false) ;
		copyGameBoard.InsertVertex(4, false) ;
		copyGameBoard.InsertVertex(5, false) ;
		copyGameBoard.InsertVertex(6, false) ;

		for (int i = 0 ; i < currentGameBoard->vertices->Length() ; i++)
		{
			for (int j = 0 ; j < currentGameBoard->vertices->Length() ; j++)
			{
				copyGameBoard.InsertEdge(i + 1 , j + 1, currentGameBoard->edges->GetValue(i , j) , false) ;
				// std::cout << currentGameBoard->edges->GetValue(i , j) << " \n" ;
			}
		}

		copyGameBoard.Print() ;
	}

	Dynamic1DArray<GameState*>* GetChildren() { return children ; } ;
} ;

#endif