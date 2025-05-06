//Youssef Elsanhawy
//Project 10 - wordup.c
//April 29, 2025

#include <stdio.h>
#include <stdbool.h>

#define WORD_LENGTH 5
#define MAX_GUESSES 6

void compareGuess(char word[], char guess[], char result[], char pointedTo[]);
void displayGuesses(char comparedAnswers[][WORD_LENGTH + 1], char pointedTo[][WORD_LENGTH + 1], int count);
void lowerCase(char guess[]);
void getGuess(char guess[], int guessCount);
void readWord(char word[]);
void upperCase(char word[]);
bool checkGuess(char guess[], char word[]);
bool okGuess(char guess[]);
bool okLength(char guess[]);
bool letter(char c);



int main() {
char word[WORD_LENGTH + 1];
readWord(word);
char userWords[MAX_GUESSES][WORD_LENGTH + 1];
char comparedAnswers[MAX_GUESSES][WORD_LENGTH + 1];
char pointedTo[MAX_GUESSES][WORD_LENGTH + 1];
int guessCount = 0;
bool correct = false;

while (guessCount < MAX_GUESSES && !correct) {
char guess[WORD_LENGTH + 1];
getGuess(guess, guessCount);
lowerCase(guess);

for (int i = 0; i < WORD_LENGTH + 1; i++) {
userWords[guessCount][i] = guess[i];
}
if (okLength(guess) && okGuess(guess))
compareGuess(word, guess, comparedAnswers[guessCount], pointedTo[guessCount]);
if (checkGuess(guess, word)) {
correct = true;
upperCase(word);
if (guessCount == 0)
printf("               %s\n       You won in 1 guess! \n               GOATED!\n", word);
if (guessCount == 1)
printf("               %s\n       You won in 2 guesses! \n               AMAZING!\n", word);
if (guessCount == 2)
printf("               %s\n       You won in 3 guesses! \n               AMAZING!\n", word);
if (guessCount == 3)
printf("               %s\n       You won in 4 guesses! \n               Nice!\n", word);
if (guessCount == 4)
printf("               %s\n       You won in 5 guesses! \n               Nice!\n", word);
if (guessCount == 5)
printf("               %s\n       You won in 6 guesses!\n", word);
break;
}
displayGuesses(comparedAnswers, pointedTo, guessCount + 1);
guessCount++;
}
if (!correct) {
printf("You lost, better luck next time!\n");
}
return 0;
}
void readWord(char word[]) {
FILE *f = fopen("word.txt", "r");
if (f == NULL) {
printf("Error, the file word.txt could not open.\n");
return;
}
for (int i = 0; i < WORD_LENGTH; i++) {
word[i] = fgetc(f);
}
word[WORD_LENGTH] = '\0';
fclose(f);
}
bool letter(char c) {
return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
bool okGuess(char guess[]) {
int length = 0;
while (guess[length] != '\0') {
if (!letter(guess[length])) return false;
length++;
}
return true;
}
bool okLength(char guess[]) {
int length = 0;
while (guess[length] != '\0') {
length++;
}
return length == WORD_LENGTH;
}
void lowerCase(char guess[]) {
for (int i = 0; i < WORD_LENGTH; i++) {
if (guess[i] >= 'A' && guess[i] <= 'Z') {
guess[i] += 'a' - 'A';
}
}
}
void upperCase(char guess[]) {
for (int i = 0; i < WORD_LENGTH; i++) {
if (guess[i] >= 'a' && guess[i] <= 'z') {
guess[i] -= 'a' - 'A';
}
}
}
void getGuess(char guess[], int guessCount) {
char temp[100];
int valid = 0;
bool flag = 0;
do {
if (guessCount != 5 && flag == 0) {
printf("GUESS %d! Enter your guess: ", guessCount + 1);
}
else if (flag == 1) {
} 
else {
printf("FINAL GUESS: ");
}
scanf("%99s", temp);
int ch;
while ((ch = getchar()) != '\n');
int length = 0;
while (temp[length] != '\0') {
length++;
}
if (!okGuess(temp) && length != WORD_LENGTH) {
printf("Your guess must be 5 letters long. Your guess must contain only letters.\n");
printf("Please try again: ");
flag = 1;
} else if (!okGuess(temp)) {
printf("Your guess must contain only letters.\n");
printf("Please try again: ");
flag = 1;
} else if (length != WORD_LENGTH) {
printf("Your guess must be 5 letters long.\n");
printf("Please try again: ");
flag = 1;
} else {
printf("================================\n");
valid = 1;
}
} while (!valid);
for (int i = 0; i < WORD_LENGTH; i++) {
guess[i] = temp[i];
}
guess[WORD_LENGTH] = '\0';
}
bool checkGuess(char guess[], char word[]) {
for (int i = 0; i < WORD_LENGTH; i++) {
if (guess[i] != word[i]) return false;
}
return true;
}
void compareGuess(char word[], char guess[], char result[], char pointedTo[]) {
bool used[WORD_LENGTH] = {false};
for (int i = 0; i < WORD_LENGTH; i++) {
if (guess[i] == word[i]) {
result[i] = guess[i] - ('a' - 'A');
pointedTo[i] = ' ';
used[i] = true;
} else {
result[i] = guess[i];
pointedTo[i] = ' ';
}
}
for (int i = 0; i < WORD_LENGTH; i++) {
if (result[i] == guess[i]) { 
for (int j = 0; j < WORD_LENGTH; j++) {
if (!used[j] && guess[i] == word[j]) {
pointedTo[i] = '^';
used[j] = true;
break;
}
}
}
}
result[WORD_LENGTH] = '\0';
pointedTo[WORD_LENGTH] = '\0';
}
void displayGuesses(char comparedAnswers[][WORD_LENGTH + 1], char pointedTo[][WORD_LENGTH + 1], int count) {
for (int i = 0; i < count; i++) {
printf("%s\n", comparedAnswers[i]);
printf("%s\n", pointedTo[i]);
}
}
