/*
* Équipe:  1013
* Auteurs: Yolaine Ntabugi Karemere
*          Yousra Khettal
*          Oriane Claudelle
*          Émy Xiao
*
* Date: 16 Mars 2025
* 
* Description: Implémentation de la classe Roues.
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

#include "roues.h"

Roues::Roues() 
{
    DDRB |= (1 << PB3) | (1 << PB4) | (1 << PB2) | (1 << PB5);
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
    TCCR0B = (1 << CS00);
}

void Roues::ajusterPwmTimer0(uint16_t pwmGauche, uint16_t pwmDroit) 
{

    OCR0A = pwmGauche; 
    OCR0B = pwmDroit; 
}

void Roues::avancer(uint8_t vitesseRoueGauche, uint8_t vitesseRoueDroite)
{
    PORTB &= ~(1 << PB2); 
    PORTB &= ~(1 << PB5); 
    PORTB |= (1 << PB3) | (1 << PB4); 
    ajusterPwmTimer0(vitesseRoueGauche, vitesseRoueDroite);
}

void Roues::reculer(uint8_t vitesse) 
{
    PORTB &= ~(1 << PB3); 
    PORTB &= ~(1 << PB4); 
    PORTB |= (1 << PB5) | (1 << PB2); 
    ajusterPwmTimer0(vitesse, vitesse - AJUSTEMENT_ROUE);
}

void Roues::arreter() 
{
    ajusterPwmTimer0(0, 0);
}

