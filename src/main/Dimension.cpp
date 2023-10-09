#include <iostream>
#include <string.h>

using namespace std;

#include "Dimension.h"

Dimension::Dimension()
{
#ifdef DEBUG
	cout<<"\033[42mDEBUG : Constructeur par défaut de Dimension\033[49m"<<endl;
#endif
	setLargeur(1);
	setHauteur(1);
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

void Dimension::Affiche()
{
	cout<<" largeur="<<largeur<<" hauteur="<<hauteur<<endl;
}

void Dimension::setLargeur(int largeur)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : setLargeur de Dimension\033[49m"<<endl;
#endif
	this->largeur=largeur;
}

int Dimension::getLargeur()
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
	this->hauteur=hauteur;
}

int Dimension::getHauteur()
{
#ifdef DEBUGVERBOSE
	cout<<"\033[44mDEBUGVERBOSE : getHauteur de Dimension\033[49m"<<endl;
#endif
	return hauteur;
}
