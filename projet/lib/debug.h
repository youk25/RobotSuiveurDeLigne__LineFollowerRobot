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
* But: Définition de la classe 'Debug'.
*      La classe 'Debug' est utilise comme outil de resolution
*      de probleme. La commande %make debug active 
*      le mode de debogage.
*
*/

#pragma once
#define F_CPU 8000000UL

#include <avr/io.h>
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAXIMALE 4
#define MODE_DECIMAL    10

void afficherDebug(const char* message, uint8_t variable);
void afficherUneVariable(uint8_t variable);
void afficherChaine(const char* message);
#ifdef DEBUG
#define DEBUG_PRINT(variable) afficherUneVariable(variable);
#define DEBUG_PRINT_MESSAGE_VARIABlE(message, variable) afficherDebug(message, variable); 
#define DEBUG_PRINT_MESSAGE(message )afficherChaine(message) 

#else
#define DEBUG_PRINT(variable) 
#define DEBUG_PRINT_MESSAGE_VARIABlE(message, variable) 
#define DEBUG_PRINT_MESSAGE(message )
#endif
