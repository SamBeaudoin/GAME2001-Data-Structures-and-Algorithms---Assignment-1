#include <iostream>
#include <assert.h>

#include "Array.h"

using namespace std;

int main()
{
	OrderedArray<int> OrderArray(2);
	
	UnorderedArray<float> UnorderArray(4);

	OrderArray.push(10);
	cout << "OrderArray size: " << OrderArray.GetMaxSize() << endl;
	OrderArray.push(4);
	cout << "OrderArray size: " << OrderArray.GetMaxSize() << endl;
	OrderArray.push(6);
	cout << "OrderArray size: " << OrderArray.GetMaxSize() << endl;
	OrderArray.push(4);
	cout << "OrderArray size: " << OrderArray.GetMaxSize() << endl;
	OrderArray.push(5);
	cout << "OrderArray size: " << OrderArray.GetMaxSize() << endl;
	OrderArray.push(12);
	cout << "OrderArray size: " << OrderArray.GetMaxSize() << endl;
	OrderArray.push(7);
	cout << "OrderArray size: " << OrderArray.GetMaxSize() << endl;
	OrderArray.push(14);
	cout << "OrderArray size: " << OrderArray.GetMaxSize() << endl;
	OrderArray.push(24);
	cout << "OrderArray size: " << OrderArray.GetMaxSize() << endl;
	
	cout << "------------------------------------------------------------------\n";
	cout << endl << "Ordered Array Contents:" << endl << endl;
	cout << "------------------------------------------------------------------\n";

	for (int i = 0; i < OrderArray.GetSize(); i++)
	{
		cout << "Element at Index " << i << " is: " << OrderArray[i] << endl;
	}

	UnorderArray.push(1.3f);
	UnorderArray.push(3.3f);
	UnorderArray.push(6.8f);
	UnorderArray.push(9.2f);

	cout << "------------------------------------------------------------------\n";
	cout << endl << "Un-Ordered Array Contents:" << endl << endl;
	cout << "------------------------------------------------------------------\n";

	for (int i = 0; i < UnorderArray.GetSize(); i++)
	{
		cout << "Element at Index " << i << " is: " << UnorderArray[i] << endl;
	}


	return 0;
}