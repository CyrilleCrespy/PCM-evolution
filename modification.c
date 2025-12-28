void trouverFichier (GtkWidget *boutonValider, gpointer user_data)
{
	StructFicheSignal *ficheSignal = (StructFicheSignal*)user_data ;
	StructFicheCoureur *ficheCoureur = ficheSignal->ficheCoureur ;
	GtkWidget *champNom = (GtkWidget*)ficheSignal->champNomDeFichier ;
	GtkWidget *grilleDialogue ;
	const char *nomFichier = gtk_editable_get_text(GTK_EDITABLE(champNom)) ;
	strcpy(ficheCoureur->nom, nomFichier) ;
	char message[500] ;

	FILE* fichier = NULL ;
	fichier = fopen(nomFichier, "r") ;
	g_print("Fichier : %s\n", nomFichier) ;

	if (fichier == NULL) //Le fichier demandé par l'utilisateur n'existe pas (il doit être dans le dossier courant).
	{
		GtkWidget *grilleExiste ;
		grilleDialogue = gtk_grid_new() ;
		
		if(gtk_stack_get_child_by_name(GTK_STACK (pile), "Le fichier existe") == NULL)
		{
			gtk_stack_add_named(GTK_STACK (pile), grilleDialogue, "Le fichier existe") ;
		}
		
		GtkWidget *messageErreur ;
		
		messageErreur = gtk_label_new("Erreur, fichier inexistant ou inacessible (ouverture impossible).") ;
		gtk_grid_attach(GTK_GRID(grilleDialogue), messageErreur, 0, 0, 5, 1) ;
	}
	
	else //L'ouverture du fichier est un succès, on peut passer à la suite.
	{
		fclose(fichier) ;
		g_print("Fichier lu avec succès.\n") ;
		chargerCoureur(ficheSignal) ;
	}
}

/*La fiche du coureur existe (on l'a vérifié dans trouverFichier), et on charge les informations inscrites dans le fichier directement
dans la structure StructFicheCoureur.*/

void chargerCoureur(gpointer user_data)
{	
	StructFicheSignal *ficheSignal = (StructFicheSignal*)user_data ;
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)ficheSignal->ficheCoureur ;
	ficheCoureur->style = 0 ;
	
	int compteur ;
	char messageJournal[100] ;
	int fichierOK ;

	char cpe[30] ;
	sprintf(cpe, "Courses par éstapes") ;

	int notesInitiales[14] = {0} ;

	FILE *fichier = NULL ;
	fichier = fopen(ficheCoureur->nom, "r") ;
	fscanf(fichier, "%d %*s %*s %d %*s %*s %d", &ficheCoureur->style, &ficheCoureur->principal, &ficheCoureur->secondaire) ;
	fscanf(fichier, "%d %*s", &ficheCoureur->taille) ;
	fscanf(fichier, "%d %*s", &ficheCoureur->poids) ;
	fscanf(fichier, "%d", &ficheCoureur->jour) ;
	fgetc(fichier) ; //Pour ignorer le / de la date
	fscanf(fichier, "%d", &ficheCoureur->mois) ;
	fgetc(fichier) ;
	fscanf(fichier, "%d %*s %*s %*s", &ficheCoureur->annee) ;
	fscanf(fichier, "%s %*s %*s %*s", &ficheCoureur->course1[0]) ;
	fscanf(fichier, "%s %*s %*s %*s", &ficheCoureur->course2[0]) ;
	fscanf(fichier, "%s %*s %*s %*s", &ficheCoureur->course3[0]) ;
	fscanf(fichier, "%s %*s", &ficheCoureur->pays[0]) ;
	fscanf(fichier, "%d %*s", &ficheCoureur->points) ;
	fscanf(fichier, "%d %*s %*s", &ficheCoureur->pointsDepenses) ;
	fscanf(fichier, "%d %*s", &ficheCoureur->potentiel) ;
	
	for(compteur = 0 ; compteur < 14 ; compteur ++)
	{
		fscanf(fichier, "%d %*s %*s %*s", &ficheCoureur->notes[compteur]) ;
	}
	
	fichierOK = verifierDonnees(ficheCoureur) ;
	if (fichierOK == 1)
	{
		remplirJournal("Fichier de sauvegarde OK.") ;
	}
	else
	{
		remplirJournal("Fichier de sauvegarde mal enregistré. Restauration.") ;
		restaurerSauvegarde(ficheCoureur->nom) ;
	}
	
	if (fichier != NULL)
	{
		fclose(fichier) ;
	}
	
	afficherNotes(NULL, ficheSignal) ;
}

void afficherNotes(GtkWidget *objet, gpointer user_data)
{
	GtkWidget *grilleModif ;
	grilleModif = gtk_grid_new() ;
	StructFicheSignal *ficheSignal = (StructFicheSignal*)user_data ;
	StructFicheCoureur *ficheCoureur = ficheSignal->ficheCoureur ;

	calculStyle(ficheCoureur->principal, ficheCoureur->secondaire, ficheCoureur->nom) ;
	
	gtk_stack_add_named(GTK_STACK (pile), grilleModif, "Modification de coureur") ;	
	
	int compteur ;
	FILE* fichierMax = NULL ;
	char *nomFichierMax = malloc(strlen(ficheCoureur->nom) + sizeof(char) * 5);
	strcpy(nomFichierMax, ficheCoureur->nom) ;
	strcat(nomFichierMax, "_max") ;
	fichierMax = fopen(nomFichierMax, "r") ;

	for(compteur = 0 ; compteur < 14 ; compteur ++)
	{
		fscanf(fichierMax, "%d", &ficheCoureur->notesMax[compteur]) ;
	}
	
	fclose(fichierMax) ;
	enregistrer(ficheCoureur) ;
		
	GtkWidget *texteFiche ;
	GtkWidget *texteTaille ;
	GtkWidget *textePoids ;
	GtkWidget *texteDateNaissance ;
	GtkWidget *textePrincipal ;
	GtkWidget *texteSecondaire ;
	GtkWidget *texteCourse1 ;
	GtkWidget *texteCourse2 ;
	GtkWidget *texteCourse3 ;
	GtkWidget *textePays ;
		
	GtkWidget *afficherNom ;
	GtkWidget *afficherTaille ;
	GtkWidget *afficherPoids ;
	GtkWidget *afficherDateNaissance ;
	GtkWidget *afficherPrincipal ;
	GtkWidget *afficherSecondaire ;	
	GtkWidget *afficherCourse1 ;
	GtkWidget *afficherCourse2 ;
	GtkWidget *afficherCourse3 ;
	GtkWidget *afficherPays ;
	GtkWidget *afficherPoints ;
	GtkWidget *afficherPotentiel ;
	GtkWidget *textePoints ;
	GtkWidget *textePotentiel ;
	GtkWidget *texteAjoutPoints ;
	GtkWidget *champAjoutPoints ;
	GtkWidget *boutonPoints ;
	GtkWidget *quitter ;
	GtkWidget *boutonAnnuler ;

	texteFiche = gtk_label_new("Fiche du coureur") ;
	texteTaille = gtk_label_new("Taille") ;
	textePoids = gtk_label_new("Poids") ;
	texteDateNaissance = gtk_label_new("Date de naissance") ;
	textePrincipal = gtk_label_new("Spécialité 1") ;
	texteSecondaire = gtk_label_new("Spécialité 2") ;
	texteCourse1 = gtk_label_new("Course favorite n°1") ;
	texteCourse2 = gtk_label_new("Course favorite n°2") ;
	texteCourse3 = gtk_label_new("Course favorite n°3") ;
	textePays = gtk_label_new("Nationalité") ;
	textePotentiel = gtk_label_new("Potentiel") ;

	textePoints = gtk_label_new("Points restants : ") ;

	afficherNom = gtk_label_new(ficheCoureur->nom) ;

	//Les int ne pouvant pas être affichés directement par gtk_label_new, on les convertit en gchar.

	char *taille ;
	taille = (char *)malloc(3 * (sizeof(char))) ;
	sprintf(taille, "%d", ficheCoureur->taille) ;
	afficherTaille = gtk_label_new(taille) ;

	char *poids ;
	poids = (char *)malloc(3 * (sizeof(char))) ;
	sprintf(poids, "%d", ficheCoureur->poids) ;
	afficherPoids = gtk_label_new(poids) ;
		
	char *dateNaissance ;
	dateNaissance = (char *)malloc(20 * (sizeof(char))) ;
	sprintf(dateNaissance, "%d/%d/%d", ficheCoureur->jour, ficheCoureur->mois, ficheCoureur->annee) ;
	afficherDateNaissance = gtk_label_new(dateNaissance) ;

	char *principal ;
	principal = (char *)malloc(100 * sizeof(char)) ;
	sprintf(principal, "%s", types[ficheCoureur->principal]) ;
	afficherPrincipal = gtk_label_new(principal) ;

	char *secondaire ;
	secondaire = (char *)malloc(100 * sizeof(char)) ;
	sprintf(secondaire, "%s", types[ficheCoureur->secondaire]) ;
	afficherSecondaire = gtk_label_new(secondaire) ;

	char *nombrePoints ;
	nombrePoints = (char *)malloc(6 * sizeof(char)) ;
	sprintf(nombrePoints, "%d", ficheCoureur->points) ;
	afficherPoints = gtk_label_new(nombrePoints) ;

	char *potentiel ;
	potentiel = (char *)malloc(2 * sizeof(char)) ;
	sprintf(potentiel, "%d", ficheCoureur->potentiel) ;
	afficherPotentiel = gtk_label_new(potentiel) ;

	afficherCourse1 = gtk_label_new(ficheCoureur->course1) ;
	afficherCourse2 = gtk_label_new(ficheCoureur->course2) ;
	afficherCourse3 = gtk_label_new(ficheCoureur->course3) ;
	afficherPays = gtk_label_new(ficheCoureur->pays) ;

	quitter = gtk_button_new_with_label("Quitter") ;
	boutonAnnuler = gtk_button_new_with_label("Menu principal") ;
	texteAjoutPoints = gtk_label_new("Ajout de points") ;
	champAjoutPoints = gtk_editable_label_new("0") ;
	boutonPoints = gtk_button_new_with_label("Ajouter les points") ;

	gtk_grid_attach(GTK_GRID (grilleModif), texteFiche, 0, 0, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), texteTaille, 0, 1, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), textePoids, 0, 2, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), texteDateNaissance, 0, 3, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), textePrincipal, 0, 4, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), texteSecondaire, 0, 5, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), texteCourse1, 0, 6, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), texteCourse2, 0, 7, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), texteCourse3, 0, 8, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), textePays, 0, 9, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), textePoints, 0, 10, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherPoints, 1, 10, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), texteAjoutPoints, 0, 11, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), GTK_WIDGET(champAjoutPoints), 1, 11, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), GTK_WIDGET(boutonPoints), 0, 12, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), textePotentiel, 0, 13, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherPotentiel, 1, 13, 1, 1) ;

	gtk_grid_attach(GTK_GRID (grilleModif), afficherNom, 1, 0, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherTaille, 1, 1, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherPoids, 1, 2, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherDateNaissance, 1, 3, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherPrincipal, 1, 4, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherSecondaire, 1, 5, 1, 1) ;

	gtk_grid_attach(GTK_GRID (grilleModif), afficherCourse1, 1, 6, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherCourse2, 1, 7, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherCourse3, 1, 8, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherPays, 1, 9, 1, 1) ;

	gtk_grid_attach(GTK_GRID (grilleModif), GTK_WIDGET(quitter), 0, 14, 1, 1) ;
	gtk_grid_attach(GTK_GRID (grilleModif), GTK_WIDGET(boutonAnnuler), 1, 14, 1, 1) ;

	GtkWidget *boutonsMoins[14] ;
	GtkWidget *boutonsPlus[14] ;
	GtkWidget *textesCarac[14] ;
	GtkWidget *textesNotes[14] ;
	StructFicheCalcul *ficheCopie[14] ;
	for (compteur = 0 ; compteur < 14 ; compteur ++)
	{
		ficheCopie[compteur] = malloc(sizeof(StructFicheCalcul)) ;
	}
	
	for (compteur = 0 ; compteur < 14 ; compteur ++) //Chaque ligne associée à une note est reconstruite dynamiquement à chaque change de l'utilisateur.
	{
		ficheCopie[compteur]->originel = ficheCoureur ;
		ficheCopie[compteur]->selection = compteur ;
		ficheCopie[compteur]->grilleModif = grilleModif ;

		char *noteAfficher ;
		noteAfficher = g_malloc(8) ;
		sprintf(noteAfficher, "%d", ficheCoureur->notes[compteur]) ;
		textesCarac[compteur] = gtk_label_new(abbreviations[compteur]) ;
		textesNotes[compteur] = gtk_label_new(noteAfficher) ;
		boutonsMoins[compteur] = gtk_button_new_with_label("-") ;
		boutonsPlus[compteur] = gtk_button_new_with_label("+") ;
		
		determinerCouleurNote(textesNotes[compteur]) ;
		
		gtk_grid_attach(GTK_GRID (grilleModif), GTK_WIDGET(textesCarac[compteur]), 2, compteur, 1, 1) ;
		gtk_grid_attach(GTK_GRID (grilleModif), GTK_WIDGET(boutonsMoins[compteur]), 3, compteur, 1, 1) ;
		gtk_grid_attach(GTK_GRID (grilleModif), GTK_WIDGET(textesNotes[compteur]), 4, compteur, 1, 1) ;
		gtk_grid_attach(GTK_GRID (grilleModif), GTK_WIDGET(boutonsPlus[compteur]), 5, compteur, 1, 1) ;
		
		g_signal_connect(boutonsMoins[compteur], "clicked", G_CALLBACK(calculDiminution), ficheCopie[compteur]) ;
		g_signal_connect(boutonsPlus[compteur], "clicked", G_CALLBACK(calculAugmentation), ficheCopie[compteur]) ;

		char *notePotentiel ;
		notePotentiel = g_malloc(8) ;
		sprintf(notePotentiel, "%d", ficheCoureur->notesMax[compteur]) ;
		GtkWidget *afficherPotentiel ;
		GtkWidget *boutonAjoutPotentiel ;
		
		afficherPotentiel = gtk_label_new(notePotentiel) ;
		boutonAjoutPotentiel = gtk_button_new_with_label("Augmenter le potentiel") ;
		
		determinerCouleurNote(afficherPotentiel) ;
		
		gtk_grid_attach(GTK_GRID (grilleModif), afficherPotentiel, 6, (compteur), 1, 1) ;
		gtk_grid_attach(GTK_GRID (grilleModif), boutonAjoutPotentiel, 7, (compteur), 1, 1) ;
		
		g_signal_connect(boutonAjoutPotentiel, "clicked", G_CALLBACK(determinerCoutPotentiel), ficheCopie[compteur]) ;
		
		g_free(noteAfficher) ;
	}

	SignalPoints *signalPoints ;
	signalPoints = malloc(sizeof(SignalPoints)) ;
	signalPoints->coureur = ficheCoureur ;
	signalPoints->points = champAjoutPoints ;
	signalPoints->grilleModif = grilleModif ;

	g_signal_connect(quitter, "clicked", G_CALLBACK(exit), NULL) ;
	g_signal_connect(boutonAnnuler, "clicked", G_CALLBACK(annuler), ficheSignal->fenetrePrincipale) ;
	g_signal_connect(boutonPoints, "clicked", G_CALLBACK(ajoutPoints), signalPoints) ;

	gtk_stack_set_visible_child_name (GTK_STACK (pile), "Modification de coureur") ;
	g_main_context_iteration(NULL, FALSE) ;
}
