#include "SortedArrayList.h"

template <class T> SortedArrayList<T>::SortedArrayList() : ArrayList<T>()
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;42mDEBUGVERYVERBOSE : Constructeur par défaut de SortedArrayList\033[0m" << endl;
#endif
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;42mDEBUGVERYVERBOSE : Fin Constructeur par défaut de SortedArrayList\033[0m" << endl;
#endif
}

template <class T> SortedArrayList<T>::~SortedArrayList()
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;41mDEBUGVERYVERBOSE : Destructeur de SortedArrayList\033[0m" << endl;
#endif
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;41mDEBUGVERYVERBOSE : Fin Destructeur de SortedArrayList\033[0m" << endl;
#endif
}

template <class T> SortedArrayList<T>::SortedArrayList(const SortedArrayList &sortedArrayList) : ArrayList<T>(sortedArrayList)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;42mDEBUGVERYVERBOSE : Constructeur de copie de SortedArrayList\033[0m" << endl;
#endif
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;42mDEBUGVERYVERBOSE : Fin Constructeur de copie de SortedArrayList\033[0m" << endl;
#endif
}

template <class T> SortedArrayList<T> &SortedArrayList<T>::operator=(const SortedArrayList &sortedArrayList)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur d'affectation de SortedArrayList\033[0m" << endl;
#endif
	ArrayList<T>::operator=(sortedArrayList);
	return *this;
}

template <class T> void SortedArrayList<T>::insereElement(const T &data)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : insereElement de SortedArrayList\033[0m" << endl;
#endif
	/*
	node<T> *newNode = new node<T>;
	newNode->data = data;
	*/
	node<T> *newNode = new node<T>{data};
	if (this->head == nullptr)
	{
		this->head = newNode;
	}
	else
	{
		node<T> *currentNode = this->head;
		node<T> *previousNode = nullptr;
		while (currentNode != nullptr && currentNode->data <= data)
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
		if (previousNode == nullptr)
		{
			newNode->next = this->head;
			this->head = newNode;
		}
		else
		{
			previousNode->next = newNode;
			newNode->next = currentNode;
		}
	}
}
