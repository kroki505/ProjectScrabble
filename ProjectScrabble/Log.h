#pragma once

void Round(int numberOfLetters, int& shuffles, int& roundCounter, int& score, int& rounds);

void NewGame(int rounds, int numberOfLetters, int shuffles);

void ChangeNumberOfLetters(int& numberOfLetters);

void ChangeNumberOfRounds(int& rounds);

void ChangeNumberOfShuffles(int& shuffles);

void Settings(int& rounds, int& numberOfLetters, int& shuffles);

void AddWordToDictionary();

void MainMenu(int Rounds, int NumberOfLetters, int Shuffles);