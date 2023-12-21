#ifndef IMAGEB_H
#define IMAGEB_H

#include <iostream>

#include "Image.h"
#include "Couleur.h"

using std::ostream;

class ImageB : public Image
{
private:
	bool **matrice = nullptr;

	void createMatrice();
	void freeMatrice(bool **matrice, const Dimension &dimension);
	void freeMatrice();
	void copyMatrice(bool **matrice, const Dimension &dimension, bool **matriceToCopy, const Dimension &dimensionOfMatriceToCopy);
	void copyMatrice(const ImageB &image);

public:
	ImageB();
	~ImageB();
	ImageB(int id, const string &nom, const Dimension &dimension);
	ImageB(int id, const string &nom);
	ImageB(const string &nom);
	ImageB(const ImageB &image);

	ImageB &operator=(const ImageB &image);
	friend ostream &operator<<(ostream &outputStream, const ImageB &image);

	void setDimension(const Dimension &dimension) override;
	void setBackground(bool couleur);
	void setPixel(int x, int y, bool couleur);
	bool getPixel(int x, int y) const;

	static Couleur couleurFalse;
	static Couleur couleurTrue;

	void Dessine() const override;

	void exportToFile(const string &nomFichier, const string &formatFichier) const override;

	void Save(ofstream &fichier) const;
	void Load(ifstream &fichier);
};

#endif
