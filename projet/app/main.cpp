#define F_CPU 8000000UL

#include <avr/io.h> 
#include <util/delay.h>
#include "can.h"
#include "roues.h"
#include "capteurinfrarouge.h"
#include "debug.h"
#include "del.h"
#include "robot.h"
#include "capteurLigne.h"
#include "grille.h"
#include "maison.h"
#include "etatParcours.h"

#define VITESSE_QUATRE_VINGT_QUINZE 95
#define VITESSE_CENT_CINQ 105

int main() {

    Maison maison;
    Robot robot;
    Grille grille;

    EtatParcours etatCourant = EtatParcours::INIT;

    Ligne ligne;
    const uint8_t LIGNES_VIDES_MAX = 5;
    uint8_t compteurLignesVides = 0;
        
    while (true)
    {
        switch (etatCourant) {
            case (EtatParcours::INIT):
                DEBUG_PRINT_MESSAGE("Etat INIT");
                if (robot.positionDepart == 'a') 
                    etatCourant = EtatParcours::FOURCHETTE; 
                
    
                else if (robot.positionDepart == 'y')
                    etatCourant = EtatParcours::GRILLE;
                
                break;
    
            case (EtatParcours::FOURCHETTE):
                DEBUG_PRINT_MESSAGE("Etat FOURCHETTE");
                etatCourant = EtatParcours::MAISON;
                break;
    
            case (EtatParcours::MAISON):
                DEBUG_PRINT_MESSAGE("Etat MAISON");
                if (robot.positionDepart == 'a') 
                {
                    etatCourant = EtatParcours::GRILLE;
                }
                
                else 
                {
                    etatCourant = EtatParcours::PARKING;
                }
                break;
                
                
            case (EtatParcours::GRILLE):
                DEBUG_PRINT_MESSAGE("Etat GRILLE");
                if (robot.positionDepart == 'a') 
                {
                    etatCourant = EtatParcours::PARKING;
                    break;
                }
                
                else 
                {
                    etatCourant = EtatParcours::FOURCHETTE;
                }
     
            case (EtatParcours::PARKING):
                DEBUG_PRINT_MESSAGE("Etat PARKING");
                break;
    
            default:
                break;
        }
    
        switch (etatCourant) {
            case (EtatParcours::INIT):
                DEBUG_PRINT_MESSAGE("Enregistrer directions...");
                robot.enregistrerDirections();
                DEBUG_PRINT_MESSAGE("Suivre ligne PID...");

                while (!(robot.capteurLigne.presenceLigne() == VIDE || robot.capteurLigne.presenceLigne() == PLEIN)) {
                    robot.capteurLigne.suivreLignePIDGrille(robot.capteurLigne, robot.roues); }

                robot.roues.arreter();
    
                if (robot.capteurLigne.presenceLigne() == VIDE) {
                    robot.positionDepart = 'a';
                    DEBUG_PRINT_MESSAGE("Position de depart = a");
                }
                
    
                else if (robot.capteurLigne.presenceLigne() == PLEIN) {
                    robot.positionDepart = 'y';
                    DEBUG_PRINT_MESSAGE("Position de depart = y");
                }
                
                break;
    
            case (EtatParcours::FOURCHETTE):
                DEBUG_PRINT_MESSAGE("Faire fourchette...");

                while (true) {
                    ligne = robot.capteurLigne.presenceLigne();

                    if (robot.capteurLigne.presenceLigne() == VIDE) {
                        DEBUG_PRINT_MESSAGE("bifurquer choix b");
                        compteurLignesVides++;
                        if (compteurLignesVides >= LIGNES_VIDES_MAX) {
                            DEBUG_PRINT_MESSAGE("Ligne vide confirmee, commencer bifurquer...");
                            robot.bifurquer(robot.choixPointB);
                            break;
                        }
                    }
                    else {
                        DEBUG_PRINT_MESSAGE("suivre ligne...");
                        compteurLignesVides = 0;
                        robot.capteurLigne.suivreLignePIDFourchette(robot.capteurLigne, robot.roues);
                    }
                }
            
                while (true) {
                    if (robot.capteurLigne.presenceLigne() == VIDE) {
                        DEBUG_PRINT_MESSAGE("bifurquer choix c");
                        robot.bifurquer(robot.choixPointC);
                        ligne = robot.capteurLigne.presenceLigne();

                        while ( 
                                ligne != DROITE_90_BEAUCOUP && 
                                ligne != GAUCHE_90_BEAUCOUP 
                              )
                        {
                            ligne = robot.capteurLigne.presenceLigne();
                            robot.capteurLigne.suivreLignePIDFourchette(robot.capteurLigne, robot.roues);
                        }
                        DEBUG_PRINT_MESSAGE("Coin detecte");
                        break;
                    }
                    else
                        robot.capteurLigne.suivreLignePIDFourchette(robot.capteurLigne, robot.roues);
                }

                robot.roues.arreter();
                _delay_ms(DELAI_CINQ_CENT);
                robot.roues.avancer(VITESSE_DEUX_CENT, VITESSE_DEUX_CENT);
                _delay_ms(DELAI_CINQ_CENT_CINQUANTE);
                robot.roues.arreter();
                _delay_ms(DELAI_CINQ_CENT);

                // il a rencontre un coin (coin de 90)
                if (robot.choixPointC == 'd') { 
                    robot.tournerGauche(VITESSE_CENT_CINQ);
                }

                else if (robot.choixPointC == 'g') { 
                    robot.tournerDroite(VITESSE_CENT_CINQ);
                }

                while ( (robot.capteurLigne.presenceLigne()) != DROITE_90_BEAUCOUP )
                {
                    robot.capteurLigne.suivreLignePIDFourchette(robot.capteurLigne, robot.roues);
                }

                robot.roues.arreter();

                // tourner au coin
                DEBUG_PRINT_MESSAGE("On a atteint le dernier coin.");
                
                robot.roues.avancer(VITESSE_DEUX_CENT, VITESSE_DEUX_CENT);
                _delay_ms(DELAI_CINQ_CENT_CINQUANTE);
                robot.roues.arreter();
                _delay_ms(DELAI_CINQ_CENT);
                robot.roues.avancer(0, VITESSE_CENT_QUARANTE); // tourner droite 
                _delay_ms(DELAI_QUATRE_CENT);

                DEBUG_PRINT_MESSAGE("Fin du boost du dernier coin");
            
                while (!(robot.capteurLigne.peutAvancer()))
                {
                    robot.roues.avancer(0, VITESSE_QUATRE_VINGT_QUINZE); // tourner droite
                    _delay_ms(DELAI_TOURNER);
                }
            
                robot.roues.arreter();
                _delay_ms(DELAI_ATTENDRE_500_MS);

                DEBUG_PRINT_MESSAGE("Fin de la fourchette");
            
                break;
    
            case (EtatParcours::MAISON):
                // faire maison
                maison.traverserMaison(maison, robot.capteurLigne, robot.roues, robot.del);
                break;
    
            case (EtatParcours::GRILLE):
                // faire grille
                grille.traverserGrille(robot.capteurLigne, robot.capteurInfrarouge, robot, false);
                robot.roues.arreter();

                grille.traverserGrille(robot.capteurLigne, robot.capteurInfrarouge, robot, true);
                robot.roues.arreter();
                break;
    
            case (EtatParcours::PARKING):
                // faire parking
                robot.roues.arreter();
                robot.del.alternerRougeVert2Hz(DELAI_1000_MS);
                break;
    
            default:
                break;
                
        }
    }
    
}    
