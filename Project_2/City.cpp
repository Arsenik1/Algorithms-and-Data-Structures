#include "City.hh"

void City::organize_connections(int city_size)
{
	_fast_connections = new Vector<int>(city_size + 1, -1);
	int size = _connections.size();
	for(int i = 0; i < size; i++)
	{
		if(_connections[i][1] != -1)
		{
			(*_fast_connections)[_connections[i][0]] = _connections[i][1];
		}
	}
	

}