#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template <class T> struct node
{
	T data;
	node<T> *next = nullptr;
};

template <class T> class ArrayList
{
private:
	node<T> *head = nullptr;

	void clearList();
	void copyList(const ArrayList &arrayList);

public:
	ArrayList();
	~ArrayList();
	ArrayList(const ArrayList &arrayList);

	ArrayList &operator=(const ArrayList &arrayList);

	void insereElement(const T &data);
	T &getElement(int index) const;
	T retireElement(int index);

	bool estVide() const;
	int getNombreElements() const;

	void Affiche() const;
};

#endif
