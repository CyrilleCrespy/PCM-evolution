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
		printf("1 Augmenter.\n") ;
		printf("2 Diminuer.\n") ;
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
	int coutEvolution[50] = {-1} ;
	int augmentationMax = 0 ;
	int noteFictive = noteActuelle ;
	int continuerBoucle = 1 ;
	int compteur = 0 ;
	int augmentationVoulue ;
	
	while (continuerBoucle == 1)
	{
		if(noteFictive >= limiteMax || noteFictive >= maximum[choix -1])
		{
			continuerBoucle = 0 ;
			break ;
		}
		coutEvolution[compteur] = 1 + coutEvolution[compteur] + (noteFictive / 61) + (noteFictive / 66) + (noteFictive / 71) + (noteFictive / 76) + (noteFictive / 81) ;
		if (coutEvolution[compteur] > *points)
		{
			continuerBoucle = 0 ;
			coutEvolution[compteur] = 0 ; //L'achat étant impossible, on passe son coût à 0 pour qu'il ne soit pas proposé.
		}
		else
		{
			noteFictive ++ ;
			augmentationMax ++ ;
			compteur ++ ;
			coutEvolution[compteur] = coutEvolution[compteur-1] ; //Le prochain achat coûtera le coût du précédent, plus le complément calculé dans la prochaine itération de la boucle.
		}
	}
	
	if (augmentationMax == 0)
	{
		return noteActuelle ;
	}
	
	compteur = 1 ;
	system(clear) ;

	printf("Augmentation(s) possible(s).\n") ;
	while (compteur <= augmentationMax)
	{
		printf("%d. Augmenter la note %d fois pour %d point(s) d'%svolution (passer %s %d).\n", compteur, compteur, coutEvolution[compteur], é, à, noteActuelle + compteur) ;
		compteur ++ ;
	}
	scanf("%d", &augmentationVoulue) ;
	if (coutEvolution[augmentationVoulue] != 0)
	{
		noteActuelle = noteActuelle + augmentationVoulue ;
		*points = *points - coutEvolution[augmentationVoulue] ;
	}
	return noteActuelle ;
}

int calculDiminution(int noteActuelle, int *points, int noteInitiale)
{
	int pointsRedonnes[50] = {-1} ;
	int diminutionMax = noteActuelle - noteInitiale ;
	int noteFictive = noteActuelle ;
	int continuerBoucle = 1 ;
	int compteur = 0 ;
	int diminutionVoulue ;
	
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
	
	compteur = 1 ;
	system(clear) ;

	printf("Diminution(s) possible(s).\n") ;
	while (compteur <= diminutionMax)
	{
		printf("%d. Diminuer la note %d fois pour %d point(s) d'%svolution (passer %s %d).\n", compteur, compteur, pointsRedonnes[compteur], é, à, noteActuelle - compteur) ;
		compteur ++ ;
	}
	scanf("%d", &diminutionVoulue) ;
	if (pointsRedonnes[diminutionVoulue] != 0)
	{
		noteActuelle = noteActuelle - diminutionVoulue ;
		*points = *points + pointsRedonnes[diminutionVoulue] ;
	}
	return noteActuelle ;
}
