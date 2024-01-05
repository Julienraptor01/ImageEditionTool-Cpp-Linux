#include "PhotoShop.h"

#include <iostream>

#include "Iterateur.h"

using std::cout;
using std::endl;

PhotoShop *PhotoShop::instance = new PhotoShop();

int PhotoShop::currentId = 1;

PhotoShop::PhotoShop()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur par défaut de PhotoShop\033[0m" << endl;
#endif
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur par défaut de PhotoShop\033[0m" << endl;
#endif
}

PhotoShop::~PhotoShop()
{
#ifdef DEBUG
	cout << "\033[32;41mDEBUG : Destructeur de PhotoShop\033[0m" << endl;
#endif
	reset();
#ifdef DEBUG
	cout << "\033[34;41mDEBUG : Fin Destructeur de PhotoShop\033[0m" << endl;
#endif
}

PhotoShop &PhotoShop::getInstance()
{
#ifdef DEBUGVERBOSE
	cout << "\033[32;44mDEBUGVERBOSE : getInstance de PhotoShop\033[0m" << endl;
#endif
	return *instance;
}

void PhotoShop::reset()
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : reset de PhotoShop\033[0m" << endl;
#endif
	while (!images.estVide())
	{
		Image *imageToDelete = images.retireElement(0);
		delete imageToDelete;
	}
	currentId = 1;
}

void PhotoShop::ajouteImage(Image *image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : ajouteImage de PhotoShop\033[0m" << endl;
#endif
	image->setId(currentId);
	currentId++;
	images.insereElement(image);
}

void PhotoShop::afficheImages() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : afficheImages de PhotoShop\033[0m" << endl;
#endif
	for (Iterateur<Image *> iterateur(images); !iterateur.end(); iterateur++)
		(static_cast<Image *>(iterateur))->Affiche();
}

void PhotoShop::dessineImages() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : dessineImages de PhotoShop\033[0m" << endl;
#endif
	for (Iterateur<Image *> iterateur(images); !iterateur.end(); iterateur++)
		(static_cast<Image *>(iterateur))->Dessine();
}

Image *PhotoShop::getImageParIndice(int index) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : getImageParIndice de PhotoShop\033[0m" << endl;
#endif
	return images.getElement(index);
}

Image *PhotoShop::getImageParId(int id) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : getImageParId de PhotoShop\033[0m" << endl;
#endif
	for (Iterateur<Image *> iterateur(images); !iterateur.end(); iterateur++)
		if ((static_cast<Image *>(iterateur))->getId() == id)
			return static_cast<Image *>(iterateur);
	return nullptr;
}

void PhotoShop::supprimeImageParIndice(int index)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : supprimeImageParIndice de PhotoShop\033[0m" << endl;
#endif
	Image *imageToDelete = images.retireElement(index);
	delete imageToDelete;
}

void PhotoShop::supprimeImageParId(int id)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : supprimeImageParId de PhotoShop\033[0m" << endl;
#endif
	Iterateur<Image *> iterateur(images);
	for (int index = 0; !iterateur.end(); iterateur++, index++)
		if ((static_cast<Image *>(iterateur))->getId() == id)
		{
			Image *imageToDelete = images.retireElement(index);
			delete imageToDelete;
			return;
		}
}
