#ifndef IMAGENG_H
#define IMAGENG_H

#include "Dimension.h"

class ImageNG
{
private:
	int id;
	char * nom = NULL;
	Dimension dimension;

public:
	ImageNG();
	~ImageNG();
	ImageNG(int id, const char *nom, const Dimension &dimension);
	ImageNG(int id, const char *nom);
	ImageNG(const ImageNG &image);

	void Affiche()const;

	void setId(int id);
	int getId()const;
	void setNom(const char *nom);
	char *getNom()const;
	void setDimension(const Dimension &dimension);
	Dimension getDimension()const;
};

#endif
