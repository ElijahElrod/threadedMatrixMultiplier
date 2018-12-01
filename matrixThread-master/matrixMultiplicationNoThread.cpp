
#include <iostream>
#include <vector>
#include <cstdlib>
// #include <pthread.h> IMPLEMENT ME

using namespace std;

// #define NUM_THREAD 4; number of threads to split calculations between

// Function prototypes
vector<vector<int> > matrixMultiplier(vector<vector<int> > &matrix1, vector<vector<int> >  &matrix2);
void matrixDisplay(vector<vector<int> > &matrix);

const int NUM_ELEMENTS = 20;

int main ()
{
    // Uses seed based on current time
    srand(time(NULL));
    vector<vector<int> > matrix1, matrix2, returnMatrix;
    

    matrix1.resize(NUM_ELEMENTS);
    matrix2.resize(NUM_ELEMENTS);

    // Randomly generates values for each matrices and pushes them onto the end of each vector
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        for (int j = 0; j < NUM_ELEMENTS; j++)
        {
            matrix1.at(i).push_back(rand() % 10);
            matrix2.at(j).push_back(rand() % 10);
        }
    }

    returnMatrix = matrixMultiplier(matrix1, matrix2);

    cout << "\nFirst Matrix \n" << endl;
    matrixDisplay(matrix1);
    cout << "\nSecond Matrix \n" <<  endl;
    matrixDisplay(matrix2);
    cout << "\nFinal Matrix from multiplication \n" << endl;
    matrixDisplay(returnMatrix);

    return 0;
}

// Multiplys two matrices by passing reference to each matrix and returning an empty
// matrix if the two matrices have different dimensions
vector<vector<int> > matrixMultiplier(vector<vector<int> >  &matrix1, vector<vector<int> >  &matrix2)
{
    vector<vector<int> > returnMatrix;

    int nrows = matrix1.size();
    int ncols = matrix1.at(0).size();

    // Checks to make sure both matrices are of the same dimensions
    if (nrows != matrix2.size() || ncols != matrix2.at(0).size())
        return returnMatrix;
    else   
        returnMatrix.resize(nrows);

    // Calculation of result for each index of the resulting matrix
    for (int i = 0; i < nrows; i++)
    {
        returnMatrix[i].resize(ncols);
        for (int j = 0; j < ncols; j++)
        {
            returnMatrix[i][j] = 0; 
            for (int k = 0 ; k < nrows; k++)
                returnMatrix.at(i).at(j) += matrix1.at(i).at(k) * matrix2.at(k).at(j);
        }
    }
    return returnMatrix;
}


// Displays a matrix passed by reference using &matrix.
void matrixDisplay(vector<vector<int> > &matrix)
{
    int nrows = matrix.size();
    int ncols = matrix.at(0).size();
    
    for (int i = 0; i < nrows; i++)
    {
        cout << matrix.at(i).at(0);
        for (int j = 0; j < ncols; j++)
        {
            cout << "   " << matrix.at(i).at(j);
        }
        cout << endl;
    }
}
