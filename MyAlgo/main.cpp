#include "Log.h"
#include <sstream>
#include "GeneticAlgo.h"

const int encoding_type = 0;
const int crossover_rate = 70;
const int mutation_rate = 100;
const int population_size = 10;
const int number_iterations = 7000;
const int numb_of_params = 2;
const int tournament_size = population_size / 4;

int main()
{
    // Run the GA!
    GeneticAlgorithm ga;

    ga.Initialize( encoding_type,
                   crossover_rate,
                   mutation_rate,
                   population_size,
                   number_iterations,
                   numb_of_params,
                   tournament_size,
                   "/Users/Yasya/Desktop/Second.txt");
    ga.Run();

    return 0;
}