void enregistrer(int session, int style, int coureur[], int potentiel, int principal, int secondaire, int taille, int poids, int mois, int jour, char *nationalite, char *course1, char *course2, char *course3, int notesInitiales[], int maximum[])
{	
	FILE* fichier = NULL ;
	suppressionEspace() ; //On retire les caractères de fin de ligne issus des données entrées par l'utilsateur.
	printf("Tentative d'ouverture de '%s.\n", nomDeFichier) ;
	fichier = fopen(nomDeFichier, "w+") ;
	char *types[7] = {"courses_par_étapes", "grimpeur", "sprint", "contre-la-montre", "puncheur",\
"baroud", "classiques_du_nord"} ; //Version avec les accents d'une même variable concernée ailleurs par les instructions de préprocesseur.

	if (remove(nomDeFichier) == 0) //Suppression du fichier avec les données
	{
		printf("Fichier pr%sc%sdent supprim%s.\n", é, é, é) ;
	}

	fichier = fopen(nomDeFichier, "w+") ;
	if (fichier != NULL)
	{
		printf("Fichier %s ouvert.\n", nomDeFichier) ;
	}
	else
	{
		printf("Ouverture du fichier %s impossible.\n", nomDeFichier) ;
		perror("Erreur dans modification.c, void enregistrer.\n") ;
		exit(EXIT_FAILURE) ;
	}
	
	fprintf(fichier, u8"%d session\n", session) ;
	
	if (principal == secondaire)
	{
		fprintf(fichier, u8"%d spécialité principale : %s ; spécialité secondaire : aucune\n", style, types[principal]) ;
	}
	else
	{
		fprintf(fichier, u8"%d spécialité principale : %s ; spécialité secondaire : %s\n", style, types[principal], types[secondaire]) ;
	}
	
	fprintf(fichier, u8"%d taille\n", taille) ;
	fprintf(fichier, u8"%d poids\n", poids) ;
	fprintf(fichier, u8"%d/%d date de naissance\n", jour, mois) ;
	fprintf(fichier, u8"%d potentiel\n", potentiel) ;
	fprintf(fichier, u8"%s nationalité\n", nationalite) ;
	fprintf(fichier, u8"%s course favorite 1\n", course1) ;
	fprintf(fichier, u8"%s course favorite 2\n", course2) ;
	fprintf(fichier, u8"%s course favorite 3\n", course3) ;
	//D'avance, désolé pour cette immondice, mais l'écriture d'un fichier n'ayant pas les mêmes limitations que l'horrible ligne de commande Windows, on peut utiliser de vrais accents,
	//ce qui rend les //define complètement inopérants, et même gênants, on doit donc tout retaper à la main, sauf si quelqu'un a une meilleure idée.
	fprintf(fichier, u8"%d plaine (+ %d)\n", coureur[0], coureur[0] - notesInitiales[0]) ;
	fprintf(fichier, u8"%d montagne (+ %d)\n", coureur[1], coureur[1] - notesInitiales[1]) ;
	fprintf(fichier, u8"%d moyenne_montagne (+ %d)\n", coureur[2], coureur[2] - notesInitiales[2]) ;
	fprintf(fichier, u8"%d vallon (+ %d)\n", coureur[3], coureur[3] - notesInitiales[3]) ;
	fprintf(fichier, u8"%d contre-la-montre (+ %d)\n", coureur[4], coureur[4] - notesInitiales[4]) ;
	fprintf(fichier, u8"%d prologue (+ %d)\n", coureur[5], coureur[5] - notesInitiales[5]) ;
	fprintf(fichier, u8"%d pavés (+ %d)\n", coureur[6], coureur[6] - notesInitiales[6]) ;
	fprintf(fichier, u8"%d sprint (+ %d)\n", coureur[7], coureur[7] - notesInitiales[7]) ;
	fprintf(fichier, u8"%d accélération (+ %d)\n", coureur[8], coureur[8] - notesInitiales[8]) ;
	fprintf(fichier, u8"%d descente (+ %d)\n", coureur[9], coureur[9] - notesInitiales[9]) ;
	fprintf(fichier, u8"%d baroud (+ %d)\n", coureur[10], coureur[10] - notesInitiales[10]) ;
	fprintf(fichier, u8"%d endurance (+ %d)\n", coureur[11], coureur[11] - notesInitiales[11]) ;
	fprintf(fichier, u8"%d résistance (+ %d)\n", coureur[12], coureur[12] - notesInitiales[12]) ;
	fprintf(fichier, u8"%d récupération (+ %d)\n", coureur[13], coureur[13] - notesInitiales[13]) ;
	
	fprintf(fichier, u8"%d point(s) dépensé(s).\n", pointsDepenses) ;
	fclose(fichier) ;
	if(maximum != NULL)
	{
		enregistrerMax(maximum) ;
	}
	creerCopie() ;
}

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

int verifierDonnees(int session, int style, int coureur[], int potentiel, int principal, int secondaire, int taille, int poids, int mois, int jour, char *nationalite, char *course1, char *course2, char *course3)
{
	int compteur = 0 ;

	if (session < 1 || style < 0 || style > 48 || potentiel < 3 || potentiel > 8 || principal < 0 || principal > 7 || secondaire < 0 || secondaire > 7 || taille < 150 || taille > 200 || poids < 50 || poids > 100 || mois < 1 || mois > 12 || jour < 1 || jour > 31 || strlen(nationalite) == 0 || strlen(course1) == 0 || strlen(course2) == 0 || strlen(course3) == 0)
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
		putc(ch, fichier2) ;
	}
	fclose(fichier1) ;
	fclose(fichier2) ;
}
