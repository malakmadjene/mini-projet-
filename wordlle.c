#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/* ===== FEEDBACK LOGIQUE ===== */
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
