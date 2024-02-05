#include "VectorDataset.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <sstream>

using namespace std;

int main()
{
    // Create a VectorDataset object and read the dataset from a CSV file
    VectorDataset dataset;
    string trainData;
    cout << "Enter the CSV file name for the vector datasheet: " << endl;
    cin >> trainData;

    // Check if the file exists
    ifstream fileCheck(trainData);
    if (!fileCheck)
    {
        cout << "Error: The file " << trainData << " does not exist." << endl;
        return 1; // Exit with an error code
    }

    // Read the dataset from the CSV file
    dataset.readDataset(trainData);

    // Get the test vector from the user
    vector<double> testVectorValues;
    VectorDataset testVectorSet;
    string testVectorFileName;

    cout << "Enter the CSV file name for the test vector: ";
    cin >> testVectorFileName;

    // Open the test vector file
    ifstream testVectorFile(testVectorFileName);

    if (!testVectorFile.is_open())
    {
        cout << "Could not open the test vector file: " << testVectorFileName << endl;
        return 1;
    }

    VectorDataset testDataset;
    testDataset.readDataset(testVectorFileName);

    // Perform k-Nearest Neighbor search
    size_t k;
    cout << "Enter the value of k: ";
    cin >> k;

    string nearestNeighborsFileName = "nearest_neighbors.csv";
    ofstream nearestNeighborsFile(nearestNeighborsFileName);

    vector<DataVector> testVectors = testDataset.getDataset();
    auto startSearch = chrono::high_resolution_clock::now();
    for (auto testVector : testVectors)
    {
        VectorDataset kNearestNeighbors = dataset.kNearestNeighbor(testVector, k);
        

        // Display the k-Nearest Neighbors
        const vector<DataVector> &neighbors = kNearestNeighbors.getDataset();

        if (!nearestNeighborsFile.is_open())
        {
            cout << "Could not create the nearest neighbors file: " << nearestNeighborsFileName << endl;
            return 1;
        }

        // Write the nearest neighbors to the CSV file
        for (size_t i = 0; i < neighbors.size(); ++i)
        {
            const DataVector &neighbor = neighbors[i];
            size_t dimension = neighbor.getDimension();

            for (size_t j = 0; j < dimension; ++j)
            {
                nearestNeighborsFile << neighbor[j];
                if (j < dimension - 1)
                {
                    nearestNeighborsFile << ",";
                }
            }

            nearestNeighborsFile << "\n"; 
        }
        nearestNeighborsFile << "\n"; 
        
    }
    auto endSearch = chrono::high_resolution_clock::now();
    // Calculate and display the total time taken for searching
    auto totalTimeSearch = chrono::duration_cast<chrono::milliseconds>(endSearch - startSearch);
    nearestNeighborsFile << "Total time for k-Nearest Neighbor search: " << totalTimeSearch.count() << " milliseconds" << endl;
    cout << "Total time for k-Nearest Neighbor search: " << totalTimeSearch.count() << " milliseconds" << endl<<endl;
    cout << "Nearest neighbors written to: " << nearestNeighborsFileName << endl;
    nearestNeighborsFile.close();

    return 0;
}
