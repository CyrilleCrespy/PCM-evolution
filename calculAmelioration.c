int calculAmelioration(int noteActuelle, int limiteMax, int *points, int maximum[], int choix, int noteInitiale)
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
		scanf("%d", &entreeMenu) ;

		if (entreeMenu == 0)
		{
			return 0 ;
		}
		else if (entreeMenu == 1)
		{
			noteActuelle = calculAugmentation(noteActuelle, limiteMax, points, maximum, choix) ;
		}
		else if (entreeMenu == 2)
		{
			noteActuelle = calculDiminution(noteActuelle, points, noteInitiale) ;
		}
		else
		{
			printf("Entrée incorrecte.\n") ;
		}
	}
	return noteActuelle ;
}

int calculAugmentation(int noteActuelle, int limiteMax, int *points, int maximum[], int choix)
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
		if(noteFictive > limiteMax)
		{
			augmentationMax -- ;
			raisons[0] = 1 ;
			continuerBoucle = 0 ;
		}
		if(noteFictive > maximum[choix - 1])
		{
			augmentationMax -- ;
			raisons[1] = 1 ;
			continuerBoucle = 0 ;
		}
		if (coutEvolution[compteur] > *points)
		{
			augmentationMax -- ;
			raisons[2] = 1 ;
			continuerBoucle = 0 ;
		}
		if (raisons[0] == 0 && raisons[1] == 0 && raisons[2] == 0)
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
		printf("Potentiel trop faible pour augmenter davantage (note maximale du potentiel : %d).\n", limiteMax) ;
	}
	if (raisons[1] == 1)
	{
		printf("La note atteint d%sj%s le plafond (%d) permis par ce type de coureur.\n", é, à, maximum[choix - 1]) ;
	}
	if (raisons[2] == 1)
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
	
	if (augmentationVoulue != 0)
	{
		noteActuelle = noteActuelle + augmentationVoulue ;
		*points = *points - coutEvolution[augmentationVoulue - 1] ;
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
		printf("Appuyez sur Entr%se pour continuer.\n", é) ;
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
	}
	return noteActuelle ;
}
