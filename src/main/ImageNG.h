#ifndef IMAGENG_H
#define IMAGENG_H

#include <iostream>

#include "Image.h"
#include "Dimension.h"

using std::string;
using std::istream;
using std::ostream;

class ImageNG : public Image
{
private:
	unsigned char ** matrice = nullptr;

	void createMatrice();
	void freeMatrice(unsigned char **matrice, const Dimension &dimension);
	void freeMatrice();
	void copyMatrice(unsigned char **matrice, const Dimension &dimension, unsigned char** matriceToCopy, const Dimension &dimensionOfMatriceToCopy);
	void copyMatrice(const ImageNG &image);

public:
	ImageNG();
	~ImageNG();
	ImageNG(int id, const string &nom, const Dimension &dimension);
	ImageNG(int id, const string &nom);
	ImageNG(const string &nom);
	ImageNG(const ImageNG &image);

	ImageNG& operator=(const ImageNG &image);
	ImageNG operator+(unsigned char grayLevel)const;
	friend ImageNG operator+(unsigned char grayLevel, const ImageNG &image);
	ImageNG operator+(const ImageNG &image)const;
	ImageNG operator-(unsigned char grayLevel)const;
	friend ImageNG operator-(unsigned char grayLevel, const ImageNG &image);
	ImageNG operator-(const ImageNG &image)const;
	ImageNG& operator++();
	ImageNG operator++(int);
	ImageNG& operator--();
	ImageNG operator--(int);
	bool operator==(const ImageNG &image)const;
	bool operator!=(const ImageNG &image)const;
	bool operator<(const ImageNG &image)const;
	bool operator<=(const ImageNG &image)const;
	bool operator>(const ImageNG &image)const;
	bool operator>=(const ImageNG &image)const;
	friend ostream& operator<<(ostream &outputStream, const ImageNG &image);

	void setDimension(const Dimension &dimension);
	void setBackground(unsigned char grayLevel);
	void setPixel(int x, int y, unsigned char grayLevel);
	int getPixel(int x, int y)const;

	int getLuminance()const;
	int getMinimum()const;
	int getMaximum()const;
	float getContraste()const;

	void importFromFile(const string &nomFichier);
};

#endif
