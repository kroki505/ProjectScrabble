/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Mihail Bukov
* @idnumber 0MI0600111
* @compiler VC
*
* <main file>
*
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string>
#include "Log.h"
using namespace std;

bool WordExistsInDictionary(string& word)
{
    ifstream Myfile;
    string line;
    Myfile.open("words.txt");

    while (getline(Myfile, line)) // Checks to see if the written word exists in the dictionary
    {
        if (line == word)
        {
            Myfile.close();
            return 1;
        }
    }
    Myfile.close();
    return 0;
}

bool WordIsCorrect(int wordLength, int numberOfLetters, string word, char roundLetters[], int numberOfTriesLeft)
{
    if (!WordExistsInDictionary(word))
    {
        if (numberOfTriesLeft < 2)
            cout << "Invalid word. Use a shuffle or try again: ";
        word.clear();
        return 0;
    }
        
    int thereIsInvalidWord = 0;
    for (int z = 0; z < wordLength; z++)
    {
        for (int j = 0; j < numberOfLetters; j++)
        {
            if (word[z] == roundLetters[j]) // Each letter that has been used is removed from the initial available letters
            {
                roundLetters[j] = 0;
                break;
            }
            else if (j == numberOfLetters - 1) // If it reaches the end and it hasn't found a letter triggers a flag
            {
                word.clear();
                if (numberOfTriesLeft < 2)
                    cout << "Invalid word. Use a shuffle or try again: ";

                return 0;
            }
        }
    }
    return 1;
}

bool Shuffle(int &shuffles, int& roundCounter, string& word)
{
    if (word == "0" && shuffles != 0) // If shuffles are available reduce the roundCounter and start a new round with new letters
    {
        shuffles -= 1;
        cout << "Remaining shuffles: " << shuffles << endl;
        roundCounter--;
        return 1;
    }
    else if (word == "0" && shuffles == 0)
    {
        do {
            cout << "No shuffles remaining. Type a word. ";
            word.clear();
            cin >> word;
        } while (word == "0");
    }
    return 0;
}

void Round(int numberOfLetters, int& shuffles, int& roundCounter, int& score, int &rounds)
{
    srand((unsigned int)time(NULL));

    cout << "Round " << roundCounter << ":" << endl;
    cout << "Available letters:";

    char* roundLetters = new char[numberOfLetters];
    for (int i = 0; i < numberOfLetters; i++) // Creates only numbers whose ascii table values are small letters
    {
        roundLetters[i] = 97 + (rand() % 26);
        cout << " " << roundLetters[i];
    }

    cout << endl;
    cout << "Type a word with available letters or type 0 to use a shuffle: ";
    string word;
    int wordLength;

    for (int numberOfTries = 0; numberOfTries < 3; numberOfTries++)
    {
        cin >> word;
        wordLength = word.length();

        if (Shuffle(shuffles, roundCounter, word))
            break;

        bool wordIsCorrect = WordIsCorrect(wordLength, numberOfLetters, word, roundLetters, numberOfTries);
        if (wordIsCorrect) // If a valid word has been written update score and go to next round
        {
            score += wordLength;
            if (roundCounter == rounds)
                break;
            cout << "Your points so far are " << score << endl;
            cout << "Next round:" << endl;
            break;
        }
        else if (numberOfTries == 2 && !wordIsCorrect) // If an invalid word has been written 3 times force skip to next round
        {
            cout << "Invalid word. No remaining tries." << endl;
            if (roundCounter == rounds)
                break;
            cout << "Your points so far are " << score << endl;
            cout << "Next round:" << endl;
        }
         
    }

    delete[] roundLetters;
    return;
}

void NewGame(int rounds, int numberOfLetters, int shuffles)
{
    system("CLS");
    int score = 0;

    for (int roundCounter = 1; roundCounter <= rounds; roundCounter++)
    {
        Round(numberOfLetters, shuffles, roundCounter, score, rounds);
    }

    cout << "Your total points are: " << score << endl;
    cout << "Return to main menu?" << endl;
    system("Pause");
    return;
}

void ChangeNumberOfLetters(int& numberOfLetters)
{
    system("CLS");
    cout << "1. Change number of letters per round to 10" << endl;
    cout << "2. Change number of letters per round to 15" << endl;
    cout << "3. Change number of letters per round to 20" << endl;

    int actionChangeLetters;
    cout << "Choose desired option. ";

    do {
        cin >> actionChangeLetters;
        switch (actionChangeLetters)
        {
        case 1:
        {
            numberOfLetters = 10;
            break;
        }
        case 2:
        {
            numberOfLetters = 15;
            break;
        }
        case 3:
        {
            numberOfLetters = 20;
            break;
        }
        default:
            cout << "Invalid action! Choose again. ";
        }
    } while (actionChangeLetters < 1 || actionChangeLetters > 3);
}

void ChangeNumberOfRounds(int& rounds)
{
    system("CLS");
    cout << "1. Change number of rounds to 5." << endl;
    cout << "2. Change number of rounds to 7." << endl;
    cout << "3. Change number of rounds to 10." << endl;

    int actionChangeRounds;
    cout << "Choose desired option. ";

    do {
        cin >> actionChangeRounds;
        switch (actionChangeRounds)
        {
        case 1:
        {
            rounds = 5;
            break;
        }
        case 2:
        {
            rounds = 7;
            break;
        }
        case 3:
        {
            rounds = 10;
            break;
        }
        default:
            cout << "Invalid action! Choose again. ";
        }
    } while (actionChangeRounds < 1 || actionChangeRounds > 3);
}

void ChangeNumberOfShuffles(int& shuffles)
{
    system("CLS");
    cout << "1. Change number of shuffles to 1." << endl;
    cout << "2. Change number of shuffles to 2." << endl;
    cout << "3. Change number of shuffles to 3." << endl;

    int actionChangeShuffles;
    cout << "Choose desired option. ";

    do {
        cin >> actionChangeShuffles;
        switch (actionChangeShuffles)
        {
        case 1:
        {
            shuffles = 1;
            break;
        }
        case 2:
        {
            shuffles = 2;
            break;
        }
        case 3:
        {
            shuffles = 3;
            break;
        }
        default:
            cout << "Invalid action! Choose again. ";
        }
    } while (actionChangeShuffles < 1 || actionChangeShuffles > 3);
}

void Settings(int &rounds, int &numberOfLetters, int &shuffles)
{
    system("CLS");
    cout << "1. Change number of letters per round." << endl;
    cout << "2. Change number of rounds." << endl;
    cout << "3. Change number of shuffles." << endl;

    int actionSettings;
    
    do {
        cin >> actionSettings;
        switch (actionSettings)
        {
        case 1:
        {
            ChangeNumberOfLetters(numberOfLetters);
            break;
        }
        case 2:
        {
            ChangeNumberOfRounds(rounds);
            break;
        }
        case 3:
        {
            ChangeNumberOfShuffles(shuffles);
            break;
        }
        default:
            cout << "Invalid action! Choose again. ";
        }
    } while (actionSettings < 1 || actionSettings > 3);
}

void AddWordToDictionary()
{
    system("CLS");
    cout << "Write a word to add to the dictionary: ";
    string newWord;
    cin >> newWord;
    if (WordExistsInDictionary(newWord))
    {
        cout << "Word already exists in the dictionary." << endl;
        system("Pause");
        return;
    }
    ofstream outfile;
    outfile.open("words.txt", ios::app);
    outfile << "\n" << newWord;
    outfile.close();
    cout << newWord << " is added to the dictionary." << endl;
    system("Pause");
    return;
}

void MainMenu(int Rounds, int NumberOfLetters, int Shuffles)
{
    system("CLS");
    cout << "1. Start game" << endl;
    cout << "2. Options" << endl;
    cout << "3. Add new word" << endl;
    cout << "4. Exit" << endl;

    int actionMainMenu;
    cout << "\nChoose action: ";
    
    do
    {
        cin >> actionMainMenu;
        switch (actionMainMenu)
        {
        case 1:
        {
            NewGame(Rounds, NumberOfLetters, Shuffles);
            MainMenu(Rounds, NumberOfLetters, Shuffles);
            break;
        }
        case 2:
        {
            Settings(Rounds, NumberOfLetters, Shuffles);
            MainMenu(Rounds, NumberOfLetters, Shuffles);
            break;
        }
        case 3:
        {
            AddWordToDictionary();
            MainMenu(Rounds, NumberOfLetters, Shuffles);
            break;
        }
        case 4:
        {
            return;
        }
        default:
            cout << "Invalid action! Choose again. ";
        } 
    } while (actionMainMenu < 1 || actionMainMenu > 4); 
}

int main()
{
    int defaultRounds = 5;
    int defaultNumberOfLetters = 10;
    int defaultShuffles = 2;
    MainMenu(defaultRounds, defaultNumberOfLetters, defaultShuffles);
    return 0;
}