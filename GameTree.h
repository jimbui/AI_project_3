// Defines the game tree which will be used to determine the best possible move
// for the computer.  Total moves to fill gameboard:  O((15 - CurrentMove)!)

/******************************************************************
*	Depth bound @ each move:
*	Move	Bound	Space		Time		Total Space		Player
*	1		3		O(2730)		O(32760)	O(2730)			P1
*	2		3		O(2184)		O(24024)	O(2184)			P2
*	3		3		O(1716)		O(17160)	O(4446)			P1
*	4		3		O(1320)		O(11880)	O(3504)			P2
*	5		4		O(7920)		O(55440)	O(12366)		P1
*	6		4		O(5040)		O(30240)	O(8544)			P2
*	7		5		O(15120)	...
******************************************************************/

#ifndef GAMETREE_H
#define GAMETREE_H

#include "GameState.h"

class GameTree
{
private:
	// Root of tree
	GameState* root;

	// The maximum depth of this tree, in levels.  This will ensure limited runtime.
	// int maxDepth;
	int numElements;

	void ClearRecursive(GameState* gsIterator)
	{
		for (int i = 0; i < gsIterator->GetChildren()->Length(); i++)
			ClearRecursive(gsIterator->GetChildren()->GetValue(i));

		delete gsIterator;
	}

	/*void DFSMin(GameState* gsIterator, int maximum)
	{
		for (int i = 0; i < gsIterator->GetChildren()->Length(); i++)
			DFSMax(gsIterator, maximum);
	}*/

	// Minimax algorithm used to determine best move.  Note that it is only useful later in the game.
	int Minimax(GameState* gsIterator, bool maximizingPlayer, int startingPlayer, int currentPlayer)
	{
		if (gsIterator->GetChildren()->Length() == 0)  // Base case.  Get utility of node.
		{
			gsIterator->SetUtility(100, 100, 10, startingPlayer, currentPlayer);
			return gsIterator->Utility();
		}

		if (maximizingPlayer)  // Maximizing player.  Propagate utility function upward.
		{
			int bestValue = -100000;

			for (int i = 0; i < gsIterator->GetChildren()->Length(); i++)
			{
				int v = Minimax(gsIterator->GetChildren()->GetValue(i), false, startingPlayer, (currentPlayer == 2 ? 1 : 2));
				bestValue = (bestValue > v ? bestValue : v);
			}

			gsIterator->SetUtility(bestValue);
			return bestValue;
		}
		else  // Minimizing player.  Propagate utility function upward.
		{
			int bestValue = 100000;

			for (int i = 0; i < gsIterator->GetChildren()->Length(); i++)
			{
				int v = Minimax(gsIterator->GetChildren()->GetValue(i), true, startingPlayer, (currentPlayer == 2 ? 1 : 2));
				bestValue = (bestValue < v ? bestValue : v);
			}

			gsIterator->SetUtility(bestValue);
			return bestValue;
		}
	}

public:
	GameTree(GameState* Root  /*, int MaxDepth*/)
	{
		root = Root;
		// maxDepth = MaxDepth;

		numElements = 1;
	}

	// Gets the root of this game tree.
	GameState* Root() { return root; };

	// Builds the tree until a certain depth is reached (see top of document)
	void BuildTree(int currentMove, int maxLevel, int player, bool showOutput)
	{
		// int currentDepth = 0;
		if (showOutput)
			cout << root << ":  Depth = 0; P" << player << "; U(n) = " << root->Utility() << endl;

		queue<int> depthQueue;
		queue<int> currentMoveQueue;
		queue<int> currentPlayerQueue;
		queue<GameState*> nextState;

		currentPlayerQueue.push(player);
		depthQueue.push(0);
		currentMoveQueue.push(currentMove);
		nextState.push(root);

		// Standard BFS
		while (depthQueue.size() > 0 && nextState.size() > 0 && currentPlayerQueue.size() > 0)
		{
			GameState* gs = nextState.front();
			int currentDepth = depthQueue.front();
			int currentCurrentMove = currentMoveQueue.front();
			int currentPlayer = currentPlayerQueue.front();

			nextState.pop();
			depthQueue.pop();
			currentMoveQueue.pop();
			currentPlayerQueue.pop();

			if (currentDepth < maxLevel)  // Build tree if maximum desired level is not reached.
			{
				gs->Expand(player, currentPlayer, 15 - currentCurrentMove, false, currentDepth + 1);  // True expansion occurs here.

				for (int i = 0; i < gs->GetChildren()->Length(); i++)
				{
					GameState* next_gs = gs->GetChildren()->GetValue(i);

					if (showOutput)
						cout << next_gs << ":  Depth = " << currentDepth + 1 << "; P" << (currentPlayer == 1 ? 2 : 1) << "; U(n) = " << gs->Utility() << endl;

					nextState.push(next_gs);
					depthQueue.push(currentDepth + 1);
					currentMoveQueue.push(currentCurrentMove + 1);
					currentPlayerQueue.push((currentPlayer == 1 ? 2 : 1));
				}
			}
			else  // Calculate the utility function of each node.
			{
				// Stopped here!!!!
				// gs->SetUtility(1, 1, player, currentPlayer);
			}
		}
	}

	~GameTree()
	{
		// delete root->GetChildren();
		// delete root;
		Clear();

		// delete root;
	}

	// Minimax needed here

	// Returns a copy of the gamestate containing the best move.  Uses DFS to determine this node.
	GameState* BestMove(int currentPlayer)
	{
		// TODO:  Design Alpha-Beta pruning algorithm in order to find the best possible move.  This function
		// will return an opcode specifying what move to make.
		
		if (root->GetChildren()->Length() > 0)
		{
			/*if (root->GetChildren()->Length() > 1)
				return root->GetChildren()->GetValue(rand() % (root->GetChildren()->Length()))->CopyWithoutLinks();
			else
				return root->GetChildren()->GetValue(0)->CopyWithoutLinks();*/
			
			// Recursively adding letters to 'minimax'.
			Minimax(root, true, currentPlayer, currentPlayer);

			// Return move with same heuristic as child nodes.
			for (int i = 0; i < root->GetChildren()->Length(); i++)
			{
				GameState* child = root->GetChildren()->GetValue(i);

				if (child->Utility() == root->Utility())
					return child->CopyWithoutLinks();
			}
		}
		else
			return NULL;
	}

	// Performs a breadth-first print operation. (Debug only)
	void BFPrint()
	{
		queue<GameState*> gsq;

		cout << "0x" << root << ":  Depth = " << root->Depth() << "; h(n) = " << root->Utility() << endl;
		
		gsq.push(root);

		while (gsq.size() > 0)
		{
			GameState* cur = gsq.front();
			gsq.pop();

			for (int i = 0; i < cur->GetChildren()->Length(); i++)
			{
				cout << "0x" << cur->GetChildren()->GetValue(i) << ":  Depth = " << cur->GetChildren()->GetValue(i)->Depth() 
					<< "; h(n) = " << cur->GetChildren()->GetValue(i)->Utility() << endl;

				gsq.push(cur->GetChildren()->GetValue(i));
			}
		}
	}

	// Clears the entire game tree using DFS and attempts to free memory.
	void Clear()
	{
		ClearRecursive(root);

		// delete root;

		//root = NULL;
	}
};

#endif