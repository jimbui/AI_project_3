// Defines the game tree which will be used to determine the best possible move
// for the computer.  Total moves to fill gameboard:  O((15 - CurrentMove)!)

#ifndef GAMETREE_H
#define GAMETREE_H

#include "GameState.h"

class GameTree
{
private:
	// Root of tree
	GameState* root;

	// The maximum depth of this tree, in levels.  This will ensure limited runtime.
	int maxDepth;
	int numElements;

public:
	GameTree(GameState* Root, int MaxDepth)
	{
		root = Root;
		maxDepth = MaxDepth;

		numElements = 1;
	}

	~GameTree()
	{
		delete root->GetChildren();
		delete root;
	}

	// Alpha-Beta Pruning needed here...
	int BestMove()
	{
		// TODO:  Design Alpha-Beta pruning algorithm in order to find the best possible move.  This function
		// will return an opcode specifying what move to make.

		return 0;
	}
};

#endif