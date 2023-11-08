#include <algorithm>
#include <limits.h>

#include "Couleur.h"

using std::cout;
using std::endl;
using std::hex;
using std::dec;
using std::clamp;

Couleur::Couleur()
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur par défaut de Couleur\033[0m"<<endl;
#endif
	setARGB(0xFF000000); //fully opaque black
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur par défaut de Couleur\033[0m"<<endl;
#endif
}

Couleur::~Couleur()
{
#ifdef DEBUG
	cout<<"\033[32;41mDEBUG : Destructeur de Couleur\033[0m"<<endl;
#endif
#ifdef DEBUG
	cout<<"\033[34;41mDEBUG : Fin Destructeur de Couleur\033[0m"<<endl;
#endif
}

Couleur::Couleur(unsigned int packedARGB)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur d'initialisation complet de Couleur (packedARGB)\033[0m"<<endl;
#endif
	setARGB(packedARGB);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de Couleur (packedARGB)\033[0m"<<endl;
#endif
}

Couleur::Couleur(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur d'initialisation complet de Couleur (alpha, red, green, blue)\033[0m"<<endl;
#endif
	setAlpha(alpha);
	setRouge(red);
	setVert(green);
	setBleu(blue);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de Couleur (alpha, red, green, blue)\033[0m"<<endl;
#endif
}

Couleur::Couleur(unsigned char red, unsigned char green, unsigned char blue)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur d'initialisation partiel de Couleur (unsigned char red, unsigned char green, unsigned char blue)\033[0m"<<endl;
#endif
	setAlpha(0xFF); //fully opaque
	setRouge(red);
	setVert(green);
	setBleu(blue);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de Couleur (unsigned char red, unsigned char green, unsigned char blue)\033[0m"<<endl;
#endif
}

Couleur::Couleur(int red, int green, int blue)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur d'initialisation partiel de Couleur (int red, int green, int blue)\033[0m"<<endl;
#endif
	setAlpha(0xFF); //fully opaque
	setRouge(red);
	setVert(green);
	setBleu(blue);
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de Couleur (int red, int green, int blue)\033[0m"<<endl;
#endif
}

Couleur::Couleur(const Couleur &couleur)
{
#ifdef DEBUG
	cout<<"\033[34;42mDEBUG : Constructeur de copie de Couleur\033[0m"<<endl;
#endif
	setARGB(couleur.getARGB());
#ifdef DEBUG
	cout<<"\033[31;42mDEBUG : Fin Constructeur de copie de Couleur\033[0m"<<endl;
#endif
}

ostream& operator<<(ostream &outputStream, const Couleur &couleur)
{
#ifdef DEBUG
	cout<<"\033[33;46mDEBUGVERBOSE : Opérateur << de Couleur\033[0m"<<endl;
#endif
	outputStream << hex << (int)couleur.getAlpha() << dec << " " << hex << (int)couleur.getRouge() << dec << " " << hex << (int)couleur.getVert() << dec << " " << hex << (int)couleur.getBleu() << dec;
	return outputStream;
}

void Couleur::setARGB(unsigned int packedARGB)
{
#ifdef DEBUG
	cout<<"\033[31;44mDEBUGVERBOSE : setARGB de Couleur\033[0m"<<endl;
#endif
	color.packedARGB=packedARGB;
}

unsigned int Couleur::getARGB()const
{
#ifdef DEBUG
	cout<<"\033[32;44mDEBUGVERBOSE : getARGB de Couleur\033[0m"<<endl;
#endif
	return color.packedARGB;
}

void Couleur::setAlpha(unsigned char alpha)
{
#ifdef DEBUG
	cout<<"\033[31;44mDEBUGVERBOSE : setAlpha de Couleur\033[0m"<<endl;
#endif
	color.unpacked.alpha=alpha;
}

unsigned char Couleur::getAlpha()const
{
#ifdef DEBUG
	cout<<"\033[32;44mDEBUGVERBOSE : getAlpha de Couleur\033[0m"<<endl;
#endif
	return color.unpacked.alpha;
}

void Couleur::setRouge(unsigned char red)
{
#ifdef DEBUG
	cout<<"\033[31;44mDEBUGVERBOSE : setRouge de Couleur (unsigned char red)\033[0m"<<endl;
#endif
	color.unpacked.red=red;
}

void Couleur::setRouge(int red)
{
#ifdef DEBUG
	cout<<"\033[31;44mDEBUGVERBOSE : setRouge de Couleur (int red)\033[0m"<<endl;
#endif
	color.unpacked.red=(unsigned char)clamp(red, 0, UCHAR_MAX);
}

unsigned char Couleur::getRouge()const
{
#ifdef DEBUG
	cout<<"\033[32;44mDEBUGVERBOSE : getRouge de Couleur\033[0m"<<endl;
#endif
	return color.unpacked.red;
}

void Couleur::setVert(unsigned char green)
{
#ifdef DEBUG
	cout<<"\033[31;44mDEBUGVERBOSE : setVert de Couleur (unsigned char green)\033[0m"<<endl;
#endif
	color.unpacked.green=green;
}

void Couleur::setVert(int green)
{
#ifdef DEBUG
	cout<<"\033[31;44mDEBUGVERBOSE : setVert de Couleur (int green)\033[0m"<<endl;
#endif
	color.unpacked.green=(unsigned char)clamp(green, 0, UCHAR_MAX);
}

unsigned char Couleur::getVert()const
{
#ifdef DEBUG
	cout<<"\033[32;44mDEBUGVERBOSE : getVert de Couleur\033[0m"<<endl;
#endif
	return color.unpacked.green;
}

void Couleur::setBleu(unsigned char blue)
{
#ifdef DEBUG
	cout<<"\033[31;44mDEBUGVERBOSE : setBleu de Couleur (unsigned char blue)\033[0m"<<endl;
#endif
	color.unpacked.blue=blue;
}

void Couleur::setBleu(int blue)
{
#ifdef DEBUG
	cout<<"\033[31;44mDEBUGVERBOSE : setBleu de Couleur (int blue)\033[0m"<<endl;
#endif
	color.unpacked.blue=(unsigned char)clamp(blue, 0, UCHAR_MAX);
}

unsigned char Couleur::getBleu()const
{
#ifdef DEBUG
	cout<<"\033[32;44mDEBUGVERBOSE : getBleu de Couleur\033[0m"<<endl;
#endif
	return color.unpacked.blue;
}

const Couleur Couleur::NOIR(0xFF000000);
const Couleur Couleur::BLEU(0xFF0000FF);
const Couleur Couleur::VERT(0xFF00FF00);
const Couleur Couleur::ROUGE(0xFFFF0000);
const Couleur Couleur::BLANC(0xFFFFFFFF);

void Couleur::Affiche()const
{
#ifdef DEBUG
	cout<<"\033[33;44mDEBUGVERBOSE : Affiche de Couleur\033[0m"<<endl;
#endif
	cout << "Couleur : " << hex << getARGB() << dec << endl;
}
