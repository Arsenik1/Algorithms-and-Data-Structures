#ifndef __STRING__
#define __STRING__

#define T 8;

#include <iostream>

using namespace std;

class String
{
	public:
	String();
	String(string input);
	String(const String& input);
	~String();
	String& operator=(const String& input);
	
	int length() const;

	private:
	char* _string;
	int _length;
};

#endif