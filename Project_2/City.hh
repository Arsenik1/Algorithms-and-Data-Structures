#ifndef __CITY__
#define __CITY__

#include "Vector.hh"
#include "Vector.cpp"
#include "String.hh"

class City
{
	public:
	City() : _i(0), _j(0), _name(), _id(0), _as_i(0), _as_j(0) {_connections = Vector<Vector<int>>(1, Vector<int>(2, -1));}
	City(int i, int j, String name, int id, int as_i, int as_j) : _i(i), _j(j), _name(name), _id(id), _as_i(as_i), _as_j(as_j) { _connections = Vector<Vector<int>>(1, Vector<int>(2, -1));}
	City(const City& other) : _i(other._i), _j(other._j), _name(other._name), _id(other._id), _as_i(other._as_i), _as_j(other._as_j), _connections(other._connections) {}

	inline int get_i() const { return _i; }
	inline int get_j() const { return _j; }
	inline String get_name() const { return _name; }
	inline int get_id() const { return _id; }
	inline int get_as_i() const { return _as_i; }
	inline int get_as_j() const { return _as_j; }
	inline Vector<Vector<int>> get_connections() const { return _connections; }
	inline void add_connection(int id, int distance) { if((*_fast_connections)[id] == -1 && distance >= 0) (*_fast_connections)[id] = distance;}
	inline void add_connections(const Vector<int> connection) { _connections.push_back(connection); }
	inline int& find_connection(int id) {return (*_fast_connections)[id];}
	inline Vector<int>& find_connections(int id) { for(int i = 0; i < _connections.size(); i++) if(_connections[i][0] == id) return _connections[i]; return _connections[0];}
	inline void update_connections(Vector<int> &new_connection) { for(int i = 0; i < _connections.size(); i++) if(_connections[i][0] == new_connection[0]) _connections[i][1] = new_connection[1];}
	inline void update_connection(Vector<int> &new_connection) {(*_fast_connections)[new_connection[0]] = new_connection[1];}
	inline City& operator=(const City& other) { _i = other._i; _j = other._j; _name = other._name; _id = other._id; _as_i = other._as_i; _as_j = other._as_j; _connections = other._connections; return *this; }
	void organize_connections(int city_size);

	private:
		int _as_i; //asterisk i
		int _as_j; //asterisk j
		int _i;	//name x
		int _j;	//name y
		int _id; //city id
		String _name; //city name

		Vector<Vector<int>> _connections; //connections to other cities
		Vector<int> *_fast_connections;

		/*
		_connections holds the road information for one city.
		Every line includes where the road is heading at and that the distance is.
		"other city id" can have more than one of the same id's in case current city has
		more than one connections to the other city.
	    __________________________________
		|index| other city id | distance |
		|   0 |               |          |
		|   1 |               |          |
		|   2 |               |          |
		|   3 |               |          |
		|   4 |               |          |
		|   5 |               |          |
		|   6 |               |          |
		| ... |               |          |
	    __________________________________
		*/
};

#endif