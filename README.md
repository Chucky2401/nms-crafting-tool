# NMS Crafting Tool	

## Description
Outil permettant de lister les composants d'une recette du jeux No Man's Sky
**/!\ OUTILS TOUJOURS EN DEVELOPPEMENT - PAS DE SORTIE POUR LE MOMENT /!\\**

## Fonctionnement
A partir d'une recette, liste tous les composants nécessaires. Si les composants sont eux aussi une recette, les composants sont aussi listés, et ainsi de suite, de manière récursif. Tout ceci est affiché dans une liste de type arbre (Treeview).
Finalement, toutes les ressources de base (Carbone, Solanium, etc.) sont listés pour obtenir le total pour la recette principale.
Il est aussi possible d'afficher le nombre de plant qu'il sera nécessaire ainsi que le nombre de dome associé.

![v0.1.4.2](https://i.imgur.com/LPkTEdz.jpg)

## Langages
NMSCT<sup>[1](#nmsct)</sup> est développer en C++ avec le framework [Qt 5.1.3][Qt] (j'essaie de maintenir Qt à jour).
Pour la base de données j'utilise SQLite v3. A terme, pour que le logiciel soit le plus "communautaire" possible, je basculerais sur une base de données serveur (MariaDB - PostgreSQL étant surdimensionné pour la quantité de données aujourd'hui).
Je ne suis pas partis sur cette solution tout de suite car je suis en pleins développement. De plus, héberger une base de données soit même aujourd'hui et beaucoup trop risqué [Ranswonware Serveur MySQL][ransonwareBDD]. De plus, cela coûtant de l'argent (serveur, nom de domaine et certificat SSL), je ne peux pas me permettre aujourd'hui de payer cela.

![QtIDE](https://i.imgur.com/xNaFNefm.jpg)

![SQLite](https://i.imgur.com/KcBvoNUm.jpg)

## A venir
Voici une liste des choses que j'aimerais implémenter (incomplet) :
- [ ] Utilisation d'une base de données serveur
- [ ] Permettre l'ajout de recettes
- [ ] Gestion des recettes (modification, suppression)
- [ ] Gestion des ressources (modification, suppression)
- [ ] Gestion des données de farming
- [ ] Création d'un installeur
  Aujourd'hui je ne sais pas faire (sip...), mais je suis autodidacte, si quelqu'un s'y connaît bien, je suis preneur d'une bonne documentation/tuto :smile:
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
Ici gros ajout au niveau du code pour une petite modification<sup>[2](#imageQt)</sup>.
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
* Ajout d'une case à cocher 'Farming ?' qui permet d'afficher les données pour l'agriculture. Soit : le nombre de Plant et le nombre de Dome pour la quantité de Plant
* Ajout d'une seconde case à cocher 'Etendre tout automatiquement ?' qui permet lors de l'affichage des ressources, d'étendre toute la vue automatiquement. De cette manière vous n'êtes pas obligé de cliquer sur chaque ligne ou le bouton 'Etendre Tout'.
* Utilisation d'un fichier .ini :
  - Groupe BDD
    + Chemin vers la base de données
    + Nom de la base de données
  - Groupe Image
    + Chemin vers les images
  - Groupe Utilisateur
    + Mémoriser l'état du bouton 'Farming ?'
    + Mémoriser l'état du bouton 'Etendre tout automatiquement ?'

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
        + Etendre automatique - *Lié à la case à cocher dans la fenêtre*
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

## Divers
**16/06/2019** - [Premier post sur le groupe][premierPost]
**06/08/2019** - Création d'une page [Facebook][nmsctFacebook]
**07/08/2019** - Hébergement web gratuit réservé [NMSCT][epizy.com]

## References
[Qt]: https://www.qt.io/
[ransonwareBDD]: https://www.silicon.fr/grandcrab-242223.html
[nmsfr]: https://www.facebook.com/groups/215415605504595
[premierPost]: https://www.facebook.com/groups/215415605504595/permalink/831562540556562/
[nmsctFacebook]: https://www.facebook.com/NMS-Crafting-Tool-107068020644537
[epizy.com]: http://nmsct.epizy.com

## Notes
<a name="nmsct">1</a>: NMSCT pour NMS Crafting Tool

<a name="imageQt">2</a>: Je ne pensais pas qu'ajouter une image avec Qt, surtout avec le besoin de la redimensionner serait aussi complexe...
