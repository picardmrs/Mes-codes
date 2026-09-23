# Projet Fondements de l'Informatique

**Clemente Iwan — Picard Marius — Moulin Yann**  
10 décembre 2025

---

## Table des matières

1. Introduction
2. Méthodologie et outils
3. Architecture générale du pilote
4. Approche algorithmique
5. Optimisations et spécificités
6. Difficultés rencontrées
7. Résultats et validation
8. Conclusion

Annexes : A. Extraits de code — B. Structures de données — C. Compilation

---

## 1. Introduction

### 1.1 Contexte

Le projet consiste à écrire en C99 un pilote autonome pour une course F1 virtuelle. Le pilote communique avec un Gestionnaire de Course (GDC) via `stdin`/`stdout` : à chaque tour, il reçoit les positions des trois voitures et doit renvoyer une accélération `(ax, ay)` dans un délai strict d'**une seconde**.

### 1.2 Objectifs

Atteindre la ligne d'arrivée le plus vite possible sans :
- sortir de la piste (cases `.`, `~`, `=`, `#`) ;
- tomber à carburant nul ;
- dépasser la limite de vitesse sur sable (`|v| ≤ 1`).

### 1.3 Contraintes techniques

| Contrainte | Valeur |
|---|---|
| Langage | C99, flags `-ansi -pedantic -Wall -Wextra` |
| Temps de calcul / tour | < 1 s (timeout interne : 0,8 s) |
| Accélération | `ax, ay ∈ {-1, 0, +1}` → 9 actions possibles |
| Vitesse | `vx, vy ∈ [-5, +5]` → 121 états de vitesse |
| Espace d'état total | `W × H × 11 × 11` nœuds |

Ces contraintes transforment le pathfinding 2D classique en un **problème d'optimisation dans un espace 4D contraint**.

---

## 2. Méthodologie et outils

### 2.1 Environnement de développement

- Compilateur : `gcc` avec `-ansi -pedantic -Wall -Wextra -O2`
- Makefile minimaliste : cibles `all`, `clean`, `run`
- Débogage via traces `stderr` + fichiers `stderr_driver_N.txt` produits par le GDC

### 2.2 Collaboration

- Git / GitLab avec branches par fonctionnalité et merge requests
- Branches principales : `main`, `astar`, `dijkstra`, `physics`

### 2.3 Répartition du travail

| Membre | Module principal |
|---|---|
| Iwan | A\* (recherche dynamique) |
| Marius | Dijkstra inversé (heuristique) |
| Yann | Communication GDC, file de priorité (min-heap), structures communes |

Après les fondations, développement en alternance par itérations tests/ajustements.

---

## 3. Architecture générale

### 3.1 Modules

```
main.c
├── comm.c        lecture/écriture stdin/stdout (protocole GDC)
├── map.c         parsing et stockage de la grille + zones spéciales
├── physics.c     validation de mouvement, suivi de ligne, consommation
└── path_search.c A* 4D + Dijkstra inversé
```

**schéma** *Diagramme de dépendances entre modules : flèches d'appel de main → comm/map/physics/path_search, et flèches internes path_search → physics*

### 3.2 Cycle de décision (par tour)

```
GDC → [positions x3] → mise à jour état interne (vx, vy, fuel)
    → A* 4D depuis (x, y, vx, vy) courant
    → remontée du chemin → extraction du premier mouvement (ax, ay)
    → stdout → GDC
```

**schéma** *Flowchart du cycle : réception → parsing → A* → vérification fuel → envoi accélération → boucle suivante*

Contraintes du cycle :
- Pas d'allocation dynamique pendant la recherche (pool pré-alloué)
- Réinitialisation du marquage 4D en O(1) (identifiant de recherche incrémental)
- Sortie anticipée si `clock() > T_start + 0.8s`

### 3.3 Protocole GDC

```
Initialisation : lecture carte (W H, puis H lignes)
Tour n         : "x1 y1 x2 y2 x3 y3\n"  ← 6 entiers
Réponse        : "ax ay\n"               → 2 entiers ∈ {-1,0,+1}
```

---

## 4. Approche algorithmique

### 4.1 Représentation de l'espace d'état

Un nœud est le quadruplet `s = (x, y, vx, vy)`.

La transition physique est :
```
vx' = vx + ax       vy' = vy + ay
x'  = x  + vx'      y'  = y  + vy'
```
avec `ax, ay ∈ {-1, 0, +1}` → **9 successeurs** par nœud.

Taille de l'espace : `W × H × 11 × 11`. Sur une carte 100×100 : ~1,2 M nœuds.

**schéma** *Comparaison espace d'état 2D (grille positionnelle) vs 4D (grille + vecteur vitesse) : deux états à même position (x,y) mais vitesses différentes → successeurs distincts*

### 4.2 Dijkstra inversé (pré-calcul de l'heuristique)

Exécuté **une seule fois** au démarrage sur la grille 2D.

```
Source : toutes les cases de la ligne d'arrivée (coût 0)
Coût d'un arc :
  case '.' ou '=' → +1
  case '~'        → +7   (pénalité sable)
  case '#'        → infini (mur, non traversable)
```

Résultat : tableau `dist[x][y]` = distance minimale pondérée vers l'arrivée depuis `(x,y)`.

Complexité : O((W·H) log(W·H)) avec la min-heap.

**schéma** *Heatmap de la carte avec gradient de couleur représentant dist[x][y] : zones proches de l'arrivée en bleu froid, zones éloignées ou sable en rouge chaud*

### 4.3 A\* dans l'espace 4D

**Heuristique** :
```c
h(s) = dist[x][y] / 7
```
Le diviseur 7 est le coût maximum par case (sable), ce qui garantit **h admissible** (h ne surestime jamais g\*) et donc l'**optimalité** de la solution.

**Coût réel** d'un arc `s → s'` :
```c
g_cost = (terrain[x'][y'] == '~') ? 7 : 1
```

**Condition de revisit** : un état `s` est ignoré si déjà visité avec `fuel_visited ≥ fuel_courant`. Sinon rouvrir (nécessaire à cause du sable qui différencie deux chemins à même état cinématique).

**Reconstruction** : remontée des pointeurs parents jusqu'à la racine → le premier mouvement de la liste est renvoyé au GDC.

**schéma** *Illustration A\* sur petit exemple : graphe d'états (x,y,vx,vy) avec arcs, coûts g+h, file de priorité, et chemin optimal coloré*

### 4.4 Validation de trajectoire — `follow_line`

Entre deux positions `(x0,y0)` et `(x1,y1)` (potentiellement non adjacentes à haute vitesse), `follow_line` vérifie **toutes les cases intermédiaires** par algorithme de tracé de segment discret (Bresenham).

Conditions de rejet :
- case hors grille
- case `'#'` (mur)
- case occupée par un adversaire (position courante du tour)

**schéma** *Exemple de trajectoire à vitesse 3 : cases intermédiaires vérifiées une à une, mise en évidence d'un mur qui invalide le mouvement*

### 4.5 Consommation de carburant

Formule appliquée à chaque transition :

```
Δfuel = -(ax² + ay² + ⌊√(vx'² + vy'²) × 1.5⌋)
```
avec un malus additionnel de `-1` si la case courante est `'~'`.

- Terme `ax² + ay²` : pénalise les accélérations (énergie cinétique)
- Terme `⌊√(v²) × 1.5⌋` : modélise la traînée aérodynamique

Un mouvement est refusé par A\* si `fuel_après ≤ 0`.

Sur sable, la vitesse est bornée à `|vx'| ≤ 1` et `|vy'| ≤ 1` pour éviter les consommations excessives.

---

## 5. Optimisations et spécificités

### 5.1 Pool de nœuds pré-alloué

```c
#define POOL_SIZE (W * H * 11 * 11)
AStarNode pool[POOL_SIZE];
int pool_index = 0;   // réinitialisé à 0 à chaque tour
```

Aucun `malloc`/`free` pendant la course → pas de fragmentation, latence stable.

**schéma** *Schéma mémoire : tableau statique pool[], pointeur pool_index qui avance à chaque allocation, réinitialisé en début de tour*

### 5.2 Marquage 4D avec identifiant de recherche

```c
uint32_t visited[W][H][11][11];  // valeur = search_id au moment de la visite
uint32_t search_id = 0;
// Pour marquer : visited[x][y][vx+5][vy+5] = search_id
// Pour tester  : visited[...] == search_id
// Réinitialisation : search_id++  → O(1) au lieu de memset O(W*H*121)
```

### 5.3 Timeout adaptatif

```c
if (clock() - t_start > 0.8 * CLOCKS_PER_SEC) {
    /* retourner le meilleur nœud atteint (plus faible f = g+h) */
}
```

Marge de 0,2 s sur la limite GDC d'1 s pour absorber les variations système.

### 5.4 Min-heap pour la file de priorité

Implémentation tableau avec `sift_up` / `sift_down`. Opérations en O(log n).

---

## 6. Difficultés rencontrées

### 6.1 Gestion mémoire temps réel

**Problème** : `malloc` répété à chaque tour → fragmentation mesurable, pics de latence.  
**Solution** : pool pré-alloué (§5.1), réinitialisation par pointeur en O(1).

### 6.2 Revisit avec carburant variable

**Problème** : un état `(x, y, vx, vy)` peut être atteint par plusieurs chemins avec des niveaux de carburant différents. Marquage binaire insuffisant.  
**Solution** : stocker `fuel` dans le nœud visité ; rouvrir si `fuel_nouveau > fuel_visité`.

### 6.3 Timeout sur grandes cartes

**Problème** : sur cartes 100×100+, l'espace 4D devient trop vaste pour être exploré complètement en 0,8 s.  
**Solution** : retour du meilleur nœud en cours (f minimal dans la frontière ouverte) ; l'heuristique Dijkstra assure une direction cohérente même avec exploration partielle.

### 6.4 Cohérence physique à haute vitesse

**Problème** : à `|v| = 4`, la voiture "saute" 4 cases par tour. Un mur entre `(x,y)` et `(x+4,y)` n'était pas détecté.  
**Solution** : `follow_line` vérifie chaque case intermédiaire (§4.4).

---

## 7. Résultats et validation

### 7.1 Méthodologie de test

Tests en conditions réelles contre le GDC sur l'ensemble des cartes fournies. Métriques observées : atteinte de l'arrivée, nombre de tours, carburant restant, sortie de piste (= 0 attendu).

### 7.2 Comportement observé

| Critère | Résultat |
|---|---|
| Sorties de piste | 0 |
| Pannes sèches | 0 |
| Gestion des collisions | réinitialisation vitesse → OK |
| Respect des limites sable | OK |

### 7.3 Comparaison avec `droitAuBut`

| Scénario | Notre pilote | `droitAuBut` |
|---|---|---|
| Circuit avec virages | Termine, trajectoire lisse | Sort de piste |
| Ligne droite pure | Plus lent (prudent) | Plus rapide |
| Zone sable | Contourne si possible | Traverse, ralentit |

### 7.4 Limites

- Boosts non implémentés → sous-performance sur lignes droites longues
- Adversaires pris en compte uniquement sur leur position courante (pas de prédiction multi-tours)
- Comportement conservateur en fin de carburant (exploration A\* tronquée par la contrainte `fuel > 0`)

---

## 8. Conclusion

Notre pilote combine une recherche A\* dans un espace 4D `(x, y, vx, vy)` avec une heuristique Dijkstra inversée pré-calculée. L'espace d'état modélise fidèlement la physique du jeu ; la consommation est intégrée comme contrainte dans l'exploration. Les optimisations (pool, marquage incrémental, timeout) maintiennent le temps de réponse sous 0,8 s sur l'ensemble des cartes testées.

Améliorations possibles : intégration des boosts, prédiction des adversaires sur N tours, heuristique 4D (intégrant vitesse) pour réduire le nombre de nœuds explorés.

---

## Annexes

### A. Extraits de code pertinents

*(file de priorité, follow_line, formule carburant)*

### B. Structures de données

```c
typedef struct {
    int x, y, vx, vy;
    int g, h, fuel;
    int parent_idx;
} AStarNode;
```

### C. Compilation

```bash
make          # gcc -ansi -pedantic -Wall -Wextra -O2 -o pilote src/*.c
make run      # ./pilote < carte.txt
```
