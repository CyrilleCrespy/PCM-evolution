/* Ceci est un programme développé spécifiquement pour les besoins des carrières collaboratives
 * sur Pro cycling manager. Il permet de créer des fiches de coureurs, et de savoir quelles évolutions
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
	entreeStats(caracteristiques) ;
}

int choixNomDeFichier()
{
	unsigned char choix = 0 ;
	printf("Veuillez choisir un nom de fichier.\n") ;
	scanf("%s", &nomDeFichier) ;
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

int entreeStats(char *caracteristiques[])
{
	int compteurDeNotes = 0 ;
	int note = 0 ;
	while(compteurDeNotes < 14)
	{
		while(note < 50 || note > 85)
		{
			printf("Entrez la note de %s, qui doit %stre entre 50 et 85.\n", caracteristiques[compteurDeNotes], ê) ;
			getc(stdin) ;
			scanf("%d", &note) ;
			printf("Note de %s : %d enregistr%se.\n", caracteristiques[compteurDeNotes], note, é) ;
			if (note < 50 || note > 85)
			{
				printf("Note non valide. veuillez s%slectionner entre 50 et 85 inclus.\n", é) ;
			}
			else
			{
				fichier = fopen(nomDeFichier, "a") ;
				fprintf(fichier, "%d\n", note) ;
				fclose(fichier) ;
			}
		}
		compteurDeNotes ++ ;
		note = 0 ;
	}
	modification() ;
}

int demandeNomDeFichier()
{
	printf("Veuillez choisir un nom de fichier.\n") ;
	scanf("%s", &nomDeFichier) ;
	modification() ;
}

int modification()
{
	fichier = fopen(nomDeFichier, "r") ;
	int choix = 999 ;
	points = 0 ;
	int coureur[14] = {0} ;
	fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d", &coureur[0], &coureur[1], &coureur[2],\
&coureur[3], &coureur[4], &coureur[5], &coureur[6], &coureur[7], &coureur[8], &coureur[9], &coureur[10],\
&coureur[11], &coureur[12], &coureur[13]) ;

	printf("Combien de points de cha%sne as-tu ?\n", î) ;
	scanf("%d", &points) ;

	while (choix != 0)
	{
		printf("1. Plaine : %d.\n2. Montagne : %d.\n3. Moyenne montagne : %d.\n4. Vallon : %d.\n\
5. Contre-la-montre : %d.\n6. Prologue : %d.\n7. Pav%ss : %d.\n8. Sprint : %d\n\
9. Acc%sl%sration : %d.\n10. Descente : %d.\n11. Baroud : %d.\n12. Endurance : %d.\n\
13. R%ssistance : %d.\n14. R%scup%sration : %d.\n15. Sauvegarder les changements.\n", coureur[0], coureur[1], coureur[2], coureur[3],\
coureur[4], coureur[5], é, coureur[6], coureur[7], é, é, coureur[8], coureur[9], coureur[10], coureur[11], é,\
coureur[12], é, é, coureur[13]) ;
		printf("Tu as %d points de cha%sne restants.\n", points, î) ;

		if (points < 500)
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
			enregistrer(coureur) ;
			return 0 ;
		}
		else if (coureur[choix-1] >= 85)
		{
			printf("Cette caract%sristique est d%sj%s au maximum.\n", é, é, à) ;
			continue ;
		}

		coureur[choix-1] = calculAmelioration(coureur[choix-1]) ; //La liste commençant à l'indice 0, on compense.
	}
}

int calculAmelioration(int caracteristique)
{
	int choix = 0 ;	
	printf("Tu as actuellement %d dans cette caract%sristique.\n", caracteristique, é) ;
	if (caracteristique < 60)
	{
		printf("Veux-tu d%spenser 500 points de cha%sne pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points = points - 500 ;
			caracteristique ++ ;
			return caracteristique ;
		}
		else
		{
			return 0 ;
		}
	}
	else if (caracteristique < 65 && points >= 800)
	{
		printf("Veux-tu d%spenser 800 points de cha%sne pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points = points - 800 ;
			caracteristique ++ ;
			return caracteristique ;
		}
		else
		{
			return 0 ;
		}
	}
	else if (caracteristique < 70 && points >= 1000)
	{
		printf("Veux-tu d%spenser 1000 points de cha%sne pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points = points - 1000 ;
			caracteristique ++ ;
			return caracteristique ;
		}
		else
		{
			return 0 ;
		}
	}
	else if (caracteristique < 75 && points >= 1500)
	{
		printf("Veux-Tu d%spenser 1 500 points de cha%sne pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points = points - 1500 ;
			caracteristique ++ ;
			return caracteristique ;
		}
		else
		{
			return 0 ;
		}
	}
	else if (caracteristique < 80 && points >= 2000)
	{
		printf("Veux-tu d%spenser 2 000 points de cha%sne pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points = points - 2000 ;
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
		printf("Veux-tu d%spenser 3 000 points de cha%sne pour un point de plus ?\n", é, î) ;
		printf("1. Oui\n2. Non\n") ;
		scanf("%d", &choix) ;
		if (choix == 1)
		{
			points = points - 3000 ;
			caracteristique ++ ;
			return caracteristique ;
		}
		else
		{
			printf("Tu n'as pas assez de points pour augmenter cette caract%sristique.\n", é) ;
			return 0 ;
		}
	}
}

void enregistrer(int coureur[])
{
	FILE* fichier = NULL ;
	fichier = fopen(nomDeFichier, "w+") ;
	int compteurDeNotes = 0 ;
	while(compteurDeNotes < 14)
	{
		fprintf(fichier, "%d\n", coureur[compteurDeNotes]) ;
		compteurDeNotes ++ ;
	}
}
