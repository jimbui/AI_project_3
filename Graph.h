// Implements a graph using adjacency matrix representation

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
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

public:

	Dynamic1DArray<T>* vertices;
	Dynamic2DArray<int>* edges;
	Graph()
	{
		// vertexCount = 0;
		// arraySize = sz;

		// vertices = new int[arraySize];
		vertices = new Dynamic1DArray<T>(-1);
		edges = new Dynamic2DArray<int>(-1, true);

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

	void ForwardIDFS(int v, int limit)
	{
		cout << "Forward IDFS:" << endl << endl;

		bool* visited = new bool[vertices->Length()];

		for (int i = 0; i < vertices->Length(); i++)
			visited[i] = false;

		DFSRecursive(v, &visited);
	}

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

	// Checks the entire graph for triangles.

	bool TriangleDetection()
	{
		int v = 0 ;
		// Get all vertices and perform depth-limited BFS on each.
		for (int i = 0; i < vertices->Length(); i++)
		{
			// Do for both players' edges.
			for (int j = 1; j <= 2; j++)
			{
				int* visitedDepth = new int[vertices->Length()];
				int currentDepth = 0;

				for (int k = 0; k < vertices->Length(); k++)
					visitedDepth[k] = 0;

				int start = i;

				// Print vertex and mark as visited.
				cout << "Vertex with value " << v << " visited.  Depth = " << currentDepth << endl;
				visitedDepth[start] = currentDepth;

				// Enqueue starting vertex index + depth
				queue<int> q;
				q.push(start);

				// BFS by index...
				while (q.size() > 0)
				{
					int v1Index = q.front();
					q.pop();

					for (int k = 0; k < vertices->Length(); k++)
					{
						if (vertices->GetValue(k) != -1 /*&& !visited[i]*/)
						{
							// cout << "Vertex with value " << vertices->GetValue(i) << " visited." << endl;
							// visited[i] = true;

							q.push(vertices->GetValue(k));
						}
					}
				}
			}
		}
	}

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
							cout << GetFormatting(to_string(vertices->GetValue(j - 2)), 5).c_str() << vertices->GetValue(j - 2);
						if (i == 1)
							cout << "_____";  // 5 underscores
					}
					if (i > 1)
					{
						if (j == 0)
							cout << "    " << GetFormatting(to_string(vertices->GetValue(i - 2)), 5).c_str() << vertices->GetValue(i - 2);
						if (j == 1)
							cout << "    |";  // 1 right boundary
					}

					if (j > 1 && i > 1)  // Print values
						cout << GetFormatting((edges->GetValue(i - 2, j - 2) != -1 ? to_string(edges->GetValue(i - 2, j - 2)) : "-"), 5).c_str() 
							<< (edges->GetValue(i - 2, j - 2) == -1 ? "-" : to_string(edges->GetValue(i - 2, j - 2)));
				}
			}

			// End line
			cout << endl ;
		}
		
		cout << endl ;
	}
};

#endif