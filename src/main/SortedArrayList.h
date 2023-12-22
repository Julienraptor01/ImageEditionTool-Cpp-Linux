#ifndef SORTEDARRAYLIST_H
#define SORTEDARRAYLIST_H

#include "ArrayList.h"

template <class T> class SortedArrayList : public ArrayList<T>
{
public:
	SortedArrayList();
	~SortedArrayList();
	SortedArrayList(const SortedArrayList &sortedArrayList);

	SortedArrayList &operator=(const SortedArrayList &sortedArrayList);

	void insereElement(const T &data);
};

#include "SortedArrayList.tpp"

#endif
