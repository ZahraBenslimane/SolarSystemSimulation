/** Réalisé par
- Dahmani Yasmine
- Belhamri Lina
- Ben Guirat Siwar
- Benslimane Zahra
*/

#include "SysSolaire.h"
#include "FilesManager.h"
#include "OrbitsCalculator.h"

int main(){

    int select;
    printf("01 : Systeme Terre-Lune simplife.\n02 : Systeme Terre-Lune.\n03 : Systeme Solaire simplifie.\n04 : Systeme Solaire Complet.\n");
    printf("Veuillez selectionner une simulation  = ");
    if(scanf("%d",&select)!= 1){
        printf("Veuillez reesayer");
        exit(EXIT_FAILURE);
    }
        /***********   ETAPE 01 : SYSTEME TERRE-LUNE SIMPLIFIE   **************/
    if (select ==01){

      double deltaT= 12*60*60.;      //pas de simulation
      double Tsimu= 60*24*60*60.;
      int N = ceil(Tsimu/deltaT);

        // Création du système terre-lune
        astre Lune  = CreerAstre(deltaT,Tsimu,"Lune",ML,N,384400e+03,0,0,1023.162);
        astre Terre   = CreerAstre(deltaT,Tsimu,"Terre",MT,N,0., 0.,0.,0.);

        // TOUTES LES METHODES
        // EULER
            double **LuneMat = euler(&Lune,Terre,deltaT,&N,Tsimu);
            writeMat(TACHE01_LUNE_EULER,Lune.position,N,2);
        // DIFFERENCES FINIES
            DiffFinies(&Lune,Terre,Tsimu,deltaT,&N);
            writeMat(TACHE01_LUNE_DIF,Lune.position,N,2);
        // RUNGE KUTTA 2
            rungeKutta2(Lune,Terre,deltaT,Tsimu,&N);
            writeMat(TACHE01_LUNE_RK2,Lune.position,N,2);
        // RUNGE KUTTA 4
            rungeKutta4(Lune,Terre,deltaT,Tsimu,&N);
            writeMat(TACHE01_LUNE_RK4,Lune.position,N,2);

        freeMat(&Lune.position,N);freeMat(&Lune.vitesse,N);
    }
        /***********   ETAPE 02 : SYSTEME TERRE-LUNE   *****************/

   if (select == 02){

      int selectMethode;
        double deltaT= 1*60*60.;      //pas de simulation
        double Tsimu= 60*24*60*60.;

      printf("\n01 : Methode Differences finies .\n02 : RK4.\n03 : Les deux methodes simultanement\n");
      printf("Veuillez selectionner une simulation  = ");

        if(scanf("%d",&selectMethode)!= 1){
        printf("Veuillez selectionnez une simulation valide");
        exit(EXIT_FAILURE);
        }

        // Le nombre d'itérations
        int N = ceil(Tsimu/deltaT);

        astre Lune     = CreerAstre(deltaT,Tsimu,"Lune",ML,N,384400e+03,0,0,1023.162);
        astre Terre   = CreerAstre(deltaT,Tsimu,"Terre",MT,N,0., 0.,0.,0.);
        // Différences finies
        if(selectMethode == 01){
         DiffFinies2(&Lune,&Terre,Tsimu,deltaT,&N);
        // Ecriture des résulatats dans les fichiers correspandants
        writeMat(TACHE02_LUNE,Lune.position,N,2);
        writeMat(TACHE02_TERRE,Terre.position,N,2);
        }
        // Runge-Kutta 4
        if(selectMethode == 02){
        rungeKutta4_doubleForces(Lune,Terre,deltaT,Tsimu,&N);
        // Ecriture des résulatats dans les fichiers correspandants
        writeMat(XY_LUNE,Lune.position,N,2);
        writeMat(XY_TERRE,Terre.position,N,2);
        }

                // Runge-Kutta 4
        if(selectMethode == 03){

        rungeKutta4_doubleForces(Lune,Terre,deltaT,Tsimu,&N);
        writeMat(XY_LUNE,Lune.position,N,2);
        writeMat(XY_TERRE,Terre.position,N,2);

        DiffFinies2(&Lune,&Terre,Tsimu,deltaT,&N);
        writeMat(TACHE02_LUNE,Lune.position,N,2);
        writeMat(TACHE02_TERRE,Terre.position,N,2);

        }



        // Désalouer la mémoire
        freeMat(&Lune.position,N);freeMat(&Lune.vitesse,N);
        freeMat(&Terre.position,N);freeMat(&Terre.vitesse,N);

   }
        /***********   ETAPE 03 : SYSTEME SOLAIRE SIMPLIFIE   **************/

    if(select ==03){

      int selectMethode;
     double deltaT= 24*60*60.;      //pas de simulation
     double Tsimu= 2*365.25*24*60*60.;
     int N = ceil(Tsimu/deltaT);

      printf("\n01 : Methode Differences finies .\n02 : Runge-Kutta 4.\n");
      printf("Veuillez selectionner une simulation  = ");

        if(scanf("%d",&selectMethode)!= 1){
        printf("Veuillez selectionnez une simulation valide");
        exit(EXIT_FAILURE);
        }

     /// Création du système solaire
     astre Soleil  = CreerAstre(deltaT,Tsimu,"Soleil",MS,N,0.,0.,0.,0.);
     astre Mercure = CreerAstre(deltaT,Tsimu,"Mercure",MMer,N,57.91e+09, 0.,0.,47872.39);
     astre Venus   = CreerAstre(deltaT,Tsimu,"Venus",MV,N,108.2e+09, 0.,0.,35017.92);
     astre Terre   = CreerAstre(deltaT,Tsimu,"Terre",MT,N,149.6e+09, 0.,0.,29785.68);
     astre Mars    = CreerAstre(deltaT,Tsimu,"Mars",MMar,N,227.9e+09, 0.,0.,24751.87);
     astre Jupiter = CreerAstre(deltaT,Tsimu,"Jupiter",MJ,N,763.5e+09,0.,0.,12667.87);
     astre Saturne = CreerAstre(deltaT,Tsimu,"Saturne",MSat,N,0.,1.434e+12,-9845.257,0.);
     astre Uranus  = CreerAstre(deltaT,Tsimu,"Uranus",MU,N,-2.871e+12,0.,0.,-6805.026);
     astre Neptune = CreerAstre(deltaT,Tsimu,"Neptune",MN,N,-4.495e+12,0.,0.,-5424.025);

     if (selectMethode == 01){
     // Appel à la fonction de calcule + écriture dans les fichiers correspandant
     DiffFinies(&Mercure,Soleil,Tsimu,deltaT,&N);     writeMat(TACHE03_MERCURE,Mercure.position,N,2);
     DiffFinies(&Venus,Soleil,Tsimu,deltaT,&N);       writeMat(TACHE03_VENUS,Venus.position,N,2);
     DiffFinies(&Terre,Soleil,Tsimu,deltaT,&N);       writeMat(TACHE03_TERRE,Terre.position,N,2);
     DiffFinies(&Mars,Soleil,Tsimu,deltaT,&N);        writeMat(TACHE03_MARS,Mars.position,N,2);
     DiffFinies(&Jupiter,Soleil,Tsimu,deltaT,&N);     writeMat(TACHE03_JUPITER,Jupiter.position,N,2);
     DiffFinies(&Saturne,Soleil,Tsimu,deltaT,&N);     writeMat(TACHE03_SATURNE,Saturne.position,N,2);
     DiffFinies(&Uranus,Soleil,Tsimu,deltaT,&N);      writeMat(TACHE03_URANUS,Uranus.position,N,2);
     DiffFinies(&Neptune,Soleil,Tsimu,deltaT,&N);     writeMat(TACHE03_NEPTUNE,Neptune.position,N,2);
     }

     if (selectMethode == 2){
     // Appel à la fonction de calcule + écriture dans les fichiers correspandant
     rungeKutta4(Mercure,Soleil,deltaT,Tsimu,&N);   writeMat(SIMPLE_MERCURE,Mercure.position,N,2);
     rungeKutta4(Venus,Soleil,deltaT,Tsimu,&N);     writeMat(SIMPLE_VENUS,Venus.position,N,2);
     rungeKutta4(Terre,Soleil,deltaT,Tsimu,&N);     writeMat(SIMPLE_TERRE,Terre.position,N,2);
     rungeKutta4(Mars,Soleil,deltaT,Tsimu,&N);      writeMat(SIMPLE_MARS,Mars.position,N,2);
     rungeKutta4(Jupiter,Soleil,deltaT,Tsimu,&N);   writeMat(SIMPLE_JUPITER,Jupiter.position,N,2);
     rungeKutta4(Saturne,Soleil,deltaT,Tsimu,&N);   writeMat(SIMPLE_SATURNE,Saturne.position,N,2);
     rungeKutta4(Uranus,Soleil,deltaT,Tsimu,&N);    writeMat(SIMPLE_URANUS,Uranus.position,N,2);
     rungeKutta4(Neptune,Soleil,deltaT,Tsimu,&N);   writeMat(SIMPLE_NEPTUNE,Neptune.position,N,2);
     }

     // free the allocated memory
     freeSystemeSolaire(&Soleil ,&Mercure, &Venus, &Terre, &Mars,&Jupiter,&Saturne, &Uranus,&Neptune,N);
    }


                           /***********   ETAPE 04 : SYSTEME SOLAIRE   **************/
    if(select==04){
     int selectMethode;
     double deltaT= 24*60*60.;      //pas de simulation
     double Tsimu= 15*365.25*24*60*60.;
     int N = ceil(Tsimu/deltaT);

      printf("\n01 : Methode Differences finies .\n02 : Runge-Kutta 4.\n");
      printf("Veuillez selectionner une simulation  = ");

        if(scanf("%d",&selectMethode)!= 1){
        printf("Veuillez selectionnez une simulation valide");
        exit(EXIT_FAILURE);
        }

     /// Création du système solaire  avec lune
     astre Soleil  = CreerAstre(deltaT,Tsimu,"Soleil",MS,N,0.,0.,0.,0.);
     astre Mercure = CreerAstre(deltaT,Tsimu,"Mercure",MMer,N,57.91e+09, 0.,0.,47872.39);
     astre Venus   = CreerAstre(deltaT,Tsimu,"Venus",MV,N,108.2e+09, 0.,0.,35017.92);
     astre Terre   = CreerAstre(deltaT,Tsimu,"Terre",MT,N,149.6e+09, 0.,0.,29785.68);
     astre Mars    = CreerAstre(deltaT,Tsimu,"Mars",MMar,N,227.9e+09, 0.,0.,24751.87);
     astre Jupiter = CreerAstre(deltaT,Tsimu,"Jupiter",MJ,N,763.5e+09,0.,0.,12667.87);
     astre Saturne = CreerAstre(deltaT,Tsimu,"Saturne",MSat,N,0.,1.434e+12,-9845.257,0.);
     astre Uranus  = CreerAstre(deltaT,Tsimu,"Uranus",MU,N,-2.871e+12,0.,0.,-6805.026);
     astre Neptune = CreerAstre(deltaT,Tsimu,"Neptune",MN,N,-4.495e+12,0.,0.,-5424.025);
     astre Lune    = CreerAstre(deltaT,Tsimu,"Lune",ML,N,149.6e+09 + 384400e+03,0.,0.,29785.68 + 1023.162 );

     if (selectMethode == 01){
      // Calcul des trajectoires
      DiffFinies9Forces(Soleil,Mercure,Venus,Terre,Mars,Jupiter,Saturne,Uranus,Neptune,Lune,Tsimu,deltaT);
     // Ecriture dans les fichiers
     writeMat(TACHE04_MERCURE,Mercure.position,N,2);
     writeMat(TACHE04_VENUS,Venus.position,N,2);
     writeMat(TACHE04_TERRE,Terre.position,N,2);
     writeMat(TACHE04_MARS,Mars.position,N,2);
     writeMat(TACHE04_JUPITER,Jupiter.position,N,2);
     writeMat(TACHE04_SATURNE,Saturne.position,N,2);
     writeMat(TACHE04_URANUS,Uranus.position,N,2);
     writeMat(TACHE04_NEPTUNE,Neptune.position,N,2);
     writeMat(TACHE04_LUNE,Lune.position,N,2);
     }
     if( selectMethode == 02){
     // Calcul des trajectoires
     rungeKutta4_nineForces(Soleil ,Mercure, Venus, Terre, Mars,Jupiter,Saturne, Uranus,Neptune, Lune, deltaT,Tsimu);
     // Ecriture dans les fichiers
     writeMat(MERCURE,Mercure.position,N,2);
     writeMat(VENUS,Venus.position,N,2);
     writeMat(TERRE,Terre.position,N,2);
     writeMat(MARS,Mars.position,N,2);
     writeMat(JUPITER,Jupiter.position,N,2);
     writeMat(SATURNE,Saturne.position,N,2);
     writeMat(URANUS,Uranus.position,N,2);
     writeMat(NEPTUNE,Neptune.position,N,2);
     writeMat(LUNE,Lune.position,N,2);

     }
     /// Free allocated memory
     freeSystemeSolaire2(&Soleil ,&Mercure, &Venus, &Terre, &Mars,&Jupiter,&Saturne, &Uranus,&Neptune,&Lune,N);

    }

    return 0;
}



