int calculAmelioration(int noteActuelle, int *points, int *maximum, int choix, int noteInitiale, int *potentiel, int potentielInitial)
{
	int entreeMenu = 3 ;
	system(clear) ;
	while (entreeMenu != 1 && entreeMenu != 2)
	{
		system(clear) ;
		printf("Voulez-vous augmenter ou diminuer la note ?\n") ;
		printf("Rappel : vous ne pourrez pas descendre la note en-dessous du niveau qu'elle avait au d%sbut de la session.\n", é) ;
		printf("0. Annuler.\n") ;
		printf("1. Augmenter.\n") ;
		printf("2. Diminuer.\n") ;
		if(potentielInitial == *potentiel) //Uniquement si le potentiel ne vient pas d'être augmenté.
		{	
			printf("3. Augmenter le potentiel.\n") ;
		}
		scanf("%d", &entreeMenu) ;

		switch (entreeMenu)
		{
			case 0 :
				return 0 ;
				break ;
			case 1 :
				noteActuelle = calculAugmentation(noteActuelle, points, maximum, choix) ;
				break ;
			case 2 :
				noteActuelle = calculDiminution(noteActuelle, points, noteInitiale) ;
				break ;
			case 3 :
				if(potentielInitial == *potentiel)
				{
					calculPotentiel(noteActuelle, points, potentiel, maximum) ;
				}
				return noteActuelle ;
			default :
				printf("Entrée incorrecte.\n") ;
		}
	}
	return noteActuelle ;
}

int calculAugmentation(int noteActuelle, int *points, int *maximum, int choix)
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
	

	
	compteur = 1 ;
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
		scanf("%d", &augmentationVoulue) ;
	}
	else
	{
		printf("Appuie sur Entr%se pour continuer.\n", é) ;
		getchar() ;
		return noteActuelle ;
	}
	
	if (augmentationVoulue != 0 && augmentationVoulue < augmentationMax)
	{
		noteActuelle = noteActuelle + augmentationVoulue ;
		*points = *points - coutEvolution[augmentationVoulue - 1] ;
		pointsDepenses = pointsDepenses + coutEvolution[augmentationVoulue - 1] ;
		getchar() ;
	}
	return noteActuelle ;
}

int calculDiminution(int noteActuelle, int *points, int noteInitiale)
{
	int pointsRedonnes[50] ;
	int diminutionMax = noteActuelle - noteInitiale ;
	int noteFictive = noteActuelle ;
	int continuerBoucle = 1 ;
	int compteur = 0 ;
	int diminutionVoulue ;
	
	pointsRedonnes[0] = -1 ;
	
	if (diminutionMax == 0) //Si aucune amélioration n'a été faite depuis le lancement.
	{
		printf("Vous n'avez pas augment%s cette note durant cette session. Diminution impossible.\n", é) ;
		printf("Appuie sur Entr%se pour continuer.\n", é) ;
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
	scanf("%d", &diminutionVoulue) ;
	if (pointsRedonnes[diminutionVoulue] != 0)
	{
		noteActuelle = noteActuelle - diminutionVoulue ;
		*points = *points + pointsRedonnes[diminutionVoulue] ;
		pointsDepenses = pointsDepenses - pointsRedonnes[diminutionVoulue] ;
	}
	return noteActuelle ;
}

void calculPotentiel (int noteActuelle, int *points, int *potentiel, int *maximum)
{
	int choix = -1 ;
	int augmentation = 0 ;
	int cout = 2000 ;
	
	viderBuffer() ;
	system(clear) ;
	
	printf("Tu ne peux augmenter ton potentiel que trois fois durant toute la carri%sre. Une fois par session.\n", è) ;
	printf("Une %svolution co%sute %d points de chaîne.\n", é, û, *points) ;
	printf("Assure-toi des les avoir, toute triche sera sanctionn%se.\n", é) ;
	printf("Appuie sur Entr%se pour continuer.\n", é) ;
	
	getchar() ;
	
	if (noteActuelle < 75)
	{
		augmentation = 3 ;
	}
	else if (noteActuelle < 81)
	{
		augmentation = 2 ;
	}
	else if (noteActuelle < 85)
	{
		augmentation = 1 ;
	}
	else
	{
		printf("Note au maximum permis par le jeu.\n") ;
	}
	
	printf("Veux-tu augmenter ton potentiel dans cette note de %d points pour %d points de cha%sne ?\n", augmentation, cout, î) ;
	printf("0. Non\n") ;
	printf("1. Oui\n") ;

	while (choix != 0 && choix != 1)
	{
		scanf("%d", &choix) ;
		if (choix == 0)
		{
			continue ;
		}
		else if (choix == 1)
		{
			*potentiel = *potentiel + 1 ;
			*maximum = *maximum + augmentation ;
		}
		else
		{
			printf("Entr%se invalide", é) ;
		}
	}
}
