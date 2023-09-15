#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define MAX_WORD_LENGTH 256
#define MAX_GUESSES 7

void forca(erros){
	
    printf(" -------------\n");
    printf(" |           |\n");
    printf(" |           %s\n", ((erros >= 1)? "O" : " "));
    printf(" |          %s%s%s\n", ((erros >= 3)? "/" : " "), ((erros >= 2)? "|" : " "), ((erros >= 4)? "\\" : " "));
    printf(" |           %s\n", ((erros >= 5)? "|" : " "));
    printf(" |           %s%s\n", ((erros >= 6)? "/" : " "), ((erros >= 7)? "\\" : " "));
    printf("---           \n\n\n");
	
}

void displayHeader() {
    printf("*******************************************\n");
    printf("******* BEM VINDO AO JOGO DA FORCA! ******\n");
    printf("*******************************************\n\n\n\n");
}

void addWordToDatabase() {
    displayHeader();
    FILE* file;
    char word[MAX_WORD_LENGTH];
    
    printf("Qual palavra você deseja adicionar?\n\n\nDigite aqui sua resposta: ");
    scanf("%s", word);
    
    file = fopen("palavrasescondidas.txt", "a");
    
	if (file == NULL) {
    	printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    fprintf(file, "%s\n", word);
    fclose(file);
}

void deleteWordFromDatabase() {
    displayHeader();
    FILE* file;
    int lineCount = 0, deleteChoice;
    
    file = fopen("palavrasescondidas.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    char word[MAX_WORD_LENGTH];
    while (fgets(word, sizeof(word), file)) { 
        lineCount++;
    }
    fclose(file);
    
    if (lineCount == 0) {
        printf("Banco de palavras vazio.\n");
        return;
    }
    
    printf("Qual palavra deseja apagar?\n\n\n");
    file = fopen("palavrasescondidas.txt", "r");
    
    int i;
    
    for (i = 0; i < lineCount; i++) {
        fscanf(file, "%s", word);
        printf("%d) %s\n", i + 1, word);
    }
    fclose(file);
    
    printf("\nDigite sua resposta aqui: ");
    scanf("%d", &deleteChoice);
    
    if (deleteChoice < 1 || deleteChoice > lineCount) {
        printf("Escolha inválida.\n");
        return;
    }
    
    file = fopen("palavrasescondidas.txt", "r");
    FILE* tempFile = fopen("temp.txt", "w");
    
    for (i = 0; i < lineCount; i++) {
        fgets(word, sizeof(word), file);
        if (i != deleteChoice - 1) {
            fprintf(tempFile, "%s", word);
        }
    }
    
    fclose(file);
    fclose(tempFile);
    remove("palavrasescondidas.txt");
    rename("temp.txt", "palavrasescondidas.txt");
}

void modifyWordInDatabase() {
    displayHeader();
    FILE* file;
    int lineCount = 0, modifyChoice;
    int i;
    
    file = fopen("palavrasescondidas.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    char word[MAX_WORD_LENGTH], newWord[MAX_WORD_LENGTH];
    
    while (fgets(word, sizeof(word), file)) { 
        lineCount++;
    }
    fclose(file);
    
    if (lineCount == 0) {
        printf("Banco de palavras vazio.\n");
        return;
    }
    
    printf("Qual palavra deseja alterar?\n\n\n");
    file = fopen("palavrasescondidas.txt", "r");
    
    for (i = 0; i < lineCount; i++) {
        fscanf(file, "%s", word);
        printf("%d) %s\n", i + 1, word);
    }
    fclose(file);
    
    printf("\nDigite aqui sua resposta: ");
    scanf("%d", &modifyChoice);
    
    if (modifyChoice < 1 || modifyChoice > lineCount) {
        printf("Escolha inválida.\n");
        return;
    }
    
    system("cls");
    displayHeader();
    
    printf("Por qual palavra deseja substituir?\n\n\nDigite aqui: ");
    scanf("%s", newWord);
    
    file = fopen("palavrasescondidas.txt", "r");
    FILE* tempFile = fopen("temp.txt", "w");
    
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
    rename("temp.txt", "palavrasescondidas.txt");
}

int chooseRandomWord(char *word) {
    FILE* file;
    int lineCount = 0;
    int i;
    
    file = fopen("palavrasescondidas.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    
    char line[MAX_WORD_LENGTH];
    
    while (fgets(line, sizeof(line), file)) { 
        lineCount++;
    }
    
    if (lineCount == 0) {
        printf("Banco de palavras vazio.\n");
        fclose(file);
        return 0;
    }
    
    srand(time(NULL));
    int randomLineNumber = rand() % lineCount + 1;
    
    fseek(file, 0, SEEK_SET);
    
    for (i = 0; i < randomLineNumber; i++) {
        fgets(line, sizeof(line), file);
    }
    

    strtok(line, "\n");
    
    fclose(file);
    
    strcpy(word, line);
    
    return 1;
}

void playHangman() {
    char wordToGuess[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];
    int numGuesses = 0;
    int wordLength;
    int i;
    int letterGuessed = 0;
    char guess;
    int erros = 0;
    
    if (!chooseRandomWord(wordToGuess)) {
        printf("Não há palavras no banco de palavras. Adicione palavras para jogar.\n");
        return;
    }
    
    wordLength = strlen(wordToGuess);
    
    for (i = 0; i < wordLength; i++) {
        guessedWord[i] = '_';
    }
    
    guessedWord[wordLength] = '\0';
    
    while (1) {
        system("cls");
        displayHeader();
        forca(erros);
        
        printf("Palavra a ser adivinhada: %s\n", guessedWord);
        printf("Tentativas restantes:");
        printf("%d/%d\n", numGuesses, MAX_GUESSES);
        
        if (numGuesses == MAX_GUESSES) {
            printf("Você excedeu o número máximo de tentativas. A palavra era: %s\n", wordToGuess);
            break;
        }
        
        printf("Adivinhe uma letra: ");
        scanf(" %c", &guess);
        
        for (i = 0; i < wordLength; i++) {
            if (guess == guessedWord[i]) {
                printf("Você já adivinhou essa letra.\n");
                letterGuessed = 1;
                
                break;
            }
        }
        
        if (!letterGuessed) {
            letterGuessed = 0;
            for (i = 0; i < wordLength; i++) {
                if (guess == wordToGuess[i]) {
                    guessedWord[i] = guess;
                    letterGuessed = 1;
                }
            }
            
            if (!strcmp(wordToGuess, guessedWord)) {
                system("cls");
                displayHeader();
                printf("Parabéns! Você adivinhou a palavra: %s\n", wordToGuess);
                break;
            }
            if (!letterGuessed) {
                printf("Letra incorreta. Tente novamente.\n");
                numGuesses++;
                erros++;               
            }
        } else {
            letterGuessed = 0;
        }
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");
    system("cls");
    displayHeader();
    int menuChoice;
    
    do {
        printf("1) Jogar\n2) Alterar Palavra\n3) Excluir Palavra\n4) Adicionar Palavra\n5) Sair\n\n\nDigite sua resposta aqui: ");
        scanf("%d", &menuChoice);
        system("cls");
        
        switch (menuChoice) {
            case 1:
                playHangman();
                break;
            case 2:
                modifyWordInDatabase();
                break;
            case 3:
                deleteWordFromDatabase();
                break;
            case 4:
                addWordToDatabase();
                break;
            case 5:
                printf("Obrigado por jogar! Adeus.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (menuChoice != 5);
}
        

