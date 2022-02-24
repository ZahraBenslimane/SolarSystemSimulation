#include "SysSolaire.h"
#include "FilesManager.h"
#include "OrbitsCalculator.h"



  /**********************************   ETAPE 01 : SYSTEME TERRE-LUNE SIMPLIFIE   ********************************/

                                        /********** METHODE D'EULER ********/


// CETTE FONCTION CALCULE LES POSITIONS D'UN SEUL ASTRE QUI BOUGE PAR RAPPORT A UN AUTRE QUI EST FIXE
    double** euler(astre* astre_a,astre astre_fixe, double dt, int *n, double Tsimu){
    int i;
    *n=ceil(Tsimu/dt); // Nombre de points
    double *r=calloc(*n,sizeof(double)); // Allocation dynamique
    double masseFixe = astre_fixe.masse; // Extraction de la masse de l'astre

    for(i=0; i<*n-1 ; i++)
    {

        /// RAYON REPRESENTANT LA DISTANCE ENTRE 2 ASTRES
        r[i] = sqrt(  pow (( astre_a->position[i][0]- astre_fixe.position[0][0]), 2)
                          + pow ( (astre_a->position[i][1]- astre_fixe.position[0][1] ), 2 ) );

        /// VITESSE DE L'ASTRE_A EN X
        astre_a->vitesse[i+1][0]=astre_a->vitesse[i][0]-(dt*masseFixe*G*(astre_a->position[i][0]))/pow(r[i],3);
        /// VITESSE DE L'ASTRE_A EN Y
        astre_a->vitesse[i+1][1]=astre_a->vitesse[i][1]-(dt*masseFixe*G*(astre_a->position[i][1]))/pow(r[i],3);
        /// POSITIONS DE L'ASTRE_A EN X
        astre_a->position[i+1][0]=astre_a->position[i][0]+dt*(astre_a->vitesse[i][0]);
        /// POSITIONS DE L'ASTRE_A EN Y
        astre_a->position[i+1][1]=astre_a->position[i][1]+dt*(astre_a->vitesse[i][1]);
    }

    return astre_a->position;
}

                                    /********** METHODE DES DIFFERENCES FINIES ********/


// CETTE FONCTION CALCULE LES POSITIONS D'UN SEUL ASTRE QUI BOUGE PAR RAPPORT A UN AUTRE QUI EST FIXE
void DiffFinies ( astre* astre_a,astre astre_fixe, int Tsimu, double deltaT, int *n)
{
    int i;
    *n=ceil(Tsimu/deltaT);

    double *r=calloc(*n,sizeof(double)); // Allocation dynamique
    double masseFixe = astre_fixe.masse; // Extraction de la masse de l'astre

    /// RECUPERATION DE LA PREMIERE POSITION ( [1] ) EN X ET Y POUR L'ASTRE_A, EN UTILISANT EULER
    double **pos=createMat(*n,2);
    pos=euler(astre_a,astre_fixe,deltaT,n,Tsimu);


    for(i=1; i<*n-1; i++)
    {
        /// RAYON REPRESENTANT LA DISTANCE ENTRE 2 ASTRES
        r[i]=sqrt(astre_a->position[i][0]*astre_a->position[i][0]+astre_a->position[i][1]*astre_a->position[i][1]);
        /// POSITIONS DE L'ASTRE_A EN X
        astre_a->position[i+1][0]=(2-((G*masseFixe*deltaT*deltaT)/(pow(r[i],3))))*astre_a->position[i][0]-astre_a->position[i-1][0];
        /// POSITIONS DE L'ASTRE_A Y
        astre_a->position[i+1][1]=(2-((G*masseFixe*deltaT*deltaT)/(pow(r[i],3))))*astre_a->position[i][1]-astre_a->position[i-1][1];


    }


}
                                           /**************   RK2   **************/

// fonction à pour but de  calculer le derivée de la position = à la vitesse
double f(double temps,double position ,double vitesse){
    return vitesse;
}
// fonction à pour but de calcluer le derivée de la vitesse = ( -G*MT*position )/((rayon_t)^3)
double g(double temps,double position,double vitesse, double rayon_t,double MasseAstreFixe){
    return ( ( -MasseAstreFixe*G*position )/(pow(rayon_t,3)) );
}
void RK2(double t0,int index,astre* myAstre,astre myAstreFixe, double deltaT ){ // dans cette fonction nous avons calculer les coefficient K et L à partir des résultat théorique
    double K1,K2,L1,L2;
    double MasseAstreFixe = myAstreFixe.masse; //calcule de la masse
    double current_Posx,current_Posy,V0x,V0y;
    // calculer le rayon à partir de les prochains valeurs de la position de x et y
    double rayon_t = sqrt(  pow (( myAstre->position[index-1][0]- myAstreFixe.position[0][0]), 2)
                          + pow ( (myAstre->position[index-1][1]- myAstreFixe.position[0][1] ), 2 ) );
/* calcule position en x et vitesse*/
// stocker les valeurs précedents  dans la matrice
    V0x = myAstre->vitesse[index-1][0];
   current_Posx = myAstre->position[index-1][0];
   // calcule les coefficients pour position x et vitesse en x
    K1 =  f(t0, current_Posx, V0x);
    L1 =  g(t0, current_Posx, V0x, rayon_t, MasseAstreFixe);

    K2 =  f(t0+deltaT, current_Posx+(K1*deltaT), V0x+(L1*deltaT));
    L2 =  g(t0+deltaT, current_Posx+(K1*deltaT), V0x+(L1*deltaT), rayon_t, MasseAstreFixe);
    // calcule  les prochains points x(t+∆t) ,vx(t+∆t) incrémentation
     myAstre->position[index][0] = current_Posx +deltaT*(K1+K2)/2;
      myAstre->vitesse[index][0]  = V0x+deltaT*(L1+L2)/2;
/* calcule position en y et vitesse*/
// stocker les valeurs précedents  dans la matrice
      V0y = myAstre->vitesse[index-1][1];
   current_Posy = myAstre->position[index-1][1];
  // calcule les coefficients pour position y et vitesse en y
    K1 =  f(t0, current_Posy, V0y);
    L1 =  g(t0, current_Posy, V0y, rayon_t, MasseAstreFixe);

    K2 =  f(t0+deltaT, current_Posy+(K1*deltaT), V0y+(L1*deltaT));
    L2 =  g(t0+deltaT, current_Posy+(K1*deltaT), V0y+(L1*deltaT), rayon_t, MasseAstreFixe);
    // calcule  les prochains points x(t+∆t) ,vx(t+∆t) incrémentation
      myAstre->position[index][1] = current_Posy +deltaT*(K1+K2)/2;
      myAstre->vitesse[index][1]  = V0y+deltaT*(L1+L2)/2;
}

void rungeKutta2(astre myAstre,astre myAstreFixe, double deltaT, double simuT,int* N){
    *N = ceil(simuT/deltaT);
    double t0=0.;
    int index;
    for (index=1; index <(*N); index++){ // calculer les prochains points x(t+∆t) ,vx(t+∆t), y(t+∆t) ,vy(t+∆t)

        RK2(t0,index,&myAstre,myAstreFixe,deltaT);
    }
}



                                           /**************   RK4    **************/



void RK4(double t0,int index,astre* myAstre,astre myAstreFixe, double deltaT ){
    double K1,K2,K3,K4,L1,L2,L3,L4;
    double MasseAstreFixe = myAstreFixe.masse;
    double current_PosX,current_PosY,V0X,V0Y;
    double rayon_t = sqrt(  pow (( myAstre->position[index-1][0]- myAstreFixe.position[0][0]), 2)
                          + pow ( (myAstre->position[index-1][1]- myAstreFixe.position[0][1] ), 2 ) );

    // X
     V0X = myAstre->vitesse[index-1][0];
     current_PosX = myAstre->position[index-1][0];

    K1 = deltaT * f(t0, current_PosX, V0X);
    L1 = deltaT * g(t0, current_PosX, V0X, rayon_t, MasseAstreFixe);

    K2 = deltaT * f(t0+(deltaT/2), current_PosX+(K1/2), V0X+(L1/2));
    L2 = deltaT * g(t0+(deltaT/2), current_PosX+(K1/2), V0X+(L1/2), rayon_t, MasseAstreFixe);

    K3 = deltaT * f(t0+(deltaT/2), current_PosX+(K2/2), V0X+(L1/2));
    L3 = deltaT * g(t0+(deltaT/2), current_PosX+(K2/2), V0X+(L1/2), rayon_t, MasseAstreFixe);

    K4 = deltaT * f(t0+deltaT, current_PosX+K3, V0X+L3 );
    L4 = deltaT * g(t0+deltaT, current_PosX+K3, V0X+L3, rayon_t, MasseAstreFixe);

     myAstre->vitesse[index][0]  = V0X + (L1+2*L2+2*L3+L4)/6;
     myAstre->position[index][0] = current_PosX + (K1+2*K2+2*K3+K4)/6;

     // Y
     V0Y = myAstre->vitesse[index-1][1];
     current_PosY = myAstre->position[index-1][1];
    K1 = deltaT * f(t0, current_PosY, V0Y);
    L1 = deltaT * g(t0, current_PosY, V0Y, rayon_t, MasseAstreFixe);

    K2 = deltaT * f(t0+(deltaT/2), current_PosY+(K1/2), V0Y+(L1/2));
    L2 = deltaT * g(t0+(deltaT/2), current_PosY+(K1/2), V0Y+(L1/2), rayon_t, MasseAstreFixe);

    K3 = deltaT * f(t0+(deltaT/2), current_PosY+(K2/2), V0Y+(L1/2));
    L3 = deltaT * g(t0+(deltaT/2), current_PosY+(K2/2), V0Y+(L1/2), rayon_t, MasseAstreFixe);

    K4 = deltaT * f(t0+deltaT, current_PosY+K3, V0Y+L3 );
    L4 = deltaT * g(t0+deltaT, current_PosY+K3, V0Y+L3, rayon_t, MasseAstreFixe);

     myAstre->vitesse[index][1]  = V0Y + (L1+2*L2+2*L3+L4)/6;
     myAstre->position[index][1] = current_PosY + (K1+2*K2+2*K3+K4)/6;


}

//
void rungeKutta4(astre myAstre,astre myAstreFixe, double deltaT, double simuT,int* N){
    *N = ceil(simuT/deltaT);
    double t0=0.;
    int index;
    for (index=1; index <(*N); index++){
        // CALCUL DU PROCHAIN POINT X(t+1) + VITESSE EN CE POINT && Y(t+1) VITESSE EN CE POINT
        RK4(t0,index,&myAstre,myAstreFixe,deltaT);
    }
}


      /*************************   ETAPE 02 : SYSTEME TERRE-LUNE    **************************************************/


/// METHODE DES DIFFERENCES FINIES
// CETTE FONCTION CALCULE LES POSITIONS DE 2 ASTRES QUI BOUGENT EN X ET Y, EN PRENANT EN CONSIDERATION LEUR INTERRACTION
void DiffFinies2 ( astre* astre_a,astre* astre_b, int Tsimu, double deltaT, int *n)
{
    int i;
    *n=ceil(Tsimu/deltaT);
    double *r=calloc(*n,sizeof(double)); // Allocation dynamique
    /// RECUPERATION DES MASSES DES ASTRES
    double masseB = astre_b->masse;
    double masseA = astre_a->masse;

    /// RECUPERATION DE LA PREMIERE POSITION EN X ET Y POUR L'ASTRE A et B, EN UTILISANT RK4
    astre astre_a_prime = *astre_a; // Declaration d'un astre intermediaire qui nous permettra de faciliter les calculs
    astre astre_b_prime = *astre_b; // Declaration d'un astre intermediaire qui nous permettra de faciliter les calculs
    rungeKutta4_doubleForces(astre_a_prime,*astre_b,deltaT,Tsimu,n);// appel à la fctn RK4 qui calculera la position 1


    for(i=1; i<*n-1; i++)
    {

        /// RAYON REPRESENTANT LA DISTANCE ENTRE 2 ASTRES
        r[i]=sqrt(((astre_a_prime.position[i][0]-astre_b->position[i][0])*(astre_a_prime.position[i][0]-astre_b->position[i][0]))+((astre_a_prime.position[i][1]-astre_b->position[i][1])*(astre_a_prime.position[i][1]-astre_b->position[i][1])));

        /* POSITION DE LA LUNE EN CONSIDERANT LA TERRE FIXE */

        /// POSITIONS DE L'ASTRE EN X
        astre_a_prime.position[i+1][0]=(2-((G*masseB*deltaT*deltaT)/(pow(r[i],3))))*astre_a_prime.position[i][0]-astre_a_prime.position[i-1][0]+(G*masseB*deltaT*deltaT)/(pow(r[i],3))*astre_b_prime.position[i][0];
        /// POSITIONS DE L'ASTRE EN Y
        astre_a_prime.position[i+1][1]=(2-((G*masseB*deltaT*deltaT)/(pow(r[i],3))))*astre_a_prime.position[i][1]-astre_a_prime.position[i-1][1]+(G*masseB*deltaT*deltaT)/(pow(r[i],3))*astre_b_prime.position[i][1];

        /* POSITION DE LA TERRE EN CONSIDERANT LA LUNE FIXE  */

        /// POSITIONS DE L'ASTRE EN X
        astre_b->position[i+1][0]=(2-((G*masseA*deltaT*deltaT)/(pow(r[i],3))))*astre_b->position[i][0]-astre_b->position[i-1][0]+(G*masseA*deltaT*deltaT)/(pow(r[i],3))*astre_a->position[i][0];
        /// POSITIONS DE L'ASTRE EN Y
        astre_b->position[i+1][1]=(2-((G*masseA*deltaT*deltaT)/(pow(r[i],3))))*astre_b->position[i][1]-astre_b->position[i-1][1]+(G*masseA*deltaT*deltaT)/(pow(r[i],3))*astre_a->position[i][1];

    }


}


/*******************************   ETAPE 03 : SYSTEME SOLAIRE SIMPLIFIE    **************************************************/

// DANS CETTE ETAPE NOUS AVONS MODELISE DANS UN PLAN 2D LA ROTATION DES 8 PLANETES ( MERCURE ,MARS, VENUS , URANUS, NEPTUNE ,
// JUPITER, SATURNE, TERRE ) EN SUPPOSANT LE SOLEIL FIXE ET AUCUNE INTERRACTION ENTRE LES PLANETES, CE QUI A ETE RESOLUE PAR LA
// MÊME METHODE QU'A L'ETAPE 01



/*******************************   ETAPE 04 : SYSTEME SOLAIRE COMPLET    **************************************************/


/// METHODE DES DIFFERENCES FINIES 9 FORCES
// DANS CETTE FONCTION NOUS CONSIDERONS L'INTERRACTION ENTRE TOUS LES ASTRES Y COMPRIS LA LUNE EN GARDANT LE SOLEIL FIXE
// NOUS Y CALCULONS LE POINT PROCHAIN D'UN SEUL ASTRE DEFINI EN POINTEUR EN CONSIDERANT TOUS LES AUTRES ASTRES FIXES
// NOUS AVONS COMMENCE PAR DEFINIR 9 RAYONS POUR LES 9 PLANETES ( SOLEIL EXCLU CAR IL RESTE FIXE ), DANS LESQUELS NOUS
// CALCULONS LA DISTANCE DE L'ASTRE EN MOUVEMENT PAR RAPPORT AUX 9 AUTRES ASTRES FIXES
// PUIS NOUS AVONS ETABLIS LES EQUATIONS DES POSITIONS EN X ET Y DE L'ASTRE EN MOUVEMENT EN PRENANT EN CONSIDERATION LES 9
// AUTRES ASTRES ( ET DONC 9 FORCES )
void DiffFiniesSYS( astre astre_b,astre* astre_a,astre astre_c,astre astre_d,astre astre_e,astre astre_f,
                   astre astre_g,astre astre_h,astre astre_i,astre astre_j, int Tsimu, double deltaT, int i)

{
    int n=ceil(Tsimu/deltaT); // NOMBRE DE POINTS

    //ALLOCATION DYNAMIQUE DES RAYON DES DIFFERENTES PLANETES
    double *r_a=calloc(n,sizeof(double));
    double *r_c=calloc(n,sizeof(double));
    double *r_d=calloc(n,sizeof(double));
    double *r_e=calloc(n,sizeof(double));
    double *r_f=calloc(n,sizeof(double));
    double *r_g=calloc(n,sizeof(double));
    double *r_h=calloc(n,sizeof(double));
    double *r_i=calloc(n,sizeof(double));
    double *r_j=calloc(n,sizeof(double));

    //EXTRACTION DES MASSES DES 10 ASTRES
    double masseA = astre_a->masse;
    double masseB = astre_b.masse;
    double masseC = astre_c.masse;
    double masseD = astre_d.masse;
    double masseE = astre_e.masse;
    double masseF = astre_f.masse;
    double masseG = astre_g.masse;
    double masseH = astre_h.masse;
    double masseI = astre_i.masse;
    double masseJ = astre_j.masse;

    /*RECUPERATION DE LA PREMIERE POSITION ( [1] ) DE CHAQUE PLANETE EN UTILISANT RK4*/
    RK4_3(0.,i,astre_a,astre_b,astre_c,astre_d,astre_e,astre_f,astre_g,astre_h,astre_i,astre_j,deltaT);


        /* EQUATIONS DES RAYONS ( DISTANCES ) DES 9 PLANETES ( astre_a bouge les autres sont fixes )*/
        r_a[i] = sqrt(  pow (( astre_a->position[i][0]- astre_b.position[i][0]), 2)
                      + pow ( (astre_a->position[i][1]- astre_b.position[i][1]), 2 ) );
        r_c[i] = sqrt(  pow (( astre_a->position[i][0]- astre_c.position[i][0]), 2)
                      + pow ( (astre_a->position[i][1]- astre_c.position[i][1]), 2 ) );
        r_d[i] = sqrt(  pow (( astre_a->position[i][0]- astre_d.position[i][0]), 2)
                      + pow ( (astre_a->position[i][1]- astre_d.position[i][1]), 2 ) );
        r_e[i] = sqrt(  pow (( astre_a->position[i][0]- astre_e.position[i][0]), 2)
                      + pow ( (astre_a->position[i][1]- astre_e.position[i][1]), 2 ) );
        r_f[i] = sqrt(  pow (( astre_a->position[i][0]- astre_f.position[i][0]), 2)
                      + pow ( (astre_a->position[i][1]- astre_f.position[i][1]), 2 ) );
        r_g[i] = sqrt(  pow (( astre_a->position[i][0]- astre_g.position[i][0]), 2)
                      + pow ( (astre_a->position[i][1]- astre_g.position[i][1]), 2 ) );
        r_h[i] = sqrt(  pow (( astre_a->position[i][0]- astre_h.position[i][0]), 2)
                      + pow ( (astre_a->position[i][1]- astre_h.position[i][1]), 2 ) );
        r_i[i] = sqrt(  pow (( astre_a->position[i][0]- astre_i.position[i][0]), 2)
                      + pow ( (astre_a->position[i][1]- astre_i.position[i][1]), 2 ) );
        r_j[i] = sqrt(  pow (( astre_a->position[i][0]- astre_j.position[i][0]), 2)
                      + pow ( (astre_a->position[i][1]- astre_j.position[i][1]), 2 ) );


        /// ASTRE A
        // POSITIONS DE L'ASTRE EN X
        astre_a->position[i+1][0]=( -G*deltaT*deltaT*masseB*(astre_a->position[i][0]-astre_b.position[i][0])/pow(r_a[i],3)   )
                                  -( G*deltaT*deltaT*masseC*(astre_a->position[i][0]-astre_c.position[i][0])/pow(r_c[i],3)  )
                                  -( G*deltaT*deltaT*masseD*(astre_a->position[i][0]-astre_d.position[i][0])/pow(r_d[i],3)  )
                                  -( G*deltaT*deltaT*masseE*(astre_a->position[i][0]-astre_e.position[i][0])/pow(r_e[i],3)  )
                                  -( G*deltaT*deltaT*masseF*(astre_a->position[i][0]-astre_f.position[i][0])/pow(r_f[i],3)  )
                                  -( G*deltaT*deltaT*masseG*(astre_a->position[i][0]-astre_g.position[i][0])/pow(r_g[i],3) )
                                  -( G*deltaT*deltaT*masseH*(astre_a->position[i][0]-astre_h.position[i][0])/pow(r_h[i],3) )
                                  -( G*deltaT*deltaT*masseI*(astre_a->position[i][0]-astre_i.position[i][0])/pow(r_i[i],3) )
                                  -( G*deltaT*deltaT*masseJ*(astre_a->position[i][0]-astre_j.position[i][0])/pow(r_j[i],3) )
                                  +2*astre_a->position[i][0]                        -astre_a->position[i-1][0];

        // POSITIONS DE L'ASTRE EN Y
        astre_a->position[i+1][1]=( -G*deltaT*deltaT*masseB*(astre_a->position[i][1]-astre_b.position[i][1])/pow(r_a[i],3)   )
                                  -( G*deltaT*deltaT*masseC*(astre_a->position[i][1]-astre_c.position[i][1])/pow(r_c[i],3)  )
                                  -( G*deltaT*deltaT*masseD*(astre_a->position[i][1]-astre_d.position[i][1])/pow(r_d[i],3)  )
                                  -( G*deltaT*deltaT*masseE*(astre_a->position[i][1]-astre_e.position[i][1])/pow(r_e[i],3)  )
                                  -( G*deltaT*deltaT*masseF*(astre_a->position[i][1]-astre_f.position[i][1])/pow(r_f[i],3)  )
                                  -( G*deltaT*deltaT*masseG*(astre_a->position[i][1]-astre_g.position[i][1])/pow(r_g[i],3) )
                                  -( G*deltaT*deltaT*masseH*(astre_a->position[i][1]-astre_h.position[i][1])/pow(r_h[i],3) )
                                  -( G*deltaT*deltaT*masseI*(astre_a->position[i][1]-astre_i.position[i][1])/pow(r_i[i],3) )
                                  -( G*deltaT*deltaT*masseJ*(astre_a->position[i][1]-astre_j.position[i][1])/pow(r_j[i],3) )
                                   +2*astre_a->position[i][1]                       -astre_a->position[i-1][1];

}

/// METHODE DES DIFFERENCES FINIES POUR LES 9 ASTRES QUI BOUGENT EN MÊME TEMP ( SOLEIL FIXE MODELISE PAR astre_b )
// ON APPELLE LA FCTN DiffFiniesSYS 9 FOIS POUR LES 9 ASTRES EN METTANT L'ADRESSE DE L'ASTRE DONT ON VEUT RECUPERER
                                        // LA POSITION EN GARDANT UN ASTRE TJRS FIXE ( QUI EST LE SOLEIL )

    void DiffFinies9Forces( astre astre_b,astre astre_a,astre astre_c,astre astre_d,astre astre_e,astre astre_f,
                   astre astre_g,astre astre_h,astre astre_i,astre astre_j, int Tsimu, double deltaT)
{
       int i;
       int n=ceil(Tsimu/deltaT); // NOMBRE DE POINTS


        for (i=1;i<n-1;i++)
        {
        // EQUATION DU MOUVEMENT DE L'ASTRE N°1
        DiffFiniesSYS(astre_b,&astre_a,astre_c,astre_d,astre_e,astre_f,astre_g,astre_h,astre_i,astre_j,Tsimu,deltaT,i);
        // EQUATION DU MOUVEMENT DE L'ASTRE N°2
        DiffFiniesSYS(astre_b,&astre_c,astre_a,astre_d,astre_e,astre_f,astre_g,astre_h,astre_i,astre_j,Tsimu,deltaT,i);
        // EQUATION DU MOUVEMENT DE L'ASTRE N°3
        DiffFiniesSYS(astre_b,&astre_d,astre_c,astre_a,astre_e,astre_f,astre_g,astre_h,astre_i,astre_j,Tsimu,deltaT,i);
        // EQUATION DU MOUVEMENT DE L'ASTRE N°4
        DiffFiniesSYS(astre_b,&astre_e,astre_c,astre_d,astre_a,astre_f,astre_g,astre_h,astre_i,astre_j,Tsimu,deltaT,i);
        // EQUATION DU MOUVEMENT DE L'ASTRE N°5
        DiffFiniesSYS(astre_b,&astre_f,astre_c,astre_d,astre_e,astre_a,astre_g,astre_h,astre_i,astre_j,Tsimu,deltaT,i);
        // EQUATION DU MOUVEMENT DE L'ASTRE N°6
        DiffFiniesSYS(astre_b,&astre_g,astre_c,astre_d,astre_e,astre_f,astre_a,astre_h,astre_i,astre_j,Tsimu,deltaT,i);
        // EQUATION DU MOUVEMENT DE L'ASTRE N°7
        DiffFiniesSYS(astre_b,&astre_h,astre_c,astre_d,astre_e,astre_f,astre_g,astre_a,astre_i,astre_j,Tsimu,deltaT,i);
        // EQUATION DU MOUVEMENT DE L'ASTRE N°8
        DiffFiniesSYS(astre_b,&astre_i,astre_c,astre_d,astre_e,astre_f,astre_g,astre_h,astre_a,astre_j,Tsimu,deltaT,i);
        // EQUATION DU MOUVEMENT DE L'ASTRE N°9
        DiffFiniesSYS(astre_b,&astre_j,astre_c,astre_d,astre_e,astre_f,astre_g,astre_h,astre_i,astre_a,Tsimu,deltaT,i);

        }
}




