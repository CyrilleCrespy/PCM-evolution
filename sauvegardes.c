void enregistrer(StructFicheCoureur* pointeur)
{	
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)pointeur ;
	FILE* fichier = NULL ;
	printf("Tentative d'ouverture de '%s.\n", ficheCoureur->nom) ;
	fichier = fopen(ficheCoureur->nom, "w+") ;

	if (remove(ficheCoureur->nom) == 0) //Suppression du fichier avec les données
	{
		printf("Fichier pr%sc%sdent supprim%s.\n", é, é, é) ;
	}
	else
	{
		printf("Pas de fichier %s supprimer.\n", à) ;
	}

	fichier = fopen(ficheCoureur->nom, "w+") ;
	if (fichier != NULL)
	{
		printf("Fichier %s ouvert.\n", ficheCoureur->nom) ;
	}
	else
	{
		printf("Ouverture du fichier %s impossible.\n", ficheCoureur->nom) ;
		perror("Erreur dans modification.c, void enregistrer.\n") ;
		exit(EXIT_FAILURE) ;
	}
	
	fprintf(fichier, "%d Specialite principale %d specialite secondaire %d\n", ficheCoureur->style, ficheCoureur->principal, ficheCoureur->secondaire) ;
	
	fprintf(fichier, "%d taille\n", ficheCoureur->taille) ;
	fprintf(fichier, "%d poids\n", ficheCoureur->poids) ;
	fprintf(fichier, "%d/%d/%d date de naissance\n", ficheCoureur->jour, ficheCoureur->mois, ficheCoureur->annee) ;
	fprintf(fichier, "%s course favorite 1\n", ficheCoureur->course1) ;
	fprintf(fichier, "%s course favorite 2\n", ficheCoureur->course2) ;
	fprintf(fichier, "%s course favorite 3\n", ficheCoureur->course3) ;
	fprintf(fichier, "%s nationalite\n", ficheCoureur->pays) ;
	fprintf(fichier, "%d points\n", ficheCoureur->points) ;
	fprintf(fichier, "%d potentiel\n", ficheCoureur->potentiel) ;
	
	char *caracteristiques[14] = {"Plaine", "Montagne", "Moyenne_montagne", "Vallon", "Contre-la-montre", "Prologue", "Paves",\
	"Sprints", "Acceleration", "Descente", "Baroud", "Endurance", "Resistance", "Recuperation"} ;
	int compteur ;
	for (compteur = 0 ; compteur < 14 ; compteur ++)
	{
		char *caracteristique = caracteristiques[compteur] ;
		int noteCourante = ficheCoureur->notes[compteur] ;
		int initialCourant = notesInitiales[compteur] ;
		fprintf (fichier, "%d %s (+ %d)\n", noteCourante, caracteristique, (noteCourante - initialCourant)) ;
	}

	fclose(fichier) ;
	
	FILE *maximum = NULL ;
	
	enregistrerMax(ficheCoureur) ;
	creerCopie(ficheCoureur->nom) ;
}

void enregistrerMax(StructFicheCoureur *pointeur)
{
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur*)pointeur ;
	FILE* fichier = NULL ;
	char fichierMax[255] ;
	int compteur = 0 ;
	
	sprintf(fichierMax, "%s_max", ficheCoureur->nom) ;
	printf("%s _MAX \n", fichierMax) ;
	fichier = fopen(fichierMax, "w+") ;
	if(fichier == NULL)
	{
		printf("Erreur, impossible d'ouvrir %s. Dans sauvegardes.c, void enregistrerMax.\n", fichierMax) ;
	}
	else
	{
		while (compteur < 14)
		{
			fprintf(fichier, u8"%d\n", ficheCoureur->notesMax[compteur]) ;
			compteur ++ ;
		}
	}
	fclose(fichier) ;
}

void creerCopie(char nom[250])
{
	FILE *fichier1, *fichier2 = NULL ;
	char fichierCopie[255] ;
	char ch ;
	
	sprintf(fichierCopie, "%s_cop", nom) ;
	fichier1 = fopen(nom, "r") ;
	fichier2 = fopen(fichierCopie, "w+") ;
	
	while((ch = getc(fichier1)) != EOF)
	{
		putc(ch, fichier2);
	}
	fclose(fichier1) ;
	fclose(fichier2) ;
}

int verifierDonnees(StructFicheCoureur *pointeur)
{
	StructFicheCoureur *ficheCoureur = (StructFicheCoureur *)pointeur ;
	FILE* fichier = NULL ;
	int compteur = 0 ;
	int erreur = 0 ;

	if (ficheCoureur->style < 0 || ficheCoureur->style > 48)
	{
		g_print("Style impossible.\n") ;
		erreur = 1 ;
	}
	if (ficheCoureur->potentiel < 0 || ficheCoureur->potentiel > 8)
	{
		g_print("Potentiel impossible.\n") ;
		erreur = 1 ;
	}
	if (ficheCoureur->principal < 0 || ficheCoureur->principal > 7)
	{
		g_print("Style principal impossible.\n") ;
		erreur = 1 ;
	}
	if (ficheCoureur->secondaire < 0 || ficheCoureur->secondaire > 7)
	{
		g_print("Style secondaire impossible.\n") ;
		erreur = 1 ;
	}
	if (ficheCoureur->taille < 150 || ficheCoureur->taille > 200)
	{
		g_print("Taille impossible.\n") ;
		erreur = 1 ;
	}
	if (ficheCoureur->poids < 50 || ficheCoureur->poids > 100)
	{
		g_print("Poids impossible.\n") ;
		erreur = 1 ;
	}
	/*if (ficheCoureur->mois < 1 || ficheCoureur->mois > 12 || ficheCoureur->jour < 1 || ficheCoureur->jour > 31)
	{
		g_print("Date impossible.\n") ;
		erreur = 1 ;
	}*/
	if (strlen(ficheCoureur->pays) == 0 || strlen(ficheCoureur->course1) == 0 || strlen(ficheCoureur->course2) == 0 || strlen(ficheCoureur->course3) == 0)
	{
		g_print("Il manque le pays et / ou une course préférée.\n") ;
		erreur = 1 ;
	}
	if (erreur == 1)
	{
		printf("Erreur. Donn%ses enregistr%s impossibles.\n", é, é) ;
		getchar() ;
		return 0 ;
	}
	while (compteur < 14)
	{
		if (ficheCoureur->notes[compteur] < 50 || ficheCoureur->notes[compteur] > 85)
		{
			g_print("Notes impossibles (au-delà des limites du jeu).\n") ;
			return 0 ;
		}
		compteur ++ ;
	}
	return 1 ;
}

void restaurerSauvegarde(char nom[250])
{
	FILE *fichier1, *fichier2 = NULL ;
	char fichierCopie[255] ;
	char ch ;
	
	sprintf(fichierCopie, "%s_cop", nom) ;
	fichier1 = fopen(fichierCopie, "r") ;
	fichier2 = fopen(nom, "w+") ;
	
	while((ch = getc(fichier1)) != EOF)
	{
		putc(ch, fichier2) ;
	}
	fclose(fichier1) ;
	fclose(fichier2) ;
}
