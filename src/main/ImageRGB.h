#ifndef IMAGERGB_H
#define IMAGERGB_H

#include <iostream>

#include "Image.h"
#include "Couleur.h"

using std::ostream;
using std::string;

class ImageRGB : public Image
{
private:
	Couleur **matrice = nullptr;

	void createMatrice();
	void freeMatrice(Couleur **matrice, const Dimension &dimension);
	void freeMatrice();
	void copyMatrice(Couleur **matrice, const Dimension &dimension, Couleur **matriceToCopy, const Dimension &dimensionOfMatriceToCopy);
	void copyMatrice(const ImageRGB &image);

public:
	ImageRGB();
	~ImageRGB();
	ImageRGB(int id, const string &nom, const Dimension &dimension);
	ImageRGB(int id, const string &nom);
	ImageRGB(const string &nom);
	ImageRGB(const ImageRGB &image);

	ImageRGB &operator=(const ImageRGB &image);
	friend ostream &operator<<(ostream &outputStream, const ImageRGB &image);

	void setDimension(const Dimension &dimension) override;
	void setBackground(const Couleur &couleur);
	void setPixel(int x, int y, const Couleur &couleur);
	Couleur getPixel(int x, int y) const;

	void Dessine() const override;

	void importFromFile(const string &nomFichier);
	void exportToFile(const string &nomFichier, const string &formatFichier) const override;
};

#endif
