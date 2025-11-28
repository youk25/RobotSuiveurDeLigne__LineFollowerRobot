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

#include "capteurinfrarouge.h"
#include "debug.h"

CapteurInfrarouge::CapteurInfrarouge()
{
    DDRA &= ~(1 << PA6) ; 
}
    
uint16_t CapteurInfrarouge::lireValeurAnalogique()
{
    uint16_t distance = convertisseur_.lecture(PA6);
    return distance;
}

bool CapteurInfrarouge::presencePoteau()
{
    return ((lireValeurAnalogique() >= DISTANCE_OBJET_MIN) && (lireValeurAnalogique() <= DISTANCE_OBJET_MAX));
}

bool CapteurInfrarouge::presencePoteauGrille()
{
    return ((lireValeurAnalogique() >= DISTANCE_OBJET_MIN_GRILLE) && (lireValeurAnalogique() <= DISTANCE_OBJET_MAX));
}
