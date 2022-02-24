# ifndef _FilesManager_h
#define _FilesManager_h


/**ETAPE 01 : Système terre-lune simplifié*/
// Différences finies
#define TACHE01_LUNE_DIF "Etape01/DIF-S-P.txt"
// Euler
#define TACHE01_LUNE_EULER "Etape01/EUL-S-P.txt"
// RK2
#define TACHE01_LUNE_RK2 "Etape01/RK2-S-P.txt"
// RK4
#define TACHE01_LUNE_RK4 "Etape01/RK4-S-P.txt"

/**ETAPE 02 : Système terre-lune */
// Diffèrences finies
#define TACHE02_LUNE "Etape02/Lune-S-P.txt"
#define TACHE02_TERRE "Etape02/Terre-S-P.txt"
// RK4
#define XY_TERRE "Etape02/Terre_XY_2Forces.txt"
#define XY_LUNE  "Etape02/Lune_XY_2Forces.txt"

/**ETAPE 03 : Système terre-lune */
// Différences finies
#define TACHE03_MERCURE "Etape03/MERCURE-S-P.txt"
#define TACHE03_VENUS   "Etape03/VENUS-S-P.txt"
#define TACHE03_TERRE   "Etape03/TERRE-S-P.txt"
#define TACHE03_MARS    "Etape03/MARS-S-P.txt"
#define TACHE03_JUPITER "Etape03/JUPITER-S-P.txt"
#define TACHE03_SATURNE "Etape03/SATURNE-S-P.txt"
#define TACHE03_URANUS  "Etape03/URANUS-S-P.txt"
#define TACHE03_NEPTUNE "Etape03/NEPTUNE-S-P.txt"

// RK4
#define SIMPLE_MERCURE "Etape03/simple_mercure_XY_RK4.txt"
#define SIMPLE_VENUS   "Etape03/simple_venus_XY_RK4.txt"
#define SIMPLE_TERRE   "Etape03/simple_terre_XY_RK4.txt"
#define SIMPLE_MARS    "Etape03/simple_mars_XY_RK4.txt"
#define SIMPLE_JUPITER "Etape03/simple_jupiter_XY_RK4.txt"
#define SIMPLE_SATURNE "Etape03/simple_saturne_XY_RK4.txt"
#define SIMPLE_URANUS  "Etape03/simple_uranus_XY_RK4.txt"
#define SIMPLE_NEPTUNE "Etape03/simple_neptune_XY_RK4.txt"

/**ETAPE 04 : Système terre-lune */
// Différences Finies
#define TACHE04_MERCURE "Etape04/MERCURE-S-P9.txt"
#define TACHE04_VENUS   "Etape04/VENUS-S-P9.txt"
#define TACHE04_TERRE   "Etape04/TERRE-S-P9.txt"
#define TACHE04_MARS    "Etape04/MARS-S-P9.txt"
#define TACHE04_JUPITER "Etape04/JUPITER-S-P9.txt"
#define TACHE04_SATURNE "Etape04/SATURNE-S-P9.txt"
#define TACHE04_URANUS  "Etape04/URANUS-S-P9.txt"
#define TACHE04_NEPTUNE "Etape04/NEPTUNE-S-P9.txt"
#define TACHE04_LUNE    "Etape04/LUNE-S-P9.txt"

// RK4
#define SOLEIL  "Etape04/soleil_XY.txt"
#define MERCURE "Etape04/mercure_XY.txt"
#define VENUS   "Etape04/venus_XY.txt"
#define TERRE   "Etape04/terre_XY.txt"
#define MARS    "Etape04/mars_XY.txt"
#define JUPITER "Etape04/jupiter_XY.txt"
#define SATURNE "Etape04/saturne_XY.txt"
#define URANUS  "Etape04/uranus_XY.txt"
#define NEPTUNE "Etape04/neptune_XY.txt"
#define LUNE    "Etape04/lune_XY.txt"


                    /******************************         STURCTURES MANAGER          *****************************/

 typedef struct
{
    char* nom;
    double masse;
    double** position;
    double** vitesse;
} astre;


void printAstre(astre My_Astre,int N);

astre CreerAstre(double deltaT, double Tsimu, char*nom, double masse, int N, double x0, double y0,double vx0, double vy0);


void freeSystemeSolaire2(astre* astre0, astre* astre1,astre* astre2,astre* astre3,astre* astre4,astre* astre5,astre* astre6,astre* astre7,
                        astre* astre8, astre* astre9,int N);

void freeSystemeSolaire(astre* astre0, astre* astre1,astre* astre2,astre* astre3,astre* astre4,astre* astre5,astre* astre6,astre* astre7,astre* astre8,int N);


                /**********************************         MATRICES MANAGER         *******************************/


//ECRIRE UNE MATRICE DANS UN FICHIER TEXT
void writeMat(char* fName,double**Matrice,int nbLines, int nbRows);
//FONCTION QUI CREE UNE MATRICE AVEC ALLOCATION DYNAMIQUE
double** createMat(int nbLines, int nbRows);
//FONCTION QUI LIBERE UNE MATRICE ALLOUEE DYNAMIQUEMENT
void freeMat(double*** Matrice,int nbLines);
//FONCTION QUI AFFICHE UNE MATRICE
void printMat(double**Matrice,int nbLines,int nbRows);





# endif // _astre_h
