char nomDeFichier[255] ; //Limite imposée par le NTFS, pour plus de compatibilité.
int points ;
int pointsDepenses ;

int demandeNomDeFichier(char *caracteristiques[])
{
	printf("Veuillez choisir un nom de fichier.\n") ;
	viderBuffer() ;
	fgets(nomDeFichier, 255, stdin) ;
	corrigerNomDeFichier() ;
	pointsDepenses = 0 ;
	modification(0, caracteristiques, 150) ;
	return 0 ;
}

void modification(int nouveau, char *caracteristiques[], int taille)
{
	FILE* fichier = NULL ;
	system(clear) ;
	points = 0 ;
	int coureur[21] = {0} ;
	int style = 0 ;
	int principal = 0 ;
	int secondaire = 0 ;
	int compteur ;
	int limiteMax ;
	int choix = 999 ;
	int maximum[14] = {0} ;
	int potentiel ;
	int coutPotentiel = 0 ;
	int poids ;
	int mois ;
	int jour ;
	int fichierOuvert = 0 ;
	char nationalite[100] ;
	char course1[100] ;
	char course2[100] ;
	char course3[100] ;

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
	fscanf(fichier, "%d %*s %*s %*s %*s %*s %*s %*s %*s %*s", &style) ;
	fscanf(fichier, "%d %*s", &taille) ;
	fscanf(fichier, "%d %*s", &poids) ;
	fscanf(fichier, "%d", &jour) ;
	fgetc(fichier) ; //Pour ignorer le / de la date
	fscanf(fichier, "%d %*s %*s %*s", &mois) ;
	fscanf(fichier, "%d %*s", &potentiel) ;
	fscanf(fichier, "%s %*s", &nationalite[0]) ;
	fscanf(fichier, "%s %*s %*s %*s", &course1[0]) ;
	fscanf(fichier, "%s %*s %*s %*s", &course2[0]) ;
	fscanf(fichier, "%s %*s %*s %*s", &course3[0]) ;
	
	for(compteur = 0 ; compteur < 14 ; compteur ++)
	{
		fscanf(fichier, "%d %*s %*s %*s", &coureur[compteur]) ;
	}
	
	principal = style / 14 ;
	secondaire = (style % 14) - 1 ;
	fclose(fichier) ;

	if(nouveau == 1)
	{
		points = 200 ;
		printf("En tant que nouveau coureur, tu as droit %s 200 points.\n", à) ;
		printf("Tu d%smarres au potentiel 3 et tu ne pourras pas augmenter (tout de suite) de note au-dessus de 70.\n", é) ;
		nouveau = 0 ;
	}

	else
	{
		printf("Combien de points d'am%slioration as-tu ?\n", é) ;
		scanf("%d", &points) ;
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
	
	for (compteur = 0 ; compteur < 14 ; compteur ++)
	{
		maximum[compteur] = determinerNotesMax(principal, secondaire, compteur) ;
	}

	while (choix != 0)
	{
		compteur = 0 ;
		enregistrer(style, coureur, potentiel, principal, secondaire, taille, poids, mois, jour, nationalite, course1, course2, course3, notesInitiales) ;
		limiteMax = determinerLimitePotentiel(potentiel) ;
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
		
		coutPotentiel = calculCoutPotentiel(potentiel) ;
		if (coutPotentiel != 0)
		{
			printf("15. Augmenter le potentiel (%d) pour %d points de cha%sne (assures-toi des les avoir).\n", potentiel, coutPotentiel, î) ;
		}
		
		printf("Tu as %d points d'am%slioration restants.\n", points, é) ;
		printf("Limite de chaque note avec le potentiel actuel (qui est de %d sur 8) : %d.\n", potentiel, limiteMax) ;

		printf("Entre 0 pour quitter le programme, ou le chiffre correspondant %s la note que tu veux changer.\n", à) ;
		scanf("%d", &choix) ;

		if (choix == 0)
		{
			printf("Merci d'avoir utilis%s PCM %svolution !\n", é, É) ;
			exit(EXIT_SUCCESS) ;
		}
		else if (coureur[choix-1] >= 85)
		{
			printf("Cette caract%sristique est d%sj%s au maximumimum.\n", é, é, à) ;
		}
		if (choix > 0 && choix <=14)
		{
			coureur[choix-1] = calculAmelioration(coureur[choix-1], limiteMax, &points, maximum, choix, notesInitiales[choix-1]) ; //La liste commençant à l'indice 0, on compense.
		}
		else if (choix == 15)
		{
			potentiel = augmenterPotentiel(potentiel) ;
		}
		else
		{
			printf("Entrée invalide, merci de ne taper qu'un nombre entre 0 et 15.\n") ;
		}
	}
}

int calculCoutPotentiel(int potentiel)
{
	int coutPotentiel ;
	if(potentiel == 3)
		{
			coutPotentiel = 1000 ;
		}
	else if(potentiel == 4)
		{
			coutPotentiel = 2000 ;
		}
	else if(potentiel == 5)
		{
			coutPotentiel = 3000 ;
		}
	else if(potentiel == 6)
		{
			coutPotentiel = 4000 ;
		}
	else if(potentiel == 7)
		{
			coutPotentiel = 5000 ;
		}
	return coutPotentiel ;
}

int augmenterPotentiel (int potentiel)
{
	int choix = 0 ;
	system(clear) ;
	printf("ATTENTION. Il te faut avoir assez de points de cha%sne.\n", î) ;
	printf("Toute modification sera v%srifi%se, n'essaie pas de tricher.\n", é, é) ;
	printf("Tu risques une sanction en cas de tentative de fraude.\n") ;
	printf("Tape Entr%se si tu as compris.\n", é) ;
	getchar() ;
	getchar() ;
	printf("Confirmer le choix ?\n") ;
	printf("1. Oui\n") ;
	printf("2. Non\n") ;
	while (choix != 1 && choix != 2)
	{
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			potentiel ++ ;
			printf("%d", potentiel) ;
			return potentiel ;
		}
		else if (choix == 2)
		{
			return potentiel ;
		}
		else
		{
			printf("Entr%se invalide", é) ;
		}
	}
	return potentiel ;
}

int determinerLimitePotentiel(int potentiel)
{
	int limiteMax ;
	if (potentiel == 3)
	{
		limiteMax = 70 ;
	}
	else if (potentiel == 4 || potentiel == 5)
	{
		limiteMax = 75 ;
	}
	else if (potentiel == 6 || potentiel == 7)
	{
		limiteMax = 80 ;
	}
	else if (potentiel == 8)
	{
		limiteMax = 85 ;
	}
	else
	{
		printf("Potentiel invalide (%d).\n", potentiel) ;
		exit(EXIT_FAILURE) ;
	}
	return limiteMax ;
}

void enregistrer(int style, int coureur[], int potentiel, int principal, int secondaire, int taille, int poids, int mois, int jour, char *nationalite, char *course1, char *course2, char *course3, int notesInitiales[])
{	
	FILE* fichier = NULL ;
	supressionEspace() ; //On retire les caractères de fin de ligne issus des données entrées par l'utilsateur.
	printf("Tentative d'ouverture de '%s.\n", nomDeFichier) ;
	fichier = fopen(nomDeFichier, "w+") ;
	char *types[7] = {"courses_par_étapes", "grimpeur", "sprint", "contre-la-montre", "puncheur",\
"baroud", "classiques_du_nord"} ; //Version avec les accents d'une même variable concernée ailleurs par les instructions de préprocesseur.

	if (remove(nomDeFichier) == 0) //Suppression du fichier avec les données
	{
		printf("Fichier pr%sc%sdent supprim%s.\n", é, é, é) ;
	}

	fichier = fopen(nomDeFichier, "w+") ;
	if (fichier != NULL)
	{
		printf("Fichier %s ouvert.\n", nomDeFichier) ;
	}
	else
	{
		printf("Ouverture du fichier %s impossible.\n", nomDeFichier) ;
		perror("Erreur dans modification.c, void enregistrer.\n") ;
		exit(EXIT_FAILURE) ;
	}
	
	if (principal == secondaire)
	{
		fprintf(fichier, u8"%d spécialité principale : %s ; spécialité secondaire : aucune\n", style, types[principal]) ;
	}
	else
	{
		fprintf(fichier, u8"%d spécialité principale : %s ; spécialité secondaire : %s\n", style, types[principal], types[secondaire]) ;
	}
	
	fprintf(fichier, u8"%d taille\n", taille) ;
	fprintf(fichier, u8"%d poids\n", poids) ;
	fprintf(fichier, u8"%d/%d date de naissance\n", jour, mois) ;
	fprintf(fichier, u8"%d potentiel\n", potentiel) ;
	fprintf(fichier, u8"%s nationalité\n", nationalite) ;
	fprintf(fichier, u8"%s course favorite 1\n", course1) ;
	fprintf(fichier, u8"%s course favorite 2\n", course2) ;
	fprintf(fichier, u8"%s course favorite 3\n", course3) ;
	
	//D'avance, désolé pour cette immondice, mais l'écriture d'un fichier n'ayant pas les mêmes limitations que l'horrible ligne de commande Windows, on peut utiliser de vrais accents,
	//ce qui rend les //define complètement inopérants, et même gênants, on doit donc tout retaper à la main, sauf si quelqu'un a une meilleure idée.
	fprintf(fichier, u8"%d plaine (+ %d)\n", coureur[0], coureur[0] - notesInitiales[0]) ;
	fprintf(fichier, u8"%d montagne (+ %d)\n", coureur[1], coureur[1] - notesInitiales[1]) ;
	fprintf(fichier, u8"%d moyenne_montagne (+ %d)\n", coureur[2], coureur[2] - notesInitiales[2]) ;
	fprintf(fichier, u8"%d vallon (+ %d)\n", coureur[3], coureur[3] - notesInitiales[3]) ;
	fprintf(fichier, u8"%d contre-la-montre (+ %d)\n", coureur[4], coureur[4] - notesInitiales[4]) ;
	fprintf(fichier, u8"%d prologue (+ %d)\n", coureur[5], coureur[5] - notesInitiales[5]) ;
	fprintf(fichier, u8"%d pavés (+ %d)\n", coureur[6], coureur[6] - notesInitiales[6]) ;
	fprintf(fichier, u8"%d sprint (+ %d)\n", coureur[7], coureur[7] - notesInitiales[7]) ;
	fprintf(fichier, u8"%d accélération (+ %d)\n", coureur[8], coureur[8] - notesInitiales[8]) ;
	fprintf(fichier, u8"%d descente (+ %d)\n", coureur[9], coureur[9] - notesInitiales[9]) ;
	fprintf(fichier, u8"%d baroud (+ %d)\n", coureur[10], coureur[10] - notesInitiales[10]) ;
	fprintf(fichier, u8"%d endurance (+ %d)\n", coureur[11], coureur[11] - notesInitiales[11]) ;
	fprintf(fichier, u8"%d résistance (+ %d)\n", coureur[12], coureur[12] - notesInitiales[12]) ;
	fprintf(fichier, u8"%d récupération (+ %d)\n", coureur[13], coureur[13] - notesInitiales[13]) ;
	
	fprintf(fichier, u8"%d points d%spens%ss.\n", pointsDepenses, é, é) ;
	fclose(fichier) ;
}
