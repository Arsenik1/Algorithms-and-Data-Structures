#ifndef SELECTOR
#define SELECTOR

#include "String.hh"
#include "List.hh"

class Selector
{
public:
	Selector();

	struct Attribute
	{
		String _name;
		String _value;
	};
	bool add_attr(string attr_name, string right);
	bool del_attr(string attr_name);
	bool update_attr(string attr_name, string value);
	Attribute get_attr();


private:
	String selector_name;
	Attribute[T] _attributes;
};

#endif