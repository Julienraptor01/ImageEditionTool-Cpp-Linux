#include <iostream>
#include <string.h>

using namespace std;

#include "ImageNG.h"
#include "Dimension.h"
#include "MyQT.h"

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
	matrice = new int*[dimension.getLargeur()];
	for(int i=0;i<dimension.getLargeur();i++)
	{
		matrice[i] = new int[dimension.getHauteur()];
		for(int j=0;j<dimension.getHauteur();j++)
			matrice[i][j] = 0;
	}
}

void ImageNG::freeMatrice(int **matrice, const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[43mDEBUGVERBOSE : freeMatrice de ImageNG (matrice)\033[49m"<<endl;
#endif
	for(int i=0;i<dimension.getLargeur();i++)
		delete[] matrice[i];
	delete[] matrice;
}

void ImageNG::freeMatrice()
{
#ifdef DEBUGVERBOSE
	cout<<"\033[43mDEBUGVERBOSE : freeMatrice de ImageNG\033[49m"<<endl;
#endif
	freeMatrice(matrice, dimension);
	matrice = nullptr;
}

void ImageNG::copyMatrice(int **matrice, const Dimension &dimension, int **matriceToCopy, const Dimension &dimensionOfMatriceToCopy)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[43mDEBUGVERBOSE : copyMatrice de ImageNG (matrice, dimension, matriceToCopy, dimensionOfMatriceToCopy)\033[49m"<<endl;
#endif
	int minLargeur = (dimension.getLargeur() < dimensionOfMatriceToCopy.getLargeur()) ? dimension.getLargeur() : dimensionOfMatriceToCopy.getLargeur();
	int minHauteur = (dimension.getHauteur() < dimensionOfMatriceToCopy.getHauteur()) ? dimension.getHauteur() : dimensionOfMatriceToCopy.getHauteur();
	for(int i=0;i<minLargeur;i++)
		for(int j=0;j<minHauteur;j++)
			matrice[i][j] = matriceToCopy[i][j];
}

ImageNG::ImageNG()
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur par défaut de ImageNG\033[49m"<<endl;
#endif
	setId(1);
	setNom("ImageNG sans nom");
	setDimension(dimension);
}

ImageNG::~ImageNG()
{
#ifdef DEBUG
	cout<<"\033[41mDEBUG : Destructeur de ImageNG\033[49m"<<endl;
#endif
	if(nom != NULL)
		freeNom();
	if(matrice != nullptr)
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
}

ImageNG::ImageNG(int id, const char *nom)
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur d'initialisation partiel de ImageNG\033[49m"<<endl;
#endif
	setId(id);
	setNom(nom);
	setDimension(dimension);
}

ImageNG::ImageNG(const ImageNG &image)
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur de copie de ImageNG\033[49m"<<endl;
#endif
	setId(image.id);
	setNom(image.nom);
	setDimension(image.dimension);
	copyMatrice(matrice,dimension,image.matrice,image.dimension);
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
	if(matrice == nullptr)
	{
		//this->dimension=dimension;
		//do each component of dimension separately because technically we didn't 	overload the = operator so it just work by sheer luck
		this->dimension.setLargeur(dimension.getLargeur());
		this->dimension.setHauteur(dimension.getHauteur());
		createMatrice();
	}
	//else we need to copy the old matrix into the new one
	else
	{
		//we need to make a hard save of the old matrix
		int **oldMatrice = new int*[this->dimension.getLargeur()];
		for(int i=0;i<this->dimension.getLargeur();i++)
		{
			oldMatrice[i] = new int[this->dimension.getHauteur()];
			for(int j=0;j<this->dimension.getHauteur();j++)
				oldMatrice[i][j] = matrice[i][j];
		}
		//we need to save the old dimension
		Dimension oldDimension;
		oldDimension.setLargeur(this->dimension.getLargeur());
		oldDimension.setHauteur(this->dimension.getHauteur());
		//we need to free the old matrix
		freeMatrice();
		//we need to set the new dimension
		this->dimension.setLargeur(dimension.getLargeur());
		this->dimension.setHauteur(dimension.getHauteur());
		//we need to create the new matrix
		createMatrice();
		//we need to copy the old matrix into the new one
		copyMatrice(matrice,this->dimension,oldMatrice,oldDimension);
		//we need to free the old matrix
		freeMatrice(oldMatrice, oldDimension);
	}
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
#ifdef DEBUGVERYVERBOSE
	cout<<"\033[44mDEBUGVERYVERBOSE : setPixel de ImageNG\033[49m"<<endl;
#endif
	if(x>=0 && x<dimension.getLargeur() && y>=0 && y<dimension.getHauteur())
		matrice[x][y] = couleur;
}

int ImageNG::getPixel(int x, int y) const
{
#ifdef DEBUGVERYVERBOSE
	cout<<"\033[44mDEBUGVERYVERBOSE : getPixel de ImageNG\033[49m"<<endl;
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
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : Dessine de ImageNG\033[49m"<<endl;
#endif
	MyQT::ViewImage(*this);
}

void ImageNG::importFromFile(const char *nomFichier)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : importFromFile de ImageNG\033[49m"<<endl;
#endif
	MyQT::ImportFromFile(*this, nomFichier);
}

void ImageNG::exportToFile(const char *nomFichier, const char *formatFichier) const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : exportToFile de ImageNG\033[49m"<<endl;
#endif
	MyQT::ExportToFile(*this, nomFichier, formatFichier);
}
