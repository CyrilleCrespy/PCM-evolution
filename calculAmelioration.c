int calculAmelioration(int noteActuelle, int *points, int *maximum, int noteInitiale, int *potentiel, int potentielInitial)
{
	int entreeMenu = 3 ;
	system(clear) ;
	while (entreeMenu != 1 && entreeMenu != 2)
	{
		int typeAugmentation ;
		
		system(clear) ;
		printf("Voulez-vous augmenter ou diminuer la note ?\n") ;
		printf("Rappel : vous ne pourrez pas descendre la note en-dessous du niveau qu'elle avait au d%sbut de la session.\n", é) ;
		printf("0. Annuler.\n") ;
		printf("1. Augmenter.\n") ;
		printf("2. Diminuer.\n") ;
			
		typeAugmentation = verifierAugmentationPotentiel(potentiel) ;
		
		if(potentielInitial == *potentiel && (typeAugmentation == 1 || typeAugmentation == 2)) //Uniquement si le potentiel ne vient pas d'être augmenté.
		//Et si une évolution est possible par points d'évolution (1) ou points de chaîne (2).
		{	
			printf("3. Augmenter le potentiel.\n") ;
			entreeMenu = verificationEntreeNumerique(0, 3) ;
		}
		else
		{
		entreeMenu = verificationEntreeNumerique(0, 2) ;
		}

		switch (entreeMenu)
		{
			case 0 :
				return 0 ;
				break ;
			case 1 :
				noteActuelle = calculAugmentation(noteActuelle, points, maximum) ;
				break ;
			case 2 :
				noteActuelle = calculDiminution(noteActuelle, points, noteInitiale) ;
				break ;
			case 3 :
				if(potentielInitial == *potentiel && (typeAugmentation == 1 || typeAugmentation == 2))
				{
					calculPotentiel(noteActuelle, potentiel, maximum, typeAugmentation, points) ;
				}
				return noteActuelle ;
			default :
				printf("Exception inattendue dans calculAmelioration.c, int calculAmelioration.\n") ;
				exit(EXIT_FAILURE) ;
		}
	}
	return noteActuelle ;
}

int calculAugmentation(int noteActuelle, int *points, int *maximum)
{
	int coutEvolution[50] = {0} ;
	int augmentationMax = 0 ;
	int noteFictive = noteActuelle ;
	int continuerBoucle = 1 ;
	int compteur = 0 ;
	int augmentationVoulue ;
	int raisons[3] = {0} ;
	
	while (continuerBoucle == 1)
	{
		noteFictive ++ ;
		augmentationMax ++ ;
		
		coutEvolution[compteur] = 1 + coutEvolution[compteur] + (noteFictive / 61) + (noteFictive / 66) + (noteFictive / 71) + (noteFictive / 76) + (noteFictive / 81) ;
		if(noteFictive > *maximum)
		{
			augmentationMax -- ;
			raisons[0] = 1 ;
			continuerBoucle = 0 ;
		}
		if (coutEvolution[compteur] > *points)
		{
			augmentationMax -- ;
			raisons[1] = 1 ;
			continuerBoucle = 0 ;
		}
		if (raisons[0] == 0 && raisons[1] == 0)
		{
			compteur ++ ;
			coutEvolution[compteur] = coutEvolution[compteur - 1] ; //Le prochain achat coûtera le coût du précédent, plus le complément calculé dans la prochaine itération de la boucle.
		}
	}
	
	compteur = 0 ;
	system(clear) ;

	if (augmentationMax > 0)
	{
		printf("Augmentation(s) possible(s).\n") ;
	}
	while (compteur < augmentationMax)
	{
		printf("%d. Augmenter la note %d fois pour %d point(s) d'%svolution (passer %s %d).\n", compteur + 1, compteur + 1, coutEvolution[compteur], é, à, noteActuelle + compteur + 1) ;
		compteur ++ ;
	}
	printf ("Voici la ou les raison(s) qui ne permettent pas d'augmenter au-del%s de ces possibilit%ss :\n", à, é) ;
	if (raisons[0] == 1)
	{
		printf("Potentiel trop faible pour augmenter davantage (potentiel : %d).\n", *maximum) ;
	}
	if (raisons[1] == 1)
	{
		printf("Tu n'as plus assez de points d'%svolution pour augmenter davantage.\n", é) ;
	}
	
	if (augmentationMax > 0)
	{
		printf("Tape 0 pour annuler cette demande.\n") ;
		augmentationVoulue = verificationEntreeNumerique(0, augmentationMax) ;
	}
	else
	{
		printf("Appuie sur Entr%se pour continuer.\n", é) ;
		remplirJournal("Augmentation annul%se car impossible.") ;
		getchar() ;
		return noteActuelle ;
	}
	
	if (augmentationVoulue != 0 && augmentationVoulue <= augmentationMax)
	{
		noteActuelle = noteActuelle + augmentationVoulue ;
		*points = *points - coutEvolution[augmentationVoulue - 1] ;
		pointsDepenses = pointsDepenses + coutEvolution[augmentationVoulue - 1] ;
		getchar() ;
		remplirJournal("Augmentation validée.") ;
		
		return noteActuelle ;
	}
	else
	{
		printf("Augmentation impossible.\n") ;
		remplirJournal("Augmentation requise impossible.") ;
		return noteActuelle ;
	}
}

int calculDiminution(int noteActuelle, int *points, int noteInitiale)
{
	int pointsRedonnes[50] = {0} ;
	int diminutionMax = noteActuelle - noteInitiale ;
	int noteFictive = noteActuelle ;
	int continuerBoucle = 1 ;
	int compteur = 0 ;
	int diminutionVoulue ;
	
	if (diminutionMax == 0) //Si aucune amélioration n'a été faite depuis le lancement.
	{
		printf("Vous n'avez pas augment%s cette note durant cette session. Diminution impossible.\n", é) ;
		printf("Appuie sur Entr%se pour continuer.\n", é) ;
		remplirJournal("Diminution impossible.") ;
		getchar() ;
		getchar() ;
		return noteActuelle ;
	}
	
	while (continuerBoucle == 1)
	{
		pointsRedonnes[compteur] = 1 + pointsRedonnes[compteur] + (noteFictive / 61) + (noteFictive / 66) + (noteFictive / 71) + (noteFictive / 76) + (noteFictive / 81) ;
		noteFictive -- ;
		compteur ++ ;
		pointsRedonnes[compteur] = pointsRedonnes[compteur-1] ;
		if (compteur + 1 > diminutionMax)
		{
			pointsRedonnes[compteur] = 1 + pointsRedonnes[compteur] + (noteFictive / 61) + (noteFictive / 66) + (noteFictive / 71) + (noteFictive / 76) + (noteFictive / 81) ;
			break ;
		}
	}
	
	compteur = 0 ;
	system(clear) ;

	printf("Diminution(s) possible(s).\n") ;
	while (compteur < diminutionMax)
	{
		printf("%d. Diminuer la note %d fois pour %d point(s) d'%svolution (passer %s %d).\n", compteur + 1, compteur + 1, pointsRedonnes[compteur], é, à, noteActuelle - (compteur + 1)) ;
		compteur ++ ;
	}
	printf("Tape 0 pour annuler cette demande.\n") ;
	diminutionVoulue = verificationEntreeNumerique (0, diminutionMax) ;
	if (diminutionVoulue != 0)
	{
		noteActuelle = noteActuelle - diminutionVoulue ;
		*points = *points + pointsRedonnes[diminutionVoulue] - 1 ;
		pointsDepenses = pointsDepenses - pointsRedonnes[diminutionVoulue] ;
		remplirJournal("Diminution validée.") ;
	}
	else
	{
		remplirJournal("Diminution annulée.") ;
	}
	return noteActuelle ;
}

void calculPotentiel (int noteActuelle, int *potentiel, int *maximum, int typeAugmentation, int *points)
{
	int choix = -1 ;
	int augmentationPossible = 0 ;
	
	int coutAugmentationPotentiel = determinerCoutPotentiel(potentiel) ;
	char messageJournal[100] = {0} ;
	
	viderBuffer() ;
	system(clear) ;
	
	printf("Tu ne peux augmenter ton potentiel que trois fois durant toute la carri%sre. Une fois par session.\n", è) ;
	printf("Appuie sur Entr%se pour continuer.\n", é) ;
	
	getchar() ;
	
	if (noteActuelle == 85)
	{
		printf("Note au maximum permis par le jeu.\n") ;
		printf("Appuie sur Entr%se pour continuer.\n", é) ;
		getchar() ;
		return ;
	}
	else if (typeAugmentation == 1 && coutAugmentationPotentiel > *points)
	{
		printf("Pas assez de points d'%svolution pour cet achat.\n", é) ;
		printf("Appuie sur Entr%se pour continuer.\n", é) ;
		getchar() ;
		return ;
	}
	
	augmentationPossible = determinationAugmentationPotentielPossible(maximum) ;
	
	if (typeAugmentation == 1)
	{
		printf("Veux-tu augmenter ton potentiel dans cette note de %d points pour %d points d'%svolution ?\n", augmentationPossible, coutAugmentationPotentiel, é) ;
	}
	else if (typeAugmentation == 2)
	{
		printf("Veux-tu augmenter ton potentiel dans cette note de %d points pour %d points de cha%sne ?\n", augmentationPossible, coutAugmentationPotentiel, î) ;
		printf("Assure-toi des les avoir, toute triche sera sanctionn%se.\n", é) ;
	}
	printf("0. Non\n") ;
	printf("1. Oui\n") ;

	choix = verificationEntreeNumerique (0, 1) ;
	if (choix == 0)
	{
		return ;
	}
	else if (typeAugmentation == 1)
	{
		*potentiel = *potentiel + 1 ;
		*maximum = *maximum + augmentationPossible ;
		*points = *points - coutAugmentationPotentiel ;
	}
	else
	{
		*potentiel = *potentiel + 1 ;
		*maximum = *maximum + augmentationPossible ;
		sprintf(messageJournal, "Augmentation de potentiel validée. Potentiel : %d.", *potentiel) ;
		remplirJournal(messageJournal) ;
	}
}

int verifierAugmentationPotentiel(int *potentiel)
{
	int positionInitiale ;
	int	typeAugmentation ;
	FILE* fichier = NULL ;
	int ligne = *potentiel - 1 ;
	positionInitiale = (ligne * 19) + 11 ;
	//On se place sur le bout de ligne qui correspond à la valeur décrivant le système d'évolution de potentiel,
	//sur la ligne correspondant au potentiel initial trouvé dans la fiche coureur,
	//Trois valeurs sont possibles. 0 : augmentation rendue volontairement impossible. 1 : points d'évolution. 2 : points de chaîne.
	fichier = fopen("configuration", "r") ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	fscanf(fichier, "%d", &typeAugmentation) ;
	fclose(fichier) ;
	return typeAugmentation ;
}

int determinerCoutPotentiel(int *potentiel)
{
	int positionInitiale ;
	int cout ;
	FILE* fichier = NULL ;
	int ligne = *potentiel - 1 ;
	positionInitiale = (ligne * 19) + 13 ;
	//On se place sur le bout de ligne qui correspond au coût pour augmenter le potentiel d'un point,
	//sur la ligne correspondant au potentiel initial trouvé dans la fiche coureur.
	//Coût noté sur cinq chiffres, comme 02000 pour 2 000 points de chaîne ou 0005 pour points de chaîne.
	fichier = fopen("configuration", "r") ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	fscanf(fichier, "%d", &cout) ;
	fclose(fichier) ;
	return cout ;
}

int determinationAugmentationPotentielPossible(int *maximum)
{
	int augmentationPossible ;
	int positionInitiale ;
	FILE* fichier = NULL ;
	positionInitiale = 133 + ((*maximum - 50) * 6) + 4 ;
	//133 représente le premier caractère de la première ligne qui décrit la configuration concernant le nombre de points d'augmentation possibles pour chaque note initiale.
	//6 est le décalage nécessaire pour passer à la note suivante.
	//4 place au bout de la ligne qui correspond à l'augmentation possible.
	fichier = fopen("configuration", "r") ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	fscanf(fichier, "%d", &augmentationPossible) ;
	fclose(fichier) ;
	return augmentationPossible ;
}
