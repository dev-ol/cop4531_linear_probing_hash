#include <iostream>
#include <fstream>

using namespace std;

int hashFunction(int key, int n);

struct HashEl
{
    int key;
    int value;
    bool set = false;
};

int main()
{
    int size = 5;
    int loadFactor = 0.5; // a
    int threshold = size * loadFactor;

    HashEl *table = new HashEl[size];

    int probing = 0;

    int test[] = {2, 12, 22, 32};

    for (int i = 0; i < 4; i++)
    {
        int x = 1;
        int keyHash = hashFunction(test[i], size);

        int index = keyHash;

        while (table[index].set == true)
        {
            index = (keyHash + (x * x)) % size;
            x = x + 1;

            probing++;
        }

        table[index].set = true;
        table[index].key = keyHash;
        table[index].value = test[i];

        if (i > threshold)
        {
            //TODO should we update the hash table
        }

        // cout << "position to insert = " << index << endl;
    }

    for (int i = 0; i < size; i++)
    {
        cout << i << ") "
             << "Key : " << table[i].key << " value : " << table[i].value << endl;
    }

    cout << "Probing amount : " << probing << endl;
    return 0;
}

int hashFunction(int key, int n)
{
    return key % n;
}

void Run()
{
    ofstream resultFile("results/quadratic_probing.txt");

    resultFile.close();
}