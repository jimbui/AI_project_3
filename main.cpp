#include <iostream>
#include "GameState.h"

using namespace std;

// Test for playing two player game
void Play2PlayerGame()
{
	// Starting graph
	Graph<int>* graffiti = new Graph<int>();

	// Generate 6 starting vertices for graph
	graffiti->InsertVertex(1, false);
	graffiti->InsertVertex(2, false);
	graffiti->InsertVertex(3, false);
	graffiti->InsertVertex(4, false);
	graffiti->InsertVertex(5, false);
	graffiti->InsertVertex(6, false);

	// Store graph in game board
	GameState* gameBoard = new GameState(NULL, graffiti);

	// Coin toss --> Player starting game is chosen at random.
	int currentPlayer = 1 + rand() % 2;

	// Start game
	while (true)
	{
		int startVertex;
		int endVertex;
		char ui;

		gameBoard->GameBoard()->Print();

		cout << endl;

		cout << "It's player " << currentPlayer << "'s turn.  Do you want to quit yet?  (y) or (n)" << endl << endl;
		cin >> ui;

		while (ui != 'y' && ui != 'n')
		{
			cout << "I'm sorry.  I didn't get that.  Please enter (y) to quit and (n) to keep playing:  ";
			cin >> ui;
		}

		if (ui == 'y')
			break;

		do
		{
			cout << "Enter starting vertex:  ";
			cin >> startVertex;
			cout << "Enter ending vertex:  ";
			cin >> endVertex;
		} 
		while (!gameBoard->GameBoard()->InsertEdge(startVertex, endVertex, currentPlayer, true));

		// Make player alternate.

		cout << endl;
	}
}

int main(void)
{
	cout << "......................      BOO!!!!!!!" << endl;

	Play2PlayerGame();

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