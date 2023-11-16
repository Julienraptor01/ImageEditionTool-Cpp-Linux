#ifndef DIMENSION_H
#define DIMENSION_H

#include <iostream>

using std::istream;
using std::ostream;

#ifndef DIMENSION_H_DEFAULT_LARGEUR
#define DIMENSION_H_DEFAULT_LARGEUR 400
#endif
#ifndef DIMENSION_H_DEFAULT_HAUTEUR
#define DIMENSION_H_DEFAULT_HAUTEUR 300
#endif

class Dimension
{
private:
	int largeur, hauteur;

public:
	Dimension();
	~Dimension();
	Dimension(int largeur, int hauteur);
	Dimension(const Dimension &dimension);

	bool operator==(const Dimension &dimension) const;
	bool operator!=(const Dimension &dimension) const;
	friend istream &operator>>(istream &inputStream, Dimension &dimension);
	friend ostream &operator<<(ostream &outputStream, const Dimension &dimension);

	void setLargeur(int largeur);
	int getLargeur() const;
	void setHauteur(int hauteur);
	int getHauteur() const;

	static const Dimension VGA;
	static const Dimension HD;
	static const Dimension FULL_HD;

	void Affiche() const;
};

#endif
