
#include <iostream>
#include <vector>
#include <cstdlib>
#include <pthread.h>

using namespace std;


//Function prototype
void* matrixMultiplier(void* arg);
void matrixDisplay(vector<vector<int> > &matrix);

// Globally declares three matrix of type vector<vector<int>>
vector<vector<int> > matrix1, matrix2, returnMatrix;

//Global constant and variable
const int NUM_ELEMENTS = 4;
const int NUM_THREADS = 4;
int matrixStep = 0;

int main ()
{
    // Randomly generates seed and creates thread storage of type pthread_t
    srand(time(NULL));
    pthread_t thread[NUM_THREADS];

    matrix1.resize(NUM_ELEMENTS);
    matrix2.resize(NUM_ELEMENTS);

    // Generates random integers to fill in two vector matrices
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        for (int j = 0; j < NUM_ELEMENTS; j++)
        {
            matrix1.at(i).push_back(rand() % 10);
            matrix2.at(j).push_back(rand() % 10);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        int* matrixPtr;
        cout << "Creating thread: " << i << endl;
        pthread_create(&thread[i], NULL, matrixMultiplier, (void*)matrixPtr); // Passes matrix multi function to thread
        pthread_join(thread[i], NULL); // Waits for thread termination
    }
    
    // Displays each matrix
    cout << "\nFirst Matrix \n" << endl;
    matrixDisplay(matrix1);
    cout << "\nSecond Matrix \n" <<  endl;
    matrixDisplay(matrix2);
    cout << "\nFinal Matrix from multiplication \n" << endl;
    matrixDisplay(returnMatrix);

    return 0;
}

// Utilizes pthreads to split into four parts
void* matrixMultiplier(void* arg)
{
   
    int thread = matrixStep++;

    returnMatrix.resize(NUM_ELEMENTS);

    // Each thread does 1/4 of matrix calculation.
    for (int i = thread * NUM_ELEMENTS/4; i < ((thread+1) * NUM_ELEMENTS/4); i++)
    {
        returnMatrix[i].resize(NUM_ELEMENTS);
        for (int j = 0; j < NUM_ELEMENTS; j++)
        { 
            for (int k = 0 ; k < NUM_ELEMENTS; k++)
                returnMatrix.at(i).at(j) += matrix1.at(i).at(k) * matrix2.at(k).at(j);
        }
    }

    return 0;
}

// Displays Matrix passed by reference using & in function definition.
void matrixDisplay(vector<vector<int> > &matrix)
{
    for (int i = 0; i < NUM_ELEMENTS; i++)
     {
        for (int j = 0 ; j < NUM_ELEMENTS; j++)
            cout << matrix.at(i).at(j) << " ";
        cout << endl;
     }
    
}
