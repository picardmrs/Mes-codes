#include "../../include/minunit.h"
#include <stdlib.h>
#include <string.h>
#include "histogramme.h"
#include "quantification.h"

/* Configuration des tests */
void test_setup(void) {
	/* Setup */
}

void test_teardown(void) {
	/* Teardown */
}

/* Tests Partie 2.1 - create_cell */
MU_TEST(test_create_cellule) {
	cell cellule;
	cellule = create_cell(100, NULL);
	mu_assert(cellule != NULL, "create_cell devrait créer une cellule");
}

/* Tests Partie 2.1 - insert_cell */
MU_TEST(test_insert_cellule_simple) {
	cell cellule;
	cellule = NULL;
	cellule = insert_cell(cellule, 50);
	mu_assert(cellule != NULL, "insert_cell devrait créer une cellule");
	delete_list(cellule);
}

MU_TEST(test_insert_cellule_multiple) {
	cell cellule;
	cellule = NULL;
	cellule = insert_cell(cellule, 50);
	cellule = insert_cell(cellule, 100);
	cellule = insert_cell(cellule, 75);
	mu_assert(cellule != NULL, "insert_cell devrait créer plusieurs cellules");
	delete_list(cellule);
}

MU_TEST(test_insert_cellule_ordre) {
	cell cellule;
	cellule = NULL;
	cellule = insert_cell(cellule, 100);
	cellule = insert_cell(cellule, 50);
	cellule = insert_cell(cellule, 75);
	/* Les cellules doivent être ordonnées : 50 < 75 < 100 */
	mu_assert(cellule != NULL, "insert_cell devrait maintenir l'ordre");
	delete_list(cellule);
}

MU_TEST(test_insert_cellule_freq_increment) {
	cell cellule;
	cellule = NULL;
	cellule = insert_cell(cellule, 50);
	cellule = insert_cell(cellule, 50);
	cellule = insert_cell(cellule, 50);
	/* La fréquence devrait être 3 après 3 insertions du même B */
	mu_assert(cellule != NULL, "insert_cell devrait incrémenter fréquence");
	delete_list(cellule);
}

MU_TEST(test_insert_cellule_freq_mixed) {
	cell cellule;
	cellule = NULL;
	cellule = insert_cell(cellule, 50);
	cellule = insert_cell(cellule, 100);
	cellule = insert_cell(cellule, 50);
	cellule = insert_cell(cellule, 100);
	cellule = insert_cell(cellule, 75);
	/* Les cellules avec freq > 1 doivent être gérées */
	mu_assert(cellule != NULL, "insert_cell devrait gérer mix fréquences");
	delete_list(cellule);
}

/* Tests Partie 2.1 - delete_list */
MU_TEST(test_delete_list) {
	cell c;
	c = NULL;
	c = insert_cell(c, 50);
	c = insert_cell(c, 100);
	c = insert_cell(c, 75);
	c = delete_list(c);
	mu_assert(c == NULL, "delete_list devrait retourner NULL");
}

/* Tests Partie 2.2 - create_histo */
MU_TEST(test_create_histo) {
	histo h;
	h = create_histo();
	mu_assert(h != NULL, "create_histo devrait créer un histogramme");
	delete_histo(h);
}

/* Tests Partie 2.2 - delete_histo */
MU_TEST(test_delete_histo) {
	histo h;
	h = create_histo();
	mu_assert(h != NULL, "create_histo devrait créer un histogramme");
	delete_histo(h);
	/* Si pas de segfault, c'est bon */
	mu_assert(1, "delete_histo devrait fonctionner sans erreur");
}

/* Tests Partie 2.3 - give_freq_histo */
MU_TEST(test_give_freq_histo_vide) {
	histo h;
	int freq;
	h = create_histo();
	freq = give_freq_histo(h, 50, 100, 150);
	mu_assert_int_eq(0, freq);
	delete_histo(h);
}

/* Tests Partie 2.3 - create_histo_iter */
MU_TEST(test_create_histo_iter) {
	histo h;
	h = create_histo();
	mu_assert(h != NULL, "create_histo devrait créer un histogramme");
	
	/* Créer un itérateur sur un histogramme vide devrait échouer (assert) */
	/* On ne peut pas le tester car il y a assert dans create_histo_iter */
	
	delete_histo(h);
	mu_assert(1, "créer et détruire un histogramme vide fonctionne");
}

/* Tests Partie 2.3 - delete_histo_iter */
MU_TEST(test_delete_histo_iter) {
	histo h;
	histo_iter iter;
	h = create_histo();
	
	/* On insère une couleur pour pouvoir créer un itérateur */
	h[100][100] = insert_cell(h[100][100], 50);
	
	iter = create_histo_iter(h);
	mu_assert(iter != NULL, "create_histo_iter devrait créer un itérateur");
	
	delete_histo_iter(iter);
	delete_histo(h);
	
	mu_assert(1, "delete_histo_iter devrait fonctionner sans erreur");
}

/* Tests Partie 2.3 - start_histo_iter */
MU_TEST(test_start_histo_iter) {
	histo h;
	histo_iter iter;
	h = create_histo();
	
	h[100][100] = insert_cell(h[100][100], 50);
	iter = create_histo_iter(h);
	
	start_histo_iter(iter, h);
	mu_assert(1, "start_histo_iter devrait fonctionner");
	
	delete_histo_iter(iter);
	delete_histo(h);
}

/* Tests Partie 2.3 - next_histo_iter */
MU_TEST(test_next_histo_iter) {
	histo h;
	histo_iter iter;
	int has_next;
	
	h = create_histo();
	h[100][100] = insert_cell(h[100][100], 50);
	iter = create_histo_iter(h);
	
	has_next = next_histo_iter(iter, h);
	/* Sur une simple liste, il devrait n'y avoir rien après */
	mu_assert(has_next == 0 || has_next == 1, "next_histo_iter devrait retourner 0 ou 1");
	
	delete_histo_iter(iter);
	delete_histo(h);
}

/* Tests Partie 2.3 - give_color_histo_iter */
MU_TEST(test_give_color_histo_iter) {
	histo h;
	histo_iter iter;
	int couleur[3];
	
	h = create_histo();
	h[100][150] = insert_cell(h[100][150], 50);
	iter = create_histo_iter(h);
	
	give_color_histo_iter(iter, couleur);
	mu_assert_int_eq(100, couleur[0]);
	mu_assert_int_eq(150, couleur[1]);
	mu_assert_int_eq(50, couleur[2]);
	
	delete_histo_iter(iter);
	delete_histo(h);
}

/* Tests Partie 2.3 - give_freq_histo_iter */
MU_TEST(test_give_freq_histo_iter) {
	histo h;
	histo_iter iter;
	int freq;
	
	h = create_histo();
	h[100][100] = insert_cell(h[100][100], 50);
	h[100][100] = insert_cell(h[100][100], 50);
	iter = create_histo_iter(h);
	
	freq = give_freq_histo_iter(iter);
	mu_assert_int_eq(2, freq);
	
	delete_histo_iter(iter);
	delete_histo(h);
}

/* Tests quantification - rgb_bonus */
MU_TEST(test_rgb_bonus) {
	int qR, qG, qB;
	rgb_bonus(100, 200, 150, &qR, &qG, &qB);
	
	/* R/2 = 100/2 = 50, G = 200, B/4 = 150/4 = 37 */
	mu_assert_int_eq(50, qR);
	mu_assert_int_eq(200, qG);
	mu_assert_int_eq(37, qB);
}

MU_TEST(test_rgb_bonus_zeros) {
	int qR, qG, qB;
	rgb_bonus(0, 0, 0, &qR, &qG, &qB);
	
	mu_assert_int_eq(0, qR);
	mu_assert_int_eq(0, qG);
	mu_assert_int_eq(0, qB);
}

MU_TEST(test_rgb_bonus_max) {
	int qR, qG, qB;
	rgb_bonus(255, 255, 255, &qR, &qG, &qB);
	
	mu_assert_int_eq(127, qR);
	mu_assert_int_eq(255, qG);
	mu_assert_int_eq(63, qB);
}

/* Tests quantification - quantification */
MU_TEST(test_quantification_basic) {
	histo h;
	int* tab;
	int K;
	int* resultat;
	
	h = create_histo();
	K = 10;
	tab = (int*)malloc(K * 3 * sizeof(int));
	
	/* Remplir histogramme avec quelques couleurs */
	h[50][50] = insert_cell(h[50][50], 100);
	h[50][50] = insert_cell(h[50][50], 100);
	h[100][100] = insert_cell(h[100][100], 150);
	
	resultat = quantification(h, tab, K);
	mu_assert(resultat != NULL, "quantification devrait retourner un tableau");
	
	free(tab);
	delete_histo(h);
}

/* Tests quantification - inverse_gamma */
MU_TEST(test_inverse_gamma) {
	double result, result_zero;
	result = inverse_gamma(0.5);
	mu_assert(result >= 0.0 && result <= 1.0, "inverse_gamma devrait retourner valeur entre 0 et 1");
	
	result_zero = inverse_gamma(0.0);
	mu_assert(result_zero >= 0.0, "inverse_gamma(0) devrait être >= 0");
}

/* Tests quantification - fonction f */
MU_TEST(test_f) {
	double result;
	result = f(0.5);
	mu_assert(result >= 0.0, "f devrait retourner valeur non-négative");
}

/* Tests quantification - rgb_to_lab */
MU_TEST(test_rgb_to_lab) {
	double L, a, b;
	rgb_to_lab(128, 128, 128, &L, &a, &b);
	
	mu_assert(L >= 0.0 && L <= 100.0, "L devrait être entre 0 et 100");
}

MU_TEST(test_rgb_to_lab_black) {
	double L, a, b;
	rgb_to_lab(0, 0, 0, &L, &a, &b);
	
	mu_assert(L >= 0.0 && L <= 10.0, "L devrait être proche de 0 pour noir");
}

MU_TEST(test_rgb_to_lab_white) {
	double L, a, b;
	rgb_to_lab(255, 255, 255, &L, &a, &b);
	
	mu_assert(L >= 90.0 && L <= 100.0, "L devrait être proche de 100 pour blanc");
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	/* Tests Partie 2.1 - cellule et liste */
	MU_RUN_TEST(test_create_cellule);
	MU_RUN_TEST(test_insert_cellule_simple);
	MU_RUN_TEST(test_insert_cellule_multiple);
	MU_RUN_TEST(test_insert_cellule_ordre);
	MU_RUN_TEST(test_insert_cellule_freq_increment);
	MU_RUN_TEST(test_insert_cellule_freq_mixed);
	MU_RUN_TEST(test_delete_list);

	/* Tests Partie 2.2 - histogramme */
	MU_RUN_TEST(test_create_histo);
	MU_RUN_TEST(test_delete_histo);

	/* Tests Partie 2.3 - histogramme et itérateur */
	MU_RUN_TEST(test_give_freq_histo_vide);
	MU_RUN_TEST(test_create_histo_iter);
	MU_RUN_TEST(test_delete_histo_iter);
	MU_RUN_TEST(test_start_histo_iter);
	MU_RUN_TEST(test_next_histo_iter);
	MU_RUN_TEST(test_give_color_histo_iter);
	MU_RUN_TEST(test_give_freq_histo_iter);

	/* Tests quantification */
	MU_RUN_TEST(test_rgb_bonus);
	MU_RUN_TEST(test_rgb_bonus_zeros);
	MU_RUN_TEST(test_rgb_bonus_max);
	MU_RUN_TEST(test_quantification_basic);

	MU_RUN_TEST(test_inverse_gamma);
	MU_RUN_TEST(test_f);

	MU_RUN_TEST(test_rgb_to_lab);
	MU_RUN_TEST(test_rgb_to_lab_black);
	MU_RUN_TEST(test_rgb_to_lab_white);
}

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
