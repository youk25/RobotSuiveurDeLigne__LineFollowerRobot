/* 
* Section: 01
* Équipe:  1013
* Auteurs: Yolaine Ntabugi Karemere
*          Yousra Khettal
*          Oriane Claudelle
*          Émy Xiao
*
* Date de remise: 17 avril 2025
*
* But: Implémentation de la classe 'Musique'.
*      Utilise Timer2 en mode CTC pour jouer une note donnée à une certaine fréquence.
*      
* Matériel: Brancher le fil du piezo aux ports PD6 et PD6 qui sont en sortie.
*
*/  

#include "musique.h"

Musique::Musique()
{
    DDRD  |= (1 << PD6) | (1 << PD7);
    TCNT2 = 0;
    TCCR2A |= (1 << COM2A0) | (1 << WGM21);
}

Musique::~Musique(){}

float Musique::trouverDistance(double frequence) 
{
    return (F_CPU / (frequence * PERIODE_2_FOIS * PRESCALER_1024)) - 1;
}

void Musique::jouerNoteAFrequence(uint8_t frequence) 
{
    TCCR2B |= (1 << CS22) | (1 << CS20);

    OCR2A = trouverDistance(frequence);
}

void Musique::arreter() 
{
    TCCR2B &= ~((1 << CS22) | (1 << CS20));
}
