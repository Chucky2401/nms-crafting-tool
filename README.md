# NMS Crafting Tool	



[TOC]



## Description
Outil permettant de lister les composants d'une recette du jeux No Man's Sky

**/!\ OUTILS TOUJOURS EN DEVELOPPEMENT /!\\**

## Fonctionnement
A partir d'une recette, liste tous les composants nécessaires. Si les composants sont eux aussi une recette, les composants sont aussi listés, et ainsi de suite, de manière récursif. Tout ceci est affiché dans une liste de type arbre (Treeview).
Finalement, toutes les ressources de base (Carbone, Solanium, etc.) sont listés pour obtenir le total pour la recette principale.
Il est aussi possible d'afficher le nombre de plant qu'il sera nécessaire ainsi que le nombre de dôme associé.

![v0.1.4.7-01](https://i.imgur.com/pZL94RK.jpg)

![v0.1.4.7-02](https://i.imgur.com/kc23UgU.jpg)

![v0.1.4.7-03](https://i.imgur.com/NK1CPs9.jpg)

![v0.1.5.2a](https://i.imgur.com/hBCFltx.jpg)

![v0.1.5.3a](https://i.imgur.com/RIB7LZB.jpg)

## Langages
NMSCT<sup>[1](#nmsct)</sup> est développer en C++ avec le Framework [Qt 5.1.3][Qt] (j'essaie de maintenir Qt à jour).
Pour la base de données j'utilise SQLite v3. A terme, pour que le logiciel soit le plus "communautaire" possible, je basculerais sur une base de données serveur (Maria DB - PostgreSQL étant surdimensionné pour la quantité de données aujourd'hui).
Je ne suis pas partis sur cette solution tout de suite car je suis en pleins développement. De plus, héberger une base de données soit même aujourd'hui et beaucoup trop risqué [Ransomware Serveur MySQL][ransomwareBDD]. De plus, cela coûtant de l'argent (serveur, nom de domaine et certificat SSL), je ne peux pas me permettre aujourd'hui de payer cela.

![QtIDE](https://i.imgur.com/xNaFNefm.jpg)

![SQLite](https://i.imgur.com/KcBvoNUm.jpg)

## A venir
Voici une liste des choses que j'aimerais implémenter (incomplet) :
- [ ] ~~Utilisation d'une base de données serveur~~
- [x] Permettre l'ajout de recettes
- [ ] Gestion des recettes (modification, suppression)
- [ ] Gestion des ressources (modification, suppression)
- [ ] Export / Import des recettes
- [x] Gestion des données de farming
- [x] Création d'un installeur <sup>[2](#QtIF)</sup>
  ~~Aujourd'hui je ne sais pas faire (sip...), mais je suis autodidacte, si quelqu'un s'y connaît bien, je suis preneur d'une bonne documentation/tuto :smile:~~
- [x] Mise en place des mises à jour
- [x] Modification de l'interface
  *Masquage bouton, etc.*
- [ ] ...

## Suivis des modifications

### **v0.1.0** - *16/06/2019*
Première version, premier code !
Cette version est la toute première.
Pas de long discours, juste une image.

![v0.1.0](https://i.imgur.com/qQvWFiU.jpg)

### **v0.1.1** - *16/06/2019*
Dans cette version, juste un petit changement suite aux premières remarques sur le groupe [No Man's Sky FR][nmsfr].
La combo box qui liste les recettes a été modifié pour pouvoir saisir au clavier la recette à afficher.

![v0.1.1](https://i.imgur.com/70CpomY.jpg)

### **v0.1.2** - *16/06/2019*
Ici gros ajout au niveau du code pour une petite modification<sup>[3](#imageQt)</sup>.
J'ai ajouté toutes les images, dans :
* La liste des recettes
* A gauche de la description
* La liste des composants
En bref, voici ce que ça donne :

![v0.1.2](https://i.imgur.com/x1jGSfd.jpg)

### **v0.1.3** - *07/08/2019*
Après presque deux mois d'absence, de nouvelles modifications !
La liste n'est pas bien longue, mais voici la liste :
* Ajout d'un menu
  - Seulement un bouton Fichier qui contient Quitter (avec le raccourci Ctrl + Q)
* Ajout d'une case à cocher 'Farming ?' qui permet d'afficher les données pour l'agriculture. Soit : le nombre de Plant et le nombre de Dôme pour la quantité de Plant
* Ajout d'une seconde case à cocher 'Étendre tout automatiquement ?' qui permet lors de l'affichage des ressources, d'étendre toute la vue automatiquement. De cette manière vous n'êtes pas obligé de cliquer sur chaque ligne ou le bouton 'Étendre Tout'.
* Utilisation d'un fichier .ini :
  - Groupe BDD
    + Chemin vers la base de données
    + Nom de la base de données
  - Groupe Image
    + Chemin vers les images
  - Groupe Utilisateur
    + Mémoriser l'état du bouton 'Farming ?'
    + Mémoriser l'état du bouton 'Étendre tout automatiquement ?'

![v0.1.3](https://i.imgur.com/E6wt7TM.jpg)

### **v0.1.4.1** - *08/08/2019*
Au départ, j'étais partie pour implémenter entièrement la fenêtre pour ajouter une recette...
Au départ... Mais je suis comme un petit oiseau qui vole. Je suis dans mes pensées, et je code comme ça vient !
Donc, voici les modification :

* Création d'une classe pour les paramètres
    - set / get / getIni ImagePath()
    - set / get / getIni BddPath()
    - set / get / getIni BddName()
    - set / get / getIni Farming()
    - set / get / getIni AutoExpand()
* Modification du menu principale (sous la barre de titre)
    - Fichier -> Quitter avec une icone
    - Edition
        + Ajouter Recette - *Ouvre une fenêtre vide pour le moment*
    - Outil
        + Préférences - *Ne fait rien pour le moment. A terme ouvrira une fenêtre de préférence*
        + Farming - *Lié à la case à cocher dans la fenêtre*
        + Étendre automatique - *Lié à la case à cocher dans la fenêtre*
* Surcharge de la method closeEvent pour :
	1. Fermer toutes les fenêtre modal ouverte
	2. Demander confirmation avant fermeture
* **BUG**
    - Reproduire le bug : *Lister une recette, étendre des objets dans la liste, changer la quantité et actualiser. Changer de recette et lister les ingrédients. Switcher le bouton Farming et actualiser.*
    - Correction : *Lors du clique sur le bouton Actualiser, ne prendre que les objets qui ont un enfant*
* Ajout de commentaires dans le code

![v0.1.4.1](https://i.imgur.com/oRX4pLf.jpg)

### **v0.1.4.2** - *10/08/2019*
Bon, on avance sur la fenêtre d'ajout !
J'ai mis tous les éléments, dans des onglets. Cela me parait plus claire dans deux onglets distincts. A vous de trancher !
Voici le détails
* Fenêtre '*Ajouter une recette*'
	- Bouton Annuler
	- Rechercher une icône
        * Si cette dernière n'est pas dans le répertoire du programme, elle est copié. *C'est cette dernière qui sera utilisé*
	- Pour le titre et le sous-titre, mis en place du compteur de caractère.
	- Pour la quantité obtenue, valeur autorisé entre 1 et 5
	- Pour les quantités nécessaire valeur autorisé entre 1 et 999
* Fenêtre principale
	- Ajouter d'une option '*Restaurer dernière recette ?*'
		*Cette dernière vous permet de mémoriser la dernière recette visualisé avec la quantité lors de l'ouverture du programme.*
* Modification diverse
	- Utilisation d'une classe personnalisé pour l'accès à la base de données
	- Ajout des infos nécessaires à la classe *settings* pour la mémorisation de la recette
	- Fermeture de la connexion à la base de données lors de fermeture de fenêtre

![v0.1.4.2](https://i.imgur.com/LPkTEdz.jpg)

### **v0.1.4.3** - *11/09/2019*
Cette version là est pour l'ajout d'une recette.
Fenêtre finaliser et correction de divers bug.
* Fenêtre '*Ajouter une recette*'
	- Remplissage des lists en fonction du type de composant
	- Insertion dans la base de recettes
* Fenêtre principale
	- Bug de quantité sur les ressources
	- Bug du calcul de quantité nécessaire
	- Possibilité de mémorisé la position de la fenêtre
	- Ajout des données de farm si existante
	- Bug de quantité doubler si deux recettes avec le même nom
* Divers
	- Lisibilité du code

### **v0.1.4.4** - *11/09/2019*
Version pour quelque corrections, rien d'exceptionnel
* Fenêtre principale
	- Après l'ajout d'une recette, la liste est mise à jour
* Fenêtre d'ajout de recette
	- Peaufinage
* Divers
	- Utilisation des transactions SQL

### **v0.1.4.7a** - *20/10/2019*
Première version en pre-release !
Correction d'un bug, ajout de fonction pour le développement de mon côté.
* Fenêtre principale
	- Correction MessageBox qui apparait pour signaler qu'aucune données de farm n'a été trouvé même si l'option n'est pas activé

![v0.1.4.7a](https://i.imgur.com/pZL94RK.jpg)

### **v0.1.5.1a** - *29/10/2019*
Version qui modifie un peu le fonctionnement du logiciel.
Après divers tests avec le Qt Installer Framework, pour l'installation du programme et la possibilité de mettre à jour, j'ai déplacé la base de données.
Cela pour une raison simple, lors de l'installation de la mise à jour, elle était écrasé...
Enfin, au premier lancement du programme, si la base n'existe pas elle est créée avec des données de bases (celle avec lesquelles que je travail pour mes tests).
* Classe database
	- Initialise la base de données si inexistante.
* Classe settings
	- Modification des chemins de la base

### **v0.1.5.2a** - *01/11/2019*
Comme j'ai utilisé Qt Installer Framework pour déployer l'application, j'ai fait des tests pour les mises à jour.
Pour cela, il faut utiliser un dépôts sur un serveur. Or, la seule solution native pour vérifier les mises à jour est de lancer l'exécutable prévu à cette effet.
J'ai donc intégrer la possibilité de vérifier les mises à jour dans l'applications.
J'ai aussi ajouté un menu pour afficher le A Propos, inutile mais je voulais l'ajouter :).

* Fenêtre principale
	- [Ajout] Menu 'A Propos'
	- [Ajout] Menu 'Vérifier mise à jour'
	- [Bug] Correction si modification de la quantité mais qu'aucune recette n'est sélectionné.
* Classe settings
	- [Amélioration] Suppression du nom de la base de données suite à la modification des paramètres en ligne de commande.
* Fenêtre A Propos
	- [Ajout] Création

![v0.1.5.2a](https://i.imgur.com/hBCFltx.jpg)

### **v0.1.5.3a** - *03/11/2019*
Aller, ajout d'une nouvelle fenêtre !
Il le fallait bien, avec la mise à jour possible avec la nouvelle version, il fallait bien quelque part où le configurer. J'ai donc ajouter la fenêtre des préférences !
Voici la liste des modifications
* Fenêtre principale
	- [Suppression] Option pour restaurer la dernière recette à l'ouverture
	- [Suppression] Option pour restaurer la taille et la position
	- [Amélioration] Icone pour les options "A Propos" et "Vérifier les mises à jour"
	- [Ajout] Vérification des mises à jour en fonction des préférences *(par défaut : désactiver)*
	- [Amélioration] Modification du message si une mise à jour est disponible *(information -> question)*
	- [Amélioration] Passage du statut test (vrai ou faux) à la fenêtre Ajouter Recette
	- [Ajout] Ouverture de la fenêtre
	- [Ajout] Slots pour l'affichage des cases à cocher "Farming ?" et "Étendre tout automatiquement ?"
* Fenêtre A Propos
	- [Amélioration] Ajout d'une barre de titre avec un titre correcte
* Fenêtre Préférences
	- [Ajout] Création
	- [Ajout] Case pour vérifier les mises à jour automatiquement *(par défaut : désactiver)*
	- [Ajout] Nombre de jours entre chaque vérification *(par défaut : 7)*
	- [Ajout] Option pour restaurer la taille et la position de la fenêtre *(par défaut : désactiver)*
	- [Ajout] Option pour restaurer la dernière recette *(par défaut : désactiver)*
	- [Ajout] Possibilité d'afficher ou masquer le bouton 'Farming ?' *(par défaut : afficher)*
	- [Ajout] Possibilité d'afficher ou masquer le bouton 'Étendre tout automatiquement ?' *(par défaut : afficher)*
* Classe settings
	- [Ajout] Gestion de l'option farming
	- [Ajout] Gestion de l'option étendre tout automatiquement
	- [Ajout] Vérification des mises à jour auto
	- [Ajout] Nombre de jour entre chaque mise à jour
	- [Ajout] Sauvegarde de la date de prochaine vérification des mises à jour automatique
	- [Amélioration] Nettoyage du code superflus.

![v0.1.5.3a](https://i.imgur.com/RIB7LZB.jpg)

### **v0.1.5.4a** - *07/11/2019*
Pour cette version correction de gros bug et d'oublie...
Amélioration du code et ajout d'une petite fonctionnalité au passage.

Comme quoi les tests, ça sert !

* Main
	- [Correction] Initialisation variable pour mode test à *false*
* Fenêtre Principale
	- [Correction] Constructeur pour initialiser variable pour mode test
	- [Amélioration] Utilisation de la classe Settings en pointeur
	- [Amélioration] Modification appel aux méthode de la classe Settings pour s'adapter au passage en pointeur.
	- [Amélioration] Suppression du pointeur dans le destructeur pour éviter les fuites mémoires.
	- [Correction] Vérification des mises à jour disponible après initialisation complète du constructeur
	- [Ajout] Prise en compte du paramètre pour le message de confirmation de fermeture.
	- [Amélioration] Passage de la classe Settings en paramètre à la fenêtre des Préférences
* Fenêtre Préférences
	- [Correction] Constructeur pour initialiser variable pour mode test
	- [Amélioration] Utilisation de la classe Settings en pointeur
	- [Amélioration] Modification appel aux méthode de la classe Settings pour s'adapter au passage en pointeur.
	- [Amélioration] Suppression du pointeur dans le destructeur pour éviter les fuites mémoires.
	- [Ajout] Prise en compte du paramètre pour le message de confirmation de fermeture.
* Classe Settings
	- [Amélioration] Classe renommer de 'settings' à 'Settings' pour charte et faciliter
	- [Amélioration] Suppression du paramètre pour la date de prochaine mise à jour par la date de dernière mise à jour.
	- [Ajout] Gestion du paramètre pour afficher ou non le message de confirmation de fermeture.
* Classe Database
	- [Amélioration] Modification nom classe Settings pour prendre la modification de nom
	- [Correction] Ajout d'un contrôle sur l'existence du dossier 'bdd' qui faisait planter au premier démarrage ou générer une erreur qui empêcher l'utilisation.
* Fenêtre Ajouter Recette
	- [Correction] Constructeur pour initialiser variable pour mode test

### **v0.1.5.5a** - *10/11/2019*
Version pour peaufinage et livraison !


## Divers
**16/06/2019** - [Premier post sur le groupe][premierPost]
**06/08/2019** - Création d'une page [Facebook][nmsctFacebook]
**07/08/2019** - Hébergement web gratuit réservé [NMSCT][epizy.com]
**22/10/2019** - Ouverture du GitHub en "public" et livraison pre-release [GitHub][github]
**31/10/2019** - Changement d'hébergeur pour le site. Qui permet l'utilisation du repository [PlanetHoster][planethoster]

## References
[Qt]: https://www.qt.io/
[ransomwareBDD]: https://www.silicon.fr/grandcrab-242223.html
[nmsfr]: https://www.facebook.com/groups/215415605504595
[premierPost]: https://www.facebook.com/groups/215415605504595/permalink/831562540556562/
[nmsctFacebook]: https://www.facebook.com/NMS-Crafting-Tool-107068020644537
[epizy.com]: http://nmsct.epizy.com
[github]: https://github.com/Chucky2401/nms-crafting-tool/releases/tag/v0.1.4.7a
[planethoster]:http://nmsct.blackwizard.yj.fr/

## Notes
<a name="nmsct">1</a>: NMSCT pour NMS Crafting Tool

<a name="QtIF">2</a>: Finalement, en prenant le temps de lire la documentation et de faire des tests, ce n'est pas si compliqué !

<a name="imageQt">3</a>: Je ne pensais pas qu'ajouter une image avec Qt, surtout avec le besoin de la redimensionner serait aussi complexe...
