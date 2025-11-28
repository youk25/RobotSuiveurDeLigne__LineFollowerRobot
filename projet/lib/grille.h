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
* But: Cette classe permet de definir la méthode implémentant l'algorithme de l'obstacle Grille.
*      Elle réalise le parcours duu point J au point A. 
* Matériel:
*    
*/ 
#pragma once

#include "capteurLigne.h"
#include "robot.h"

class Grille
{
public:
    Grille() = default;
    ~Grille() = default;

    void traverserGrille(CapteurLigne& capteurLigne, CapteurInfrarouge& capteurRouge, Robot& robot, bool deuxiemePassage);
    void tournerDroiteCoin(Robot& robot);
    void tournerGaucheCoin(Robot& robot);

};