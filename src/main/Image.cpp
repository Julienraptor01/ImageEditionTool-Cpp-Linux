#include "Image.h"
#include "Dimension.h"
#include "MyQT.h"

using std::cout;
using std::endl;

void Image::setId(int id)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[31;44mDEBUGVERBOSE : setId de Image\033[0m"<<endl;
#endif
	this->id=id;
}

int Image::getId()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[32;44mDEBUGVERBOSE : getId de Image\033[0m"<<endl;
#endif
	return id;
}

void Image::setNom(const string &nom)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[31;44mDEBUGVERBOSE : setNom de Image\033[0m"<<endl;
#endif
	this->nom=nom;
}

string Image::getNom()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[32;44mDEBUGVERBOSE : getNom de Image\033[0m"<<endl;
#endif
	return nom;
}

//DON'T USE AS IS, OVERRIDE IT
void Image::setDimension(const Dimension &dimension)
{
#ifdef DEBUGVERBOSE
	cout<<"\033[31;44mDEBUGVERBOSE : setDimension de Image\033[0m"<<endl;
#endif
	cout << "!!! OVERRIDE SETDIMENSION !!!" << endl;
	exit(EXIT_FAILURE);
}

Dimension Image::getDimension()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[32;44mDEBUGVERBOSE : getDimension de Image\033[0m"<<endl;
#endif
	return dimension;
}

void Image::Affiche()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : Affiche de Image\033[0m"<<endl;
#endif
	cout << "Id : " << id << "\t" << "Nom : " << nom << "\t" << "Dimension : (" << dimension << ")" << endl;
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin Affiche de Image\033[0m"<<endl;
#endif
}

void Image::Dessine()const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : Dessine de Image\033[0m"<<endl;
#endif
	//TODO: Remove that nasty cast when all Image derived classes will be implemented
	MyQT::ViewImage((ImageNG&)*this);
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin Dessine de Image\033[0m"<<endl;
#endif
}

void Image::exportToFile(const string &nomFichier, const string &formatFichier)const
{
#ifdef DEBUGVERBOSE
	cout<<"\033[35;43mDEBUGVERBOSE : exportToFile de Image\033[0m"<<endl;
#endif
	//TODO: Remove that nasty cast when all Image derived classes will be implemented
	MyQT::ExportToFile((ImageNG&)*this, nomFichier.c_str(), formatFichier.c_str());
#ifdef DEBUGVERBOSE
	cout<<"\033[36;43mDEBUGVERBOSE : Fin exportToFile de Image\033[0m"<<endl;
#endif
}