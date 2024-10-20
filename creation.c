FILE* fichier = NULL ;

int creation(char *caracteristiques[])
{
	int fichierOK = 0 ;
	int taille = 0 ;
	int notesBase[14] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50} ;
	int principal ;
	int secondaire ;
	int style ;
	int poids ;
	int jourMax = 0 ;
	int mois ;
	int jour ;
	char nationalite[100] ;
	char course1[100] ;
	char course2[100] ;
	char course3[100] ;
	
	while (fichierOK != 1)
	{
		fichierOK = choixNomDeFichier(caracteristiques) ;
	}
	
	principal = choixPrincipal() ;
	secondaire = choixSecondaire(principal) ;
	style = calculStyle(principal, secondaire) ;
	taille = choixTaille() ;
	poids = choixPoids() ;
	mois = choixMoisDeNaissance() ;
	if (mois == 2)
	{
		jourMax = 28 ;
	}
	else if (mois % 2 == 0)
	{
		jourMax = 30 ;
	}
	else
	{
		jourMax = 31 ;
	}
	jour = choixJourDeNaissance(jourMax) ;
	
	strcpy(nationalite,choixNationalite()) ;
	
	strcpy(course1, choixCourseFavorite(1)) ;
	strcpy(course2, choixCourseFavorite(2)) ;
	strcpy(course3, choixCourseFavorite(3)) ;
	
	enregistrer(style, notesBase, 3, principal, secondaire, taille, poids, mois, jour, nationalite, course1, course2, course3) ;
	modification(1, caracteristiques, taille) ;
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

int choixNomDeFichier()
{
	unsigned char choix = 0 ;
	printf("Entre le num%sro d'inscription qui t'a %st%s donn%s.\n", é, é, é, é) ;
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

int choixTaille()
{
	int taille = 0 ;
	int confirmation = 0 ;
	while ((taille < 150 || taille > 200) && confirmation != 1)
	{
		printf("Entre ta taille en centim%stres (entre 150 et 200).\n", è) ;
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
			printf("Taille entr%se : %d centim%stres.\n", é, taille, è) ;
			printf("0. Annuler \n") ;
			printf("1. Confirmer \n") ;
			scanf("%d", &confirmation) ;
		}
	}
	return taille ;
}

int choixPoids()
{
	int poids = 0 ;
	int confirmation = 0 ;
	while ((poids < 150 || poids > 200) && confirmation != 1)
	{
		printf("Entre ton poids en kilos (entre 50 et 100).\n") ;
		scanf("%d", &poids) ;
		if (poids < 50)
		{
			printf("C'est trop peu pour le jeu (d%ssol%s).\n", é, é) ;
		}
		else if (poids > 100)
		{
			printf("C'est trop pour le jeu (d%ssol%s).\n", é, é) ;
		}
		else
		{
			printf("Taille entr%se : %d kilos.\n", é, poids) ;
			printf("0. Annuler \n") ;
			printf("1. Confirmer \n") ;
			scanf("%d", &confirmation) ;
		}
	}
	return poids ;
}

int choixMoisDeNaissance()
{
	int mois = 0 ;
	printf("Nous allons choisir ta date de naissance pour ton coureur n%s en 2006.\n", é) ;
	printf("Choisis un mois.\n") ;
	printf("1.  Janvier\n2.  F%svrier\n3.  Mars\n4.  Avril\n5.  Mai\n6.  Juin\n7.  Juillet\n8.  Ao%st\n\
9.  Septembre\n10. Octobre\n11. Novembre\n12. D%scembre\n", é, û, é) ;
	while (mois < 1 || mois > 12)
	{
		scanf("%d", &mois) ;
		if (mois < 1 || mois > 12)
		{
			printf("Mois invalide.\n") ;
		}
		else
		{
			return mois ;
		}
	}
	return 0 ;
}

int choixJourDeNaissance(int jourMax)
{
	printf("Choisis un jour du mois, entre 1 et %d.\n", jourMax) ;
	int jour = 0 ;
	while(jour < 1 || jour > jourMax)
	{
		scanf("%d", &jour) ;
		if (jour < 1 || jour > jourMax)
		{
			printf("Mois invalide.\n") ;
		}
		else
		{
			return jour ;
		}
	}
	return 0 ;
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

char *choixNationalite()
{
	static char nationalite[100] = {0} ;
	char premiereLettre ;
	while (nationalite[0] == 0)
	{
		printf("Choisis ta nationalit%s.\n", é) ;
		printf("Premi%sre lettre (en majuscule) ?\n", è) ;
		getchar() ;
		scanf("%c", &premiereLettre) ;
		strcpy(nationalite, propositionDonnees(1, premiereLettre)) ;
	}
	return nationalite ;
}

char *choixCourseFavorite(int iteration)
{
	static char courseFavorite[100] ;
	char premiereLettre ;
	
	memset(courseFavorite, 0, 50) ;
	
	while (courseFavorite[0] == 0)
	{
		printf("Choisis ta course favorite n%s%d.\n", symboleNumero, iteration) ;
		printf("Premi%sre lettre (en majuscule) ?\n", è) ;
		getchar() ;
		scanf("%c", &premiereLettre) ;
		strcpy(courseFavorite, propositionDonnees(2, premiereLettre)) ;
	}
	return courseFavorite ;
}

char *propositionDonnees(int typeFichiers, char premiereLettre)
{
	FILE* fichier = NULL ;
	if (typeFichiers == 1)
	{
		fichier = fopen("pays", "r") ;
	}
	else if (typeFichiers == 2)
	{
		fichier = fopen("courses", "r") ;
	}
	char lettreFichier = '0' ;
	char dump[500] ;
	char *affichage[100] ;
	int compteur ;
	static char donnee[100] ;
	int choix ;
	
	compteur = 0 ;
	while(premiereLettre != lettreFichier) //On écarte les données qui précèdent la lettre désirée.
	{
		lettreFichier = fgetc(fichier) ;
		if(premiereLettre != lettreFichier)
		{
			fgets(dump, 500, fichier) ;
		}
	}
	while (1)
	{
		while (premiereLettre == lettreFichier)
		{
			fseek(fichier, -1, SEEK_CUR) ; //On se repositionne en début de ligne pour compenser le fgetc.
			affichage[compteur] = malloc(sizeof(char[100])) ;
			fgets(affichage[compteur], 500, fichier) ;
			printf("%d. %s", compteur + 1, affichage[compteur]) ;
			compteur ++ ;
			lettreFichier = fgetc(fichier) ;
		}
		printf("Entre le num%sro de ton choix (0 pour annuler).\n", é) ;
		scanf("%d", &choix) ;
		if (choix == 0)
		{
			memset(donnee, 0, 100) ;
			return donnee ;
		}
		else if (choix > 0 && choix <= compteur + 1)
		{
			strcpy(donnee, affichage[choix - 1]) ;
			return donnee ;
		}
		else
		{
			printf("Entr%se invalide.\n", é) ;
		}
	}
	return donnee ;
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
			printf("%d. Pas de sp%scialit%s secondaire\n", compteurDeNotes + 1, é, é) ;
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
	printf("Le stye a %st%s correctement entr%s. Code : %d\n", é, é, é, style) ;
	printf("Appuyez sur Entr%se pour continuer.\n", é) ;
	getchar() ;
	system(clear) ;
	
	return style ;
}
