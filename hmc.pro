#-------------------------------------------------
#
# Project created by QtCreator 2020-08-31T13:54:08
#
#-------------------------------------------------

QT += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hmc
TEMPLATE = app
# destination de l'executable de l'application
DESTDIR    = bin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

# copie la doc
CONFIG *= file_copies
COPIES += myDocumentation
myDocumentation.files = $$files(doc/*)
myDocumentation.path = $$OUT_PWD/bin/doc

SOURCES += \
        main.cpp \
    profil/profil.cpp \
    profil/profilprive.cpp \
    utilisateur/utilisateurbase.cpp \
    utilisateur/utilisateurmedecin.cpp \
    utilisateur/utilisateur.cpp \
    gui/infoprofilgui.cpp \
    gui/afficheprofilgui.cpp \
    gui/messagegui.cpp \
    gui/logingui.cpp \
    gui/appligui.cpp \
    fonctions/fonctions.cpp

HEADERS += profil/profil.h \
    profil/profilprive.h \
    utilisateur/utilisateurbase.h \
    utilisateur/utilisateurmedecin.h \
    utilisateur/utilisateur.h \
    gui/infoprofilgui.h \
    gui/afficheprofilgui.h \
    gui/messagegui.h \
    gui/logingui.h \
    chemin.h \
    gui/appligui.h \
    fonctions/fonctions.h

FORMS += gui/infoprofilgui.ui \
    gui/afficheprofilgui.ui \
    gui/messagegui.ui \
    gui/logingui.ui \
    gui/appligui.ui

# fichier de traduction qui sera generé
TRANSLATIONS += hmc_en.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
