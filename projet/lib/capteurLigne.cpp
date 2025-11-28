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
* But: Cette classe permet de lire les valeurs du capteurs de ligne et de suivre
*      la ligne en utilisant un PID. Nous implémentons plusieurs méthodes de 
*      suiveur de ligne selon les différents obstacles du parcours.
*      
* Matériel: Suiveur de ligne Maker Line
*           Les Ports C3, C4, C5, C6, C7 de la carte mère sont en entrées
*/ 

#include "capteurLigne.h"
#include "debug.h"
#include "roues.h"
#include "can.h"


CapteurLigne::CapteurLigne()
{
    DDRC &= ~((1 << CAPTEUR1)|(1 << CAPTEUR2)|(1 << CAPTEUR3)|(1 << CAPTEUR4)|(1 << CAPTEUR5)); 
}


uint16_t CapteurLigne:: lireCapteur(uint16_t capteur){
    return ((PINC & (1 << capteur)) != 0)? 1 : 0;
}

Ligne CapteurLigne::presenceLigne()
{
    uint8_t resultat = 0b00000;    

    if ((PINC & (1 << CAPTEUR1)) != 0) resultat |= (1 << 4);  
    if ((PINC & (1 << CAPTEUR2)) != 0) resultat |= (1 << 3);  
    if ((PINC & (1 << CAPTEUR3)) != 0) resultat |= (1 << 2);  
    if ((PINC & (1 << CAPTEUR4)) != 0) resultat |= (1 << 1);  
    if ((PINC & (1 << CAPTEUR5)) != 0) resultat |= (1 << 0);  

    return static_cast<Ligne>(resultat);
}


bool CapteurLigne::peutAvancer()
{
    return (PINC & ((1 << CAPTEUR1) | (1 << CAPTEUR2) | (1 << CAPTEUR3) | (1 << CAPTEUR4) | (1 << CAPTEUR5))) != 0;
}

void CapteurLigne::suivreLignePID(CapteurLigne& capteur, Roues& robot) 
{
    // Constantes du PID 
    double kP = 10;   // Plus kP est grand plus on tourne agressivement
    double kI = 0;    // Corrige les petits écarts persistants
    double kD = 2;    // Plus kD est grand plus il freine les changements trop brusques

    // Variables PID
    static double erreurPrecedente = 0;  
    static double integrale = 0;         

    // Lire la ligne détectée par les capteurs
    Ligne ligne = capteur.presenceLigne();

    // Calcul de l'erreur
    int erreur = 0;
    switch (ligne) 
    {
        case CENTRE:
        case CENTRE_LARGE:
            erreur = 0;  
            break;
        case CENTRE_DROITE:
            erreur = 1;  
            break;
        case CENTRE_GAUCHE:
            erreur = ERREUR_CENTRE_GAUCHE;  
            break;
        case DROITE_PEU:
            erreur = ERREUR_DROITE_PEU;  
            break;
        case DROITE_MOYEN:
            erreur = ERREUR_DROITE_MOYEN;  
            break;
        case DROITE_BEAUCOUP:
            erreur = ERREUR_DROITE_BEAUCOUP;  
            break;
        case GAUCHE_PEU:
            erreur = ERREUR_GAUCHE_PEU;  
            break;
        case GAUCHE_MOYEN:
            erreur = ERREUR_GAUCHE_MOYEN;  
            break;
        case GAUCHE_BEAUCOUP:
            erreur = ERREUR_GAUCHE_BEAUCOUP;  
            break;
        default:
            erreur = 0;  
            break;
    }

    if (ligne == GAUCHE_90_BEAUCOUP || ligne == GAUCHE_90) 
    {
        robot.avancer(105, 0); 
        while ((ligne == 0b00110 || ligne == 0b01100|| ligne == 0b00100|| ligne == 0b01110))
        {
        }
    } 
    else if (ligne == DROITE_90_BEAUCOUP || ligne == DROITE_90)
    {
        robot.avancer(0, 105); 
        while ((ligne == 0b00110 || ligne == 0b01100|| ligne == 0b00100|| ligne == 0b01110))
        {
        }
    }
    else if (ligne == PLEIN) 
    {
        robot.avancer(200, 200);
        _delay_ms(500);
        robot.arreter();
        _delay_ms(1000);
        robot.avancer(255, 0);
        _delay_ms(450);
    }
    else 
    {
        // Application du PID 
        integrale += erreur; 
        double derivee = erreur - erreurPrecedente;

        // Calcul de la correction PID
        double correction = kP * erreur + kI * integrale + kD * derivee;

        // Mise à jour de l'erreur précédente
        erreurPrecedente = erreur;

        // Limiter la correction (valeur de correction entre -255 et 255)
        int maxCorrection = 50;       
        if (correction > maxCorrection) correction = maxCorrection;
        if (correction < -maxCorrection) correction = -maxCorrection;

        // Définir les vitesses des roues gauche et droite
        int vitesseBase = 110;  // Vitesse de base
        int vitesseGauche = vitesseBase - correction;
        int vitesseDroite = vitesseBase + correction;

        // Limiter les vitesses des moteurs entre 0 et 255
        if (vitesseGauche > 255) vitesseGauche = 255;
        if (vitesseGauche < 0) vitesseGauche = 0;

        if (vitesseDroite > 255) vitesseDroite = 255;
        if (vitesseDroite < 0) vitesseDroite = 0;

        // Appliquer les vitesses aux moteurs
        robot.avancer(vitesseGauche, vitesseDroite);
    }
}

void CapteurLigne::suivreLignePIDFourchette(CapteurLigne& capteur, Roues& roues) // suivre ligne PID fourchette
{
    // Constantes du PID 
    double kP = 10;   // Plus kP est grand plus on tourne agressivement
    double kI = 0;    // Corrige les petits écarts persistants
    double kD = 2;    // Plus kD est grand plus il freine les changements trop brusques

    // Variables PID
    static double erreurPrecedente = 0;  
    static double integrale = 0;         

    // Lire la ligne détectée par les capteurs
    Ligne ligne = capteur.presenceLigne();

    // Calcul de l'erreur
    int erreur = 0;
    switch (ligne)
    {
        case CENTRE:
        case CENTRE_LARGE:
            erreur = 0;  
            break;
        case CENTRE_DROITE:
            erreur = 1;  
            break;
        case CENTRE_GAUCHE:
            erreur = -3;  
            break;
        case DROITE_PEU:
            erreur = 2;  
            break;
        case DROITE_MOYEN:
            erreur = 3;  
            break;
        case DROITE_BEAUCOUP:
            erreur = 10;  
            break;
        case GAUCHE_PEU:
            erreur = -2;  
            break;
        case GAUCHE_MOYEN:
            erreur = -4;  
            break;
        case GAUCHE_BEAUCOUP:
            erreur = -5;  
            break;
        case GAUCHE_90_BEAUCOUP:
            erreur = -10;
            break;
        default:
            erreur = 0;  
            break;
    }

    if (ligne == GAUCHE_90_BEAUCOUP || ligne == GAUCHE_90)
    {
        roues.avancer(115, 50);
        while ((ligne == 0b00110 || ligne == 0b01100|| ligne == 0b00100|| ligne == 0b01110))
        {
        }
    } 
    else if (ligne == DROITE_90_BEAUCOUP || ligne == DROITE_90) 
    {
        roues.avancer(50, 115);
        while ((ligne == 0b00110 || ligne == 0b01100|| ligne == 0b00100|| ligne == 0b01110))
        {
        }
    }
    else if (ligne == PLEIN) 
    {
        return;
    }
    else 
    {
        // Application du PID 
        integrale += erreur; 
        double derivee = erreur - erreurPrecedente;

        // Calcul de la correction PID
        double correction = kP * erreur + kI * integrale + kD * derivee;

        // Mise à jour de l'erreur précédente
        erreurPrecedente = erreur;

        // Limiter la correction (valeur de correction entre -255 et 255)
        int maxCorrection = 50;       
        if (correction > maxCorrection) correction = maxCorrection;
        if (correction < -maxCorrection) correction = -maxCorrection;

        // Définir les vitesses des roues gauche et droite
        int vitesseBase = 95;  // Vitesse de base
        int vitesseGauche = vitesseBase - correction;
        int vitesseDroite = vitesseBase + correction;

        // Limiter les vitesses des moteurs entre 0 et 255
        if (vitesseGauche > 255) vitesseGauche = 255;
        if (vitesseGauche < 0) vitesseGauche = 0;

        if (vitesseDroite > 255) vitesseDroite = 255;
        if (vitesseDroite < 0) vitesseDroite = 0;

        // Appliquer les vitesses aux moteurs
        roues.avancer(vitesseGauche, vitesseDroite);
    }
}


void CapteurLigne::suivreLignePIDGrille(CapteurLigne& capteur, Roues& roues) 
{
    // Constantes du PID 
    double kP = 10;   // Plus kP est grand plus on tourne agressivement
    double kI = 0;    // Corrige les petits écarts persistants
    double kD = 2;    // Plus kD est grand plus il freine les changements trop brusques

    // Variables PID
    static double erreurPrecedente = 0;  
    static double integrale = 0;         

    // Lire la ligne détectée par les capteurs
    Ligne ligne = capteur.presenceLigne();

    // Calcul de l'erreur
    int erreur = 0;
    switch (ligne) 
    {
        case CENTRE:
        case CENTRE_LARGE:
            erreur = 0;  
            break;
        case CENTRE_DROITE:
            erreur = 1;  
            break;
        case CENTRE_GAUCHE:
            erreur = -1;  
            break;
        case DROITE_PEU:
            erreur = 2;  
            break;
        case DROITE_MOYEN:
            erreur = 3;  
            break;
        case DROITE_BEAUCOUP:
            erreur = 10;  
            break;
        case GAUCHE_PEU:
            erreur = -2;  
            break;
        case GAUCHE_MOYEN:
            erreur = -3;  
            break;
        case GAUCHE_BEAUCOUP:
            erreur = -4;  
            break;
        default:
            erreur = 0;  
            break;
    }

    if (ligne == GAUCHE_90_BEAUCOUP || ligne == GAUCHE_90 )
    {
        return;
    } 
    else if (ligne == DROITE_90_BEAUCOUP || ligne == DROITE_90) 
    {
        return;
    }
    else if (ligne == PLEIN) 
    {
        return;
    }
    else if (ligne == VIDE) 
    {
        return;
    }
    else 
    {
        // Application du PID 
        integrale += erreur; 
        double derivee = erreur - erreurPrecedente;

        // Calcul de la correction PID
        double correction = kP * erreur + kI * integrale + kD * derivee;

        // Mise à jour de l'erreur précédente
        erreurPrecedente = erreur;

        // Limiter la correction (valeur de correction entre -255 et 255)
        int maxCorrection = 50;       
        if (correction > maxCorrection) correction = maxCorrection;
        if (correction < -maxCorrection) correction = -maxCorrection;

        // Définir les vitesses des roues gauche et droite
        int vitesseBase = 95;  // Vitesse de base
        int vitesseGauche = vitesseBase - correction;
        int vitesseDroite = vitesseBase + correction;

        // Limiter les vitesses des moteurs entre 0 et 255
        if (vitesseGauche > 255) vitesseGauche = 255;
        if (vitesseGauche < 0) vitesseGauche = 0;

        if (vitesseDroite > 255) vitesseDroite = 255;
        if (vitesseDroite < 0) vitesseDroite = 0;

        // Appliquer les vitesses aux moteurs
        roues.avancer(vitesseGauche, vitesseDroite);
    }
}