#ifndef __VECTOR_CPP__
#define __VECTOR_CPP__

#include "Vector.hh"

template<class T>
Vector<T>::Vector()
{
	_size = 0;
	_capacity = 0;
	_data = NULL;
}

template<class T>
Vector<T>::Vector(const int size)
{
	if(size >= 0)
	{
		_size = size;
		_capacity = size;
		_data = new T[size];
	}
	else cout << "Vector ERROR: NEGATIVE VALUE IN SIZE DETECTED" << endl;
}

template<class T>
Vector<T>::Vector(const int size, const T& default_value)
{
	if(size >= 0)
	{
		_size = size;
		_capacity = size;
		_data = new T[size];
		for(int i = 0; i < size; i++)
		{
			_data[i] = T(default_value);
		}
	}
	else cout << "Vector ERROR: NEGATIVE VALUE IN SIZE DETECTED" << endl;
}

template<class T>
Vector<T>::Vector(const Vector& other)
{
	_size = other._size;
	_capacity = other._capacity; //hata burada
	_data = new T[_capacity];
	for(int i = 0; i < _size; i++)
	{
		_data[i] = other._data[i];
	}
}

template<class T>
Vector<T>::Vector(Vector&& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_data = other._data;
	other._size = 0;
	other._capacity = 0;
	other._data = NULL;
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
	_size = other._size;
	_capacity = other._capacity;
	if(_data != nullptr)
		delete[] _data;
	_data = new T[_capacity];
	for(int i = 0; i < _size; i++)
	{
		_data[i] = other._data[i];
	}

	return *this;
}

template<class T>
Vector<T>::~Vector()
{
	if(_data != NULL)
		delete[] _data;
}

template<class T>
void Vector<T>::push_back(const T& item)
{
	if(_size == _capacity)
	{
		if(_capacity == 0) _capacity = 1;
		else _capacity *= 2;
		T *temp = new T[_capacity];
		for(int i = 0; i < _size; i++)
		{
			temp[i] = _data[i];
		}
		delete[] _data;
		_data = temp;
	}
	_data[_size] = item;
	_size++;
}

template<class T>
void Vector<T>::pop_back()
{
	if(_size > 0)
	{
		_size--;
	}
}

template<class T>
void Vector<T>::insert(const int index, const T& data)
{
	if(index >= 0 && index < size)
	{
		if(_size == _capacity)
		{
			if(_capacity == 0) _capacity = 1;
			else _capacity *= 2;
			T* temp = new T[_capacity];
			for(int i = 0; i < size(); i++)
				temp[i] = _data[i];
			delete[] _data;
			_data = temp;
		}
		for(int i = size; i > index; i--)
			_data[i] = _data[i - 1];
		_data[index] = data;
		++_size;
	}
	else cout << "Vector ERROR: INDEX OUT OF BOUNDS1" << endl;
}

template<class T>
void Vector<T>::erase(const int index)
{
	if(index >= 0 && index < size)
	{
		for(int i = index; i < size - 1; i++)
			_data[i] = _data[i + 1];
		--_size;
	}
	else cout << "Vector ERROR: INDEX OUT OF BOUNDS2" << endl;
}

template<class T>
void Vector<T>::clear()
{
	_size = 0;
}

template<class T>
void Vector<T>::resize(const int size)
{
	if(size >= 0)
	{
		if(size > _capacity)
		{
			_capacity = size;
			T* temp = new T[_capacity];
			for(int i = 0; i < _size; i++)
				temp[i] = _data[i];
			delete[] _data;
			_data = temp;
		}
		_size = size;
	}
	else cout << "Vector ERROR: NEGATIVE VALUE IN SIZE DETECTED" << endl;
}

template<class T>
void Vector<T>::resize(const int size, const T& default_value)
{
	if(size >= 0)
	{
		if(size > _capacity)
		{
			_capacity = size;
			T* temp = new T[_capacity];
			for(int i = 0; i < _size; i++)
				temp[i] = _data[i];
			delete[] _data;
			_data = temp;
		}
		for(int i = _size; i < size; i++)
			_data[i] = default_value;
		_size = size;
	}
	else cout << "Vector ERROR: NEGATIVE VALUE IN SIZE DETECTED" << endl;
}

template<class T>
const int Vector<T>::size() const
{
	return _size;
}

template<class T>
const int Vector<T>::capacity() const
{
	return _capacity;
}

template<class T>
T& Vector<T>::operator[](const int index)
{
	if(index >= 0 && index < _size)
	{
		return _data[index];
	}
	else cout << "Vector ERROR: INDEX OUT OF BOUNDS3" << index << endl;

	return _data[0];
}

template<class T>
T& Vector<T>::at(const int index)
{
	if(index >= 0 && index < _size)
	{
		return _data[index];
	}
	else cout << "Vector ERROR: INDEX OUT OF BOUNDS4" << endl;

	return _data[0];
}

#endif