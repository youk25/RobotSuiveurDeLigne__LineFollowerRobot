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
* But: Cette classe permet de traverser la grille du parcours.
*/    

#include "grille.h"

void Grille::traverserGrille(CapteurLigne& capteurLigne, CapteurInfrarouge& capteurRouge, Robot& robot, bool deuxiemePassage) {
    DEBUG_PRINT_MESSAGE("VerifierPoteauGrille ...");
  
    // boost avancer
    if (!deuxiemePassage) {
        DEBUG_PRINT_MESSAGE("Robot avance pour se positionner.");
        robot.roues.avancer(165, 165);
        _delay_ms(400);
    }
    DEBUG_PRINT_MESSAGE("Robot arrete.");
    robot.roues.arreter();
    _delay_ms(1000);


    // ÉTAPE 1 : Poteau Centre?
    // verification poteau centre

    //  OUI (POTEAU CENTRE)
    DEBUG_PRINT_MESSAGE("Vérification du poteau centre...");
    if (capteurRouge.presencePoteauGrille()) {
        DEBUG_PRINT_MESSAGE("Poteau centre detecte.");

        // décaler à gauche
        robot.roues.avancer(155, 0);
        _delay_ms(500);
        DEBUG_PRINT_MESSAGE("Robot décalé à gauche arrêté.");
        robot.roues.arreter();
        _delay_ms(1000);
        // ÉTAPE 2 : Poteau Gauche?
        // vérification poteau gauche
        // tac-tac jusqu'à ce qu'on trouve une ligne ou qu'on capte un poteau
        while((capteurLigne.presenceLigne() == VIDE) && (!capteurRouge.presencePoteauGrille())){
            robot.roues.avancer(110, 0);
            _delay_ms(5);
        }
        DEBUG_PRINT_MESSAGE("Robot arrete.");
        robot.roues.arreter();
        _delay_ms(1000);

        // OUI (POTEAU GAUCHE)
        if (capteurLigne.presenceLigne() == VIDE){      // si on est pas sur une ligne
            DEBUG_PRINT_MESSAGE("Poteau gauche détecté.");
            DEBUG_PRINT_MESSAGE("Revenir au centre.");
            while((capteurLigne.presenceLigne() == VIDE)){      // on redresse vers le centre
                robot.roues.avancer(0, 110);                    // jusqu'à ce qu'on trouve une ligne
                _delay_ms(5);
            }    
            robot.roues.arreter();
            _delay_ms(1000);
            robot.roues.reculer(140);
            _delay_ms(600);
            DEBUG_PRINT_MESSAGE("Chemin libre à droite.");

            // boost à droite
            robot.roues.avancer(0, 155);
            _delay_ms(500);
            robot.del.allumerVerte();
            robot.roues.arreter();
            _delay_ms(500);
            while((capteurLigne.presenceLigne() == VIDE)){      // on redresse vers la droite
                robot.roues.avancer(0, 110);                    // jusqu'à ce qu'on trouve une ligne
                _delay_ms(5);
            }
            robot.del.eteindre();
            robot.roues.arreter(); 
            _delay_ms(1000);

            // aller vers le chemin de droite
            while (capteurLigne.presenceLigne() != 0b11110 &&
                    capteurLigne.presenceLigne() != 11100 &&
                    capteurLigne.presenceLigne() != 0b11000 &&
                    capteurLigne.presenceLigne() != 0b11111) {
                        DEBUG_PRINT_MESSAGE("Suivre ligne à droite.");
                        capteurLigne.suivreLignePIDGrille(capteurLigne, robot.roues);
            }
            DEBUG_PRINT_MESSAGE("Coin gauche detecte.");
            tournerGaucheCoin(robot);

            // continuer jusqu'à la prochaine ligne de verification
            int compteurIntersectionDroite = 0;
            while(compteurIntersectionDroite < 2){
                DEBUG_PRINT_MESSAGE_VARIABlE("Compteur intersection droite: ", compteurIntersectionDroite);
                if (capteurLigne.presenceLigne() == 0b11110 ||
                    capteurLigne.presenceLigne() == 0b11100 ||     
                    capteurLigne.presenceLigne() == 0b11111){
                        compteurIntersectionDroite += 1;
                    DEBUG_PRINT_MESSAGE("Intersection detectee.");
                }
                else capteurLigne.suivreLignePIDGrille(capteurLigne, robot.roues);
            }
            DEBUG_PRINT_MESSAGE("Deux intersections detectees.");
            robot.roues.arreter();
            _delay_ms(1000);

            // si on est au 2e passage, on tourne à droite après 1 intersection
            if (deuxiemePassage){
                tournerDroiteCoin(robot);
                int compteurIntersectionDroite = 0;
                while(compteurIntersectionDroite < 2){
                    if (capteurLigne.presenceLigne() == 0b01111 ||     
                        capteurLigne.presenceLigne() == 0b11111){   // capteurLigne.presenceLigne() == 0b00111 ||
                            compteurIntersectionDroite += 1;
                        DEBUG_PRINT_MESSAGE_VARIABlE("Intersection detectee.", compteurIntersectionDroite);
                    }
                    else capteurLigne.suivreLignePIDGrille(capteurLigne, robot.roues);
                }
                robot.roues.arreter();
                _delay_ms(1000);
                tournerDroiteCoin(robot);
                return;     // on a parké
            }

            // si on est au 1er passage, on tourne à gauche pour remettre le robot au chemin du centre
            tournerGaucheCoin(robot);
            while (capteurLigne.presenceLigne() != CENTRE &&
                    capteurLigne.presenceLigne() != CENTRE_LARGE &&
                    capteurLigne.presenceLigne() != CENTRE_DROITE &&
                    capteurLigne.presenceLigne() != CENTRE_GAUCHE){
                        robot.roues.avancer(0, 110);
                        _delay_ms(5);
                            }

            robot.roues.arreter();
            _delay_ms(1000);
            while (capteurLigne.presenceLigne() != PLEIN)
                capteurLigne.suivreLignePIDGrille(capteurLigne, robot.roues);
            robot.roues.arreter();
            _delay_ms(1000);
            tournerDroiteCoin(robot);
            robot.roues.reculer(140);
            _delay_ms(600);
            return;     // retour au centre après passage à gauche
                
        }
        // else{
        
        // PAS POTEAU GAUCHE
        else if ((capteurLigne.presenceLigne() != VIDE)){       // si on capte une ligne --> pas de poteau
            DEBUG_PRINT_MESSAGE("Pas poteau gauche.");
            while(capteurLigne.presenceLigne() != 0b01111 &&                    // tant qu'on est pas à un coin
                capteurLigne.presenceLigne() != 0b00111 && 
                capteurLigne.presenceLigne() != 0b11111) {
                DEBUG_PRINT_MESSAGE("Suivre ligne à gauche.");
                capteurLigne.suivreLignePIDGrille(capteurLigne, robot.roues);   
                }
            
            DEBUG_PRINT_MESSAGE("Coin droite detecte.");
            tournerDroiteCoin(robot);
            robot.del.allumerVerte();
            
            // continuer jusqu'à la prochaine ligne de verification
            int compteurIntersectionGauche = 0;
            while(compteurIntersectionGauche < 2){
                DEBUG_PRINT_MESSAGE_VARIABlE("Compteur intersection gauche: ", compteurIntersectionGauche);
                if (capteurLigne.presenceLigne() == 0b01111 ||
                    capteurLigne.presenceLigne() == 0b00111 || 
                    capteurLigne.presenceLigne() == 0b11111){
                        compteurIntersectionGauche += 1;
                    DEBUG_PRINT_MESSAGE("Intersection detectee.");
                }
                else capteurLigne.suivreLignePIDGrille(capteurLigne, robot.roues);
            }
            robot.del.eteindre();
            DEBUG_PRINT_MESSAGE("Deux intersections detectees.");
            robot.roues.arreter();
            _delay_ms(1000);

            // si on est au 2e passage, on tourne à droite après 3 intersection
            if (deuxiemePassage){
                tournerDroiteCoin(robot);
                int compteurIntersectionGauche = 0;
                while(compteurIntersectionGauche < 4){
                    if (capteurLigne.presenceLigne() == 0b01111 ||     
                        capteurLigne.presenceLigne() == 0b11111){ // capteurLigne.presenceLigne() == 0b00111 ||
                            compteurIntersectionGauche += 1;
                        DEBUG_PRINT_MESSAGE_VARIABlE("Intersection detectee.", compteurIntersectionGauche);
                    }
                    else capteurLigne.suivreLignePIDGrille(capteurLigne, robot.roues);
                }
                robot.roues.arreter();
                _delay_ms(1000);
                tournerDroiteCoin(robot);
                return;             // on a parké
            }
            

            // si on est au 1er passage, on tourne à droite pour remettre le robot au chemin du centre
            tournerDroiteCoin(robot);
            while(capteurLigne.presenceLigne() != PLEIN)
                capteurLigne.suivreLignePIDGrille(capteurLigne, robot.roues);
            robot.roues.arreter();
            _delay_ms(1000);
            tournerGaucheCoin(robot);
            robot.roues.arreter();
            _delay_ms(1000);
            robot.roues.reculer(140);
            _delay_ms(600);
            return;     // retour au centre après passage à gauche
        
        }
    }

    else {
        DEBUG_PRINT_MESSAGE("Pas de poteau centre détecté.");
        // NON (PAS POTEAU CENTRE)
        // pas de poteau au centre      
        // continuer jusqu'à la prochaine ligne de verification
        robot.del.allumerVerte();
        int compteurIntersectionCentre = 0;
        while(compteurIntersectionCentre < 2){
            DEBUG_PRINT_MESSAGE_VARIABlE("Compteur intersection centre: ", compteurIntersectionCentre);
            if (capteurLigne.presenceLigne() == 0b01111 ||
                capteurLigne.presenceLigne() == 0b11110 || 
                capteurLigne.presenceLigne() == 0b11111){
                    compteurIntersectionCentre += 1;
                DEBUG_PRINT_MESSAGE("Intersection detectee.");
            }
            else capteurLigne.suivreLignePIDGrille(capteurLigne, robot.roues);
        }
        DEBUG_PRINT_MESSAGE("Deux intersections detectees.");
        robot.del.eteindre();
        robot.roues.arreter();
        _delay_ms(1000);
        
        // si on est au 2e passage, on tourne à droite après 2 intersections
        if (deuxiemePassage){
            tournerDroiteCoin(robot);
            int compteurIntersectionCentre = 0;
            while(compteurIntersectionCentre < 3){
                if (capteurLigne.presenceLigne() == 0b01111 ||
                    capteurLigne.presenceLigne() == 0b11111){ // capteurLigne.presenceLigne() == 0b00111 ||     
                        compteurIntersectionCentre += 1;
                    DEBUG_PRINT_MESSAGE_VARIABlE("Intersection detectee.", compteurIntersectionCentre);
                }
                else capteurLigne.suivreLignePIDGrille(capteurLigne, robot.roues);
            }
            robot.roues.arreter();
            _delay_ms(1000);
            tournerDroiteCoin(robot);
            return;     // on a parké
        }
        // si on est au 1er passage, on reste au centre pcq on est déjà dans le chemin du centre
        return;     // retour au centre après passage au centre
    }    
    
}
 

void Grille::tournerDroiteCoin(Robot& robot){
    DEBUG_PRINT_MESSAGE("Tourner droite coin");
    robot.roues.arreter();          // quand on est à un coin, on s'arrète
    _delay_ms(1000); 
    robot.roues.avancer(155, 155);  // boost devant
    _delay_ms(600);
    robot.roues.arreter();
    _delay_ms(1000);
    robot.roues.avancer(0, 155);    // boost droite
    _delay_ms(550);
    robot.roues.arreter();
    _delay_ms(1000);

    while (robot.capteurLigne.presenceLigne() != CENTRE &&
            robot.capteurLigne.presenceLigne() != CENTRE_DROITE &&
            robot.capteurLigne.presenceLigne() != CENTRE_GAUCHE) {
        robot.roues.avancer(0, 110);
        _delay_ms(5);
    }
}

void Grille::tournerGaucheCoin(Robot& robot){
    DEBUG_PRINT_MESSAGE("Tourner gauche coin");
    robot.roues.arreter();          // quand on est à un coin, on s'arrète
    _delay_ms(1000); 
    robot.roues.avancer(155, 155);  // boost devant
    _delay_ms(650);
    robot.roues.arreter();
    _delay_ms(1000);
    robot.roues.avancer(155, 0);    // boost gauche
    _delay_ms(550);
    robot.roues.arreter();
    _delay_ms(1000);

    while (robot.capteurLigne.presenceLigne() != CENTRE &&
            robot.capteurLigne.presenceLigne() != CENTRE_DROITE &&
            robot.capteurLigne.presenceLigne() != CENTRE_GAUCHE) {
        robot.roues.avancer(110, 0);
        _delay_ms(5);
    }
}