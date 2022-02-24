#include "FilesManager.h"
#include "SysSolaire.h"
#include "OrbitsCalculator.h"

   /*******************************         STRUCTURES MANAGER + MATRICES         *********************************/


  /// FONCTIONS QUI CREE,AFFICHE, ET DESALOUE UNE MATRICE DE TYPE DOUBLE

double** createMat(int nbLines, int nbRows){
    int i;
    double** Matrice = malloc(nbLines*sizeof(double*));
    for(i=0; i<nbLines; i++)
    {
        Matrice[i]= calloc(nbRows,sizeof(double));
    }
    return Matrice;
}

void printMat(double**Matrice,int nbLines,int nbRows)
{
    int i,j;
    for(i=0; i<nbLines; i++)
    {
        for(j=0; j<nbRows; j++)
        {
            printf("%le\t",Matrice[i][j]);
        }
        printf("\n");
    }
}

void freeMat(double*** Matrice,int nbLines)
{
    int i;
    for(i=0; i< nbLines; i++)
        free(*(Matrice)[i]);
    free(*Matrice);
    (*Matrice)=NULL;
}

/// FONCTION QUI ECRIT UNE MATRICE DE TYPE DOUBLE DANS UN FICHIER
void writeMat(char* fName,double**Matrice,int nbLines, int nbRows)
{
    FILE* fTxt = fopen (fName,"w");
    if(fTxt != NULL)
    {
        int i,j;
        fprintf(fTxt, "%d %d\n",nbLines,nbRows);
        for(i=0; i<nbLines; i++)
        {
            for(j=0; j<nbRows; j++)
                fprintf(fTxt, "%le ",Matrice[i][j]);
            fprintf(fTxt, "\n");
        }
        fclose(fTxt);
    }
    else
        printf("Error Opening File for Writing\n");
}

   /*******************************         STUCTURES MANAGER          ************************************/

//FONCTION QUI CREE UN ASTRE AVEC L'ALLOCATION DYNAMIQUE
astre CreerAstre(double deltaT, double Tsimu, char*nom, double masse, int N, double x0, double y0,double vx0, double vy0)
{

    astre ASTRE;
    ASTRE.nom=nom;
    ASTRE.masse=masse;

    double **Pos=createMat(N,2);
    Pos[0][0]=x0;
    Pos[0][1]=y0;

    double **Vit=createMat(N,2);
    Vit[0][0]=vx0;
    Vit[0][1]=vy0;

    ASTRE.position=Pos;
    ASTRE.vitesse=Vit;

    return ASTRE;
}

// FONCTION QUI DESALOUE LA MEMOIRE ALLOUER POUR DES CHAMPS D'UNE STRUCTURE
void FreeAstre (astre *monAstre)
{
    monAstre->nom=NULL;
    monAstre->masse=0;
    int j;
    for( j=0; j<2; j++)
    {
        free(monAstre->position[j]);
    }
    free(monAstre->position);
    for( j=0; j<2; j++)
    {
        free(monAstre->vitesse[j]);
    }
    free(monAstre->vitesse);

    monAstre->position=NULL;
    monAstre->vitesse=NULL;


}

// FONCTION QUI AFFICHE LES DIFFERENTS CHAMPS D'UNE STRUCTURE

void printAstre(astre My_Astre,int N)
{
    printf("Ma structure : %s\n", My_Astre.nom);
    printf("Sa masse : %e\n", My_Astre.masse);
    printf("Matrice Position\n");
    printf("x(t)\t\t y(t)\n");
    printMat(My_Astre.position,N,2);
    printf("Matrice Vitesses\n");
    printf("Vx(t)\t\t Vy(t)\n");
    printMat(My_Astre.vitesse,N,2);
}

// FONCTION QUI DESALOUE LES MATRICES POSITIONS ET VITESSES DE 9 STRUCTURES ASTRES : UTILISER POUR L'ETAPE 3

void freeSystemeSolaire(astre* astre0, astre* astre1,astre* astre2,astre* astre3,astre* astre4,astre* astre5,astre* astre6,astre* astre7,astre* astre8,int N){
 freeMat(&astre0->position,N);freeMat(&astre0->vitesse,N);
 freeMat(&astre1->position,N);freeMat(&astre1->vitesse,N);
 freeMat(&astre2->position,N);freeMat(&astre2->vitesse,N);
 freeMat(&astre3->position,N);freeMat(&astre3->vitesse,N);
 freeMat(&astre4->position,N);freeMat(&astre4->vitesse,N);
 freeMat(&astre5->position,N);freeMat(&astre5->vitesse,N);
 freeMat(&astre6->position,N);freeMat(&astre6->vitesse,N);
 freeMat(&astre7->position,N);freeMat(&astre7->vitesse,N);
 freeMat(&astre8->position,N);freeMat(&astre8->vitesse,N);
}

// FONCTION QUI DESALOUE LES MATRICES POSITIONS ET VITESSES DE 10 STRUCTURES ASTRES : UTILISER POUR L'ETAPE 4

void freeSystemeSolaire2(astre* astre0, astre* astre1,astre* astre2,astre* astre3,astre* astre4,astre* astre5,astre* astre6,astre* astre7,
                        astre* astre8, astre* astre9,int N){
 freeMat(&astre0->position,N);freeMat(&astre0->vitesse,N);
 freeMat(&astre1->position,N);freeMat(&astre1->vitesse,N);
 freeMat(&astre2->position,N);freeMat(&astre2->vitesse,N);
 freeMat(&astre3->position,N);freeMat(&astre3->vitesse,N);
 freeMat(&astre4->position,N);freeMat(&astre4->vitesse,N);
 freeMat(&astre5->position,N);freeMat(&astre5->vitesse,N);
 freeMat(&astre6->position,N);freeMat(&astre6->vitesse,N);
 freeMat(&astre7->position,N);freeMat(&astre7->vitesse,N);
 freeMat(&astre8->position,N);freeMat(&astre8->vitesse,N);
 freeMat(&astre9->position,N);freeMat(&astre9->vitesse,N);

}


