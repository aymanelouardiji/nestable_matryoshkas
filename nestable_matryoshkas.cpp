#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>

class MatryoshkaCalculator
{
public:
    int calculateRecursive(int largestSize, int smallestSize, double reductionPercentage)
    {
        if (largestSize <= smallestSize)
        {
            return 0;
        }
        else
        {
            int nextSize = largestSize - (largestSize * reductionPercentage / 100);
            return 1 + calculateRecursive(nextSize, smallestSize, reductionPercentage);
        }
    }

    int calculateIterative(int largestSize, int smallestSize, double reductionPercentage)
    {
        int count = 0;
        double currentSize = largestSize;

        while (currentSize > smallestSize)
        {
            currentSize -= (currentSize * reductionPercentage / 100);
            count++;
        }

        return count;
    }
};

int main()
{
    int largestSize, smallestSize;
    double reductionPercentage;

    std::cout << "Enter the size of the largest matryoshka: ";
    std::cin >> largestSize;
    std::cout << "Enter the size of the smallest matryoshka: ";
    std::cin >> smallestSize;
    std::cout << "Enter the percentage reduction for the next smallest matryoshka: ";
    std::cin >> reductionPercentage;

    if (largestSize <= 0 || smallestSize <= 0 || reductionPercentage <= 0 || reductionPercentage >= 100)
    {
        std::cout << "Invalid input. Please enter positive values for sizes and a reduction percentage between 0 and 100." << std::endl;
        return 1;
    }

    MatryoshkaCalculator calculator;
    int recursiveCount = calculator.calculateRecursive(largestSize, smallestSize, reductionPercentage);
    int iterativeCount = calculator.calculateIterative(largestSize, smallestSize, reductionPercentage);

    std::cout << "Number of nestable Matryoshkas Recursive: " << recursiveCount << std::endl;
    std::cout << "Number of nestable Matryoshkas Iterative: " << iterativeCount << std::endl;
    std::srand(static_cast<unsigned>(std::time(0)));

    std::ofstream outputFile("matryoshka_experiment.csv");
    outputFile << "Experiment,Largest Size,Smallest Size,Percentage,Recursive Result,Iterative Result,Recursive Time ,Iterative Time \n";

    for (int i = 0; i < 25; i++)
    {
        int largestSize = std::rand() % 100 + 50;
        int smallestSize = std::rand() % 50 + 1;
        double percentage = (std::rand() % 50 + 1) * 0.1;

        MatryoshkaCalculator calculator;

        auto start = std::chrono::high_resolution_clock::now();
        int recursiveResult = calculator.calculateRecursive(largestSize, smallestSize, percentage);
        auto end = std::chrono::high_resolution_clock::now();
        auto recursiveTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        int iterativeResult = calculator.calculateIterative(largestSize, smallestSize, percentage);
        end = std::chrono::high_resolution_clock::now();
        auto iterativeTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "Experiment " << i + 1 << ":\n";
        std::cout << "Largest Size: " << largestSize << ", Smallest Size: " << smallestSize << ", Percentage: " << percentage << std::endl;
        std::cout << "Recursive Result: " << recursiveResult << ", Time (ms): " << recursiveTime << std::endl;
        std::cout << "Iterative Result: " << iterativeResult << ", Time (ms): " << iterativeTime << std::endl;

        outputFile << i + 1 << "," << largestSize << "," << smallestSize << "," << percentage << "," << recursiveResult << "," << iterativeResult << "," << static_cast<double>(recursiveTime) / 1000 << "," << static_cast<double>(iterativeTime) / 1000 << "\n";
    }

    outputFile.close();
    return 0;
}
