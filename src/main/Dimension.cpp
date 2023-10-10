#include <iostream>
#include <string.h>

using namespace std;

#include "Dimension.h"

Dimension::Dimension()
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur par défaut de Dimension\033[49m"<<endl;
#endif
	setLargeur(DIMENSION_H_DEFAULT_LARGEUR);
	setHauteur(DIMENSION_H_DEFAULT_HAUTEUR);
}

Dimension::~Dimension()
{
#ifdef DEBUG
	cout<<"\033[41mDEBUG : Destructeur de Dimension\033[49m"<<endl;
#endif
}

Dimension::Dimension(int largeur, int hauteur)
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur d'initialisation complet de Dimension\033[49m"<<endl;
#endif
	setLargeur(largeur);
	setHauteur(hauteur);
}

Dimension::Dimension(const Dimension &dimension)
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur de copie de Dimension\033[49m"<<endl;
#endif
	setLargeur(dimension.largeur);
	setHauteur(dimension.hauteur);
}

void Dimension::Affiche()const
{
	cout<<" largeur="<<largeur<<" hauteur="<<hauteur<<endl;
}

void Dimension::setLargeur(int largeur)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : setLargeur de Dimension\033[49m"<<endl;
#endif
	if (largeur<=0) largeur=DIMENSION_H_DEFAULT_LARGEUR;
	this->largeur=largeur;
}

int Dimension::getLargeur()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : getLargeur de Dimension\033[49m"<<endl;
#endif
	return largeur;
}

void Dimension::setHauteur(int hauteur)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : setHauteur de Dimension\033[49m"<<endl;
#endif
	if (hauteur<=0) hauteur=DIMENSION_H_DEFAULT_HAUTEUR;
	this->hauteur=hauteur;
}

int Dimension::getHauteur()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : getHauteur de Dimension\033[49m"<<endl;
#endif
	return hauteur;
}

const Dimension Dimension::VGA(640,480);
const Dimension Dimension::HD(1280,720);
const Dimension Dimension::FULL_HD(1920,1080);