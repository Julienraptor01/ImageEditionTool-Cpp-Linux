#include "Image.h"

#include "MyQT.h"

using std::cout;
using std::endl;

Image::Image()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur par défaut de Image\033[0m" << endl;
#endif
	setId(0);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur par défaut de Image\033[0m" << endl;
#endif
}

Image::~Image()
{
#ifdef DEBUG
	cout << "\033[32;41mDEBUG : Destructeur de Image\033[0m" << endl;
#endif
#ifdef DEBUG
	cout << "\033[34;41mDEBUG : Fin Destructeur de Image\033[0m" << endl;
#endif
}

Image::Image(int id)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation partiel de Image (id, dimension)\033[0m" << endl;
#endif
	setId(id);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de Image (id, dimension)\033[0m" << endl;
#endif
}

Image::Image(const Image &image)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur de copie de Image\033[0m" << endl;
#endif
	setId(image.getId());
	setNom(image.getNom());
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur de copie de Image\033[0m" << endl;
#endif
}

void Image::setId(int id)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : setId de Image\033[0m" << endl;
#endif
	this->id = id;
}

int Image::getId() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[32;44mDEBUGVERBOSE : getId de Image\033[0m" << endl;
#endif
	return id;
}

void Image::setNom(const string &nom)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : setNom de Image\033[0m" << endl;
#endif
	this->nom = nom;
}

string Image::getNom() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[32;44mDEBUGVERBOSE : getNom de Image\033[0m" << endl;
#endif
	return nom;
}

Dimension Image::getDimension() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[32;44mDEBUGVERBOSE : getDimension de Image\033[0m" << endl;
#endif
	return dimension;
}

void Image::Affiche() const
{
	cout << "Id : " << id << "\t" << "Nom : " << nom << "\t" << "Dimension : (" << dimension << ")" << endl;
}

void Image::Save(ofstream &fichier) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Save de Image\033[0m" << endl;
#endif
	int id = getId();
	fichier.write(reinterpret_cast<char *>(&id), sizeof(int));
	string nom = getNom();
	int taille = nom.size();
	fichier.write(reinterpret_cast<char *>(&taille), sizeof(int));
	fichier.write(nom.data(), taille * sizeof(char));
	Dimension dimension = getDimension();
	dimension.Save(fichier);
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Save de Image\033[0m" << endl;
#endif
}

void Image::Load(ifstream &fichier)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Load de Image\033[0m" << endl;
#endif
	int id;
	fichier.read(reinterpret_cast<char *>(&id), sizeof(int));
	setId(id);
	string nom;
	int taille;
	fichier.read(reinterpret_cast<char *>(&taille), sizeof(int));
	nom.resize(taille);
	fichier.read(nom.data(), taille * sizeof(char));
	setNom(nom);
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Load de Image\033[0m" << endl;
#endif
}
