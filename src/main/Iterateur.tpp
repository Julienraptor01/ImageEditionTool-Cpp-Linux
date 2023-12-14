#include "Iterateur.h"

template <class T> Iterateur<T>::Iterateur(const ArrayList<T> &arrayList) : arrayList(arrayList)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;42mDEBUGVERYVERBOSE : Constructeur de Iterateur\033[0m" << endl;
#endif
	current = arrayList.head;
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;42mDEBUGVERYVERBOSE : Fin Constructeur de Iterateur\033[0m" << endl;
#endif
}

template <class T> Iterateur<T>::~Iterateur()
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;41mDEBUGVERYVERBOSE : Destructeur de Iterateur\033[0m" << endl;
#endif
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;41mDEBUGVERYVERBOSE : Fin Destructeur de Iterateur\033[0m" << endl;
#endif
}

template <class T> bool Iterateur<T>::operator++()
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de pré-incrémentation de Iterateur\033[0m" << endl;
#endif
	if (current != nullptr)
	{
		current = current->next;
		return true;
	}
	else
		return false;
}

template <class T> bool Iterateur<T>::operator++(int)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de post-incrémentation de Iterateur\033[0m" << endl;
#endif
	return operator++();
}

template <class T> Iterateur<T>::operator T() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de casting de Iterateur\033[0m" << endl;
#endif
	if (current != nullptr)
		return current->data;
	else
		//throw Exception("L'itérateur est à la fin de la liste");
		//without Exception
		throw "L'itérateur est à la fin de la liste";
}

template <class T> T &Iterateur<T>::operator&() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de référence de Iterateur\033[0m" << endl;
#endif
	if (current != nullptr)
		return current->data;
	else
		//throw Exception("L'itérateur est à la fin de la liste");
		//without Exception
		throw "L'itérateur est à la fin de la liste";
}

template <class T> void Iterateur<T>::reset()
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : reset de Iterateur\033[0m" << endl;
#endif
	current = arrayList.head;
}

template <class T> bool Iterateur<T>::end() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : end de Iterateur\033[0m" << endl;
#endif
	return (current == nullptr);
}
