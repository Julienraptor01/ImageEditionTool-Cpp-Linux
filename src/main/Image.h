#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>

#include "Dimension.h"

using std::string;
using std::istream;
using std::ostream;

class Image
{
protected:
	int id;
	string nom;
	Dimension dimension;

public:
	void setId(int id);
	int getId()const;
	void setNom(const string &nom);
	string getNom()const;
	void setDimension(const Dimension &dimension);
	Dimension getDimension()const;

	void Affiche()const;
	void Dessine()const;

	void exportToFile(const string &nomFichier, const string &formatFichier)const;
};

#endif