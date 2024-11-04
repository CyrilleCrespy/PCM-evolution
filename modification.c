char nomDeFichier[250] ;
int points ;
int pointsDepenses ;
FILE* fichier = NULL ;

void demandeNomDeFichier(char *caracteristiques[])
{
	while (1)
	{
		system(clear) ;
		int fichierOuvert ;
		int session ;
		char messageJournal[100] ;
		
		printf("Merci de choisir un nom de fichier.\n") ;
		viderBuffer() ;
		fgets(nomDeFichier, 250, stdin) ;
		corrigerNomDeFichier() ;
		suppressionEspace() ;
		fichierOuvert = verificationExistanceDuFichier() ;
		pointsDepenses = 0 ;
		
		fichier = fopen(nomDeFichier, "r") ;
		
		if (fichierOuvert == 0)
		{
			perror("Impossible d'ouvrir le fichier. Le fichier existe-t-il ? As-tu les droits de lecture dessus ?\n") ;
			printf("Nom de fichier attendu : %s.\n", nomDeFichier) ;
			printf("Appuie sur Entr%se pour continuer.\n", é) ;
			getchar() ;
			fclose(fichier) ;
			continue ;
		}
		else
		{
			fscanf(fichier, "%d %*s", &session) ;
			session ++ ;
			sprintf(messageJournal, "| SESSION %d | Fichier modifié", session) ;
			remplirJournal(messageJournal) ;
			modification(session, 0, caracteristiques, 150) ;
		}
		viderBuffer() ;
	}
}

void modification(int session, int points, char *caracteristiques[], int taille)
{
	system(clear) ;
	
	points = 0 ;
	int coureur[21] = {0} ;
	int style = 0 ;
	int principal = 0 ;
	int secondaire = 0 ;
	int compteur ;
	int choix = 999 ;
	int maximum[14] = {0} ;
	int potentiel ;
	int potentielInitial ;
	int poids ;
	int mois ;
	int jour ;
	int fichierOK ;
	int fichierOuvert = 0 ;
	char nationalite[100] ;
	char course1[100] ;
	char course2[100] ;
	char course3[100] ;
	char messageJournal[100] ;

	char cpe[30] ;
	sprintf(cpe, "Courses par %stapes", é) ;
	char *types[7] = {cpe, "Grimpeur", "Sprint", "Contre-la-montre", "Puncheur",\
"Baroud", "Classiques du Nord"} ;

	int notesInitiales[14] = {0} ;

	fichier = fopen(nomDeFichier, "r") ;
	fichierOuvert = verificationExistanceDuFichier() ;
	if (fichierOuvert == 0)
	{
		perror("Impossible d'ouvrir le fichier. Erreur dans modification.c, void modification.\n") ;
		printf("Nom de fichier attendu : %s.\n", nomDeFichier) ;
	}
	fscanf(fichier, "%*s %*s") ; //La ligne d'indicateur de session est ignorée, car inchangée au cours de la session.
	fscanf(fichier, "%d %*s %*s %*s %*s %*s %*s %*s %*s %*s", &style) ;
	fscanf(fichier, "%d %*s", &taille) ;
	fscanf(fichier, "%d %*s", &poids) ;
	fscanf(fichier, "%d", &jour) ;
	fgetc(fichier) ; //Pour ignorer le / de la date
	fscanf(fichier, "%d %*s %*s %*s", &mois) ;
	fscanf(fichier, "%d %*s", &potentiel) ;
	potentielInitial = potentiel ; //Utilisé pour vérifier qu'une seule augmentation de potentiel a été faite.
	fscanf(fichier, "%s %*s", &nationalite[0]) ;
	fscanf(fichier, "%s %*s %*s %*s", &course1[0]) ;
	fscanf(fichier, "%s %*s %*s %*s", &course2[0]) ;
	fscanf(fichier, "%s %*s %*s %*s", &course3[0]) ;
	
	for(compteur = 0 ; compteur < 14 ; compteur ++)
	{
		fscanf(fichier, "%d %*s %*s %*s", &coureur[compteur]) ;
	}
	
	fichierOK = verifierDonnees(session, style, coureur, potentiel, principal, secondaire, taille, poids, mois, jour, nationalite, course1, course2, course3) ;
	if (fichierOK == 1)
	{
		printf("Fichier de sauvegarde OK.\n") ;
	}
	else
	{
		printf("Fichier de sauvegarde mal enregistr%s. Restauration.\n", é) ;
		restaurerSauvegarde() ;
	}
	
	getchar() ;
	
	principal = style / 7 ;
	secondaire = (style % 7) ;
	fclose(fichier) ;

	if(session == 0)
	{
		points = 200 ;
		printf("En tant que nouveau coureur, tu as droit %s 200 points.\n", à) ;
		potentiel = 3 ;
		potentielInitial = 3 ;
		session = 1 ;
	}

	else
	{
		printf("Combien de points d'am%slioration as-tu ?\n", é) ;
		points = verificationEntreeNumerique(0, 5000) ;
		sprintf(messageJournal, "%d points disponibles selon l'utilisateur.", points) ;
		remplirJournal(messageJournal) ;
		memset(messageJournal, 0, 100) ;
	}
	
	for (compteur = 0 ; compteur < 14 ; compteur ++)
	{
		maximum[compteur] = retrouverNotesMax(compteur) ;		
	}
	
	getchar() ;
	
	for(compteur = 0 ; compteur < 14 ; compteur ++)
	{
		notesInitiales[compteur] = coureur[compteur] ; //Doublon des valeurs initiales pour vérifier la validité des baisses de notes demandées par la suite.
	}
	
	printf("Une %svolution co%ste :\n%s 1 point jusqu'%s la note 60.\n%s 2 points jusqu'%s 65\n%s 3 points jusqu'%s 70\n%s 4 points jusqu'%s 75\n%s 5 points jusqu'%s 80\n%s 6 points jusqu'%s 85.\n",\
é, û, tiret, à, tiret, à, tiret, à, tiret, à, tiret, à, tiret, à) ;
	printf("Appuie sur Entr%se pour continuer.\n", é) ;
	getchar() ;
	


	while (choix != 0)
	{
		compteur = 0 ;
		enregistrer(session, style, coureur, potentiel, principal, secondaire, taille, poids, mois, jour, nationalite, course1, course2, course3, notesInitiales, maximum) ;
		system(clear) ;
		
		printf("\nTu mesures %d centim%stres.\n", taille, è) ;
		printf("Tu p%sses %d kilos.\n", è, poids) ;
		printf("Tu es n%s le %d/%d.\n", é, jour, mois) ;
		printf("Pays : %s\n", nationalite) ;
		printf("Course favorite 1 : %s\n", course1) ;
		printf("Course favorite 2 : %s\n", course2) ;
		printf("Course favorite 3 : %s\n", course3) ;
		printf("Ton style principal est %s et ton style secondaire %s.\n", types[principal], types[secondaire]) ;
		
		for (compteur = 0 ; compteur < 14 ; compteur ++)
		{
			printf("%d. %s : %d (max : %d).\n", (compteur + 1), caracteristiques[compteur], coureur[compteur], maximum[compteur]) ;
		}
		
		printf("Tu as %d point(s) d'am%slioration restant(s).\n", points, é) ;

		printf("Entre 0 pour quitter le programme, ou le chiffre correspondant %s la note que tu veux changer.\n", à) ;
		choix = verificationEntreeNumerique(0, 14) ;

		if (choix == 0)
		{
			printf("Merci d'avoir utilis%s PCM %svolution !\n", é, É) ;
			exit(EXIT_SUCCESS) ;
		}
		else if (coureur[choix-1] >= 85)
		{
			printf("Cette caract%sristique est d%sj%s au maximum.\n", é, é, à) ;
		}
		if (choix > 0 && choix <=14)
		{
			coureur[choix - 1] = calculAmelioration(coureur[choix - 1], &points, &maximum[choix - 1], notesInitiales[choix - 1], &potentiel, potentielInitial) ; //La liste commençant à l'indice 0, on compense.
			sprintf(messageJournal, "Note %s : %d. Nouveaux points : %d.", caracteristiques[choix - 1], coureur[choix - 1], points) ;
			remplirJournal(messageJournal) ;
			memset(messageJournal, 0, 100) ;
			sprintf(messageJournal, "Potentiel %s : %d.", caracteristiques[choix - 1], maximum[choix - 1]) ;
			remplirJournal(messageJournal) ;
			memset(messageJournal, 0, 100) ;
		}
	}
}
