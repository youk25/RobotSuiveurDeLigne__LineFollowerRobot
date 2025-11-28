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
* But:  Cette classe permet de gérer les actions du robot, 
*       y compris la gestion des boutons, l'enregistrement des directions, la bifurcation, le balayage 
*       de la fourchette et le contrôle des roues.
*      
* Matériel: Capteur de ligne
*           Capteur infrarouge
*/ 

#pragma once

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "del.h"
#include "uart.h"
#include "capteurLigne.h"
#include "roues.h"
#include "musique.h"
#include "debug.h"

#define DELAI_DEBOUNCE_MS         2
#define BOUTON_INT                0
#define BOUTON_BLANC              1
#define N_CHOIX_BOUTON            2
#define DELAI_DEBOUNCE_BOUTON_MS  50
#define N_APPUIS_BOUTONS_MAX      2
#define VITESSE_DEUX_CENT         200
#define VITESSE_CENT_QUARANTE     140
#define VITESSE_QUATRE_CENT       400

#define DELAI_QUATRE_CENT         400
#define DELAI_CINQ_CENT           500
#define DELAI_CINQ_CENT_CINQUANTE 550
#define DELAI_SEPT_CENT           700
#define DELAI_TOURNER             5
#define NOTE_GRAVE                35
#define DELAI_MUSIQUE             4000

class Robot
{
public:
    Robot();
    ~Robot() = default;

    void tournerDroite(uint8_t vitesse);
    void tournerGauche(uint8_t vitesse);

    void enregistrerDirections();
    bool gererBouton(uint8_t bouton, char direction, int nAppuisBouton);
    void allumerDel(uint8_t bouton); 

    void bifurquer(char position);
    void balayageFourchette(char direction);
    void jouerSonGrave();

    bool trouverBoutonAppuye(uint8_t bouton); // 0 pour INT, 1 pour bouton blanc

    char choixPointB = ' '; 
    char choixPointC = ' ';
    char positionDepart = ' ';

    Del del;
    Uart uart;
    CapteurLigne capteurLigne;
    CapteurInfrarouge capteurInfrarouge;
    Roues roues;
    Musique musique;
};
