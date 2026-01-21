## MyShayla324 (Équipe 1013)
Le MyShayla324 a été réalisé dans le cadre du projet intégrateur de première année en génie logiciel/informatique à Polytechnique Montréal.

# Objectif
Le but de ce projet est de créer un robot qui suit une ligne noire sur un parcours défini. Le robot doit être capable de détecter et d'éviter des obstacles sur son chemin, tout en respectant certaines contraintes de vitesse et de distance.
Les trois obstacles principaux du robot sont :
1. La fourchette
2. La maison
3. La grille

Le robot doit compléter une boucle complète du parcours et revenir à son point de départ.

# structure du projet
app/
: Contient fichier main à exécuter.
lib/
: Contient les fichiers de la librairie.

Commandes: make dans lib, make install dans app

## Branchements matériels

| Composant              | Connexion Microcontrôleur                          | Détails                                 |
|------------------------|----------------------------------------------------|-----------------------------------------|
| **Capteurs de ligne**  | **Port C** – broches **C3 à C7**                  | 5 capteurs pour suivre la ligne noire   |
| **Capteur infrarouge** | **A6 (entrée analogique)** + **VCC et GND (Port A)** | Mesure de distance pour détection de poteau |
| **Roue gauche**        | **B2** (direction) + **B4** (PWM EN)              | Contrôle de vitesse et direction        |
| **Roue droite**        | **B3** (direction) + **B5** (PWM EN)              | Contrôle de vitesse et direction        |
| **Bouton poussoir**    | **D3** (Port D) + VCC et GND                      | Utilisé pour démarrer le robot          |
| **Interruption (INT)** | **D2** (Port D)                                   | Déclenchement via interruption externe  |
| **Piézo (buzzer)**     | **D6 et D7** (Port D)                             | Émission de sons ou mélodies            |
| **DEL RGB**            | **A0 et A1** (Port A)                             | Contrôle des couleurs                   |
| **Alimentation**       | **5V et GND**                                     | Source d’alimentation du robot          |


# Librairie - `lib/`
# Contenu de la librairie :

| Module             | Description |
|--------------------|-------------|
| **Can**            | Convertisseur analogique-numérique (CAN) |
| **CapteurInfrarouge** | Détection de poteaux dans la grille ou la maison |
| **CapteurLigne**   | Suivi de ligne noire via 5 capteurs |
| `presenceLigne()`  | Retourne la position de la ligne lue |
| **Debug**          | Affichage des messages UART pour le débogage |
| **Del**            | Contrôle de la DEL tricolore (rouge, verte, ambre) |
| **Grille**         | Contient la logique de détection et traversée de la grille |
| **Maison**         | Logique de détection d’intersections, poteau rouge et sortie |
| **Musique**        | Mélodies pour feedback sonore |
| **Robot**          | Structure principale regroupant les composants |
| **Roues**          | Contrôle de la vitesse et direction des moteurs |



## Démarrage du robot

1. Brancher le robot via USB.
2. **Appuyer deux fois** sur n’importe quel bouton poussoir (INT ou bouton blanc).
3. Le robot démarre automatiquement :
   - suit le parcours,
   - franchit la fourchette, la maison et la grille,
   - revient à son point de départ.

---


## Auteurs

Projet réalisé par l'Équipe 1013 dans le cadre du cours Projet intégrateur 1  
Département de génie logiciel / informatique  
Polytechnique Montréal – 2024-2025

* Auteurs: Yolaine Ntabugi Karemere
*          Yousra Khettal
*          Oriane Claudelle
*          Émy Xiao
---
