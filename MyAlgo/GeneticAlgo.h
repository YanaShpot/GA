#ifndef MYGA_GENETICALGO_H
#define MYGA_GENETICALGO_H

#include "Population.h"
#include "Log.h"

class GeneticAlgorithm
{
public:

    GeneticAlgorithm(void);
    ~GeneticAlgorithm(void);

    void Initialize( const int& enc,
                     const int& crate,
                     const int& mrate,
                     const int& psize,
                     const int& iter,
                     const int& params,
                     const int& tsize,
                     const std::string& path );
    void Run();
    //void Roulette(int& index1);

private:

    void CreatePopulation();
    double Evaluate();
    void Crossover();
    void Mutate();
    void Select();

    void Select2();

    void SetParameters( const int& enc,
                        const int& crate,
                        const int& mrate,
                        const int& psize,
                        const int& iter,
                        const int& params,
                        const int& tsize );

    void LogResult( const double& result,
                    const int& iter,
                    const int& count );

private:

    //int encoding;
    int mutationRate;
    int crossoverRate;
    int populationSize;
    int numberIterations;
    int numberParams;
    int chromosomeSize;
    int tournamentSize;

    int bestFitnessIndex;
    double bestFitness;
    float best_x;
    float best_y;

    Population pop;
    Log log;
};
#endif //MYGA_GENETICALGO_H
