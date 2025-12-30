#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <glib.h>
#include "config.h"

int limitesPaliers[10] ;
int valeursPaliers[10] ;
int coutsPotentiel[7] ;

int main(int argc, char *argv[])
{
	int status ;
	gtk_init() ;
	PCM_Config = gtk_application_new ("config.pcm.evo", G_APPLICATION_DEFAULT_FLAGS) ;
	
	g_signal_connect (PCM_Config, "activate", G_CALLBACK (initialisationFenetre), NULL) ;
	status = g_application_run (G_APPLICATION (PCM_Config), argc, argv) ;
	g_object_unref (PCM_Config) ;
	return status ;	
}

void initialisationFenetre (GtkApplication* PCM_Evolution, gpointer user_data)
{
	fenetreConfig = gtk_application_window_new (PCM_Config) ;		
	(void)user_data ; //Faire taire le compilateur.
	GtkCssProvider *cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_file (cssProvider, g_file_new_for_path ("style.css"));
	gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER) ;
	gtk_window_set_title (GTK_WINDOW (fenetreConfig), "PCM Évolution (config)") ;
	gtk_window_set_default_size (GTK_WINDOW (fenetreConfig), 800, 600) ;
	
	fenetreConfig = gtk_application_window_new (PCM_Config) ;
	
	Configuration configuration ;	
	
	FILE* fichier = NULL ;
	fichier = fopen("configuration", "r") ;
	
	GtkDropDown *menu ;
	
	int positionInitiale = 13 ; //Cela correspond au premier caractère décrivant le coût d'une évolution de potentiel dans le fichier configuration.
	fseek(fichier, positionInitiale, SEEK_SET) ;
	int i = 0 ;
	while (i < 7)
	{
		int cout ;
		fscanf(fichier, "%d", &cout) ;
		configuration.coutsPotentiel[i] = cout ;
		configuration=configuration;
		i ++ ;
		positionInitiale = positionInitiale + 19 ;
		fseek(fichier, positionInitiale, SEEK_SET) ;
	}
	
	positionInitiale = 137 ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	i = 0 ;
	while (i < 35)
	{
		int gain ;
		fscanf(fichier, "%d", &gain) ;
		configuration.gainsPotentiel[i] = gain ;
		i ++ ;
		positionInitiale = positionInitiale + 7 ;
		fseek(fichier, positionInitiale, SEEK_SET) ;
	}
	
	positionInitiale = 375 ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	i = 0 ;
	while (i < 35)
	{
		int gain ;
		fscanf(fichier, "%d", &gain) ;
		configuration.coutsProgression[i] = gain ;
		i ++ ;
		positionInitiale = positionInitiale + 7 ;
		fseek(fichier, positionInitiale, SEEK_SET) ;
	}	
	
	fclose(fichier) ;	
	
	grilleConfig = gtk_grid_new() ; 
	gtk_window_set_child(GTK_WINDOW (fenetreConfig), grilleConfig) ;	
	const char *optionsMenu[6] = {"Sélectionner une entrée dans ce menu", "Gérer le coût de l'augmentation de potentiel", "Gérer le gain fourni par un gain de potentiel", "Gérer le coût de progression des notes", "Gérer la date de départ de la partie", NULL} ;
	menu = GTK_DROP_DOWN(gtk_drop_down_new_from_strings(optionsMenu)) ;
	gtk_grid_attach(GTK_GRID (grilleConfig), GTK_WIDGET(menu), 0, 0, 1, 1) ;
	g_signal_connect(menu, "notify::selected-item", G_CALLBACK(choixMenu), menu) ;
	gtk_window_present (GTK_WINDOW (fenetreConfig)) ;
}

void choixMenu(GtkWidget *objet, GParamSpec *pspec, gpointer user_data)
{
	GtkDropDown *menu = (GtkDropDown*)user_data ;
	int choix = gtk_drop_down_get_selected(GTK_DROP_DOWN(menu)) ;
	viderGrille() ;
	switch(choix)
	{
		case 1:
			augmentationPotentiel() ;
			break ;
		case 2:
			grillePaliers(1) ;
			break ;
		case 3:
			grillePaliers(2) ;
			break ;
		case 4 :
			dateDepart() ;
			break ;
	}
}

void augmentationPotentiel()
{
	GtkWidget *valider ;
	int i = 0 ;
	
	valider = gtk_button_new_with_label("Valider") ;
	
	gtk_grid_attach(GTK_GRID (grilleConfig), valider, 0, 8, 1, 1) ;
	g_signal_connect(valider, "clicked", G_CALLBACK(validerPotentiel), NULL) ;	
	
	while (i < 7)
	{
		GtkWidget *etiquette ;
		GtkWidget *champ ;
		char texte[100] ;
		
		sprintf(texte, "Passer le potentiel de %d à %d", i + 1, i + 2) ;
		etiquette = gtk_label_new(texte) ;
		
		champ = gtk_entry_new() ;
		
		//On passe une structure au signal de changement de l'Entry, pour que la fonction puisse prendre en compte quel est le rang du potentiel concerné.
		StructPotentiel *structPotentiel = malloc(sizeof(StructPotentiel)) ;
		structPotentiel->champ = champ ;		
		structPotentiel->selection = i ;
		
		gtk_grid_attach(GTK_GRID (grilleConfig), etiquette, 0, i + 1, 1, 1) ;
		gtk_grid_attach(GTK_GRID (grilleConfig), champ, 1, i + 1, 1, 1) ;
		g_signal_connect(champ, "changed", G_CALLBACK(verificationCoutPotentiel), structPotentiel) ;
		
		i ++ ;
	}
}

void grillePaliers(int mode)
{
	GtkWidget *palier ;
	GtkWidget *textePalier ;
	GtkWidget *niveauPalier ;
	GtkWidget *valider ;
	
	int i = 0 ;
	while (i < 10) //Les deux tableaux étant utilisés en valeurs globales, ils doivent être nettoyés pour ne pas garder ce qui a été entré avant de changer d'option.
	{
		limitesPaliers[i] = 0 ;
		valeursPaliers[i] = 0 ;
		i ++ ;
	}
	
	i = 0 ;
	while (i< 7)
	{
		coutsPotentiel[i] = 0 ;
		i ++ ;
	}

	if (mode == 1)
	{
		palier = gtk_label_new("Niveau du palier (gain par potentiel)") ;
	}
	else 
	{
		palier = gtk_label_new("Niveau du palier (coût par amélioration)") ;
	}
	if (mode == 1)
	{
		textePalier = gtk_label_new("Gain d'une note max améliorée avec le potentiel") ;
	}
	else 
	{
		textePalier = gtk_label_new("Coût d'une améliore de notes en points") ;
	}
	textePalier = gtk_label_new("Limite du palier") ;
	niveauPalier = gtk_label_new("Gain apporté par le potentiel à ce palier") ;
	valider = gtk_button_new_with_label("Valider") ;
	
	gtk_grid_attach(GTK_GRID (grilleConfig), palier, 0, 1, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleConfig), textePalier, 1, 1, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleConfig), niveauPalier, 2, 1, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleConfig), valider, 0, 12, 1, 1) ;
	
	i = 0 ;
	while (i < 10)
	{
		GtkWidget *etiquette ;
		GtkWidget *champ1 ;
		GtkWidget *champ2 ;
		char texte[100] ;
		
		sprintf(texte, "Sélectionner le palier %d", i + 1) ;
		etiquette = gtk_label_new(texte) ;
		champ1 = gtk_entry_new() ;
		champ2 = gtk_entry_new() ;		
		
		gtk_grid_attach(GTK_GRID (grilleConfig), etiquette, 0, i + 2, 1, 1) ;
		gtk_grid_attach(GTK_GRID (grilleConfig), champ1, 1, i + 2, 1, 1) ;
		gtk_grid_attach(GTK_GRID (grilleConfig), champ2, 2, i + 2, 1, 1) ;
		
		StructEntry *structEntry = malloc(sizeof(StructEntry)) ;
		structEntry->champ1 = champ1 ;
		structEntry->champ2 = champ2 ;
		structEntry->selection = i ;
		structEntry->mode = mode ;

		g_signal_connect(champ1, "changed", G_CALLBACK(verificationChamp), structEntry) ;	
		g_signal_connect(champ2, "changed", G_CALLBACK(verificationChamp), structEntry) ;
		if (i == 0)
		{	
			g_signal_connect(valider, "clicked", G_CALLBACK(validerPaliers), structEntry) ;
		}		
		
		i ++ ;
	}
}

void dateDepart()
{
	GtkWidget *etiquette ;
	GtkWidget *champ ;
	etiquette = gtk_label_new("Année de départ de la partie") ;
	champ = gtk_entry_new() ;
	gtk_grid_attach(GTK_GRID (grilleConfig), etiquette, 0, 1, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleConfig), champ, 1, 1, 1, 1) ;
	g_signal_connect(champ, "changed", G_CALLBACK(verificationDate), champ) ;
}

void verificationCoutPotentiel(GtkWidget *objet, gpointer user_data)
{
	StructPotentiel *structPotentiel = (StructPotentiel*)user_data ;
	GtkWidget *champ = (GtkWidget*)structPotentiel->champ ;
	int selection = (int)structPotentiel->selection ;
	const gchar *pot_str = gtk_editable_get_text(GTK_EDITABLE(champ)) ;
	char *charFin ;
	if (!pot_str)
	{
		pot_str = "" ;
	}
	long pot_long = strtol(pot_str, &charFin, 10) ;
	
	if (*charFin != '\0')
	{
		GtkWidget *erreur ;
		erreur = gtk_label_new("Entre une valeur numérique (positive).") ;
		gtk_grid_attach(GTK_GRID(grilleConfig), erreur, 1, 0, 1, 1) ;
	}
	else
	{
		int valeur = (int)pot_long ; 
		if (valeur < 0)
		{
			GtkWidget *erreur ;
			erreur = gtk_label_new("Entre une valeur numérique (positive).") ;
			gtk_grid_attach(GTK_GRID(grilleConfig), erreur, 1, 0, 1, 1) ;
		}
		else if (valeur > 99999)
		{
			GtkWidget *erreur ;
			erreur = gtk_label_new("Entre une valeur inférieure à 100000.") ;
			gtk_grid_attach(GTK_GRID(grilleConfig), erreur, 1, 0, 1, 1) ;
		}
		else 
		{
			GtkWidget *message ;
			message = gtk_label_new("La valeur entrée est correcte.") ;
			gtk_grid_attach(GTK_GRID(grilleConfig), message, 1, 0, 1, 1) ;
			coutsPotentiel[selection] = pot_long ;
		}
	}
}

void verificationChamp(GtkWidget *objet, gpointer user_data)
{
	StructEntry *structEntry = (StructEntry*)user_data ;
	int selection = (int)structEntry->selection ;
	int mode = (int)structEntry->mode ;
	GtkWidget * champ ;
	if (mode == 1 )
	{
		champ = (GtkWidget*)structEntry->champ1 ;
	}
	else 
	{
		champ = (GtkWidget*)structEntry->champ2 ;
	}
	const gchar *champ_str = gtk_editable_get_text(GTK_EDITABLE(champ)) ;
	char *charFin ;
	if (!champ_str)
	{
		champ_str = "" ;
	}
	long champ_long = strtol(champ_str, &charFin, 10) ;
	
	if (*charFin != '\0')
	{
		GtkWidget *erreur ;
		erreur = gtk_label_new("Entre une valeur numérique (entre 50 et 84).") ;
		gtk_grid_attach(GTK_GRID(grilleConfig), erreur, 1, 0, 1, 1) ;
	}
	else
	{
		int valeur = (int)champ_long ; 
		if (valeur < 50 || valeur > 84)
		{
			GtkWidget *erreur ;
			erreur = gtk_label_new("Entre une valeur numérique (entre 50 et 84).") ;
			gtk_grid_attach(GTK_GRID(grilleConfig), erreur, 1, 0, 1, 1) ;
		}
		else 
		{
			GtkWidget *message ;
			message = gtk_label_new("La valeur entrée est correcte.") ;
			gtk_grid_attach(GTK_GRID(grilleConfig), message, 1, 0, 1, 1) ;
			if (mode == 1)
			{
				limitesPaliers[selection] = champ_long ;
			}
			else 
			{
				valeursPaliers[selection] = champ_long ;
			}
		}
	}
}

void verificationDate(GtkWidget *objet, gpointer user_data)
{
	GtkWidget *date = (GtkWidget*)user_data ;
	const gchar *date_str = gtk_editable_get_text(GTK_EDITABLE(date)) ;
	char *charFin ;
	if (!date_str)
	{
		date_str = "" ;
	}
	long date_long = strtol(date_str, &charFin, 10) ;
	
	if (*charFin != '\0')
	{
		GtkWidget *erreur ;
		erreur = gtk_label_new("Entre une valeur numérique (positive).") ;
		gtk_grid_attach(GTK_GRID(grilleConfig), erreur, 2, 0, 1, 1) ;
	}
	else if (date_long < 1000 || date_long > 9999)
	{
		GtkWidget *erreur ;
		erreur = gtk_label_new("Entre un nombre à quatre chiffres.") ;
		gtk_grid_attach(GTK_GRID(grilleConfig), erreur, 2, 0, 1, 1) ;
	}
	else 
	{
		validerDate(date_long) ;
	}	
}

void validerPotentiel(GtkWidget *objet, gpointer user_data)
{
	int i = 0 ;
	FILE* fichier = NULL ;
	fichier = fopen("configuration", "r+") ;
	int positionInitiale = 13 ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	
	while (i < 7)
	{
		char pot_str[6] ;
		if (coutsPotentiel[i] < 10)
		{
			sprintf(pot_str, "0000%d", coutsPotentiel[i]) ;
		}
		else if (coutsPotentiel[i] < 100 )
		{
			sprintf(pot_str, "000%d", coutsPotentiel[i]) ;
		}
		else if (coutsPotentiel[i] < 1000)
		{
			sprintf(pot_str, "00%d", coutsPotentiel[i]) ;
		}
		else if (coutsPotentiel[i] < 10000 )
		{
			sprintf(pot_str, "0%d", coutsPotentiel[i]) ;
		}
		else if (coutsPotentiel[i] < 100000 )
		{
			sprintf(pot_str, "%d", coutsPotentiel[i]) ;
		}
		else //Si pour une raison ou une autre, la donnée n'est pas valide, on continue à analyser le reste des données entrées.
		{
			i ++ ;
			continue ;
		}
		fputs(pot_str, fichier) ;
		positionInitiale = positionInitiale + 19 ;
		fseek(fichier, positionInitiale, SEEK_SET) ;
		i ++ ;
	}
	fclose(fichier) ;	
}

void validerPaliers(GtkWidget *objet, gpointer user_data)
{
	StructEntry *structEntry = (StructEntry*)user_data ;
	int mode = structEntry->mode ;
	
	int i = 0 ;
	int variable ;
	int positionInitiale ;
	FILE* fichier = NULL ;
	fichier = fopen("configuration", "r+") ;	
		
	if (mode == 1)
	{
		positionInitiale = 137 ;
		variable = limitesPaliers[i] ;
	}
	else 
	{
		positionInitiale = 375 ;
		variable = valeursPaliers[i] ;
	}
	
	fseek(fichier, positionInitiale, SEEK_SET) ;
	
	while (i < 10)
	{
		i ++ ;
		char var_str[3] ;
		if (variable < 50 || variable > 84 )
		{
			i ++ ;
			continue ;
		}
		else 
		{
			sprintf(var_str, "%d", variable) ;
			fputs(var_str, fichier) ;
			positionInitiale = positionInitiale + 7 ;
			fseek(fichier, positionInitiale, SEEK_SET) ;
			i ++ ;
		}	
	}
}

void validerDate(long date)
{
	FILE* fichier = NULL ;
	char date_str[4] ;
	fichier = fopen("configuration", "r+") ;	
	int positionInitiale = 623 ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	sprintf(date_str, "%ld", date) ;
	fputs(date_str, fichier) ;
}

void viderGrille()
{
	int i = 0 ;
	while (i <= 10)
	{
		gtk_grid_remove_row (GTK_GRID(grilleConfig), 1) ;
		i ++ ;
	}
}