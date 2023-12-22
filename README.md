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

/RefsCours/build_index_lex ./word2vec/bin/fasttext-fr.bin ./RefsCours/output/dic.lex

gcc "./RefsCours/build_index_lex.c" "./RefsCours/CSTrees.c" -I"./headers" -lm -o "./RefsCours/build_index_lex"


gcc "./RefsCours/dictionary_lookup.c" "./RefsCours/CSTrees.c" -I"./headers" -lm -o "./RefsCours/dictionary_lookup"