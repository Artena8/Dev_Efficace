# Dev_Efficace
Dossier pour travailler de manière expérimentale sur la SAE - moteur de score

## Compilation

- **Compiler Lev_similarity**
    <br>Windows :
    ```
    C:\MinGW\bin> .\gcc.exe "Modules Dones\lev_similarity.c" "Modules Dones\levenstein.c" -o "Modules Dones\lev_similarity.exe"
    ```
    Linux :
    ```
    gcc "./Modules Dones/lev_similarity.c" "./Modules Dones/levenstein.c" -o "./Modules Dones/lev_similarity"
    ```
- 

## Creer le dictionnaire de l'arbre lexicographique (build_index_lex)
gcc "./sourcefiles/build_index_lex.c" "./sourcefiles/functions.c" -I"./headers" -lm -o "./exec_WINDOWS/build_index_lex"

./gcc.exe "U:\GITHUB\Dev_Efficace/sourcefiles/build_index_lex.c" "U:\GITHUB\Dev_Efficace/sourcefiles/functions.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace/exec_WINDOWS/build_index_lex"

## Rechercher si un mot existe dans le dictionnaire (dictionnary_lookup)
gcc "./sourcefiles/dictionary_lookup.c" "./sourcefiles/functions.c" -I"./headers" -lm -o "./exec_WINDOWS/dictionary_lookup"

./gcc.exe "U:\GITHUB\Dev_Efficace/sourcefiles/dictionary_lookup.c" "U:\GITHUB\Dev_Efficace/sourcefiles/functions.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace/exec_WINDOWS/dictionary_lookup"

## Calculer la similarite orthographique (lev_similarity)
.\gcc.exe "U:\GITHUB\Dev_Efficace\sourcefiles\lev_similarity.c" "U:\GITHUB\Dev_Efficace/sourcefiles/functions.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace\exec_WINDOWS\lev_similarity.exe"

## Calculer la similarite semantique (sem_similarity)
./gcc.exe "U:\GITHUB\Dev_Efficace/sourcefiles/sem_similarity.c" "U:\GITHUB\Dev_Efficace/sourcefiles/functions.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace/exec_WINDOWS/sem_similarity"

## Creer le fichier de partie (new_game)
./gcc.exe "U:\GITHUB\Dev_Efficace/sourcefiles/new_game.c" "U:\GITHUB\Dev_Efficace/sourcefiles/functions.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace/exec_WINDOWS/new_game"

## Ajouter un mot à la partie (add_word)
./gcc.exe "U:\GITHUB\Dev_Efficace/sourcefiles/add_word.c" "U:\GITHUB\Dev_Efficace/sourcefiles/functions.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace/exec_WINDOWS/add_word"