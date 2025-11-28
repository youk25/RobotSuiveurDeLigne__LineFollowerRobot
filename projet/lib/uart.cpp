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

#include "uart.h"
#include <util/delay.h>

Uart::Uart()
{
    UBRR0H = 0;
    UBRR0L = INITIALISER_BAUD;
    UCSR0A = 0; 
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) ; 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
void Uart::transmettreDonneesVersPCViaUART (uint8_t donnee)
{
    while ( !( UCSR0A & (1 << UDRE0)));
    UDR0 = donnee;        
}