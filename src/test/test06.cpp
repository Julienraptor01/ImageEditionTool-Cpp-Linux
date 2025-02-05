#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <QApplication>
#include <time.h>

using namespace std;

#include "Dimension.h"
#include "ImageNG.h"
#include "ImageB.h"
#include "ImageRGB.h"
#include "Couleur.h"
#include "XYException.h"
#include "ColorException.h"

#define CATCH_AFFICHE \
catch (Exception &e) \
{ \
	if (dynamic_cast<ColorException *>(&e)) \
	{ \
		static_cast<ColorException *>(&e)->Affiche(); \
	} \
	else if (dynamic_cast<XYException *>(&e)) \
	{ \
		static_cast<XYException *>(&e)->Affiche(); \
	} \
	else \
	{ \
		e.Affiche(); \
	} \
}

int Menu();
void Essai1();
void Essai2();
void Essai3();
void Essai4();
void Essai5();
void Essai6();

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	close(2);

	int choix;
	bool fini = false;

	while (!fini)
	{
		if (argc == 2)
		{
			choix = atoi(argv[1]);
			fini = true;
		}
		else
			choix = Menu();
		switch (choix)
		{
		case 1:
			Essai1();
			break;
		case 2:
			Essai2();
			break;
		case 3:
			Essai3();
			break;
		case 4:
			Essai4();
			break;
		case 5:
			Essai5();
			break;
		case 6:
			Essai6();
			break;
		default:
			fini = true;
			break;
		}
	}

	return 0;
}

int Menu()
{
	cout << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	cout << "--- JEU DE TEST 6 ---------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	cout << " 1. Tests de ColorException dans la classe Couleur" << endl;
	cout << " 2. Tests de XYException dans la classe Dimension" << endl;
	cout << " 3. Tests de setBackground et set/getPixel dans la classe ImageNG" << endl;
	cout << " 4. Tests des operateurs - < > == de la classe ImageNG" << endl;
	cout << " 5. Tests de set/getPixel dans la classe ImageRGB" << endl;
	cout << " 6. Tests de set/getPixel dans la classe ImageB" << endl;
	cout << " 7. Quitter" << endl << endl;

	int ch;
	cout << "Choix : ";
	cin >> ch;
	cin.ignore();
	return ch;
}

void Essai1()
{
	cout << "***** (1) Tests de ColorException dans la classe Couleur *********************" << endl;
	try
	{
		Couleur c;
		cout << "Couleur cree par defaut = " << c << endl;
		cout << "Modification de la couleur..." << endl;
		int val;
		cout << "Composante Rouge : ";
		cin >> val;
		cin.ignore();
		c.setRouge(val);
		cout << "Composante Verte : ";
		cin >> val;
		cin.ignore();
		c.setVert(val);
		cout << "Composante Bleue : ";
		cin >> val;
		cin.ignore();
		c.setBleu(val);
		cout << "Couleur modifiee = " << c << endl << endl;

		int r, v, b;
		cout << "Creation d'une couleur..." << endl;
		cout << "Composante Rouge : ";
		cin >> r;
		cin.ignore();
		cout << "Composante Verte : ";
		cin >> v;
		cin.ignore();
		cout << "Composante Bleue : ";
		cin >> b;
		cin.ignore();
		Couleur c1(r, v, b);
		cout << "Couleur creee = " << c1 << endl << endl;
	}
	CATCH_AFFICHE;
	cout << endl;
}

void Essai2()
{
	cout << "***** (2) Tests de XYException dans la classe Dimension *********************" << endl;
	try
	{
		Dimension d;
		cout << "Dimension creee par defaut = " << d << endl;
		cout << "Modification de la dimension..." << endl;
		int val;
		cout << "Largeur : ";
		cin >> val;
		cin.ignore();
		d.setLargeur(val);
		cout << "Hauteur : ";
		cin >> val;
		cin.ignore();
		d.setHauteur(val);
		cout << "Dimension modifiee = " << d << endl << endl;

		int l, h;
		cout << "Creation d'une dimension..." << endl;
		cout << "Largeur : ";
		cin >> l;
		cin.ignore();
		cout << "Hauteur : ";
		cin >> h;
		cin.ignore();
		Dimension d1(l, h);
		cout << "Dimension creee = " << d1 << endl << endl;

		cout << "Modification d'une dimension par saisie clavier..." << endl;
		cin >> d1;
		cout << "Dimension saisie : " << d1 << endl;
	}
	CATCH_AFFICHE;
	cout << endl;
}

void Essai3()
{
	cout << "***** (3) Tests de setBackground et set/getPixel dans la classe ImageNG ******************" << endl;
	try
	{
		ImageNG im;
		cout << "ImageNG creee par defaut :" << endl << im << endl;
		im.Dessine();
		int val;
		cout << "Nouveau fond : ";
		cin >> val;
		cin.ignore();
		im.setBackground(val);
		cout << "Image modifiee :" << endl << im << endl;
		im.Dessine();

		int x, y;
		cout << "Dessin d'un pixel..." << endl;
		cout << "x : ";
		cin >> x;
		cin.ignore();
		cout << "y : ";
		cin >> y;
		cin.ignore();
		cout << "Niveau de gris : ";
		cin >> val;
		cin.ignore();
		im.setPixel(x, y, val);
		cout << "Image modifiee :" << endl << im << endl;
		im.Dessine();

		cout << "Recuperation valeur d'un pixel..." << endl;
		cout << "x : ";
		cin >> x;
		cin.ignore();
		cout << "y : ";
		cin >> y;
		cin.ignore();
		cout << "Valeur en (" << x << "," << y << ") = " << im.getPixel(x, y) << endl << endl;
	}
	CATCH_AFFICHE;
	cout << endl;
}

void Essai4()
{
	cout << "***** (4) Tests des operateurs - < > == de la classe ImageNG ******************" << endl;
	try
	{
		ImageNG im1, im2;
		cout << "Choisissez deux images parmi " << endl;
		cout << "a) joconde.bmp" << endl;
		cout << "b) lena.bmp" << endl;
		cout << "c) bulles.bmp" << endl;
		char ch;
		cout << "Image 1 : ";
		cin >> ch;
		cin.ignore();
		switch (ch)
		{
		case 'a':
			im1.importFromFile("./src/assets/images/joconde.bmp");
			break;
		case 'b':
			im1.importFromFile("./src/assets/images/lena.bmp");
			break;
		default:
			im1.importFromFile("./src/assets/images/bulles.bmp");
			break;
		}
		cout << "Image 2 : ";
		cin >> ch;
		cin.ignore();
		switch (ch)
		{
		case 'a':
			im2.importFromFile("./src/assets/images/joconde.bmp");
			break;
		case 'b':
			im2.importFromFile("./src/assets/images/lena.bmp");
			break;
		default:
			im2.importFromFile("./src/assets/images/bulles.bmp");
			break;
		}
		cout << "Voici image 1 :" << endl << im1 << endl;
		im1.Dessine();
		cout << "Voici image 2 :" << endl << im2 << endl;
		im2.Dessine();

		cout << "Comparaison (c) ou difference (d) ? ";
		cin >> ch;
		cin.ignore();

		if (ch == 'c')
		{
			cout << "Comparaison des deux images..." << endl;
			if (im1 < im2)
				cout << "image1 < image2" << endl;
			else if (im1 > im2)
				cout << "image1 > image2" << endl;
			else if (im1 == im2)
				cout << "image1 ==image2" << endl;
			else
				cout << "Aucune des 3 possibilités" << endl;
		}
		else
		{
			cout << "Difference des deux images..." << endl;
			ImageNG im = im1 - im2;
			cout << "Voici l'image resultat :" << endl << im << endl;
			im.Dessine();
		}
	}
	CATCH_AFFICHE;
	cout << endl;
}

void Essai5()
{
	cout << "***** (5) Tests de set/getPixel dans la classe ImageRGB *************************" << endl;
	try
	{
		ImageRGB im;
		cout << "ImageRGB creee par defaut :" << endl;
		cout << "On modifie la couleur du fond..." << endl;
		im.setBackground(Couleur(0, 255, 255));
		cout << "Image modifiee :" << endl << im << endl;
		im.Dessine();

		int x, y;
		cout << "Dessin d'un pixel..." << endl;
		cout << "x : ";
		cin >> x;
		cin.ignore();
		cout << "y : ";
		cin >> y;
		cin.ignore();
		im.setPixel(x, y, Couleur(255, 0, 0));
		cout << "Image modifiee :" << endl << im << endl;
		im.Dessine();

		cout << "Recuperation valeur d'un pixel..." << endl;
		cout << "x : ";
		cin >> x;
		cin.ignore();
		cout << "y : ";
		cin >> y;
		cin.ignore();
		cout << "Valeur en (" << x << "," << y << ") = " << im.getPixel(x, y) << endl << endl;
	}
	CATCH_AFFICHE;
	cout << endl;
}

void Essai6()
{
	cout << "***** (6) Tests de set/getPixel dans la classe ImageB ***************************" << endl; 
	try
	{
		ImageB im;
		cout << "ImageB creee par defaut :" << endl << im << endl;
		im.Dessine();

		int x, y;
		cout << "Dessin d'un pixel..." << endl;
		cout << "x : ";
		cin >> x;
		cin.ignore();
		cout << "y : ";
		cin >> y;
		cin.ignore();
		im.setPixel(x, y, true);
		cout << "Image modifiee :" << endl << im << endl;
		im.Dessine();

		cout << "Recuperation valeur d'un pixel..." << endl;
		cout << "x : ";
		cin >> x;
		cin.ignore();
		cout << "y : ";
		cin >> y;
		cin.ignore();
		cout << "Valeur en (" << x << "," << y << ") = " << im.getPixel(x, y) << endl << endl;
	}
	CATCH_AFFICHE;
	cout << endl;
}
