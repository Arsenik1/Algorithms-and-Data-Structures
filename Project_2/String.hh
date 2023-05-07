#ifndef __STRING__
#define __STRING__

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class String
{
	public:
	String();
	String(const int len);
	String(const char *str);
	String(const char *str, const int len);
	String(const String& other);
	String(String &&other);
	friend std::ostream& operator<<(std::ostream& os, const String& other);
	friend std::istream& operator>>(std::istream& is, String& other);
	String &operator=(const String& other);
	String &operator=(const char* other);
	String operator+(const String& other);
	String operator+(const char* other);
	String &operator +=(const String& other);
	String &operator +=(const char* other);
	String &operator +=(const char& other);
	bool operator==(const String& other);
	bool operator==(const char* other);
	bool operator!=(const String& other);
	bool operator!=(const char* other);
	char &operator[](int index);
	~String();

	int length();
	void append(const String& other);
	void append(const char* other);
	char *get_str();

	private:
	char *_str;
	int _len;
};

std::ostream& operator<<(std::ostream& os, const String& other);
std::istream& operator>>(std::istream& is, String& other);

#endif
