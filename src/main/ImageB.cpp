#include "ImageB.h"
#include "MyQT.h"
#include "XYException.h"

using std::cout;
using std::endl;

void ImageB::createMatrice()
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : createMatrice de ImageB\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	matrice = new bool *[hauteur];
	for (int i = 0; i < hauteur; i++)
	{
		matrice[i] = new bool[largeur];
		for (int j = 0; j < largeur; j++)
			matrice[i][j] = false;
	}
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin createMatrice de ImageB\033[0m" << endl;
#endif
}

void ImageB::freeMatrice(bool **matrice, const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : freeMatrice de ImageB (matrice, dimension)\033[0m" << endl;
#endif
	int hauteur = dimension.getHauteur();
	for (int i = 0; i < hauteur; i++)
	{
		delete[] matrice[i];
	}
	delete[] matrice;
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin freeMatrice de ImageB (matrice, dimension)\033[0m" << endl;
#endif
}

void ImageB::freeMatrice()
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : freeMatrice de ImageB\033[0m" << endl;
#endif
	freeMatrice(matrice, dimension);
	matrice = nullptr;
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin freeMatrice de ImageB\033[0m" << endl;
#endif
}

void ImageB::copyMatrice(bool **matrice, const Dimension &dimension, bool **matriceToCopy, const Dimension &dimensionOfMatriceToCopy)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : copyMatrice de ImageB (matrice, dimension, matriceToCopy, dimensionOfMatriceToCopy)\033[0m" << endl;
#endif
	int minLargeur = (dimension.getLargeur() < dimensionOfMatriceToCopy.getLargeur()) ? dimension.getLargeur() : dimensionOfMatriceToCopy.getLargeur(), minHauteur = (dimension.getHauteur() < dimensionOfMatriceToCopy.getHauteur()) ? dimension.getHauteur() : dimensionOfMatriceToCopy.getHauteur();
	for (int i = 0; i < minHauteur; i++)
		for (int j = 0; j < minLargeur; j++)
			matrice[i][j] = matriceToCopy[i][j];
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin copyMatrice de ImageB (matrice, dimension, matriceToCopy, dimensionOfMatriceToCopy)\033[0m" << endl;
#endif
}

void ImageB::copyMatrice(const ImageB &image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : copyMatrice de ImageB (image)\033[0m" << endl;
#endif
	copyMatrice(matrice, dimension, image.matrice, image.dimension);
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin copyMatrice de ImageB (image)\033[0m" << endl;
#endif
}

ImageB::ImageB() : Image()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur par défaut de ImageB\033[0m" << endl;
#endif
	setNom("ImageB sans nom");
	setDimension(dimension);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur par défaut de ImageB\033[0m" << endl;
#endif
}

ImageB::~ImageB()
{
#ifdef DEBUG
	cout << "\033[32;41mDEBUG : Destructeur de ImageB\033[0m" << endl;
#endif
	if (matrice != nullptr)
		freeMatrice();
#ifdef DEBUG
	cout << "\033[34;41mDEBUG : Fin Destructeur de ImageB\033[0m" << endl;
#endif
}

ImageB::ImageB(int id, const string &nom, const Dimension &dimension) : Image(id)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation complet de ImageB\033[0m" << endl;
#endif
	setNom(nom);
	setDimension(dimension);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation complet de ImageB\033[0m" << endl;
#endif
}

ImageB::ImageB(int id, const string &nom) : Image(id)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation partiel de ImageB (id, nom)\033[0m" << endl;
#endif
	setNom(nom);
	setDimension(dimension);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de ImageB (id, nom)\033[0m" << endl;
#endif
}

ImageB::ImageB(const string &nom) : Image()
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur d'initialisation partiel de ImageB (nom)\033[0m" << endl;
#endif
	setNom(nom);
	setDimension(dimension);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur d'initialisation partiel de ImageB (nom)\033[0m" << endl;
#endif
}

ImageB::ImageB(const ImageB &image) : Image(image)
{
#ifdef DEBUG
	cout << "\033[34;42mDEBUG : Constructeur de copie de ImageB\033[0m" << endl;
#endif
	setDimension(image.getDimension());
	copyMatrice(image);
#ifdef DEBUG
	cout << "\033[31;42mDEBUG : Fin Constructeur de copie de ImageB\033[0m" << endl;
#endif
}

ImageB &ImageB::operator=(const ImageB &image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;45mDEBUGVERBOSE : Opérateur d'affectation de ImageB\033[0m" << endl;
#endif
	setId(image.getId());
	setNom(image.getNom());
	setDimension(image.getDimension());
	copyMatrice(image);
	return *this;
}

ostream &operator<<(ostream &outputStream, const ImageB &image)
{
#ifdef DEBUGVERBOSE
	cout << "\033[33;46mDEBUGVERBOSE : Opérateur d'écriture de ImageB\033[0m" << endl;
#endif
	outputStream << "ImageB : " << image.getNom() << " " << image.getDimension();
	return outputStream;
}

void ImageB::setDimension(const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;43mDEBUGVERBOSE : setDimension de ImageB\033[0m" << endl;
#endif
	bool **oldMatrice = matrice;
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

void ImageB::setBackground(bool couleur)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : setBackground de ImageB\033[0m" << endl;
#endif
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	for (int i = 0; i < hauteur; i++)
		for (int j = 0; j < largeur; j++)
			setPixel(j, i, couleur);
}

void ImageB::setPixel(int x, int y, bool couleur)
{
#ifdef DEBUGVERBOSE
	cout << "\033[31;44mDEBUGVERBOSE : setPixel de ImageB\033[0m" << endl;
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

bool ImageB::getPixel(int x, int y) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[32;44mDEBUGVERBOSE : getPixel de ImageB\033[0m" << endl;
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

Couleur ImageB::couleurFalse(0xFF000000);
Couleur ImageB::couleurTrue(0xFFFFFFFF);

void ImageB::Dessine() const
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Dessine de ImageB\033[0m" << endl;
#endif
	MyQT::ViewImage(*this);
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Dessine de ImageB\033[0m" << endl;
#endif
}

void ImageB::exportToFile(const string &nomFichier, const string &formatFichier) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : exportToFile de ImageB\033[0m" << endl;
#endif
	MyQT::ExportToFile(*this, nomFichier.c_str(), formatFichier.c_str());
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin exportToFile de ImageB\033[0m" << endl;
#endif
}

/*
Il s'agit ici d'une première utilisation des flux en distinguant les flux caractères et les flux
bytes (méthodes write et read). Dans cette première approche, nous ne considérerons que les flux
bytes.
Les classes ImageNG, ImageB et ImageRGB se sérialisent elles-mêmes
On souhaite enregistrer (« sérialiser ») sur disque les différentes images de notre future
application mais dans un format propriétaire (c’est-à-dire propre et uniquement manipulable par
notre application). Cela servira pour la sauvegarde de l’état de notre future application.
On demande donc de compléter les classes ImageNG, ImageB et ImageRGB avec les deux
méthodes suivantes :
 Save(ofstream & fichier) const permettant d’enregistrer sur flux fichier toutes les données
d’une image (id, nom, dimension et matrice de pixels) et cela champ par champ. Le fichier
obtenu sera un fichier binaire (utilisation des méthodes write et read).
 Load(ifstream & fichier) permettant de charger toutes les données relatives à une image
enregistrée sur le flux fichier passé en paramètre.
Afin de vous aider dans le développement, on vous demande d’utiliser l’encapsulation, c’est-à-dire
de laisser chaque classe gérer sa propre sérialisation. En d’autres termes, on vous demande d’ajouter
aux classes Dimension, Image, et Couleur les méthodes suivantes :
• void Save(ofstream & fichier) const : méthode permettant à un objet de s’écrire lui-même
sur le flux fichier qu’il a reçu en paramètre.
• void Load(ifstream & fichier) : méthode permettant à un objet de se lire lui-même sur le
flux fichier qu’il a reçu en paramètre.
Ces méthodes seront appelées par les méthodes Save et Load des classes
ImageNG/ImageB/ImageRGB lorsqu’elle devra enregistrer ou lire ses variables membres dont le
type n’est pas un type de base.
Important
Tous les enregistrements seront de taille variable. Pour l’enregistrement d’une chaine de
caractères « chaine » de type char *, on enregistrera tout d’abord le nombre de caractères de la
chaine (strlen(chaine)) puis ensuite la chaine elle-même. Ainsi, lors de la lecture dans le fichier, on
lit tout d’abord la taille de la chaine et on sait directement combien de caractères il faut allouer et
lire ensuite.
Pour les chaînes de caractères de type string, il faut également faire attention car un objet de type
string a une taille pouvant varier et un code du genre
string chaine = « Je suis la chaine a enregistrer »;
fichierOut.write((char*)&chaine,sizeof(string));
…
string chaineLue;
fichierIn.read((char*)&chaineLue,sizeof(string));
ne fonctionnera pas. Il est nécessaire, comme pour les char* d’enregistrer d’abord le nombre de
caractères de la chaîne puis la chaîne elle-même :
int taille = chaine.size();
fichierOut.write((char*)&taille,sizeof(int));
fichierOut.write((char*)chaine.data(),taille*sizeof(char));
…
int t;
fichierIn.read((char*)&t,sizeof(int));
chaine2.resize(t); // preuve que le type chaine est de taille variable…
fichierIn.read((char*)chaine2.data(),t*sizeof(char));
*/
void ImageB::Save(ofstream &fichier) const
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Save de ImageB\033[0m" << endl;
#endif
	Image::Save(fichier);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	bool *vector = new bool[largeur * hauteur];
	for (int i = 0; i < hauteur; i++)
		for (int j = 0; j < largeur; j++)
			vector[i * largeur + j] = getPixel(j, i);
	fichier.write((char *)vector, largeur * hauteur * sizeof(bool));
	delete[] vector;
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Save de ImageB\033[0m" << endl;
#endif
}

void ImageB::Load(ifstream &fichier)
{
#ifdef DEBUGVERBOSE
	cout << "\033[35;43mDEBUGVERBOSE : Load de ImageB\033[0m" << endl;
#endif
	Image::Load(fichier);
	Dimension dimension;
	dimension.Load(fichier);
	setDimension(dimension);
	int largeur = dimension.getLargeur(), hauteur = dimension.getHauteur();
	bool *vector = new bool[largeur * hauteur];
	fichier.read((char *)vector, largeur * hauteur * sizeof(bool));
	for (int i = 0; i < hauteur; i++)
		for (int j = 0; j < largeur; j++)
			setPixel(j, i, vector[i * largeur + j]);
	delete[] vector;
#ifdef DEBUGVERBOSE
	cout << "\033[36;43mDEBUGVERBOSE : Fin Load de ImageB\033[0m" << endl;
#endif
}
