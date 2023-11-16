#include "Dimension.h"
#include "XYException.h"

using std::cout;
using std::endl;

Dimension::Dimension()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur par défaut de Dimension\033[0m" << endl;
#endif
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur par défaut de Dimension\033[0m" << endl;
#endif
}

Dimension::~Dimension()
{
#ifdef DEBUG
	cout << "\033[32;41mDEBUG : Destructeur de Dimension\033[0m" << endl;
#endif
#ifdef DEBUG
	cout << "\033[34;41mDEBUG : Fin Destructeur de Dimension\033[0m" << endl;
#endif
}

Dimension::Dimension(int largeur, int hauteur)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation complet de Dimension\033[0m" << endl;
#endif
	setLargeur(largeur);
	setHauteur(hauteur);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de Dimension\033[0m" << endl;
#endif
}

Dimension::Dimension(const Dimension &dimension)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur de copie de Dimension\033[0m" << endl;
#endif
	setLargeur(dimension.getLargeur());
	setHauteur(dimension.getHauteur());
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur de copie de Dimension\033[0m" << endl;
#endif
}

bool Dimension::operator==(const Dimension &dimension) const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur d'égalité de Dimension\033[0m" << endl;
#endif
	return (getLargeur() == dimension.getLargeur() && getHauteur() == dimension.getHauteur());
}

bool Dimension::operator!=(const Dimension &dimension) const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur de différence de Dimension\033[0m" << endl;
#endif
	return !(*this == dimension);
}

istream &operator>>(istream &inputStream, Dimension &dimension)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;46mDEBUGVERBOSE : Opérateur de lecture de Dimension\033[0m" << endl;
#endif
	int largeur, hauteur;
	inputStream >> largeur;
	dimension.setLargeur(largeur);
	inputStream >> hauteur;
	dimension.setHauteur(hauteur);
	return inputStream;
}

ostream &operator<<(ostream &outputStream, const Dimension &dimension)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;46mDEBUGVERBOSE : Opérateur d'écriture de Dimension\033[0m" << endl;
#endif
	outputStream << dimension.getLargeur() << " " << dimension.getHauteur();
	return outputStream;
}

void Dimension::setLargeur(int largeur)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setLargeur de Dimension\033[0m" << endl;
#endif
	if (largeur <= 0)
		throw XYException("setLargeur invalide", 'x', largeur);
	this->largeur = largeur;
}

int Dimension::getLargeur() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : getLargeur de Dimension\033[0m" << endl;
#endif
	return largeur;
}

void Dimension::setHauteur(int hauteur)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setHauteur de Dimension\033[0m" << endl;
#endif
	if (hauteur <= 0)
		throw XYException("setHauteur invalide", 'y', hauteur);
	this->hauteur = hauteur;
}

int Dimension::getHauteur() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : getHauteur de Dimension\033[0m" << endl;
#endif
	return hauteur;
}

const Dimension Dimension::VGA(640, 480);
const Dimension Dimension::HD(1280, 720);
const Dimension Dimension::FULL_HD(1920, 1080);

void Dimension::Affiche() const
{
	cout << "Largeur : " << largeur << "\t" << "Hauteur : " << hauteur << endl;
}
