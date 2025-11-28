/*  
* Section: 01
* Equipe:  1013
* Auteurs: Yolaine Ntabugi Karemere
*          Yousra Khettal
*          Oriane Claudelle
*          Émy Xiao
* 
* Date de remise : 17 Mars 2025
*
* But: Implémentation de la classe Uart.
*      La classe UART permet la communication avec la mémoire flash de l'ATMega324 
*      en utilisant le protocole RS232 via le port USB. La conversion de protocole
*      est faite par l'ATMega8 et le programme serieViaUSB. Ainsi,cela permet de
*      transmettre et recevoie des données entre la carte mère et le PC. 
*/

#pragma once
#include <avr/io.h>

#define INITIALISER_BAUD 0xCF

class Uart
{
public:
    Uart(); 
    ~Uart() = default; 
    
    void transmettreDonneesVersPCViaUART (uint8_t donnee);
};
