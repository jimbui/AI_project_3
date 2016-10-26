// This is a node containing the current game state and pointers to "next" nodes.  State space
// = O(((5 + 4 + 3 + 2 + 1) - CurrentMove)!) = O((15 - CurrentMove)!)

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include "Graph.h"

class GameState
{
private:
	GameState* parent;

	Graph<int>* currentGameBoard;
	int utilityFcn;
	

	Dynamic1DArray<GameState*>* children;

	// Add flags as necessary...

	// Utility function
	int GetUtility(Graph<int>* GameBoard)
	{
		int utility = 0;

		// TODO:  Add method to determine the correct utility function.

		return utility;
	}

public:
	GameState(GameState* Parent, Graph<int>* GameBoard)
	{
		parent = Parent;
		currentGameBoard = GameBoard;
		children = new Dynamic1DArray<GameState*>(NULL);

		utilityFcn = GetUtility(currentGameBoard);
	}

	~GameState()
	{
		delete currentGameBoard;
	}

	// Expand() function
	void Expand()
	{
		// TODO:  Make child nodes according to legal moves.  Since directed graph from previous project is used,
		// be sure to insert 2 edges:  1 going to and one coming from.
	}

	Dynamic1DArray<GameState*>* GetChildren() { return children; };
};

#endif