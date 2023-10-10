#ifndef IMAGENG_H
#define IMAGENG_H

class ImageNG
{
private:
	int id;
	char * nom;

public:
	ImageNG();
	~ImageNG();
	ImageNG(int id, const char *nom);
	ImageNG(const ImageNG &image);

	void Affiche()const;

	void setId(int id);
	int getId()const;
	void setNom(const char *nom);
	char *getNom()const;
};

#endif
