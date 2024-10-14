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
	int principal = 0 ;
	int secondaire = 0 ;
	int compteur ;
	int limiteMax ;
	int choix = 999 ;
	int maximum[14] = {0} ;
	int potentiel ;

	char cpe[30] ;
	sprintf(cpe, "Courses par %stapes", é) ;
	char *types[7] = {cpe, "Grimpeur", "Sprint", "Contre-la-montre", "Puncheur",\
"Baroud", "Classiques du Nord"} ;

	fichier = fopen(nomDeFichier, "r") ;
	fscanf(fichier, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &style, &potentiel, &coureur[0], &coureur[1], &coureur[2],\
&coureur[3], &coureur[4], &coureur[5], &coureur[6], &coureur[7], &coureur[8], &coureur[9], &coureur[10],\
&coureur[11], &coureur[12], &coureur[13]) ;
	principal = style / 14 ;
	secondaire = (style % 14) - 1 ;
	fclose(fichier) ;

	printf("Ton style principal est %s et ton style secondaire %s.\n", types[principal], types[secondaire]) ;

	if(nouveau == 1)
	{
		points = 200 ;
		printf("En tant que nouveau coureur, tu as droit %s 200 points.\n", à) ;
		printf("Une %svolution co%ste \n", é, û) ;
		printf("Tu d%smarres au potentiel 3 et tu ne pourras pas augmenter (tout de suite) de note au-dessus de 70.\n", é) ;
		potentiel = 3 ;
	}

	else
	{
		printf("Combien de points d'am%slioration as-tu ?\n", é) ;
		scanf("%d", &points) ;
	}

	limiteMax = determinerLimitePotentiel(potentiel) ;

	for (compteur = 0 ; compteur < 14 ; compteur ++)
	{
		maximum[compteur] = determinerNotesMax(principal, secondaire, compteur) ;
	}

	compteur = 0 ;
	while (choix != 0)
	{
		for (compteur = 0 ; compteur < 14 ; compteur ++)
		{
			printf("%d. %s : %d (max : %d).\n", (compteur + 1), caracteristiques[compteur], coureur[compteur], maximum[compteur]) ;
		}
		printf("Tu as %d points d'am%slioration restants.\n", points, î) ;
		printf("Limite de chaque note avec le potentiel actuel (qui est de %d sur 8) : %d.\n", potentiel, limiteMax) ;

		if (points < 1)
		{
			printf("Tu n'as pas assez de points pour am%sliorer ton coureur. %s la prochaine !\n", é, À) ;
			exit(EXIT_SUCCESS) ;
		}

		printf("Entrez 0 pour quitter le programme, ou le chiffre correspondant %s la note que vous voulez changer.\n", à) ;
		scanf("%d", &choix) ;

		if (choix == 0)
		{
			printf("Merci d'avoir utilis%s PCM %svolution !\n", é, É) ;
			exit(EXIT_SUCCESS) ;
		}
		else if (choix == 15)
		{
			enregistrer(style, coureur, potentiel) ;
			exit(EXIT_SUCCESS) ;
		}
		else if (coureur[choix-1] >= 85 || coureur[choix-1] >= maximum[choix-1] || coureur[choix-1] >= limiteMax)
		{
			printf("Cette caract%sristique est d%sj%s au maximumimum.\n", é, é, à) ;
		}

		coureur[choix-1] = calculAmelioration(coureur[choix-1], limiteMax, points, maximum, choix) ; //La liste commençant à l'indice 0, on compense.
	}
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

void enregistrer(int style, int coureur[], int potentiel)
{
	FILE* fichier = NULL ;
	fichier = fopen(nomDeFichier, "w+") ;
	fprintf(fichier, "%d\n", style) ;
	fprintf(fichier, "%d\n", potentiel) ;
	int compteurDeNotes = 0 ;
	while(compteurDeNotes < 14)
	{
		fprintf(fichier, "%d\n", coureur[compteurDeNotes]) ;
		compteurDeNotes ++ ;
	}
}
