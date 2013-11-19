//
//  phase0.cpp
//  NetworkBuilder
//
//  Created by Jonathan Banon on 19/11/2013.
//  Copyright (c) 2013 Jonathan Banon. All rights reserved.
//

/*
 Ces constantes sont définies explicitement mais devrontt être fixées par un choix de l'utilisateur fait en amont. 
 Je sais plus exactement qui se charge de recevoir les données utilisateurs mais faudra qu'on se mette d'accord pour l'interfaçage.
 */

#include "phase0.h"

//Nombre de batiments dans le réseau
const int NB_BUILDINGS = 5;

//Tableau contenant les distances entre batiments
float tabDistanceB2B[NB_BUILDINGS][NB_BUILDINGS];

//tableau contenant les visibilités entre batiment
bool tabVisibilityB2B[NB_BUILDINGS][NB_BUILDINGS];

//Nombre de sections à considérer par batiment
const int NB_FLOORS = 3;

//Nombre d'utilisateurs avec un accès "standard" (internet + serveurs publics)
const int NB_USERS = 300;

//Nombre d'utilisateurs avec un accès "supérieur" (internet + serveurs publics/privés)
const int NB_USERS_SUP = 30;

//Nombre d'utilisateurs avec un accès "admin" (internet + serveurs publics/privés + serveurs admins)
const int NB_USERS_ADMIN = 3;

