#include <iostream>

#include "ColorException.h"

using std::cout;
using std::endl;

ColorException::ColorException() : Exception()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur par défaut de ColorException\033[0m" << endl;
#endif
	setMessage("Exception RGB non spécifiée");
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur par défaut de ColorException\033[0m" << endl;
#endif
}

ColorException::~ColorException()
{
#ifdef DEBUG
	cout << "\033[32;41mDEBUG : Destructeur de ColorException\033[0m" << endl;
#endif
#ifdef DEBUG
	cout << "\033[34;41mDEBUG : Fin Destructeur de ColorException\033[0m" << endl;
#endif
}

ColorException::ColorException(const string &message, const int valeur) : Exception(message)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation complet de ColorException\033[0m" << endl;
#endif
	setValeur(valeur);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de ColorException\033[0m" << endl;
#endif
}

ColorException::ColorException(const ColorException &ColorException) : Exception(ColorException)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur de copie de ColorException\033[0m" << endl;
#endif
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur de copie de ColorException\033[0m" << endl;
#endif
}

void ColorException::setValeur(const int valeur)
{
#ifdef DEBUG
	cout << "\033[31;44mDEBUG : setValeur de ColorException\033[0m" << endl;
#endif
	this->valeur = valeur;
}

int ColorException::getValeur() const
{
#ifdef DEBUG
	cout << "\033[31;44mDEBUG : getValeur de ColorException\033[0m" << endl;
#endif
	return valeur;
}

void ColorException::Affiche() const
{
	cout << "ColorException : " << message;
	if (valeur != 1)
		cout << "\t" << "Valeur : " << valeur;
	cout << endl;
}
