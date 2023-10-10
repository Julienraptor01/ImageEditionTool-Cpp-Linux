#include <iostream>
#include <string.h>

using namespace std;

#include "ImageNG.h"
#include "Dimension.h"

void ImageNG::freeNom()
{
#ifdef DEBUGVERBOSE
	cout<<"\033[43mDEBUGVERBOSE : freeNom de ImageNG\033[49m"<<endl;
#endif
	free(nom);
	nom=NULL;
}

void ImageNG::createMatrice()
{
#ifdef DEBUGVERBOSE
	cout<<"\033[43mDEBUGVERBOSE : createMatrice de ImageNG\033[49m"<<endl;
#endif
	/*
	if(matrice != nullptr)
		freeMatrice();
	matrice = new int*[dimension.getLargeur()];
	for(int i=0;i<dimension.getLargeur();i++)
		matrice[i] = new int[dimension.getHauteur()];
	*/
	//same but each element is initialized to 0
	if(matrice != nullptr)
		freeMatrice();
	matrice = new int*[dimension.getLargeur()];
	for(int i=0;i<dimension.getLargeur();i++)
	{
		matrice[i] = new int[dimension.getHauteur()];
		for(int j=0;j<dimension.getHauteur();j++)
			matrice[i][j] = 0;
	}
}

void ImageNG::freeMatrice()
{
#ifdef DEBUGVERBOSE
	cout<<"\033[43mDEBUGVERBOSE : freeMatrice de ImageNG\033[49m"<<endl;
#endif
	for(int i=0;i<dimension.getLargeur();i++)
		delete[] matrice[i];
	delete[] matrice;
	matrice = nullptr;
}

ImageNG::ImageNG()
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur par défaut de ImageNG\033[49m"<<endl;
#endif
	setId(1);
	setNom("ImageNG sans nom");
	createMatrice();
}

ImageNG::~ImageNG()
{
#ifdef DEBUG
	cout<<"\033[41mDEBUG : Destructeur de ImageNG\033[49m"<<endl;
#endif
	if(nom != NULL)
		freeNom();
	if(nom != nullptr)
		freeMatrice();
}

ImageNG::ImageNG(int id, const char *nom, const Dimension &dimension)
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur d'initialisation complet de ImageNG\033[49m"<<endl;
#endif
	setId(id);
	setNom(nom);
	setDimension(dimension);
	createMatrice();
}

ImageNG::ImageNG(int id, const char *nom)
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur d'initialisation partiel de ImageNG\033[49m"<<endl;
#endif
	setId(id);
	setNom(nom);
	createMatrice();
}

ImageNG::ImageNG(const ImageNG &image)
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur de copie de ImageNG\033[49m"<<endl;
#endif
	setId(image.id);
	setNom(image.nom);
	setDimension(image.dimension);
	createMatrice();
}

void ImageNG::setId(int id)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : setId de ImageNG\033[49m"<<endl;
#endif
	this->id=id;
}

int ImageNG::getId()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : getId de ImageNG\033[49m"<<endl;
#endif
	return id;
}

void ImageNG::setNom(const char *nom)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : setNom de ImageNG\033[49m"<<endl;
#endif
	if(nom != NULL)
		freeNom();
	this->nom=(char *)malloc(strlen(nom)+1);
	strcpy(this->nom,nom);
}

char *ImageNG::getNom()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : getNom de ImageNG\033[49m"<<endl;
#endif
	return nom;
}

void ImageNG::setDimension(const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : setDimension de ImageNG\033[49m"<<endl;
#endif
	if(matrice != nullptr)
		freeMatrice();
	this->dimension=dimension;
	createMatrice();
}

Dimension ImageNG::getDimension()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : getDimension de ImageNG\033[49m"<<endl;
#endif
	return dimension;
}

void ImageNG::setBackground(int couleur)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : setBackground de ImageNG\033[49m"<<endl;
#endif
	for(int i=0;i<dimension.getLargeur();i++)
		for(int j=0;j<dimension.getHauteur();j++)
			setPixel(i,j,couleur);
}

void ImageNG::setPixel(int x, int y, int couleur)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : setPixel de ImageNG\033[49m"<<endl;
#endif
	if(x>=0 && x<dimension.getLargeur() && y>=0 && y<dimension.getHauteur())
		matrice[x][y] = couleur;
}

int ImageNG::getPixel(int x, int y) const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : getPixel de ImageNG\033[49m"<<endl;
#endif
	if(x>=0 && x<dimension.getLargeur() && y>=0 && y<dimension.getHauteur())
		return matrice[x][y];
	return -1;
}

void ImageNG::Affiche()const
{
	cout<<" id="<<id<<" nom="<<nom<<" dimension=("<<dimension.getLargeur()<<","<<dimension.getHauteur()<<")"<<endl;
}

void ImageNG::Dessine() const
{
}

void ImageNG::importFromFile(const char *nomFichier)
{
}

void ImageNG::exportToFile(const char *nomFichier, const char *formatFichier) const
{
}
