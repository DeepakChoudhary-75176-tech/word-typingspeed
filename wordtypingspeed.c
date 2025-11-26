#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 20
#define WORD_LEN 20
#define SCORE_FILE "score.txt"

char *words[MAX_WORDS] = {
    "apple", "river", "storm", "silent", "planet",
    "bright", "keyboard", "future", "laptop", "castle",
    "dragon", "forest", "speed", "typing", "energy",
    "shadow", "winter", "summer", "travel", "rocket"
};

void saveHighScore(int score) {
    FILE *fp = fopen(SCORE_FILE, "a");
    if (fp != NULL) {
        fprintf(fp, "%d\n", score);
        fclose(fp);
    } else {
        printf("Error: Could not save score.\n");
    }
}

int loadHighScore() {
    FILE *fp = fopen(SCORE_FILE, "r");
    int highScore = 0, temp;
    if (fp != NULL) {
        while (fscanf(fp, "%d", &temp) == 1) {
            if (temp > highScore) highScore = temp;
        }
        fclose(fp);
    }
    return highScore;
}

int main() {
    srand(time(NULL));
    char input[WORD_LEN + 1]; // +1 for null terminator
    int score = 0, totalWords = 0;
    clock_t startTime = clock();
    double gameTime = 30.0; // in seconds
    int highScore = loadHighScore();

    printf("=====================================\n");
    printf("        TYPING SPEED GAME\n");
    printf("=====================================\n");
    printf("Type the words as fast as possible!\n");
    printf("You have 30 seconds. Type 'quit' to exit early.\n");
    printf("Current High Score: %d\n\n", highScore);
    printf("Press ENTER to start...");
    getchar();

    while ((clock() - startTime) / CLOCKS_PER_SEC < gameTime) {
        int index = rand() % MAX_WORDS;
        printf("\nWord: %s\n", words[index]);
        printf("Type: ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0; // Remove newline

        if (strcmp(input, "quit") == 0) {
            printf("Game exited early.\n");
            break;
        }

        if (strlen(input) == 0) {
            printf("✖ No input!\n");
        } else if (strcmp(input, words[index]) == 0) {
            score++;
            printf("✔ Correct!\n");
        } else {
            printf("✖ Wrong! (You typed: %s)\n", input);
        }
        totalWords++;
    }

    float accuracy = totalWords > 0 ? (score / (float)totalWords) * 100 : 0;

    printf("\n=====================================\n");
    printf("              RESULTS\n");
    printf("=====================================\n");
    printf("Time Over!\n");
    printf("Correct Words: %d\n", score);
    printf("Total Words: %d\n", totalWords);
    printf("Accuracy: %.2f%%\n", accuracy);

    if (score > highScore) {
        printf("New High Score!\n");
    }

    saveHighScore(score);
    printf("Your score is saved in %s\n", SCORE_FILE);
    printf("=====================================\n");

    return 0;
}
