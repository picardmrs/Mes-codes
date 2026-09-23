# Consignes – Grand Prix F1 (ENSICAEN S6, 2025-2026)
> Document de référence : `instruction_2026.pdf`, version 1.4 (31 mars 2026)

---

## 2. Langage & environnement

- Pilote obligatoirement écrit en **C**.
- Compilable sous **Linux Ubuntu 22.04** sans warning.
- Architecture de référence : machines de salle de TP du bâtiment E (cybele).
- Flags obligatoires dans le Makefile : `-ansi -pedantic -Wall -Wextra`
- **Aucun exécutable** dans l'archive rendue.
- Un code qui ne compile pas → pilote déclaré forfait + pénalité sur la note.

---

## 3. Mécanique de jeu

### 3.1 La carte

- Grille rectangulaire discrète de dimensions `(dx, dy)`.
- 4 types de cases :

| Symbole | Nom | Description |
|---------|-----|-------------|
| `#` | Piste | Zone normale, comportement optimal |
| `~` | Sable | Ralentit fortement (vitesse max = 1) |
| `.` | Hors-piste | Inaccessible |
| `=` | Arrivée | Objectif à atteindre |

- 3 cases numérotées `1`, `2`, `3` : points de départ des 3 pilotes.
- Format de la première ligne de la carte : `dx dy carburant_initial`

### 3.2 Protocole de communication avec le GDC (stdin/stdout)

1. À l'initialisation, le GDC envoie la carte ligne par ligne (première ligne : `width height gas`).
2. À chaque tour, le GDC envoie les positions des 3 pilotes :
   ```
   myX myY\tadversaire1X adversaire1Y\tadversaire2X adversaire2Y\n
   ```
3. Le pilote répond avec son vecteur accélération :
   ```
   dvx dvy\n
   ```
4. **Délai maximum : 1 seconde** pour répondre. Sans réponse dans le délai, le pilote passe son tour (vitesse conservée, voiture immobile).
5. L'ordre de passage est aléatoire mais équitable (change à chaque tour).

> ⚠️ Le `fflush(stdout)` après chaque écriture est **obligatoire**.

### 3.3 Physique du mouvement

- Chaque pilote a une position `(x, y)` et un vecteur vitesse `(vx, vy)`, initialement nuls.
- Le pilote choisit un vecteur accélération `(dvx, dvy)` avec :
  - En mode normal : `dvx, dvy ∈ {-1, 0, 1}` → 9 possibilités
  - Avec boost : `(dvx, dvy) ∈ {-2,-1,0,1,2}² \ {-1,0,1}²` → 16 possibilités supplémentaires
- **5 boosts disponibles**, à usage unique.
- Nouvelle vitesse : `vnew = vbefore + a`
- Nouvelle position : `pos_new = pos + vnew`
- **Norme de vitesse ≤ 5** (≤ 1 dans le sable).

### 3.4 Conditions d'invalidité (→ vitesse remise à zéro, voiture immobilisée)

- Accélération invalide (hors plage autorisée)
- Vitesse résultante dépassant la norme max
- Position finale hors-piste ou occupée par une autre voiture
- **Trajectoire passant par une case hors-piste ou occupée** (pas de téléportation — toutes les positions intermédiaires sont vérifiées)

> Un pilote est considéré arrivé **uniquement si sa position finale** est sur une case `=` (les positions intermédiaires ne comptent pas pour la ligne d'arrivée).

### 3.5 Gestion du carburant

- Réserve initiale `C` fournie en début de course (première ligne de la carte).
- Consommation par tour :

```
Δc = -( (dvx)² + (dvy)² + floor( sqrt( 3*(vx² + vy²) / 2 ) ) )
```

> Notation exacte du PDF : `Δc = -( (dvx)² + (dvy)² + ⌊ √(3(vx²+vy²)/2) ⌋ )`

- Pénalité supplémentaire : **-1 par tour passé dans le sable**.
- La consommation est calculée **même si l'accélération est invalide**.
- Si `C ≤ 0` → voiture arrêtée (vitesse nulle).
- **C'est au pilote de calculer lui-même son carburant restant.**

### 3.6 Positions intermédiaires

- Bibliothèque fournie : `./follow_line/` (`follow_line.h`, `follow_line.c`)
- Fonctions utiles : `initLine()` et `nextPoint()` pour parcourir les cases d'un segment.
- Exemple d'utilisation : `./follow_line/main.c` (fonction `traverse()`).

---

## 4. Structure du projet

```
./drivers/              ← vos pilotes compilés (nécessaire pour que le GDC les lance)
./tracks/               ← 10 cartes disponibles
./test_pilot/           ← pilote exemple "droitAuBut" (naïf)
./follow_line/          ← bibliothèque de parcours de segments
./include/gpcontrol.h   ← gestion des collisions dans le GDC (lecture seule)
./src/gpcontrol.cpp
```

### Cartes disponibles

| Fichier | Difficulté |
|---------|-----------|
| `starter_droit_au_but.txt` | Très facile |
| `starter_virages.txt` | Normale |
| `starter_virage_sable.txt` | Difficile |
| `starter_deux_virages.txt` | — |
| `starter_raccourcis.txt` | — |
| `starter_serpent.txt` | — |
| `f-Zero_Crossroad_Circuit.txt` | — |
| `f-Zero_Crossroad_Circuit_mur.txt` | — |
| `f-Zero_Death_Wind.txt` | — |
| `f-Zero_Landmine_Circuit.txt` | — |

> Les cartes de la phase éliminatoire et de la finale sont **inconnues** à l'avance.

---

## 5. Débogage

- **Option 1** : écrire dans un fichier texte dédié.
- **Option 2** : écrire sur `stderr` → le GDC sauvegarde dans `stderr_driver_N.txt` et affiche en temps réel via le bouton « StdErr ».
- **libasan** (`-fsanitize=address`) : détecte SEGFAULT et erreurs mémoire. Version à installer selon le compilateur :

| gcc | paquet |
|-----|--------|
| 4.8 | libasan0 |
| 5 | libasan2 |
| 6 | libasan3 |
| 7 | libasan4 |
| 8 | libasan5 |

> ⚠️ **Désactiver les logs et `-fsanitize=address` avant de rendre le pilote** — impact significatif sur les performances.

---

## 6. Dossier à remettre (archive)

- Tous les fichiers **nécessaires et uniquement eux** à la compilation sur cybele/bâtiment E.
- Un fichier `Makefile` correct (avec les flags obligatoires).
- **Aucun exécutable.**
- Le dossier peut inclure `follow_line.h` et `follow_line.c` si utilisés.
- Vérifier la compilation propre avant soumission.


## 10. Évaluation

- Qualité de la présentation orale
- Qualité du support de présentation
- Qualité du rapport
- Qualité du code source
- Solution algorithmique (écrite, orale, implémentée)
- Bonification compétition
---

## 11. Format de la compétition

- Phase de poules : courses à 3 pilotes, chaque pilote fait 3 courses.
- Points par course : 1er → 4 pts, 2e → 2 pts, 3e → 0 pt.
- Un pilote qui ne quitte pas la ligne de départ → **0 point**.
- Phase éliminatoire : 1/8, 1/4, demi-finales, finale.
- Finale : best of 3 (2 courses gagnantes).
- Petite finale (3e/4e) : 1 course.
- Les cartes de la phase éliminatoire et finale sont **inconnues**.
- Si un pilote ralentit excessivement la course (abus de temps de calcul) → arrêt artificiel possible.
