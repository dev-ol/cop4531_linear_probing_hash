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

void AddContributions(string key, double amount, Contributors contributors[], int size);
void ReadSlushFile(Contributors contributors[], int size);
void ReadNameFile(Contributors contributors[], ifstream &nameFile, int nameCount);

int main()
{
    int nameCount = 0;
    string line;
    int count = 0;
    bool firstLine = false;

    ifstream nameFile("names.txt"); // read file
    nameFile >> nameCount;

    Contributors contributors[maxContributors];
    ReadNameFile(contributors, nameFile, nameCount);
    //reading line by line
    cout.flush();
    nameFile.close();

    ReadSlushFile(contributors, nameCount);

    cout << "\nTotal Contributions per Contributors \n"
         << endl;

    for (int i = 0; i < nameCount; i++)
    {

        cout << contributors[i].name << endl;
        cout << contributors[i].amount << endl;
    }

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

    //reading line by line
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
            cout << "\nDonated an INVALID AMOUNT\n"
                 << endl;
        }
    }
    slushFile.close();
}

void AddContributions(string key, double amount, Contributors contributors[], int size)
{
    cout.flush();
    bool found = false;
    for (int i = 0; i < size; i++)
    {
        if (contributors[i].name == key)
        {
            cout << key << " donated $" << amount << endl;
            contributors[i].amount += amount;
            found = true;
            break;
        }
    }
    if (found == false)
        cout << key << " donated $" << amount << endl;
}