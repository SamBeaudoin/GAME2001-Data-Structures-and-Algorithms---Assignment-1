#pragma once
#include <cassert>
#include "Array.h"

template<class T>
class OrderedArray: public Array
{
public:
	// Public Variables
	bool m_dupesAllowed;	// Whether or not copies of data are allowed in the array

	// Constructor 

	OrderedArray(int size), m_dupesAllowed = false : Array(size) { std::cout << "Ordered Constructor." << std::endl; };

	// Gets and Sets
	int GetDupesAllowed()
	{
		return m_dupesAllowed;
	}
	int SetDupesAllowed(bool state)
	{
		m_dupesAllowed = state;
	}

	// Insertion -- Big-O = O(N)
	void push(T val)
	{
		assert(m_array != nullptr);

		if ((return binarySearch(val, 0, m_numElements - 1) != -1) && !GetDupesAllowed())	// Duplicate Check
		{
			std::cout << std::endl << std::endl "Duplicate data found! Unable to enter value: " << val << std::endl << std::endl;
			return;
		}

		if (m_numElements >= m_maxSize)
		{
			Expand();
		}

		int i, k;	// i - Index to be inserted. k - Used for shifting purposes
		// Step 1: Find the index to insert val
		for (i = 0; i < m_numElements; i++)
		{
			if (m_array[i] > val)
			{
				break;
			}
		}

		// Step 2: Shift everything to the right of the index(i) forward by one. Work backwards
		for (k = m_numElements; k > i; k--)
		{
			m_array[k] = m_array[k - 1];
		}

		// Step 3: Insert val into the array at index
		m_array[i] = val;

		m_numElements++;

		// return i;
	}

	// Searching
	// Binary Search
	int search(T val)
	{
		// Call to binary search recursive function
		// Binary Search: searchKey, initial lowerBound, initial upperBound
		return binarySearch(val, 0, m_numElements - 1);
	}

private:
	// Private functions
	// Recursive Binary Search
	int binarySearch(T val, int lowerBound, int upperBound)
	{
		assert(m_array != nullptr);
		assert(lowerBound >= 0);
		assert(upperBound < m_numElements);

		// Bitwise divide by 2
		int current = (lowerBound + upperBound) >> 1;

		// Check 1 "Base case": Did we find the searchKey at the current index?
		if (m_array[current] == val)
		{
			// We found it! Return the index
			return current;
		}
		// Check 2 "Base base": Are we done searching? 
		else if (lowerBound > upperBound)
		{
			// Did not find searchKey within m_array
			return -1;
		}
		// Check 3: Which half of the array is searchKey in?
		else
		{
			if (m_array[current] < val)
			{
				// Search the upper half of the array
				return binarySearch(val, current + 1, upperBound);
			}
			else
			{
				// Search the lower half of the array
				return binarySearch(val, lowerBound, current - 1);
			}
		}

		return -1;
	}
	
};