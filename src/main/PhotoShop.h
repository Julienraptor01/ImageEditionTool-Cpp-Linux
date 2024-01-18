#ifndef PHOTOSHOP_H
#define PHOTOSHOP_H

#include "ArrayList.h"
#include "Image.h"

class PhotoShop
{
private:
	static PhotoShop *instance;
	ArrayList<Image *> images;
	static int currentId;

	PhotoShop();
	PhotoShop(const PhotoShop &photoShop) = delete;

	PhotoShop &operator=(const PhotoShop &photoShop) = delete;

public:
	~PhotoShop();

	static PhotoShop &getInstance();

	void reset();
	void ajouteImage(Image *image);

	void afficheImages() const;
	void dessineImages() const;

	Image *getImageParIndice(int index) const;
	Image *getImageParId(int id) const;

	ArrayList<Image *> getImages() const;

	void supprimeImageParIndice(int index);
	void supprimeImageParId(int id);

	static Image *operande1;
	static Image *operande2;
	static Image *resultat;
};

#endif
