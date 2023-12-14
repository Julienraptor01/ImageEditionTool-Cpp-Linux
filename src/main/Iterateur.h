#ifndef ITERATEUR_H
#define ITERATEUR_H

#include "ArrayList.h"

template <class T> class Iterateur
{
private:
	const ArrayList<T> &arrayList;
	node<T> *current = nullptr;

public:
	Iterateur(const ArrayList<T> &arrayList);
	~Iterateur();

	bool operator++();
	bool operator++(int);
	operator T() const;
	T &operator&() const;

	void reset();
	bool end() const;
};

//#include "Iterateur.tpp"

#endif
