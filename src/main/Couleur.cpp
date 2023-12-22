#include "Couleur.h"

#include <algorithm>
#include <limits.h>

#include "ColorException.h"

using std::cout;
using std::dec;
using std::endl;
using std::hex;

Couleur::Couleur()
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;42mDEBUGVERYVERBOSE : Constructeur par défaut de Couleur\033[0m" << endl;
#endif
	setARGB(0xFF000000); // fully opaque black
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;42mDEBUGVERYVERBOSE : Fin Constructeur par défaut de Couleur\033[0m" << endl;
#endif
}

Couleur::~Couleur()
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;41mDEBUGVERYVERBOSE : Destructeur de Couleur\033[0m" << endl;
#endif
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;41mDEBUGVERYVERBOSE : Fin Destructeur de Couleur\033[0m" << endl;
#endif
}

Couleur::Couleur(unsigned int packedARGB)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;42mDEBUGVERYVERBOSE : Constructeur d'initialisation complet de Couleur (packedARGB)\033[0m" << endl;
#endif
	setARGB(packedARGB);
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;42mDEBUGVERYVERBOSE : Fin Constructeur d'initialisation complet de Couleur (packedARGB)\033[0m" << endl;
#endif
}

Couleur::Couleur(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;42mDEBUGVERYVERBOSE : Constructeur d'initialisation complet de Couleur (alpha, red, green, blue)\033[0m" << endl;
#endif
	setAlpha(alpha);
	setRouge(red);
	setVert(green);
	setBleu(blue);
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;42mDEBUGVERYVERBOSE : Fin Constructeur d'initialisation complet de Couleur (alpha, red, green, blue)\033[0m" << endl;
#endif
}

Couleur::Couleur(unsigned char red, unsigned char green, unsigned char blue)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;42mDEBUGVERYVERBOSE : Constructeur d'initialisation partiel de Couleur (unsigned char red, unsigned char green, unsigned char blue)\033[0m" << endl;
#endif
	setAlpha(0xFF); // fully opaque
	setRouge(red);
	setVert(green);
	setBleu(blue);
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;42mDEBUGVERYVERBOSE : Fin Constructeur d'initialisation partiel de Couleur (unsigned char red, unsigned char green, unsigned char blue)\033[0m" << endl;
#endif
}

Couleur::Couleur(int red, int green, int blue)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;42mDEBUGVERYVERBOSE : Constructeur d'initialisation partiel de Couleur (int red, int green, int blue)\033[0m" << endl;
#endif
	setAlpha(0xFF); // fully opaque
	setRouge(red);
	setVert(green);
	setBleu(blue);
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;42mDEBUGVERYVERBOSE : Fin Constructeur d'initialisation partiel de Couleur (int red, int green, int blue)\033[0m" << endl;
#endif
}

Couleur::Couleur(const Couleur &couleur)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[34;42mDEBUGVERYVERBOSE : Constructeur de copie de Couleur\033[0m" << endl;
#endif
	setARGB(couleur.getARGB());
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;42mDEBUGVERYVERBOSE : Fin Constructeur de copie de Couleur\033[0m" << endl;
#endif
}

Couleur &Couleur::operator=(const Couleur &couleur)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur d'affectation de Couleur\033[0m" << endl;
#endif
	setARGB(couleur.getARGB());
	return *this;
}

ostream &operator<<(ostream &outputStream, const Couleur &couleur)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[33;46mDEBUGVERBOSE : Opérateur d'écriture de Couleur\033[0m" << endl;
#endif
	outputStream << hex << static_cast<int>(couleur.getAlpha()) << dec << " " << hex << static_cast<int>(couleur.getRouge()) << dec << " " << hex << static_cast<int>(couleur.getVert()) << dec << " " << hex << static_cast<int>(couleur.getBleu()) << dec;
	return outputStream;
}

void Couleur::setARGB(unsigned int packedARGB)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setARGB de Couleur\033[0m" << endl;
#endif
	color.packedARGB = packedARGB;
}

unsigned int Couleur::getARGB() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : getARGB de Couleur\033[0m" << endl;
#endif
	return color.packedARGB;
}

void Couleur::setAlpha(unsigned char alpha)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setAlpha de Couleur\033[0m" << endl;
#endif
	color.unpacked.alpha = alpha;
}

unsigned char Couleur::getAlpha() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : getAlpha de Couleur\033[0m" << endl;
#endif
	return color.unpacked.alpha;
}

void Couleur::setRouge(unsigned char red)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setRouge de Couleur (unsigned char red)\033[0m" << endl;
#endif
	color.unpacked.red = red;
}

void Couleur::setRouge(int red)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setRouge de Couleur (int red)\033[0m" << endl;
#endif
	if (red < 0 || red > UCHAR_MAX)
		throw ColorException("setRouge invalide", red);
	color.unpacked.red = (unsigned char)red;
}

unsigned char Couleur::getRouge() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : getRouge de Couleur\033[0m" << endl;
#endif
	return color.unpacked.red;
}

void Couleur::setVert(unsigned char green)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setVert de Couleur (unsigned char green)\033[0m" << endl;
#endif
	color.unpacked.green = green;
}

void Couleur::setVert(int green)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setVert de Couleur (int green)\033[0m" << endl;
#endif
	if (green < 0 || green > UCHAR_MAX)
		throw ColorException("setVert invalide", green);
	color.unpacked.green = (unsigned char)green;
}

unsigned char Couleur::getVert() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : getVert de Couleur\033[0m" << endl;
#endif
	return color.unpacked.green;
}

void Couleur::setBleu(unsigned char blue)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setBleu de Couleur (unsigned char blue)\033[0m" << endl;
#endif
	color.unpacked.blue = blue;
}

void Couleur::setBleu(int blue)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[31;44mDEBUGVERYVERBOSE : setBleu de Couleur (int blue)\033[0m" << endl;
#endif
	if (blue < 0 || blue > UCHAR_MAX)
		throw ColorException("setBleu invalide", blue);
	color.unpacked.blue = (unsigned char)blue;
}

unsigned char Couleur::getBleu() const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[32;44mDEBUGVERYVERBOSE : getBleu de Couleur\033[0m" << endl;
#endif
	return color.unpacked.blue;
}

const Couleur Couleur::NOIR(0xFF000000);
const Couleur Couleur::BLEU(0xFF0000FF);
const Couleur Couleur::VERT(0xFF00FF00);
const Couleur Couleur::ROUGE(0xFFFF0000);
const Couleur Couleur::BLANC(0xFFFFFFFF);

void Couleur::Affiche() const
{
	cout << "Couleur : " << hex << color.packedARGB << dec << endl;
}

void Couleur::Save(ofstream &fichier) const
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[35;43mDEBUGVERYVERBOSE : Save de Couleur\033[0m" << endl;
#endif
	unsigned int packedARGB = getARGB();
	fichier.write((char *)&packedARGB, sizeof(unsigned int));
#ifdef DEBUGVERYVERBOSE
	cout << "\033[36;43mDEBUGVERYVERBOSE : Fin Save de Couleur\033[0m" << endl;
#endif
}

void Couleur::Load(ifstream &fichier)
{
#ifdef DEBUGVERYVERBOSE
	cout << "\033[35;43mDEBUGVERYVERBOSE : Load de Couleur\033[0m" << endl;
#endif
	unsigned int packedARGB;
	fichier.read((char *)&packedARGB, sizeof(unsigned int));
	setARGB(packedARGB);
#ifdef DEBUGVERYVERBOSE
	cout << "\033[36;43mDEBUGVERYVERBOSE : Fin Load de Couleur\033[0m" << endl;
#endif
}