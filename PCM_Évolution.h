int creation(char *caracteristiques[]) ; //Choix 1 du menu
int choixNomDeFichier() ; 
int verificationExistanceDuFichier() ;
int entreeStats(char *caracteristiques[]) ;
int demandeNomDeFichier() ;
int modification() ;
int lireStats() ;
int calculAmelioration(int caracteristique) ;
void enregistrer(int coureur[]) ;

#define Linux
#ifdef Windows
#define é "\x82"
#define É "\x90"
#define è "\x9A"
#define à "\x85"
#define À "\xB7"
#define ê "\x88"
#define î "\x8C"

#else //Pour les systèmes d'exploitation normalement constitués
#define é "é"
#define É "É"
#define à "à"
#define À "À"
#define ê "Ê"
#define è "È"
#define î "î"
#endif
