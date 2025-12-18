#include <stdio.h>  // Bibliothèque standard pour les entrées/sorties (printf, scanf)
#include <stdlib.h> // Fonctions utilitaires (exit, rand, srand)
#include <string.h> // Manipulation des chaînes de caractères (strcmp, strcpy, strlen)
#include <time.h>   // Gestion du temps (time) pour l'aléatoire
#include "wordle.h" // Fichier d'en-tête du projet (constantes et prototypes)

/*  FONCTIONS UTILES   */

// Cette fonction transforme une chaîne de caractères en MAJUSCULES
// Exemple : "apple" -> "APPLE"
void to_upper(char *s)
{
    // On parcourt la chaîne caractère par caractère
    for (int i = 0; s[i]; i++)
    {
        // Si le caractère est une lettre minuscule
        if (s[i] >= 'a' && s[i] <= 'z')
            // On la transforme en majuscule (différence ASCII = 32)
            s[i] -= 32;
    }
}

/* =====================================================
   ==================  DICTIONNAIRE   /

// Cette fonction charge les mots du fichier words.txt
// words : tableau qui va contenir les mots
// Retour : nombre total de mots chargés
int load_dictionary(char words[MAX_WORDS][WORD_LEN + 1])
{
    // Ouverture du fichier dictionnaire en lecture
    FILE *f = fopen("words.txt", "r");

    // Si le fichier n'existe pas ou ne s'ouvre pas
    if (!f)
    {
        printf("Erreur ouverture dictionnaire\n");
        exit(1); // Arrêt brutal du programme
    }

    int count = 0; // Compteur de mots

    // Lecture des mots (5 lettres maximum par mot)
    while (fscanf(f, "%5s", words[count]) != EOF)
    {
        // Conversion du mot en majuscules
        to_upper(words[count]);
        count++; // On passe au mot suivant
    }

    fclose(f);    // Fermeture du fichier
    return count; // Retourne le nombre de mots
}

// Vérifie si un mot proposé est valide (présent dans le dictionnaire)
// Retourne 1 si oui, 0 sinon
int is_valid_word(char words[MAX_WORDS][WORD_LEN + 1], int n, char *guess)
{
    // On parcourt tous les mots du dictionnaire
    for (int i = 0; i < n; i++)
    {
        // Comparaison du mot proposé avec un mot du dictionnaire
        if (strcmp(words[i], guess) == 0)
            return 1; // Mot trouvé
    }
    return 0; // Mot invalide
}

/* =====================================================
   ===================  FEEDBACK  ======================
   ===================================================== */

// Calcule le feedback Wordle entre le mot secret et la proposition
// G = lettre correcte et bien placée
// Y = lettre présente mais mal placée
// X = lettre absente
void compute_feedback(char *target, char *guess, char *feedback)
{
    int used[WORD_LEN] = {0}; // Tableau pour marquer les lettres déjà utilisées

    // Première passe : lettres bien placées (VERT)
    for (int i = 0; i < WORD_LEN; i++)
    {
        if (guess[i] == target[i])
        {
            feedback[i] = 'G'; // Green
            used[i] = 1;       // Lettre déjà utilisée
        }
        else
        {
            feedback[i] = 'X'; // Par défaut : lettre absente
        }
    }

    // Deuxième passe : lettres présentes mais mal placées (JAUNE)
    for (int i = 0; i < WORD_LEN; i++)
    {
        if (feedback[i] == 'X')
        {
            for (int j = 0; j < WORD_LEN; j++)
            {
                if (!used[j] && guess[i] == target[j])
                {
                    feedback[i] = 'Y'; // Yellow
                    used[j] = 1;       // Marquer comme utilisée
                    break;             // Sortir de la boucle
                }
            }
        }
    }

    feedback[WORD_LEN] = '\0'; // Fin de chaîne
}

/* =====================================================
   =================  LOGIQUE SOLVEUR  =================
   ===================================================== */

// Vérifie si un mot possible est compatible avec un feedback donné
int match_feedback(char *word, char *guess, char *feedback)
{
    char temp[WORD_LEN + 1]; // Feedback temporaire

    // On calcule le feedback théorique
    compute_feedback(word, guess, temp);

    // On compare avec le feedback réel
    return strcmp(temp, feedback) == 0;
}

// Filtre la liste des mots possibles après un feedback
int filter_words(
    char words[MAX_WORDS][WORD_LEN + 1],
    int n,
    char *guess,
    char *feedback,
    char new_words[MAX_WORDS][WORD_LEN + 1])
{
    int count = 0; // Compteur de mots restants

    // Pour chaque mot possible
    for (int i = 0; i < n; i++)
    {
        // Si le mot est compatible avec le feedback
        if (match_feedback(words[i], guess, feedback))
        {
            // On le conserve
            strcpy(new_words[count++], words[i]);
        }
    }
    return count; // Nouveau nombre de mots possibles
}

/* =====================================================
   ====================  COULEURS  =====================
   ===================================================== */

// Codes ANSI pour afficher des couleurs dans le terminal
#define GREEN "\033[1;42m"  // Fond vert
#define YELLOW "\033[1;43m" // Fond jaune
#define GRAY "\033[1;47m"   // Fond gris
#define RESET "\033[0m"     // Réinitialisation

// Affiche un mot avec les couleurs Wordle
void print_colored(char *guess, char *feedback)
{
    for (int i = 0; i < WORD_LEN; i++)
    {
        if (feedback[i] == 'G')
            printf(GREEN " %c " RESET, guess[i]);
        else if (feedback[i] == 'Y')
            printf(YELLOW " %c " RESET, guess[i]);
        else
            printf(GRAY " %c " RESET, guess[i]);
    }
    printf("\n");
}

/* =====================================================
   ===================  MODE JOUEUR  ===================
   ===================================================== */

// Mode où l'utilisateur joue lui-même
void mode_joueur(char words[MAX_WORDS][WORD_LEN + 1], int total)
{
    char target[WORD_LEN + 1];   // Mot secret
    char guess[WORD_LEN + 1];    // Mot proposé
    char feedback[WORD_LEN + 1]; // Feedback

    // Choix aléatoire du mot secret
    strcpy(target, words[rand() % total]);

    printf("\n===== WORDLE (Mode Joueur) =====\n");

    // Boucle sur les tentatives
    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++)
    {
        do
        {
            printf("Tentative %d/%d : ", attempt, MAX_ATTEMPTS);
            scanf("%5s", guess); // Lecture du mot
            to_upper(guess);     // Mise en majuscule

            if (!is_valid_word(words, total, guess))
                printf("Mot invalide\n");

        } while (!is_valid_word(words, total, guess));

        compute_feedback(target, guess, feedback);
        print_colored(guess, feedback);

        if (strcmp(feedback, "GGGGG") == 0)
        {
            printf("BRAVO ! Vous avez gagne !\n");
            return;
        }
    }

    printf("Perdu :( ! Le mot etait : %s\n", target);
}

/* =====================================================
   ============  MODE SOLVEUR AUTOMATIQUE  =============
   ===================================================== */

// Mode où l'ordinateur joue tout seul
void mode_solveur(char words[MAX_WORDS][WORD_LEN + 1], int total)
{
    char possible[MAX_WORDS][WORD_LEN + 1]; // Mots possibles
    char next[MAX_WORDS][WORD_LEN + 1];     // Mots filtrés
    char target[WORD_LEN + 1];              // Mot secret
    char guess[WORD_LEN + 1];               // Proposition
    char feedback[WORD_LEN + 1];            // Feedback

    strcpy(target, words[rand() % total]);

    // Initialement tous les mots sont possibles
    for (int i = 0; i < total; i++)
        strcpy(possible[i], words[i]);

    int count = total;

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++)
    {
        strcpy(guess, possible[0]); // Stratégie simple : premier mot
        compute_feedback(target, guess, feedback);

        print_colored(guess, feedback);

        if (strcmp(feedback, "GGGGG") == 0)
        {
            printf("Solveur a trouve le mot !\n");
            return;
        }

        count = filter_words(possible, count, guess, feedback, next);
        for (int i = 0; i < count; i++)
            strcpy(possible[i], next[i]);
    }

    printf("Solveur a perdu. Mot etait : %s\n", target);
}

/* =====================================================
   ======================== MAIN =======================
   ===================================================== */

// Fonction principale du programme
int main()
{
    char words[MAX_WORDS][WORD_LEN + 1]; // Dictionnaire
    int choix;                           // Choix du menu

    srand(time(NULL)); // Initialisation du hasard

    int total = load_dictionary(words); // Chargement des mots

    printf("===== WORDLE =====\n");
    printf("1 - Joueur humain\n");
    printf("2 - Solveur automatique\n");
    printf("Choix : ");
    scanf("%d", &choix);

    if (choix == 1)
        mode_joueur(words, total);
    else if (choix == 2)
        mode_solveur(words, total);
    else
        printf("Choix invalide\n");

    return 0; // Fin du programme
}
