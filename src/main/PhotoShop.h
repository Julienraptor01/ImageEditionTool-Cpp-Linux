#ifndef PHOTOSHOP_H
#define PHOTOSHOP_H

#include "ArrayList.h"
#include "Image.h"

class PhotoShop
{
private:
		ArrayList<Image*> images;
		static int currentId;

	public:
		PhotoShop();
		~PhotoShop();

		void reset();
		void ajouteImage(Image *image);

		void afficheImages() const;
		void dessineImages() const;

		Image *getImageParIndice(int index) const;
		Image *getImageParId(int id) const;

	void supprimeImageParIndice(int index);
	void supprimeImageParId(int id);
};

#endif
