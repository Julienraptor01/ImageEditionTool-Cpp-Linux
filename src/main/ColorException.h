#ifndef ColorException_H
#define ColorException_H

#include "Exception.h"

class ColorException : public Exception
{
private:
	// this value will never be used so i can safely use it for testing if the value is default or not
	int valeur = 1;

public:
	ColorException();
	~ColorException();
	ColorException(const string &message, const int valeur);
	ColorException(const ColorException &ColorException);

	void setValeur(const int valeur);
	int getValeur() const;

	void Affiche() const;
};

#endif
