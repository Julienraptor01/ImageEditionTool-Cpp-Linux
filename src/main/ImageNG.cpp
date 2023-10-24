#include <iostream>
#include <string.h>
#include <regex>

using std::cout;
using std::endl;
using std::regex;
using std::regex_search;
using std::regex_replace;

#include "ImageNG.h"
#include "Dimension.h"
#include "MyQT.h"

void ImageNG::freeNom()
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : freeNom de ImageNG\033[0m"<<endl;
#endif
	free(nom);
	nom=NULL;
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin freeNom de ImageNG\033[0m"<<endl;
#endif
}

void ImageNG::createMatrice()
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : createMatrice de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	matrice = new int*[largeur];
	for(int i=0;i<largeur;i++)
	{
		matrice[i] = new int[hauteur];
		for(int j=0;j<hauteur;j++)
			matrice[i][j] = 0x00000000;
	}
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin createMatrice de ImageNG\033[0m"<<endl;
#endif
}

void ImageNG::freeMatrice(int **matrice, const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : freeMatrice de ImageNG (matrice, dimension)\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	for(int i=0;i<largeur;i++)
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

void ImageNG::copyMatrice(int **matrice, const Dimension &dimension, int **matriceToCopy, const Dimension &dimensionOfMatriceToCopy)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : copyMatrice de ImageNG (matrice, dimension, matriceToCopy, dimensionOfMatriceToCopy)\033[0m"<<endl;
#endif
	int minLargeur = (dimension.getLargeur() < dimensionOfMatriceToCopy.getLargeur()) ? dimension.getLargeur() : dimensionOfMatriceToCopy.getLargeur();
	int minHauteur = (dimension.getHauteur() < dimensionOfMatriceToCopy.getHauteur()) ? dimension.getHauteur() : dimensionOfMatriceToCopy.getHauteur();
	for(int i=0;i<minLargeur;i++)
		for(int j=0;j<minHauteur;j++)
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

ImageNG::ImageNG()
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur par défaut de ImageNG\033[0m"<<endl;
#endif
	setId(1);
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
	if(nom != NULL)
		freeNom();
	if(matrice != nullptr)
		freeMatrice();
#ifdef DEBUG
	cout<<"\033[34;41mDEBUG : Fin Destructeur de ImageNG\033[0m"<<endl;
#endif
}

ImageNG::ImageNG(int id, const char *nom, const Dimension &dimension)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur d'initialisation complet de ImageNG\033[0m"<<endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setId(id);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1").c_str() : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de ImageNG\033[0m"<<endl;
#endif
}

ImageNG::ImageNG(int id, const char *nom)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur d'initialisation partiel de ImageNG\033[0m"<<endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setId(id);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1").c_str() : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de ImageNG\033[0m"<<endl;
#endif
}

ImageNG::ImageNG(const char *nom)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur d'initialisation par fichier de ImageNG\033[0m"<<endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setId(1);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1").c_str() : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur d'initialisation par fichier de ImageNG\033[0m"<<endl;
#endif
}

ImageNG::ImageNG(const ImageNG &image)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur de copie de ImageNG\033[0m"<<endl;
#endif
	setId(image.id);
	setNom(image.nom);
	setDimension(image.dimension);
	copyMatrice(image);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur de copie de ImageNG\033[0m"<<endl;
#endif
}

ImageNG& ImageNG::operator=(const ImageNG &image)
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur d'affectation de ImageNG\033[0m"<<endl;
#endif
	setId(image.id);
	setNom(image.nom);
	setDimension(image.dimension);
	copyMatrice(image);
	return *this;
}

ImageNG ImageNG::operator+(int valeur)const
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur d'addition avec int de ImageNG\033[0m"<<endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			image.matrice[i][j] += valeur;
	return image;
}

ImageNG operator+(int valeur, const ImageNG &image)
{
#ifdef DEBUG
	cout<<"\033[33;46mDEBUGVERBOSE : Opérateur inversé d'addition avec int de ImageNG\033[0m"<<endl;
#endif
	return image+valeur;
}

ImageNG ImageNG::operator+(const ImageNG &image)const
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur d'addition avec ImageNG de ImageNG\033[0m"<<endl;
#endif
	ImageNG imageToReturn(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			imageToReturn.matrice[i][j] += image.matrice[i][j];
	return imageToReturn;
}

ImageNG ImageNG::operator-(int valeur)const
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de soustraction avec int de ImageNG\033[0m"<<endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			image.matrice[i][j] -= valeur;
	return image;
}

ImageNG operator-(int valeur, const ImageNG &image)
{
#ifdef DEBUG
	cout<<"\033[33;46mDEBUGVERBOSE : Opérateur inversé de soustraction avec int de ImageNG\033[0m"<<endl;
#endif
	ImageNG imageToReturn(image);
	int largeur = image.dimension.getLargeur();
	int hauteur = image.dimension.getHauteur();
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			imageToReturn.matrice[i][j] = valeur - imageToReturn.matrice[i][j];
	return imageToReturn;
}

ImageNG ImageNG::operator-(const ImageNG &image)const
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de soustraction avec ImageNG de ImageNG\033[0m"<<endl;
#endif
	ImageNG imageToReturn(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			imageToReturn.matrice[i][j] -= image.matrice[i][j];
	return imageToReturn;
}

ImageNG& ImageNG::operator++()
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de pré-incrémentation de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			matrice[i][j]++;
	return *this;
}

ImageNG ImageNG::operator++(int)
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de post-incrémentation de ImageNG\033[0m"<<endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			matrice[i][j]++;
	return image;
}

ImageNG& ImageNG::operator--()
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de pré-décrémentation de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			matrice[i][j]--;
	return *this;
}

ImageNG ImageNG::operator--(int)
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de post-décrémentation de ImageNG\033[0m"<<endl;
#endif
	ImageNG image(*this);
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			matrice[i][j]--;
	return image;
}

bool ImageNG::operator==(const ImageNG &image)const
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur d'égalité de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	if (largeur != image.dimension.getLargeur() || hauteur != image.dimension.getHauteur())
		return false;
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			if (matrice[i][j] != image.matrice[i][j])
				return false;
	return true;
}

bool ImageNG::operator!=(const ImageNG &image)const
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de différence de ImageNG\033[0m"<<endl;
#endif
	return !(*this == image);
}

bool ImageNG::operator<(const ImageNG &image)const
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de comparaison inférieur de ImageNG\033[0m"<<endl;
#endif
	//TODO: implement operator<
	return NULL;
}

bool ImageNG::operator<=(const ImageNG &image)const
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de comparaison inférieur ou égal de ImageNG\033[0m"<<endl;
#endif
	//TODO: implement operator<=
	return NULL;
}

bool ImageNG::operator>(const ImageNG &image)const
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de comparaison supérieur de ImageNG\033[0m"<<endl;
#endif
	//TODO: implement operator>
	return NULL;
}

bool ImageNG::operator>=(const ImageNG &image)const
{
#ifdef DEBUG
	cout<<"\033[33;45mDEBUGVERBOSE : Opérateur de comparaison supérieur ou égal de ImageNG\033[0m"<<endl;
#endif
	//TODO: implement operator>=
	return NULL;
}

ostream& operator<<(ostream &outputStream, const ImageNG &image)
{
#ifdef DEBUG
	cout<<"\033[33;46mDEBUGVERBOSE : Opérateur d'écriture de ImageNG\033[0m"<<endl;
#endif
	outputStream << image.id << " " << image.nom << " " << image.dimension << " " << image.getLuminance() << " " << image.getContraste();
	return outputStream;
}

void ImageNG::setId(int id)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[31;44mDEBUGVERBOSE : setId de ImageNG\033[0m"<<endl;
#endif
	this->id=id;
}

int ImageNG::getId()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[32;44mDEBUGVERBOSE : getId de ImageNG\033[0m"<<endl;
#endif
	return id;
}

void ImageNG::setNom(const char *nom)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[31;44mDEBUGVERBOSE : setNom de ImageNG\033[0m"<<endl;
#endif
	if(nom != NULL)
		freeNom();
	this->nom=(char *)malloc(strlen(nom)+1);
	strcpy(this->nom,nom);
}

char *ImageNG::getNom()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[32;44mDEBUGVERBOSE : getNom de ImageNG\033[0m"<<endl;
#endif
	return nom;
}

void ImageNG::setDimension(const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[31;44mDEBUGVERBOSE : setDimension de ImageNG\033[0m"<<endl;
#endif
	int **oldMatrice = matrice;
	matrice = nullptr;
	Dimension oldDimension(this->dimension);
	this->dimension=dimension;
	createMatrice();
	if (oldMatrice != nullptr)
	{
		copyMatrice(matrice,this->dimension,oldMatrice,oldDimension);
		freeMatrice(oldMatrice, oldDimension);
	}
}

Dimension ImageNG::getDimension()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[32;44mDEBUGVERBOSE : getDimension de ImageNG\033[0m"<<endl;
#endif
	return dimension;
}

void ImageNG::setBackground(int couleur)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[31;44mDEBUGVERBOSE : setBackground de ImageNG\033[0m"<<endl;
#endif
	int largeur = dimension.getLargeur();
	int hauteur = dimension.getHauteur();
	for(int i=0;i<largeur;i++)
		for(int j=0;j<hauteur;j++)
			setPixel(i,j,couleur);
}

void ImageNG::setPixel(int x, int y, int couleur)
{
#ifdef DEBUGVERYVERBOSE
	cout<<"\033[31;44mDEBUGVERYVERBOSE : setPixel de ImageNG\033[0m"<<endl;
#endif
	if(x>=0 && x<dimension.getLargeur() && y>=0 && y<dimension.getHauteur())
		matrice[x][y] = couleur;
}

int ImageNG::getPixel(int x, int y) const
{
#ifdef DEBUGVERYVERBOSE
	cout<<"\033[32;44mDEBUGVERYVERBOSE : getPixel de ImageNG\033[0m"<<endl;
#endif
	if(x>=0 && x<dimension.getLargeur() && y>=0 && y<dimension.getHauteur())
		return matrice[x][y];
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

void ImageNG::Affiche()const
{
	cout<<" id="<<id<<" nom="<<nom<<" dimension=("<<dimension.getLargeur()<<","<<dimension.getHauteur()<<")"<<endl;
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

void ImageNG::importFromFile(const char *nomFichier)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : importFromFile de ImageNG\033[0m"<<endl;
#endif
	MyQT::ImportFromFile(*this, nomFichier);
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin importFromFile de ImageNG\033[0m"<<endl;
#endif
}

void ImageNG::exportToFile(const char *nomFichier, const char *formatFichier) const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : exportToFile de ImageNG\033[0m"<<endl;
#endif
	MyQT::ExportToFile(*this, nomFichier, formatFichier);
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin exportToFile de ImageNG\033[0m"<<endl;
#endif
}
