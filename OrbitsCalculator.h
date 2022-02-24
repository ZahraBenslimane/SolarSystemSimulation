#ifndef orbits_Calculator_h_
#define orbits_Calculator_h_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "FilesManager.h"
#include "SysSolaire.h"



           /************************  ETAPE 02 :  SYSTEME TERRE LUNE ***********************************************************/

/*ENSSEMBLE DES ODO QUI DEFINISSE LE SYST7ME TERRE-lUNE */
double f2(double temps,double position_A ,double vitesse_A);
double g2(double temps,double position_A ,double vitesse_A, double rayon_t, double position_B, double Masse_B );

void RK4_2(double t0,int index,astre* myAstre_A, astre myAstre_B,double deltaT);
void rungeKutta4_doubleForces(astre myAstre_A, astre myAstre_B , double deltaT, double simuT,int* N);

          /************************  ETAPE 04 :  SYSTEME SOLAIRE  ****************************************************/

//ENSSEMBLE DES ODO QUI DEFINISSE LE SYSTEME SOLAIRE COMPLET
double g33(double position_A,double position_B, double masse_B, double rayonAB);


double g3(double temps,double position0 , double vitesse0, double position_1, double Masse_1,  double rayon_1,
                       double position_2, double Masse_2, double rayon_2, double position_3, double Masse_3, double rayon_3,
                       double position_4, double Masse_4, double rayon_4, double position_5, double Masse_5, double rayon_5,
                       double position_6, double Masse_6, double rayon_6, double position_7, double Masse_7, double rayon_7,
                       double position_8, double Masse_8, double rayon_8, double position_9, double Masse_9, double rayon_9);

void RK4_3(double t0,int index,astre* myAstre, astre myAstre_1, astre myAstre_2, astre myAstre_3, astre myAstre_4 ,astre myAstre_5, astre myAstre_6,
                                astre myAstre_7, astre myAstre_8, astre myAstre_9 ,double deltaT);

void rungeKutta4_nineForces(astre myAstre, astre myAstre_1, astre myAstre_2, astre myAstre_3, astre myAstre_4 ,astre myAstre_5,
                            astre myAstre_6, astre myAstre_7, astre myAstre_8, astre myAstre_9,double deltaT, double simuT);




#endif // orbits_Calculator_h_

