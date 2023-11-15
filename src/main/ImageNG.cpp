#include <regex>
#include <algorithm>
#include <limits.h>

#include "ImageNG.h"
#include "MyQT.h"

using std::cout;
using std::endl;
using std::regex;
using std::regex_search;
using std::regex_replace;
using std::clamp;

void ImageNG::createMatrice()
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : createMatrice de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	matrice = new unsigned char*[largeur];
	for(int i=0; i<largeur; i++)
	{
		matrice[i] = new unsigned char[hauteur];
		for(int j=0; j<hauteur; j++)
			matrice[i][j] = 0x00;
	}
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin createMatrice de ImageNG\033[0m"<<endl;
#endif
}

void ImageNG::freeMatrice(unsigned char **matrice, const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : freeMatrice de ImageNG (matrice, dimension)\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	for(int i=0; i<largeur; i++)
		delete[] matrice[i];
	delete[] matrice;
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin freeMatrice de ImageNG (matrice, dimension)\033[0m"<<endl;
#endif
}

void ImageNG::freeMatrice()
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : freeMatrice de ImageNG\033[0m"<<endl;
#endif
	freeMatrice(matrice, dimension);
	matrice = nullptr;
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin freeMatrice de ImageNG\033[0m"<<endl;
#endif
}

void ImageNG::copyMatrice(unsigned char **matrice, const Dimension &dimension, unsigned char **matriceToCopy, const Dimension &dimensionOfMatriceToCopy)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : copyMatrice de ImageNG (matrice, dimension, matriceToCopy, dimensionOfMatriceToCopy)\033[0m"<<endl;
#endif
	int minLargeur = (dimension.getLargeur() < dimensionOfMatriceToCopy.getLargeur()) ? dimension.getLargeur() : dimensionOfMatriceToCopy.getLargeur();
	int minHauteur = (dimension.getHauteur() < dimensionOfMatriceToCopy.getHauteur()) ? dimension.getHauteur() : dimensionOfMatriceToCopy.getHauteur();
	for(int i=0; i<minLargeur; i++)
		for(int j=0; j<minHauteur; j++)
			matrice[i][j] = matriceToCopy[i][j];
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin copyMatrice de ImageNG (matrice, dimension, matriceToCopy, dimensionOfMatriceToCopy)\033[0m"<<endl;
#endif
}

void ImageNG::copyMatrice(const ImageNG &image)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : copyMatrice de ImageNG (image)\033[0m"<<endl;
#endif
	copyMatrice(matrice,dimension,image.matrice,image.dimension);
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin copyMatrice de ImageNG (image)\033[0m"<<endl;
#endif
}

ImageNG::ImageNG() : Image()
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur par défaut de ImageNG\033[0m"<<endl;
#endif
	setNom("ImageNG sans nom");
	setDimension(dimension);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur par défaut de ImageNG\033[0m"<<endl;
#endif
}

ImageNG::~ImageNG()
{
#ifdef DEBUG
	cout<<"\033[32;41mDEBUG : Destructeur de ImageNG\033[0m"<<endl;
#endif
	if(matrice != nullptr)
		freeMatrice();
#ifdef DEBUG
	cout<<"\033[34;41mDEBUG : Fin Destructeur de ImageNG\033[0m"<<endl;
#endif
}

ImageNG::ImageNG(int id, const string &nom, const Dimension &dimension) : Image(id)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur d'initialisation complet de ImageNG\033[0m"<<endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1") : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de ImageNG\033[0m"<<endl;
#endif
}

ImageNG::ImageNG(int id, const string &nom) : Image(id)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur d'initialisation partiel de ImageNG (id, nom)\033[0m"<<endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1") : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de ImageNG (id, nom)\033[0m"<<endl;
#endif
}

ImageNG::ImageNG(const string &nom) : Image()
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur d'initialisation partiel de ImageNG (nom)\033[0m"<<endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1") : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de ImageNG (nom)\033[0m"<<endl;
#endif
}

ImageNG::ImageNG(const ImageNG &image) : Image(image)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur de copie de ImageNG\033[0m"<<endl;
#endif
	setDimension(image.getDimension());
	copyMatrice(image);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur de copie de ImageNG\033[0m"<<endl;
#endif
}

ImageNG& ImageNG::operator=(const ImageNG &image)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur d'affectation de ImageNG\033[0m"<<endl;
#endif
	setId(image.getId());
	setNom(image.getNom());
	setDimension(image.getDimension());
	copyMatrice(image);
	return *this;
}

ImageNG ImageNG::operator+(unsigned char grayLevel)const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur d'addition de ImageNG (grayLevel)\033[0m"<<endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			image.setPixel(i, j, image.getPixel(i, j) + grayLevel);
	return image;
}

ImageNG operator+(unsigned char grayLevel, const ImageNG &image)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;46mDEBUGVERBOSE : Opérateur d'addition de ImageNG (grayLevel, image)\033[0m"<<endl;
#endif
	return image + grayLevel;
}

ImageNG ImageNG::operator+(const ImageNG &image)const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur d'addition de ImageNG (image)\033[0m"<<endl;
#endif
	ImageNG imageToReturn(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			imageToReturn.setPixel(i, j, imageToReturn.getPixel(i, j) + image.getPixel(i, j));
	return imageToReturn;
}

ImageNG ImageNG::operator-(unsigned char grayLevel)const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de soustraction de ImageNG (grayLevel)\033[0m"<<endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			image.setPixel(i, j, image.getPixel(i, j) - grayLevel);
	return image;
}

ImageNG operator-(unsigned char grayLevel, const ImageNG &image)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;46mDEBUGVERBOSE : Opérateur de soustraction de ImageNG (grayLevel, image)\033[0m"<<endl;
#endif
	ImageNG imageToReturn(image);
	int largeur = image.dimension.getLargeur();
	int hauteur = image.dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			imageToReturn.setPixel(i, j, grayLevel - imageToReturn.getPixel(i, j));
	return imageToReturn;
}

ImageNG ImageNG::operator-(const ImageNG &image)const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de soustraction de ImageNG (image)\033[0m"<<endl;
#endif
	ImageNG imageToReturn(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			imageToReturn.setPixel(i, j, imageToReturn.getPixel(i, j) - image.getPixel(i, j));
	return imageToReturn;
}

ImageNG& ImageNG::operator++()
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de pré-incrémentation de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			setPixel(i, j, getPixel(i, j) + 20);
	return *this;
}

ImageNG ImageNG::operator++(int)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de post-incrémentation de ImageNG\033[0m"<<endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			setPixel(i, j, getPixel(i, j) + 20);
	return image;
}

ImageNG& ImageNG::operator--()
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de pré-décrémentation de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			setPixel(i, j, getPixel(i, j) - 20);
	return *this;
}

ImageNG ImageNG::operator--(int)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de post-décrémentation de ImageNG\033[0m"<<endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			setPixel(i, j, getPixel(i, j) - 20);
	return image;
}

bool ImageNG::operator==(const ImageNG &image)const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur d'égalité de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	if (largeur != image.dimension.getLargeur() || hauteur != image.dimension.getHauteur())
		return false;
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			if (getPixel(i, j) != image.getPixel(i, j))
				return false;
	return true;
}

bool ImageNG::operator!=(const ImageNG &image)const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de différence de ImageNG\033[0m"<<endl;
#endif
	return !(*this == image);
}

bool ImageNG::operator<(const ImageNG &image)const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de comparaison inférieur de ImageNG\033[0m"<<endl;
#endif
	if (dimension != image.dimension)
		return getLuminance() < image.getLuminance();
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			if (getPixel(i, j) >= image.getPixel(i, j))
				return false;
	return true;
}

bool ImageNG::operator<=(const ImageNG &image)const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de comparaison inférieur ou égal de ImageNG\033[0m"<<endl;
#endif
	return !(*this > image);
}

bool ImageNG::operator>(const ImageNG &image)const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de comparaison supérieur de ImageNG\033[0m"<<endl;
#endif
	if (dimension != image.dimension)
		return getLuminance() > image.getLuminance();
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			if (getPixel(i, j) <= image.getPixel(i, j))
				return false;
	return true;
}

bool ImageNG::operator>=(const ImageNG &image)const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de comparaison supérieur ou égal de ImageNG\033[0m"<<endl;
#endif
	return !(*this < image);
}

ostream& operator<<(ostream &outputStream, const ImageNG &image)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[33;46mDEBUGVERBOSE : Opérateur d'écriture de ImageNG\033[0m"<<endl;
#endif
	outputStream << image.getId() << " " << image.getNom() << " " << image.getDimension() << " " << image.getLuminance() << " " << image.getContraste();
	return outputStream;
}

void ImageNG::setDimension(const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[31;44mDEBUGVERBOSE : setDimension de ImageNG\033[0m"<<endl;
#endif
	unsigned char **oldMatrice = matrice;
	matrice = nullptr;
	Dimension oldDimension(this->dimension);
	this->dimension = dimension;
	createMatrice();
	if (oldMatrice != nullptr)
	{
		copyMatrice(matrice, this->dimension, oldMatrice, oldDimension);
		freeMatrice(oldMatrice, oldDimension);
	}
}

void ImageNG::setBackground(unsigned char grayLevel)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[31;44mDEBUGVERBOSE : setBackground de ImageNG (unsigned char grayLevel)\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0; i<largeur; i++)
		for(int j=0; j<hauteur; j++)
			setPixel(i, j, grayLevel);
}

void ImageNG::setBackground(int grayLevel)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[31;44mDEBUGVERBOSE : setBackground de ImageNG (int grayLevel)\033[0m"<<endl;
#endif
	setBackground((unsigned char)clamp(grayLevel, 0, UCHAR_MAX));
}

void ImageNG::setPixel(int x, int y, unsigned char grayLevel)
{
#ifdef DEBUGVERYVERBOSE
	cout<<"\033[31;44mDEBUGVERYVERBOSE : setPixel de ImageNG (x, y, unsigned char grayLevel)\033[0m"<<endl;
#endif
	if(x >= 0 && x < dimension.getLargeur() && y >= 0 && y < dimension.getHauteur())
		matrice[x][y] = grayLevel;
}

void ImageNG::setPixel(int x, int y, int grayLevel)
{
#ifdef DEBUGVERYVERBOSE
	cout<<"\033[31;44mDEBUGVERYVERBOSE : setPixel de ImageNG (x, y, int grayLevel)\033[0m"<<endl;
#endif
	setPixel(x,y,(unsigned char)clamp(grayLevel, 0, UCHAR_MAX));
}

int ImageNG::getPixel(int x, int y) const
{
#ifdef DEBUGVERYVERBOSE
	cout<<"\033[32;44mDEBUGVERYVERBOSE : getPixel de ImageNG\033[0m"<<endl;
#endif
	if (x >= 0 && x < dimension.getLargeur() && y >= 0 && y < dimension.getHauteur())
		return matrice[x][y];
	//TODO: throw exception
	return -1;
}

int ImageNG::getLuminance() const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[32;44mDEBUGVERBOSE : getLuminance de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	int luminance = 0;
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			luminance += matrice[i][j];
	return luminance/(largeur*hauteur);
}

int ImageNG::getMinimum() const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[32;44mDEBUGVERBOSE : getMinimum de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	int minimum = matrice[0][0];
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			if (matrice[i][j] < minimum)
				minimum = matrice[i][j];
	return minimum;
}

int ImageNG::getMaximum() const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[32;44mDEBUGVERBOSE : getMaximum de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	int maximum = matrice[0][0];
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			if (matrice[i][j] > maximum)
				maximum = matrice[i][j];
	return maximum;
}

float ImageNG::getContraste() const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[32;44mDEBUGVERBOSE : getContraste de ImageNG\033[0m"<<endl;
#endif
	int minimum = getMinimum();
	int maximum = getMaximum();
	return (float)(maximum-minimum)/(maximum+minimum);
}

void ImageNG::Dessine() const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : Dessine de ImageNG\033[0m"<<endl;
#endif
	MyQT::ViewImage(*this);
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin Dessine de ImageNG\033[0m"<<endl;
#endif
}

void ImageNG::importFromFile(const string &nomFichier)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : importFromFile de ImageNG\033[0m"<<endl;
#endif
	MyQT::ImportFromFile(*this, nomFichier.c_str());
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin importFromFile de ImageNG\033[0m"<<endl;
#endif
}

void ImageNG::exportToFile(const string &nomFichier, const string &formatFichier) const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : exportToFile de ImageNG\033[0m"<<endl;
#endif
	MyQT::ExportToFile(*this, nomFichier.c_str(), formatFichier.c_str());
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin exportToFile de ImageNG\033[0m"<<endl;
#endif
}
