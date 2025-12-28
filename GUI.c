GListStore *courses ;
GListStore *pays ;

GtkWidget *pile ;
GtkWidget *fenetreMenu ;
GtkWidget *grilleMenu ;
GtkApplication *PCM_Evolution ;
int existenceFenetre = 0 ;

void initialisationFenetre (GtkApplication* PCM_Evolution, gpointer user_data)
{		
	(void)user_data ; //Faire taire le compilateur.

	GtkWidget *texteBienvenue ;
	GtkWidget *boutonNouvelleFiche ;
	GtkWidget *boutonAncienneFiche ;
	GtkWidget *boutonQuitter ;
	
	if (existenceFenetre == 0)
	{
		fenetreMenu = gtk_application_window_new (PCM_Evolution) ;
		grilleMenu = gtk_grid_new() ;
	}
	
	gtk_window_set_child(GTK_WINDOW (fenetreMenu), grilleMenu) ;
	
	existenceFenetre = 1 ;
	
	GtkCssProvider *cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_file (cssProvider, g_file_new_for_path ("style.css"));
	gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER) ;
	
	gtk_window_set_title (GTK_WINDOW (fenetreMenu), "PCM Évolution") ;
	gtk_window_set_default_size (GTK_WINDOW (fenetreMenu), 800, 600) ;
	
	texteBienvenue = gtk_label_new("Bienvenue dans PCM Évolution.\nMenu principal de l'application :\n") ;
	
	boutonNouvelleFiche = gtk_button_new_with_label("Nouvelle fiche") ;
	boutonAncienneFiche = gtk_button_new_with_label("Modifier une fiche existante") ;
	boutonQuitter = gtk_button_new_with_label("Quitter PCM Évolution") ;
	
	gtk_grid_attach(GTK_GRID (grilleMenu), texteBienvenue, 0, 0, 5, 1) ;
	gtk_grid_attach(GTK_GRID (grilleMenu), boutonNouvelleFiche, 0, 5, 10, 5) ;
	gtk_grid_attach(GTK_GRID (grilleMenu), boutonAncienneFiche, 0, 10, 10, 5) ;
	gtk_grid_attach(GTK_GRID (grilleMenu), boutonQuitter, 0, 20, 10, 5) ;
	
	g_assert(G_IS_APPLICATION (PCM_Evolution)) ;
	
	g_signal_connect(boutonNouvelleFiche, "clicked", G_CALLBACK(fenetreNouvelleFiche), NULL) ;
	g_signal_connect(boutonAncienneFiche, "clicked", G_CALLBACK(demandeNomDeFichier), NULL) ;
	g_signal_connect(boutonQuitter, "clicked", G_CALLBACK(exit), NULL) ;
	
	gtk_window_present (GTK_WINDOW (fenetreMenu)) ;
}

void fenetreNouvelleFiche(GtkApplication* PCM_Evolution, gpointer user_data)
{
	GtkWidget *grilleNouveau ;
	GtkWidget *textePresentation ;
	GtkWidget *texteNomDeFichier ;	
	GtkWidget *boutonValider ;
	GtkWidget *boutonAnnuler ;
	
	StructFicheSignal *ficheSignal ;
	ficheSignal = malloc(sizeof(StructFicheSignal)) ;
	
	StructFicheCoureur *ficheCoureur ;
	ficheCoureur = malloc(sizeof(StructFicheCoureur)) ;
	ficheSignal->ficheCoureur = ficheCoureur ;
	
	GtkWidget *fenetrePrincipale = gtk_window_new() ;
	ficheSignal->fenetrePrincipale = GTK_WIDGET(fenetrePrincipale) ;
	grilleNouveau = gtk_grid_new() ;
	pile = gtk_stack_new() ;
	
	gtk_window_set_child(GTK_WINDOW (fenetrePrincipale), pile) ;	
	gtk_stack_add_named(GTK_STACK (pile), grilleNouveau, "Nouveau coureur") ;	
	
	textePresentation = gtk_label_new("Bienvenue dans la création de fiche.") ;
	texteNomDeFichier = gtk_label_new("Nom de fichier") ;
	ficheSignal->champNomDeFichier = gtk_editable_label_new ("Entre ton prénom suivi de ton nom.") ;
	boutonValider = gtk_button_new_with_label("Valider") ;
	boutonAnnuler = gtk_button_new_with_label("Annuler") ;
	
	gtk_grid_attach(GTK_GRID (grilleNouveau), textePresentation, 0, 0, 10, 1) ;
	gtk_grid_attach(GTK_GRID (grilleNouveau), texteNomDeFichier, 0, 1, 5, 1) ;
	gtk_grid_attach(GTK_GRID (grilleNouveau), ficheSignal->champNomDeFichier, 7, 1, 5, 1) ;
	gtk_grid_attach(GTK_GRID (grilleNouveau), boutonValider, 7, 2, 5, 1) ;
	gtk_grid_attach(GTK_GRID (grilleNouveau), boutonAnnuler, 0, 2, 5, 1) ;
	
	g_signal_connect(boutonValider, "clicked", G_CALLBACK(verificationExistanceDuFichier), ficheSignal) ;
	g_signal_connect(boutonAnnuler, "clicked", G_CALLBACK(annuler), GTK_WINDOW(fenetrePrincipale)) ;
	
	gtk_stack_set_visible_child_name (GTK_STACK (pile), "Nouveau coureur") ;
	gtk_window_present (GTK_WINDOW (fenetrePrincipale)) ;
}

void initialisationCoureur(GtkWidget *boutonNouvelleFiche, gpointer user_data)
{
	//Les éléments interactifs qui doivent être transmis au signal de validation sont définis dans PCM_Évolution.h
	StructFicheSignal *ficheSignal = (StructFicheSignal*)user_data ;
	StructFicheJoueur *ficheJoueur = (StructFicheJoueur*)ficheSignal->ficheJoueur ;
	
	ficheJoueur = malloc(sizeof(StructFicheJoueur)) ;
	ficheSignal->ficheJoueur = ficheJoueur ;
	
	GtkWidget *texteTaille ;
	GtkWidget *textePoids ;
	GtkWidget *textePrincipal ;
	GtkWidget *texteSecondaire ;
	GtkWidget *texteCourse1 ;
	GtkWidget *texteCourse2 ;
	GtkWidget *texteCourse3 ;
	GtkWidget *textePays ;
	GtkWidget *texteDateNaissance ;
	GtkWidget *boutonAnnuler ;
	
	if (ficheJoueur == NULL)
	{
		g_print("Erreur d'allocation mémoire dans GUI.c") ;
		exit(0) ;
	}

	GtkWidget *grilleCreation = gtk_grid_new() ;
	ficheSignal->grilleCreation = GTK_WIDGET(grilleCreation) ;

	texteTaille = gtk_label_new("Taille") ;
	ficheJoueur->taille = gtk_entry_new() ;
	gtk_editable_set_text(GTK_EDITABLE(ficheJoueur->taille), "Entre 150 et 200 (cm).") ;
	
	textePoids = gtk_label_new("Poids") ;
	ficheJoueur->poids = gtk_entry_new() ;
	gtk_editable_set_text(GTK_EDITABLE(ficheJoueur->poids), "Entre 50 et 100 (kg).") ;

	int anneeCourante ;
	FILE* fichier = NULL ;
	fichier = fopen("configuration", "r") ;
	int positionInitiale = 623 ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	fscanf(fichier, "%d", &anneeCourante) ;

	ficheJoueur->calendrier = gtk_calendar_new() ;
	gtk_calendar_set_year(GTK_CALENDAR (ficheJoueur->calendrier), (anneeCourante - 18)) ;
	gtk_calendar_set_month(GTK_CALENDAR (ficheJoueur->calendrier), 0) ;
	gtk_calendar_set_day(GTK_CALENDAR (ficheJoueur->calendrier), 1) ;
	
	textePrincipal = gtk_label_new("Spécialité 1") ;
	ficheJoueur->principal = GTK_DROP_DOWN(gtk_drop_down_new_from_strings(types)) ;
	texteSecondaire = gtk_label_new("Spécialité 2") ;
	ficheJoueur->secondaire = GTK_DROP_DOWN(gtk_drop_down_new_from_strings(types)) ;

	texteCourse1 = gtk_label_new("Course favorite n°1") ;
	ficheJoueur->course1 = GTK_DROP_DOWN(gtk_drop_down_new(G_LIST_MODEL(courses), NULL)) ;
	gtk_drop_down_get_enable_search(ficheJoueur->course1) ;
	texteCourse2 = gtk_label_new("Course favorite n°2") ;
	ficheJoueur->course2 = GTK_DROP_DOWN(gtk_drop_down_new(G_LIST_MODEL(courses), NULL)) ;
	gtk_drop_down_get_enable_search(ficheJoueur->course2) ;
	texteCourse3 = gtk_label_new("Course favorite n°3") ;
	ficheJoueur->course3 = GTK_DROP_DOWN(gtk_drop_down_new(G_LIST_MODEL(courses), NULL)) ;
	gtk_drop_down_get_enable_search(ficheJoueur->course3) ;
	
	//On passe trois fois la liste dans des objets différents, il faut donc augmenter son compteur de références pour que le signal de destruction de la fenêtre n'essaie pas d'unref un objet détruit.
	//En outre, on souhaite qu'une référence subsite après la destruction de la fenêtre, pour une utilisation future.
	g_object_ref(courses) ;
	g_object_ref(courses) ;
	g_object_ref(courses) ;
	
	g_object_ref(pays) ;
	
	textePays = gtk_label_new("Nationalité") ;
	ficheJoueur->pays = GTK_DROP_DOWN(gtk_drop_down_new(G_LIST_MODEL(pays), NULL)) ;
	gtk_drop_down_get_enable_search(ficheJoueur->pays) ;

	texteDateNaissance = gtk_label_new("Date de naissance") ;

	boutonAnnuler = gtk_button_new_with_label("Annuler") ;
	
	gtk_stack_add_named(GTK_STACK (pile), ficheSignal->grilleCreation, "Création de coureur") ;	
	
	//On fournit une date de naissance par défaut calquée sur l'année de départ de la partie fournie par le fichier configuration.
	ficheSignal->ficheCoureur->jour = 1 ;
	ficheSignal->ficheCoureur->mois = 1 ;
	ficheSignal->ficheCoureur->annee = (anneeCourante - 18) ;
	
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), texteTaille, 0, 0, 2, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), GTK_WIDGET(ficheJoueur->taille), 5, 0, 1, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), textePoids, 0, 1, 5, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), GTK_WIDGET(ficheJoueur->poids), 5, 1, 1, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), textePrincipal, 0, 2, 5, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), GTK_WIDGET(ficheJoueur->principal), 5, 2, 1, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), texteSecondaire, 0, 3, 5, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), GTK_WIDGET(ficheJoueur->secondaire), 5, 3, 1, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), texteCourse1, 0, 4, 5, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), GTK_WIDGET(ficheJoueur->course1), 5, 4, 1, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), texteCourse2, 0, 5, 5, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), GTK_WIDGET(ficheJoueur->course2), 5, 5, 1, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), texteCourse3, 0, 6, 5, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), GTK_WIDGET(ficheJoueur->course3), 5, 6, 1, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), textePays, 0, 7, 5, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), GTK_WIDGET(ficheJoueur->pays), 5, 7, 1, 1) ;

	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), boutonAnnuler, 0, 8, 1, 1) ;

	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), texteDateNaissance, 0, 9, 1, 1) ;
	gtk_grid_attach(GTK_GRID (ficheSignal->grilleCreation), GTK_WIDGET(ficheJoueur->calendrier), 0, 10, 1, 10) ;
	g_signal_connect(ficheJoueur->taille, "changed", G_CALLBACK(verificationEditable), ficheSignal) ;
	g_signal_connect(ficheJoueur->poids, "changed", G_CALLBACK(verificationEditable), ficheSignal) ;
	g_signal_connect(ficheJoueur->calendrier, "day-selected", G_CALLBACK(ecrireDate), ficheSignal) ;
	g_signal_connect(ficheJoueur->principal, "notify::selected-item", G_CALLBACK(verificationDropDown), ficheSignal) ;
	g_signal_connect(ficheJoueur->secondaire, "notify::selected-item", G_CALLBACK(verificationDropDown), ficheSignal) ;
	g_signal_connect(ficheJoueur->course1, "notify::selected-item", G_CALLBACK(verificationDropDown), ficheSignal) ;
	g_signal_connect(ficheJoueur->course2, "notify::selected-item", G_CALLBACK(verificationDropDown), ficheSignal) ;
	g_signal_connect(ficheJoueur->course3, "notify::selected-item", G_CALLBACK(verificationDropDown), ficheSignal) ;
	g_signal_connect(ficheJoueur->pays, "notify::selected-item", G_CALLBACK(verificationDropDown), ficheSignal) ;
	g_signal_connect(boutonAnnuler, "clicked", G_CALLBACK(annuler), ficheSignal->fenetrePrincipale) ;

	gtk_stack_set_visible_child_name (GTK_STACK (pile), "Création de coureur") ;
}

int verificationExistanceDuFichier(GtkWidget *boutonValider, gpointer user_data)
{
	StructFicheSignal *ficheSignal = (StructFicheSignal*)user_data ;
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)ficheSignal->ficheCoureur ;
	
	const gchar *nomFichier = gtk_editable_get_text(GTK_EDITABLE(ficheSignal->champNomDeFichier)) ;
		
	strcpy(ficheCoureur->nom, nomFichier) ;

	FILE* fichier = NULL ;
	fichier = fopen(ficheCoureur->nom, "r") ;

	if (fichier != NULL)
	{
		fclose(fichier) ;
		GtkWidget *grilleDialogue ;
		
		GtkWidget *question ;
		GtkWidget *oui ;
		GtkWidget *non ;
		
		grilleDialogue = gtk_grid_new() ;
		
		if(gtk_stack_get_child_by_name(GTK_STACK (pile), "Supprimer le fichier ?") == NULL)
		{
			gtk_stack_add_named(GTK_STACK (pile), grilleDialogue, "Supprimer le fichier ?") ;
		}
		
		question = gtk_label_new("Voulez-vous supprimer le fichier portant déjà ce nom ?") ;
		oui = gtk_button_new_with_label("Oui") ;
		non = gtk_button_new_with_label("Non") ;
		
		gtk_grid_attach(GTK_GRID(grilleDialogue), question, 0, 0, 5, 1) ;
		gtk_grid_attach(GTK_GRID(grilleDialogue), oui, 0, 1, 1, 1) ;
		gtk_grid_attach(GTK_GRID(grilleDialogue), non, 2, 1, 1, 1) ;
		
		g_signal_connect(oui, "clicked", G_CALLBACK(suppressionCreation), ficheSignal) ;
		g_signal_connect(non, "clicked", G_CALLBACK(annuler), ficheSignal->fenetrePrincipale) ;
		
		gtk_stack_set_visible_child_name (GTK_STACK (pile), "Supprimer le fichier ?") ;
		remplirJournal("Fiche du même nom existante.") ;
	}
	else
	{
		remplirJournal("Fiche inexistante. Création.") ;
		initialisationCoureur(NULL, ficheSignal) ;
	}	
	return 0 ;
}

void determinerCouleurNote(GtkWidget *pointeur)
{
	GtkWidget *note = (GtkWidget*)pointeur ;
	const gchar *noteTexte = gtk_label_get_text(GTK_LABEL (note)) ;
	char *charFin ;
	long noteNombre = strtol(noteTexte, &charFin, 10) ;
	
	if (noteNombre < 70)
	{
		gtk_widget_add_css_class(note, "note_basse") ;
	}
	else if (noteNombre < 74)
	{
		gtk_widget_add_css_class(note, "note_inter") ;
	}
	else if (noteNombre < 78)
	{
		gtk_widget_add_css_class(note, "note_haute") ;
	}
	else if (noteNombre < 83)
	{
		gtk_widget_add_css_class(note, "note_extreme") ;
	}
	else
	{
		gtk_widget_add_css_class(note, "note_max") ;
	}
}

void demandeNomDeFichier ()
{
	GtkWidget *demandeNom ;
	GtkWidget *boutonValider ;
	GtkWidget *boutonAnnuler ;
	GtkWidget *grilleChercherFiche ;
	GtkWidget *fenetrePrincipale ;
	
	fenetrePrincipale = gtk_window_new() ;
	grilleChercherFiche = gtk_grid_new() ;
	
	StructFicheSignal *ficheSignal = malloc(sizeof(StructFicheSignal)) ;
	StructFicheCoureur *ficheCoureur = malloc(sizeof(StructFicheCoureur));
	ficheSignal->ficheCoureur = ficheCoureur ;
	
	ficheSignal->fenetrePrincipale = fenetrePrincipale ;
	
	pile = gtk_stack_new() ;
	gtk_window_set_child(GTK_WINDOW (fenetrePrincipale), pile) ;	
	gtk_stack_add_named(GTK_STACK (pile), grilleChercherFiche, "Chercher une fiche") ;	
	
	demandeNom = gtk_label_new("Entre le nom de ton fichier") ;
	ficheSignal->champNomDeFichier = gtk_editable_label_new("ici") ;
	
	boutonValider = gtk_button_new_with_label("Valider") ;
	boutonAnnuler = gtk_button_new_with_label("Annuler") ;
	
	gtk_grid_attach(GTK_GRID (grilleChercherFiche), demandeNom, 0, 0, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleChercherFiche), ficheSignal->champNomDeFichier, 1, 0, 1, 1) ;
	
	gtk_grid_attach(GTK_GRID (grilleChercherFiche), boutonValider, 1, 1, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleChercherFiche), boutonAnnuler, 0, 1, 1, 1) ;
	
	g_signal_connect(boutonValider, "clicked", G_CALLBACK(trouverFichier), ficheSignal) ;
	g_signal_connect(boutonAnnuler, "clicked", G_CALLBACK(annuler), fenetrePrincipale) ;
	
	gtk_stack_set_visible_child_name (GTK_STACK (pile), "Chercher une fiche") ;
	gtk_window_present (GTK_WINDOW (fenetrePrincipale)) ;
	g_main_context_iteration(NULL, FALSE) ;
}

void annuler(GtkWidget *boutonAnnuler, gpointer user_data)
{
	GtkWidget* fenetre = (GtkWidget*)user_data ;
	gtk_window_destroy(GTK_WINDOW(fenetre)) ;
	initialisationFenetre (PCM_Evolution, NULL) ;
}
