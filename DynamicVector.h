#pragma once
#include "Dog.h"
#include <assert.h>

template <typename TElement>
class DynamicVector
{
private:
	TElement* elems;
	int size;
	int capacity;

public:
	DynamicVector(int capacity = 10); //Default constructor for dynamic vector
	DynamicVector(const DynamicVector& v); //Copy constructor for a dynamic vector
	~DynamicVector();
	DynamicVector& operator+(TElement& d);

	DynamicVector& operator-(TElement& d);
	DynamicVector& operator=(const DynamicVector& v); //assignment operator for Dynamic Vector
	void cleanDynamicVector();
	void add(TElement e); //Adds an element to the Dynamic Vector
	void update(TElement e,int pos);
	void deleteOnPos(int pos);


	int getSize() const;

	TElement* getAllElems() const;
private:
	void resize(double factor = 2); //Resizez the current dynamic vector, multiplying its capacity by a given factor






};


template <typename TElement>
DynamicVector<TElement>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elems = new TElement[capacity];
}

template <typename TElement>
void DynamicVector<TElement>::cleanDynamicVector()
{
	this->size = 0;
}

template <typename TElement>
DynamicVector<TElement>::DynamicVector(const DynamicVector& v)
{
	this->size = v.size;
	this->capacity = v.capacity;
	this->elems = new TElement[this->capacity];
	for (int i = 0; i < v.size; i++)
	{
		this->elems[i] = v.elems[i];
	}

}


template <typename TElement>
DynamicVector<TElement>::~DynamicVector()
{
	delete[] this->elems;

}


template <typename TElement>
DynamicVector<TElement>& DynamicVector<TElement>::operator=(const DynamicVector<TElement>& v)
{
	if (this == &v)
		return *this;
	this->size = v.size;
	this->capacity = v.capacity;
	delete[] this->elems;
	this->elems = new TElement[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
	return *this;

}


template <typename TElement>
void DynamicVector<TElement>::add(TElement e)
{

	if (this->size == this->capacity)
		this->resize();
	this->elems[this->size] = e;
	this->size++;

}


template <typename TElement>
void DynamicVector<TElement>::update(TElement e, int pos)
{
	if (pos > this->size)
		return;
	this->elems[pos] = e;
}


template <typename TElement>
void DynamicVector<TElement>::deleteOnPos(int pos)
{
	for (int i = pos; i < this->size - 1; i++)
		this->elems[i] = this->elems[i + 1];
	this->size--;

}


template <typename TElement>
void DynamicVector<TElement>::resize(double factor)
{

	this->capacity *= factor;
	TElement* els = new TElement[this->capacity];
	for (int i = 0; i < this->size; i++)
	{
		els[i] = this->elems[i];
	}
	delete[] this->elems;
	this->elems = els;


}


template <typename TElement>
TElement* DynamicVector<TElement>::getAllElems() const
{
	
	return this->elems;

}

template <typename TElement>
DynamicVector<TElement>& DynamicVector<TElement>::operator+(TElement& d)
{
	this->add(d);
	return *this;

}


template <typename TElement>
DynamicVector<TElement>& DynamicVector<TElement>::operator-(TElement& d)
{

	int exists = 0;
	std::string name = d.getName();
	TElement* elems = this->getAllElems();
	for (int i = 0; i < this->getSize() && exists==0; i++)
	{
		if (elems[i].getName() == d.getName())
		{
			exists = 1;
			this->deleteOnPos(i);

		}
	}
	return *this;

}

template <typename TElement>
int DynamicVector<TElement>::getSize() const
{
	return this->size;

}
template <typename TElement>
DynamicVector<TElement>& operator+(TElement& d, DynamicVector<TElement>& d2) { return d2 + d; }



void testBonus();