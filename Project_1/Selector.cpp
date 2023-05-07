#include "Selector.hh"

int find(string input, char to_find, int instance = 1)
{
	int index = -999;
	for(int i = 0; i < input.length(); i++)
		if(input.at(i) == to_find)
		{
			if(--instance == 0)
			{
				index = i;
				break;
			}
		}
	return index;
}

