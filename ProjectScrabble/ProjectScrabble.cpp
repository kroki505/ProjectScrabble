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
using namespace std;

void MainMenu()
{
    cout << "1. Start game" << endl;
    cout << "2. Options" << endl;
    cout << "3. Add new word" << endl;
    cout << "4. Exit" << endl;

    int number;
    cout << "\nChoose action: ";
    
    do
    {
        cin >> number;
        switch (number)
        {
        case 1:
        {

            break;
        }
        case 2:
        {

            break;
        }
        case 3:
        {

            break;
        }
        case 4:
        {

            break;
        }
        default:
            cout << "Invalid action! Choose again. ";
        } 
    } while (number < 1 || number > 4);
    
}

int main()
{
    MainMenu();
}
