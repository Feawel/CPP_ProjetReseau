Ensemble des tests unitaires.

IMPORTANT : SI IL Y A ERREUR D’IMPORTATION DE FICHIER, C’EST QUE LE CHEMIN DOIT ETRE EN RELATIF ET PAS ABSOLU: 
	INCORRECT : model/component/firewall.h
	CORRECT :   ../component.firewall.h (ici je suis sur building.h par exemple) 

Commandes à exécuter pour effectuer les tests :
	1. ../cxxtest-4.3/bin/cxxtestgen --error-printer -o TestXXXXX.cpp TestXXXXXX.h
	2. g++ -I ../cxxtest-4.3/ TestXXXXX.cpp -o TestXXXXX
	3. ./TestXXXXX

Descriptions des tests unitaires :
    
    TestBuilding: tests unitaires sur la classe Building