# TP0_LEDAd
## But du laboratoire
L'objectif de ce TP est de découvrir le fonctionnement de la carte PIC32MX et de l'environnement MPLAB Harmony à travers la réalisation d'un chenillard de 8 LEDs, la lecture de deux potentiomètres via les ADC internes et l'affichage des valeurs mesurées sur un écran LCD
## Configuration graphique du timer
La configuration du timer est réalisée à l'aide de l'outil MPLAB Harmony Configurator. Il est important de configurer correctement les périphériques dès le début du projet afin d'utilisé correctement les fonction d'entrée sortie de la carte.
<img width="636" height="94" alt="image" src="https://github.com/user-attachments/assets/c452c5c1-400f-45e0-95fe-eaf665afd549" />

La donnée spécifie une interruption toutes les 100 millisecondes. Le calcul permettant de déterminer les paramètres du timer est le suivant :
TP=((t*freq.uc)/Prescaler)-1

<img width="225" height="72" alt="image" src="https://github.com/user-attachments/assets/fb685be3-a35d-4422-a632-bc6699b127e1" />
Avec : un temps de 100ms -> 0.1s, une fréquence de microntroller de 80MHz. Comme le timer est configuré en mode 16bit la période ne doit pas dépasser 65535
Ce qui donne : ((0.1s*80MHz)/256))-1=31249 ce qui est plus petit que 65535 donc le prescaler doit être de 256.
<img width="538" height="276" alt="image" src="https://github.com/user-attachments/assets/359f5118-e515-49ec-8e95-979b2561bad7" />




