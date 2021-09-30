#include <iostream>
#include <assert.h>

#include "OrderedArray.h"
#include "UnorderedArray.h"

int main()
{
	OrderedArray<int> OrderArray(3);

	Array<double> array(2);
	
	UnorderedArray<float> UnorderArray(4);

	OrderArray.push(2);
	OrderArray.push(4);
	OrderArray.push(6);

	for (int i = 0; i < OrderArray; i++)
	{
		// Gotta figure out the basics again lol
	}

	UnorderArray.push(1.3f);
	UnorderArray.push(3.3f);
	UnorderArray.push(6.8f);
	UnorderArray.push(9.2f);
	return 0;
}