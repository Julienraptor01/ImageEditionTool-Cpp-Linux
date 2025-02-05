#include "ImageNG.h"

#include <regex>
#include <algorithm>
#include <climits>

#include "MyQT.h"
#include "XYException.h"
#include "ColorException.h"

using std::cout;
using std::endl;
using std::regex;
using std::regex_replace;
using std::regex_search;

void ImageNG::createMatrice()
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : createMatrice de ImageNG\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	matrice = new unsigned char *[largeur];
	for (int i = 0; i < largeur; i++)
	{
		matrice[i] = new unsigned char[hauteur];
		for (int j = 0; j < hauteur; j++)
			matrice[i][j] = 0x00;
	}
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin createMatrice de ImageNG\033[0m" << endl;
#endif
}

void ImageNG::freeMatrice(unsigned char **matrice, const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : freeMatrice de ImageNG (matrice, dimension)\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur();
	for (int i = 0; i < largeur; i++)
		delete[] matrice[i];
	delete[] matrice;
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin freeMatrice de ImageNG (matrice, dimension)\033[0m" << endl;
#endif
}

void ImageNG::freeMatrice()
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : freeMatrice de ImageNG\033[0m" << endl;
#endif
	freeMatrice(matrice, dimension);
	matrice = nullptr;
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin freeMatrice de ImageNG\033[0m" << endl;
#endif
}

void ImageNG::copyMatrice(unsigned char **matrice, const Dimension &dimension, unsigned char **matriceToCopy, const Dimension &dimensionOfMatriceToCopy)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : copyMatrice de ImageNG (matrice, dimension, matriceToCopy, dimensionOfMatriceToCopy)\033[0m" << endl;
#endif
	int minLargeur = (dimension.getLargeur() < dimensionOfMatriceToCopy.getLargeur()) ? dimension.getLargeur() : dimensionOfMatriceToCopy.getLargeur(), minHauteur = (dimension.getHauteur() < dimensionOfMatriceToCopy.getHauteur()) ? dimension.getHauteur() : dimensionOfMatriceToCopy.getHauteur();
	for (int i = 0; i < minLargeur; i++)
		for (int j = 0; j < minHauteur; j++)
			matrice[i][j] = matriceToCopy[i][j];
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin copyMatrice de ImageNG (matrice, dimension, matriceToCopy, dimensionOfMatriceToCopy)\033[0m" << endl;
#endif
}

void ImageNG::copyMatrice(const ImageNG &image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : copyMatrice de ImageNG (image)\033[0m" << endl;
#endif
	copyMatrice(matrice, dimension, image.matrice, image.dimension);
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin copyMatrice de ImageNG (image)\033[0m" << endl;
#endif
}

ImageNG::ImageNG() : Image()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur par défaut de ImageNG\033[0m" << endl;
#endif
	setNom("ImageNG sans nom");
	setDimension(dimension);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur par défaut de ImageNG\033[0m" << endl;
#endif
}

ImageNG::~ImageNG()
{
#ifdef DEBUG
	cout << "\033[32;41mDEBUG : Destructeur de ImageNG\033[0m" << endl;
#endif
	if (matrice != nullptr)
		freeMatrice();
#ifdef DEBUG
	cout << "\033[34;41mDEBUG : Fin Destructeur de ImageNG\033[0m" << endl;
#endif
}

ImageNG::ImageNG(int id, const string &nom, const Dimension &dimension) : Image(id)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation complet de ImageNG\033[0m" << endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1") : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de ImageNG\033[0m" << endl;
#endif
}

ImageNG::ImageNG(int id, const string &nom) : Image(id)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation partiel de ImageNG (id, nom)\033[0m" << endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1") : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de ImageNG (id, nom)\033[0m" << endl;
#endif
}

ImageNG::ImageNG(const string &nom) : Image()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation partiel de ImageNG (nom)\033[0m" << endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1") : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de ImageNG (nom)\033[0m" << endl;
#endif
}

ImageNG::ImageNG(const ImageNG &image) : Image(image)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur de copie de ImageNG\033[0m" << endl;
#endif
	setDimension(image.getDimension());
	copyMatrice(image);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur de copie de ImageNG\033[0m" << endl;
#endif
}

ImageNG &ImageNG::operator=(const ImageNG &image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur d'affectation de ImageNG\033[0m" << endl;
#endif
	setId(image.getId());
	setNom(image.getNom());
	setDimension(image.getDimension());
	copyMatrice(image);
	return *this;
}

ImageNG ImageNG::operator+(unsigned char grayLevel) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur d'addition de ImageNG (grayLevel)\033[0m" << endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			try
			{
				image.setPixel(i, j, image.getPixel(i, j) + grayLevel);
			}
			RETHROW(ColorException);
	return image;
}

ImageNG operator+(unsigned char grayLevel, const ImageNG &image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;46mDEBUGVERBOSE : Opérateur d'addition de ImageNG (grayLevel, image)\033[0m" << endl;
#endif
	try
	{
		return image + grayLevel;
	}
	RETHROW(ColorException);
}

ImageNG ImageNG::operator+(const ImageNG &image) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur d'addition de ImageNG (image)\033[0m" << endl;
#endif
	ImageNG imageToReturn(*this);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			try
			{
				imageToReturn.setPixel(i, j, imageToReturn.getPixel(i, j) + image.getPixel(i, j));
			}
			RETHROW(ColorException);
	return imageToReturn;
}

ImageNG ImageNG::operator-(unsigned char grayLevel) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de soustraction de ImageNG (grayLevel)\033[0m" << endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			try
			{
				image.setPixel(i, j, image.getPixel(i, j) - grayLevel);
			}
			RETHROW(ColorException);
	return image;
}

ImageNG operator-(unsigned char grayLevel, const ImageNG &image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;46mDEBUGVERBOSE : Opérateur de soustraction de ImageNG (grayLevel, image)\033[0m" << endl;
#endif
	ImageNG imageToReturn(image);
	int largeur = image.dimension.getLargeur(), hauteur = image.dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			try
			{
				imageToReturn.setPixel(i, j, grayLevel - imageToReturn.getPixel(i, j));
			}
			RETHROW(ColorException);
	return imageToReturn;
}

ImageNG ImageNG::operator-(const ImageNG &image) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de soustraction de ImageNG (image)\033[0m" << endl;
#endif
	ImageNG imageToReturn(*this);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			try
			{
				imageToReturn.setPixel(i, j, imageToReturn.getPixel(i, j) - image.getPixel(i, j));
			}
			RETHROW(ColorException);
	return imageToReturn;
}

ImageNG &ImageNG::operator++()
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de pré-incrémentation de ImageNG\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			try
			{
				setPixel(i, j, getPixel(i, j) + 20);
			}
			RETHROW(ColorException);
	return *this;
}

ImageNG ImageNG::operator++(int)
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de post-incrémentation de ImageNG\033[0m" << endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			try
			{
				setPixel(i, j, getPixel(i, j) + 20);
			}
			RETHROW(ColorException);
	return image;
}

ImageNG &ImageNG::operator--()
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de pré-décrémentation de ImageNG\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			try
			{
				setPixel(i, j, getPixel(i, j) - 20);
			}
			RETHROW(ColorException);
	return *this;
}

ImageNG ImageNG::operator--(int)
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de post-décrémentation de ImageNG\033[0m" << endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			try
			{
				setPixel(i, j, getPixel(i, j) - 20);
			}
			RETHROW(ColorException);
	return image;
}

bool ImageNG::operator==(const ImageNG &image) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur d'égalité de ImageNG\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	if (largeur != image.dimension.getLargeur() || hauteur != image.dimension.getHauteur())
		return false;
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			if (getPixel(i, j) != image.getPixel(i, j))
				return false;
	return true;
}

bool ImageNG::operator!=(const ImageNG &image) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de différence de ImageNG\033[0m" << endl;
#endif
	return !(*this == image);
}

bool ImageNG::operator<(const ImageNG &image) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de comparaison inférieur de ImageNG\033[0m" << endl;
#endif
	if (dimension != image.dimension)
		throw XYException("Comparaison invalide", 'd');
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			if (getPixel(i, j) >= image.getPixel(i, j))
				return false;
	return true;
}

bool ImageNG::operator<=(const ImageNG &image) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de comparaison inférieur ou égal de ImageNG\033[0m" << endl;
#endif
	return !(*this > image);
}

bool ImageNG::operator>(const ImageNG &image) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de comparaison supérieur de ImageNG\033[0m" << endl;
#endif
	if (dimension != image.dimension)
		throw XYException("Comparaison invalide", 'd');
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			if (getPixel(i, j) <= image.getPixel(i, j))
				return false;
	return true;
}

bool ImageNG::operator>=(const ImageNG &image) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de comparaison supérieur ou égal de ImageNG\033[0m" << endl;
#endif
	return !(*this < image);
}

ostream &operator<<(ostream &outputStream, const ImageNG &image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;46mDEBUGVERBOSE : Opérateur d'écriture de ImageNG\033[0m" << endl;
#endif
	outputStream << image.getId() << " " << image.getNom() << " " << image.getDimension() << " " << image.getLuminance() << " " << image.getContraste();
	return outputStream;
}

void ImageNG::setDimension(const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : setDimension de ImageNG\033[0m" << endl;
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
	cout << "\033[31;44mDEBUGVERBOSE : setBackground de ImageNG (unsigned char grayLevel)\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			setPixel(i, j, grayLevel);
}

void ImageNG::setBackground(int grayLevel)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : setBackground de ImageNG (int grayLevel)\033[0m" << endl;
#endif
	if (grayLevel < 0 || grayLevel > UCHAR_MAX)
		throw ColorException("setBackground invalide", grayLevel);
	setBackground(static_cast<unsigned char>(grayLevel));
}

void ImageNG::setPixel(int x, int y, unsigned char grayLevel)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setPixel de ImageNG (x, y, unsigned char grayLevel)\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	if ((x < 0 || x >= largeur) && (y < 0 || y >= hauteur))
		throw XYException("SetPixel invalide", 'd', x, y);
	if (x < 0 || x >= largeur)
		throw XYException("SetPixel invalide", 'x', x);
	if (y < 0 || y >= hauteur)
		throw XYException("SetPixel invalide", 'y', y);
	matrice[x][y] = grayLevel;
}

void ImageNG::setPixel(int x, int y, int grayLevel)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setPixel de ImageNG (x, y, int grayLevel)\033[0m" << endl;
#endif
	if (grayLevel < 0 || grayLevel > UCHAR_MAX)
		throw ColorException("setPixel invalide", grayLevel);
	try
	{
		setPixel(x, y, static_cast<unsigned char>(grayLevel));
	}
	RETHROW(XYException);
}

int ImageNG::getPixel(int x, int y) const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : getPixel de ImageNG\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	if ((x < 0 || x >= largeur) && (y < 0 || y >= hauteur))
		throw XYException("GetPixel invalide", 'd', x, y);
	if (x < 0 || x >= largeur)
		throw XYException("GetPixel invalide", 'x', x);
	if (y < 0 || y >= hauteur)
		throw XYException("GetPixel invalide", 'y', y);
	return matrice[x][y];
}

int ImageNG::getLuminance() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[32;44mDEBUGVERBOSE : getLuminance de ImageNG\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur(), luminance = 0;
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			luminance += matrice[i][j];
	return luminance / (largeur * hauteur);
}

int ImageNG::getMinimum() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[32;44mDEBUGVERBOSE : getMinimum de ImageNG\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur(), minimum = matrice[0][0];
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			if (matrice[i][j] < minimum)
				minimum = matrice[i][j];
	return minimum;
}

int ImageNG::getMaximum() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[32;44mDEBUGVERBOSE : getMaximum de ImageNG\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur(), maximum = matrice[0][0];
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			if (matrice[i][j] > maximum)
				maximum = matrice[i][j];
	return maximum;
}

float ImageNG::getContraste() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[32;44mDEBUGVERBOSE : getContraste de ImageNG\033[0m" << endl;
#endif
	int minimum = getMinimum(), maximum = getMaximum();
	return (float)(maximum - minimum) / (maximum + minimum);
}

void ImageNG::Dessine() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Dessine de ImageNG\033[0m" << endl;
#endif
	MyQT::ViewImage(*this);
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Dessine de ImageNG\033[0m" << endl;
#endif
}

void ImageNG::importFromFile(const string &nomFichier)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : importFromFile de ImageNG\033[0m" << endl;
#endif
	MyQT::ImportFromFile(*this, nomFichier.c_str());
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin importFromFile de ImageNG\033[0m" << endl;
#endif
}

void ImageNG::exportToFile(const string &nomFichier, const string &formatFichier) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : exportToFile de ImageNG\033[0m" << endl;
#endif
	MyQT::ExportToFile(*this, nomFichier.c_str(), formatFichier.c_str());
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin exportToFile de ImageNG\033[0m" << endl;
#endif
}

void ImageNG::Save(ofstream &fichier) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Save de ImageNG\033[0m" << endl;
#endif
	Image::Save(fichier);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	unsigned char *vector = new unsigned char[largeur * hauteur];
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			vector[i * hauteur + j] = getPixel(i, j);
	fichier.write(reinterpret_cast<char *>(vector), largeur * hauteur * sizeof(unsigned char));
	delete[] vector;
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Save de ImageNG\033[0m" << endl;
#endif
}

void ImageNG::Load(ifstream &fichier)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Load de ImageNG\033[0m" << endl;
#endif
	Image::Load(fichier);
	Dimension dimension;
	dimension.Load(fichier);
	setDimension(dimension);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	unsigned char *vector = new unsigned char[largeur * hauteur];
	fichier.read(reinterpret_cast<char *>(vector), largeur * hauteur * sizeof(unsigned char));
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			setPixel(i, j, vector[i * hauteur + j]);
	delete[] vector;
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Load de ImageNG\033[0m" << endl;
#endif
}
