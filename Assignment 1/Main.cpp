#include <iostream>
#include <assert.h>

#include "Array.h"

using namespace std;

int main()
{
	OrderedArray<int> OrderArray(2, false);
	
	UnorderedArray<float> UnorderArray(4);

	OrderArray.push(10);
	OrderArray.push(4);
	OrderArray.push(6);
	OrderArray.push(4);
	OrderArray.push(5);
	OrderArray.push(12);
	OrderArray.push(7);
	OrderArray.push(14);
	OrderArray.push(24);
	OrderArray.push(24);
	OrderArray.push(55);
	
	OrderArray.DisplayContents();

	UnorderArray.push(1.3f);
	UnorderArray.push(3.3f);
	UnorderArray.push(6.8f);
	UnorderArray.push(9.2f);
	UnorderArray.push(10.2f);
	UnorderArray.push(9.2f);

	UnorderArray.DisplayContents();


	return 0;
}