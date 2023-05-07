#include <iostream>
#include <vector>
#include <float.h>
#include <math.h>

using namespace std;

const int EPSILON = 0.01;

struct point{
	public:
		point(int id, int x, int y) : _id(id), _x(x), _y(y) {}
		point() : _id(0), _x(-999), _y(-999) {}
		const int getId()
		{
			return _id;
		}
		const int get_x()
		{
			return _x;
		}
		const int get_y()
		{
			return _y;
		}
		void set_Id(int id)
		{
			if(id >= 0)
				_id = id;
		}
		void set_x(int x)
		{
			_x = x;
		}
		void set_y(int y)
		{
			_y = y;
		}
		void set(int id, int x, int y)
		{
			set_Id(id);
			set_x(x);
			set_y(y);
		}
	private:
	int _id;
	int _x;
	int _y;
};

int vectorSize(vector<point> vec)
{
	for(int i = 1; i < 1000; i++)
		if(vec.at(i).get_x() == -999)
			return i;
	return vec.size();
}

bool is_equal(int a, int b)
{
	return 	fabs(a - b) < EPSILON;
}

int which_field(point dot)
{
	int x = dot.get_x(), y = dot.get_y();

	if((x > 0 || is_equal(0, x)) && (y > 0) || is_equal(0, y))
		return 1;
	else if((x < 0 || is_equal(0, x)) && y > 0)
		return 2;
	else if(x < 0 && (y < 0) || is_equal(0, y))
		return 3;
	else if((x > 0 || is_equal(0, x)) && y < 0)
		return 4;
}

void move_point(point &dot, int dirx, int diry)
{
	dot.set_x(dot.get_x() + dirx);
	dot.set_y(dot.get_y() + diry);
}

void sort_vertices(vector<vector<point>> &polygons, int number_of_lines)
{
	int avg_x = 0, avg_y = 0;
	int dir_x = 0.1, dir_y = 0;
	point current_point;
	int biggest_x = 0, smallest_x = 0, biggest_y = 0, smallest_y = 0;
	int x_diff_current = 0, y_diff_current = 0;
	int rotatecount = 0;
	vector<point> temp_polygon(10000);
	int current_index = 0;

	for(int k = 0; k < number_of_lines; k++)
	{
		auto &a = polygons.at(k);
		avg_x = avg_y = 0;
		biggest_x = biggest_y = -2147483647 - 1;
		smallest_x = smallest_y = 2147483647;
		current_index = 0;

		for(auto &q : temp_polygon)
			if(q.get_x() != -999)
			{
				point temp;
				q = temp;
			}

		// cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
		// for(auto q : temp_polygon)
		// 	if(q.get_x() != -999)
		// 	cout << q.get_x() << '^' << q.get_y() << endl;
		for(int l = 0; l < vectorSize(a); l++)
		{
			auto &b = a.at(l);
			if(b.get_x() > biggest_x)
				biggest_x = b.get_x();
			if(b.get_y() > biggest_y)
				biggest_y = b.get_y();
			if(b.get_x() < smallest_x)
				smallest_x = b.get_x();
			if(b.get_y() < smallest_y)
				smallest_y = b.get_y();

			avg_x += b.get_x();
			avg_y += b.get_y();
		}
		avg_x /= vectorSize(a);
		avg_y /= vectorSize(a);

		for(int m = 0; m < vectorSize(a); m++)
		{
			a.at(m).set_x(a.at(m).get_x() - avg_x);
			a.at(m).set_y(a.at(m).get_y() - avg_y);
		}

		avg_x = avg_y = 0;

		current_point.set_x(smallest_x);
		current_point.set_y(biggest_y);

		rotatecount = 0;
		while(rotatecount < 4)
		{
			while(((current_point.get_x() < biggest_x || is_equal(current_point.get_x(), biggest_x)) && rotatecount == 0) || ((current_point.get_y() > smallest_y || is_equal(current_point.get_y(), smallest_y))&& rotatecount == 1) 
					|| ((current_point.get_x() > smallest_x || is_equal(current_point.get_x(), smallest_x)) && rotatecount == 2) || ((current_point.get_y() < biggest_y || is_equal(current_point.get_y(), biggest_y)) && rotatecount == 3))
			{
				// cout << endl << rotatecount << "\naa\n";
				x_diff_current = current_point.get_x() - avg_x;
				y_diff_current = current_point.get_y() - avg_y;

				for(int l = 0; l < vectorSize(a); l++)
				{
					auto &b = a.at(l);
					if(is_equal(y_diff_current/x_diff_current, ((b.get_y() - avg_y)/(b.get_x() - avg_x)))
								&& which_field(current_point) == which_field(b))
							temp_polygon.at(current_index++) = b;
				}
				move_point(current_point, dir_x, dir_y);
			}
			if(rotatecount == 0)
			{
				dir_x = 0;
				dir_y = -0.1;
				++rotatecount;
			}
			else if(rotatecount == 1)
			{
				dir_x = -0.1;
				dir_y = 0;
				++rotatecount;
			}
			else if(rotatecount == 2)
			{
				dir_x = 0;
				dir_y = 0.1;
				++rotatecount;
			}
			else if(rotatecount == 3)
			{
				dir_x = 0.1;
				dir_y = 0;
				++rotatecount;
			}
		}
		for(int i = 0; temp_polygon.at(i).get_x() != -999; i++)
			temp_polygon.at(i).set_Id(i);
		a = temp_polygon;
	}
}

void calcPolygons(vector<vector<point>> &polygons, int num_of_lines)
{
		cout << endl;
	int sum_x = 0, sum_y = 0;
	for(int i = 0; i < num_of_lines; i++)
	{
		sum_x = 0;
		sum_y = 0;
		int size = vectorSize(polygons.at(i));
		int curr_x, curr_y, next_x, next_y;
		for(int j = 0; j < size; j++)
		{
			curr_y = polygons.at(i).at(j).get_y();
			curr_x = polygons.at(i).at(j).get_x();
			if(j == size - 1)
			{
				next_x = polygons.at(i).at(0).get_x();
				next_y = polygons.at(i).at(0).get_y();
			}
			else
			{
				next_x = polygons.at(i).at(j + 1).get_x();
				next_y = polygons.at(i).at(j + 1).get_y();
			}
				sum_x += curr_x * next_y;
				sum_y += curr_y * next_x;
		}
		cout << abs((sum_x - sum_y) / 2) << endl;
	}
}

void printPolygons(vector<vector<point>> polygons, int num_of_lines)
{
	for(int i = 0; i < num_of_lines; i++)
	{
		int size = vectorSize(polygons.at(i));
		for(int j = 0; j < size; j++)
		{
			cout << polygons.at(i).at(j).getId() << ' ' << polygons.at(i).at(j).get_x() << ' ' << polygons.at(i).at(j).get_y() << '/';
		}
		cout << 'e' << endl;
	}
}

int main()
{
	int num_of_lines = 0;
	int num_of_points = 0;
	vector<vector<point>> polygons(1000, vector<point>(1000));

	cin >> num_of_lines;


	vector<point> polygon_temp(1000);
	for(int i = 0; i < num_of_lines; i++)
	{
		cin >> num_of_points;
		num_of_points /= 2;
		point temp_point;
		int input_x, input_y;
		for(int j = 0; j < num_of_points; j++)
		{
			
			cin >> input_x >> input_y;
			temp_point.set(j, input_x, input_y);
			polygons.at(i).at(j) = temp_point;
		}
	}

	// cout << "\nhaha\n";
	// printPolygons(polygons, num_of_lines);

	// sort_vertices(polygons, num_of_lines);

	// cout << endl;

	// printPolygons(polygons, num_of_lines);

	calcPolygons(polygons, num_of_lines);


	return 0;
}