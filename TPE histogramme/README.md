# Histogramme - Projet de Quantification d'Images

## Auteurs
**PICARD Marius** et **RAMDANI Rayan**

## Description du projet
Ce projet implémente un système d'analyse et de quantification d'images au format PPM. L'objectif principal est d'optimiser l'utilisation de la mémoire en réduisant le nombre de couleurs d'une image tout en préservant au maximum sa qualité visuelle. Le programme utilise une structure de données hybride (tableau 2D + listes chaînées) pour stocker efficacement l'histogramme des couleurs, évitant ainsi d'allouer de la mémoire pour toutes les combinaisons RGB possibles (16 millions). La quantification permet de ne conserver que les K couleurs les plus populaires.

## Exécution
```bash
make              # Compiler
./bin/histogramme.bin   # Lancer le programme
```

## Menu interactif
Le programme propose 3 options principales :
1. **Afficher l'histogramme** : Analyse complète des couleurs RGB et leurs fréquences
2. **Quantification mapping1** : Réduction de couleurs avec distance Manhattan (RGB)
3. **Quantification mapping2** : Réduction de couleurs avec distance CIELAB (perception humaine)

L'utilisateur entre le nom de l'image (depuis `ressources/IMAGES/`), le nombre de couleurs K souhaité, et le nom du fichier de sortie.

## Contenu des fichiers

**histogramme.c** : Implémente la structure d'histogramme optimisée en mémoire (tableau 2D de listes chaînées), les fonctions de création, insertion, parcours et suppression, ainsi qu'un itérateur pour parcourir toutes les couleurs présentes dans l'image.

**quantification.c** : Contient les algorithmes de quantification par popularité avec grouping spécial (R/2, G, B/4), les deux fonctions de mapping (distance Manhattan RGB et distance CIELAB), ainsi que les conversions RGB vers CIELAB pour une meilleure perception des couleurs.
