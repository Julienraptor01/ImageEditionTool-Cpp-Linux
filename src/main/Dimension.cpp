#include <iostream>
#include <string.h>

using namespace std;

#include "Dimension.h"

Dimension::Dimension()
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur par défaut de Dimension\033[0m"<<endl;
#endif
	setLargeur(DIMENSION_H_DEFAULT_LARGEUR);
	setHauteur(DIMENSION_H_DEFAULT_HAUTEUR);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur par défaut de Dimension\033[0m"<<endl;
#endif
}

Dimension::~Dimension()
{
#ifdef DEBUG
	cout<<"\033[32;41mDEBUG : Destructeur de Dimension\033[0m"<<endl;
#endif
#ifdef DEBUG
	cout<<"\033[34;41mDEBUG : Fin Destructeur de Dimension\033[0m"<<endl;
#endif
}

Dimension::Dimension(int largeur, int hauteur)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur d'initialisation complet de Dimension\033[0m"<<endl;
#endif
	setLargeur(largeur);
	setHauteur(hauteur);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de Dimension\033[0m"<<endl;
#endif
}

Dimension::Dimension(const Dimension &dimension)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur de copie de Dimension\033[0m"<<endl;
#endif
	setLargeur(dimension.largeur);
	setHauteur(dimension.hauteur);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur de copie de Dimension\033[0m"<<endl;
#endif
}

void Dimension::setLargeur(int largeur)
{
#ifdef DEBUGVERYVERBOSE
	cout<<"\033[31;44mDEBUGVERYVERBOSE : setLargeur de Dimension\033[0m"<<endl;
#endif
	if (largeur<=0)
		largeur=DIMENSION_H_DEFAULT_LARGEUR;
	this->largeur=largeur;
}

int Dimension::getLargeur()const
{
#ifdef DEBUGVERYVERBOSE
	cout<<"\033[32;44mDEBUGVERYVERBOSE : getLargeur de Dimension\033[0m"<<endl;
#endif
	return largeur;
}

void Dimension::setHauteur(int hauteur)
{
#ifdef DEBUGVERYVERBOSE
	cout<<"\033[31;44mDEBUGVERYVERBOSE : setHauteur de Dimension\033[0m"<<endl;
#endif
	if (hauteur<=0)
		hauteur=DIMENSION_H_DEFAULT_HAUTEUR;
	this->hauteur=hauteur;
}

int Dimension::getHauteur()const
{
#ifdef DEBUGVERYVERBOSE
	cout<<"\033[32;44mDEBUGVERYVERBOSE : getHauteur de Dimension\033[0m"<<endl;
#endif
	return hauteur;
}

const Dimension Dimension::VGA(640,480);
const Dimension Dimension::HD(1280,720);
const Dimension Dimension::FULL_HD(1920,1080);

void Dimension::Affiche()const
{
	cout<<" largeur="<<largeur<<" hauteur="<<hauteur<<endl;
}
