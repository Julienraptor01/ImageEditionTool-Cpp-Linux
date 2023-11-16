#include <iostream>

#include "RGBException.h"

using std::cout;
using std::endl;

RGBException::RGBException() : Exception()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur par défaut de RGBException\033[0m" << endl;
#endif
	setMessage("Exception RGB non spécifiée");
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur par défaut de RGBException\033[0m" << endl;
#endif
}

RGBException::~RGBException()
{
#ifdef DEBUG
	cout << "\033[32;41mDEBUG : Destructeur de RGBException\033[0m" << endl;
#endif
#ifdef DEBUG
	cout << "\033[34;41mDEBUG : Fin Destructeur de RGBException\033[0m" << endl;
#endif
}

RGBException::RGBException(const string &message, const int valeur) : Exception(message)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation complet de RGBException\033[0m" << endl;
#endif
	setValeur(valeur);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de RGBException\033[0m" << endl;
#endif
}

RGBException::RGBException(const RGBException &rgbException) : Exception(rgbException)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur de copie de RGBException\033[0m" << endl;
#endif
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur de copie de RGBException\033[0m" << endl;
#endif
}

void RGBException::setValeur(const int valeur)
{
#ifdef DEBUG
	cout << "\033[31;44mDEBUG : setValeur de RGBException\033[0m" << endl;
#endif
	this->valeur = valeur;
}

int RGBException::getValeur() const
{
#ifdef DEBUG
	cout << "\033[31;44mDEBUG : getValeur de RGBException\033[0m" << endl;
#endif
	return valeur;
}

void RGBException::Affiche() const
{
	cout << "RGBException : " << message;
	if (valeur != NULL)
		cout << "\t" << "Valeur : " << valeur;
	cout << endl;
}
