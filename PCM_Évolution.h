int creation(char *caracteristiques[]) ; //Choix 1 du menu
int choixNomDeFichier() ; 
int verificationExistanceDuFichier() ;
int choixStyle() ;
int entreeStats() ;
int demandeNomDeFichier() ;
int modification(int points) ;
int lireStats() ;
int calculAmelioration() ;
void enregistrer(int style, int coureur[]) ;
int determinerNotesMax(int principal, int secondaire, int compteur) ;

#define Windows
#ifdef Windows
#define é "\x82"
#define É "\x90"
#define è "\x9A"
#define à "\x85"
#define À "\xB7"
#define ê "\x88"
#define î "\x8C"
#define clear "cls"

#else //Pour les systèmes d'exploitation normalement constitués
#define é "é"
#define É "É"
#define à "à"
#define À "À"
#define ê "Ê"
#define è "È"
#define î "î"
#define clear "clear"
#endif
