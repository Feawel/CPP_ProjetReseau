CPP_ProjetReseau
================

Déroulement du coeur du programme

Phase 0 : Définition des usages
        Nombre de bâtiments
        Nombre d’étages (en réalité division des bâtiments : 4 étages de 5 salles pour lesquelles on veut un réseau unique donne 20 et non 4)
        Utilisateurs
                Nombre d’utilisateurs pour chaque batiment/étage (accès à déterminer pour règles FW)
                Nombre d’accès privilège (accès internet + serveurs publics/privés)
                Nombre d’accès admin (accès internet + serveurs publics/privés + admin)
        Création des règles du FW

Phase I : Création du backbone
        Adresse du backbone : 10.10.0.0/16
        Un switch L2/3 par bâtiment
        Une adresse par bâtiment : pour chaque bâtiment i
                10.10.i.i
        Un bâtiment désigné comme « Bat Admin » (Bat admin à TRUE ?)

Phase II : Technologies de liaison inter-batiments
        Définition des distances B2B
        Fibre optique (défaut)
        Paire torsadée (SI paire torsadée déjà câblée entre bâtiments)
        InfraRouge (D(B2B) < 3 && vision == true)
        Pont Wifi (D(B2B) < 0,5 && vision == true)


Phase III : Sous réseaux intra-bâtiment
        Pour chaque étage i, bâtiment j
                Mise en place d’un L2
                Adresse du switch : 10.j.i.199
                Adresse de broadcast : 10.j.i.255
                Adresses disponibles pour DHCP : 10.j.i.200 - 10.j.i.254
                Adresse privée du réseau : 10.j.i.0/24
        Pour chaque bâtiment 
                Indiquer DHCP Relay : 10.j(admin).i(admin serveurs privés).10(arbitraire)
                Indiquer Default Route : next hop : adresse privée router (coté intérieur du FW)


Phase IV : Ajouts pour permettre une génération facile du graphe
        Définition du « next_hop »
