#ifndef COULEUR_H
#define COULEUR_H

#include <iostream>

using std::ostream;

class Couleur
{
private:
	typedef union
	{
		unsigned int packedARGB;
		struct
		{
			unsigned char blue;
			unsigned char green;
			unsigned char red;
			unsigned char alpha;
		} unpacked;
	} argb;
	argb color;

public:
	Couleur();
	~Couleur();
	Couleur(unsigned int packedARGB);
	Couleur(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue);
	Couleur(unsigned char red, unsigned char green, unsigned char blue);
	Couleur(int red, int green, int blue);
	Couleur(const Couleur &couleur);

	Couleur &operator=(const Couleur &couleur);
	friend ostream &operator<<(ostream &outputStream, const Couleur &couleur);

	void setARGB(unsigned int packedARGB);
	unsigned int getARGB() const;
	void setAlpha(unsigned char alpha);
	unsigned char getAlpha() const;
	void setRouge(unsigned char red);
	void setRouge(int red);
	unsigned char getRouge() const;
	void setVert(unsigned char green);
	void setVert(int green);
	unsigned char getVert() const;
	void setBleu(unsigned char blue);
	void setBleu(int blue);
	unsigned char getBleu() const;

	static const Couleur NOIR;
	static const Couleur BLEU;
	static const Couleur VERT;
	static const Couleur ROUGE;
	static const Couleur BLANC;

	void Affiche() const;
};

#endif
