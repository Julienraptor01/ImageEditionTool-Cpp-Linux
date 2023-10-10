#include <iostream>
#include <string.h>

using namespace std;

#include "ImageNG.h"
#include "Dimension.h"

ImageNG::ImageNG()
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur par défaut de ImageNG\033[49m"<<endl;
#endif
	setId(1);
	setNom("ImageNG sans nom");
}

ImageNG::~ImageNG()
{
#ifdef DEBUG
	cout<<"\033[41mDEBUG : Destructeur de ImageNG\033[49m"<<endl;
#endif
	if(nom !=NULL)
		free(nom);
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
}

ImageNG::ImageNG(const ImageNG &image)
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur de copie de ImageNG\033[49m"<<endl;
#endif
	setId(image.id);
	setNom(image.nom);
	setDimension(image.dimension);
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
	if(this->nom !=NULL)
	{
		free(this->nom);
	}
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
	this->dimension=dimension;
}

Dimension ImageNG::getDimension()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : getDimension de ImageNG\033[49m"<<endl;
#endif
	return dimension;
}

void ImageNG::Affiche()const
{
	cout<<" id="<<id<<" nom="<<nom<<" dimension=("<<dimension.getLargeur()<<","<<dimension.getHauteur()<<")"<<endl;
}
