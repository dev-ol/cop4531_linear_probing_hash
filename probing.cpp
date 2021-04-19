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
void quadraticProbing(int array[], int hashSize,
                      int arraySize, double loadFactor);
void linearProbing(int array[], int hashSize,
                   int arraySize, double loadFactor);

void doubleHashing(int array[], int hashSize,
                   int arraySize, double loadFactor);

void myHashProbing(int array[], int hashSize,
                   int arraySize, double loadFactor);

int main()
{

    int max = 1000000;
    double loadfactor = 0.5;
    int hashSize = (max);
    int *array;
    int arraySize = 0;

    clearFiles();

    while (loadfactor <= 0.99)
    {
        arraySize = (int)ceil(max * loadfactor);
        
        array = new int[arraySize];
        GenerateArray(array, arraySize);

        quadraticProbing(array, hashSize, arraySize, loadfactor);
        

        linearProbing(array, hashSize, arraySize, loadfactor);
 
        doubleHashing(array, hashSize, arraySize, loadfactor);
        myHashProbing(array,  hashSize, arraySize, loadfactor);
    

        loadfactor = loadfactor + 0.1;

        if(loadfactor > 0.99){
            loadfactor-= 0.01;
        }
    }

    delete[] array;
    

    return 0;
}

void quadraticProbing(int array[], int hashSize, int arraySize, double loadFactor)
{
    HashEl *table = new HashEl[hashSize];
   
    ofstream resultFile("results/quadratic_probing.txt", std::ios::app);

    int32_t numProbes = 0;


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
                index = (keyHash + (x * x)) % hashSize;
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

void linearProbing(int array[],  int hashSize,
                   int arraySize, double loadFactor)
{
    HashEl *table = new HashEl[hashSize];

    ofstream resultFile("results/linear_probing.txt", std::ios::app);

    int32_t numProbes = 0;

   
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

void doubleHashing(int array[], int hashSize,
                   int arraySize, double loadFactor)
{
     HashEl *table = new HashEl[hashSize];
    ofstream resultFile("results/double_hashing.txt", std::ios::app);

    int32_t numProbes = 0;
  
    for (int i = 0; i < arraySize; i++)
    {
        int x = 1;
        int keyHash = hashFunction(array[i], hashSize);

        int index = keyHash;
       
        if(table[index].set == false){
 
           table[index].set = true;
            table[index].value = array[i];
            table[index].key = keyHash;
         

        } else{
         
            while (table[index].set == true)
            {
                int test = (x * (7 - (keyHash % 7)));
               
                index = abs((keyHash + test) % hashSize);
                x++;

                numProbes++;
            }
             
        
             table[index].set = true;
             table[index].key = keyHash;
             table[index].value = array[i];
        }

        
    }


    resultFile << "x = " << loadFactor << " y = "
               << abs(numProbes) << endl;

    resultFile.close();
}


void myHashProbing(int array[], int hashSize,
                   int arraySize, double loadFactor){
    HashEl *table = new HashEl[hashSize];
   
    ofstream resultFile("results/my_hash_probing.txt", std::ios::app);

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
                
                index = (keyHash + (x * x * x) + (keyHash/2)) % hashSize;
                x = x + 1;

               // keyHash= (keyHash + 7) * x;

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
    remove( "results/my_hash_probing.txt");
}
