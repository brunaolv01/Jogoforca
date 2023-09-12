#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

void displayHeader() {
    printf("*******************************************\n");
    printf("******* BEM VINDO AO JOGO DA FORCA!********\n");
    printf("*******************************************\n\n\n\n");
}

void clearScreen() {
    system("clear");
}

void addWordToDatabase(){
    displayHeader();
    FILE* file;
    int i;
    file = fopen("palavrasescondidas.txt", "a");
    char word[256];
    fflush(stdin);
    printf("Qual palavra você deseja adicionar?\n\n\nDigite aqui sua resposta  ");
    scanf("%s", word);
    fprintf(file, "\n%s", word);
    fclose(file);
}

void deleteWordFromDatabase(){
    displayHeader();
    FILE* file;
    int i, lineCount = 0, deleteChoice;
    file = fopen("palavrasescondidas.txt", "r");
    char buffer[256], word[256];
    while (fgets(buffer, sizeof(buffer), file)) { 
        lineCount++;
    }
    fclose(file);
    printf("Qual palavra deseja apagar?\n\n\n");
    file = fopen("palavrasescondidas.txt", "r");
    for (i = 0; i < lineCount; i++) {
        fscanf(file, "\n%s", word);
        printf("%d) %s\n", i+1, word);
    }
    fclose(file);
    printf("\nDigite sua resposta aqui ====> ");
    scanf("%d", &deleteChoice);
    file = fopen("palavrasescondidas.txt","r");
    FILE* tempFile = fopen("palavrasescondidas.txt", "w");
    for (i = 0; i < lineCount; i++) {
        fgets(word, sizeof(word), file);
        if (i != deleteChoice - 1) {
            fprintf(tempFile, "%s", word);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("palavrasescondidas.txt");
    rename("palavrasescondidas.txt", "palavrasescondidas.txt");
}

void modifyWordInDatabase() {
    displayHeader();
    FILE* file;
    int i, lineCount = 0, modifyChoice;
    file = fopen("palavrasescondidas.txt", "r");
    char buffer[256], word[256], newWord[256];
    while (fgets(buffer, sizeof(buffer), file)) { 
        lineCount++;
    }
    fclose(file);
    printf("Qual palavra deseja alterar?\n\n\n");
    file = fopen("palavrasescondidas.txt", "r");
    for (i = 0; i < lineCount; i++) {
        fscanf(file, "\n%s", word);
        printf("%d) %s\n", i+1, word);
    }
    fclose(file);
    printf("\nDigite aqui sua resposta ====> ");
    scanf("%d", &modifyChoice);
    clearScreen();
    displayHeader();
    printf("Por qual palavra deseja substituir?\n\n\nDigite aqui  ");
    scanf("%s", newWord);
    file = fopen("palavrasescondidas.txt", "r");
    FILE* tempFile = fopen("palavrasescondidas.txt", "w");
    for (i = 0; i < lineCount; i++) {
        fgets(word, sizeof(word), file);
        if (i == modifyChoice - 1) {
            fprintf(tempFile, "%s\n", newWord);
        } else {
            fprintf(tempFile, "%s", word);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("palavrasescondidas.txt");
    rename("palavrasescondidas.txt", "palavrasescondidas.txt");
}

void playHangman() {
    FILE* file;
    int i;
    file = fopen("palavrasescondidas.txt", "r");
    int lineCount = 0, letterIndex = 0, letterCount = 0, correctGuesses = 0, errorCounter = 0, errors = 0, chosenLettersCount = 0, bodyCounter = 0, bodyCounter2 = 0, repeatedLetter = 0, guessedCorrectly = 0;
    char buffer[256], word[256], letter[256], guessedLetter, correctLetters[256], chosenLetters[26], incorrectLetters[256];
    while (fgets(buffer, sizeof(buffer), file)) { 
        lineCount++;
    }
    fclose(file);
    srand(time(NULL));
    int randomWordIndex = rand();
    int scannedWordIndex = randomWordIndex % lineCount;
    scannedWordIndex++;
    file = fopen("palavrasescondidas.txt", "r");
    for(i = 0; i < scannedWordIndex; i++){
        fscanf(file, "%s", word);
    }
    fclose(file);
    for (i = 0; word[i] != '\0'; i++) {
        if (isalpha(word[i])) {
            letterCount++;
        }
            }
    for (i = 0; word[i] != '\0'; i++) {
        if (isalpha(word[i])) {
            letter[letterIndex] = word[i];
            letterIndex++;
        }
    }
    printf("Palavra selecionada: %s\n", word);
    clearScreen();
    for (i = 0; i < letterCount; i++) {
        correctLetters[i] = '_';
    }
    for (i = 0; i < 7; i++) {
        incorrectLetters[i] = '_';
    }
    correctLetters[letterCount] = '\0';
    incorrectLetters[letterCount] = '\0';
    
    do {
        if(bodyCounter2 == 0){
            displayHeader();
            printf(" -------------\n");
            printf(" |           |\n");
            printf(" |            \n");
            printf(" |            \n");
            printf(" |            \n");
            printf(" |            \n");
            printf("---           \n");
        }
        
        fflush(stdin);
        printf("\nDigite sua resposta aqui ===>  ");
        scanf(" %c", &guessedLetter);
        
        for (i = 0; i < chosenLettersCount; i++) {
            if (tolower(guessedLetter) == chosenLetters[i]) {
                repeatedLetter = 1;
                break;
            }
        }
        
        if (!repeatedLetter) {
            chosenLetters[chosenLettersCount] = tolower(guessedLetter);
            chosenLettersCount++;
            
            for (i = 0; i < letterCount; i++) {
                if (tolower(guessedLetter) == tolower(letter[i])) {
                    correctLetters[i] = letter[i];
                    guessedCorrectly = 1;
                    correctGuesses++;
                }
            }
            
            if (!guessedCorrectly) {
                incorrectLetters[errorCounter++] = guessedLetter;
                errors++;
                bodyCounter++;
            }
        }
        
        clearScreen();
        displayHeader();
        
        // desenho
        printf(" -------------\n");
        printf(" |           |\n");
        printf(" |           %s\n", ((bodyCounter >= 1)? "O" : " "));
        printf(" |          %s%s%s\n", ((bodyCounter >= 3)? "/" : " "), ((bodyCounter >= 2)? "|" : " "), ((bodyCounter >= 4)? "\\" : " "));
        printf(" |           %s\n", ((bodyCounter >= 5)? "|" : " "));
        printf(" |           %s%s\n", ((bodyCounter >= 6)? "/" : " "), ((bodyCounter >= 7)? "\\" : " "));
        printf("---           \n\n\n");
        
        bodyCounter2++;
        printf("Letras que errou: %s\n\n", incorrectLetters);
        printf("%s\n", correctLetters);
        
    } while (errors <= 7 && correctGuesses < letterCount);
}

int main() {
    setlocale(LC_ALL, "portuguese");
    clearScreen();
    displayHeader();
    int menu;
    int choice;
    do {
        printf("1) Jogar\n2) Alterar Palavra\n3) Excluir Palavra\n4) Adicionar Palavra\n5) Sair\n\n\nDigite sua resposta aqui ====> ");
        scanf("%d", &menu);
        clearScreen();
        switch(menu) {
            case 1:
                playHangman();
                printf("Deseja voltar para o menu principal?\n1) Sim\n2) Não\n\n\nDigite sua resposta aqui ====> ");
                scanf("%d", &choice);
                if (choice == 1) {
                    main();
                }
                break;
            case 2:
                modifyWordInDatabase();
                clearScreen();
                displayHeader();
                printf("Deseja voltar para o menu principal?\n1) Sim\n2) Não\n\n\nDigite sua resposta aqui ====> ");
                scanf("%d", &choice);
                if (choice == 1) {
                    main();
                }
                break;
            case 3:
                deleteWordFromDatabase();
                clearScreen();
                displayHeader();
                printf("Deseja voltar para o menu principal?\n1) Sim\n2) Não\n\n\nDigite sua resposta aqui ====> ");
                scanf("%d", &choice);
                if (choice == 1) {
                    main();
                }
                break;
            case 4:
                addWordToDatabase();
                clearScreen();
                displayHeader();
                printf("Deseja voltar para o menu principal?\n1) Sim\n2) Não\n\n\nDigite sua resposta aqui ====> ");
                scanf("%d", &choice);
                if (choice == 1) {
                    main();
                }
                break;
        }
    } while ((choice < 1) || (choice > 5));
    
}

        

