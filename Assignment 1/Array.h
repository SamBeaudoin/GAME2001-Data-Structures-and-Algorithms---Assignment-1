#pragma once
#include <assert.h>
#include <iostream>

using namespace std;

template<class T>
class Array
{
private:

public:
	// Public Variables
	T* m_array;			// Pointer to the beginning of the array

	int m_maxSize;		// Maximum size of the array
	int m_growSize = 2;		// Amount the array can grow through expansion
	int m_numElements = 0;	// Number of items currently in the array
	

	// Constructor
	Array(int size) : m_array(NULL), m_maxSize(0), m_growSize(2), m_numElements(0)
	{
		if (size)	// Is this a legal size for an array?
		{
			m_maxSize = size;
			m_array = new T[m_maxSize];		// Dynamically allocating an array to m_maxSize
			memset(m_array, 0, sizeof(T) * m_maxSize);	// Explicitly set 0 to all elements in the array
			
		}
	}
	// Destructor
	~Array()
	{
		if (m_array != nullptr)
		{
			delete[] m_array;
			m_array = nullptr;
		}
	}

	// Gets and Sets
	int GetSize()
	{
		return m_numElements;
	}
	int GetMaxSize()
	{
		return m_maxSize;
	}
	int GetGrowSize()
	{
		return m_growSize;
	}
	int SetGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}

	// Virtuals
	virtual void push(T val) = 0;
	virtual int search(T val) = 0;

	// Overloaded [] operator
	T& operator[](int index)
	{
		assert(m_array != nullptr && index < m_numElements);
		return m_array[index];
	}
	// Display
	void DisplayContents()
	{
		cout << "\n--------------------------------\n";
		cout << "Contents inside Array: ";
		for (int i = 0; i < m_numElements; i++)
		{
			cout << m_array[i] << " ";
		}
		cout << "\n--------------------------------\n";
	}
	// Clear
	void clear()
	{
		m_numElements = 0;	 // Ignore (or forgets) all current items in the array
	}

	// Deletion (2 ways)
	// Remove the last item inserted into the array
	void pop()
	{
		if (m_numElements > 0)
		{
			m_numElements--;	// Reduce the total number of elements by 1. Ignoring the last element.
		}
	}
	// Remove an item given an index
	// (Almost) Brute-force execution -- Big-O = O(N)
	void remove(int index)
	{
		assert(m_array != nullptr);

		if (index >= m_numElements)
		{
			// I am trying to remove something outside of the bounds of the array
			return;	// <-- Maybe could do some form of exception handling
		}

		for (int i = index; i < m_numElements; i++)
		{
			// Start at the index we want to remove.
			// Shift everything after index back by one.
			if (i + 1 < m_numElements)	// Confines the loop into the array
			{
				m_array[i] = m_array[i + 1];
			}
		}
		m_numElements--;
	}

	// Expansion
	bool Expand()
	{
		if (m_growSize <= 0)
		{
			// LEAVE!
			return false;
		}

		// Create the new array
		T* temp = new T[m_maxSize + m_growSize];
		assert(temp != nullptr);

		// Copy the contents of the original array into the new array
		memcpy(temp, m_array, sizeof(T) * m_maxSize);

		// Delete the old array
		delete[] m_array;

		// Clean up variable assignments
		m_array = temp;
		temp = nullptr;

		cout << "\nGrowing Array by: " << m_growSize << endl << endl;

		m_maxSize += m_growSize;
		m_growSize *= 2;

		return true;
	}
};

// Ordered Array Template Class

template<class T>
class OrderedArray final : public Array<T>
{
private:

public:
	// Public Variables
	bool m_dupesAllowed;	// Whether or not copies of data are allowed in the array

	// Constructor 

	OrderedArray(int size, bool isDupesAllowed) : Array<T>(size)
	{
		m_dupesAllowed = isDupesAllowed;
	};

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
		assert(this->m_array != nullptr);

		if (((binarySearch(val, 0, this->m_numElements - 1)) != -1) && !GetDupesAllowed())	// Duplicate Check
		{
			std::cout << std::endl << "Duplicate data found! Unable to enter value: " << val << std::endl << std::endl;
			return;
		}

		if (this->m_numElements >= this->m_maxSize)
		{
			this->Expand();
		}

		int i, k;	// i - Index to be inserted. k - Used for shifting purposes
		// Step 1: Find the index to insert val
		for (i = 0; i < this->m_numElements; i++)
		{
			if (this->m_array[i] > val)
			{
				break;
			}
		}

		// Step 2: Shift everything to the right of the index(i) forward by one. Work backwards
		for (k = this->m_numElements; k > i; k--)
		{
			this->m_array[k] = this->m_array[k - 1];
		}

		cout << "Adding the value: " << val << " to Array.\n";

		// Step 3: Insert val into the array at index
		this->m_array[i] = val;

		this->m_numElements++;

		// return i;
	}

	// Searching
	// Binary Search
	int search(T val)
	{
		// Call to binary search recursive function
		// Binary Search: searchKey, initial lowerBound, initial upperBound
		return binarySearch(val, 0, this->m_numElements - 1);
	}

private:
	// Private functions
	// Recursive Binary Search
	int binarySearch(T val, int lowerBound, int upperBound)
	{
		assert(Array<T>::m_array != nullptr);
		//assert(lowerBound >= 0);
		///assert(upperBound < this->m_numElements);

		// Bitwise divide by 2
		int current = (lowerBound + upperBound) >> 1;

		// Check 1 "Base case": Did we find the searchKey at the current index?
		if (Array<T>::m_array[current] == val)
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
			if (Array<T>::m_array[current] < val)
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

// Un-Ordered Templated Array Class

template<class T>
class UnorderedArray final : public Array<T>
{
private:

public:
	// Constructor 

	UnorderedArray(int size) : Array<T>(size) {};

	// Insertion
	// Fast insertion for UnorderedArray -- Big-O is O(1)
	void push(T val)
	{
		assert(Array<T>::m_array != nullptr); // Debugging purposes

		if (Array<T>::m_numElements >= this->m_maxSize)	// Check if the array has to expand to accommodate the new data.
		{
			Array<T>::Expand();
		}

		cout << "Adding the value: " << val << " to Array.\n";

		// My array has space for a new value. Let's add it!
		Array<T>::m_array[Array<T>::m_numElements] = val;
		Array<T>::m_numElements++;
	}

	// Searching
	// Linear Search
	int search(T val)
	{
		assert(Array<T>::m_array != nullptr);

		// Brute-force Search
		for (int i = 0; i < Array<T>::m_numElements; i++)
		{
			if (Array<T>::m_array[i] == val)
			{
				return i;	// Return the index of where the item is located in the array
			}
		}

		return -1;
	}

};
