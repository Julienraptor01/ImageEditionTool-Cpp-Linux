#include "ArrayList.h"

#include <iostream>

using std::cout;
using std::endl;

template <class T> void ArrayList<T>::clearList()
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[35;43mDEBUGVERYVERBOSE : clearList de ArrayList\033[0m" << endl;
#endif
	if (head != nullptr)
	{
		node<T> *currentNode = head;
		node<T> *nextNode = nullptr;
		while (currentNode != nullptr)
		{
			nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}
	}
}

template <class T> void ArrayList<T>::copyList(const ArrayList &arrayList)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[35;43mDEBUGVERYVERBOSE : copyList de ArrayList\033[0m" << endl;
#endif
	node<T> *currentNode = arrayList.head;
	while (currentNode != nullptr)
	{
		insereElement(currentNode->data);
		currentNode = currentNode->next;
	}
}

template <class T> ArrayList<T>::ArrayList()
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;42mDEBUGVERYVERBOSE : Constructeur par défaut de ArrayList\033[0m" << endl;
#endif
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;42mDEBUGVERYVERBOSE : Fin Constructeur par défaut de ArrayList\033[0m" << endl;
#endif
}

template <class T> ArrayList<T>::~ArrayList()
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;41mDEBUGVERYVERBOSE : Destructeur de ArrayList\033[0m" << endl;
#endif
	clearList();
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;41mDEBUGVERYVERBOSE : Fin Destructeur de ArrayList\033[0m" << endl;
#endif
}

template <class T> ArrayList<T>::ArrayList(const ArrayList &arrayList)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;42mDEBUGVERYVERBOSE : Constructeur de copie de ArrayList\033[0m" << endl;
#endif
	copyList(arrayList);
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;42mDEBUGVERYVERBOSE : Fin Constructeur de copie de ArrayList\033[0m" << endl;
#endif
}

template <class T> ArrayList<T> &ArrayList<T>::operator=(const ArrayList &arrayList)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur d'affectation de ArrayList\033[0m" << endl;
#endif
	clearList();
	copyList(arrayList);
	return *this;
}

template <class T> void ArrayList<T>::insereElement(const T &data)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : insereElement de ArrayList\033[0m" << endl;
#endif
	node<T> *newNode = new node<T>;
	newNode->data = data;
	if (head == nullptr)
		head = newNode;
	else
	{
		node<T> *currentNode = head;
		while (currentNode->next != nullptr)
		{
			currentNode = currentNode->next;
		}
		currentNode->next = newNode;
	}
}

template <class T> T &ArrayList<T>::getElement(int index) const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : getElement de ArrayList\033[0m" << endl;
#endif
	node<T> *currentNode = head;
	for (int i = 0; i < index; i++)
	{
		currentNode = currentNode->next;
	}
	return currentNode->data;
}

template <class T> T ArrayList<T>::retireElement(int index)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : retireElement de ArrayList\033[0m" << endl;
#endif
	node<T> *currentNode = head;
	node<T> *previousNode = nullptr;
	for (int i = 0; i < index; i++)
	{
		previousNode = currentNode;
		currentNode = currentNode->next;
	}
	if (previousNode == nullptr)
		head = currentNode->next;
	else
		previousNode->next = currentNode->next;
	T data = currentNode->data;
	delete currentNode;
	return data;
}

template <class T> bool ArrayList<T>::estVide() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : estVide de ArrayList\033[0m" << endl;
#endif
	return head == nullptr;
}

template <class T> int ArrayList<T>::getNombreElements() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : getNombreElements de ArrayList\033[0m" << endl;
#endif
	int size = 0;
	node<T> *currentNode = head;
	while (currentNode != nullptr)
	{
		size++;
		currentNode = currentNode->next;
	}
	return size;
}

template <class T> void ArrayList<T>::Affiche() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : Affiche de ArrayList\033[0m" << endl;
#endif
	node<T> *currentNode = head;
	while (currentNode != nullptr)
	{
		cout << currentNode->data << endl;
		currentNode = currentNode->next;
	}
}

template class ArrayList<int>;
#include "Couleur.h"
template class ArrayList<Couleur>;