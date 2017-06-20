#include "Log.h"
#include <sstream>
#include "GeneticAlgo.h"

const int encoding_type = 0;
const int crossover_rate = 70;
const int mutation_rate = 5;
const int population_size = 100;
const int number_iterations = 10000;
const int number_parameters = 2;
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
                   number_parameters,
                   tournament_size,
                   "/Users/Yasya/Desktop/res_a.txt");
    ga.Run();

    return 0;
}