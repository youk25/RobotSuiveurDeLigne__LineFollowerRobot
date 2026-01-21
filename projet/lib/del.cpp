/* 
* Section: 01
* Équipe:  1013
* Auteurs: Yolaine Ntabugi Karemere
*          Yousra Khettal
*          Oriane Claudelle
*          Émy Xiao
*
* Date de remise: 16 Avril 2025
*
* But: Implémentation de la classe 'Del'.
*      La classe 'Led' permet de contrôler la Del libre sur l'ATmega324AP. 
*      Elle peut être soit éteinte ou allumée de couleur verte, rouge et ambre.
*      
* Matériel: Les broches PA0 et PA1 du port A doivent être en mode sortie
*           et reliés par un fil aux broches de la Del.
*/                                                      

#include "del.h"

Del::Del(){
    DDRA |= (1 << PA0) | (1 << PA1); 
}

void Del::eteindre() 
{
    PORTA &= ~((1 << PA0) | (1 << PA1)); 
}

void Del::allumerVerte() 
{
    PORTA |=  (1 << PA1);
    PORTA &= ~(1 << PA0);
}

void Del::allumerRouge() 
{
    PORTA |=  (1 << PA0);
    PORTA &= ~(1 << PA1);
}

void Del::clignoter4Hz(uint8_t couleur, uint16_t dureeMs)
{
    uint16_t tempsEcoule = 0;
    while (tempsEcoule < dureeMs) 
    {
        if (couleur == 0) 
        { 
            allumerVerte();
        } 
        else if (couleur == 1) 
        { 
            allumerRouge();
        }
        _delay_ms(DELAI_CLIGNOTER_4HZ);
        eteindre();
        _delay_ms(DELAI_CLIGNOTER_4HZ);
        tempsEcoule += AJOUT_DEUX_CENT_CINQUANTE;
    }
}

void Del::alternerRougeVert2Hz(uint16_t dureeMs)
{
    uint16_t tempsEcoule = 0;
    while (tempsEcoule < dureeMs) 
    {
        allumerRouge();
        _delay_ms(DELAI_CLIGNOTER_2HZ);
        allumerVerte();
        _delay_ms(DELAI_CLIGNOTER_2HZ);
        tempsEcoule += AJOUT_CINQ_CENT;
    }
    eteindre();
}
