#include "Navigation.hh"

#define INT_MAX 2147483647

Navigation::Navigation() : _cities()
{
	width = height = 0;
	current_city_id = 0;
	cin >> width >> height;

	_map = Vector<String>(height, String(width));
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
			cin >> _map[i][j];
		_map[i][width] = '\0';
	}


	find_cities();
	_replacement_map = _map;
	int size = _cities.size();
	for(int i = 0; i < size; i++)
	{
		update_replacement_map();
		_replacement_map[_cities[i].get_as_i()][_cities[i].get_as_j()] = 'o';
		find_roads(_cities[i], _replacement_map, _cities[i].get_as_i(), _cities[i].get_as_j(), 0);
	// cout << "\nTEST\n";
	}
	take_flight_input();
	for(int i = 0; i < size; i++)
		_cities[i].organize_connections(size);
}

void Navigation::take_flight_input()
{
	int flag1 = 0, flag2 = 0;
	int n;
	int dist;
	String from(30), to(30);
	Vector<int> connection_1(2, -1), connection_2(2, -1);
	// cout << "\nTEST\n";
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> from >> to >> dist;
		// cout << endl << from << "to" << to << "in" << dist << endl << endl;
		if(dist > 0)
		{
			flag1 = flag2 = 0;
			int size = _cities.size();
			for(int j = 0; j < size; j++)
			{
				if(from == _cities[j].get_name() && flag1 == 0)
				{
					// cout << from << " " << _cities[j].get_name() << " MATCH1\n";
					connection_1[0] = _cities[j].get_id();
					connection_1[1] = dist;
					flag1 = 1;
				}
				if(to == _cities[j].get_name() && flag2 == 0)
				{
					// cout << to << " " << _cities[j].get_name() << " MATCH2\n";
					// cout << to << "\nMATCH2\n";
					connection_2[0] = _cities[j].get_id();
					connection_2[1] = dist;
					flag2 = 1;
					// cout << connection_2[0] << endl;
				}
				if(flag1 && flag2)
					break;
				// cout << _cities.size() << endl;
				// cout << _cities[j].get_name() << _cities[j].get_name().length() << " " << _cities[j].get_name()[0] << " - " << from.length() << from << "|" << (int)from[6] << endl;
			}
			if(connection_1[0] >= 0 && connection_2[0] >= 0)
			{
				// cout << _cities[connection_1[0]].get_name() << " " << connection_2[0] << endl;
				Vector<int> temp = _cities[connection_1[0]].find_connections(connection_2[0]);
				if(temp[0] == connection_2[0])
				{
					if(temp[1] > dist)
						_cities[connection_1[0]].update_connections(connection_2);
				}
				else
						_cities[connection_1[0]].add_connections(connection_2);
			}
		}
		// _cities[from].add_connection(to, dist);
		// _cities[to].add_connection(from, dist);
	}
}

void Navigation::print_map()
{
	cout << "Matrix:" << endl;
	for(int i = 0; i < _map.size(); i++)
	{
		for(int j = 0; j < _map[i].length(); j++)
			cout << _map[i][j];
		cout << endl;
	}
}

void Navigation::print_cities()
{
	cout << "Cities:" << endl;
	int size = _cities.size();
	for(int i = 0; i < size; i++)
	{
		cout << _cities[i].get_id() << " - " << _cities[i].get_name() << " " << _cities[i].get_as_i() << " " << _cities[i].get_as_j() << endl;
		cout << "Connections:" << endl;
		int len = _cities[i].get_connections().size();
		for(int j = 0; j < len; j++)
		{
			for(int a = 0; a < size; a++)
			{
				if(_cities[a].get_id() == _cities[i].get_connections()[j][0])
					cout << _cities[a].get_name() << "\t";
			}
			cout << _cities[i].get_connections()[j][1] << endl;
		}
		cout << endl;
	}
}

void Navigation::get_input()
{
	int input_lines = 0, query = 0;
	String src(30), dest(30);
	City src_city, dest_city;
	int input_flag = 0;

	cin >> input_lines;

	for(int i = 0; i < input_lines; i++)
	{
		/*
		one iteration includes:
		take input
		find source and dest cities in the database
		find the route between these cities, also considering the query to show the correct output
		*/
		cin >> src >> dest >> query;
		input_flag = 0;
		int size = _cities.size();
		for(int j = 0; j < size; j++)
		{
			if(src == _cities[j].get_name())
				{
					src_city = _cities[j];
					++input_flag;
				}	
			if(dest == _cities[j].get_name())
				{
					dest_city = _cities[j];
					++input_flag;
				}	
		}
		if(input_flag == 2)
			shortest_path(src_city, dest_city, query);
		else
			cout << "Incorrect city name entered." << endl;
	}
}

int Navigation::find_roads(City& current_city, Vector<String> replacement_map, int i, int j, int depth)
{
	if(i < 0 || j < 0 || i >= _map.size() || j >= _map[i].length())
		return 0;

	// if(i == 9 && j == 13)
	// 	cout << "-------------------GELDIK" << current_city.get_name() << "----------------" << endl;

	if(_map[i][j] == '.')
		return 0;
	int directed_i = i, directed_j = j;

	if(find_in_four_directions(replacement_map, i, j, '*', directed_i, directed_j) && (directed_i != current_city.get_as_i() || directed_j != current_city.get_as_j()))
	{
		++depth;
		replacement_map[directed_i][directed_j] = 'o';
		int size = _cities.size();
		for(int a = 0; a < size; a++)
		{
			if(_cities[a].get_as_i() == directed_i && _cities[a].get_as_j() == directed_j)
			{
				Vector<int> *old_connection = &current_city.find_connections(_cities[a].get_id()); //buradan devam
				if(old_connection != nullptr)
				{
					// cout << "otuzbes";
					if((*old_connection)[0] == _cities[a].get_id())
					{
						if((*old_connection)[1] > depth)
						{
							// cout << "\nREPLACEMENT\n";
							(*old_connection)[1] = depth;
							current_city.update_connections((*old_connection));
						}
					}
					else
					{
						Vector<int> connection(2);
						connection[0] = _cities[a].get_id();
						connection[1] = depth;
						current_city.add_connections(connection);
					}
					return 1;
				}
			}
		}
		return 0;
	}
	else if(find_in_four_directions(replacement_map, i, j, '#', directed_i, directed_j))
	{
		int path_found = 0;
		++depth;
		replacement_map[directed_i][directed_j] = 'o';
		path_found += find_roads(current_city, replacement_map, directed_i, directed_j, depth); //buradan giriyor
		while(find_in_four_directions(replacement_map, i, j, '#', directed_i, directed_j))
		{
			replacement_map[directed_i][directed_j] = 'o';
			path_found += find_roads(current_city, replacement_map,directed_i, directed_j, depth);
		}
		if(path_found == 0)
			return 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

void Navigation::find_cities()
{
	int city_index = 0;
	int size = _map.size();
	for(int i = 0; i < size; i++)
	{
		int len = _map[i].length();
		for(int j = 0; j < len; j++)
		{
			if(_map[i][j] >= 'A' && _map[i][j] <= 'Z')
			{
				String name = read_city_name(i, j);
				int asterisk_x = 0, asterisk_y = 0;

				int temp_i = i, temp_j = j;
				len = _map[temp_i].length();
				while(_map[temp_i][temp_j] >= 'A' && _map[temp_i][temp_j] <= 'Z' && j < len && temp_i < size)
				{
					find_in_eight_directions(_map, temp_i, temp_j, '*', asterisk_x, asterisk_y);
					temp_j++;
				}
				_cities.push_back(City(i, j, name, current_city_id++, asterisk_x, asterisk_y));

				len = _map[i].length();
				while(_map[i][j] >= 'A' && _map[i][j] <= 'Z' && j < len && i < size)
					j++;
			}
		}
	}
}

String Navigation::read_city_name(int x, int y)
{
	String city_name = "";
	int i = x, j = y;

	int len = _map[i].length();
	int size = _map.size();
	while(_map[i][j] >= 'A' && _map[i][j] <= 'Z' && j < len && i < size)
	{
		city_name += _map[i][j];
		j++;
	}
	// cout << "-----" << city_name << city_name.length() << "-----" << endl;
	return city_name;
}

template<class T>
bool Navigation::find_in_eight_directions(T &matrix, int i, int j, char to_find, int &ret_i, int &ret_j)
{
	int size = matrix.size();
	int len = matrix[i].length();
	
	if(i < 0 || j < 0 || i >= size || j >= len)
		return false;

	if(j + 1 < len && matrix[i][j + 1] == to_find)
	{
		ret_i = i;
		ret_j = j + 1;
		return true;
	}
	else if(j + 1 < len && i + 1 < size && matrix[i + 1][j + 1] == to_find)
	{
		ret_i = i + 1;
		ret_j = j + 1;
		return true;
	}
	else if(i + 1 < size && matrix[i + 1][j] == to_find)
	{
		ret_i = i + 1;
		ret_j = j;
		return true;
	}
	else if(j - 1 >= 0 && i + 1 < size && matrix[i + 1][j - 1] == to_find)
	{
		ret_i = i + 1;
		ret_j = j - 1;
		return true;
	}
	else if(j - 1 >= 0 && matrix[i][j - 1] == to_find)
	{
		ret_i = i;
		ret_j = j - 1;
		return true;
	}
	else if(j - 1 >= 0 && i - 1 >= 0 && matrix[i - 1][j - 1] == to_find)
	{
		ret_i = i - 1;
		ret_j = j - 1;
		return true;
	}
	else if(i - 1 >= 0 && matrix[i - 1][j] == to_find)
	{
		ret_i = i - 1;
		ret_j = j;
		return true;
	}
	else if(i - 1 >= 0 && j + 1 < len && matrix[i - 1][j + 1] == to_find)
	{
		ret_i = i - 1;
		ret_j = j + 1;
		return true;
	}
	return false;
}

template<class T>
bool Navigation::find_in_four_directions(T &matrix, int i, int j, char to_find, int &ret_i, int &ret_j)
{
	int size = matrix.size();
	int len = matrix[i].length();

	if(i < 0 || j < 0 || i >= size || j >= len)
		return false;

	if(j + 1 < len && matrix[i][j + 1] == to_find) //right
	{
		ret_i = i;
		ret_j = j + 1;
		return true;
	}
	else if(i + 1 < size && matrix[i + 1][j] == to_find) //up
	{
		ret_i = i + 1;
		ret_j = j;
		return true;
	}
	else if(j - 1 >= 0 && matrix[i][j - 1] == to_find) //left
	{
		ret_i = i;
		ret_j = j - 1;
		return true;
	}
	else if(i - 1 >= 0 && matrix[i - 1][j] == to_find) //down
	{
		ret_i = i - 1;
		ret_j = j;
		return true;
	}
	return false;
}

int Navigation::min_distance(Vector<int> &weights, Vector<bool> &visited)
{
	int min = INT_MAX, min_index;
	int size = _cities.size();

	for(int i = 0; i < size; i++)
	{
		if(visited[i] == false && weights[i] <= min)
		{
			min = weights[i];
			min_index = i;
		}
	}
	return min_index;
}

void Navigation::shortest_path(City& start, City& end, int query)
{
	int size = _cities.size();
	Vector<int> distance(size, INT_MAX);
	distance[start.get_id()] = 0;
	Vector<bool> visited(size, false);
	Vector<int> parent(size, -1);

	for(int i = 0;i < size - 1; i++)
	{
		int smallest_city = min_distance(distance, visited);
		visited[smallest_city] = true;

		for(int j = 0; j < size; j++)
		{
			int *connection = &_cities[smallest_city].find_connection(_cities[j].get_id());
			if(!visited[j] && distance[smallest_city] != INT_MAX
					&& distance[smallest_city] + *connection < distance[j] && *connection != -1)
			{
				/*if we did not set it as current node before and there is an edge between the smallest
				city and the source and the distance is smaller and there is a connection, it will be updated.*/
				// cout << _cities[smallest_city].get_name() << distance[smallest_city] << " " << connection[1] << endl;
				distance[j] = distance[smallest_city] + *connection;
				parent[j] = smallest_city;
			}
		}
	}


	// int highest = 0;
	// for(int i = 0; i < distance.size(); i++)
	// {
	// 	if(distance[i] > highest)
	// 		highest = distance[i];
	// }
	cout << distance[end.get_id()];
	Vector<String> output;

	if(query == 1)
	{
		cout << " ";
		int i = end.get_id();
		while(i != start.get_id())
		{
			if(parent[i] != -1)
			{
				if(_cities[parent[i]].get_id() != start.get_id())
					output.push_back(_cities[parent[i]].get_name());
				i = parent[i];
			}
		}
		for(int i = output.size() - 1; i >= 0; i--)
			cout << output[i] << " ";
		
		cout << endl;
	}
	else cout << endl;
}

//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