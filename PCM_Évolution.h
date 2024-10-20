int creation(char *caracteristiques[]) ; //Choix 1 du menu
int choixNomDeFichier() ; 
int verificationExistanceDuFichier() ;
int choixPrincipal() ;
int choixSecondaire() ;
int calculStyle(int principal, int secondaire) ;
int choixTaille() ;
int choixPoids() ;
int choixMoisDeNaissance() ;
int choixJourDeNaissance(int jourMax) ;
char *choixNationalite() ;
char *propositionDonnees(int typeFichier, char premiereLettre) ;
char *choixCourseFavorite() ;
int demandeNomDeFichier(char *caracteristiques[]) ;
void modification(int points, char *caracteristiques[], int taille) ;
int lireStats() ;
int calculAmelioration(int noteActuelle, int limiteMax, int *points, int maximum[], int choix, int notesInitiales) ;
void enregistrer(int style, int coureur[], int potentiel, int principal, int secondaire, int taille, int poids, int mois, int jour, char *nationalite, char *course1, char *course2, char *course3) ;
int determinerNotesMax(int principal, int secondaire, int compteur) ;
int determinerLimitePotentiel(int potentiel) ;
void corrigerNomDeFichier() ;
int calculAugmentation(int noteActuelle, int limiteMax, int *points, int maximum[], int choix) ;
int calculDiminution(int noteActuelle, int *points, int notesInitiales) ;
int calculCoutPotentiel(int potentiel) ;
int augmenterPotentiel(int potentiel) ;
void correctionString(char *string) ;

#define Windows
#ifdef Windows
#define é "\x82"
#define É "\x90"
#define è "\x8A"
#define à "\x85"
#define À "\xB7"
#define ê "\x88"
#define î "\x8C"
#define û "\x96"
#define tiret "\xC4"
#define clear "cls"
#define symboleNumero "\xA7"

#else //Pour les systèmes d'exploitation normalement constitués
#define é "é"
#define É "É"
#define è "è"
#define à "à"
#define À "À"
#define ê "Ê"
#define î "î"
#define û "û"
#define tiret "─"
#define clear "clear"
#define symboleNumero "°"
#endif
