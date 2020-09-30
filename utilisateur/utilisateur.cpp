#include "utilisateur.h"
#include "../fonctions/fonctions.h"
#include <QPrinter>
#include <qtextdocument.h>

Utilisateur::Utilisateur()
{
	profilChoisi = new ProfilPrive;
}


Utilisateur::~Utilisateur(){
	delete profilChoisi;
}


void Utilisateur::selectCurrentProfil(QString pseudo){

	QFile file;
	file.setFileName(PROFILPATH+pseudo+"/"+pseudo+EXTPUBLIC);

	// charger les données publiques du profil avec le nom pseudo
	QDomDocument xmlBOM;
	file.open(QFile::ReadOnly | QFile::Text);

	xmlBOM.setContent(&file);
	QDomElement element = xmlBOM.documentElement().firstChild().toElement();
	QDomElement sousElement;

	while(!element.isNull())
	{
		if(element.tagName()=="admin"){
			if(element.text() == "true")
				profilChoisi->setInAdmin(true);
			else
				profilChoisi->setInAdmin(false);
		}else if(element.tagName()=="nom"){
			if(element.attribute("prive", "no") == "0"){
				profilChoisi->setNom(element.text());
				profilChoisi->setPriveNom(false);
			}else{
				profilChoisi->setNom(decrypter(element.text()));
				profilChoisi->setPriveNom(true);
			}
		}else if(element.tagName()=="prenom"){
			if(element.attribute("prive", "no") == "0")
				profilChoisi->setPrenom(element.text());
			else
				profilChoisi->setPrenom(decrypter(element.text()));
		}else if(element.tagName()=="sexe"){
			if(element.attribute("prive", "no") == "0"){
				profilChoisi->setSexe(element.text());
				profilChoisi->setPriveSexe(false);
			}else{
				profilChoisi->setSexe(decrypter(element.text()));
				profilChoisi->setPriveSexe(true);
			}
		}else if(element.tagName()=="taille"){
			if(element.attribute("prive", "no") == "0"){
				profilChoisi->setTaille(element.text().toInt());
				profilChoisi->setPriveCorps(false);
			}else{
				profilChoisi->setTaille(decrypter(element.text()).toInt());
				profilChoisi->setPriveCorps(true);
			}
		}else if(element.tagName()=="poids"){
			if(element.attribute("prive", "no") == "0")
				profilChoisi->setPoids(element.text().toDouble());
			else
				profilChoisi->setPoids(decrypter(element.text()).toDouble());
		}else if(element.tagName()=="groupe"){
			if(element.attribute("prive", "no") == "0"){
				profilChoisi->setGroupSanguin(element.text());
				profilChoisi->setPriveGroupSanguin(false);
			}else{
				profilChoisi->setGroupSanguin(decrypter(element.text()));
				profilChoisi->setPriveGroupSanguin(true);
			}
		}else if(element.tagName()=="date"){
			if(element.attribute("prive", "no") == "0"){
				profilChoisi->setDateNaissance(element.text());
				profilChoisi->setPriveDateNaissance(false);
			}else{
				profilChoisi->setDateNaissance(decrypter(element.text()));
				profilChoisi->setPriveDateNaissance(true);
			}
		}else if(element.tagName()=="tel"){
			if(element.attribute("prive", "no") == "0"){
				profilChoisi->setTel(element.text());
				profilChoisi->setPriveTel(false);
			}else{
				profilChoisi->setTel(decrypter(element.text()));
				profilChoisi->setPriveTel(true);
			}
		}else if(element.tagName()=="adress"){
			if(element.attribute("prive", "no") == "0"){
				profilChoisi->setAdresse(element.text());
				profilChoisi->setPriveAdress(false);
			}else{
				profilChoisi->setAdresse(decrypter(element.text()));
				profilChoisi->setPriveAdress(true);
			}
		}else if (element.tagName()=="profession"){
			if(element.attribute("prive", "no") == "0"){
				profilChoisi->setProfession(element.text());
				profilChoisi->setPriveProfession(false);
			}else{
				profilChoisi->setProfession(decrypter(element.text()));
				profilChoisi->setPriveProfession(true);
			}
		}else if(element.tagName()=="medecin"){
			sousElement = element.firstChild().toElement();
			while(!sousElement.isNull())
			{
				if(sousElement.tagName()=="nom"){
					if(element.attribute("prive", "no") == "0"){
						profilChoisi->setMedecinNom(sousElement.text());
						profilChoisi->setPriveMed(false);
					}else{
						profilChoisi->setMedecinNom(decrypter(sousElement.text()));
						profilChoisi->setPriveMed(true);
					}
				}else if(sousElement.tagName()=="tel"){
					if(element.attribute("prive", "no") == "0")
						profilChoisi->setMedecinTel(sousElement.text());
					else
						profilChoisi->setMedecinTel(decrypter(sousElement.text()));
				}
				sousElement = sousElement.nextSibling().toElement();
			}
		}
		else if (element.tagName()=="contact"){
			sousElement = element.firstChild().toElement();
			while(!sousElement.isNull())
			{
				if(sousElement.tagName()=="nom")
					profilChoisi->setPersonContactNom(sousElement.text());
				else if(sousElement.tagName()=="tel")
					profilChoisi->setPersonContactTel(sousElement.text());
				sousElement = sousElement.nextSibling().toElement();
			}
		}

		element = element.nextSibling().toElement();
	}

	file.close();

	// charger les données privées
	profilChoisi->clearAllList();
	bool allerg = false, antPerso = false, antFam = false, prescri = false, vac = false;
	QString ligne;
	QFile filePriv;
	filePriv.setFileName(PROFILPATH+pseudo+"/"+pseudo+EXTPRIVATE);
	if (filePriv.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream out(&filePriv);
		while(!out.atEnd()){
			out >> ligne;
			if(decrypter(ligne) == "Allergies"){
				allerg = true;
				continue;
			}else if(decrypter(ligne) == "fin_allergies"){
				allerg = false;
				continue;
			}

			if(decrypter(ligne) == "Ante_Perso"){
				antPerso = true;
				continue;
			}else if(decrypter(ligne) == "fin_Ante_Perso"){
				antPerso = false;
				continue;
			}

			if(decrypter(ligne) == "Ant_Famille"){
				antFam = true;
				continue;
			}
			else if(decrypter(ligne) == "fin_Ant_Famille"){
				antFam = false;
				continue;
			}

			if(decrypter(ligne) == "Prescriptions"){
				prescri = true;
				continue;
			}
			else if(decrypter(ligne) == "fin_Prescriptions"){
				prescri = false;
				continue;
			}

			if(decrypter(ligne) == "Vaccins"){
				vac = true;
				continue;
			}
			else if(decrypter(ligne) == "fin_Vaccins"){
				vac = false;
				continue;
			}

			if(allerg){
				profilChoisi->ajouterAllergie(decrypter(ligne));
			}
			if(antPerso){
				profilChoisi->ajouterAntecedentPerso(decrypter(ligne));
			}
			if(antFam){
				profilChoisi->ajouterAntecedentFamil(decrypter(ligne));
			}
			if(prescri){
				profilChoisi->ajouterPrescription(decrypter(ligne));
			}
			if(vac){
				profilChoisi->ajouterVaccin(decrypter(ligne));
			}

		}

		filePriv.close();
	}
}


ProfilPrive* Utilisateur::getProfil(){
	return profilChoisi;
}


void Utilisateur::genererPdf(QString path){
	QTextDocument document;

	QPrinter printer(QPrinter::PrinterResolution);
	printer.setOutputFormat(QPrinter::PdfFormat);
	printer.setPaperSize(QPrinter::A4);
	printer.setOutputFileName(path+"\\"+tr("données.pdf"));
	printer.setPageMargins(QMarginsF(15, 15, 15, 15));

	QString entete = "<header><h1>Dossier Médical</h1>"
					 "</header>";

	QString barreLaterale = "<nav><ul><li>Nom:"+profilChoisi->getNom()+"</li><li>Prenom:"+profilChoisi->getPrenom()+"</li>"
							"<li>Sexe:"+profilChoisi->getSexe()+"</li>"
							"</ul></nav>";

	QString section1 = "<section><h3>Données principales</h3>"
					   "</section>";

	QString section2 = "<section><h3>Données avancées</h3>"
					   "</section>";

	QString piedDePage = "<footer>Date : "+QDateTime::currentDateTime().toString("hh:mm dd/MM/yyyy")+"</footer>";

	/*QString html = "<br><table width=100%>"
			"<tr><td align=center> </td><td align=center><strong><u>Calibration black time</u></strong></td><td align=center><strong><u>Calibration gain time</u></strong></td><td align=center><strong><u>Scanning time</u></strong></td> <td align=center><strong><u> Total </u></strong></td></tr>"
			"<tbody>"
			"<tr><td align=center><strong> Duration </strong></td><td align=center>xxx </td><td align=center>xxx  </td><td align=center> xx </td> <td align=center>xxx </td></tr>"
			"</tbody></table><hr width=100%></hr>";*/

	document.setHtml(entete+barreLaterale+section1+section2+piedDePage);
	document.print(&printer);
}
