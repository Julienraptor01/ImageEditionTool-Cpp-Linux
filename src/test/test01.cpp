#include <stdlib.h>
#include <iostream>

using namespace std;

#include "ImageNG.h"

int main()
{
	cout << endl << "(1) ***** Test constructeur par defaut + Affiche *******************************************" << endl;
	{
		ImageNG image;
		image.Affiche();
	}

	cout << endl << "(2) ***** Test des setters et getters ******************************************************" << endl;
	{
		ImageNG image;
		image.Affiche();
		image.setId(3);
		image.setNom("joconde");
		image.Affiche();
		cout << "Nom = " << image.getNom() << endl;
		cout << "Id = " << image.getId() << endl;
	}

	cout << endl << "(3) ***** Test du constructeur d'initialisation ********************************************" << endl;
	{
		ImageNG image(6, "boat");
		image.Affiche();
	}

	cout << endl << "(4) ***** Test du constructeur de copie ****************************************************" << endl;
	{
		ImageNG image1(2, "joconde");
		cout << "image1 (AVANT) :" << endl;
		image1.Affiche();
		{
			ImageNG image2(image1);
			cout << "image2 :" << endl;
			image2.Affiche();
			cout << "--> on modifie la copie" << endl;
			image2.setNom("superman");
			image2.Affiche();
			cout << "--> on detruit la copie" << endl;
		}
		cout << "image1 (APRES) :" << endl;
		image1.Affiche();
	}

	cout << endl << "(5) ***** Test d'allocation dynamique ******************************************************" << endl;
	{
		ImageNG *i = new ImageNG();
		i->Affiche();
		delete i;
		i = new ImageNG(12, "fleur");
		i->setNom("rose");
		i->Affiche();
		delete i;
	}

	return 0;
}
