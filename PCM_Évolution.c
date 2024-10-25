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
#include "modification.c"
#include "creation.c"
#include "calculAmelioration.c"

char nomDeFichier[250] ;
char paves[10] ;
int points ;

int main(void)
{
	system(clear) ;
	char paves[10] ;
	sprintf(paves, "Pav%ss", é) ;
	char acceleration[20] ;
	sprintf(acceleration, "Acc%sl%sration", é, é) ;
	char resistance[15] ;
	sprintf(resistance, "R%ssistance", é) ;
	char recuperation[20] ;
	sprintf(recuperation, "R%scup%sration", é, é) ;
	unsigned char choix = 5 ;
	char *caracteristiques[14] = {"Plaine", "Montagne", "Moyenne montagne", "Vallon",\
"Contre-la-montre", "Prologue", paves, "Sprint", acceleration, "Descente", "Baroud",\
"Endurance", resistance, recuperation} ;

	while(choix != 0) //Répétion du menu tant que l'utilisateur n'a pas demandé à quitter.
	{
		printf("Bienvenue dans PCM %svolution.\n", É) ; //Variable définie selon l'OS pour les accents.
		printf("Menu.\n") ;
		printf("1. Cr%sation de fiche coureur.\n", é) ;
		printf("2. Modification de fiche coureur.\n") ;
		printf("Quitter avec 0.\n") ;
		if (scanf("%hhu", &choix) == 1)
		{
			supressionEspace() ;
			if (choix == 1)
			{
				creation(caracteristiques) ;
				return 0 ;
			}
			else if (choix == 2)
			{
				demandeNomDeFichier(caracteristiques) ;
				return 0 ;
			}
			else
			{
				printf("Merci de taper 1 ou 2.\n") ;
			}
		}
		else
		{
			printf("Entr%se incorrecte. Merci de ne taper qu'un chiffre : 1 ou 2.\n", é) ;
			viderBuffer() ; //Permet d'éviter que la boucle ne se relance pas avec l'affichage du menu en boucle.
		}
	}
	return -1 ;
}

int determinerNotesMax(int principal, int secondaire, int compteur)
{
	int maximumDetermine ;
	int positionInitiale ;
	fichier = fopen("combinaisons", "r") ;
	positionInitiale = ((principal * 7) + (secondaire * 42) + (compteur * 3)) ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	fscanf(fichier, "%d", &maximumDetermine) ;
	fclose(fichier) ;
	return maximumDetermine ;
}

int retrouverNotesMax(int compteur)
{
	char fichierMax[255] ;
	sprintf(fichierMax, "%s_max", nomDeFichier) ;
	int maximumDetermine ;
	int positionInitiale ;
	
	fichier = fopen(fichierMax, "r") ;
	
	if(fichier == NULL)
	{
		printf("Erreur, impossible de lire %s. Dans PCM_%svolution.c, int retrouverNotesMax.\n", fichierMax, É) ;
	}
	positionInitiale = 0 + (compteur * 3) ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	fscanf(fichier, "%d", &maximumDetermine) ;
	fclose(fichier) ;
	return maximumDetermine ;
}

void viderBuffer()
{
	int vider = 0 ;
	while (vider != '\n' && vider != EOF)
	{
		vider = getchar() ;
	}
}

void supressionEspace()
{
	while (nomDeFichier[strlen(nomDeFichier)] == 32 || nomDeFichier[strlen(nomDeFichier)] == 92)
	{
		if (nomDeFichier[strlen(nomDeFichier)] == 32 || nomDeFichier[strlen(nomDeFichier)] == 92)
		{
			nomDeFichier[strlen(nomDeFichier) - 1] = '\0' ;
			printf("%s\n", nomDeFichier) ;
			getchar() ;
		}
	}
}

void corrigerNomDeFichier()
{
	int compteur ;
	int espaces = 0 ;
	char nomProvisoire[250] = {0} ;
	for (compteur = 0 ; compteur < strlen(nomDeFichier + espaces) ; compteur ++)
	{
		if (nomDeFichier[compteur] == 36 || nomDeFichier[compteur] == 39 || nomDeFichier[compteur] == 10)
		{
			nomProvisoire[compteur + espaces] = '\0' ;
		}
		else
		{
			nomProvisoire[compteur + espaces] = nomDeFichier[compteur] ;
		}
	}
	memcpy(nomDeFichier, nomProvisoire, 250) ;
}
