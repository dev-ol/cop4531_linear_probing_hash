#include <iostream>

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
    int size = 10;
    int loadFactor = 0.5; // a
    int threshold = size * loadFactor;

    HashEl *table = new HashEl[size];

    int probing = 0;

    int test[] = {18, 14, 22, 32, 44, 59, 79};

    for (int i = 0; i < 7; i++)
    {
        int x = 1;
        int keyHash = hashFunction(test[i], size);

        int index = keyHash;

        while (table[index].set == true)
        {
            index = (keyHash + x) % size;
            x = x + 1;

            probing++;
        }

        table[index].set = true;
        table[index].key = keyHash;
        table[index].value = test[i];

        if (i > threshold)
        {
        }

        // cout << "position to insert = " << index << endl;
    }
    cout << "Probing amount : " << probing << endl;
    return 0;
}

int hashFunction(int key, int n)
{
    return key % n;
}