#include "String.hh"

String::String()
{
	_len = 0;
	_str = new char[1];
	_str[0] = '\0';
}

String::String(const int len)
{
	if(len >= 0)
	{
		_len = len;
		_str = new char[len + 1];
		memset(_str,'\0',_len + 1);
	}
	else cout << "String ERROR: NEGATIVE VALUE IN LENGTH DETECTED" << endl;
}

String::String(const char *str)
{
	_len = strlen(str);
	_str = new char[_len + 1];
	memset(_str,'\0',_len + 1);
	strcpy(_str, str);
}

String::String(const char *str,const int len)
{
	if(len >= 0)
	{
		_len = len;
		if(strlen(str) != len)
		{
			_len = strlen(str);
			cout << "String ERROR: _len AND STRING LENGTH DO NOT MATCH" << endl;
		}
		_str = new char[len + 1]();
		strcpy(_str, str);
	}
	else cout << "String ERROR: NEGATIVE VALUE IN LENGTH DETECTED" << endl;
}


String::String(const String& other)
{
	_len = other._len;
	_str = new char[_len + 1]();
	strcpy(_str, other._str);
}

String::String(String &&other)
{
	_len = other._len;
	_str = other._str;
	other._str = NULL;
	other._len = 0;
}

String &String::operator=(const String& other)
{
	_len = other._len;
	delete[] _str;
	_str = new char[_len + 1]();
	strcpy(_str, other._str);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const String& other)
{
	os << other._str;
	return os;
}

std::istream& operator>>(std::istream& is, String& other)
{
	is >> other._str;
	other._len = strlen(other._str);
	return is;
}

String &String::operator=(const char* other)
{
	_len = strlen(other);
	delete[] _str;
	_str = new char[_len + 1]();
	strcpy(_str, other);

	return *this;
}


String String::operator+(const String& other)
{
	String temp;
	temp._len = _len + other._len;
	temp._str = new char[temp._len + 1]();
	strcpy(temp._str, _str);
	strcat(temp._str, other._str);
	temp._str[temp._len] = '\0';

	return temp;
}

String String::operator+(const char* other)
{
	String temp;
	temp._len = _len + strlen(other);
	temp._str = new char[temp._len + 1]();
	strcpy(temp._str, _str);
	strcat(temp._str, other);
	temp._str[temp._len] = '\0';

	return temp;
}

String &String::operator+=(const String& other)
{
	char *temp = _str;
	_str = new char[other._len + _len + 1]();
	for(int i = 0; i < _len; i++)
		_str[i] = temp[i];
	delete[] temp;
	for(int i = _len; i < _len + other._len; i++)
		_str[i] = other._str[i - _len];
	_len += other._len;
	_str[_len] = '\0';

	return *this;
}

String &String::operator+=(const char* other)
{
	char *temp = _str;
	_str = new char[strlen(other) + _len + 1]();
	for(int i = 0; i < _len; i++)
		_str[i] = temp[i];
	for(int i = _len; i < _len + strlen(other); i++)
		_str[i] = other[i - _len];
	delete[] temp;
	_len += strlen(other);
	_str[_len] = '\0';

	return *this;
}

String &String::operator+=(const char& other)
{
	char *temp = _str;
	_str = new char[2 + _len]();
	for(int i = 0; i < _len; i++)
		_str[i] = temp[i];
	_str[_len] = other;
	delete[] temp;
	_len += 1;
	_str[_len] = '\0';

	return *this;
}

bool String::operator==(const String& other)
{
	if(_len != other._len)
		return false;
	for(int i = 0; i < _len; i++)
		if(_str[i] != other._str[i])
			return false;
	return true;
}

bool String::operator!=(const String& other)
{
	return !(*this == other);
}

bool String::operator!=(const char* other)
{
	return !(*this == other);
}

bool String::operator==(const char* other)
{
	if(_len != strlen(other))
		return false;
	for(int i = 0; i < _len; i++)
		if(_str[i] != other[i])
			return false;
	return true;
}

char &String::operator[](int index)
{
	if(index >= 0 && index <= _len)
		return _str[index];
	else cout << "String ERROR: NEGATIVE INDEX DETECTED" << " len: " << _len << " index: " << index << endl;

	return _str[0];
}

String::~String()
{
	if(_str != NULL)
		delete[] _str;
}

int String::length()
{
	return _len;
}

void String::append(const String& other)
{
	char *temp = _str;
	_str = new char[other._len + _len + 1];
	for(int i = 0; i < _len; i++)
		_str[i] = temp[i];
	delete[] temp;
	for(int i = _len; i < _len + other._len; i++)
		_str[i] = other._str[i - _len];
	_len += other._len;
}

void String::append(const char* other)
{
	char *temp = _str;
	_str = new char[strlen(other) + _len + 1];
	for(int i = 0; i < _len; i++)
		_str[i] = temp[i];
	for(int i = _len; i < _len + strlen(other); i++)
		_str[i] = other[i - _len];
	delete[] temp;
	_len += strlen(other);
}

char *String::get_str()
{
	char *temp;
	temp = new char[_len + 1];
	strcpy(temp, _str);
	return temp;
}
