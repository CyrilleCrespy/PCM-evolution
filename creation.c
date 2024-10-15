FILE* fichier = NULL ;

int creation(char *caracteristiques[])
{
	int fichierOK = 0 ;
	while (fichierOK != 1)
	{
		fichierOK = choixNomDeFichier(caracteristiques) ;
	}
	choixStyle() ;
	entreeStats(caracteristiques) ;
	return 0 ;
}

int verificationExistanceDuFichier()
{
	FILE* fichier = NULL ;
	fichier = fopen(nomDeFichier, "r") ;
	if (fichier != NULL)
	{
		fclose(fichier) ;
		return 1 ; //Fiche du même nom déjà existante
	}
	else
	{
		return 0 ; 
	}
}

int entreeStats(char *caracteristiques[])
{
	int compteurDeNotes = 0 ;
	while(compteurDeNotes < 14)
	{
		fichier = fopen(nomDeFichier, "a") ;
		fprintf(fichier, "%d\n", 50) ;
		fclose(fichier) ;
		compteurDeNotes ++ ;
	}
	modification(1, caracteristiques) ;
	return 0 ;
}

int choixNomDeFichier()
{
	unsigned char choix = 0 ;
	printf("Veuillez choisir le nom et le pr%snom de votre coureur, s%spar%ss par une espace.\n", é, é, é) ;
	getchar() ;
	fgets(nomDeFichier, 255, stdin) ;
	corrigerNomDeFichier() ;
	int fichierOuvert = verificationExistanceDuFichier(nomDeFichier) ;
	if (fichierOuvert == 1)
	{
		printf("Fiche d%sj%s existante. Voulez-vous supprimer l'ancien  %s ?\n", é, à, nomDeFichier) ;
		printf("1. Oui\n") ;
		printf("2. Non\n") ;
		scanf("%hhu", &choix) ;
		if (choix == 1)
		{
			if (remove(nomDeFichier) == 0)
			{
				printf("Fichier supprim%s.\n", é) ;
				return 1 ;
			}
			else
			{
				perror("Suppression du fichier impossible.\n") ;
				return 0 ;
			}
		}
		else
		{
			printf("Fichier pr%sserv%s.\n", é, é) ;
			return 0 ;
		}
	}
	else 
	{
		return 1 ;
	}
}

void corrigerNomDeFichier()
{
	int compteur ;
	for (compteur = 0 ; compteur < 255 ; compteur ++)
	{
		if (nomDeFichier[compteur] == 36 || nomDeFichier[compteur] == 39 || nomDeFichier[compteur] == 10)
		{
			nomDeFichier[compteur] = '\0' ;
		}
	compteur ++ ;
	}
}

int choixStyle()
{
	int principal = -1;
	int secondaire = -1;

	int style ;
	int compteurDeNotes = 0 ;

	char cpe[30] ;
	sprintf(cpe, "Courses par %stapes", é) ;
	char *types[7] = {cpe, "Grimpeur", "Sprint", "Contre-la-montre", "Puncheur",\
"Baroud", "Classiques du Nord"} ;

	system(clear) ; //Appel système différent selon le SE.
	printf("Veuillez choisir un style principal.\n") ;
	while (compteurDeNotes < 7)
	{
		printf("%d. %s\n", compteurDeNotes+1, types[compteurDeNotes]) ;
		compteurDeNotes ++ ;
	}
	while (principal <= 0 || principal > 14) 
	{
		scanf("%d", &principal) ;
		if (principal <= 0 || principal > 14)
		{
			printf("Valeur invalide.\n") ;
		}
	}
	principal = ((principal -1) * 14) ; //On se prépare à former la variable qui cumulera les deux.
	compteurDeNotes = 0 ; //On propose à nouveau tous les choix.
	
	system(clear) ;
	printf("Veuillez choisir un style secondaire.\n") ;
	while (compteurDeNotes < 7)
	{	
		printf("%d. %s\n", compteurDeNotes+1, types[compteurDeNotes]) ;
		compteurDeNotes ++ ;
	}
	while (secondaire + 1 <= 0 || secondaire + 1 > 15)
	{
		scanf("%d", &secondaire) ;
		if (secondaire + 1 <=0 || secondaire + 1 > 15)
		{
			printf("Valeur invalide.\n") ;
		}
	}

	style = principal + secondaire ;
	printf("Le stye a été correctement entré. Code : %d\n", style) ;
	printf("Appuyez sur Entrée pour continuer.\n") ;
	getchar() ;
	system(clear) ;
	fichier = fopen(nomDeFichier, "w+") ;
	fprintf(fichier, "%d\n", style) ;
	fprintf(fichier, "3\n") ; //Tous les nouveaux coureurs commencent au potentiel 3
	fclose(fichier) ;
	return 0 ;
}
