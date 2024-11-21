# Projet : Compilateur pour un langage simple

## Présentation

Ce projet est un compilateur pour un langage de programmation simple. Il permet d'analyser du code source en vérifiant les erreurs lexicales, syntaxiques et sémantiques. Le but est d'apprendre à créer un compilateur de manière simple et éducative.

## Fonctionnalités

- **Analyse Lexicale** : Identification des tokens comme les identifiants, les constantes, les opérateurs, etc.
- **Analyse Syntaxique** : Vérification que la structure du programme respecte la grammaire du langage.
- **Analyse Sémantique** : Vérification des erreurs comme les variables non déclarées.

## Comment ça marche

1. **Entrée** : Le programme prend un fichier source en entrée.
2. **Analyse Lexicale** : Le code source est transformé en tokens (mots-clés, identifiants, nombres, etc.).
3. **Analyse Syntaxique** : Le programme vérifie que la structure des tokens est correcte.
4. **Analyse Sémantique** : Le programme vérifie les erreurs liées aux variables et à la logique.
5. **Table des symboles** : Le programme crée une table avec les variables, constantes, et le nom du programme.

## Utilisation

### 1. Cloner le dépôt
```bash
git clone https://github.com/votreutilisateur/ProjetCompilaENSIAS.git
cd ProjetCompilaENSIAS
