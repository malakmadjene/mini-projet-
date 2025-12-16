#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "wordle.h"

/* ===== UTILS ===== */
void to_upper(char *s) {
for (int i = 0; s[i]; i++)
if (s[i] >= 'a' && s[i] <= 'z')
s[i] -= 32;
}

/* ===== DICTIONARY ===== */
int load_dictionary(char words[MAX_WORDS][WORD_LEN + 1]) {
FILE *f = fopen("words.txt", "r");
if (!f) {
printf("Erreur ouverture dictionnaire\n");
exit(1);
}

int count = 0;
while (fscanf(f, "%5s", words[count]) != EOF) {
to_upper(words[count]);
count++;
}
fclose(f);
return count;
}

int is_valid_word(char words[MAX_WORDS][WORD_LEN + 1], int n, char *guess) {
for (int i = 0; i < n; i++)
if (strcmp(words[i], guess) == 0)
return 1;
return 0;
}

/* ===== FEEDBACK ===== */
void compute_feedback(char *target, char *guess, char *feedback) {
int used[WORD_LEN] = {0};

for (int i = 0; i < WORD_LEN; i++) {
if (guess[i] == target[i]) {
feedback[i] = 'G';
used[i] = 1;
} else {
feedback[i] = 'X';
}
}

for (int i = 0; i < WORD_LEN; i++) {
if (feedback[i] == 'X') {
for (int j = 0; j < WORD_LEN; j++) {
if (!used[j] && guess[i] == target[j]) {
feedback[i] = 'Y';
used[j] = 1;
break;
}
}
}
}
feedback[WORD_LEN] = '\0';
}

/* ===== SOLVER LOGIQUE ===== */
int match_feedback(char *word, char *guess, char *feedback) {
char temp[WORD_LEN + 1];
compute_feedback(word, guess, temp);
return strcmp(temp, feedback) == 0;
}

int filter_words(
char words[MAX_WORDS][WORD_LEN + 1],
int n,
char *guess,
char *feedback,
char new_words[MAX_WORDS][WORD_LEN + 1]
) {
int count = 0;
for (int i = 0; i < n; i++)
if (match_feedback(words[i], guess, feedback))
strcpy(new_words[count++], words[i]);
return count;
}

/* ===== COULEURS ===== */
#define GREEN "\033[1;42m"
#define YELLOW "\033[1;43m"
#define GRAY "\033[1;47m"
#define RESET "\033[0m"

void print_colored(char *guess, char *feedback) {
for (int i = 0; i < WORD_LEN; i++) {
if (feedback[i] == 'G')
printf(GREEN " %c " RESET, guess[i]);
else if (feedback[i] == 'Y')
printf(YELLOW " %c " RESET, guess[i]);
else
printf(GRAY " %c " RESET, guess[i]);
}
printf("\n");
}

/* ===== MODE JOUEUR ===== */
void mode_joueur(char words[MAX_WORDS][WORD_LEN + 1], int total) {
char target[WORD_LEN + 1];
char guess[WORD_LEN + 1];
char feedback[WORD_LEN + 1];

strcpy(target, words[rand() % total]);

printf("\n===== WORDLE (Mode Joueur) =====\n");
printf("Devinez le mot (5 lettres)\n");
printf("6 tentatives maximum\n\n");

for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
do {
printf("Tentative %d/%d : ", attempt, MAX_ATTEMPTS);
scanf("%5s", guess);
to_upper(guess);

if (!is_valid_word(words, total, guess))
printf("Mot invalide\n");

} while (!is_valid_word(words, total, guess));

compute_feedback(target, guess, feedback);
print_colored(guess, feedback);

if (strcmp(feedback, "GGGGG") == 0) {
printf("BRAVO ! Vous avez gagne !\n");
return;
}
}

printf("Perdu :( ! Le mot etait : %s\n", target);
}

/* ===== MODE SOLVEUR AUTOMATIQUE ===== */
void mode_solveur(char words[MAX_WORDS][WORD_LEN + 1], int total) {
char possible[MAX_WORDS][WORD_LEN + 1];
char next[MAX_WORDS][WORD_LEN + 1];
char target[WORD_LEN + 1];
char guess[WORD_LEN + 1];
char feedback[WORD_LEN + 1];

strcpy(target, words[rand() % total]);

for (int i = 0; i < total; i++)
strcpy(possible[i], words[i]);

int count = total;

printf("\n===== WORDLE (Solveur Automatique) =====\n");

for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
strcpy(guess, possible[0]);
compute_feedback(target, guess, feedback);

printf("Tentative %d : %s\n", attempt, guess);
print_colored(guess, feedback);

if (strcmp(feedback, "GGGGG") == 0) {
printf("Solveur a trouve le mot !\n");
return;
}

count = filter_words(possible, count, guess, feedback, next);
for (int i = 0; i < count; i++)
strcpy(possible[i], next[i]);
}

printf("Solveur a perdu. Mot etait : %s\n", target);
}

/* ===== MODE SOLVEUR INTERACTIF ===== */
void mode_solveur_interactif(char words[MAX_WORDS][WORD_LEN + 1], int total) {
char possible[MAX_WORDS][WORD_LEN + 1];
char next[MAX_WORDS][WORD_LEN + 1];
char guess[WORD_LEN + 1];
char feedback[WORD_LEN + 1];

for (int i = 0; i < total; i++)
strcpy(possible[i], words[i]);

int count = total;

printf("\n===== WORDLE (Solveur Interactif) =====\n");
printf("L'ordinateur propose un mot, vous entrez le feedback (G/Y/X)\n\n");

for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
if (count == 0) {
printf("Aucun mot possible restant ! Verifiez le feedback\n");
return;
}

strcpy(guess, possible[0]);
printf("Tentative %d : %s\n", attempt, guess);

do {
printf("Feedback (G/Y/X) : ");
scanf("%5s", feedback);
to_upper(feedback);
} while (strlen(feedback) != WORD_LEN);

if (strcmp(feedback, "GGGGG") == 0) {
printf("Solveur a trouve le mot secret !\n");
return;
}

count = filter_words(possible, count, guess, feedback, next);
for (int i = 0; i < count; i++)
strcpy(possible[i], next[i]);
}

printf("Solveur n'a pas trouve le mot en %d tentatives.\n", MAX_ATTEMPTS);
}

/* ===== MAIN ===== */
int main() {
char words[MAX_WORDS][WORD_LEN + 1];
int choix;

srand(time(NULL));
int total = load_dictionary(words);

printf("===== WORDLE =====\n");
printf("1 - Joueur humain\n");
printf("2 - Solveur automatique\n");
printf("3 - Solveur interactif (vous donnez le feedback)\n");
printf("Choix : ");
scanf("%d", &choix);

if (choix == 1)
mode_joueur(words, total);
else if (choix == 2)
mode_solveur(words, total);
else if (choix == 3)
mode_solveur_interactif(words, total);
else
printf("Choix invalide\n");

return 0;
}