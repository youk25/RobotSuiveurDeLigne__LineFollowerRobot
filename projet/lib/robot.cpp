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
* But:  Cette classe permet de gérer les actions du robot, 
*       y compris la gestion des boutons, l'enregistrement des directions, la bifurcation, le balayage 
*       de la fourchette et le contrôle des roues.
*      
* Matériel: Capteur de ligne
*           Capteur infrarouge
*/ 

#include "robot.h"

Robot::Robot()
{
    DDRD &= ~(1 << PD2) & ~(1 << PD3);
}

bool Robot::trouverBoutonAppuye(uint8_t bouton)
{
    if (bouton == BOUTON_INT) 
    { 
        uint8_t scan1 = PIND & (1 << PD2); 
        _delay_ms(DELAI_DEBOUNCE_BOUTON_MS); 
        uint8_t scan2 = PIND & (1 << PD2);
        return scan1 && scan2;
    }

    else if (bouton == BOUTON_BLANC) 
    { 
        uint8_t scan1 = !(PIND & (1 << PD3)); 
        _delay_ms(DELAI_DEBOUNCE_BOUTON_MS); 
        uint8_t scan2 = !(PIND & (1 << PD3));
        return scan1 && scan2;
    }
    return false;
}

void Robot::enregistrerDirections()
{
    int nAppuisBouton = 0;

    while (nAppuisBouton < N_APPUIS_BOUTONS_MAX)
    {
        if (gererBouton(BOUTON_INT, 'd', nAppuisBouton)) 
        {
            nAppuisBouton++;
        }

        if (gererBouton(BOUTON_BLANC, 'g', nAppuisBouton)) 
        {
            nAppuisBouton++;
        }
    }

    del.eteindre();
}

bool Robot::gererBouton(uint8_t bouton, char direction, int nAppuisBouton)
{
    if (trouverBoutonAppuye(bouton)) 
    {
        if (nAppuisBouton == 0) 
        {
            choixPointB = direction;
        } 
        else if (nAppuisBouton == 1) 
        {
            choixPointC = direction;
        }

        while (trouverBoutonAppuye(bouton))
        {
            allumerDel(bouton);
        }

        del.eteindre();
        return true;
    }

    return false;
}

void Robot::allumerDel(uint8_t bouton)
{
    if (bouton == BOUTON_INT) 
    {
        del.allumerVerte();
    }
    else if (bouton == BOUTON_BLANC) 
    {
        del.allumerRouge();
    }
}
void Robot::bifurquer(char position)
{
    roues.arreter();
    jouerSonGrave();

    if (position == 'g') 
    {
        balayageFourchette('g');
    } 
    else if (position == 'd') 
    {
        balayageFourchette('d');
    }
}

void Robot::balayageFourchette(char direction)
{

    if (direction == 'g') 
    {
        roues.avancer(VITESSE_DEUX_CENT, VITESSE_DEUX_CENT);
        _delay_ms(DELAI_SEPT_CENT);
        tournerGauche(VITESSE_CENT_QUARANTE);
    } 
    else if (direction == 'd') 
    {
        roues.avancer(VITESSE_DEUX_CENT, VITESSE_DEUX_CENT);
        _delay_ms(DELAI_SEPT_CENT);
        tournerDroite(VITESSE_CENT_QUARANTE);
    }
}

void Robot::jouerSonGrave()
{
    musique.jouerNoteAFrequence(NOTE_GRAVE);
    _delay_ms(DELAI_MUSIQUE);
    musique.arreter();
}

void Robot::tournerDroite(uint8_t vitesse) 
{   
    roues.avancer(VITESSE_DEUX_CENT,VITESSE_DEUX_CENT);
    _delay_ms(VITESSE_QUATRE_CENT);
    roues.avancer(0, vitesse);
    _delay_ms(VITESSE_QUATRE_CENT);

    while (!(capteurLigne.peutAvancer()))
    {
        roues.avancer(0, vitesse);
        _delay_ms(DELAI_TOURNER);
    }

    roues.arreter();
    _delay_ms(DELAI_CINQ_CENT);
   return;
}

void Robot::tournerGauche(uint8_t vitesse) 
{   
    roues.avancer(VITESSE_DEUX_CENT, VITESSE_DEUX_CENT);  // gauche
    _delay_ms(DELAI_QUATRE_CENT);
    roues.avancer(vitesse, 0);
    _delay_ms(DELAI_CINQ_CENT_CINQUANTE);

    while (!(capteurLigne.peutAvancer()))
    {
        roues.avancer(vitesse, 0);
        _delay_ms(DELAI_TOURNER);
    }

    roues.arreter();
    _delay_ms(DELAI_CINQ_CENT);

    return;
}
