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

gcc "./sourcefiles/build_index_lex.c" "./sourcefiles/CSTrees.c" -I"./headers" -lm -o "./sourcefiles/build_index_lex"

gcc "./sourcefiles/dictionary_lookup.c" "./sourcefiles/CSTrees.c" -I"./headers" -lm -o "./sourcefiles/dictionary_lookup"


./gcc.exe "U:\GITHUB\Dev_Efficace/RefsCours/dictionary_lookup.c" "U:\GITHUB\Dev_Efficace/RefsCours/CSTrees.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace/RefsCours/dictionary_lookup"

./gcc.exe "U:\GITHUB\Dev_Efficace/RefsCours/build_index_lex.c" "U:\GITHUB\Dev_Efficace/RefsCours/CSTrees.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace/RefsCours/build_index_lex"

.\gcc.exe "U:\GITHUB\Dev_Efficace\ModulesDones\lev_similarity.c" "U:\GITHUB\Dev_Efficace\ModulesDones\levenstein.c" "U:\GITHUB\Dev_Efficace/RefsCours/CSTrees.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace\ModulesDones\lev_similarity.exe"

./gcc.exe "U:\GITHUB\Dev_Efficace/RefsCours/sem_similarity.c" "U:\GITHUB\Dev_Efficace/RefsCours/CSTrees.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace/RefsCours/sem_similarity"

./gcc.exe "U:\GITHUB\Dev_Efficace/new_game.c" "U:\GITHUB\Dev_Efficace/RefsCours/CSTrees.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace/new_game"

./gcc.exe "U:\GITHUB\Dev_Efficace/add_word.c" "U:\GITHUB\Dev_Efficace/RefsCours/CSTrees.c" -I"./headers" -lm -o "U:\GITHUB\Dev_Efficace/add_word"