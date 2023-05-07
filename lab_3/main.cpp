#include <iostream>
#include <vector>

using namespace std;

bool add_one(vector<bool> &bin)
{
	for(int i = bin.size() - 1; i >= 0; i--)
	{
		for(int j = 0; j < bin.size(); j++)
		{
			if(bin.at(j) == 0)
				break;
			if(j == bin.size() - 1)
				return false;
		}
		if(bin.at(i) == false)
		{
			bin.at(i) = true;
			return true;
		}
		else
		{
			bin.at(i) = false;
		}
	}
	return true;
}

bool subtract_one(vector<bool> &bin)
{
	for(int i = bin.size() - 1; i >= 0; i--)
	{
		for(int j = 0; j < bin.size(); j++)
		{
			if(bin.at(j) == 1)
				break;
			if(j == bin.size() - 1)
				return false;
		}
		if(bin.at(i) == true)
		{
			bin.at(i) = false;
			return true;
		}
		else
		{
			bin.at(i) = true;
		}
	}
	return true;
}

vector<bool> conv_to_binary(int num)
{
	vector<bool> bin_version(8, false);
	bool a;
	while(num)
	{
		num--;
		a = add_one(bin_version);
	}

	return bin_version;
}

int conv_to_int(vector<bool> bin_version)
{
	int num = 0;
	bool a;
	int exponent = 1;
	for(int i = bin_version.size() - 1; i >= 0; i--)
	{
		if(bin_version.at(i) == true)
		{
			num += exponent;
		}
		exponent *= 2;
	}
	return num;
}

int calc_profit(vector<vector<int>> &storage, int capacity, vector<bool> &profit_selection)
{
	vector<bool> bin_version(storage.at(0).size(), true);
	int exponent = 1, num_of_items = bin_version.size();
	int in_car = 0, off_car = 0, curr_capacity = 0;
	int profit = 0;

	while(num_of_items)
	{
		exponent *= 2;
		--num_of_items;
	}
	// cout << '/' << exponent << '/';
	while(true)
	{
		curr_capacity = off_car = in_car = 0;
		for(int i = 0; i < bin_version.size(); i++)
		{
			if(bin_version.at(i) == true)
			{
				in_car += storage.at(0).at(i);
				curr_capacity += storage.at(1).at(i);
			}
			else
			{
				off_car += storage.at(0).at(i);
			}
		}
		if(curr_capacity <= capacity && in_car > profit)
		{
			profit_selection = bin_version;
			profit = in_car;
		}
		if(conv_to_int(bin_version) == 0)
			break;

		subtract_one(bin_version);
		// cout << conv_to_int(bin_version) << endl;
		// cout << "\nTEST\n\n";
	}
	return profit;
}

int main()
{
	int num_of_items = 0; //max 15
	int capacity = 0;
	int profit = 0;
	int repeat = 500;

	// vector<bool> bin_version(5, false);
	// add_one(bin_version);
	// cout << conv_to_int(bin_version);

	while(repeat)
	{
		cin >> num_of_items;

		vector<vector<int>> storage(2, vector<int>(num_of_items, 0));
		vector<bool> profitCalc(num_of_items, false);

		for(int i = 0; i < num_of_items; i++)
			cin >> storage.at(0).at(i);
		for(int i = 0; i < num_of_items; i++)
			cin >> storage.at(1).at(i);

		cin >> capacity;

		profit = calc_profit(storage, capacity, profitCalc);
		cout << profit << endl;

		--repeat;
	}

	return 0;
}