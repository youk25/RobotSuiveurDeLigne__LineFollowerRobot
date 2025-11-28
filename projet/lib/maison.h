
/* 
* Section: 01
* Équipe:  1013
* Auteurs: Yolaine Ntabugi Karemere
*          Yousra Khettal
*          Oriane Claudelle
*          Émy Xiao
*
* Date de remise:  16 avril 2025
*
* But: cette classe permet de chercher la maison dans le parcours du robot tout en évitant les poteaux.
* Matériel: suiveur de ligne Maker Line, capteur de distance GP2Y0A21YK0F
*/     

#pragma once

#include <avr/io.h> 
#include <util/delay.h>
#include "capteurinfrarouge.h"
#include "capteurLigne.h"


#define DELAI_ATTENDRE_400_MS  400
#define DELAI_ATTENDRE_500_MS  500
#define DELAI_ATTENDRE_1000_MS 1000
#define DELAI_CLIGNOTEMENT_MS  2000 
#define DELAI_LECTURE_MS       10
#define ETAT_DEL_ROUGE         1
#define ETAT_DEL_VERT          2
#define MAX_INTERSECTIONS      2
#define PWM_AVANCER            150
#define PWM_TOURNER            105
#define PWM_TOURNER_90         165
#define PWM_BASCULER           255
#define PWM_AVANCER_200        200


class Maison
{
public :
    Maison()=default;
    ~Maison() = default;
    
    void traverserMaison(Maison& maison, CapteurLigne& capteur, Roues& robot, Del& del);
    CapteurInfrarouge capteurRouge;
    CapteurLigne capteurLigne;
};