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

char *abbreviations[14] = {"PLA", "MON", "MMO", "VAL",\
"CLM", "PRO", "PAV", "SPR", "ACC", "DES", "BAR",\
"END", "RES", "REC"} ;
int notesInitiales[14] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50} ;
char paves[10] ;
int points ;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include <gtk/gtk.h>
#include <glib.h>

#include <pthread.h>

#include "PCM_Évolution.h"
#include "GUI.c"
#include "modification.c"
#include "creation.c"
#include "calculAmelioration.c"
#include "sauvegardes.c"

int main(int argc, char *argv[])
{
	peuplerListe("pays") ;
	peuplerListe("courses") ;
	int status ;
	gtk_init() ;
	PCM_Evolution = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS) ;
	
	g_signal_connect (PCM_Evolution, "activate", G_CALLBACK (initialisationFenetre), NULL) ;
	status = g_application_run (G_APPLICATION (PCM_Evolution), argc, argv) ;
	g_object_unref (PCM_Evolution) ;	
	
	return status ;
}

int determinerNotesMax(int style, int compteur)
{
	FILE* fichier = NULL ;
	int maximumDetermine ;
	int positionInitiale ;
	fichier = fopen("combinaisons", "r") ;
	positionInitiale = (style * 42) + (compteur * 3) ;
	fseek(fichier, positionInitiale, SEEK_SET) ;
	fscanf(fichier, "%d", &maximumDetermine) ;
	fclose(fichier) ;
	return maximumDetermine ;
}

void remplirJournal(char *message)
{
	time_t horodatage = time(NULL) ; 
	FILE* fichier = NULL ;
	fichier = fopen("fichier_journal", "a") ;
	ECRIRE_TEMPS ;
	fclose(fichier) ;
}
