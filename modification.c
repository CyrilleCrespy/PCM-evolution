char nomDeFichier[255] ; //Limite imposée par le NTFS, pour plus de compatibilité.
int points ;

int demandeNomDeFichier(char *caracteristiques[])
{
	printf("Veuillez choisir un nom de fichier.\n") ;
	scanf("%s", &nomDeFichier[0]) ;
	modification(0, caracteristiques) ;
	return 0 ;
}

void modification(int nouveau, char *caracteristiques[])
{
	FILE* fichier = NULL ;
	system(clear) ;
	points = 0 ;
	int coureur[14] = {0} ;
	int style = 0 ;
	int primaire = 0 ;
	int secondaire = 0 ;
	int compteur ;
	int limiteMax ;
	int choix = 999 ;
	int maximum[14] = {0} ;
	int potentiel ;
	int coutPotentiel = 0 ;

	char cpe[30] ;
	sprintf(cpe, "Courses par %stapes", é) ;
	char *types[7] = {cpe, "Grimpeur", "Sprint", "Contre-la-montre", "Puncheur",\
"Baroud", "Classiques du Nord"} ;

	int notesInitiales[14] = {0} ;

	fichier = fopen(nomDeFichier, "r") ;
	fscanf(fichier, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &style, &potentiel, &coureur[0], &coureur[1], &coureur[2],\
&coureur[3], &coureur[4], &coureur[5], &coureur[6], &coureur[7], &coureur[8], &coureur[9], &coureur[10],\
&coureur[11], &coureur[12], &coureur[13]) ;

	for(compteur = 0 ; compteur < 14 ; compteur ++)
	{
		notesInitiales[compteur] = coureur[compteur] ; //Doublon des valeurs initiales pour vérifier la validité des baisses de notes demandées par la suite.
	}
	
	primaire = style / 14 ;
	secondaire = (style % 14) - 1 ;
	fclose(fichier) ;

	printf("Ton style primaire est %s et ton style secondaire %s.\n", types[primaire], types[secondaire]) ;

	if(nouveau == 1)
	{
		points = 200 ;
		printf("En tant que nouveau coureur, tu as droit %s 200 points.\n", à) ;
		printf("Tu d%smarres au potentiel 3 et tu ne pourras pas augmenter (tout de suite) de note au-dessus de 70.\n", é) ;
		potentiel = 3 ;
	}

	else
	{
		printf("Combien de points d'am%slioration as-tu ?\n", é) ;
		scanf("%d", &points) ;
	}
	
	printf("Une %svolution co%ste :\n%s 1 point jusqu'%s la note 60.\n%s 2 points jusqu'%s 65\n%s 3 points jusqu'%s 70\n%s 4 points jusqu'%s 75\n%s 5 points jusqu'%s 80\n%s 6 points jusqu'%s 85.\n",\
é, û, tiret, à, tiret, à, tiret, à, tiret, à, tiret, à, tiret, à) ;
	printf("Appuie sur Entr%se pour continuer.\n", é) ;
	getchar() ;

	system(clear) ;

	for (compteur = 0 ; compteur < 14 ; compteur ++)
	{
		maximum[compteur] = determinerNotesMax(primaire, secondaire, compteur) ;
	}

	compteur = 0 ;
	while (choix != 0)
	{
		limiteMax = determinerLimitePotentiel(potentiel) ;
		system(clear) ;
		enregistrer(style, coureur, potentiel, primaire, secondaire) ;
		for (compteur = 0 ; compteur < 14 ; compteur ++)
		{
			printf("%d. %s : %d (max : %d).\n", (compteur + 1), caracteristiques[compteur], coureur[compteur], maximum[compteur]) ;
		}
		
		coutPotentiel = calculCoutPotentiel(potentiel) ;
		if (coutPotentiel != 0)
		{
			printf("15. Augmenter le potentiel (%d) pour %d points de cha%sne (assurez-vous des les avoir).\n", potentiel, coutPotentiel, î) ;
		}
		
		printf("Tu as %d points d'am%slioration restants.\n", points, î) ;
		printf("Limite de chaque note avec le potentiel actuel (qui est de %d sur 8) : %d.\n", potentiel, limiteMax) ;

		printf("Entrez 0 pour quitter le programme, ou le chiffre correspondant %s la note que vous voulez changer.\n", à) ;
		scanf("%d", &choix) ;

		if (choix == 0)
		{
			printf("Merci d'avoir utilis%s PCM %svolution !\n", é, É) ;
			exit(EXIT_SUCCESS) ;
		}
		else if (coureur[choix-1] >= 85 || coureur[choix-1] >= maximum[choix-1] || coureur[choix-1] >= limiteMax)
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
	if(potentiel >= 3 && potentiel < 8)
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
	printf("Toute modification sera vérifi%se, n'essaie pas de tricher.\n", é) ;
	printf("Tu risques une sanctin en cas de tentative de fraude.\n") ;
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
			printf("Entrée invalide") ;
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
		printf("Potentiel invalide.\n") ;
		exit(EXIT_FAILURE) ;
	}
	return limiteMax ;
}

void enregistrer(int style, int coureur[], int potentiel, int primaire, int secondaire)
{
	FILE* fichier = NULL ;
	fichier = fopen(nomDeFichier, "w+") ;
	char *types[7] = {"courses par étapes", "grimpeur", "sprint", "contre-la-montre", "puncheur",\
"baroud", "classiques du Nord"} ; //Version avec les accents d'une même variable concernée ailleurs par les instructions de préprocesseur.
	
	if (primaire == secondaire)
	{
		fprintf(fichier, "%d spécialité unique : %s\n", style, types[primaire]) ;
	}
	else
	{
		fprintf(fichier, "%d spécialité primaire : %s ; spécialité secondaire : %s\n", style, types[primaire], types[secondaire]) ;
	}
	
	fprintf(fichier, "%d potentiel\n", potentiel) ;
	
	//D'avance, désolé pour cette immondice, mais l'écriture d'un fichier n'ayant pas les mêmes limitations que l'horrible ligne de commande Windows, on peut utiliser de vrais accents,
	//ce qui rend les //define complètement inopérants, et même gênants, on doit donc tout retaper à la main, sauf si quelqu'un a une meilleure idée.
	fprintf(fichier, "%d plaine\n", coureur[0]) ;
	fprintf(fichier, "%d montagne\n", coureur[1]) ;
	fprintf(fichier, "%d moyenne montagne\n", coureur[2]) ;
	fprintf(fichier, "%d vallon\n", coureur[3]) ;
	fprintf(fichier, "%d contre-la-montre\n", coureur[4]) ;
	fprintf(fichier, "%d prologue\n", coureur[5]) ;
	fprintf(fichier, "%d pavés\n", coureur[6]) ;
	fprintf(fichier, "%d sprint\n", coureur[7]) ;
	fprintf(fichier, "%d accélération\n", coureur[8]) ;
	fprintf(fichier, "%d descente\n", coureur[9]) ;
	fprintf(fichier, "%d baroud\n", coureur[10]) ;
	fprintf(fichier, "%d endurance\n", coureur[11]) ;
	fprintf(fichier, "%d résistance\n", coureur[12]) ;
	fprintf(fichier, "%d récupération\n", coureur[13]) ;
	fclose(fichier) ;
}
