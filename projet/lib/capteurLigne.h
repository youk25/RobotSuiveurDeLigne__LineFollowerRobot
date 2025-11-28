/* 
* Section: 01
* Équipe:  1013
* Auteurs: Yolaine Ntabugi Karemere
*          Yousra Khettal
*          Oriane Claudelle
*          Émy Xiao
*
* Date de remise: 16 avril 2025
*
* But: Cette classe permet de lire les valeurs du capteurs de ligne et de suivre
*      la ligne en utilisant un PID. Nous implémentons plusieurs méthodes de 
*      suiveur de ligne selon les différents obstacles du parcours.
*      
* Matériel: Suiveur de ligne Maker Line
*           Les Ports C3, C4, C5, C6, C7 de la carte mère sont en entrées
*/ 

#pragma once

#define F_CPU 8000000UL

#include <avr/io.h> 
#include <util/delay.h>
#include "roues.h"
#include "capteurinfrarouge.h"
#include "del.h"
#include "debug.h"
#include "can.h"

#define CAPTEUR1 PC3
#define CAPTEUR2 PC4
#define CAPTEUR3 PC5
#define CAPTEUR4 PC6
#define CAPTEUR5 PC7
  
#define ERREUR_CENTRE_GAUCHE -3
#define ERREUR_DROITE_PEU 2
#define ERREUR_DROITE_MOYEN 3
#define ERREUR_DROITE_BEAUCOUP 10
#define ERREUR_GAUCHE_PEU -2
#define ERREUR_GAUCHE_MOYEN -4
#define ERREUR_GAUCHE_BEAUCOUP -5

enum Ligne 
{
    CENTRE             = 0b00100,
    CENTRE_LARGE       = 0b01110,
    CENTRE_DROITE      = 0b00110,
    CENTRE_GAUCHE      = 0b01100,
    DROITE_BEAUCOUP    = 0b00001,
    DROITE_PEU         = 0b00010,
    DROITE_MOYEN       = 0b00011,
    DROITE_90          = 0b00111,
    DROITE_90_BEAUCOUP = 0b01111,
    GAUCHE_BEAUCOUP    = 0b10000,
    GAUCHE_PEU         = 0b01000,
    GAUCHE_MOYEN       = 0b11000,
    GAUCHE_90          = 0b11100,
    GAUCHE_90_BEAUCOUP = 0b11110,
    PLEIN              = 0b11111,
    VIDE               = 0b00000
}; 

class CapteurLigne
{
public:
    CapteurLigne();
    ~CapteurLigne() = default;

    Ligne presenceLigne();
    uint16_t lireCapteur(uint16_t capteur);
    bool peutAvancer();

    void suivreLignePIDGrille(CapteurLigne& capteur, Roues& roues);
    void suivreLignePIDFourchette(CapteurLigne& capteur, Roues& roues);
    void suivreLignePID(CapteurLigne& capteur, Roues& roues);
    CapteurInfrarouge capteurRouge;
};
