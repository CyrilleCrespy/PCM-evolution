GtkApplication *PCM_Config ;
GtkWidget *fenetreConfig ;
GtkWidget *grilleConfig ;

void initialisationFenetre (GtkApplication* PCM_Evolution, gpointer user_data) ;
void choixMenu(GtkWidget *objet, GParamSpec *pspec, gpointer user_data) ;
void augmentationPotentiel() ;
void grillePaliers(int mode) ;
void verificationCoutPotentiel(GtkWidget *objet, gpointer user_data) ;
void verificationChamp(GtkWidget *objet, gpointer user_data) ;
void verificationDate(GtkWidget *objet, gpointer user_data) ;
void dateDepart() ;
void viderGrille() ;
void validerPotentiel(GtkWidget *objet, gpointer user_data) ;
void validerPaliers(GtkWidget *objet, gpointer user_data) ;
void validerDate(long date) ;

typedef struct
{
	int coutsPotentiel[7] ;
	int gainsPotentiel[35] ;
	int coutsProgression[35] ;
	int selection ;
} Configuration ;

typedef struct
{
	GtkWidget *champ1 ;
	GtkWidget *champ2 ;
	int selection ;
	int mode ;
} StructEntry ;

typedef struct
{
	GtkWidget *champ ;
	int selection ;
} StructPotentiel ;