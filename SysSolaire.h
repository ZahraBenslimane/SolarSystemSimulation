# ifndef _astre_h_
#define _astre_h_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#include "FilesManager.h"
#include "OrbitsCalculator.h"

#define G 6.67433015e-11    // Constante gravitationelle
#define MT  5.972e+24       // Masse de la terre
#define ML 7.342e+22        // Masse de la lune
#define MS   1.989e+30      // Masse du soleil
#define MMer 3.285e10+23    // Masse de Mercure
#define MV   4.867e+24      // Masse de Venus
#define MMar 6.39e+23       // Masse de Mars
#define MJ   1.898e+27      // Masse de Jupiter
#define MSat 5.683e+26      // Masse de Saturne
#define MU   8.681e+25      // Masse de Uranus
#define MN   1.024e+26      // Masse de Neptune

            /**************************** ETAPE 01 :  SYSTEME TERRE LUNE SIMPLIFIE ****************************************/

                                           /**** METHODE 01 :  EULER *************/

double** euler(astre* astre_a,astre astre_fixe, double dt, int *n, double Tsimu);
double * PosInitEuler ( astre astre_a, astre astre_b, int *n);

                                        /**** METHODE 02 :  DIFFERENCES FINIES ****/

void DiffFinies ( astre* astre_a,astre astre_fixe, int Tsimu, double deltaT, int *n);
void DiffFinies2 ( astre* astre_a,astre* astre_b, int Tsimu, double deltaT, int *n);

                                        /**** METHODE 03 :  RK2 *******************/

//ENSSEMBLE DES ODO QUI DEFINISSE LE SYST7ME TERRE-lUNE SIMPLIFIE
double f(double temps,double position ,double vitesse);
double g(double temps,double position,double vitesse, double rayon_t,double MasseAstreFixe);
void RK2(double t0,int index,astre* myAstre,astre myAstreFixe, double deltaT );

                                        /**** METHODE 04 :  RK4 *******************/

void RK4(double t0,int index,astre* myAstre,astre myAstreFixe, double deltaT );
void rungeKutta4(astre myAstre,astre myAstreFixe, double deltaT, double simuT,int* N);


                /************************  ETAPE 02 :  SYSTEME TERRE LUNE ************************************************/

void DiffFinies2 ( astre* astre_a,astre* astre_b, int Tsimu, double deltaT, int *n);


               /************************  ETAPE 04 :  SYSTEME SOLAIRE  ****************************************************/

// FONCTION QUI CALCULE LA POSITION PROCHAINE DE L'ASTRE POINTEUR EN PARAMETRE EN CONSIDERANT LE RESTE COMME DES ASTRES FIXES
void DiffFiniesSYS( astre astre_b,astre* astre_a,astre astre_c,astre astre_d,astre astre_e,astre astre_f,
                   astre astre_g,astre astre_h,astre astre_i,astre astre_j, int Tsimu, double deltaT, int i);

// FONCTION QUI APPELLE DiffFiniesSYS POUR LES 9 ASTRES DANS UNE BOUCLE
void DiffFinies9Forces( astre astre_b,astre astre_a,astre astre_c,astre astre_d,astre astre_e,astre astre_f,
                   astre astre_g,astre astre_h,astre astre_i,astre astre_j, int Tsimu, double deltaT);



# endif // _astre_h
