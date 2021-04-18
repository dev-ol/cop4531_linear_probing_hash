
/* ================================================================
PROGRAM Campaign Contributions

        AUTHOR: <Antwon Bryce>
        FSU MAIL NAME: <acb19d>
        RECITATION SECTION NUMBER: <03>
        RECITATION INSTRUCTOR NAME: <Samuel Ostlund>
        Course Information: <COP 3014>
        Project Number: <6>
        Due Date: <Wednesday 7, 2021>
        PLATFORM: Windows OS / CLion IDE

SUMMARY

This program will be used to simulate the dice rolling game known as Craps.
Within this program, the game is played by two players following a set of rules.

INPUT

- The given slush.txt and names.txt text files.
- There is no input from the user for this program.

OUTPUT

Prints out each contributor, their contribution amount and the total contribution by each
contributor.

Bad Checking


ASSUMPTIONS

- Assume that each name starts at the beginning of a new line.
- Assume that there are no blank lines in the file.
- Assume that the only bad checking that is done, is to check for negative contributions.

 */
/* ================================================================ */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Contributors
{
    string name;
    double amount;
};

const int maxContributors = 25;

//add contributors' contributions
void AddContributions(string key, double amount, Contributors contributors[], int size);

//read the file with the contributions
void ReadSlushFile(Contributors contributors[], int size);

//read the file with the names of contributors
void ReadNameFile(Contributors contributors[], ifstream &nameFile, int nameCount);

//sort the array of contributors
void sortDescend(Contributors contributors[], const int nameCount);

int main()
{
    int nameCount = 0; // stores the count of contributors
    string line;       // use to read file
    int count = 0;
    bool firstLine = false;

    cout << "==============================================" << endl;
    cout
        << " Welcome to this year's list of contributors!  " << endl;
    cout
        << "==============================================" << endl;

    ifstream nameFile("names.txt"); // read file
    nameFile >> nameCount;

    Contributors contributors[maxContributors];
    //getting the names
    ReadNameFile(contributors, nameFile, nameCount);

    //reading line by line
    cout.flush();
    nameFile.close();

    ReadSlushFile(contributors, nameCount);

    cout << "\nTotal Contributions per Contributors \n"
         << endl;

    //alphabetical
    for (int i = 0; i < nameCount; i++)
    {

        cout << contributors[i].name << endl;
        cout << contributors[i].amount << endl;
    }

    cout << endl
         << endl
         << endl;
    sortDescend(contributors, nameCount);
    //descending
    for (int i = 0; i < nameCount; i++)
    {

        cout << contributors[i].name << endl;
        cout << contributors[i].amount << endl;
    }

    cout << "==============================================" << endl;
    cout
        << " Thank you once again, for your contribution! " << endl;
    cout
        << "==============================================" << endl;
    return 0;
}

void ReadNameFile(Contributors contributors[], ifstream &nameFile, int nameCount)
{
    string line;
    int count = 0;
    bool firstLine = false;

    //reading line by line
    while (getline(nameFile, line))
    {
        //doesn't read the first line of file
        if (!firstLine)
        {

            firstLine = true;
        }
        else
        {

            if (count >= nameCount)
            {
                break;
            }
            if (line.length() == 0)
            {
                continue;
            }

            contributors[count].name = line;
            contributors[count].amount = 0.0;
            count++;
        }
    }
}

void ReadSlushFile(Contributors contributors[], int size)
{
    double amount;
    string contriName;
    string line;
    ifstream slushFile("slush.txt"); // read file

    //reading line by line of the slush file with
    //contributions
    while (getline(slushFile, line))
    {

        slushFile >> amount;
        contriName = line;

        slushFile.ignore(1, '\n');

        if (amount >= 0)
        {
            AddContributions(contriName, amount, contributors, size);
        }
        else
        {
            cout << "Contributor: " << contriName << endl;
            cout << "Contribution: INVALID AMOUNT" << endl;
        }
    }
    slushFile.close();
}

//adding the contributors
void AddContributions(string key, double amount, Contributors contributors[], int size)
{
    cout.flush();
    bool found = false;

    //checking if the contributors are in the list then update
    //their donations
    for (int i = 0; i < size; i++)
    {
        if (contributors[i].name == key)
        {
            cout << "Contributor: " << key << endl;
            cout << "Contribution: $" << amount << endl;
            contributors[i].amount += amount;
            found = true;
            break;
        }
    }
}

void sortDescend(Contributors contributors[], const int nameCount)
{
    Contributors temp;
    int largestIndex;
    for (int i = 0; i < nameCount - 1; i++)
    {
        largestIndex = i;
        for (int j = i + 1; j < nameCount; j++)
        {
            if (contributors[j].amount > contributors[largestIndex].amount)
                largestIndex = j;
            if (largestIndex != i)
            {
                temp = contributors[i];
                contributors[i] = contributors[largestIndex];
                contributors[largestIndex] = temp;
            }
        }
    }
}
