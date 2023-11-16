#ifndef XYEXCEPTION_H
#define XYEXCEPTION_H

#include "Exception.h"

class XYException : public Exception
{
private:
	char axe = NULL;
	int x = NULL, y = NULL;

public:
	XYException();
	~XYException();
	XYException(const string &message);
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
