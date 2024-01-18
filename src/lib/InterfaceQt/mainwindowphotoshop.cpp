#include "mainwindowphotoshop.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QScreen>
#include <QRect>
#include <QPixmap>
#include <QColorDialog>
#include <iostream>

#include "ui_mainwindowphotoshop.h"
#include "PhotoShop.h"
#include "Iterateur.h"
#include "Traitements.h"
#include "XYException.h"
#include "ColorException.h"
#include "Couleur.h"

using std::to_string;

#define CATCH_AFFICHE                                     \
	catch (Exception & e)                                 \
	{                                                     \
		if (dynamic_cast<ColorException *>(&e))           \
		{                                                 \
			static_cast<ColorException *>(&e)->Affiche(); \
		}                                                 \
		else if (dynamic_cast<XYException *>(&e))         \
		{                                                 \
			static_cast<XYException *>(&e)->Affiche();    \
		}                                                 \
		else                                              \
		{                                                 \
			e.Affiche();                                  \
		}                                                 \
	}

MainWindowPhotoShop::MainWindowPhotoShop(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindowPhotoShop)
{
	ui->setupUi(this);
	setTitre("Mini-PhotoShop en C++");

	// Centrage de la fenetre
	QScreen *screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->availableGeometry();
	int x = (screenGeometry.width() - width()) / 2;
	int y = (screenGeometry.height() - height()) / 2;
	move(x, y);
	setFixedSize(1021, 845);

	// Configuration de la table des images
	ui->tableWidgetImages->setColumnCount(4);
	ui->tableWidgetImages->setRowCount(0);
	QStringList labelsTableOptions;
	labelsTableOptions << "Id"
					   << "Type"
					   << "Dimension"
					   << "Nom";
	ui->tableWidgetImages->setHorizontalHeaderLabels(labelsTableOptions);
	ui->tableWidgetImages->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableWidgetImages->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidgetImages->horizontalHeader()->setVisible(true);
	ui->tableWidgetImages->horizontalHeader()->setDefaultSectionSize(100);
	ui->tableWidgetImages->horizontalHeader()->setStretchLastSection(true);
	ui->tableWidgetImages->verticalHeader()->setVisible(false);
	ui->tableWidgetImages->horizontalHeader()->setStyleSheet("background-color: lightyellow");

	// Intialisation des scrollArea
	setImageNG("selection");
	setImageNG("operande1");
	setImageNG("operande2");
	setImageNG("resultat");

	// ComboBox des traitements disponibles
	ajouteTraitementDisponible("Eclaircir (+ val)");
	ajouteTraitementDisponible("Eclaircir (++)");
	ajouteTraitementDisponible("Assombrir (- val)");
	ajouteTraitementDisponible("Assombrir (--)");
	ajouteTraitementDisponible("Différence");
	ajouteTraitementDisponible("Comparaison (==)");
	ajouteTraitementDisponible("Comparaison (<)");
	ajouteTraitementDisponible("Comparaison (>)");
	ajouteTraitementDisponible("Seuillage");
	ajouteTraitementDisponible("Filtre moyenneur");
	ajouteTraitementDisponible("Filtre médian");
	ajouteTraitementDisponible("Erosion");
	ajouteTraitementDisponible("Dilatation");
	ajouteTraitementDisponible("Négatif");

	// Etape 14 (TO DO)
	// Restauration bibliothèque via fichier de sauvegarde
}

MainWindowPhotoShop::~MainWindowPhotoShop()
{
	delete ui;
}

void MainWindowPhotoShop::setTitre(string titre)
{
	this->setWindowTitle(titre.c_str());
}

void MainWindowPhotoShop::setNomImage(string nom)
{
	ui->lineEditNom->setText(QString::fromStdString(nom));
}

string MainWindowPhotoShop::getNomImage() const
{
	return ui->lineEditNom->text().toStdString();
}

void MainWindowPhotoShop::setParametresImageNG(int max, int min, int luminance, float contraste)
{
	if (max == -1)
	{
		ui->lineEditMax->setText("");
		ui->lineEditMin->setText("");
		ui->lineEditLuminance->setText("");
		ui->lineEditContraste->setText("");
		return;
	}
	char tmp[20];
	sprintf(tmp, "%d", max);
	ui->lineEditMax->setText(tmp);
	sprintf(tmp, "%d", min);
	ui->lineEditMin->setText(tmp);
	sprintf(tmp, "%d", luminance);
	ui->lineEditLuminance->setText(tmp);
	sprintf(tmp, "%f", contraste);
	ui->lineEditContraste->setText(tmp);
}

void MainWindowPhotoShop::setImageNG(string destination, const ImageNG *imageng)
{
	QPixmap *pixmap = NULL;
	if (imageng != NULL)
	{
		// Creation du QPixmap
		int largeur = imageng->getDimension().getLargeur();
		int hauteur = imageng->getDimension().getHauteur();
		QImage im1(largeur, hauteur, QImage::Format_RGB32);
		for (int x = 0; x < largeur; x++)
			for (int y = 0; y < hauteur; y++)
			{
				int valeur = imageng->getPixel(x, y);
				im1.setPixel(x, y, qRgb(valeur, valeur, valeur));
			}
		pixmap = new QPixmap(QPixmap::fromImage(im1));
	}

	// Mise en place du QPixmap
	QLabel *label = new QLabel();
	label->setAlignment(Qt::AlignCenter);
	if (pixmap)
		label->setPixmap(*pixmap);
	else
		label->setText("vide");
	if (destination == "selection")
		ui->scrollAreaSelection->setWidget(label);
	if (destination == "operande1")
		ui->scrollAreaOperande1->setWidget(label);
	if (destination == "operande2")
		ui->scrollAreaOperande2->setWidget(label);
	if (destination == "resultat")
		ui->scrollAreaResultat->setWidget(label);
}

void MainWindowPhotoShop::setImageRGB(string destination, const ImageRGB *imagergb)
{
	QPixmap *pixmap = NULL;
	if (imagergb != NULL)
	{
		// Creation du QPixmap
		int largeur = imagergb->getDimension().getLargeur();
		int hauteur = imagergb->getDimension().getHauteur();
		QImage im1(largeur, hauteur, QImage::Format_RGB32);
		for (int x = 0; x < largeur; x++)
			for (int y = 0; y < hauteur; y++)
			{
				Couleur valeur = imagergb->getPixel(x, y);
				im1.setPixel(x, y, qRgb(valeur.getRouge(), valeur.getVert(), valeur.getBleu()));
			}
		pixmap = new QPixmap(QPixmap::fromImage(im1));
	}

	// Mise en place du QPixmap
	QLabel *label = new QLabel();
	label->setAlignment(Qt::AlignCenter);
	if (pixmap)
		label->setPixmap(*pixmap);
	else
		label->setText("vide");
	if (destination == "selection")
		ui->scrollAreaSelection->setWidget(label);
	if (destination == "operande1")
		ui->scrollAreaOperande1->setWidget(label);
	if (destination == "operande2")
		ui->scrollAreaOperande2->setWidget(label);
	if (destination == "resultat")
		ui->scrollAreaResultat->setWidget(label);
}

void MainWindowPhotoShop::setImageB(string destination, const ImageB *imageb)
{
	QPixmap *pixmap = NULL;
	if (imageb != NULL)
	{
		// Creation du QPixmap
		int largeur = imageb->getDimension().getLargeur();
		int hauteur = imageb->getDimension().getHauteur();
		QImage im1(largeur, hauteur, QImage::Format_RGB32);
		for (int x = 0; x < largeur; x++)
			for (int y = 0; y < hauteur; y++)
			{
				bool valeur = imageb->getPixel(x, y);
				if (valeur)
					im1.setPixel(x, y, qRgb(ImageB::couleurTrue.getRouge(), ImageB::couleurTrue.getVert(), ImageB::couleurTrue.getBleu()));
				else
					im1.setPixel(x, y, qRgb(ImageB::couleurFalse.getRouge(), ImageB::couleurFalse.getVert(), ImageB::couleurFalse.getBleu()));
			}
		pixmap = new QPixmap(QPixmap::fromImage(im1));
	}

	// Mise en place du QPixmap
	QLabel *label = new QLabel();
	label->setAlignment(Qt::AlignCenter);
	if (pixmap)
		label->setPixmap(*pixmap);
	else
		label->setText("vide");
	if (destination == "selection")
		ui->scrollAreaSelection->setWidget(label);
	if (destination == "operande1")
		ui->scrollAreaOperande1->setWidget(label);
	if (destination == "operande2")
		ui->scrollAreaOperande2->setWidget(label);
	if (destination == "resultat")
		ui->scrollAreaResultat->setWidget(label);
}

void MainWindowPhotoShop::setResultatBoolean(int val)
{
	if (val == 1) // vrai
	{
		ui->checkBoxResultat->setChecked(true);
		ui->checkBoxResultat->setText("VRAI");
		ui->checkBoxResultat->setStyleSheet("background-color: lightgreen;border: 1px solid black;");
		return;
	}
	if (val == 0) // faux
	{
		ui->checkBoxResultat->setChecked(false);
		ui->checkBoxResultat->setText("FAUX");
		ui->checkBoxResultat->setStyleSheet("background-color: red;border: 1px solid black;");
		return;
	}
	// ni vrai, ni faux
	ui->checkBoxResultat->setChecked(false);
	ui->checkBoxResultat->setText("Résultat");
	ui->checkBoxResultat->setStyleSheet("background-color: lightyellow;border: 1px solid black;");
}

void MainWindowPhotoShop::ajouteTupleTableImages(int id, string type, string dimension, string nom)
{
	char Id[20];
	sprintf(Id, "%d", id);

	char Type[20];
	strcpy(Type, type.c_str());

	char Dimension[20];
	strcpy(Dimension, dimension.c_str());

	char Nom[80];
	strcpy(Nom, nom.c_str());

	// Ajout possible
	int nbLignes = ui->tableWidgetImages->rowCount();
	nbLignes++;
	ui->tableWidgetImages->setRowCount(nbLignes);
	ui->tableWidgetImages->setRowHeight(nbLignes - 1, 20);

	QTableWidgetItem *item = new QTableWidgetItem;
	item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	item->setTextAlignment(Qt::AlignCenter);
	item->setText(Id);
	ui->tableWidgetImages->setItem(nbLignes - 1, 0, item);

	item = new QTableWidgetItem;
	item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	item->setTextAlignment(Qt::AlignCenter);
	item->setText(Type);
	ui->tableWidgetImages->setItem(nbLignes - 1, 1, item);

	item = new QTableWidgetItem;
	item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	item->setTextAlignment(Qt::AlignCenter);
	item->setText(Dimension);
	ui->tableWidgetImages->setItem(nbLignes - 1, 2, item);

	item = new QTableWidgetItem;
	item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	item->setText(Nom);
	ui->tableWidgetImages->setItem(nbLignes - 1, 3, item);
}

void MainWindowPhotoShop::videTableImages()
{
	ui->tableWidgetImages->setRowCount(0);
}

int MainWindowPhotoShop::getIndiceImageSelectionnee()
{
	QModelIndexList liste = ui->tableWidgetImages->selectionModel()->selectedRows();
	if (liste.size() == 0)
		return -1;
	QModelIndex index = liste.at(0);
	int indice = index.row();
	return indice;
}

void MainWindowPhotoShop::ajouteTraitementDisponible(string operation)
{
	ui->comboBoxTraitements->addItem(operation.c_str());
}

void MainWindowPhotoShop::videTraitementsDisponibles()
{
	ui->comboBoxTraitements->clear();
}

string MainWindowPhotoShop::getTraitementSelectionne() const
{
	return ui->comboBoxTraitements->currentText().toStdString();
}

void MainWindowPhotoShop::dialogueMessage(const char *titre, const char *message)
{
	QMessageBox::information(this, titre, message);
}

void MainWindowPhotoShop::dialogueErreur(const char *titre, const char *message)
{
	QMessageBox::critical(this, titre, message);
}

string MainWindowPhotoShop::dialogueDemandeTexte(const char *titre, const char *question)
{
	QString chaine = QInputDialog::getText(this, titre, question);
	return chaine.toStdString();
}

int MainWindowPhotoShop::dialogueDemandeInt(const char *titre, const char *question)
{
	return QInputDialog::getInt(this, titre, question);
}

float MainWindowPhotoShop::dialogueDemandeFloat(const char *titre, const char *question)
{
	return QInputDialog::getDouble(this, titre, question);
}

string MainWindowPhotoShop::dialogueDemandeFichierOuvrir(const char *question)
{
	QString fileName = QFileDialog::getOpenFileName(this, question, "", "Tous les fichiers (*.*)");
	return fileName.toStdString();
}

string MainWindowPhotoShop::dialogueDemandeFichierEnregistrer(const char *question)
{
	QString fileName = QFileDialog::getSaveFileName(this, question, "", "Tous les fichiers (*.*)");
	return fileName.toStdString();
}

void MainWindowPhotoShop::dialogueDemandeCouleur(const char *message, int *pRouge, int *pVert, int *pBleu)
{
	QColor color = QColorDialog::getColor(Qt::red, this, message);
	*pRouge = color.red();
	*pVert = color.green();
	*pBleu = color.blue();
}

void MainWindowPhotoShop::closeEvent(QCloseEvent *event)
{
	if (event == NULL)
	{
	} // pour éviter le warning à la compilation
	// Etape 14 (TO DO)

	QApplication::exit();
}

void MainWindowPhotoShop::on_actionQuitter_triggered()
{
	// Etape 14 (TO DO)

	QApplication::exit();
}

void MainWindowPhotoShop::on_actionCharger_ImageNB_triggered()
{
	PhotoShop::getInstance().ajouteImage(new ImageNG(dialogueDemandeFichierOuvrir("Choisissez une image")));
	videTableImages();
	ArrayList<Image *> images = PhotoShop::getInstance().getImages();
	Iterateur<Image *> it(images);
	Image *image = nullptr;
	for (it.reset(); !it.end(); it++)
	{
		image = it;
		if (dynamic_cast<ImageNG *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "NG", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageRGB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "RGB", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "B", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
	}
}

void MainWindowPhotoShop::on_actionCharger_ImageRGB_triggered()
{
	PhotoShop::getInstance().ajouteImage(new ImageRGB(dialogueDemandeFichierOuvrir("Choisissez une image")));
	videTableImages();
	ArrayList<Image *> images = PhotoShop::getInstance().getImages();
	Iterateur<Image *> it(images);
	Image *image = nullptr;
	for (it.reset(); !it.end(); it++)
	{
		image = it;
		if (dynamic_cast<ImageNG *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "NG", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageRGB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "RGB", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "B", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
	}
}

void MainWindowPhotoShop::on_actionEnregistrer_ImageNB_triggered()
{
	int indice = getIndiceImageSelectionnee();
	if (indice == -1)
	{
		dialogueErreur("Erreur", "Aucune image sélectionnée");
		return;
	}
	Image *image = PhotoShop::getInstance().getImageParIndice(indice);
	if (dynamic_cast<ImageNG *>(image) == nullptr)
	{
		dialogueErreur("Erreur", "L'image sélectionnée n'est pas de type ImageNG");
		return;
	}
	string nomFichier = dialogueDemandeFichierEnregistrer("Choisissez un nom de fichier");
	string formatFichier = dialogueDemandeTexte("Format", "Choisissez un format de fichier");
	image->exportToFile(nomFichier.append(".").append(formatFichier), formatFichier);
}

void MainWindowPhotoShop::on_actionEnregistrer_ImageRGB_triggered()
{
	int indice = getIndiceImageSelectionnee();
	if (indice == -1)
	{
		dialogueErreur("Erreur", "Aucune image sélectionnée");
		return;
	}
	Image *image = PhotoShop::getInstance().getImageParIndice(indice);
	if (dynamic_cast<ImageRGB *>(image) == nullptr)
	{
		dialogueErreur("Erreur", "L'image sélectionnée n'est pas de type ImageRGB");
		return;
	}
	string nomFichier = dialogueDemandeFichierEnregistrer("Choisissez un nom de fichier");
	string formatFichier = dialogueDemandeTexte("Format", "Choisissez un format de fichier");
	image->exportToFile(nomFichier.append(".").append(formatFichier), formatFichier);
}

void MainWindowPhotoShop::on_actionEnregistrer_ImageB_triggered()
{
	int indice = getIndiceImageSelectionnee();
	if (indice == -1)
	{
		dialogueErreur("Erreur", "Aucune image sélectionnée");
		return;
	}
	Image *image = PhotoShop::getInstance().getImageParIndice(indice);
	if (dynamic_cast<ImageB *>(image) == nullptr)
	{
		dialogueErreur("Erreur", "L'image sélectionnée n'est pas de type ImageB");
		return;
	}
	string nomFichier = dialogueDemandeFichierEnregistrer("Choisissez un nom de fichier");
	string formatFichier = dialogueDemandeTexte("Format", "Choisissez un format de fichier");
	image->exportToFile(nomFichier.append(".").append(formatFichier), formatFichier);
}

void MainWindowPhotoShop::on_actionImage_selectionn_e_triggered()
{
	int indice = getIndiceImageSelectionnee();
	if (indice == -1)
	{
		dialogueErreur("Erreur", "Aucune image sélectionnée");
		return;
	}
	PhotoShop::getInstance().supprimeImageParIndice(indice);
	videTableImages();
	ArrayList<Image *> images = PhotoShop::getInstance().getImages();
	Iterateur<Image *> it(images);
	Image *image = nullptr;
	for (it.reset(); !it.end(); it++)
	{
		image = it;
		if (dynamic_cast<ImageNG *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "NG", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageRGB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "RGB", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "B", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
	}
}

void MainWindowPhotoShop::on_actionImage_par_id_triggered()
{
	int id = dialogueDemandeInt("Id", "Entrez l'id de l'image à supprimer");
	PhotoShop::getInstance().supprimeImageParId(id);
	videTableImages();
	ArrayList<Image *> images = PhotoShop::getInstance().getImages();
	Iterateur<Image *> it(images);
	Image *image = nullptr;
	for (it.reset(); !it.end(); it++)
	{
		image = it;
		if (dynamic_cast<ImageNG *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "NG", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageRGB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "RGB", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "B", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
	}
}

void MainWindowPhotoShop::on_actionCouleur_TRUE_pour_ImageB_triggered()
{
	int red, green, blue;
	dialogueDemandeCouleur("Choisissez une couleur", &red, &green, &blue);
	ImageB::couleurTrue = Couleur(red, green, blue);
}

void MainWindowPhotoShop::on_actionCouleur_FALSE_pour_imageB_triggered()
{
	int red, green, blue;
	dialogueDemandeCouleur("Choisissez une couleur", &red, &green, &blue);
	ImageB::couleurFalse = Couleur(red, green, blue);
}

void MainWindowPhotoShop::on_actionImporterCSV_triggered()
{
	// Etape 13 (TO DO)
}

void MainWindowPhotoShop::on_actionReset_triggered()
{
	// Etape 14 (TO DO)
}

void MainWindowPhotoShop::on_tableWidgetImages_itemSelectionChanged()
{
	int indice = getIndiceImageSelectionnee();
	Image *image = PhotoShop::getInstance().getImageParIndice(indice);
	setNomImage(image->getNom());
	ImageNG *imageNG = dynamic_cast<ImageNG *>(image);
	if (imageNG != nullptr)
	{
		setParametresImageNG(imageNG->getMaximum(), imageNG->getMinimum(), imageNG->getLuminance(), imageNG->getContraste());
		setImageNG("selection", imageNG);
		return;
	}
	ImageRGB *imageRGB = dynamic_cast<ImageRGB *>(image);
	if (imageRGB != nullptr)
	{
		setParametresImageNG();
		setImageRGB("selection", imageRGB);
		return;
	}
	ImageB *imageB = dynamic_cast<ImageB *>(image);
	if (imageB != nullptr)
	{
		setParametresImageNG();
		setImageB("selection", imageB);
		return;
	}
}

void MainWindowPhotoShop::on_pushButtonModifierNom_clicked()
{
	string nom = getNomImage();
	int indice = getIndiceImageSelectionnee();
	Image *image = PhotoShop::getInstance().getImageParIndice(indice);
	image->setNom(nom);
	videTableImages();
	ArrayList<Image *> images = PhotoShop::getInstance().getImages();
	Iterateur<Image *> it(images);
	for (it.reset(); !it.end(); it++)
	{
		image = it;
		if (dynamic_cast<ImageNG *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "NG", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageRGB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "RGB", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "B", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
	}
}

void MainWindowPhotoShop::on_pushButtonOperande1_clicked()
{
	int indice = getIndiceImageSelectionnee();
	if (indice == -1)
	{
		dialogueErreur("Erreur", "Aucune image sélectionnée");
		return;
	}
	PhotoShop::getInstance().operande1 = PhotoShop::getInstance().getImageParIndice(indice);
	ImageNG *imageNG = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);
	if (imageNG != nullptr)
	{
		setImageNG("operande1", imageNG);
		return;
	}
	ImageRGB *imageRGB = dynamic_cast<ImageRGB *>(PhotoShop::getInstance().operande1);
	if (imageRGB != nullptr)
	{
		setImageRGB("operande1", imageRGB);
		return;
	}
	ImageB *imageB = dynamic_cast<ImageB *>(PhotoShop::getInstance().operande1);
	if (imageB != nullptr)
	{
		setImageB("operande1", imageB);
		return;
	}
}

void MainWindowPhotoShop::on_pushButtonSupprimeOperande1_clicked()
{
	PhotoShop::getInstance().operande1 = nullptr;
	setImageNG("operande1");
}

void MainWindowPhotoShop::on_pushButtonOperande2_clicked()
{
	int indice = getIndiceImageSelectionnee();
	if (indice == -1)
	{
		dialogueErreur("Erreur", "Aucune image sélectionnée");
		return;
	}
	PhotoShop::getInstance().operande2 = PhotoShop::getInstance().getImageParIndice(indice);
	ImageNG *imageNG = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande2);
	if (imageNG != nullptr)
	{
		setImageNG("operande2", imageNG);
		return;
	}
	ImageRGB *imageRGB = dynamic_cast<ImageRGB *>(PhotoShop::getInstance().operande2);
	if (imageRGB != nullptr)
	{
		setImageRGB("operande2", imageRGB);
		return;
	}
	ImageB *imageB = dynamic_cast<ImageB *>(PhotoShop::getInstance().operande2);
	if (imageB != nullptr)
	{
		setImageB("operande2", imageB);
		return;
	}
}

void MainWindowPhotoShop::on_pushButtonSupprimerOperande2_clicked()
{
	PhotoShop::getInstance().operande2 = nullptr;
	setImageNG("operande2");
}

void MainWindowPhotoShop::on_pushButtonResultat_clicked()
{
	if (PhotoShop::getInstance().resultat == nullptr)
	{
		dialogueErreur("Erreur", "Aucun résulta à ajouter");
		return;
	}
	PhotoShop::getInstance().ajouteImage(PhotoShop::getInstance().resultat);
	videTableImages();
	ArrayList<Image *> images = PhotoShop::getInstance().getImages();
	Iterateur<Image *> it(images);
	Image *image = nullptr;
	for (it.reset(); !it.end(); it++)
	{
		image = it;
		if (dynamic_cast<ImageNG *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "NG", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageRGB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "RGB", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
		else if (dynamic_cast<ImageB *>(image) != nullptr)
			ajouteTupleTableImages(image->getId(), "B", to_string(image->getDimension().getLargeur()).append("x").append(to_string(image->getDimension().getHauteur())), image->getNom());
	}
	PhotoShop::getInstance().resultat = nullptr;
	setImageNG("resultat");
}

void MainWindowPhotoShop::on_pushButtonSupprimerResultat_clicked()
{
	setResultatBoolean(-1);
	if (PhotoShop::getInstance().resultat != nullptr)
	{
	delete PhotoShop::getInstance().resultat;
	PhotoShop::getInstance().resultat = nullptr;
	setImageNG("resultat");
	}
}

void MainWindowPhotoShop::on_pushButtonTraitement_clicked()
{
	on_pushButtonSupprimerResultat_clicked();
	string traitement = getTraitementSelectionne();
	if (PhotoShop::getInstance().operande1 == nullptr)
	{
		dialogueErreur("Erreur", "Aucune image sélectionnée pour l'opérande 1");
		return;
	}
	bool secondOperandNeeded = false;
	if (traitement == "Différence" || traitement == "Comparaison (==)" || traitement == "Comparaison (<)" || traitement == "Comparaison (>)")
	{
		secondOperandNeeded = true;
	}
	if (secondOperandNeeded && PhotoShop::getInstance().operande2 == nullptr)
	{
		dialogueErreur("Erreur", "Aucune image sélectionnée pour l'opérande 2");
		return;
	}
	ImageNG *imageNG1 = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1);
	if (imageNG1 == nullptr)
	{
		dialogueErreur("Erreur", "L'image sélectionnée pour l'opérande 1 n'est pas de type ImageNG");
		return;
	}
	if (secondOperandNeeded)
	{
		ImageNG *imageNG2 = dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande2);
		if (imageNG2 == nullptr)
		{
			dialogueErreur("Erreur", "L'image sélectionnée pour l'opérande 2 n'est pas de type ImageNG");
			return;
		}
	}
	try
	{
		if (traitement == "Eclaircir (+ val)")
		{
			PhotoShop::getInstance().resultat = new ImageNG(*imageNG1 + dialogueDemandeInt("Valeur", "Entrez la valeur à ajouter"));
			setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
		}
		else if (traitement == "Eclaircir (++)")
		{
			PhotoShop::getInstance().resultat = new ImageNG(*imageNG1++);
			setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
		}
		else if (traitement == "Assombrir (- val)")
		{
			PhotoShop::getInstance().resultat = new ImageNG(*imageNG1 - dialogueDemandeInt("Valeur", "Entrez la valeur à soustraire"));
			setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
		}
		else if (traitement == "Assombrir (--)")
		{
			PhotoShop::getInstance().resultat = new ImageNG(*imageNG1--);
			setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
		}
		else if (traitement == "Différence")
		{
			PhotoShop::getInstance().resultat = new ImageNG(*imageNG1 - *dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande2));
			setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
		}
		else if (traitement == "Comparaison (==)")
		{
			setResultatBoolean(*imageNG1 == *dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande2));
		}
		else if (traitement == "Comparaison (<)")
		{
			setResultatBoolean(*imageNG1 < *dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande2));
		}
		else if (traitement == "Comparaison (>)")
		{
			setResultatBoolean(*imageNG1 > *dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande2));
		}
		else if (traitement == "Seuillage")
		{
			PhotoShop::getInstance().resultat = new ImageB(Traitements::Seuillage(*imageNG1, dialogueDemandeInt("Seuil", "Entrez le seuil")));
			setImageB("resultat", dynamic_cast<ImageB *>(PhotoShop::getInstance().resultat));
		}
		else if (traitement == "Filtre moyenneur")
		{
			PhotoShop::getInstance().resultat = new ImageNG(Traitements::FiltreMoyenneur(*imageNG1, dialogueDemandeInt("Taille du filtre", "Entrez la taille du filtre")));
			setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
		}
		else if (traitement == "Filtre médian")
		{
			PhotoShop::getInstance().resultat = new ImageNG(Traitements::FiltreMedian(*imageNG1, dialogueDemandeInt("Taille du filtre", "Entrez la taille du filtre")));
			setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
		}
		else if (traitement == "Erosion")
		{
			PhotoShop::getInstance().resultat = new ImageNG(Traitements::Erosion(*dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1), dialogueDemandeInt("Taille du filtre", "Entrez la taille du filtre")));
			setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
		}
		else if (traitement == "Dilatation")
		{
			PhotoShop::getInstance().resultat = new ImageNG(Traitements::Dilatation(*dynamic_cast<ImageNG *>(PhotoShop::getInstance().operande1), dialogueDemandeInt("Taille du filtre", "Entrez la taille du filtre")));
			setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
		}
		else if (traitement == "Négatif")
		{
			PhotoShop::getInstance().resultat = new ImageNG(Traitements::Negatif(*imageNG1));
			setImageNG("resultat", dynamic_cast<ImageNG *>(PhotoShop::getInstance().resultat));
		}
	}
	CATCH_AFFICHE;
}
