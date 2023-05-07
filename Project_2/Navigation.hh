#ifndef __NAVIGATION__
#define __NAVIGATION__

#include "Vector.hh"
#include "Vector.cpp"
#include "City.hh"

class Navigation
{
	public:
	int current_city_id;
	Navigation();

	void print_map();
	void print_cities();
	void get_input();

	private:
	String read_city_name(int x, int y);
	void find_cities();
	int find_roads(City& current_city, Vector<String> replacement_map, int i, int j, int depth);
	void take_flight_input();

	template<class T>
	bool find_in_eight_directions(T &matrix, int i, int j, char to_find, int& ret_x, int& ret_y); //returns true if found, false otherwise
	template<class T>
	bool find_in_four_directions(T &matrix, int i, int j, char to_find, int& ret_x, int& ret_y); //returns true if found, false otherwise

	void shortest_path(City& start, City& end, int query);
	int min_distance(Vector<int> &weights, Vector<bool> &visited);

	inline void update_replacement_map(){ _replacement_map = _map; }

	Vector<City> _cities;
	Vector<String> _replacement_map;
	Vector<String> _map;
	int height;
	int width;
};

#endif