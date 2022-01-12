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
* <file with helper functions>
*
*/


#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string>
using namespace std;

void Round(int numberOfLetters, int& shuffles, int& roundCounter, int& score)
{
    srand(time(NULL));
    ifstream Myfile;
    string line;
    cout << "Round " << roundCounter << ":" << endl;
    cout << "Available letters:";
    char* roundLetters = new char[numberOfLetters];
    for (int i = 0; i < numberOfLetters; i++)
    {
        roundLetters[i] = 97 + (rand() % 26);
    }
    for (int i = 0; i < numberOfLetters; i++)
    {
        cout << " " << roundLetters[i];
    }
    cout << endl;
    cout << "Type a word with available letters or type 0 to use a shuffle: ";
    bool thereIsInvalidWord;
    bool existsInDictionary;
    for (int i = 0; i < 3; i++)
    {
        existsInDictionary = 0;
        thereIsInvalidWord = 0;
        string word;
        cin >> word;
        if (word == "0" && shuffles != 0)
        {
            shuffles -= 1;
            cout << "Remaining shuffles: " << shuffles << endl;
            roundCounter--;
            break;
        }
        else if (word == "0" && shuffles == 0)
        {
            do {
                cout << "No shuffles remaining. Type a word. ";
                word.clear();
                cin >> word;
            } while (word == "0");
        }
        Myfile.open("words.txt");

        while (getline(Myfile, line))
        {
            if (line == word)
                existsInDictionary = 1;
        }
        Myfile.close();
        if (existsInDictionary != 1)
        {
            thereIsInvalidWord = 1;
        }
            for (size_t z = 0; z < word.length(); z++)
            {
                for (int j = 0; j < numberOfLetters; j++)
                {
                    if (word[z] == roundLetters[j])
                    {
                        roundLetters[j] = 0;
                        break;
                    }
                    else if (j == numberOfLetters - 1)
                    {
                        thereIsInvalidWord = 1;
                        break;
                    }
                }

                if (thereIsInvalidWord)
                {
                    if (i < 2)
                    {
                        cout << "Invalid word. Use a shuffle or try again: ";
                    }
                    break;
                }
            }
            if (i == 2 && thereIsInvalidWord)
            {
                cout << "Invalid word. No remaining tries." << endl;
            }
            else if (!thereIsInvalidWord)
            {
                score += word.length();
                cout << "Your points so far are " << score << endl;
                cout << "Next round:" << endl;
                break;
            }  
    }
    delete[] roundLetters;
}
void NewGame(int rounds, int numberOfLetters, int shuffles)
{
    system("CLS");
    int score = 0;
    for (int roundCounter = 1; roundCounter <= rounds; roundCounter++)
    {
        Round(numberOfLetters, shuffles, roundCounter, score);
    }
    cout << "Your total points are: " << score << endl;
    cout << "Return to main menu?" << endl;
    while (!(GetKeyState('A') & 0x8000))
        continue;
    return;
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
            break;
        }
        case 2:
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
            break;
        }
        case 3:
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
    string newWord;
    ofstream outfile;
    outfile.open("words.txt", ios::app);
    cout << "Write a word to add to the dictionary: ";
    cin >> newWord;
    outfile << "\n" << newWord;
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
