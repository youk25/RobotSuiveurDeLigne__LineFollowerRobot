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
* But: Définition de la classe 'Del'.
*      La classe 'Del' permet de contrôler la Del libre sur l'ATmega324. 
*      Elle peut être soit éteinte ou allumée de couleur verte, rouge et ambre.
*      
* Matériel: Les broches PA0 et PA1 du port A doivent être en mode sortie
*           et reliés par un fil aux broches de la Del.
*/     

#pragma once

#define F_CPU 8000000UL
#define DELAI_CLIGNOTER_4HZ       125
#define DELAI_CLIGNOTER_2HZ       250
#define AJOUT_DEUX_CENT_CINQUANTE 250
#define AJOUT_CINQ_CENT           500

#include <avr/io.h> 
#include <util/delay.h>

const uint8_t DELAI_AMBRE_VERT  = 11;
const uint8_t DELAI_AMBRE_ROUGE = 2;

class Del 
{
public :
    Del();
    ~Del() = default;
    
    void eteindre();
    void allumerVerte();
    void allumerRouge();
    void clignoter4Hz(uint8_t couleur, uint16_t dureeMs);
    void alternerRougeVert2Hz(uint16_t dureeMs);
};
