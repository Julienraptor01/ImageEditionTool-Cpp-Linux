#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>

#include "Dimension.h"

using std::ifstream;
using std::ofstream;
using std::string;

class Image
{
protected:
	int id;
	string nom;
	Dimension dimension;

public:
	Image();
	virtual ~Image();
	Image(int id);
	Image(const Image &image);

	void setId(int id);
	int getId() const;
	void setNom(const string &nom);
	string getNom() const;
	virtual void setDimension(const Dimension &dimension) = 0;
	Dimension getDimension() const;

	void Affiche() const;
	virtual void Dessine() const = 0;

	virtual void exportToFile(const string &nomFichier, const string &formatFichier) const = 0;

	void Save(ofstream &fichier) const;
	void Load(ifstream &fichier);
};

#endif
