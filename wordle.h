#ifndef WORDLE_H
#define WORDLE_H

#define WORD_LEN 5
#define MAX_ATTEMPTS 6
#define MAX_WORDS 1000

void to_upper(char *s);

int load_dictionary(char words[MAX_WORDS][WORD_LEN + 1]);
int is_valid_word(char words[MAX_WORDS][WORD_LEN + 1], int n, char *guess);

void compute_feedback(char *target, char *guess, char *feedback);

int match_feedback(char *word, char *guess, char *feedback);
int filter_words(
    char words[MAX_WORDS][WORD_LEN + 1],
    int n,
    char *guess,
    char *feedback,
    char new_words[MAX_WORDS][WORD_LEN + 1]
);

void print_colored(char *guess, char *feedback);

void mode_joueur(char words[MAX_WORDS][WORD_LEN + 1], int total);
void mode_solveur(char words[MAX_WORDS][WORD_LEN + 1], int total);
void mode_solveur_interactif(char words[MAX_WORDS][WORD_LEN + 1], int total);

#endif
