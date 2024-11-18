int creation(char *caracteristiques[]) ; //Choix 1 du menu
int choixNomDeFichier() ; 
int verificationExistanceDuFichier() ;
void viderBuffer() ;
int verificationEntreeNumerique(int min, int max) ;
int confirmationEntree() ;
void remplirJournal(char *message) ;
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
void demandeNomDeFichier(char *caracteristiques[]) ;
void modification(int session, int points, char *caracteristiques[], int taille) ;
int lireStats() ;
void enregistrer(int session, int style, int coureur[], int potentiel, int principal, int secondaire, int taille, int poids, int mois, int jour, char *nationalite, char *course1, char *course2, char *course3, int notesInitiales[], int maximum[]) ;
void enregistrerMax(int maximum[]) ;
void creerCopie() ;
void restaurerSauvegarde() ;
int verifierDonnees(int session, int style, int coureur[], int potentiel, int principal, int secondaire, int taille, int poids, int mois, int jour, char *nationalite, char *course1, char *course2, char *course3) ;
int determinerNotesMax(int style, int compteur) ;
int retrouverNotesMax(int compteur) ;
void corrigerNomDeFichier() ;
int calculAmelioration(int noteActuelle, int *points, int *maximum, int notesInitiales, int *potentiel, int potentielInitial) ;
int calculAugmentation(int noteActuelle, int *points, int *maximum) ;
int calculDiminution(int noteActuelle, int *points, int notesInitiales) ;
void calculPotentiel(int noteActuelle, int *potentiel, int *maximum, int typeAugmentation, int *points) ;
int verifierAugmentationPotentiel(int *potentiel) ;
int determinerCoutPotentiel(int *potentiel) ;
int determinationAugmentationPotentielPossible(int *maximum) ;
void suppressionEspace() ;

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
#define DECALAGE 4
#define ECRIRE_TEMPS (fprintf(fichier, "%lld : %s\n", horodatage, message))

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
#define DECALAGE 3
#define ECRIRE_TEMPS (fprintf(fichier, "%ld : %s\n", horodatage, message))
#endif
