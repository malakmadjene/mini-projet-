# 🟩 Wordle Solver en C
![jeu](https://github.com/user-attachments/assets/d62c7512-83c5-4b44-bac6-88f734e6b6f8)


## 📌 Description du projet

Ce projet est une implémentation du jeu **Wordle** en langage **C**, réalisée dans le cadre du module **Algorithmes & Structures de Données (ALGO3)**.

Le programme permet :

* de jouer au jeu Wordle en mode **joueur humain**
* de laisser un **solveur automatique** deviner le mot
* d’utiliser un **solveur interactif**, où l’utilisateur fournit le feedback

Le jeu respecte les règles officielles de Wordle :

* mots de **5 lettres**
* **6 tentatives maximum**
* feedback sous forme de couleurs (vert, jaune, gris)

---

## 🎯 Objectifs pédagogiques

* Manipulation des **tableaux** et **chaînes de caractères** en C
* Utilisation des **fichiers** (`words.txt`)
* Mise en place d’un **algorithme de filtrage**
* Conception d’un programme structuré avec `.c` et `.h`
* Compréhension de la logique d’un **solveur automatique**

---

## 🗂️ Structure du projet

```
/project
│── main.c                 // Programme principal
│── wordle.c               // Implémentation des fonctions du jeu
│── wordle.h               // Prototypes et constantes
│── solver.c (optionnel)   // Logique du solveur (si séparé)
│── words.txt              // Dictionnaire de mots (5 lettres)
│── README.md              // Documentation du projet
```

---

## ▶️ Compilation et exécution

### 🔧 Compilation 


```bash
gcc main.c wordle.c -o wordle
```

### ▶️ Exécution

```bash
./wordle
```

---

## 🕹️ Modes de jeu disponibles

Au lancement du programme, un menu s’affiche :

```
1 - Joueur humain
2 - Solveur automatique
3 - Solveur interactif
```

### 1️⃣ Mode joueur humain

* L’utilisateur entre des mots
* Le programme vérifie leur validité
* Le feedback est affiché en couleurs

### 2️⃣ Mode solveur automatique

* L’ordinateur choisit automatiquement les mots
* Il filtre les possibilités selon le feedback
* Il tente de trouver le mot en ≤ 6 essais

### 3️⃣ Mode solveur interactif

* L’ordinateur propose un mot
* L’utilisateur fournit le feedback (G / Y / X)
* Utile pour résoudre un Wordle externe

---

## 🎨 Signification du feedback

* 🟩 **G (Green)** : lettre correcte et bien placée
* 🟨 **Y (Yellow)** : lettre présente mais mal placée
* ⬜ **X (Gray)** : lettre absente du mot

---

## 🧠 Stratégie du solveur

Le solveur utilise une stratégie simple mais efficace :

1. Il commence avec la liste complète des mots possibles
2. À chaque tentative, il choisit un mot candidat
3. Il compare le feedback obtenu avec tous les mots restants
4. Il élimine les mots incompatibles
5. Il répète jusqu’à trouver le mot ou atteindre 6 essais

---



## 👨‍🎓 Auteur

MADJENE malak 
MAHDI Melina 
KEDDAR Acyl 

## ✅ Remarques

* Le code est entièrement commenté pour faciliter la compréhension
* Le projet est conçu à des fins pédagogiques
* Améliorations possibles :

  * meilleure stratégie de choix des mots
  * statistiques de performance du solveur

---
##   capture d ecran d execution   


### mode joueur 
<img width="890" height="907" alt="Capture d&#39;écran 2025-12-18 220520" src="https://github.com/user-attachments/assets/16226159-6637-4794-9cdf-1ce0a29be6be" />



### mode solveur automatique 
<img width="1012" height="666" alt="Capture d&#39;écran 2025-12-18 222340" src="https://github.com/user-attachments/assets/d5824c6d-2e78-4998-ad11-f8a9c5e9f746" />



### mode solveur interactif 
<img width="1104" height="523" alt="Capture d&#39;écran 2025-12-18 220910" src="https://github.com/user-attachments/assets/6812fcc5-229f-4e13-b12f-fee976d70be9" />


🧠 *Projet Wordle Solver – Langage C*

