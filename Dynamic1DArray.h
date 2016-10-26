// Contains coding for the creation of a 1D dynamic array.

#ifndef DYNAMIC1DARRAY_H
#define DYNAMIC1DARRAY_H

#include <iostream>
#include "Node.h"

using namespace std;

template<class T> class Dynamic1DArray
{
private:
	// Value of element that does not exist
	T defaultValue;

	int numElements;
	int arraySize;

	// The dynamic array
	T* dynArray;

	// Resize the array up and then return a reference to the new one.
	T* ResizeArrayUp(T* DynArray)
	{
		T* newDynArray = new T[arraySize * 2];

		// Copy elements
		for (int i = 0; i < arraySize * 2; i++)
		{
			if (i < numElements)
				newDynArray[i] = DynArray[i];
			else
				newDynArray[i] = defaultValue;
		}

		arraySize *= 2;

		return newDynArray;
	}

	// Resize the array down and then return a reference to the new one.
	T* ResizeArrayDown(T* DynArray)
	{
		T* newDynArray = new T[arraySize / 2];

		// Copy elements
		for (int i = 0; i < arraySize / 2; i++)
		{
			if (i < numElements)
				newDynArray[i] = DynArray[i];
			else
				newDynArray[i] = defaultValue;
		}

		arraySize /= 2;

		return newDynArray;
	}

public:
	Dynamic1DArray(T DefaultValue)
	{
		defaultValue = DefaultValue;
		numElements = 0;
		arraySize = 1;

		dynArray = new T[arraySize];

		dynArray[0] = defaultValue;
	}

	// Destructor
	~Dynamic1DArray()
	{
		delete[] dynArray;
	}

	// Accessors/Mutators
	int Length() const { return numElements; };

	T GetValue(int index) const { return dynArray[index]; };

	T DefaultValue() const { return defaultValue; };

	T* GetArray() const { return dynArray; };

	// Just like add in C# --> Add element to end of dynamic array
	void Add(T element)
	{
		dynArray[numElements++] = element;

		if (numElements >= arraySize)
			dynArray = ResizeArrayUp(dynArray);
	}

	// Modify an element without inserting anything
	void Modify(int index, T element)
	{
		if (index < numElements && index >= 0)
			dynArray[index] = element;
		else
			cout << "Invalid index." << endl;
	}

	void InsertAt(int index, T element)
	{
		if (index < numElements && index >= 0)
		{
			numElements++;

			if (numElements >= arraySize)
				dynArray = ResizeArrayUp(dynArray);

			for (int i = numElements - 1; i >= index + 1; i--)
				dynArray[i] = dynArray[i - 1];

			dynArray[index] = element;
		}
		else
			cout << "Invalid index." << endl;
	}

	// Remove a certain element at a specific location and then
	// updates the rest of the array
	void RemoveAt(int index)
	{
		if (index < numElements && index >= 0)
		{
			for (int i = index; i < numElements - 1; i++)
				dynArray[i] = dynArray[i + 1];

			dynArray[numElements - 1] = defaultValue;

			numElements--;

			if (numElements * 2 < arraySize)
				dynArray = ResizeArrayDown(dynArray);
		}
		else
			cout << "Invalid index." << endl;
	}

	// Clears the array.
	void Clear()
	{
		delete[] dynArray;

		numElements = 0;
		arraySize = 1;

		dynArray = new T[arraySize];
		dynArray[0] = defaultValue;
	}
};

#endif