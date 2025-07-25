##### [🇫🇷 Version française](README.fr.md) / [🇬🇧 English version](README.md)

# PROJET GET_NEXT_LINE POUR 42
Par chdonnat (Christophe Donnat de 42 Perpignan, France)

## BUT DU PROJET
Ce projet vous permettra non seulement d'ajouter une fonction très pratique à votre collection, mais aussi de vous initier à un nouvel élément surprenant de la programmation en C : les variables statiques.

Des appels successifs à votre fonction `get_next_line()` doivent vous permettre de lire l'intégralité du contenu du fichier texte référencé par le descripteur de fichier, une ligne à la fois.

Le fichier `get_next_line_utils.c` servira à ajouter des fonctions supplémentaires nécessaires à l'implémentation de votre `get_next_line()`.

Votre fonction doit retourner la ligne qui vient d'être lue.
S'il n'y a plus rien à lire ou si une erreur survient, elle doit retourner `NULL`.
Assurez-vous que votre fonction se comporte correctement, qu'elle lise depuis un fichier ou depuis l'entrée standard.
Important :
Vous devez toujours retourner la ligne qui a été lue, suivie du `
` qui la termine, sauf lorsque vous avez atteint la fin du fichier et que le fichier ne se termine pas par un `
`.

Le fichier d'en-tête `get_next_line.h` doit contenir, au minimum, le prototype de la fonction.

## BONUS
Voici les bonus à implémenter :

- Implémenter `get_next_line()` en utilisant une seule variable statique.
- Étendre `get_next_line()` pour gérer plusieurs descripteurs de fichier (fd).
  
Par exemple, si les descripteurs de fichier 3, 4 et 5 sont lisibles, il doit être possible de lire depuis chacun d'eux à tour de rôle 
sans jamais perdre le contenu déjà lu de l'un des fds, et sans retourner la mauvaise ligne.
Vous devriez pouvoir appeler `get_next_line()` une fois avec le fd 3, puis avec le fd 4, puis le fd 5, et ensuite de nouveau avec le fd 3, encore avec le fd 4, et ainsi de suite.

## DOCUMENTATION
### variable `static` en C

En C, une variable `static` est une variable qui conserve sa valeur entre plusieurs appels de fonction.
Lorsqu'une variable est déclarée avec le mot-clé `static` à l'intérieur d'une fonction, sa durée de vie devient toute la durée de l'exécution du programme,
contrairement à une variable locale normale qui est créée et détruite à chaque appel de la fonction.
Cependant, sa portée reste limitée à la fonction dans laquelle elle est définie, ce qui signifie qu'elle ne peut pas être accédée en dehors de cette fonction.
Cela rend les variables `static` particulièrement utiles pour maintenir un état ou stocker des informations qui doivent persister entre les appels de fonction.

Les variables `static` peuvent également être déclarées en dehors des fonctions, au niveau du fichier.
Dans ce cas, leur portée est restreinte au fichier dans lequel elles sont déclarées, empêchant l'accès depuis d'autres fichiers du programme.
Ceci est utile pour l'encapsulation, car cela limite la visibilité des variables au module qui les définit.
Dans l'ensemble, les variables `static` sont une fonctionnalité puissante pour gérer l'état et améliorer la modularité en programmation C.