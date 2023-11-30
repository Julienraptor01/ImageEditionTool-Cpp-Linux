#include <iostream>

#include "Exception.h"

using std::cout;
using std::endl;

Exception::Exception()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur par défaut de Exception\033[0m" << endl;
#endif
	setMessage("Unspecified exception");
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur par défaut de Exception\033[0m" << endl;
#endif
}

Exception::~Exception()
{
#ifdef DEBUG
	cout << "\033[32;41mDEBUG : Destructeur de Exception\033[0m" << endl;
#endif
#ifdef DEBUG
	cout << "\033[34;41mDEBUG : Fin Destructeur de Exception\033[0m" << endl;
#endif
}

Exception::Exception(const string &message)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation complet de Exception\033[0m" << endl;
#endif
	setMessage(message);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de Exception\033[0m" << endl;
#endif
}

Exception::Exception(const Exception &exception)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur de copie de Exception\033[0m" << endl;
#endif
	setMessage(exception.getMessage());
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur de copie de Exception\033[0m" << endl;
#endif
}

void Exception::setMessage(const string &message)
{
#ifdef DEBUG
	cout << "\033[31;44mDEBUG : setMessage de Exception\033[0m" << endl;
#endif
	this->message = message;
}

string Exception::getMessage() const
{
#ifdef DEBUG
	cout << "\033[32;44mDEBUG : getMessage de Exception\033[0m" << endl;
#endif
	return message;
}

void Exception::Affiche() const
{
	cout << "Exception : " << message << endl;
}
