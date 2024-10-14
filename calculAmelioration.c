int calculAmelioration(int noteActuelle, int limiteMax, int points, int maximum[], int choix)
{
	int coutEvolution[10] = {0} ;
	int augmentationMax = 0 ;
	int noteFictive = noteActuelle ;
	int possible = 1 ;
	int compteur = 0 ;
	int augmentationVoulue ;
	
	while (possible == 1)
	{
		if(noteFictive > limiteMax || noteFictive > maximum[choix -1])
		{
			possible = 0 ;
			break ;
		}
		coutEvolution[compteur] = 1 + coutEvolution[compteur] + (noteFictive / 60) + (noteFictive / 65) + (noteFictive / 70) + (noteFictive / 75) + (noteFictive / 80) ;
		if (coutEvolution[compteur] > points)
		{
			possible = 0 ;
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
	while (compteur < augmentationMax)
	{
		printf("%d. Augmenter la note %d fois pour %d point(s) d'%svolution (passer à %d).\n", compteur, compteur, coutEvolution[compteur - 1], é, noteActuelle + compteur) ;
		compteur ++ ;
	}
	scanf("%d", &augmentationVoulue) ;
	if (coutEvolution[augmentationVoulue] != 0)
	{
		noteActuelle = noteActuelle + augmentationVoulue ;
	}
	return noteActuelle ;
}
