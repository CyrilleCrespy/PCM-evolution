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

char nomDeFichier[255] ; //Limite imposée par le NTFS, pour plus de compatibilité.
char paves[10] ;
int points ;

int main(int argc, char *argv[])
{
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
		scanf("%hhu", &choix) ;
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
	}
	return -1 ;
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
