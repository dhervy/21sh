# 21sh

Le but est de créer un shell qui exécute des commandes complexes et quelques bultins.

## Compiling

En exécutant `make`, un exécutable nommé `21sh` sera compilé directement.

## Usgae

`~ ./21sh`

```c
$> ls | cat -e // on va executer `ls` puis envoyer la sortit standard vers l'entrée stendard de `cat -e`
$> echo "$PATH" > path.txt // on va écrire cat -e ne recla valeur de PATH dans path.txt
$> env -i ls -G
$> cd ../test
$> cat << EOF | cat -e
>ceci sera envoyer a `cat -e`
>EOF ou CTRL + D
`ceci sera envoyer a `cat -e`$`
$> mkdir
$> chmod 777 ../test/fichier
$> echo Bonjour > test.txt ; echo Aurevoir >> test.txt ; cat -e test.txt
Bonjour$
Aurevoir$
$> ls -l 1>&2 | cat -e // la sortit de `ls` est rediriger vers la sortit d'erreur, le `pipe` lui recupere la sortit stendard qui est vide donc `cat -e` ne recupere aucune entrée
```
## Feature

* pipe `|`
* heredoc `<<`
* Double redirection `>>`
* Redirection `<` et `>`
* Agrégateur  `>&`
* Multi-commandes `;`
* Edition de ligne 
* Autocomplétion

## Bultin

* cd
* echo
* env
* setenv
* unsetenv

## Controle

* Copier `Alt + c` sélectionner avec les flêches directionelles puis pressez `Entrer`
* Couper `Alt + x` sélectionner avec les flêches directionelles puis pressez `Entrer`
* Coller `Alt + v`
* Autocomplétion `Tab`
* Se déplacer de mot en mot `Alt + Fleche Droite,gauche`
* Se déplacer d'une ligne à l'autre `Alt + Fleche Haut,Bas`
* Naviguer dans l'historique `Fleche Haut,Bas`
