#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

using std::string;

class Exception
{
protected:
	string message;

public:
	Exception();
	virtual ~Exception();
	Exception(const string &message);
	Exception(const Exception &exception);

	void setMessage(const string &message);
	string getMessage() const;

	void Affiche() const;
};

#endif
