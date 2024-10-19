FILE* fichier = NULL ;

int creation(char *caracteristiques[])
{
	int fichierOK = 0 ;
	int taille = 0 ;
	int notesBase[14] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50} ;
	int principal ;
	int secondaire ;
	int style ;
	
	while (fichierOK != 1)
	{
		fichierOK = choixNomDeFichier(caracteristiques) ;
	}
	
	principal = choixPrincipal() ;
	secondaire = choixSecondaire(principal) ;
	style = calculStyle(principal, secondaire) ;
	taille = choixTaille() ;
	/*choixPoids() ;
	choixDateDeNaissance() ;
	choixNationalite() ;
	choixCoursesFavorites() ;*/
	enregistrer(style, notesBase, 3, principal, secondaire, taille) ;
	modification(1, caracteristiques, taille) ;
	return 0 ;
}

int choixTaille()
{
	int taille = 0 ;
	int confirmation = 0 ;
	while ((taille < 150 || taille > 200) && confirmation != 1)
	{
		printf("Entrez votre taille en centimètres (entre 150 et 200).\n") ;
		scanf("%d", &taille) ;
		if (taille < 150)
		{
			printf("C'est trop petit pour le jeu (désolé).\n") ;
		}
		else if (taille > 200)
		{
			printf("C'est trop grand pour le jeu (désolé).\n") ;
		}
		else
		{
			printf("Taille entrée : %d centimètres.\n", taille) ;
			printf("0. Annuler \n") ;
			printf("1. Confirmer \n") ;
			scanf("%d", &confirmation) ;
		}
	}
	return taille ;
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

int choixPrincipal()
{
	int principal = -1;
	char cpe[30] ;
	sprintf(cpe, "Courses par %stapes", é) ;
	char *types[7] = {cpe, "Grimpeur", "Sprint", "Contre-la-montre", "Puncheur",\
"Baroud", "Classiques du Nord"} ;
	int compteurDeNotes = 0 ;
	system(clear) ; //Appel système différent selon le SE.
	printf("Veuillez choisir un style principal.\n") ;
	while (compteurDeNotes < 7)
	{
		printf("%d. %s\n", compteurDeNotes+1, types[compteurDeNotes]) ;
		compteurDeNotes ++ ;
	}
	while (principal <= 0 || principal > 7) 
	{
		scanf("%d", &principal) ;
		if (principal <= 0 || principal > 7)
		{
			printf("Valeur invalide.\n") ;
		}
	}
	return (principal - 1) ;
}

int choixSecondaire(int principal)
{
	int secondaire = -1 ;
	char cpe[30] ;
	sprintf(cpe, "Courses par %stapes", é) ;
	int compteurDeNotes = 0 ;
	sprintf(cpe, "Courses par %stapes", é) ;
	char *types[7] = {cpe, "Grimpeur", "Sprint", "Contre-la-montre", "Puncheur",\
"Baroud", "Classiques du Nord"} ;
	
	system(clear) ;
	printf("Veuillez choisir un style secondaire.\n") ;
	while (compteurDeNotes < 7)
	{	
		if (compteurDeNotes == principal)
		{
			printf("%d. Pas de spécialité secondaire\n", compteurDeNotes + 1) ;
			compteurDeNotes ++ ;
		}
		else
		{
			printf("%d. %s\n", compteurDeNotes + 1, types[compteurDeNotes]) ;
			compteurDeNotes ++ ;
		}
	}
	while (secondaire + 1 <= 0 || secondaire + 1 > 15)
	{
		scanf("%d", &secondaire) ;
		if (secondaire + 1 <=0 || secondaire + 1 > 15)
		{
			printf("Valeur invalide.\n") ;
		}
	}
	return (secondaire - 1) ;
}

int calculStyle(int principal, int secondaire)
{
	int style ;
	principal = ((principal) * 14) ;
	style = principal + secondaire + 1 ;
	printf("Le stye a été correctement entré. Code : %d\n", style) ;
	printf("Appuyez sur Entr%se pour continuer.\n", é) ;
	getchar() ;
	system(clear) ;
	
	return style ;
}
