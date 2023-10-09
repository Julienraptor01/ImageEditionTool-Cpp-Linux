#include <iostream>
#include <string.h>

using namespace std;

#include "ImageNG.h"

ImageNG::ImageNG()
{
#ifdef DEBUG
	cout<<"Constructeur par défaut de ImageNG"<<endl;
#endif
	id=1;
	//nom=NULL;
	nom=(char *)malloc(20);
	strcpy(nom,"ImageNG sans nom");
}

ImageNG::~ImageNG()
{
#ifdef DEBUG
	cout<<"Destructeur de ImageNG"<<endl;
#endif
	if(nom !=NULL)
		free(nom);
}

void ImageNG::Affiche()
{
	cout<<"id="<<id<<" nom="<<nom<<endl;
}
