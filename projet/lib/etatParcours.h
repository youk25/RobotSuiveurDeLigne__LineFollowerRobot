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
* But: Cette classe permet de definir les états du robot dans le parcours. 
*      Elle est utilisé dans la machine à état principale du main.cpp.
*/    

#pragma once

enum class EtatParcours
{
    INIT,
    FOURCHETTE,
    MAISON,
    GRILLE,
    PARKING
};

