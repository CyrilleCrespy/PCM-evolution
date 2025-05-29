void peuplerListe(char *liste)
{
	int compteur = 0 ;
	FILE* fichier = NULL ;
	fichier = fopen(liste, "r") ;
	if (liste == "pays")
	{
		pays = g_list_store_new(G_TYPE_OBJECT) ;
	}
	if (liste == "courses")
	{
		courses = g_list_store_new(G_TYPE_OBJECT) ;
	}
	
	while (1)
	{
		if (feof(fichier))
		{
			fclose(fichier) ;
			break ;
		}
		else
		{
			if (liste == "pays")
			{	
				char tampon[500] ;
				fgets(tampon, 500, fichier) ;
				int compteur ;
				for (compteur = 0 ; tampon[compteur] != '\0' ; compteur ++)
				{
					if (tampon[compteur] == '\n' || tampon[compteur] == '\r')
					{
						tampon[compteur] = '\0' ;
						break ;
					}
				}
				tampon[compteur] = '\0' ;
				g_list_store_append(G_LIST_STORE(pays), gtk_string_object_new(tampon)) ;
			}
			else if (liste == "courses")
			{
				char tampon[500] ;
				fgets(tampon, 500, fichier) ;
				int compteur ;
				for (compteur = 0 ; tampon[compteur] != '\0' ; compteur ++)
				{
					if (tampon[compteur] == '\n' || tampon[compteur] == '\r')
					{
						tampon[compteur] = '\0' ;
						break ;
					}
				}
				tampon[compteur] = '\0' ;
				g_list_store_append(G_LIST_STORE(courses), gtk_string_object_new(tampon)) ;
			}
			compteur ++ ;
		}
	}
}

void suppressionCreation(GtkWidget *boutonOui, gpointer user_data)
{
	StructFicheSignal *ficheSignal = (StructFicheSignal*)user_data ;
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)ficheSignal->ficheCoureur ;
	char fichierMax[254] ;
	if (remove(ficheCoureur->nom) == 0)
	{
		remplirJournal("Fiche supprimée à la demande de l'utilisateur.") ;
		printf("Fichier coureur supprim%s.\n", é) ;
	}
	else
	{
		remplirJournal("Suppression du fichier coureur impossible.") ;
		perror("Suppression du fichier coureur impossible.\n") ;
	}
	sprintf(fichierMax, "%s_max", ficheCoureur->nom) ;
	if (remove(fichierMax) == 0)
	{
		printf("Fichier max supprim%s.\n", é) ;
		remplirJournal("Fichier max supprimé.") ;
	}
	else
	{
		perror("Suppression du fichier max impossible.\n") ;
		remplirJournal("Suppression du fichier max impossible.") ;
	}
	initialisationCoureur(NULL, ficheSignal) ;
}

void verificationEditable(GtkWidget *objet, gpointer user_data)
{
	editableOK = 1 ;	
	
	StructFicheSignal *ficheSignal = (StructFicheSignal*)user_data ;
	StructFicheJoueur *ficheJoueur = (StructFicheJoueur*)ficheSignal->ficheJoueur ;
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)ficheSignal->ficheCoureur ;
	GtkWidget *grilleCreation = (GtkWidget*)ficheSignal->grilleCreation ;
	
	printf("%s NOM AP\n", ficheSignal->ficheCoureur->nom) ;
	
	//On transformme le gchar en un int.
	
	const gchar *taille_str = gtk_editable_get_text(GTK_EDITABLE(ficheJoueur->taille)) ;
	char *charFin ;
	if (!taille_str)
	{
		taille_str = "" ;
	}
	long taille_long = strtol(taille_str, &charFin, 10) ;
	
	//Taille.
	if (*charFin != '\0')
	{
		g_print("Erreur de conversion.\n") ;
		GtkWidget *erreur ;
		erreur = gtk_label_new("Entre uniquement une taille composée de trois chiffres.") ;
		gtk_grid_attach(GTK_GRID(grilleCreation), erreur, 10, 0, 2, 1) ;
		editableOK = 0 ;
	}
	else
	{
		ficheCoureur->taille = (int)taille_long ;
		if(ficheCoureur->taille < 150)
		{
			GtkWidget *erreur ;
			printf("Trop petit.\n") ;
			erreur = gtk_label_new("La taille entrée est trop petite. Minimum : 150.") ;
			gtk_grid_attach(GTK_GRID(grilleCreation), erreur, 10, 0, 2, 1) ;
			editableOK = 0 ;
		}
		else if(ficheCoureur->taille > 200)
		{
			GtkWidget *erreur ;
			printf("Trop grand.\n") ;
			erreur = gtk_label_new("La taille entrée est trop grande. Maximum : 200.") ;
			gtk_grid_attach(GTK_GRID(grilleCreation), erreur, 10, 0, 2, 1) ;
			editableOK = 0 ;
		}
		else
		{
			GtkWidget *validation ;
			printf("Taille valide.\n") ;
			validation = gtk_label_new("La taille entrée est valide.") ;
			printf("1\n") ;
			gtk_grid_attach(GTK_GRID(grilleCreation), validation, 10, 0, 2, 1) ;
		}
	}

	//Poids.
	
	const gchar *poids_str = gtk_editable_get_text(GTK_EDITABLE(ficheJoueur->poids)) ;
	long poids_long = strtol(poids_str, &charFin, 10) ;
	
	if (!poids_str)
	{
		poids_str = "" ;
	}
	
	if (*charFin != '\0')
	{
		g_print("Erreur de conversion.\n") ;
		GtkWidget *erreur ;
		erreur = gtk_label_new("Entre uniquement un poids composé de deux à trois chiffres.") ;
		gtk_grid_attach(GTK_GRID(grilleCreation), erreur, 10, 1, 2, 1) ;
		editableOK = 0 ;
	}
	else
	{
		ficheCoureur->poids = (int)poids_long ;
		if(ficheCoureur->poids < 50)
		{
			GtkWidget *erreur ;
			printf("Trop petit.\n") ;
			erreur = gtk_label_new("Le poids entré est trop petit. Minimum : 50.") ;
			gtk_grid_attach(GTK_GRID(grilleCreation), erreur, 10, 1, 2, 1) ;
			editableOK = 0 ;
		}
		else if(ficheCoureur->poids > 100)
		{
			GtkWidget *erreur ;
			printf("Trop grand.\n") ;
			erreur = gtk_label_new("Le poids entré est trop grand. Maximum : 100.") ;
			gtk_grid_attach(GTK_GRID(grilleCreation), erreur, 10, 1, 2, 1) ;
			editableOK = 0 ;
		}
		else
		{
			GtkWidget *validation ;
			printf("Taille valide.\n") ;
			validation = gtk_label_new("Le poids entré est valide.") ;
			gtk_grid_attach(GTK_GRID(grilleCreation), validation, 10, 1, 2, 1) ;
		}
	}
	
	printf("%d %d %d status\n", editableOK, dropDownOK, dateOK) ;
	
	if (editableOK == 1 && dropDownOK == 1 && dateOK == 1)
	{
		ficheCoureur->style = calculStyle(ficheCoureur->principal, ficheCoureur->secondaire, ficheCoureur->nom) ;
		ficheCoureur->points = 200 ;
		ficheCoureur->potentiel = 4 ;
		GtkWidget *boutonValider ;
		boutonValider = gtk_button_new_with_label("Valider") ;
		gtk_grid_attach(GTK_GRID (grilleCreation), boutonValider, 1, 8, 5, 1) ;
		g_signal_connect(boutonValider, "clicked", G_CALLBACK(afficherNotes), ficheSignal) ;
	}
}

void verificationDropDown(GtkWidget *objet, GParamSpec *pspec, gpointer user_data)
{
	StructFicheSignal *ficheSignal = (StructFicheSignal*)user_data ;
	StructFicheJoueur *ficheJoueur = (StructFicheJoueur*)ficheSignal->ficheJoueur ;
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)ficheSignal->ficheCoureur ;
	GtkWidget *grilleCreation = (GtkWidget*)ficheSignal->grilleCreation ;
	
	printf("%s NOM AP\n", ficheSignal->ficheCoureur->nom) ;
	
	//On vérifie que les courses ne soient pas en doublon.
	
	GObject *courseSelec1 = gtk_drop_down_get_selected_item(ficheJoueur->course1) ;
	GObject *courseSelec2 = gtk_drop_down_get_selected_item(ficheJoueur->course2) ;
	GObject *courseSelec3 = gtk_drop_down_get_selected_item(ficheJoueur->course3) ;
	
	//Pour cela, on transforme les GObject en char[].
	
	if(courseSelec1)
	{
		const char *stringCourse1 = gtk_string_object_get_string(GTK_STRING_OBJECT(courseSelec1)) ;
		size_t long1 = strlen(stringCourse1) ;
		memset(ficheCoureur->course1, 0, 200) ;
		strncpy(ficheCoureur->course1, stringCourse1, long1 + 1) ;
	}
	if(courseSelec2)
	{
		const char *stringCourse2 = gtk_string_object_get_string(GTK_STRING_OBJECT(courseSelec2)) ;
		size_t long2 = strlen(stringCourse2) ;
		memset(ficheCoureur->course2, 0, 200) ;
		strncpy(ficheCoureur->course2, stringCourse2, long2 + 1) ;
	}
	if(courseSelec3)
	{
		const char *stringCourse3 = gtk_string_object_get_string(GTK_STRING_OBJECT(courseSelec3)) ;
		size_t long3 = strlen(stringCourse3) ;
		memset(ficheCoureur->course3, 0, 200) ;
		strncpy(ficheCoureur->course3, stringCourse3, long3 + 1) ;
	}
	
	//Si une comparaison renvoie 0 (même tableau de char deux fois), on affiche une erreur, car on souhaite que l'utilisateur choisisse trois courses.
	if (strcmp(ficheCoureur->course1, ficheCoureur->course2) == 0 || strcmp(ficheCoureur->course2, ficheCoureur->course3) == 0 || strcmp(ficheCoureur->course1, ficheCoureur->course3) == 0)
	{
		GtkWidget *erreurCourses ;
		printf("Courses invalides : choisis-en trois différentes.\n") ;
		erreurCourses = gtk_label_new("Courses invalides : choisis-en trois différentes.") ;
		gtk_grid_attach(GTK_GRID(grilleCreation), erreurCourses, 10, 2, 2, 1) ;
		dropDownOK = 0 ;
	}
	else
	{
		g_print("Validation.\n%s\n%s\n%s\n", ficheCoureur->course1, ficheCoureur->course2, ficheCoureur->course3) ;
		GtkWidget *validationCourses ;
		printf("Courses valides : trois courses différentes ont été choisies.\n") ;
		validationCourses = gtk_label_new("Courses valides : trois courses différentes ont été choisies.") ;
		gtk_grid_attach(GTK_GRID(grilleCreation), validationCourses, 10, 2, 2, 1) ;
		dropDownOK = 1 ;
	}
	
	GObject *pays = gtk_drop_down_get_selected_item(ficheJoueur->pays) ;
	
	if(pays)
	{
		const char *stringPays = gtk_string_object_get_string(GTK_STRING_OBJECT(pays)) ;
		size_t long4 = strlen(stringPays) ;
		memset(ficheCoureur->pays, 0, 100) ;
		strncpy(ficheCoureur->pays, stringPays, long4 + 1) ;
	}
	
	//À ce stade, on a vérifié les données potentiellement problématiques (taille, âge, courses). On part du principe que le reste est valide.
	
	int compteur ;
	
	ficheCoureur->principal = gtk_drop_down_get_selected(ficheJoueur->principal) ;
	ficheCoureur->secondaire = gtk_drop_down_get_selected(ficheJoueur->secondaire) ;
	
	g_print("Principal : %d.", ficheCoureur->principal) ;
	g_print("Secondaire : %d.", ficheCoureur->secondaire) ;
	
	ficheCoureur->style = calculStyle(ficheCoureur->principal, ficheCoureur->secondaire, ficheCoureur->nom) ; //En fonction du style primaire et du style secondaire, détermine un code combinant ces deux paramètres. Il est utile pour chercher dans le fichier idoine les notes maximales attribuéer défaut à la combinaisons de styles désirée.

	for (compteur = 0 ; compteur < 14 ; compteur ++)
	{
		char *noteAfficher ;
		noteAfficher = g_malloc(8) ;
		ficheCoureur->notes[compteur] = determinerNotesMax(ficheCoureur->style, compteur) ;
		GtkWidget *texteCarac ;
		GtkWidget *texteNote ;

		texteCarac = gtk_label_new(abbreviations[compteur]) ;
		gtk_grid_attach(GTK_GRID (grilleCreation), texteCarac, 10, (4 + compteur), 1, 1) ;
		
		sprintf(noteAfficher, "%d", ficheCoureur->notes[compteur]) ;
		texteNote = gtk_label_new(noteAfficher) ;
		determinerCouleurNote(texteNote) ;
		gtk_grid_attach(GTK_GRID (grilleCreation), texteNote, 12, (4 + compteur), 1, 1) ;
		g_free(noteAfficher) ;
		
		ficheCoureur->notes[compteur] = 50 ; //On initialise la valeur par défaut de chaque note.
		printf("Note actuelle : %d.\n", ficheCoureur->notes[compteur]) ;
	}
		
	GtkWidget *texteNotesMax ;
		
	texteNotesMax = gtk_label_new("Notes maximales du profil choisi") ;
	gtk_grid_attach(GTK_GRID (grilleCreation), texteNotesMax, 10, 3, 2, 1) ;

	if (editableOK == 1 && dropDownOK == 1 && dateOK == 1)
	{
		ficheCoureur->points = 200 ;
		GtkWidget *boutonValider ;
		boutonValider = gtk_button_new_with_label("Valider") ;
		gtk_grid_attach(GTK_GRID (grilleCreation), boutonValider, 1, 8, 5, 1) ;
		g_signal_connect(boutonValider, "clicked", G_CALLBACK(afficherNotes), ficheSignal) ;
	}
}

void ecrireDate(GtkWidget *calendrier, gpointer user_data)
{
	StructFicheSignal *ficheSignal = (StructFicheSignal*)user_data ;
	StructFicheJoueur *ficheJoueur = (StructFicheJoueur*)ficheSignal->ficheJoueur ;
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)ficheSignal->ficheCoureur ;

	int anneeCourante ;
	ficheCoureur->jour = gtk_calendar_get_day(GTK_CALENDAR (ficheJoueur->calendrier)) ;
	ficheCoureur->mois = (gtk_calendar_get_month(GTK_CALENDAR (ficheJoueur->calendrier))) + 1 ;
	ficheCoureur->annee = gtk_calendar_get_year(GTK_CALENDAR (ficheJoueur->calendrier)) ;
	FILE* fichier = NULL ;
	fichier = fopen("configuration", "r") ;
	int positionInitiale = 623 ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	fscanf(fichier, "%d", &anneeCourante) ;
	
	if ((ficheCoureur->annee) + 18 < anneeCourante)
	{
		dateOK = 0 ;
	}
	else
	{
		dateOK = 1 ;
	}
}

int calculStyle(int principal, int secondaire, char nom[250])
{
	int style ;
	int maximum[14] = {0} ;
	int compteur ;
	char fichierMax[255] = {0} ;
	
	FILE* fichier = NULL ;
	
	principal = (principal) * 7 ;
	style = principal + secondaire ;
	sprintf(fichierMax, "%s_max", nom) ;
	fichier = fopen(fichierMax, "w+") ;
	if (fichier == NULL)
	{
		printf("Impossible d'ouvrir le fichier %s en %scriture. Dans creation.c, int calculStyle.\n", fichierMax, é) ;
		perror("Erreur.\n") ;
		exit(EXIT_FAILURE) ;
	}
	fclose(fichier) ;

	for (compteur = 0 ; compteur < 14 ; compteur ++)
	{
		fichier = fopen(fichierMax, "a") ;
		if (fichier != NULL)
		{
			maximum[compteur] = determinerNotesMax(style, compteur) ;
			fprintf(fichier, "%d\n", maximum[compteur]) ;
			fclose(fichier) ;
		}
		else
		{
			printf("Erreur lors de l'%scriture du maximum %d.\n", é, compteur + 1) ;
			perror("Erreur.\n") ;
			exit(EXIT_FAILURE) ;
		}
	}
	return style ;
}
