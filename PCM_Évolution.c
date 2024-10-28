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
	int choix = 5 ;
	char *caracteristiques[14] = {"Plaine", "Montagne", "Moyenne montagne", "Vallon",\
"Contre-la-montre", "Prologue", paves, "Sprint", acceleration, "Descente", "Baroud",\
"Endurance", resistance, recuperation} ;

	while (choix != 0) //Répétion du menu tant que l'utilisateur n'a pas demandé à quitter.
	{
		printf("Bienvenue dans PCM %svolution.\n", É) ; //Variable définie selon l'OS pour les accents.
		printf("Menu.\n") ;
		printf("1. Cr%sation de fiche coureur.\n", é) ;
		printf("2. Modification de fiche coureur.\n") ;
		printf("Quitter avec 0.\n") ;
		choix = verificationEntreeNumerique(0, 2) ;
		suppressionEspace() ;
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
			printf("Merci d'avoir utilis%s PCM %svolution !\n", é, É) ;
			exit(EXIT_SUCCESS) ;
		}
	}
	return -1 ;
}

int determinerNotesMax(int style, int compteur)
{
	int maximumDetermine ;
	int positionInitiale ;
	fichier = fopen("combinaisons", "r") ;
	positionInitiale = (style * 42) + (compteur * 3) ;
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
	positionInitiale = 0 + (compteur * DECALAGE) ;
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

void suppressionEspace()
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
	long unsigned int compteur ; //Long unsigned int pour la comparaison avec strlen.
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

int verificationEntreeNumerique(int min, int max)
{
	int donneeVerifiee = 65536 ;
	while (donneeVerifiee < min || donneeVerifiee > max)
	{
		if ((scanf("%d", &donneeVerifiee) == 1) && (donneeVerifiee >= min && donneeVerifiee <= max))
		{
			return donneeVerifiee ;
		}
		else
		{
			printf("Entr%se incorrecte. Merci de ne taper qu'un chiffre, sans lettre ou ponctuation, entre %d et %d.\n", é, min, max) ;
			viderBuffer() ; //Permet d'éviter que la boucle ne se relance sans tenir compte du scanf.
		}
	}
	printf("Erreur dans PCM_%svolution.c, int verificationEntreeNumerique.\n", É) ;
	printf("Valeur connue : %d, valeur min : %d, valeur max : %d.\n", donneeVerifiee, min, max) ;
	exit(EXIT_FAILURE) ;
}

int confirmationEntree()
{
	int confirmation ;
	printf("0. Annuler \n") ;
	printf("1. Confirmer \n") ;
	confirmation = verificationEntreeNumerique(0, 1) ;
	return confirmation ;
}
