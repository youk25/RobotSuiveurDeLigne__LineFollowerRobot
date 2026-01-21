#include "maison.h"

void Maison::traverserMaison(Maison& maison, CapteurLigne& capteur, Roues& robot, Del& del)
{
    uint8_t compteur = 0;
    bool fin = false;
    bool sortirMaison = false;

    while (compteur <= MAX_INTERSECTIONS) 
    {
        Ligne ligne = capteur.presenceLigne();

        if ((ligne == DROITE_90 || ligne == DROITE_90_BEAUCOUP || ligne == PLEIN))
        {
            compteur = compteur + 1;
            robot.arreter();
            _delay_ms(DELAI_ATTENDRE_400_MS);

            if (compteur == 1 ) 
            {
                del.allumerRouge();
                _delay_ms(DELAI_ATTENDRE_1000_MS);
                robot.avancer(PWM_AVANCER_200, PWM_AVANCER_200);
                _delay_ms(DELAI_ATTENDRE_500_MS);
                capteur.suivreLignePID(capteur, robot);
            }

            else if (compteur == MAX_INTERSECTIONS) 
            {
                del.allumerVerte();

                robot.avancer(PWM_AVANCER, PWM_AVANCER);
                _delay_ms(DELAI_ATTENDRE_1000_MS);
                robot.arreter();
                _delay_ms(DELAI_ATTENDRE_500_MS);
                robot.avancer(0, PWM_AVANCER_200);
                _delay_ms(DELAI_ATTENDRE_500_MS);
                while (!capteur.peutAvancer())
                {
                    robot.avancer(0, PWM_TOURNER); 
                    _delay_ms(DELAI_LECTURE_MS);
                }
                robot.arreter();
                _delay_ms(DELAI_ATTENDRE_500_MS);
                del.eteindre();
                break;
            }

            while ((ligne = capteur.presenceLigne()) == DROITE_90 || ligne == DROITE_90_BEAUCOUP || ligne == PLEIN) 
            {
                _delay_ms(DELAI_LECTURE_MS);
            }
        } 
        else 
        {
            capteur.suivreLignePID(capteur, robot);
        }
    }
    
    while (!fin) {
        Ligne ligne = capteur.presenceLigne();
        if (capteur.peutAvancer() && ligne != DROITE_90_BEAUCOUP && ligne != DROITE_90) 
        {
            capteur.suivreLignePID(capteur, robot);
            if(capteurRouge.presencePoteau())
            {
                del.allumerRouge();
                fin = true;
            }
            else
            {
                del.allumerVerte();
            }
        }
        
        else 
        {
            robot.arreter();
            _delay_ms(DELAI_ATTENDRE_1000_MS);
            robot.avancer(PWM_AVANCER_200, PWM_AVANCER_200);
            _delay_ms(DELAI_ATTENDRE_500_MS);
            while (!capteur.peutAvancer())
            {
                robot.avancer(0, PWM_TOURNER); 
                _delay_ms(DELAI_LECTURE_MS);
            }
        }
    }

    robot.arreter();
    _delay_ms(DELAI_ATTENDRE_1000_MS);
    robot.avancer(0, PWM_TOURNER_90);
    _delay_ms(DELAI_ATTENDRE_500_MS);

    while (!capteur.peutAvancer())
    {   
        robot.avancer(0, PWM_TOURNER);
        _delay_ms(DELAI_LECTURE_MS);
    }

    del.allumerVerte();
    robot.arreter();
    _delay_ms(DELAI_ATTENDRE_500_MS);  

    while(!sortirMaison)
    {
        Ligne ligne = capteur.presenceLigne();
        if (capteur.peutAvancer()        && 
            (ligne != PLEIN              && 
             ligne != GAUCHE_90_BEAUCOUP && 
             ligne != GAUCHE_90          && 
             ligne != DROITE_90_BEAUCOUP && 
             ligne != DROITE_90))
        {
            capteur.suivreLignePID(capteur, robot);
        } 
        else 
        {
            robot.arreter();
            _delay_ms(DELAI_ATTENDRE_1000_MS);
            robot.avancer(PWM_AVANCER_200, PWM_AVANCER_200);
            _delay_ms(DELAI_ATTENDRE_500_MS);
            robot.arreter();
            _delay_ms(DELAI_ATTENDRE_1000_MS);

            while (!capteur.peutAvancer())
            {
                robot.avancer(0, PWM_TOURNER); 
                _delay_ms(DELAI_LECTURE_MS);
            }
        }
    }
}