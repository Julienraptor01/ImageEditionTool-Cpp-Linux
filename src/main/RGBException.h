#ifndef RGBEXCEPTION_H
#define RGBEXCEPTION_H

#include "Exception.h"

class RGBException : public Exception
{
private:
	int valeur = NULL;

public:
	RGBException();
	~RGBException();
	RGBException(const string &message, const int valeur);
	RGBException(const RGBException &rgbException);

	void setValeur(const int valeur);
	int getValeur() const;

	void Affiche() const;
};

#endif
