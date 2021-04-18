
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

struct HashEl
{
    int key;
    int value;
    bool set = false;
};

void clearFiles();
void GenerateArray(int list[], int amount);
int hashFunction(int key, int n);
int hashFunction2(int key, int size, int prime);
void quadraticProbing(int array[], HashEl table[], int hashSize,
                      int arraySize, double loadFactor);
void linearProbing(int array[], HashEl table[], int hashSize,
                   int arraySize, double loadFactor);

void doubleHashing(int array[], HashEl table[], int hashSize,
                   int arraySize, double loadFactor);

void myHashProbing(int array[], int hashSize,
                   int arraySize, double loadFactor);

int main()
{

    int max = 10;
    double loadfactor = 0.5;
    int hashSize = (max);
    HashEl *table = new HashEl[hashSize];
    int *array;
    int arraySize = 0;

    clearFiles();

    while (loadfactor <= 0.99)
    {
        //cout << "Load factor " << loadfactor << endl;
        arraySize = (int)ceil(max * loadfactor);
        cout << "\nnumber ele "<< arraySize << endl;
        array = new int[arraySize];
        GenerateArray(array, arraySize);

        // cout << "\nQuadratic Probing" << endl;
        //quadraticProbing(array, table, hashSize, arraySize, loadfactor);
        //table = new HashEl[hashSize];

        // cout << "***********************" << endl;

        //cout << "\nLinear Probing" << endl;
       //linearProbing(array, table, hashSize, arraySize, loadfactor);
        //table = new HashEl[hashSize];

        // cout << "***********************" << endl;
        // cout << "\nDouble Hashing Probing" << endl;
     //   doubleHashing(array, table, hashSize, arraySize, loadfactor);
        myHashProbing(array,  hashSize, arraySize, loadfactor);
        //table = new HashEl[hashSize];

        // cout << "***********************" << endl;

        loadfactor = loadfactor + 0.1;

        if(loadfactor > 0.99){
            loadfactor-= 0.01;
        }
    }

    delete[] array;
    delete[] table;

    return 0;
}

void quadraticProbing(int array[], HashEl table2[], int hashSize, int arraySize, double loadFactor)
{
    HashEl *table = new HashEl[hashSize];
   
    ofstream resultFile("results/quadratic_probing.txt", std::ios::app);

    int numProbes = 0;


    for (int i = 0; i < arraySize; i++)
    {
        int x = 0;
        int keyHash = hashFunction(array[i], hashSize);

        int index = keyHash;
        
        if(table[index].set == false){

           cout << "\n INSERT \n" <<endl;
           table[index].set = true;
             table[index].key = keyHash;
           table[index].value = array[i];

        } else{

            while (table[index].set == true)
            {
                index = (keyHash + (x * x)) % hashSize;
                x = x + 1;

                numProbes++;
            }
            table[index].set = true;
           
               table[index].key = keyHash;
           table[index].value = array[i];
        }
    }


    cout << "Probing amount : " << numProbes << endl;

    resultFile << "x = " << loadFactor << " y = "
               << numProbes << endl;

    resultFile.close();
}

void linearProbing(int array[], HashEl table2[], int hashSize,
                   int arraySize, double loadFactor)
{
    HashEl *table = new HashEl[hashSize];

    ofstream resultFile("results/linear_probing.txt", std::ios::app);

    int numProbes = 0;

   
    for (int i = 0; i < arraySize; i++)
    {
        int x = 0;
        int keyHash = hashFunction(array[i], hashSize);

        int index = keyHash;
         if(table[index].set == false){

           table[index].set = true;
           table[index].key = keyHash;
           table[index].value = array[i];

        } else{

            while (table[index].set == true)
            {
                index = (keyHash + x) % hashSize;
                x = x + 1;

                numProbes++;
            }

             table[index].set = true;
             table[index].key = keyHash;
              table[index].value = array[i];
        }

      
    }

  
    resultFile << "x = " << loadFactor << " y = "
               << numProbes << endl;

    resultFile.close();
}

void doubleHashing(int array[], HashEl table2[], int hashSize,
                   int arraySize, double loadFactor)
{
     HashEl *table = new HashEl[hashSize];
    ofstream resultFile("results/double_hashing.txt", std::ios::app);

    int32_t numProbes = 0;
    //int prime = getPrime(hashSize);
  

    for (int i = 0; i < arraySize; i++)
    {
        int x = 1;
        int keyHash = hashFunction(array[i], hashSize);

        int index = keyHash;
       // cout << "num to insert " << array[i] << endl;
       // cout << "num to insert " << array[i] << endl;

        if(table[index].set == false){

        //   cout << "\n INSERT \n" <<endl;
           table[index].set = true;
            table[index].value = array[i];
            table[index].key = keyHash;
           // cout << "***index " << index << endl;

        } else{
           // int keyhash2 = hashFunction2(array[i], hashSize, 7);
            while (table[index].set == true)
            {
                int test = (x * (7 - (keyHash % 7)));
               // cout << "test#### << " << test << endl;
                index = abs((keyHash + test) % hashSize);
                x++;

                numProbes++;
            }
             
          //   cout << "***index " << index << endl;
             table[index].set = true;
             //cout << "\n INSERT 2 \n" <<endl;
             table[index].key = keyHash;
             table[index].value = array[i];
        }

        
    }


    cout << "Probing amount : " << numProbes << endl;

    resultFile << "x = " << loadFactor << " y = "
               << abs(numProbes) << endl;

    resultFile.close();
}


void myHashProbing(int array[], int hashSize,
                   int arraySize, double loadFactor){
    HashEl *table = new HashEl[hashSize];
   
    ofstream resultFile("results/quadratic_probing.txt", std::ios::app);

    int numProbes = 0;


    for (int i = 0; i < arraySize; i++)
    {
        int x = 0;
        int keyHash = hashFunction(array[i], hashSize);

        int index = keyHash;
        
        if(table[index].set == false){

           table[index].set = true;
             table[index].key = keyHash;
           table[index].value = array[i];

        } else{

            while (table[index].set == true)
            {
                index = ((keyHash + keyHash) % 7) % hashSize;
                x = x + 1;

                keyHash= (keyHash + 7) * x;

                numProbes++;
            }
            table[index].set = true;
           
               table[index].key = keyHash;
           table[index].value = array[i];
        }
    }


    resultFile << "x = " << loadFactor << " y = "
               << numProbes << endl;

    resultFile.close();
}

int hashFunction(int key, int n)
{

    return abs(key % n);
}

int hashFunction2(int key, int size, int prime)
{
    key %= size;

    if(key < 0){
        key += size;
    }
    int test = prime - key % prime;
    cout << " testtt " << test << endl;
    return test;
}

void GenerateArray(int list[], int amount)
{

    srand((unsigned)time(0));

    for (int i = 0; i < amount; i++)
    {
        list[i] = (rand() % amount) + 1;
    }
}

void clearFiles()
{
    remove("results/quadratic_probing.txt");
    remove("results/linear_probing.txt");
    remove("results/double_hashing.txt");
    //remove( "results/quadratic_probing.txt");
}

int getPrime(int hashSize)
{  
        for (int i = hashSize - 1; i >= 1; i--) {
  
            int count = 0;

            for (int j = 2; j * j <= i; j++)
  
                if (i % j == 0)
  
                
                    count++;

            if (count == 0)

                return i;
        }

        return 3;
    }