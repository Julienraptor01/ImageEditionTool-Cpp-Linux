#ifndef XYEXCEPTION_H
#define XYEXCEPTION_H

#include "Exception.h"

class XYException : public Exception
{
private:
	// theses values will never be used so i can safely use them for testing if the value is default or not
	char axe = 0;
	int x = 1, y = 1;

public:
	XYException();
	~XYException();
	XYException(const string &message, const char axe, const int x, const int y);
	XYException(const string &message, const char axe, const int valeur);
	XYException(const string &message, const char axe);
	XYException(const XYException &xyException);

	void setAxe(const char axe);
	char getAxe() const;
	void setX(const int x);
	int getX() const;
	void setY(const int y);
	int getY() const;

	void Affiche() const;
};

#endif
