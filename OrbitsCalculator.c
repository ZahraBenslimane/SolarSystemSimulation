#include "orbitsCalculator.h"
#include "FilesManager.h"
#include "SysSolaire.h"



    /*******************************        ETAPE 02 : SYSTEME TERRE-LUNE      **************************************/


double f2(double temps,double position_A ,double vitesse_A){
    return vitesse_A;
}

double g2(double temps,double position_A ,double vitesse_A, double rayon_t, double position_B, double Masse_B ){
    return ( ( -(G*Masse_B)*(position_A - position_B) )/(pow(rayon_t,3)) );
}

void RK4_2(double t0,int index,astre* myAstre_A, astre myAstre_B,double deltaT){
    double K1,K2,K3,K4,L1,L2,L3,L4;
    double current_Pos_A,current_V_A,current_Pos_B,current_Pos_AY,current_V_AY,current_Pos_BY;
    double Masse_B = myAstre_B.masse;
    double rayon_t = sqrt(  pow (( myAstre_A->position[index-1][0]- myAstre_B.position[index-1][0]), 2)
                          + pow ( (myAstre_A->position[index-1][1]- myAstre_B.position[index-1][1] ), 2 ) );
    // x
    current_Pos_A = myAstre_A->position[index-1][0];
    current_V_A   = myAstre_A->vitesse[index-1][0];
    current_Pos_B = myAstre_B.position[index-1][0];

    K1 = deltaT * f2(t0, current_Pos_A, current_V_A);
    L1 = deltaT * g2(t0, current_Pos_A, current_V_A, rayon_t,current_Pos_B, Masse_B);
    K2 = deltaT * f2(t0+(deltaT/2), current_Pos_A+(K1/2), current_V_A+(L1/2));
    L2 = deltaT * g2(t0+(deltaT/2), current_Pos_A+(K1/2), current_V_A+(L1/2), rayon_t, current_Pos_B, Masse_B);
    K3 = deltaT * f2(t0+(deltaT/2), current_Pos_A+(K2/2), current_V_A+(L1/2));
    L3 = deltaT * g2(t0+(deltaT/2), current_Pos_A+(K2/2), current_V_A+(L1/2), rayon_t,current_Pos_B, Masse_B);
    K4 = deltaT * f2(t0+deltaT, current_Pos_A+K3, current_V_A+L3 );
    L4 = deltaT * g2(t0+deltaT, current_Pos_A+K3, current_V_A+L3, rayon_t,current_Pos_B, Masse_B);

    myAstre_A->position[index][0] = current_Pos_A + (K1+2*K2+2*K3+K4)/6;
    myAstre_A->vitesse[index][0]  = current_V_A + (L1+2*L2+2*L3+L4)/6;


    // y
    current_Pos_AY = myAstre_A->position[index-1][1];
    current_V_AY   = myAstre_A->vitesse[index-1][1];
    current_Pos_BY = myAstre_B.position[index-1][1];

    K1 = deltaT * f2(t0, current_Pos_AY, current_V_AY);
    L1 = deltaT * g2(t0, current_Pos_AY, current_V_AY, rayon_t,current_Pos_BY, Masse_B);
    K2 = deltaT * f2(t0+(deltaT/2), current_Pos_AY+(K1/2), current_V_AY+(L1/2));
    L2 = deltaT * g2(t0+(deltaT/2), current_Pos_AY+(K1/2), current_V_AY+(L1/2), rayon_t, current_Pos_BY, Masse_B);
    K3 = deltaT * f2(t0+(deltaT/2), current_Pos_AY+(K2/2), current_V_AY+(L1/2));
    L3 = deltaT * g2(t0+(deltaT/2), current_Pos_AY+(K2/2), current_V_AY+(L1/2), rayon_t,current_Pos_BY, Masse_B);
    K4 = deltaT * f2(t0+deltaT, current_Pos_AY+K3, current_V_AY+L3 );
    L4 = deltaT * g2(t0+deltaT, current_Pos_AY+K3, current_V_AY+L3, rayon_t,current_Pos_BY, Masse_B);

    myAstre_A->position[index][1] = current_Pos_AY + (K1+2*K2+2*K3+K4)/6;
    myAstre_A->vitesse[index][1]  = current_V_AY + (L1+2*L2+2*L3+L4)/6;


}


void rungeKutta4_doubleForces(astre myAstre_A, astre myAstre_B , double deltaT, double simuT,int* N){
    *N = ceil(simuT/deltaT);
    double t0=0.;
    int index;
    for (index=1; index< (*N); index++){
        // EQUATION DU MOUVEMENT DE A
        RK4_2(t0,index,&myAstre_A, myAstre_B,deltaT);
        // EQUATION DU MOUVEMENT DE B
        RK4_2(t0,index,&myAstre_B, myAstre_A,deltaT);
    }
}

/*******************************        ETAPE 04 : SYSTEME SOLAIRE      *************************************************/


// LES EDO DECRIVANT LE SYSYTEME SOLAIRE

double g33(double position_A,double position_B, double masse_B, double rayonAB){
    return ( ( - G* masse_B * (position_A - position_B) )/ (pow(rayonAB,3)) );
}

double g3(double temps,double position0 , double vitesse0, double position_1, double Masse_1,  double rayon_1,
                       double position_2, double Masse_2, double rayon_2, double position_3, double Masse_3, double rayon_3,
                       double position_4, double Masse_4, double rayon_4, double position_5, double Masse_5, double rayon_5,
                       double position_6, double Masse_6, double rayon_6, double position_7, double Masse_7, double rayon_7,
                       double position_8, double Masse_8, double rayon_8, double position_9, double Masse_9, double rayon_9)
{
    double res = g33(position0,position_1,Masse_1,rayon_1) + g33(position0,position_2,Masse_2,rayon_2) + g33(position0,position_3,Masse_3,rayon_3)
               + g33(position0,position_4,Masse_4,rayon_4) + g33(position0,position_5,Masse_5,rayon_5) + g33(position0,position_6,Masse_6,rayon_6)
               + g33(position0,position_7,Masse_7,rayon_7) + g33(position0,position_8,Masse_8,rayon_8) + g33(position0,position_9,Masse_9,rayon_9);

    return res;
}

// DANS CETTE FONCTION NOUS CONSIDERONS L'INTERRACTION ENTRE TOUS LES ASTRES Y COMPRIS LA LUNE EN GARDANT LE SOLEIL FIXE
// NOUS Y CALCULONS LE POINT PROCHAIN D'UN SEUL ASTRE DEFINI EN POINTEUR EN CONSIDERANT TOUS LES AUTRES ASTRES FIXES
// NOUS AVONS COMMENCE PAR DEFINIR 9 RAYONS POUR LES 9 PLANETES ( SOLEIL EXCLU CAR IL RESTE FIXE ), DANS LESQUELS NOUS
// CALCULONS LA DISTANCE DE L'ASTRE EN MOUVEMENT PAR RAPPORT AUX 9 AUTRES ASTRES FIXES
// PUIS NOUS AVONS ETABLIS LES EQUATIONS DES POSITIONS EN X ET Y DE L'ASTRE EN MOUVEMENT EN PRENANT EN CONSIDERATION LES 9
// AUTRES ASTRES ( ET DONC 9 FORCES )  -----> IDEM QUE CELLE DES DIFFERENCES FINIES

void RK4_3(double t0,int index,astre* myAstre, astre myAstre_1, astre myAstre_2, astre myAstre_3, astre myAstre_4 ,astre myAstre_5, astre myAstre_6,
                                astre myAstre_7, astre myAstre_8, astre myAstre_9 ,double deltaT){

    double K1,K2,K3,K4,L1,L2,L3,L4;
    double current_Pos_0_X,current_V_0_X, current_Pos_0_Y,current_V_0_Y;
    double Pos_1_X,Pos_2_X,Pos_3_X,Pos_4_X,Pos_5_X,Pos_6_X,Pos_7_X,Pos_8_X,Pos_9_X,Pos_1_Y,Pos_2_Y,Pos_3_Y,Pos_4_Y,Pos_5_Y,Pos_6_Y,Pos_7_Y,Pos_8_Y,Pos_9_Y;
    /// CALCUL DES DISTANCES ENTRE myAstre ET LE RESTE DES ASTRES
    double rayon_1 = sqrt(  pow (( myAstre->position[index-1][0]- myAstre_1.position[index-1][0]), 2)
                          + pow ( (myAstre->position[index-1][1]- myAstre_1.position[index-1][1] ), 2 ) );
    double rayon_2 = sqrt(  pow (( myAstre->position[index-1][0]- myAstre_2.position[index-1][0]), 2)
                          + pow ( (myAstre->position[index-1][1]- myAstre_2.position[index-1][1] ), 2 ) );
    double rayon_3 = sqrt(  pow (( myAstre->position[index-1][0]- myAstre_3.position[index-1][0]), 2)
                          + pow ( (myAstre->position[index-1][1]- myAstre_3.position[index-1][1] ), 2 ) );
    double rayon_4 = sqrt(  pow (( myAstre->position[index-1][0]- myAstre_4.position[index-1][0]), 2)
                          + pow ( (myAstre->position[index-1][1]- myAstre_4.position[index-1][1] ), 2 ) );
    double rayon_5 = sqrt(  pow (( myAstre->position[index-1][0]- myAstre_5.position[index-1][0]), 2)
                          + pow ( (myAstre->position[index-1][1]- myAstre_5.position[index-1][1] ), 2 ) );
    double rayon_6 = sqrt(  pow (( myAstre->position[index-1][0]- myAstre_6.position[index-1][0]), 2)
                          + pow ( (myAstre->position[index-1][1]- myAstre_6.position[index-1][1] ), 2 ) );
    double rayon_7 = sqrt(  pow (( myAstre->position[index-1][0]- myAstre_7.position[index-1][0]), 2)
                          + pow ( (myAstre->position[index-1][1]- myAstre_7.position[index-1][1] ), 2 ) );
    double rayon_8 = sqrt(  pow (( myAstre->position[index-1][0]- myAstre_8.position[index-1][0]), 2)
                          + pow ( (myAstre->position[index-1][1]- myAstre_8.position[index-1][1] ), 2 ) );
    double rayon_9 = sqrt(  pow (( myAstre->position[index-1][0]- myAstre_9.position[index-1][0]), 2)
                          + pow ( (myAstre->position[index-1][1]- myAstre_9.position[index-1][1] ), 2 ) );
    /// EXTRACTION DES MASSES
    double M_1 = myAstre_1.masse;
    double M_2 = myAstre_2.masse;
    double M_3 = myAstre_3.masse;
    double M_4 = myAstre_4.masse;
    double M_5 = myAstre_5.masse;
    double M_6 = myAstre_6.masse;
    double M_7 = myAstre_7.masse;
    double M_8 = myAstre_8.masse;
    double M_9 = myAstre_9.masse;


    /// CALCUL EN X
    current_Pos_0_X  = myAstre->position[index-1][0],current_V_0_X = myAstre->vitesse[index-1][0];
    Pos_1_X = myAstre_1.position[index-1][0];
    Pos_2_X = myAstre_2.position[index-1][0];
    Pos_3_X = myAstre_3.position[index-1][0];
    Pos_4_X = myAstre_4.position[index-1][0];
    Pos_5_X = myAstre_5.position[index-1][0];
    Pos_6_X = myAstre_6.position[index-1][0];
    Pos_7_X = myAstre_7.position[index-1][0];
    Pos_8_X = myAstre_8.position[index-1][0];
    Pos_9_X = myAstre_9.position[index-1][0];


    K1 = deltaT * f2(t0, current_Pos_0_X, current_V_0_X);
    L1 = deltaT * g3(t0, current_Pos_0_X, current_V_0_X ,Pos_1_X,M_1, rayon_1,Pos_2_X,M_2,rayon_2,Pos_3_X, M_3, rayon_3,Pos_4_X,M_4, rayon_4,Pos_5_X,M_5, rayon_5,
                      Pos_6_X,M_6, rayon_6, Pos_7_X, M_7, rayon_7, Pos_8_X, M_8, rayon_8,Pos_9_X, M_9, rayon_9);

    K2 = deltaT * f2(t0+(deltaT/2), current_Pos_0_X+(K1/2), current_V_0_X+(L1/2));
    L2 = deltaT * g3(t0+(deltaT/2), current_Pos_0_X+(K1/2), current_V_0_X+(L1/2),Pos_1_X,M_1, rayon_1,Pos_2_X,M_2,rayon_2,Pos_3_X, M_3, rayon_3,Pos_4_X,M_4,
                      rayon_4,Pos_5_X,M_5, rayon_5,Pos_6_X,M_6, rayon_6, Pos_7_X, M_7, rayon_7, Pos_8_X, M_8, rayon_8,Pos_9_X, M_9, rayon_9);

    K3 = deltaT * f2(t0+(deltaT/2), current_Pos_0_X+(K2/2), current_V_0_X+(L1/2));
    L3 = deltaT * g3(t0+(deltaT/2), current_Pos_0_X+(K2/2), current_V_0_X+(L1/2),Pos_1_X,M_1, rayon_1,Pos_2_X,M_2,rayon_2,Pos_3_X, M_3, rayon_3,Pos_4_X,M_4,
                      rayon_4,Pos_5_X,M_5, rayon_5,Pos_6_X,M_6, rayon_6, Pos_7_X, M_7, rayon_7, Pos_8_X, M_8, rayon_8,Pos_9_X, M_9, rayon_9);

    K4 = deltaT * f2(t0+deltaT, current_Pos_0_X+K3, current_V_0_X+L3 );
    L4 = deltaT * g3(t0+deltaT, current_Pos_0_X+K3, current_V_0_X+L3,Pos_1_X,M_1, rayon_1,Pos_2_X,M_2,rayon_2,Pos_3_X, M_3, rayon_3,Pos_4_X,M_4,
                      rayon_4,Pos_5_X,M_5, rayon_5,Pos_6_X,M_6, rayon_6, Pos_7_X, M_7, rayon_7, Pos_8_X, M_8, rayon_8,Pos_9_X, M_9, rayon_9);

    /// UPDATING LA STRUCTURE EN X
    myAstre->position[index][0] = current_Pos_0_X + (K1+2*K2+2*K3+K4)/6;
    myAstre->vitesse[index][0]  = current_V_0_X + (L1+2*L2+2*L3+L4)/6;

    /// CALCUL EN Y
    current_Pos_0_Y  = myAstre->position[index-1][1],current_V_0_Y = myAstre->vitesse[index-1][1];
    Pos_1_Y = myAstre_1.position[index-1][1];
    Pos_2_Y = myAstre_2.position[index-1][1];
    Pos_3_Y = myAstre_3.position[index-1][1];
    Pos_4_Y = myAstre_4.position[index-1][1];
    Pos_5_Y = myAstre_5.position[index-1][1];
    Pos_6_Y = myAstre_6.position[index-1][1];
    Pos_7_Y = myAstre_7.position[index-1][1];
    Pos_8_Y = myAstre_8.position[index-1][1];
    Pos_9_Y = myAstre_9.position[index-1][1];

    K1 = deltaT * f2(t0, current_Pos_0_Y, current_V_0_Y);
    L1 = deltaT * g3(t0, current_Pos_0_Y, current_V_0_Y ,Pos_1_Y,M_1, rayon_1,Pos_2_Y,M_2,rayon_2,Pos_3_Y, M_3, rayon_3,Pos_4_Y,M_4, rayon_4,Pos_5_Y,M_5, rayon_5,
                      Pos_6_Y,M_6, rayon_6, Pos_7_Y, M_7, rayon_7, Pos_8_Y, M_8, rayon_8,Pos_9_Y, M_9, rayon_9);

    K2 = deltaT * f2(t0+(deltaT/2), current_Pos_0_Y+(K1/2), current_V_0_Y+(L1/2));
    L2 = deltaT * g3(t0+(deltaT/2), current_Pos_0_Y+(K1/2), current_V_0_Y+(L1/2),Pos_1_Y,M_1, rayon_1,Pos_2_Y,M_2,rayon_2,Pos_3_Y, M_3, rayon_3,Pos_4_Y,M_4,
                      rayon_4,Pos_5_Y,M_5, rayon_5,Pos_6_Y,M_6, rayon_6, Pos_7_Y, M_7, rayon_7, Pos_8_Y, M_8, rayon_8,Pos_9_Y, M_9, rayon_9);

    K3 = deltaT * f2(t0+(deltaT/2), current_Pos_0_Y+(K2/2), current_V_0_Y+(L1/2));
    L3 = deltaT * g3(t0+(deltaT/2), current_Pos_0_Y+(K2/2), current_V_0_Y+(L1/2),Pos_1_Y,M_1, rayon_1,Pos_2_Y,M_2,rayon_2,Pos_3_Y, M_3, rayon_3,Pos_4_Y,M_4,
                      rayon_4,Pos_5_Y,M_5, rayon_5,Pos_6_Y,M_6, rayon_6, Pos_7_Y, M_7, rayon_7, Pos_8_Y, M_8, rayon_8,Pos_9_Y, M_9, rayon_9);

    K4 = deltaT * f2(t0+deltaT, current_Pos_0_Y+K3, current_V_0_Y+L3 );
    L4 = deltaT * g3(t0+deltaT, current_Pos_0_Y+K3, current_V_0_Y+L3,Pos_1_Y,M_1, rayon_1,Pos_2_Y,M_2,rayon_2,Pos_3_Y, M_3, rayon_3,Pos_4_Y,M_4,
                      rayon_4,Pos_5_Y,M_5, rayon_5,Pos_6_Y,M_6, rayon_6, Pos_7_Y, M_7, rayon_7, Pos_8_Y, M_8, rayon_8,Pos_9_Y, M_9, rayon_9);
    /// UPDATING LA STRUCTURE EN Y
    myAstre->position[index][1] = current_Pos_0_Y + (K1+2*K2+2*K3+K4)/6;
    myAstre->vitesse[index][1]  = current_V_0_Y + (L1+2*L2+2*L3+L4)/6;


}

// ON APPELLE LA FCTN DiffFiniesSYS 9 FOIS POUR LES 9 ASTRES EN METTANT L'ADRESSE DE L'ASTRE DONT ON VEUT RECUPERER
                                        // LA POSITION EN GARDANT UN ASTRE TJRS FIXE ( QUI EST LE SOLEIL )

void rungeKutta4_nineForces(astre myAstre, astre myAstre_1, astre myAstre_2, astre myAstre_3, astre myAstre_4 ,astre myAstre_5,
                            astre myAstre_6, astre myAstre_7, astre myAstre_8, astre myAstre_9,double deltaT, double simuT){
    double t0 = 0.;
    int N = ceil(simuT/deltaT);
    int index;
    for (index=1; index< N; index++){
    // EQUATION DU MOUVEMENT DE L'ASTRE N°1
    RK4_3(t0,index,&myAstre_1,myAstre,myAstre_2,myAstre_3,myAstre_4 ,myAstre_5,myAstre_6,myAstre_7,myAstre_8,myAstre_9,deltaT );
    // EQUATION DU MOUVEMENT DE L'ASTRE N°2
    RK4_3(t0,index,&myAstre_2,myAstre,myAstre_1,myAstre_3,myAstre_4 ,myAstre_5,myAstre_6,myAstre_7,myAstre_8,myAstre_9 ,deltaT);
    // EQUATION DU MOUVEMENT DE L'ASTRE N°3
    RK4_3(t0,index,&myAstre_3,myAstre,myAstre_1,myAstre_2,myAstre_4 ,myAstre_5,myAstre_6,myAstre_7,myAstre_8,myAstre_9 ,deltaT);
    // EQUATION DU MOUVEMENT DE L'ASTRE N°4
    RK4_3(t0,index,&myAstre_4,myAstre,myAstre_1,myAstre_2,myAstre_3 ,myAstre_5,myAstre_6,myAstre_7,myAstre_8,myAstre_9 ,deltaT);
    // EQUATION DU MOUVEMENT DE L'ASTRE N°5
    RK4_3(t0,index,&myAstre_5,myAstre,myAstre_1,myAstre_2,myAstre_3 ,myAstre_4,myAstre_6,myAstre_7,myAstre_8,myAstre_9 ,deltaT);
    // EQUATION DU MOUVEMENT DE L'ASTRE N°6
    RK4_3(t0,index,&myAstre_6,myAstre,myAstre_1,myAstre_2,myAstre_3 ,myAstre_4,myAstre_5,myAstre_7,myAstre_8,myAstre_9 ,deltaT);
    // EQUATION DU MOUVEMENT DE L'ASTRE N°7
    RK4_3(t0,index,&myAstre_7,myAstre,myAstre_1,myAstre_2,myAstre_3 ,myAstre_4,myAstre_5,myAstre_6,myAstre_8,myAstre_9 ,deltaT);
    // EQUATION DU MOUVEMENT DE L'ASTRE N°8
    RK4_3(t0,index,&myAstre_8,myAstre,myAstre_1,myAstre_2,myAstre_3 ,myAstre_4,myAstre_5,myAstre_6,myAstre_7,myAstre_9 ,deltaT);
    // EQUATION DU MOUVEMENT DE L'ASTRE N°9
    RK4_3(t0,index,&myAstre_9,myAstre,myAstre_1,myAstre_2,myAstre_3 ,myAstre_4,myAstre_5,myAstre_6,myAstre_7,myAstre_8 ,deltaT);
    }

}


