#include <vector>
#include <string>
#include "Chromosome.h"
#include <stdio.h>
#include <stdarg.h>
#include <cmath>

const double infinity = 9999999999999;

class Population
{
public:
    enum Encoding {
        GRAY = 0,
        IEEE_754 = 1,
    };

    Population(void);
    ~Population(void);

    void SetChromosomeEncoding( const int& type );
    void SetChromosomeSize( const int& size );
    void CreateRandomPopulation( const int& size );
    void Crossover( const int& index1,
                    const int& index2,
                    const int& point );
    void Crossover( const int& index1,
                    const int& index2,
                    const int& point1,
                    const int& point2 );
    void Mutation( const int& index );
    double EvaluatePopulation( float& bx, float& by );
    double CalcChromosomeFitness( const int& index,
                                  float& xv,
                                  float& yv);
    double GetChromosomeFitness( const int& index ) const;
    void CopyChromosome( const int& source, const int& dest );
    void SetFitSum( const double& value );
    double GetFitSum();

private:
    Chromosome* CreateRandomChromosome();
    //std::string GetXstring( Chromosome* chr );
    //std::string GetYstring( Chromosome* chr );
    std::string GetString( Chromosome* chr, int parNum );
    float GetFloat32_IEEE754( std::string Binary );
    float GetFloat32_Gray( std::string Binary );
    int Binary32ToHex( std::string Binary );
   /* double CalculateFitnessFunction( const float& x,
                                     const float& y );*/

   template <typename ... Axes>
   double CalculateFitnessFunction( const float& x,

                                                Axes&... axes );
    double CalcChromosomeFitness_IEEE754( const int& index,
                                          float& xv, float& yv);

    double CalcChromosomeFitnessGray( const int& index,
                                      float& xv, float& yv );
    std::string Gray2Bin( std::string gray );
    long Bin2Dec( std::string bin );

private:
    std::vector< Chromosome* > pop;
    int chrSize;
    int encoding;
    double fitSum = 0;

};


template <typename ... Axes>
double Population::CalculateFitnessFunction( const float& x,

                                             Axes&... axes )
{
    // Rosenbrock: (1-x)^2 + 100(y-x*x)^2
    // (see http://en.wikipedia.org/wiki/Rosenbrock_function)
    constexpr int size = sizeof...(axes)+1;
    std::vector<std::reference_wrapper<const float>> arr = { x, axes ... };

    double fitness = ( pow( (double)( 1.0 - x ), 2 ) ) +
                     100 * ( pow( (double) ( arr[1] - ( x * x ) ), 2 ) ) ;

    return fitness;
}