int calculAugmentation(GtkWidget *boutonPlus, gpointer user_data)
{
	StructFicheCalcul *ficheCalcul = (StructFicheCalcul*)user_data ;
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)ficheCalcul->originel ;
	GtkWidget *grilleModif = (GtkWidget*)ficheCalcul->grilleModif ;
	int noteChoisie = (int)ficheCoureur->notes[ficheCalcul->selection] ;
	int noteMax = (int)ficheCoureur->notesMax[ficheCalcul->selection] ;

	if(noteChoisie >= noteMax || ficheCoureur->points <= 0)
	{
		printf("Augmentation impossible.\n") ;
		return 0 ;
	}
	else
	{	
		int coutEvolution ;
		int positionInitiale ;
		FILE* fichier = NULL ;
		positionInitiale = 382 + ((noteChoisie - 50) * 7) ;
		fichier = fopen("configuration", "r") ;
		fseek(fichier, positionInitiale, SEEK_SET) ;
		fscanf(fichier, "%d", &coutEvolution) ;
		fclose(fichier) ;
		if (ficheCoureur->points >= coutEvolution)
		{
			ficheCoureur->notes[ficheCalcul->selection] += 1 ;
			ficheCoureur->points = (ficheCoureur->points) - coutEvolution ;
			enregistrer(ficheCoureur) ;
		}
	}
	
	GtkWidget *afficherPoints ;
	GtkWidget *afficherMAJ ;

	char *points ;
	points = (char *)malloc(3 * (sizeof(char))) ;
	sprintf(points, "%d", ficheCoureur->points) ;
	afficherPoints = gtk_label_new(points) ;
	
	gtk_grid_attach(GTK_GRID (grilleModif), afficherPoints, 1, 10, 1, 1) ;
	
	char *noteMAJ ;
	noteMAJ = (char *)malloc(3 * (sizeof(char))) ;
	sprintf(noteMAJ, "%d", ficheCoureur->notes[ficheCalcul->selection]) ;
	afficherMAJ = gtk_label_new(noteMAJ) ;
	
	determinerCouleurNote(afficherMAJ) ;
	
	printf("%d noteChoisie\n", noteChoisie) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherMAJ, 4, ficheCalcul->selection, 1, 1) ;
	
	g_main_context_iteration(NULL, FALSE) ;
}

int calculDiminution(GtkWidget *boutonMoins, gpointer user_data)
{
	StructFicheCalcul *ficheCalcul = (StructFicheCalcul*)user_data ;
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)ficheCalcul->originel ;
	GtkWidget *grilleModif = (GtkWidget*)ficheCalcul->grilleModif ;
	int noteChoisie = (int)ficheCoureur->notes[ficheCalcul->selection] ;
	int noteMax = (int)ficheCoureur->notesMax[ficheCalcul->selection] ;

	if(noteChoisie <= 50)
	{
		printf("Diminution impossible.\n") ;
		return 0 ;
	}
	else
	{	
		int coutEvolution ;
		int positionInitiale ;
		FILE* fichier = NULL ;
		positionInitiale = 382 + (((noteChoisie - 50) * 7) - 7) ;
		fichier = fopen("configuration", "r") ;
		fseek(fichier, positionInitiale, SEEK_SET) ;
		fscanf(fichier, "%d", &coutEvolution) ;
		fclose(fichier) ;
		ficheCoureur->notes[ficheCalcul->selection] -= 1 ;
		ficheCoureur->points = (ficheCoureur->points) + coutEvolution ;
		enregistrer(ficheCoureur) ;
	}
	
	GtkWidget *afficherPoints ;
	GtkWidget *afficherMAJ ;

	char *points ;
	points = (char *)malloc(3 * (sizeof(char))) ;
	sprintf(points, "%d", ficheCoureur->points) ;
	afficherPoints = gtk_label_new(points) ;
	
	gtk_grid_attach(GTK_GRID (grilleModif), afficherPoints, 1, 10, 1, 1) ;
	
	char *noteMAJ ;
	noteMAJ = (char *)malloc(3 * (sizeof(char))) ;
	sprintf(noteMAJ, "%d", ficheCoureur->notes[ficheCalcul->selection]) ;
	afficherMAJ = gtk_label_new(noteMAJ) ;
	
	determinerCouleurNote(afficherMAJ) ;
	
	printf("%d noteChoisie\n", noteChoisie) ;
	gtk_grid_attach(GTK_GRID (grilleModif), afficherMAJ, 4, ficheCalcul->selection, 1, 1) ;
	
	g_main_context_iteration(NULL, FALSE) ;
}

void determinerCoutPotentiel(GtkWidget *objet, gpointer user_data)
{
	StructFicheCalcul *ficheCalcul = (StructFicheCalcul*)user_data ;
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)ficheCalcul->originel ;
	GtkWidget *grilleModif = (GtkWidget*)ficheCalcul->grilleModif ;
	int noteChoisie = (int)ficheCoureur->notes[ficheCalcul->selection] ;
	int noteMax = (int)ficheCoureur->notesMax[ficheCalcul->selection] ;
	int positionInitiale ;
	int cout ;
	int bonus ;
	FILE* fichier = NULL ;
	int ligne = (ficheCoureur->potentiel) - 1 ;
	g_print("%d LIGNE\n", ligne) ;
	positionInitiale = (ligne * 19) + 13 ;
	//On se place sur le bout de ligne qui correspond au coût pour augmenter le potentiel d'un point,
	//sur la ligne correspondant au potentiel initial trouvé dans la fiche coureur.
	//Coût noté sur cinq chiffres, comme 20000 pour 20 points 00005 pour points.
	fichier = fopen("configuration", "r") ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	fscanf(fichier, "%d", &cout) ;

	
	if (cout > 0 && ficheCoureur->points >= cout && ficheCoureur->potentiel < 8)
	{
		positionInitiale = 133 + ((noteChoisie - 50) * 7) + 4 ;
		fseek(fichier, positionInitiale, SEEK_SET) ;
		fscanf(fichier, "%d", &bonus) ;
		
		ficheCoureur->notesMax[ficheCalcul->selection] = ficheCoureur->notesMax[ficheCalcul->selection] + bonus ;
		ficheCoureur->points = ficheCoureur->points - cout ;
		ficheCoureur->potentiel ++ ;
		
		GtkWidget *afficherPotentiel ;
		GtkWidget *afficherPoints ;
		GtkWidget *afficherMax ;
		
		char *potentiel ;
		potentiel = (char *)malloc(2 * sizeof(char)) ;
		sprintf(potentiel, "%d", ficheCoureur->potentiel) ;
		afficherPotentiel = gtk_label_new(potentiel) ;
		gtk_grid_attach(GTK_GRID (grilleModif), afficherPotentiel, 1, 13, 1, 1) ;
		
		char *nombrePoints ;
		nombrePoints = (char *)malloc(6 * sizeof(char)) ;
		sprintf(nombrePoints, "%d", ficheCoureur->points) ;
		afficherPoints = gtk_label_new(nombrePoints) ;
		gtk_grid_attach(GTK_GRID (grilleModif), afficherPoints, 1, 10, 1, 1) ;
		
		char *notePotentiel ;
		notePotentiel = g_malloc(8) ;
		sprintf(notePotentiel, "%d", ficheCoureur->notesMax[ficheCalcul->selection]) ;
		afficherPotentiel = gtk_label_new(notePotentiel) ;
		determinerCouleurNote(afficherPotentiel) ;
		gtk_grid_attach(GTK_GRID (grilleModif), afficherPotentiel, 6, (ficheCalcul->selection), 1, 1) ;
		
		enregistrer(ficheCoureur) ;
	}
	else
	{
		g_print("Augmentation de potentiel impossible.\n") ;
		if (cout <= 0)
		{
			g_print("Coût <= 0 : la configuration interdit cette évolution.\n") ;
		}
		if (ficheCoureur->points < cout)
		{
			g_print("Pas assez de points.\n") ;
		}
		if (ficheCoureur->potentiel >=8)
		{
			g_print("Potentiel au maximum (ou invalide).\n") ;
		}
	}
	
	fclose(fichier) ;
}

void ajoutPoints(GtkWidget *objet, gpointer user_data)
{
	SignalPoints *signalPoints = (SignalPoints*)user_data ;
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)signalPoints->coureur ;
	GtkWidget *grilleModif = (GtkWidget*)signalPoints->grilleModif ;
	
	GtkWidget *ajoutPoints = (GtkWidget*)signalPoints->points ;
	
	GtkWidget *afficherPoints ;
	
	const gchar *pointsAjoutes = gtk_editable_get_text(GTK_EDITABLE(ajoutPoints)) ;
	char *charFin ;
	if (!pointsAjoutes)
	{
		pointsAjoutes = "0" ;
	}
	long ajouterPoints = strtol(pointsAjoutes, &charFin, 10) ;
	printf("%ld POINTS\n", ajouterPoints) ;
	printf("%d ACTUEL\n", ficheCoureur->points) ;
	ficheCoureur->points = ficheCoureur->points + ajouterPoints ;
	printf("%d ACTUEL\n", ficheCoureur->points) ;
	
	char *nombrePoints ;
	nombrePoints = (char *)malloc(10 * sizeof(char)) ;
	sprintf(nombrePoints, "%d", ficheCoureur->points) ;
	afficherPoints = gtk_label_new(nombrePoints) ;	
	gtk_grid_attach(GTK_GRID (grilleModif), afficherPoints, 1, 10, 1, 1) ;
	enregistrer(ficheCoureur) ;
	g_main_context_iteration(NULL, FALSE) ;
}
