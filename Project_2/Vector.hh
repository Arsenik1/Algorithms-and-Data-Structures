#ifndef __VECTOR__
#define __VECTOR__

#include "String.hh"

template<class T>
class Vector
{
	public:
	Vector();
	Vector(const int size);
	Vector(const int size, const T& default_value);
	Vector(const Vector& other);
	Vector(Vector&& other);
	Vector& operator=(const Vector& other);
	~Vector();

	void push_back(const T& item);
	void pop_back();
	void insert(const int index, const T& item);
	void erase(const int index);
	void clear();
	void resize(const int size);
	void resize(const int size, const T& default_value);
	const int size() const;
	const int capacity() const;
	T& operator[](const int index);
	T& at(const int index);

	private:
	T *_data;
	int _size;
	int _capacity;
};

#endif