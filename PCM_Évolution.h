typedef struct //Strucuture de la fiche enregistrée.
{
	gchar nom[250] ;
	int jour ;
	int mois ; 
	int annee ;
	int taille ;
	int poids ;
	int principal ;
	int secondaire ;
	int style ;
	char course1[200] ;
	char course2[200] ;
	char course3[200] ;
	char pays[100] ;
	int notes[14] ;
	int notesMax[14] ;
	int points ;
	int potentiel ;
} StructFicheCoureur ;

typedef struct //Structure passée aux fonctions de calcul
{
	GtkWidget *grilleModif ;
	StructFicheCoureur *originel ;
	int selection ;
} StructFicheCalcul ;

typedef struct //Struture des champs de la fenêtre d'initialisation renvoyés vers le signal.
{
	GtkWidget *taille ;
	GtkWidget *poids ;
	GtkWidget *calendrier ;
	GtkDropDown *principal ;
	GtkDropDown *secondaire ;
	GtkDropDown *course1 ;
	GtkDropDown *course2 ;
	GtkDropDown *course3 ;
	GtkDropDown *pays ;
} StructFicheJoueur ;

typedef struct
{
	GtkWidget *grilleCreation ;
	GtkWidget *fenetrePrincipale ;
	GtkWidget *champNomDeFichier ;
	StructFicheJoueur *ficheJoueur ;
	StructFicheCoureur *ficheCoureur ;
} StructFicheSignal ;

typedef struct
{
	StructFicheCoureur *coureur ;
	GtkWidget *points ;
	GtkWidget *grilleModif ;
} SignalPoints ;

int creation(char *caracteristiques[]) ; //Choix 1 du menu
int choixNomDeFichier() ; 
int editableOK = 1 ;
int dropDownOK = 1 ;
int dateOK = 1 ;

int verificationExistanceDuFichier(GtkWidget *boutonValider, gpointer user_data) ;
void suppressionCreation(GtkWidget *boutonOui, gpointer user_data) ;
void verificationEditable(GtkWidget *objet, gpointer user_data) ;
void verificationDropDown(GtkWidget *objet, GParamSpec *pspec, gpointer user_data) ;
void ecrireDate(GtkWidget *calendrier, gpointer user_data) ;
void viderBuffer() ;
int confirmationEntree() ;
void remplirJournal(char *message) ;
int choixPrincipal() ;
int choixSecondaire() ;
int calculStyle(int principal, int secondaire, char nom[]) ;
int choixJourDeNaissance(int jourMax) ;
void annuler(GtkWidget *boutonAnnuler, gpointer user_data) ;
void validerCoureur(GtkWidget *boutonValider, int *pointeur) ;
void peuplerListe(char *liste) ;
void demandeNomDeFichier() ;
void trouverFichier (GtkWidget *boutonValider, gpointer user_data) ;
void afficherCoureur(gpointer user_data) ;
void afficherNotes(GtkWidget *objet, gpointer user_data) ;
void boutonsNotes(StructFicheCoureur *ficheCoureur, int compteur) ;
void modification(int session, int points, char *caracteristiques[], int taille) ;
void enregistrer(StructFicheCoureur *ficheCoureur) ;
void enregistrerMax(StructFicheCoureur *ficheCoureur) ;
void creerCopie(char nom[250]) ;
void restaurerSauvegarde(char nom[250]) ;
int verifierDonnees(StructFicheCoureur *ficheCoureur) ;
int determinerNotesMax(int style, int compteur) ;
int retrouverNotesMax(int compteur) ;
void corrigerNomDeFichier() ;
int calculAugmentation(GtkWidget *boutonPlus, gpointer user_data) ;
int calculDiminution(GtkWidget *boutonMoins, gpointer user_data) ;
void determinerCoutPotentiel(GtkWidget *objet, gpointer user_data) ;
int determinerCoutEvolution(int noteActuelle) ;
void ajoutPoints(GtkWidget *objet, gpointer user_data) ;
void suppressionEspace() ;
void initialisationFenetre (GtkApplication* PCM_Evolution, gpointer user_data) ;
void fenetreNouvelleFiche(GtkApplication* PCM_Evolution, gpointer user_data) ;
void initialisationCoureur(GtkWidget *boutonNouvelleFiche, gpointer user_data) ;
void viderGrillePrincipale() ;
void determinerCouleurNote(GtkWidget *note) ;

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
