#ifndef CSSTEXT
#define CSSTEXT

#include "Selector.hh"

class cssText
{
	public:
	cssText();
	void read_next_selector(string input);
	bool add_new_selector(Selector sel);	
	bool delete_selector(Selector sel);
	private:
	list<Selector> _text;
};

#endif