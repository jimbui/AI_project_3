// Contains coding for the creation of a 2D dynamic array.

#ifndef DYNAMIC2DARRAY_H
#define DYNAMIC2DARRAY_H

#include <iostream>

using namespace std;

template<class T> class Dynamic2DArray
{
private:
	// Value of element that does not exist
	T defaultValue;

	int numElementsX;
	int numElementsY;

	int arraySizeX;
	int arraySizeY;

	bool isSquare;

	// The dynamic array ... [row # (Y), column # (X)]
	T** dynArray;

	// Resize the array up along the x-axis and then return a reference to the new one.
	T** ResizeArrayUpX(T** DynArray)
	{
		T** newDynArray = new T*[arraySizeY];

		// Copy elements
		for (int i = 0; i < arraySizeY; i++)
		{
			newDynArray[i] = new T[arraySizeX * 2];

			for (int j = 0; j < arraySizeX * 2; j++)
			{
				if (j < arraySizeX)
					newDynArray[i][j] = DynArray[i][j];
				else
					newDynArray[i][j] = defaultValue;
			}
		}

		arraySizeX *= 2;

		return newDynArray;
	}

	// Resize the array up along the y-axis and then return a reference to the new one.
	T** ResizeArrayUpY(T** DynArray)
	{
		T** newDynArray = new T*[arraySizeY * 2];

		// Copy elements
		for (int i = 0; i < arraySizeY * 2; i++)
		{
			newDynArray[i] = new T[arraySizeX];

			for (int j = 0; j < arraySizeX; j++)
			{
				if (i < arraySizeY)
					newDynArray[i][j] = DynArray[i][j];
				else
					newDynArray[i][j] = defaultValue;
			}
		}

		arraySizeY *= 2;

		return newDynArray;
	}

public:
	Dynamic2DArray(T DefaultValue, bool IsSquare)
	{
		defaultValue = DefaultValue;
		isSquare = IsSquare;

		numElementsX = 0;
		numElementsY = 0;

		arraySizeX = 1;
		arraySizeY = 1;

		dynArray = new T*[arraySizeY];

		for (int i = 0; i < arraySizeY; i++)
			dynArray[i] = new T[arraySizeX];

		dynArray[0][0] = defaultValue;
	}

	// Destructor
	~Dynamic2DArray()
	{
		delete[] dynArray;
	}

	// Accessors/Mutators
	int Length() const { return numElementsX * numElementsY; };

	int Length(int dimension)
	{ 
		if (dimension == 1)
			return numElementsX;
		else if (dimension == 0)
			return numElementsY;
		else
			cout << "Invalid dimension." << endl;
	}

	int Capacity(int dimension)
	{
		if (dimension == 1)
			return arraySizeX;
		else if (dimension == 0)
			return arraySizeY;
		else
			cout << "Invalid dimension." << endl;
	}

	T GetValue(int Xindex, int Yindex) const { return dynArray[Yindex][Xindex]; };

	T DefaultValue() const { return defaultValue; };

	T** GetArray() const { return dynArray; };

	// Just like add in C# --> Add element to end of dynamic array
	/*void Add(T element)
	{
		dynArray[numElements++] = element;

		if (numElements >= arraySize)
			dynArray = ResizeArrayUp(dynArray);
	}*/

	// Modify an element without inserting anything
	/*void Modify(int index, T element)
	{
		if (index < numElements && index >= 0)
			dynArray[index] = element;
		else
			cout << "Invalid index." << endl;
	}*/

	void ModifyOrInsertAt(int Xindex, int Yindex, T element)
	{
		if (Xindex < arraySizeX && Xindex >= 0 && Yindex < arraySizeY && Yindex >= 0)
		{
			dynArray[Yindex][Xindex] = element;

			if (numElementsX < Xindex + 1)
				numElementsX = Xindex + 1;
			if (numElementsY < Yindex + 1)
				numElementsY = Yindex + 1;

			if (numElementsX >= arraySizeX || (isSquare && numElementsY >= arraySizeX))
				dynArray = ResizeArrayUpX(dynArray);
			if (numElementsY >= arraySizeY || (isSquare && numElementsX >= arraySizeY))
				dynArray = ResizeArrayUpY(dynArray);
		}
		else
			cout << "Invalid indeces." << endl;
	}

	// Remove a certain element at a specific location and then
	// updates the rest of the array
	void RemoveAt(int Xindex, int Yindex)
	{
		if (Xindex < arraySizeX && Xindex >= 0 && Yindex < arraySizeY && Yindex >= 0)
		{
			dynArray[Yindex][Xindex] = defaultValue;
		}
		else
			cout << "Invalid indeces." << endl;
	}

	// Clears the array.
	void Clear()
	{
		delete[] dynArray;

		numElementsX = 0;
		numElementsY = 0;

		arraySizeX = 1;
		arraySizeY = 1;

		dynArray = new T*[arraySizeY];

		for (int i = 0; i < arraySizeY; i++)
			dynArray[i] = new T[arraySizeX];

		dynArray[0, 0] = defaultValue;
	}
};

#endif