#include "Traitements.h"

#include <iostream>
#include <climits>
#include <cmath>

#include "Exception.h"
#include "ColorException.h"
#include "ArrayList.h"
#include "SortedArrayList.h"

using std::cout;
using std::endl;
using std::min;
using std::max;
using std::to_string;

ImageB Traitements::Seuillage(const ImageNG& imageIn, int threshold)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Seuillage de Traitements\033[0m" << endl;
#endif
	if (threshold < 0 || threshold > UCHAR_MAX)
		throw ColorException("Seuillage invalide", threshold);
	ImageB imageOut(imageIn.getId(), imageIn.getNom() + "-seuil" + to_string(threshold), imageIn.getDimension());
	int width = imageIn.getDimension().getLargeur(), height = imageIn.getDimension().getHauteur();
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			imageOut.setPixel(i, j, imageIn.getPixel(i, j) < threshold);
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Seuillage de Traitements\033[0m" << endl;
#endif
	return imageOut;
}

ImageNG Traitements::FiltreMoyenneur(const ImageNG& imageIn, int size)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : FiltreMoyenneur de Traitements\033[0m" << endl;
#endif
	if (size <= 0)
		throw Exception("La taille du filtre doit être positive");
	if (size % 2 == 0)
		throw Exception("La taille du filtre doit être impaire");
	ImageNG imageOut(imageIn.getId(), imageIn.getNom() + "-moyenne" + to_string(size), imageIn.getDimension());
	int width = imageIn.getDimension().getLargeur(), height = imageIn.getDimension().getHauteur();
	int offset = (size - 1) / 2, sum, pixelCount;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			sum = 0;
			pixelCount = 0;
			for (int k = max(0, i - offset); k <= min(height - 1, i + offset); k++)
				for (int l = max(0, j - offset); l <= min(width - 1, j + offset); l++)
				{
					sum += imageIn.getPixel(k, l);
					pixelCount++;
				}
			imageOut.setPixel(i, j, static_cast<int>(round(static_cast<double>(sum) / pixelCount)));
		}
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin FiltreMoyenneur de Traitements\033[0m" << endl;
#endif
	return imageOut;
}

ImageNG Traitements::FiltreMedian(const ImageNG& imageIn, int size)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : FiltreMedian de Traitements\033[0m" << endl;
#endif
	if (size <= 0)
		throw Exception("La taille du filtre doit être positive");
	if (size % 2 == 0)
		throw Exception("La taille du filtre doit être impaire");
	ImageNG imageOut(imageIn.getId(), imageIn.getNom() + "-median" + to_string(size), imageIn.getDimension());
	int width = imageIn.getDimension().getLargeur(), height = imageIn.getDimension().getHauteur();
	int offset = (size - 1) / 2, median;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			SortedArrayList<int> pixels;
			for (int k = max(0, i - offset); k <= min(height - 1, i + offset); k++)
				for (int l = max(0, j - offset); l <= min(width - 1, j + offset); l++)
					pixels.insereElement(imageIn.getPixel(k, l));
			if (pixels.getNombreElements() % 2 == 1)
				median = pixels.getElement(pixels.getNombreElements() / 2);
			else
				median = static_cast<int>(round((pixels.getElement(pixels.getNombreElements() / 2 - 1) + pixels.getElement(pixels.getNombreElements() / 2)) / 2.0));
			imageOut.setPixel(i, j, median);
		}
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin FiltreMedian de Traitements\033[0m" << endl;
#endif
	return imageOut;
}

ImageNG Traitements::Erosion(const ImageNG& imageIn, int size)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Erosion de Traitements\033[0m" << endl;
#endif
	if (size <= 0)
		throw Exception("La taille du filtre doit être positive");
	if (size % 2 == 0)
		throw Exception("La taille du filtre doit être impaire");
	ImageNG imageOut(imageIn.getId(), imageIn.getNom() + "-erode" + to_string(size), imageIn.getDimension());
	int width = imageIn.getDimension().getLargeur(), height = imageIn.getDimension().getHauteur();
	int offset = (size - 1) / 2;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			int lowest = UCHAR_MAX;
			for (int k = max(0, i - offset); k <= min(height - 1, i + offset); k++)
				for (int l = max(0, j - offset); l <= min(width - 1, j + offset); l++)
					lowest = min(lowest, imageIn.getPixel(k, l));
			imageOut.setPixel(i, j, lowest);
		}
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Erosion de Traitements\033[0m" << endl;
#endif
	return imageOut;
}

ImageNG Traitements::Dilatation(const ImageNG& imageIn, int size)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Dilatation de Traitements\033[0m" << endl;
#endif
	if (size <= 0)
		throw Exception("La taille du filtre doit être positive");
	if (size % 2 == 0)
		throw Exception("La taille du filtre doit être impaire");
	ImageNG imageOut(imageIn.getId(), imageIn.getNom() + "-dilate" + to_string(size), imageIn.getDimension());
	int width = imageIn.getDimension().getLargeur(), height = imageIn.getDimension().getHauteur();
	int offset = (size - 1) / 2;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			int highest = 0;
			for (int k = max(0, i - offset); k <= min(height - 1, i + offset); k++)
				for (int l = max(0, j - offset); l <= min(width - 1, j + offset); l++)
					highest = max(highest, imageIn.getPixel(k, l));
			imageOut.setPixel(i, j, highest);
		}
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Dilatation de Traitements\033[0m" << endl;
#endif
	return imageOut;
}

ImageNG Traitements::Negatif(const ImageNG& imageIn)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Negatif de Traitements\033[0m" << endl;
#endif
	ImageNG imageOut(imageIn.getId(), imageIn.getNom() + "-negatif", imageIn.getDimension());
	int width = imageIn.getDimension().getLargeur(), height = imageIn.getDimension().getHauteur();
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			imageOut.setPixel(i, j, UCHAR_MAX - imageIn.getPixel(i, j));
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Negatif de Traitements\033[0m" << endl;
#endif
	return imageOut;
}
