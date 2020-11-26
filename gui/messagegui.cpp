#include "messagegui.h"
#include "ui_messagegui.h"
#include "../fonctions/fonctions.h"
#include <QFile>
#include "../utilisateur/utilisateur.h"
#include "chemin.h"
#include<QMessageBox>


 Utilisateur *U= new Utilisateur; //creation dun pobjet utilisateur
MessageGui::MessageGui(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MessageGui)
{
	ui->setupUi(this);
}

MessageGui::~MessageGui()
{
	delete ui;
    delete fm;
}


void MessageGui::settingReadingInterface()
{
    ui->B_save_message->setEnabled(false);

    ui->B_write_message->setEnabled(true);



    ui->nomMedValue->setVisible(false);
    ui->nomMedLab->setVisible(false);

    ui->adressMedValue->setVisible(false);
    ui->adresseMedLabe->setVisible(false);


    ui->dateLab->setVisible(false);
    ui->dateValue->setVisible(false);

    //QString messegeOnFile = U->readMessage();
    ui->messageValue->clear();

}

void MessageGui::show_reading_interface()
{

    settingReadingInterface();


    QFile file( PROFILPATH+lireDansFichierTemp()+"/"+lireDansFichierTemp()+"_message.txt");
   if(!file.open(QFile::ReadOnly | QFile::Text))
   {

   }
    ui->messageValue->setText(file.readAll()); // on lit l'ensemble du file
     ui->messageValue->setReadOnly(true);
     // permet l'interaction avec la sourir et le clavier
      ui->messageValue->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);

   // ui->messageValue->setText(ui->messageValue->toPlainText(messegeOnFile)+"\n");

        this->show();

}

 void MessageGui::show_writting_interface()
 {
     ui->B_save_message->setEnabled(true);

     ui->nomMedValue->setVisible(true);
     ui->nomMedLab->setVisible(true);

     ui->adressMedValue->setVisible(true);
     ui->adresseMedLabe->setVisible(true);


     ui->dateLab->setVisible(true);
     ui->dateValue->setVisible(true);
     // date du jour par defaut
     ui->dateValue->setDate(QDate::currentDate());
     // plage de date sur plus ou moins une année
     ui->dateValue->setDateRange( QDate::currentDate().addDays( -365 ),
                                  QDate::currentDate().addDays(  365 ));

     ui->messageValue->clear(); // le contenue de linterfce
      ui->nomMedValue->clear(); // on vide le nom medecin
      ui->adressMedValue->clear(); // on vide l'adresse
      ui->messageValue->setReadOnly(false);
      this->show();


 }



void MessageGui::on_B_write_message_clicked()
{
    show_writting_interface();

}

void MessageGui::on_B_retour_menu_principal_clicked()
{
    this->close();

}



void MessageGui::on_B_save_message_clicked()
{
    /* on recupère les entrées du medecin et on
     * fait appel à la fonction de sauvegarde */
    U->setNomSoignant(ui->nomMedValue->text());

    U->setdateSoin(ui->dateValue->text());
    U->setAdressesSoignant(ui->adressMedValue->text());
    U->setmessageSoignant(ui->messageValue->toPlainText());
    // toPlainText: Returns the content of the QTextEdit text field as plain text.

    // ne pas permettre le champs nom medecin adresse et text vide
    if(!ui->nomMedValue->text().isEmpty() && !ui->adressMedValue->text().isEmpty() &&
            !ui->messageValue->toPlainText().isEmpty()) {

    //appel de la fonction save
             U->saveMessage("NOM SOIGNANT: " + U->getNomSoignant(),
                           "ADRESSE DU CABINET: "+U->getAdressesSoignant(),
                           "DATE DE VISITE: "+U->getdateSoin(),
                           "MESSAGE: "+U->getmessageSoignant());
             show_reading_interface();
    }
    else{
        QMessageBox::warning(this, "Remplir tous les formulaires",
                             "Merci de renseigner votre NOM, ADRESSE et MESSAGE d'abord");
    }


}
