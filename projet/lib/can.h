/*
 * Section: 01
 * Équipe:  1013
 * Auteurs: Yolaine Ntabugi Karemere
 *          Yousra Khettal
 *          Oriane Claudelle
 *          Émy Xiao
 *
 * Date de remise: 16 Avril 2025
 *
 * Classe permettant l'acces au convertisseur analogique/numerique
 * du microcontroleur ATMega16 de Atmel.
 *
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Matthew Khouzam et Jerome Collin
 * 2005-2006
 *
 * Code qui n'est sous aucune license.
 *
 * But : Définition de la classe can.
 *       Le constructeur initialise le convertisseur.
 *       Une lecture enclanche une conversion et le résultat
 *       est retourné sur 16 bits.
 */

#ifndef CAN_H
#define CAN_H

#include <avr/io.h> 

/*
 * Classe can:
 *   Le constructeur initialise le convertisseur.
 *   Une lecture enclanche une conversion et le resultat
 *   est retourne sur 16 bits.
 *
 */

class can
{
public:

   can();
   ~can();

   // retourne la valeur numerique correspondant a la valeur
   // analogique sur le port A.  pos doit etre entre 0 et 7
   // inclusivement.  Seulement les 10 bits de poids faible
   // sont significatifs.
   uint16_t lecture(uint8_t pos);

private:
   // Donnees membres - aucun

};

#endif /* CAN_H */
