#ifndef IMAGENG_H
#define IMAGENG_H

#include "Dimension.h"

class ImageNG
{
private:
	int id;
	char * nom = NULL;
	Dimension dimension;
	int ** matrice = nullptr;

	void freeNom();
	void createMatrice();
	void freeMatrice();

public:
	ImageNG();
	~ImageNG();
	ImageNG(int id, const char *nom, const Dimension &dimension);
	ImageNG(int id, const char *nom);
	ImageNG(const ImageNG &image);

	void setId(int id);
	int getId()const;
	void setNom(const char *nom);
	char *getNom()const;
	void setDimension(const Dimension &dimension);
	Dimension getDimension()const;
	void setBackground(int couleur);
	void setPixel(int x, int y, int couleur);
	int getPixel(int x, int y)const;

	void Affiche()const;
	void Dessine()const;

	void importFromFile(const char *nomFichier);
	void exportToFile(const char *nomFichier, const char *formatFichier)const;
};

#endif
