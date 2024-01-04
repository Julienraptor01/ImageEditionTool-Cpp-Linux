#include <iostream>
#include <unistd.h>
#include <QApplication>

using namespace std;

#include "ImageNG.h"
#include "ImageB.h"
#include "ImageRGB.h"
#include "Traitements.h"
#include "PhotoShop.h"

int main(int argc,char* argv[])
{
	// Initialisation de QT
	QApplication app(argc,argv);
	close(2);

	// Creation du Garage
	PhotoShop ps;

	// Ajout d'images
	cout << endl << "//***** Ajout d'images à la biblothèque ******************************" << endl;
	cout << "Ajout image NG \"./src/assets/images/joconde.bmp\"..." << endl;
	ps.ajouteImage(new ImageNG("./src/assets/images/joconde.bmp"));

	cout << "Ajout image NG \"./src/assets/images/lena.bmp\"..." << endl;
	ImageNG *p = new ImageNG();
	p->importFromFile("./src/assets/images/lena.bmp");
	p->setNom("lena");
	ps.ajouteImage(p);

	cout << "Ajout image B lena seuillée à 127..." << endl;
	ps.ajouteImage(new ImageB(Traitements::Seuillage(*p,127)));

	cout << "Ajout image NG dessin à moi..." << endl;
	p = new ImageNG();
	p->setNom("monDessin");
	p->setDimension(Dimension(400,200));
	p->setBackground(100);
	for(int i=0 ; i<200 ; i++)
		p->setPixel(i,i,250);
	ps.ajouteImage(p);

	cout << "Ajout image RGB \"./src/assets/images/mandrill.bmp\"..." << endl;
	ps.ajouteImage(new ImageRGB("./src/assets/images/mandrill.bmp"));

	cout << endl << "//***** Images de la biblothèque *************************************" << endl;
	ps.afficheImages();
	ps.dessineImages();

	cout << endl << "//***** Ajout de 2 images par copie **********************************" << endl;
	cout << "Copie image id=3..." << endl;
	Image* pImage = ps.getImageParId(3);
	ImageB *pB = dynamic_cast<ImageB*>(pImage);
	ps.ajouteImage(new ImageB(*pB));
	cout << "Copie image indice=1..." << endl;
	pImage = ps.getImageParIndice(1);
	ImageNG *pNG = dynamic_cast<ImageNG*>(pImage);
	ps.ajouteImage(new ImageNG(*pNG));

	cout << endl << "//***** Images de la biblothèque *************************************" << endl;
	ps.afficheImages();

	cout << endl << "//***** Apres suppression par indice (1) *****************************" << endl;
	ps.supprimeImageParIndice(1);
	ps.afficheImages();

	cout << endl << "//***** Apres suppression par id (4) *********************************" << endl;
	ps.supprimeImageParId(4);
	ps.afficheImages();

	return 0;
}
