/* Ceci est un programme développé spécifiquement pour les besoins des carrières collaboratives
 * sur Pro cycling manager. Il permet de créer des fiches de coureur, et de savoir quelles évolutions
 * sont possibles en fonction du nombre de points de chaînes disponibles pour l'utilisateur.
Copyright (C) 2024  Cyrille Crespy

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "PCM_Évolution.h"

char nomDeFichier[255] ; //Limite imposée par le NTFS, pour plus de compatibilité.
FILE* fichier = NULL ;
char paves[10] ;
int points ;
char *types[7] = {"Courses par étapes", "Grimpeur", "Sprint", "Contre-la-montre", "Puncheur",\
"Baroud", "Classiques du Nord"} ;

int main(int argc, char *argv[])
{
	static char paves[10] ;
	sprintf(paves, "pav%ss", é) ;
	static char acceleration[20] ;
	sprintf(acceleration, "acc%sl%sration", é, é) ;
	static char resistance[15] ;
	sprintf(resistance, "r%ssistance", é) ;
	static char recuperation[20] ;
	sprintf(recuperation, "r%scup%sration", é, é) ;
	unsigned char choix = 5 ;
	char *caracteristiques[14] = {"plaine", "montagne", "moyenne montagne", "vallon",\
"contre-la-montre", "prologue", paves, "sprint", acceleration, "descente", "baroud",\
"endurance", resistance, recuperation} ;

	while(choix != 0) //Répétion du menu tant que l'utilisateur n'a pas demandé à quitter.
	{
		printf("Bienvenue dans PCM %svolution.\n", É) ; //Variable définie selon l'OS pour les accents.
		printf("Menu.\n") ;
		printf("1. Cr%sation de fiche coureur.\n", é) ;
		printf("2. Modification de fiche coureur.\n") ;
		printf("Quitter avec 0.\n") ;
		scanf("%hhu", &choix) ;
		if (choix == 1)
		{
			creation(caracteristiques) ;
			return 0 ;
		}
		else if (choix == 2)
		{
			demandeNomDeFichier() ;
			return 0 ;
		}
	}
	return 0 ;
}

int creation(char *caracteristiques[])
{
	int fichierOK = 0 ;
	while (fichierOK != 1)
	{
		fichierOK = choixNomDeFichier(caracteristiques) ;
	}
	choixStyle() ;
	entreeStats() ;
	return 0 ;
}

int choixNomDeFichier()
{
	unsigned char choix = 0 ;
	printf("Veuillez choisir un nom de fichier.\n") ;
	scanf("%s", &nomDeFichier[0]) ;
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

int choixStyle()
{
	int principal = -1;
	int secondaire = -1;

	int style ;
	int compteurDeNotes = 0 ;

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
	fclose(fichier) ;
	return 0 ;
}

int verificationExistanceDuFichier ()
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

int entreeStats()
{
	int compteurDeNotes = 0 ;
	while(compteurDeNotes < 14)
	{
		fichier = fopen(nomDeFichier, "a") ;
		fprintf(fichier, "%d\n", 50) ;
		fclose(fichier) ;
		compteurDeNotes ++ ;
	}
	modification(1) ;
	return 0 ;
}

int demandeNomDeFichier()
{
	printf("Veuillez choisir un nom de fichier.\n") ;
	scanf("%s", &nomDeFichier[0]) ;
	modification(0) ;
	return 0 ;
}

int modification(int nouveau)
{
	FILE* fichier = NULL ;
	system(clear) ;
	int choix = 999 ;
	points = 0 ;
	int coureur[14] = {0} ;
	int style = 0 ;
	int principal = 0 ;
	int secondaire = 0 ;
	int compteur ;

	int maximum[14] = {0} ;

	fichier = fopen(nomDeFichier, "r") ;
	fscanf(fichier, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &style, &coureur[0], &coureur[1], &coureur[2],\
&coureur[3], &coureur[4], &coureur[5], &coureur[6], &coureur[7], &coureur[8], &coureur[9], &coureur[10],\
&coureur[11], &coureur[12], &coureur[13]) ;
	principal = style / 14 ;
	secondaire = (style % 14) - 1 ;
	fclose(fichier) ;

	printf("Ton style principal est %s et ton style secondaire %s.\n", types[principal], types[secondaire]) ;

	if(nouveau == 1)
	{
		points = 50 ;
		printf("En tant que nouveau coureur, tu as droit à 50 points.\n") ;
	}

	else
	{
		printf("Combien de points d'am%slioration as-tu ?\n", î) ;
		scanf("%d", &points) ;
	}

	for (compteur = 0 ; compteur < 14 ; compteur ++)
	{
		maximum[compteur] = determinerNotesMax(principal, secondaire, compteur) ;
	}

	while (choix != 0)
	{
		printf("1. Plaine : %d (max : %d).\n2. Montagne : %d (max : %d).\n3. Moyenne montagne (max : %d): %d.\n4. Vallon (max : %d): %d.\n\
5. Contre-la-montre : %d (max : %d).\n6. Prologue : %d (max : %d).\n7. Pav%ss : %d (max : %d).\n8. Sprint : %d (max : %d).\n\
9. Acc%sl%sration : %d (max : %d).\n10. Descente : %d (max : %d).\n11. Baroud : %d (max : %d).\n12. Endurance : %d (max : %d).\n\
13. R%ssistance : %d (max : %d).\n14. R%scup%sration : %d (max : %d).\n15. Sauvegarder les changements.\n", coureur[0], maximum[0], coureur[1],\
maximum[1], coureur[2], maximum[2], coureur[3], maximum[3], coureur[4], maximum[4], coureur[5], maximum[5], é, coureur[6], maximum[6],\
coureur[7], maximum[7], é, é, coureur[8], maximum[8], coureur[9], maximum[9], coureur[10], maximum[10], coureur[11], maximum[11], é,\
coureur[12], maximum[12], é, é, coureur[13], maximum[13]) ;
		printf("Tu as %d points d'am%slioration restants.\n", points, î) ;

		if (points < 1)
		{
			printf("Tu n'as pas assez de points pour am%sliorer ton coureur. %s la prochaine !\n", é, À) ;
			return 0 ;
		}

		printf("Entrez 0 pour quitter le programme, ou le chiffre correspondant %s la note que vous voulez changer.\n", à) ;
		scanf("%d", &choix) ;

		if (choix == 0)
		{
			printf("Merci d'avoir utilis%s PCM %svolution !\n", é, É) ;
			return 0 ;
		}
		else if (choix == 15)
		{
			enregistrer(style, coureur) ;
			return 0 ;
		}
		else if (coureur[choix-1] >= 85)
		{
			printf("Cette caract%sristique est d%sj%s au maximumimum.\n", é, é, à) ;
			continue ;
		}

		coureur[choix-1] = calculAmelioration(coureur[choix-1]) ; //La liste commençant à l'indice 0, on compense.
	}
	return 0 ;
}

int calculAmelioration(int caracteristique)
{
	int choix = 0 ;	
	printf("Tu as actuellement %d dans cette caract%sristique.\n", caracteristique, é) ;
	if (caracteristique < 60)
	{
		printf("Veux-tu d%spenser 1 point d'am%slioration pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points -- ;
			caracteristique ++ ;
			return caracteristique ;
		}
		else
		{
			return 0 ;
		}
	}
	else if (caracteristique <= 65 && points >= 800)
	{
		printf("Veux-tu d%spenser 2 points d'am%slioration pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points = points - 2 ;
			caracteristique ++ ;
			return caracteristique ;
		}
		else
		{
			return 0 ;
		}
	}
	else if (caracteristique <= 70 && points >= 1000)
	{
		printf("Veux-tu d%spenser 3 points d'am%slioration pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points = points - 3 ;
			caracteristique ++ ;
			return caracteristique ;
		}
		else
		{
			return 0 ;
		}
	}
	else if (caracteristique <= 75 && points >= 1500)
	{
		printf("Veux-Tu d%spenser 4 points d'am%slioration pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points = points - 4 ;
			caracteristique ++ ;
			return caracteristique ;
		}
		else
		{
			return 0 ;
		}
	}
	else if (caracteristique <= 80 && points >= 2000)
	{
		printf("Veux-tu d%spenser 5 points d'am%slioration pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points = points - 5 ;
			caracteristique ++ ;
			return caracteristique ;
		}
		else
		{
			return 0 ;
		}
	}
	else if (caracteristique < 85 && points >= 3000)
	{
		printf("Veux-tu d%spenser 6 d'am%slioration pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points = points - 6 ;
			caracteristique ++ ;
			return caracteristique ;
		}
		else
		{
			printf("Tu n'as pas assez de points pour augmenter cette caract%sristique.\n", é) ;
			return 0 ;
		}
	}
	return 0 ;
}

void enregistrer(int style, int coureur[])
{
	FILE* fichier = NULL ;
	fichier = fopen(nomDeFichier, "w+") ;
	fprintf(fichier, "%d\n", style) ;
	int compteurDeNotes = 0 ;
	while(compteurDeNotes < 14)
	{
		fprintf(fichier, "%d\n", coureur[compteurDeNotes]) ;
		compteurDeNotes ++ ;
	}
}

int determinerNotesMax(int principal, int secondaire, int compteur)
{
	int maximumDetermine ;
	int positionInitiale ;
	fichier = fopen("combinaisons", "r") ;
	positionInitiale = ((principal) * 42 * 7) + (secondaire) * 42 + (compteur * 3) ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	fscanf(fichier, "%d", &maximumDetermine) ;
	fclose(fichier) ;
	return maximumDetermine ;
}
