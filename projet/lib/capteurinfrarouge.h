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
* But: Cette classe permet de lire la valeur analogique du capteur infrarouge et de determiner la presence d'un poteau.
*      
* Matériel: Capteur de distance GP2Y0A21YK0F
*           Convertisseur analogique numerique (CAN) 
*           Le Port A6 de la carte mère est en entrée.
*/     

#pragma once


#include <avr/io.h> 
#include <util/delay.h>
#include "can.h"
#include "roues.h"

#define BITSHIFT_PRECISION 2
#define DISTANCE_OBJET_MIN 80
#define DISTANCE_OBJET_MAX 160
#define DISTANCE_OBJET_MIN_GRILLE 40

class CapteurInfrarouge
{
public:
    CapteurInfrarouge();
    ~CapteurInfrarouge() = default;
    
    uint16_t lireValeurAnalogique();
    bool presencePoteau();
    bool presencePoteauGrille();

private:
    can convertisseur_;
};
