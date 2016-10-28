// Implements a graph using adjacency matrix representation

/*

	FOR JOHN:

		bool TriangleDetected(int currentPlayer) was implemented and placed in the main().  not fully tested yet , 
		but promising results.  on line 313.

*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <fstream>
#include <math.h>
#include "Dynamic2DArray.h"
#include "Dynamic1DArray.h"

template<class T> class Graph
{
private:

	/*int arraySize;
	int vertexCount;*/

	// Helper Methods ----------------------------------------------

	// Gets the field width of an integer value.
	int GetFieldWidth(string stringValue)
	{
		return stringValue.length();  // (intValue > 1 ? (int)log10(intValue) + 1 : (intValue > -1 ? 1 : (int)log10(abs(intValue)) + 2));
	}

	// Gets a string of spaces from a desired field with and integer input
	string GetFormatting(string stringValue, int fieldWidth)
	{
		int intWidth = GetFieldWidth(stringValue);
		string spaceString = "";

		for (int i = 0; i < fieldWidth - intWidth; i++)
			spaceString += " ";

		return spaceString;
	}

	// Resizes all of the arrays in the directed graph
	/*void ResizeArrays()
	{
		int doubleArraySize = arraySize * 2;

		int* tempVertices = new int[doubleArraySize];
		int** tempEdges = new int*[doubleArraySize];

		for (int i = 0; i < doubleArraySize; i++)
			tempEdges[i] = new int[doubleArraySize];

		for (int i = 0; i < doubleArraySize; i++)
		{
			if (i < arraySize)
				tempVertices[i] = vertices[i];
			else
				tempVertices[i] = -1;

			for (int j = 0; j < doubleArraySize; j++)
			{
				if (i < arraySize && j < arraySize)
					tempEdges[i][j] = edges[i][j];
				else
					tempEdges[i][j] = -1;
			}
		}

		delete[] edges;
		delete vertices;

		edges = tempEdges;
		vertices = tempVertices;
		arraySize = doubleArraySize;
	}*/

	// Gets the index of a vertex value.  -1 if vertex does not exist.
	int GetVertexIndex(int v)
	{
		for (int i = 0; i < vertices->Length(); i++)
			if (vertices->GetValue(i) == v)
				return i;

		return -1;
	}

	void DFSRecursive(int v, bool** visiteded)
	{
		int v1Index = GetVertexIndex(v);

		if (v1Index == -1)
		{
			cout << "Starting vertex does not exist." << endl;
			return;
		}

		// Print vertex and mark as visited.
		cout << "Vertex with value " << v << " visited." << endl;
		(*visiteded)[v1Index] = true;

		// Find next edge
		for (int i = 0; i < vertices->Length(); i++)
		{
			// int v2Index = GetVertexIndex(i);

			// If v2 exists and has not been visited, go immediately to that vertex if an edge exists.
			if (vertices->GetValue(i) != -1 && !(*visiteded)[i] && edges->GetValue(v1Index, i) != -1)
				DFSRecursive(vertices->GetValue(i), visiteded);
		}
	}

	bool ForwardIDFSRecursive(int start, int startingLimit, int v, int playerNum, int depthRemaining, int** depthFlag)
	{
		int v1Index = GetVertexIndex(v);

		// Print vertex and mark as visited.
		cout << "Vertex with value " << v << " visited.  Depth Remaining = " << depthRemaining << endl;
		(*depthFlag)[v1Index] = depthRemaining;

		// Find next edge
		if (depthRemaining > 0)
		{
			for (int i = 0; i < vertices->Length(); i++)
			{
				// int v2Index = GetVertexIndex(i);
				if (vertices->GetValue(i) == start && depthRemaining - 1 == 0)
					return true;

				// If v2 exists and has not been visited, go immediately to that vertex if an edge exists.
				if (vertices->GetValue(i) != -1 && (*depthFlag)[i] != depthRemaining + 1 && edges->GetValue(v1Index, i) == playerNum)
					ForwardIDFSRecursive(start, startingLimit, vertices->GetValue(i), playerNum, depthRemaining - 1, depthFlag);
			}
		}
	}

public:

	Dynamic1DArray<T>* vertices;
	Dynamic2DArray<int>* edges;

	Graph()
	{
		// vertexCount = 0;
		// arraySize = sz;

		// vertices = new int[arraySize];
		vertices = new Dynamic1DArray<T>(-1, 7);
		edges = new Dynamic2DArray<int>(-1, true, 7, 7);

		/*edges = new int*[arraySize];

		for (int i = 0; i < arraySize; i++)
			edges[i] = new int[arraySize];*/

		// Set all edge weights to -1 and vertex values to -1.  This is flag indicating that edge/vertex does not exist.
		/*for (int i = 0; i < arraySize; i++)
		{
			vertices[i] = -1;

			for (int j = 0; j < arraySize; j++)
				edges[i][j] = -1;
		}*/
	}

	~Graph()
	{
		delete vertices;
		delete edges;
	}

	// Deep copy
	Graph* Copy()
	{
		Graph* copiedGraph = new Graph();

		copiedGraph->vertices = vertices->Copy();
		copiedGraph->edges = edges->Copy();

		return copiedGraph;
	}

	// Accessors ---------------------------------------------------
	// int ArraySize() const { return arraySize; };
	int VertexCount() const { return vertices->Length(); };

	// Mutators ----------------------------------------------------
	// Create Graph from Text File
	void BuildGraph(string FileName)
	{
		string line;
		fstream myfile(FileName);

		if (myfile.is_open())
		{
			// Building array of vertices and edges
			int input, currentPosition = 0;
			int v1, v2;

			while (myfile >> input)
			{
				switch (currentPosition)
				{
				case 0:  // Insert v1 if possible
					v1 = input;
					InsertVertex(v1, false);

					break;

				case 1:  // Insert v2 if possible
					v2 = input;
					InsertVertex(v2, false);

					break;

				default:  // Insert edge if v1 && v2 are not equal to -1.
					InsertEdge(v1, v2, input, false);

					break;
				}

				currentPosition++;

				if (currentPosition > 2)
					currentPosition = 0;
			}

			myfile.close();
			cout << "Graph Built." << endl;
		}
		else cout << "Unable to open file";
	}

	// Build default graph for game.
	void BuildGameGraph()
	{
		for (int i = 1; i <= 6; i++)
			InsertVertex(i, false);
	}

	// Debug-Only Accessors ----------------------------------------------

	// Note that these methods were implemented in order to test graph
	// traversal.  The methods themselves are not actually used in 
	// Dijkstra's algorithm

	// Performs standard DFS on Graph
	void DFS(int v)
	{
		cout << "DFS:" << endl << endl;

		bool* visited = new bool[vertices->Length()];

		for (int i = 0; i < vertices->Length(); i++)
			visited[i] = false;

		DFSRecursive(v, &visited);
	}

	// Returns whether there is a triangle anywhere in the graph.

	/*

	bool TriangleDetection(int v, int playerNum)
	{
		cout << "Forward IDFS:" << endl << endl;

		int* depthFlag = new int[vertices->Length()];

		for (int i = 0; i < vertices->Length(); i++)
			depthFlag[i] = -2;

		return ForwardIDFSRecursive(v, 3, v, playerNum, 3, &depthFlag);
	}

	*/

	// Performs standard BFS on Graph
	void BFS(int v)
	{
		cout << "BFS:" << endl << endl;

		int* visited = new int[vertices->Length()];
		int currentDepth = 0;

		for (int i = 0; i < vertices->Length(); i++)
			visited[i] = 0;

		int start = GetVertexIndex(v);

		if (start == -1)
		{
			cout << "Starting vertex does not exist." << endl;
			return;
		}

		// Print vertex and mark as visited.
		cout << "Vertex with value " << v << " visited.  Current Depth = " << currentDepth << endl;
		visited[start] = 1;

		// Enqueue starting vertex index
		queue<int> q;

		q.push(start);

		while (q.size() > 0)
		{
			int v1Index = q.front();
			q.pop();

			for (int i = 0; i < vertices->Length(); i++)
			{
				if (vertices->GetValue(i) != -1 && visited[i] == 0 && edges->GetValue(v1Index, i) != -1)
				{
					cout << "Vertex with value " << vertices->GetValue(i) << " visited.  Current Depth = " << currentDepth << endl;
					visited[i] = 1;

					q.push(vertices->GetValue(i));
				}
			}
		}
	}

	bool TriangleDetected(int currentPlayer) // black magic.  uncomment to debug.
	{
		int k = 1 ;
		// std::cout << " \n" ;

		// int opCount = 0;

		for (int i = 0 ; i < vertices->Length() ; i++)
		{
			for (int j = 0 ; j < vertices->Length() ; j++)
			{
				if (i < j) // iterate each edge only once.
				{
					// std::cout << "looking at i: " << i + 1 << " and j: " << j + 1 << " , run# " << k << " , value: " << edges->GetValue(i , j) <<" \n" ;
					k++ ;

					int checked_array[6][6] = {0} ; // the anti-repeat device.

					if (edges->GetValue(i , j) == currentPlayer && i < j) // every first tier node that belongs to player.
					{
						checked_array[i][j] = 1 ;
						checked_array[j][i] = 1 ;

						// std::cout << "[+]    edge " << i + 1 << "->" << j + 1 << " belongs to player " << currentPlayer << ". \n" ;

						for (int k = 0 ; k < vertices->Length() ; k++)
						{
							if (edges->GetValue(j , k) == currentPlayer && checked_array[j][k] != 1) // every second tier node that belongs to player.
							{
								checked_array[j][k] = 1 ;
								checked_array[k][j] = 1 ;

								// std::cout << "    [+]    edge " << j + 1 << "->" << k + 1 << " belongs to player " << currentPlayer << ". \n" ;

								for (int g = 0 ; g < vertices->Length() ; g++)
								{
									// opCount++;

									if (edges->GetValue(k , g) == currentPlayer && (g == i || k == i) && checked_array[k][g] != 1) // every third tier node that belongs to player and is triangle.
									{
										// std::cout << "        [+]    edge " << k + 1 << "->" << g + 1 << " belongs to player " << currentPlayer << ". \n" ;
										return true ;
									}
								}
							}
						}
					}
				}
			}
		}

		return false ;
	}

	/*

	bool TriangleDetection()
	{
		// int v = 0 ;
		// Get all vertices and perform depth-limited BFS on each.
		for (int i = 0; i < vertices->Length(); i++)
		{
			// Do for both players' edges.
			for (int j = 1; j <= 2; j++)
			{
				if (TriangleDetection(vertices->GetValue(i), j))
					return true;
			}
		}

		return false;
	}

	*/

	// End Debug-Only Accessors ------------------------------------------

	// Dijkstra's Algorithm on adjacency matrix --------------------------------------------
	// Prints the shortest distance between 2 points if a path exists.
	
	// [See assignment 1]

	// -------------------------------------------------------------------------------------

	// Mutators ----------------------------------------------------
	// Insert vertex of value v

	void InsertVertex(int v, bool showOutput)
	{
		// Check to see if vertex being added exists already or is invalid
		if (v < 0)
		{
			if (showOutput)
				cout << "Invalid value.  Vertex not added." << endl;
		}
		else
		{
			for (int i = 0; i < vertices->Length(); i++)
			{
				if (vertices->GetValue(i) == v)
				{
					if (showOutput)
						cout << "Vertex already exists.  Vertex not added." << endl;
					return;
				}
			}

			if (showOutput)
				cout << "Vertex of value " << v << " successfully added." << endl;

			edges->ModifyOrInsertAt(vertices->Length(), vertices->Length(), edges->DefaultValue());
			vertices->Add(v) ; // adds vertex v to end of a dynamic array. 

			/*if (vertexCount == arraySize)
				ResizeArrays();*/
		}
	}

	// Insert edge between v1 and v2.  Returns whether successful.
	bool InsertEdge(int v1, int v2, int edgeWeight, bool showOutput) 
	{
		if(v1 == v2) // cannot insert edge between the same vertices.
		{
			return false ;
		}

		else
		{
			// Try to insert edge between existing vertices
			int vertex1Index = -1, vertex2Index = -1;

			for (int i = 0; i < vertices->Length(); i++)
			{
				if (vertices->GetValue(i) == v1)
					vertex1Index = i;
				if (vertices->GetValue(i) == v2)
					vertex2Index = i;
			}

			if (vertex1Index == -1 || vertex2Index == -1)
			{
				if (showOutput)
					cout << "    Either one or both of the vertices do not exist. \n" << endl;

				return false;
			}
			else
			{
				if (edgeWeight <= 0)
				{
					if (showOutput)
						cout << "Invalid edge weight." << endl;

					return false;
				}
				else
				{
					if (edges->GetValue(vertex1Index, vertex2Index) == edges->DefaultValue())
					{
						edges->ModifyOrInsertAt(vertex1Index, vertex2Index, edgeWeight); // edges[vertex1Index][vertex2Index] = edgeWeight;
						edges->ModifyOrInsertAt(vertex2Index, vertex1Index, edgeWeight); // since this graph is undirected , this adds the other edge. 
						if (showOutput)
							cout << "    Edge from [" << vertices->GetValue(vertex1Index) << "] --(" << edgeWeight << ")--> ["
							<< vertices->GetValue(vertex2Index) << "] added successfully. \n" << endl;
						if (showOutput)
							cout << "    Edge from [" << vertices->GetValue(vertex2Index) << "] --(" << edgeWeight << ")--> ["
							<< vertices->GetValue(vertex1Index) << "] added successfully. \n" << endl;

						return true;
					}
					else
					{
						if (showOutput)
							cout << "    Edge already exists. \n" << endl;

						return false;
					}
				}
			}
		}
	}

	// Added to reduce memory leakage.
	bool RemoveEdge(int v1, int v2, bool showOutput)
	{
		if (v1 == v2) // cannot remove edge between the same vertices.
		{
			return false;
		}
		else
		{
			// Try to delete edge between existing vertices
			int vertex1Index = -1, vertex2Index = -1;

			for (int i = 0; i < vertices->Length(); i++)
			{
				if (vertices->GetValue(i) == v1)
					vertex1Index = i;
				if (vertices->GetValue(i) == v2)
					vertex2Index = i;
			}

			if (vertex1Index == -1 || vertex2Index == -1)
			{
				if (showOutput)
					cout << "    Either one or both of the vertices do not exist. \n" << endl;

				return false;
			}
			else
			{
				if (edges->GetValue(vertex1Index, vertex2Index) != edges->DefaultValue())
				{
					if (showOutput)
						cout << "    Edge from [" << vertices->GetValue(vertex1Index) << "] --(" << edges->GetValue(vertex1Index, vertex2Index) << ")--> ["
						<< vertices->GetValue(vertex2Index) << "] deleted successfully. \n" << endl;
					if (showOutput)
						cout << "    Edge from [" << vertices->GetValue(vertex2Index) << "] --(" << edges->GetValue(vertex2Index, vertex1Index) << ")--> ["
						<< vertices->GetValue(vertex1Index) << "] deleted successfully. \n" << endl;

					edges->ModifyOrInsertAt(vertex1Index, vertex2Index, edges->DefaultValue()); // edges[vertex1Index][vertex2Index] = edgeWeight;
					edges->ModifyOrInsertAt(vertex2Index, vertex1Index, edges->DefaultValue()); // since this graph is undirected , this adds the other edge.

					return true;
				}
				else
				{
					if (showOutput)
						cout << "    Edge does not exist. \n" << endl;

					return false;
				}
			}
		}
	}

	// Display -----------------------------------------------------
	void Print()
	{
		//cout << "    Graph Vertices: \n" << endl;

		//if (vertices->Length() == 0)
		//{
		//	cout << "        Graph is empty." << endl;
		//	// return;
		//}

		//for (int i = 0; i < vertices->Length(); i++)
		//	cout << "        Vertex[" << i << "] = " << vertices->GetValue(i) << endl;

		//cout << endl;

		cout << "    Graph Edges: \n" << endl;


		for (int i = 0; i < vertices->Length() + 2; i++)
		{
			for (int j = 0; j < vertices->Length() + 2; j++)
			{
				// 0,0 --> 1,1 are blank spaces
				if (i <= 1 && j <= 1)
				{
					if ((i == 0 && j == 0) || (i == 1 && j == 1))
						cout << "     ";  // 5 spaces
					else if (i == 0 && j == 1)
						cout << "       To";
					else
						cout << "    From ";
				}
				else
				{
					if (j > 1)  // Print Underscores
					{
						if (i == 0)
						{
							int val = vertices->GetValue(j - 2);
							stringstream ss;
							ss << val;
							string sting = ss.str();

							cout << GetFormatting(sting, 5).c_str() << val;
						}
						if (i == 1)
							cout << "_____";  // 5 underscores
					}
					if (i > 1)
					{
						if (j == 0)
						{
							int val = vertices->GetValue(i - 2);
							stringstream ss;
							ss << val;
							string sting = ss.str();

							cout << "    " << GetFormatting(sting, 5).c_str() << val;
						}
						if (j == 1)
							cout << "    |";  // 1 right boundary
					}

					if (j > 1 && i > 1)  // Print values
					{
						int val = edges->GetValue(i - 2, j - 2);
						stringstream ss;
						ss << val;
						string sting = ss.str();

						cout << GetFormatting((val != -1 ? sting : "-"), 5).c_str() << (val == -1 ? "-" : sting);
					}
				}
			}

			// End line
			cout << endl;
		}

		cout << endl;
	}
};

#endif