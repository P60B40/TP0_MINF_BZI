# TP0_LEDAd
## But du laboratoire
L'objectif de ce TP est de découvrir le fonctionnement de la carte PIC32MX et de l'environnement MPLAB Harmony à travers la réalisation d'un chenillard de 8 LEDs, la lecture de deux potentiomètres via les ADC internes et l'affichage des valeurs mesurées sur un écran LCD
## Configuration graphique du timer
La configuration du timer est réalisée à l'aide de l'outil MPLAB Harmony Configurator. Il est important de configurer correctement les périphériques dès le début du projet afin d'utilisé correctement les fonction d'entrée sortie de la carte.

<img width="636" height="94" alt="image" src="https://github.com/user-attachments/assets/c452c5c1-400f-45e0-95fe-eaf665afd549" />

La donnée spécifie le déclenchement d'une interruption toutes les 100 ms. Afin de déterminer les paramètres du Timer 1, la formule suivante est utilisée :

<img width="225" height="72" alt="image" src="https://github.com/user-attachments/assets/fb685be3-a35d-4422-a632-bc6699b127e1" />

avec :
T : période souhaitée (100 ms = 0,1 s)
F : fréquence du microcontrôleur (80 MHz)
Prescaler : facteur de division du timer
Le Timer 1 étant configuré en mode 16 bits, la valeur du registre de période (PR) ne doit pas dépasser : 2^16−1=65535

<img width="538" height="276" alt="image" src="https://github.com/user-attachments/assets/359f5118-e515-49ec-8e95-979b2561bad7" />

 PR = 31249, la valeur étant inférieur à 65535, le prescaler retenu est 256.

## Mesure
### Oscillograme chenillard
<img width="1280" height="824" alt="Chenillard_LED1_A_LED4" src="https://github.com/user-attachments/assets/6eafc2c1-a388-40f2-9ae5-341cbf0101a6" />
L'oscillogramme du chenillard montre que les LEDs s'allument successivement avec un intervalle de 200 ms entre chaque commutation. La période observée pour les quatre LEDs est de 800 ms

### Oscillograme délais de 3 seconde
<img width="1280" height="824" alt="3 seconde de delais" src="https://github.com/user-attachments/assets/898d9f40-b81e-4286-b09e-50c5e631fbef" />
L'oscillogramme met en évidence le délai de 3 secondes appliqué avant l'activation du chenillard et le démarrage de la lecture des entrées analogiques (ADC). Durant cette phase d'attente, toutes les LEDs restent allumées. L'état bas observé sur les signaux correspond donc à cette temporisation initiale de 3 secondes. 



