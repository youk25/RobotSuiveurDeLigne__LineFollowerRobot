/*
* Équipe:  1013
* Auteurs: Yolaine Ntabugi Karemere
*          Yousra Khettal
*          Oriane Claudelle
*          Émy Xiao
* Date: 16 Mars 2025
*
* Description: Définition de la classe Roues.
*              Cette classe permet de controler les roues du robot.
*              Le constructeur configure les broches de direction en sortie
*              et la méthode arreter() permet d'arrêter les roues.
*
*              Les méthodes implémentées permettent de d'ajuster le PWM
*              des roues, de les faire avancer et reculer ainsi que de 
*              permettre au robot de tourner à gauche et à droite.
*
* Matériel: Les broches PB2, PB3, PB4 et PD5 du portB sont en sortie 
*           et reliées aux broches des roues pour contrôler les roues.
*           Les signaux PWM sont envoyes sur ces broches pour controler la vitesse des roues.
*/

#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DELAI_1000_MS   1000
#define MOITIE          2
#define AJUSTEMENT_ROUE 3

class Roues 
{
public:
    Roues();
    ~Roues() = default;
    
    void avancer(uint8_t vitesseRoueGauche, uint8_t vitesseRoueDroite);
    void reculer(uint8_t vitesse);
    void arreter();
    void ajusterPwmTimer0(uint16_t vitesseA, uint16_t vitesseB);
};

