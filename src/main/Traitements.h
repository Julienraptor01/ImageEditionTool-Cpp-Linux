#ifndef TRAITEMENTS_H
#define TRAITEMENTS_H

#include "ImageNG.h"
#include "ImageB.h"

class Traitements
{
public:
	static ImageB Seuillage(const ImageNG& imageIn, int threshold);
	static ImageNG FiltreMoyenneur(const ImageNG& imageIn, int size);
	static ImageNG FiltreMedian(const ImageNG& imageIn, int size);
	static ImageNG Erosion(const ImageNG& imageIn, int size);
	static ImageNG Dilatation(const ImageNG& imageIn, int size);
	static ImageNG Negatif(const ImageNG& imageIn);
};

#endif
