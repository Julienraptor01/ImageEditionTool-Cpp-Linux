#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

using std::string;

/**
 * @author Julienraptor01
 * @brief Rethrow the catched exception to the upper level
 * @param class The class of the exception to rethrow
 * @example RETHROW(XYException), RETHROW(ColorException), RETHROW(Exception)
 */
#define RETHROW(class) \
	catch (class &e) \
	{ \
		throw e; \
	}

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
