# 150cc — Pilote autonome de Grand Prix F1

Pilote autonome écrit en C (C89/C90) pour le challenge de programmation de l'ENSICAEN (2025-2026).
Le pilote dialogue avec le Gestionnaire de Course (GDC) par `stdin`/`stdout` : à chaque tour, il reçoit la position des 3 voitures et renvoie une accélération `dvx dvy`, en moins d'une seconde.

**Équipe :** Iwan Clemente · Marius Picard · Yann Moulin

## Fonctionnement

- **Dijkstra inversé** (calculé une seule fois au démarrage) : distance de chaque case jusqu'à l'arrivée, le sable coûtant plus cher. Sert d'heuristique.
- **A\* dans l'espace 4D** `(x, y, vx, vy)` : à chaque tour, recherche du meilleur enchaînement d'accélérations en tenant compte de la physique du jeu (vitesse max 5, max 1 dans le sable), du carburant et des adversaires.
- **Vérification des trajectoires** avec la bibliothèque `follow_line` du GDC : toutes les cases traversées sont contrôlées, pas seulement la case d'arrivée.
- **Timeout interne** pour toujours répondre avant la limite d'une seconde.

## Structure

```
150cc/
├── Makefile
├── src/            code source du pilote
│   ├── main.c          boucle de course
│   ├── communication.c protocole GDC (stdin/stdout)
│   ├── map.c           lecture de la carte
│   ├── physic.c        physique, carburant, validité des coups
│   ├── dijkstra.c      heuristique (Dijkstra inversé)
│   ├── path_search.c   recherche A* 4D
│   ├── heap.c, prio_queue.c  file de priorité
├── include/        en-têtes
├── driver/         copie du binaire compilé
└── gdc/            Gestionnaire de Course (dépôt séparé)
```

## Prérequis

- `gcc` et `make` (Linux Ubuntu 22.04 ou macOS)
- Pour lancer le GDC : Qt (`qmake`)

## Installation

```bash
git clone https://github.com/VeloxxDev/Pilote-automatique.git 150cc
cd 150cc
git clone https://github.com/VeloxxDev/gdc.git gdc   # le GDC est dans un dépôt séparé
```

## Commandes

| Commande | Effet |
|---|---|
| `make` | Compile le pilote avec les flags imposés `-ansi -pedantic -Wall -Wextra`. Le binaire est placé dans `gdc/drivers/150cc` (là où le GDC le cherche) et copié dans `driver/150cc`. |
| `make clean` | Supprime les fichiers objets (`obj/`) et le binaire dans `gdc/drivers/`. |

## Lancer une course

1. Compiler le GDC (une seule fois) :
   ```bash
   cd gdc
   qmake
   make
   ```
2. (Optionnel) Compiler le pilote d'exemple fourni, pour avoir un adversaire :
   ```bash
   make -C ./test_pilot install
   ```
3. Compiler notre pilote depuis la racine du projet :
   ```bash
   cd ..
   make
   ```
4. Lancer le GDC :
   ```bash
   cd gdc
   ./GrandPrix            # Linux
   open GrandPrix.app     # macOS
   ```
5. Dans l'interface : choisir une carte dans `tracks/`, sélectionner `150cc` comme pilote, puis démarrer la course.

Les messages de débogage du pilote (écrits sur `stderr`) sont enregistrés par le GDC dans `stderr_driver_N.txt` et visibles en direct avec le bouton « StdErr ».

## Résultats

Testé sur les 10 cartes fournies (`starter_*` et `f-Zero_*`) : le pilote termine chaque course sans coup invalide ni dépassement du délai d'une seconde.

## Limites

- Les boosts ne sont pas utilisés.
- Les adversaires sont pris en compte seulement sur leur position actuelle (pas de prédiction de leurs mouvements).
