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
* But: Implémentation de la classe 'Debug'.
*      La classe 'Debug' est utilise comme outil de resolution
*      de probleme. La commande %make debug active 
*      le mode de debogage.
*
*/

#include "debug.h"
#include <string.h>

Uart uart;

void afficherChaine(const char* message) 
{
    uint8_t longueurMessage = strlen(message);
    for (uint8_t i = 0; i < longueurMessage; i++)
    {  
        uart.transmettreDonneesVersPCViaUART(message[i]); 
    }
    uart.transmettreDonneesVersPCViaUART('\r'); 
    uart.transmettreDonneesVersPCViaUART('\n'); 
}

void afficherUneVariable(uint8_t variable)
{
    char strData[TAILLE_MAXIMALE]; 
    itoa(variable, strData, MODE_DECIMAL);
    afficherChaine(strData);
}

void afficherDebug(const char* message, uint8_t variable)
{
    afficherChaine(message );
    afficherChaine(" ");
    afficherUneVariable(variable);

}
