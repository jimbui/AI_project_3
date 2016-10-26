#include <iostream>
#include "GameState.h"
#include "Node.h"

using namespace std;

int main(void)
{
	cout << "......................      BOO!!!!!!!" << endl;

	// Create test graph...
	Graph<int>* graffiti = new Graph<int>();

	graffiti->Print();
	cout << endl;

	graffiti->InsertVertex(20, false);
	graffiti->InsertVertex(30, false);

	graffiti->Print();
	cout << endl;

	graffiti->InsertEdge(20, 30, 5, false);

	graffiti->Print();
	cout << endl;

	// Create test game state
	/*GameState* gs = new GameState(NULL, graffiti);

	gs->GetChildren()->Add(gs);
	gs->GetChildren()->GetValue(0)->GetChildren()->Add(gs);

	cout << "Number of children:  " << gs->GetChildren()->Length() << endl;*/

	cin.get();

	return 0;
}