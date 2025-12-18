#ifndef WORDLE_H
#define WORDLE_H

/* =====================================================
   ===============  FICHIER wordle.h  ==================
   =====================================================
   Ce fichier est un fichier d'en-tête (.h).
   Il sert à :
   - définir des constantes globales
   - déclarer (annoncer) les fonctions utilisées
   dans les fichiers .c du projet Wordle.

   Grâce à ce fichier, tous les fichiers .c
   partagent les mêmes définitions.
*/

/* =====================================================
   ============  PROTECTION CONTRE DOUBLE INCLUDE ======
   =====================================================
   Les lignes #ifndef / #define / #endif empêchent
   que ce fichier soit inclus plusieurs fois
   lors de la compilation, ce qui éviterait des erreurs.
*/

/* =====================================================
   =================  CONSTANTES  ======================
   ===================================================== */

// WORD_LEN : longueur d'un mot Wordle
// Ici, les mots font exactement 5 lettres
#define WORD_LEN 5

// MAX_ATTEMPTS : nombre maximum de tentatives autorisées
// Règle officielle du jeu Wordle : 6 essais
#define MAX_ATTEMPTS 6

// MAX_WORDS : nombre maximum de mots dans le dictionnaire
// Sert à dimensionner les tableaux de mots
#define MAX_WORDS 1000

/* =====================================================
   ===========  PROTOTYPES DES FONCTIONS  ===============
   =====================================================
   Les prototypes indiquent au compilateur :
   - le nom de la fonction
   - ses paramètres
   - son type de retour
   Sans prototype, le compilateur ne saurait pas
   comment utiliser les fonctions définies dans les .c
*/

/* ================== FONCTION UTILITAIRE ================== */

// to_upper : transforme une chaîne de caractères
// passée en paramètre en MAJUSCULES
// Exemple : "apple" devient "APPLE"
void to_upper(char *s);

/* ================== DICTIONNAIRE ================== */

// load_dictionary : charge les mots depuis le fichier words.txt
// words : tableau qui va contenir les mots du dictionnaire
// Retour : nombre total de mots chargés
int load_dictionary(char words[MAX_WORDS][WORD_LEN + 1]);

// is_valid_word : vérifie si un mot est valide
// words : dictionnaire
// n     : nombre de mots dans le dictionnaire
// guess : mot proposé par le joueur ou le solveur
// Retour : 1 si le mot existe dans le dictionnaire, 0 sinon
int is_valid_word(char words[MAX_WORDS][WORD_LEN + 1], int n, char *guess);

/* ================== FEEDBACK WORDLE ================== */

// compute_feedback : calcule le feedback Wordle
// target   : mot secret à deviner
// guess    : mot proposé
// feedback : tableau contenant le résultat (G, Y ou X)
// G : lettre correcte et bien placée
// Y : lettre correcte mais mal placée
// X : lettre absente du mot
void compute_feedback(char *target, char *guess, char *feedback);

/* ================== LOGIQUE DU SOLVEUR ================== */

// match_feedback : vérifie si un mot candidat est compatible
// avec un feedback donné
// word     : mot candidat
// guess    : mot testé
// feedback : feedback obtenu
// Retour : 1 si compatible, 0 sinon
int match_feedback(char *word, char *guess, char *feedback);

// filter_words : filtre les mots possibles après un feedback
// words     : liste actuelle des mots possibles
// n         : nombre de mots possibles
// guess     : mot testé
// feedback  : feedback correspondant
// new_words : nouvelle liste de mots filtrés
// Retour : nombre de mots restants après filtrage
int filter_words(
    char words[MAX_WORDS][WORD_LEN + 1],
    int n,
    char *guess,
    char *feedback,
    char new_words[MAX_WORDS][WORD_LEN + 1]
);

/* ================== AFFICHAGE ================== */

// print_colored : affiche un mot avec des couleurs
// en fonction du feedback (vert, jaune, gris)
// guess    : mot proposé
// feedback : feedback associé
void print_colored(char *guess, char *feedback);

/* ================== MODES DE JEU ================== */

// mode_joueur : mode où un humain joue au Wordle
// words : dictionnaire
// total : nombre total de mots
void mode_joueur(char words[MAX_WORDS][WORD_LEN + 1], int total);

// mode_solveur : mode où l'ordinateur joue automatiquement
void mode_solveur(char words[MAX_WORDS][WORD_LEN + 1], int total);

// mode_solveur_interactif : mode où l'ordinateur propose
// des mots et l'utilisateur fournit le feedback manuellement
void mode_solveur_interactif(char words[MAX_WORDS][WORD_LEN + 1], int total);

#endif // WORDLE_H

