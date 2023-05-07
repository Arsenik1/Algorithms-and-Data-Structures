#include <iostream>
#include <list>
#include <string>

using namespace std;

bool operator<(string a, string b)
{
	int len = 0;
	if(a.length() > b.length())
		return false;
	else if(a.length() < b.length())
		return true;
	
	len = a.length();
	for(int i = 0; i < len; i++)
	{
		if(a.at(i) < b.at(i))
			return true;
		else if(a.at(i) > b.at(i))
		 	return false;
	}
	return false;
}

list<string> merge(list<string> left, list<string> right)
{
	list<string> res;

	while(left.size() > 0 && right.size() > 0)
	{
		if(operator<(left.front(), right.front()))
		{
			res.push_back(left.front());
			left.pop_front();
		}
		else
		{
			res.push_back(right.front());
			right.pop_front();
		}
	}
	while(left.size() > 0)
	{
		res.push_back(left.front());
		left.pop_front();
	}
	while(right.size() > 0)
	{
		res.push_back(right.front());
		right.pop_front();
	}
	return res;
}

list<string> merge_sort(list<string> lst)
{
	int len = lst.size();

	if(len <= 1)
		return lst;

	list<string> left;
	list<string> right;

	auto curr = lst.cbegin();

	for(int i = 0; i < len; i++)
	{
		if(i < len / 2)
		{
			left.push_back(*curr);
		}
		else
		{
			right.push_back(*curr);
		}
		++curr;
	}

	left = merge_sort(left);
	right = merge_sort(right);

	return merge(left, right);
}



int main()
{
	unsigned int n;
	cin >> n;
	list<string> input;
	string temp;
	for(int i = 0; i < n; i++)
	{
		temp = "";
		cin >> temp;
		input.push_back(temp);
	}
	// input = {"13","27","328","111","25"};

	input = merge_sort(input);

	for(auto a : input)
		cout << a << ' ';

	return 0;
}