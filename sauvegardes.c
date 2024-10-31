void enregistrerMax(int maximum[])
{
	FILE* fichier = NULL ;
	char fichierMax[255] ;
	int compteur = 0 ;
	
	sprintf(fichierMax, "%s_max", nomDeFichier) ;
	fichier = fopen(fichierMax, "w+") ;
	if(fichier == NULL)
	{
		printf("Erreur, impossible d'ouvrir %s. Dans sauvegardes.c, void enregistrerMax.\n", fichierMax) ;
	}
	else
	{
		while (compteur < 14)
		{
			fprintf(fichier, "%d\n", maximum[compteur]) ;
			compteur ++ ;
		}
	}
	fclose(fichier) ;
}

void creerCopie()
{
	FILE *fichier1, *fichier2 = NULL ;
	char fichierCopie[255] ;
	char ch ;
	
	sprintf(fichierCopie, "%s_cop", nomDeFichier) ;
	fichier1 = fopen(nomDeFichier, "r") ;
	fichier2 = fopen(fichierCopie, "w+") ;
	
	while((ch = getc(fichier1)) != EOF)
	{
		putc(ch, fichier2);
	}
	fclose(fichier1) ;
	fclose(fichier2) ;
}

int verifierDonnees(int style, int coureur[], int potentiel, int principal, int secondaire, int taille, int poids, int mois, int jour, char *nationalite, char *course1, char *course2, char *course3)
{
	int compteur = 0 ;

	if (style < 0 || style > 48 || potentiel < 3 || potentiel > 8 || principal < 0 || principal > 7 || secondaire < 0 || secondaire > 7 || taille < 150 || taille > 200 || poids < 50 || poids > 100 || mois < 1 || mois > 12 || jour < 1 || jour > 31 || strlen(nationalite) == 0 || strlen(course1) == 0 || strlen(course2) == 0 || strlen(course3) == 0)
	{
		printf("Erreur. Donn%ses enregistr%s impossibles.\n", é, é) ;
		getchar() ;
		return 0 ;
	}
	while (compteur < 14)
	{
		if (coureur[compteur] < 50 || coureur[compteur] > 85)
		{
			return 0 ;
		}
		compteur ++ ;
	}
	return 1 ;
}

void restaurerSauvegarde()
{
	FILE *fichier1, *fichier2 = NULL ;
	char fichierCopie[255] ;
	char ch ;
	
	sprintf(fichierCopie, "%s_cop", nomDeFichier) ;
	fichier1 = fopen(fichierCopie, "r") ;
	fichier2 = fopen(nomDeFichier, "w+") ;
	
	while((ch = getc(fichier1)) != EOF)
	{
		putc(ch, fichier2);
	}
	fclose(fichier1) ;
	fclose(fichier2) ;
}
