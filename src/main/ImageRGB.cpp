#include "ImageRGB.h"

#include <regex>

#include "MyQT.h"
#include "XYException.h"

using std::cout;
using std::endl;
using std::regex;
using std::regex_replace;
using std::regex_search;

void ImageRGB::createMatrice()
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : createMatrice de ImageRGB\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	matrice = new Couleur *[hauteur];
	for (int i = 0; i < hauteur; i++)
		matrice[i] = new Couleur[largeur];
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin createMatrice de ImageRGB\033[0m" << endl;
#endif
}

void ImageRGB::freeMatrice(Couleur **matrice, const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : freeMatrice de ImageRGB (matrice, dimension)\033[0m" << endl;
#endif
	int hauteur = dimension.getHauteur();
	for (int i = 0; i < hauteur; i++)
	{
		delete[] matrice[i];
	}
	delete[] matrice;
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin freeMatrice de ImageRGB (matrice, dimension)\033[0m" << endl;
#endif
}

void ImageRGB::freeMatrice()
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : freeMatrice de ImageRGB\033[0m" << endl;
#endif
	freeMatrice(matrice, dimension);
	matrice = nullptr;
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin freeMatrice de ImageRGB\033[0m" << endl;
#endif
}

void ImageRGB::copyMatrice(Couleur **matrice, const Dimension &dimension, Couleur **matriceToCopy, const Dimension &dimensionOfMatriceToCopy)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : copyMatrice de ImageRGB (matrice, dimension, matriceToCopy, dimensionOfMatriceToCopy)\033[0m" << endl;
#endif
	int minLargeur = (dimension.getLargeur() < dimensionOfMatriceToCopy.getLargeur()) ? dimension.getLargeur() : dimensionOfMatriceToCopy.getLargeur(), minHauteur = (dimension.getHauteur() < dimensionOfMatriceToCopy.getHauteur()) ? dimension.getHauteur() : dimensionOfMatriceToCopy.getHauteur();
	for (int i = 0; i < minHauteur; i++)
		for (int j = 0; j < minLargeur; j++)
			matrice[i][j] = matriceToCopy[i][j];
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin copyMatrice de ImageRGB (matrice, dimension, matriceToCopy, dimensionOfMatriceToCopy)\033[0m" << endl;
#endif
}

void ImageRGB::copyMatrice(const ImageRGB &image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : copyMatrice de ImageRGB (image)\033[0m" << endl;
#endif
	copyMatrice(matrice, dimension, image.matrice, image.dimension);
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin copyMatrice de ImageRGB (image)\033[0m" << endl;
#endif
}

ImageRGB::ImageRGB() : Image()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur par défaut de ImageRGB\033[0m" << endl;
#endif
	setNom("ImageRGB sans nom");
	setDimension(dimension);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur par défaut de ImageRGB\033[0m" << endl;
#endif
}

ImageRGB::~ImageRGB()
{
#ifdef DEBUG
	cout << "\033[32;41mDEBUG : Destructeur de ImageRGB\033[0m" << endl;
#endif
	if (matrice != nullptr)
		freeMatrice();
#ifdef DEBUG
	cout << "\033[34;41mDEBUG : Fin Destructeur de ImageRGB\033[0m" << endl;
#endif
}

ImageRGB::ImageRGB(int id, const string &nom, const Dimension &dimension) : Image(id)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation complet de ImageRGB\033[0m" << endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1") : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de ImageRGB\033[0m" << endl;
#endif
}

ImageRGB::ImageRGB(int id, const string &nom) : Image(id)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation partiel de ImageRGB (id, nom)\033[0m" << endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1") : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de ImageRGB (id, nom)\033[0m" << endl;
#endif
}

ImageRGB::ImageRGB(const string &nom) : Image()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation partiel de ImageRGB (nom)\033[0m" << endl;
#endif
	static const regex isFileRegex("^(?:\\.?\\/)?(?:.+\\/)*(.+)?(?:\\..+)$");
	bool isFile = regex_search(nom, isFileRegex);
	setNom(isFile ? regex_replace(nom, isFileRegex, "$1") : nom);
	setDimension(dimension);
	if (isFile)
		importFromFile(nom);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de ImageRGB (nom)\033[0m" << endl;
#endif
}

ImageRGB::ImageRGB(const ImageRGB &image) : Image(image)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur de copie de ImageRGB\033[0m" << endl;
#endif
	setDimension(image.getDimension());
	copyMatrice(image);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur de copie de ImageRGB\033[0m" << endl;
#endif
}

ImageRGB &ImageRGB::operator=(const ImageRGB &image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur d'affectation de ImageRGB\033[0m" << endl;
#endif
	setId(image.getId());
	setNom(image.getNom());
	setDimension(image.getDimension());
	copyMatrice(image);
	return *this;
}

ostream &operator<<(ostream &outputStream, const ImageRGB &image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;46mDEBUGVERBOSE : Opérateur d'écriture de ImageRGB\033[0m" << endl;
#endif
	outputStream << image.getId() << " " << image.getNom() << " " << image.getDimension();
	return outputStream;
}

void ImageRGB::setDimension(const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : setDimension de ImageRGB\033[0m" << endl;
#endif
	Couleur **oldMatrice = matrice;
	matrice = nullptr;
	Dimension oldDimension(this->dimension);
	this->dimension = dimension;
	createMatrice();
	if (oldMatrice != nullptr)
	{
		copyMatrice(matrice, this->dimension, oldMatrice, oldDimension);
		freeMatrice(oldMatrice, oldDimension);
	}
}

void ImageRGB::setBackground(const Couleur &couleur)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : setBackground de ImageRGB\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < largeur; i++)
		for (int j = 0; j < hauteur; j++)
			setPixel(i, j, couleur);
}

void ImageRGB::setPixel(int x, int y, const Couleur &couleur)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : setPixel de ImageRGB\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	if ((x < 0 || x >= largeur) && (y < 0 || y >= hauteur))
		throw XYException("setPixel invalide", 'd', x, y);
	if (x < 0 || x >= largeur)
		throw XYException("setPixel invalide", 'x', x);
	if (y < 0 || y >= hauteur)
		throw XYException("setPixel invalide", 'y', y);
	matrice[y][x] = couleur;
}

Couleur ImageRGB::getPixel(int x, int y) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[32;44mDEBUGVERBOSE : getPixel de ImageRGB\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	if ((x < 0 || x >= largeur) && (y < 0 || y >= hauteur))
		throw XYException("getPixel invalide", 'd', x, y);
	if (x < 0 || x >= largeur)
		throw XYException("getPixel invalide", 'x', x);
	if (y < 0 || y >= hauteur)
		throw XYException("getPixel invalide", 'y', y);
	return matrice[y][x];
}

void ImageRGB::Dessine() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Dessine de ImageRGB\033[0m" << endl;
#endif
	MyQT::ViewImage(*this);
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Dessine de ImageRGB\033[0m" << endl;
#endif
}

void ImageRGB::importFromFile(const string &nomFichier)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : importFromFile de ImageRGB\033[0m" << endl;
#endif
	MyQT::ImportFromFile(*this, nomFichier.c_str());
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin importFromFile de ImageRGB\033[0m" << endl;
#endif
}

void ImageRGB::exportToFile(const string &nomFichier, const string &formatFichier) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : exportToFile de ImageRGB\033[0m" << endl;
#endif
	MyQT::ExportToFile(*this, nomFichier.c_str(), formatFichier.c_str());
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin exportToFile de ImageRGB\033[0m" << endl;
#endif
}

void ImageRGB::Save(ofstream &fichier) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Save de ImageRGB\033[0m" << endl;
#endif
	Image::Save(fichier);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < hauteur; i++)
		for (int j = 0; j < largeur; j++)
			getPixel(j, i).Save(fichier);
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Save de ImageRGB\033[0m" << endl;
#endif
}

void ImageRGB::Load(ifstream &fichier)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Load de ImageRGB\033[0m" << endl;
#endif
	Image::Load(fichier);
	Dimension dimension;
	dimension.Load(fichier);
	setDimension(dimension);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < hauteur; i++)
		for (int j = 0; j < largeur; j++)
		{
			Couleur couleur;
			couleur.Load(fichier);
			setPixel(j, i, couleur);
		}
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Load de ImageRGB\033[0m" << endl;
#endif
}
