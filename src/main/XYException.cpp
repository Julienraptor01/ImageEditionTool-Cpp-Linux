#include <iostream>

#include "XYException.h"

using std::cout;
using std::endl;

XYException::XYException() : Exception()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur par défaut de XYException\033[0m" << endl;
#endif
	setMessage("Exception XY non spécifiée");
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur par défaut de XYException\033[0m" << endl;
#endif
}

XYException::~XYException()
{
#ifdef DEBUG
	cout << "\033[32;41mDEBUG : Destructeur de XYException\033[0m" << endl;
#endif
#ifdef DEBUG
	cout << "\033[34;41mDEBUG : Fin Destructeur de XYException\033[0m" << endl;
#endif
}

XYException::XYException(const string &message, const char axe, const int x, const int y) : Exception(message)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation complet de XYException\033[0m" << endl;
#endif
	setAxe(axe);
	setX(x);
	setY(y);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de XYException\033[0m" << endl;
#endif
}

XYException::XYException(const string &message, const char axe, const int valeur) : Exception(message)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation partiel de XYException\033[0m" << endl;
#endif
	setAxe(axe);
	switch (axe)
	{
	case 'x':
		setX(valeur);
		break;
	case 'y':
		setY(valeur);
		break;
	default:
		cout << "You misused the constructor of XYException" << endl;
	}
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de XYException\033[0m" << endl;
#endif
}

XYException::XYException(const XYException &xyException) : Exception(xyException)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur de copie de XYException\033[0m" << endl;
#endif
	setAxe(xyException.getAxe());
	setX(xyException.getX());
	setY(xyException.getY());
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur de copie de XYException\033[0m" << endl;
#endif
}

void XYException::setAxe(const char axe)
{
#ifdef DEBUG
	cout << "\033[31;44mDEBUG : setAxe de XYException\033[0m" << endl;
#endif
	this->axe = axe;
}

char XYException::getAxe() const
{
#ifdef DEBUG
	cout << "\033[32;44mDEBUG : getAxe de XYException\033[0m" << endl;
#endif
	return axe;
}

void XYException::setX(const int x)
{
#ifdef DEBUG
	cout << "\033[31;44mDEBUG : setX de XYException\033[0m" << endl;
#endif
	this->x = x;
}

int XYException::getX() const
{
#ifdef DEBUG
	cout << "\033[32;44mDEBUG : getX de XYException\033[0m" << endl;
#endif
	return x;
}

void XYException::setY(const int y)
{
#ifdef DEBUG
	cout << "\033[31;44mDEBUG : setY de XYException\033[0m" << endl;
#endif
	this->y = y;
}

int XYException::getY() const
{
#ifdef DEBUG
	cout << "\033[32;44mDEBUG : getY de XYException\033[0m" << endl;
#endif
	return y;
}

void XYException::Affiche() const
{
	cout << "XYException : " << message;
	if (axe != NULL)
		cout << "\t" << "Axe : " << axe;
	if (axe == 'x' || axe == 'd')
		cout << "\t" << "X : " << x;
	if (axe == 'y' || axe == 'd')
		cout << "\t" << "Y : " << y;
	cout << endl;
}
