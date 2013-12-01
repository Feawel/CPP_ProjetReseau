NetworkBuilder 1.0 Readme file

-- Contents --
- Installation
- Description
- Logique Métier

———————— Installation ————————

Notre programme nécessite l’installation de Graphviz qu’il utilise pour générer des graphes.

	1. Télécharger Graphviz (http://www.graphviz.org/Download..php)
	2. Suivre la procédure d’installation
	3. Ajouter Graphviz au path Windows (C:\Program Files (x86)\Graphviz2.34\bin)

———————— Description ————————

Ce logiciel se déroule en 4 étapes logiques, détaillées ci-dessous.

- Etape 1 -

Création de la requête (objet Request) via l'interface graphique
Une requête contient une liste de bâtiments (objet Building), une liste de lien bâtiments/bâtiments (objet Building_Building).

Chaque bâtiments contient une liste d'étage (objet Floor). Les bâtiments et les étages possèdent une liste de technologies déjà en place (définie dans l'objet parent Location).

- Etape 2 -
La requête passe à travers un certains nombre de phases qui ajoutent des composants (objet Component) aux objets Location comme des switch (objet Switch), des firewalls (objet Firewall)...

Des liens (objet Link) sont crées entre les composants et ajoutés dans une liste à la requête. Les adresses sont définies.

- Etape 3 - 
Les composants et les liens sont transformés en un graphe (langage graphviz)

- Etape 4 -
Un fichier result.txt est généré avec un récapitulait sous forme de tableau du réseau final.

———————— Logique Métier ————————

Déroulement du coeur du programme

Phase I : Création du backbone
	Adresse du backbone : 10.10.0.0/16
	Un switch L2/3 par bâtiment
	Une adresse par bâtiment : pour chaque bâtiment i
		10.10.i.i
	Un bâtiment désigné comme « Bat Admin » 

Phase II : Technologies de liaison inter-batiments
	Définition des distances B2B
	Choix des liens (on privilégie les technos pré-existantes, puis les plus courtes distances)
	Choix des technologies pour ces liens
		Fibre optique (défaut)
		Paire torsadée (SI paire torsadée déjà câblée entre bâtiments)
		InfraRouge (D(B2B) < 1,5 && vision == true)
		Pont Wifi (D(B2B) < 0,5 && vision == true)


Phase III : Sous réseaux intra-bâtiment
	Pour chaque étage i, bâtiment j
		Mise en place d’un L2
		Adresse du switch : 10.j.i.199
		Adresse de broadcast : 10.j.i.255
		Adresse privée du réseau : 10.j.i.0/24
	Pour le bâtiment admin
		Ajout d’une section admin (avec firewall et règles adaptées)
		Ajout d’une section privée (avec firewall et règles adaptées)