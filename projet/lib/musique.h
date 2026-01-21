/* 
* Section: 01
* Équipe:  1013
* Auteurs: Yolaine Ntabugi Karemere
*          Yousra Khettal
*          Oriane Claudelle
*          Émy Xiao
*
* Date de remise: 25 mars 2025
*
* But: Définition de la classe 'Musique'.
*      Utilise Timer2 en mode CTC pour jouer une note donnée à une certaine fréquence.
*      
* Matériel: Brancher le fil du piezo aux ports PD6 et PD6 qui sont en sortie.
*
*/  
#pragma once

#include <avr/io.h>
#include <math.h>

#define F_CPU 8000000UL
#define NOTE_REFERENCE 45
#define NOTE_MAXIMALE  81
#define PRESCALER_1024 1024
#define PERIODE_2_FOIS 2

class Musique 
{
public:
    Musique();
    ~Musique();

    float trouverDistance(double frequence);
    void jouerNoteAFrequence(uint8_t note);
    void arreter();
};

