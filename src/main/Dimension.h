#ifndef DIMENSION_H
#define DIMENSION_H

class Dimension
{
private:
	int largeur;
	int hauteur;

public:
	Dimension();
	~Dimension();
	Dimension(int largeur, int hauteur);
	Dimension(const Dimension &dimension);

	void Affiche();

	void setLargeur(int largeur);
	int getLargeur();
	void setHauteur(int hauteur);
	int getHauteur();
};

#endif