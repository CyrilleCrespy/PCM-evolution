int creation(char *caracteristiques[]) ; //Choix 1 du menu
int choixNomDeFichier() ; 
int verificationExistanceDuFichier() ;
int choixStyle() ;
int entreeStats() ;
int demandeNomDeFichier(char *caracteristiques[]) ;
void modification(int points, char *caracteristiques[]) ;
int lireStats() ;
int calculAmelioration(int noteActuelle, int limiteMax, int *points, int maximum[], int choix) ;
void enregistrer(int style, int coureur[], int potentiel) ;
int determinerNotesMax(int principal, int secondaire, int compteur) ;
int determinerLimitePotentiel(int potentiel) ;

#define Windows
#ifdef Windows
#define é "\x82"
#define É "\x90"
#define è "\x9A"
#define à "\x85"
#define À "\xB7"
#define ê "\x88"
#define î "\x8C"
#define û "\x96"
#define clear "cls"

#else //Pour les systèmes d'exploitation normalement constitués
#define é "é"
#define É "É"
#define à "à"
#define À "À"
#define ê "Ê"
#define è "È"
#define î "î"
#define û "û"
#define clear "clear"
#endif
