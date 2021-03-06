#include "Chromosome.h"
#include <iostream>

// Constructor
Chromosome::Chromosome(int size): chrSize(size) {
    chr = new char[size];
}
//Chromosome::Chromosome(void): chrSize(64) {}

// Destructor
Chromosome::~Chromosome(void) {
    delete[] chr;

}

// Set chromosome element
void Chromosome::SetChromosome( const int& index, const unsigned char& value )
{
    if ( index < 0 || index >= chrSize ) return;
    chr[ index ] = value;
}

// Get chromosome element
unsigned char Chromosome::GetChromosome( const int& index )
{
    unsigned char element = chr[ index ];
    return element;
}

// Set fitness of chromosome
void Chromosome::SetFitness( const double& value )
{
    fitness = value;
}

// Get chromosome fitness
double Chromosome::GetFitness() const
{
    return fitness;
}

// Get number of elements in the chromosome
int Chromosome::size() const
{
    return chrSize;
}
// Output the chromosome and its fitness
void Chromosome::Print( const int& index ) const
{
    std::string str;
    for ( int i = 0; i < chrSize; i++ ) {
        unsigned char value = chr[ i ];
        str.append( value == 0 ? "0" : "1" );
    }
    std::cout << index << "\t" << str.c_str() << "\t" << fitness << std::endl;
}