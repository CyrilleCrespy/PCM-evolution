This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Ceci est un programme développé spécifiquement pour les besoins des carrières collaboratives
sur Pro cycling manager. Il permet de créer des fiches de coureur, et de savoir quelles évolutions
sont possibles en fonction du nombre de points de chaînes disponibles pour l'utilisateur.
Copyright (C) 2024  Cyrille Crespy

Le programme nécessite la présence des fichiers combinaisons, courses et pays, qui doivent être fournis dans l'archive où se trouve ce fichier texte.
La compilation nécessite de passer #define Windows pour obtenir un exécutable pour ce système d'exploitation, par exemple en passant l'argument -D Windows à gcc.

Code source disponible en ligne : https://github.com/CyrilleCrespy/PCM-evolution

Version 0.1 : commit f1217b416f9ed8f54390c465aca112df2a04c40e
=> création et modification d'une fiche de coureur
=> instructions de préprocesseurs pour prendre en compte l'interopérabilité

Version 0.2 : commit f1a39166052462b8c159cac85f5cf8e830ce8ac8
=> refonte du système de création, établissement de styles de coureurs liés à des notes maximales
=> passage d'une comptabilité en points de chaîne à une comptabilité en points d'évolution

Version 0.3 :
=> prise en charge du potentiel
=> fichier sauvegarde plus lisible

Projets à venir :
=> gestion des erreurs (typiquement des entrées qui ne sont pas des int) (0.4)
=> sauvegarde automatique de secours restaurables, en cas d'interruption du programme inopiné qui ferait péter la fiche (0.5)
=> interface graphique (1.0)
