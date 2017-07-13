#include "Population.h"
#include <bitset>
#include <iostream>
#include <math.h>
#include <stdlib.h>

const int divisor_32 = 4294967295; // 2 ^ 32 - 1
const int divisor_31 = 2147483647; // 2 ^ 31 - 1

Population::Population(void)
{
    // Set default chromosome size 32 + 32 = 64 - two numbers
    chrSize = 64;
}

Population::~Population(void)
{
    int size =  pop.size();
    for ( int i = 0; i < size; i++ )
    {
        Chromosome* chr = pop.at( i );
        if ( chr != NULL)
        {
            delete chr;
        }
    }
    pop.clear();
}

// Set the type of chromosomal encoding used: IEEE 754, Gray etc
void Population::SetChromosomeEncoding( const int& type )
{
    encoding = type;
}

// Create initial arbitrary population of chromosomes
void Population::CreateRandomPopulation( const int& size )
{
    for ( int i = 0; i < size; i++ )
    {
        Chromosome* chr = CreateRandomChromosome();
        pop.push_back( chr );
    }
}

// Apply one-point crossover to selected chromosome pair (the simplest)
/*void Population::Crossover( const int& index1, const int& index2,
                            const int& point )
{
    if ( point < 0 || point >= chrSize )
    {
        return;
    }

    Chromosome* chr1 = pop.at( index1 );
    Chromosome* chr2 = pop.at( index2 );

    for ( int i = point; i < chrSize; i++ )
    {
        unsigned char v1 = chr1->GetChromosome( i );
        unsigned char v2 = chr2->GetChromosome( i );
        chr1->SetChromosome( index1, v2 );
        chr2->SetChromosome( index1, v1 );
    }
}*/

// Apply one-point crossover to selected chromosome pair
void Population::Crossover( const int& index1, const int& index2,
                            const int& point1, const int& point2 )
{
    //not necessary
    if ( point1 < 0 || point1 >= chrSize || point2 < 0 || point2 >= chrSize)
        return;



    int p1 = point1;
    int p2 = point2;

    //not necessary
    if ( p1 > p2 )
    {
        int tmp = p1;
        p1 = p2;
        p2 = tmp;
    }

    Chromosome* chr1 = pop.at( index1 );
    Chromosome* chr2 = pop.at( index2 );

    // Do crossover on x portion of chromosome:
    // either before or after point p1
    int start = 0;
    int end = p1;
    if ( rand() % 100 < 50 ) {
        start = p1;
        end = chrSize / 2;
    }

    for ( int i = start; i < end; i++ ) {
        unsigned char v1 = chr1->GetChromosome( i );
        unsigned char v2 = chr2->GetChromosome( i );
        chr1->SetChromosome( i, v2 );
        chr2->SetChromosome( i, v1 );
    }

    // Do crossover on x portion of chromosome
    // either before or after point p2
    start = chrSize / 2;
    //start = 0;
    end = p2;
    if ( rand() % 100 < 50 ) {
        start = p2;
        end = chrSize;
    }
    for ( int i = start; i < end; i++ ) {
        chr1->SetChromosome( i, chr2->GetChromosome( i ) );
        chr2->SetChromosome( i, chr1->GetChromosome( i ) );
    }
}

// Apply the simplest two-point crossover to selected chromosome pair
/*void Population::Crossover( const int& index1, const int& index2,
                            const int& point1, const int& point2 )
{
    //not necessary
    if ( point1 < 0 || point1 >= chrSize || point2 < 0 || point2 >= chrSize)
        return;



    int p1 = point1;
    int p2 = point2;

    //not necessary
    if ( p1 > p2 )
    {
        int tmp = p1;
        p1 = p2;
        p2 = tmp;
    }

    Chromosome* chr1 = pop.at( index1 );
    Chromosome* chr2 = pop.at( index2 );

    int start = p1;
    int end = p2;

    for ( int i = start; i < end; i++ ) {
        unsigned char v1 = chr1->GetChromosome( i );
        unsigned char v2 = chr2->GetChromosome( i );
        chr1->SetChromosome( i, v2 );
        chr2->SetChromosome( i, v1 );
    }

}*/

// Apply mutation to selected chromosome: x part or y part
//на проміжку заміняють все на протилежне. ПОМІНЯТИ! НАДТО РАДИКАЛЬНО!
void Population::Mutation( const int& index )
{
    Chromosome* chr = pop.at( index );
    bool xpart = rand() % 100 < 50 ? true : false;
    int start = xpart ? 0 : chrSize / 2;
    int end = xpart ? chrSize / 2 : chrSize;

    for ( int i = start; i < end; i++ ) {
        unsigned char value = chr->GetChromosome( i );
        value = value == 0 ? 1 : 0;
        chr->SetChromosome( i, value );
    }
}

// Evaluate the population fitnesses
double Population::EvaluatePopulation( float& bx, float& by )
{
    double totalFitness = 0.0;
    //double aveFitness = 0.0;
    double bestFitness = infinity;
    int bestFitnessIndex = 0;

    for ( int i = 0; i < pop.size(); i++ ) {
        float x, y;
        double fitness = CalcChromosomeFitness( i, x, y );
        Chromosome* chr = pop.at( i );
        //встановлюємо фітнес для хромосоми
        chr->SetFitness( fitness );
        SetFitSum(fitness);

        // Output the chromosome (optional - comment out if desired)
        chr->Print( i );
        totalFitness += fitness;

        // Store best solution

        if ( fitness < bestFitness ) {
            bestFitness = fitness;
            bestFitnessIndex = i;
            //у змінні впишуться числа х і у з найкращим результатом
            bx= x;
            by= y;
        }
    }

    std::cout << "nn";
    //aveFitness = totalFitness / pop.size();
    return bestFitness;
}

void Population::SetFitSum( const double& value ){
    fitSum += fabs(value);
};
double Population::GetFitSum() {
    return fitSum;
};


// Create an arbitrary random chromosome
Chromosome* Population::CreateRandomChromosome()
{
    Chromosome* chr = new Chromosome(chrSize);

    //Тут рандомна хромосома тупо заповнюється одиничками і нулями. Може, краще в конструктор дати?
    // Randomize chromosome elements
    for ( int i = 0; i < chr->size(); i++ )
    {
        unsigned char value = rand() % 100 < 50 ? 0 : 1;

        chr->SetChromosome( i, value );
    }

    return chr;
}


// Calculate chromosome fitness according to chromosome encoding used
double Population::CalcChromosomeFitness(
        const int& index,
        float& xv,
        float& yv)
{
    if ( encoding == GRAY )
    {
        return CalcChromosomeFitnessGray( index, xv, yv );
    }
    else
    {
        return CalcChromosomeFitness_IEEE754( index, xv, yv );
    }
}


// Get fitness of selected chromosome according to IEEE 754 coding
double Population::CalcChromosomeFitness_IEEE754(
        const int& index,
        float& xv,
        float& yv )
{
    // Get the chromosome elements
    Chromosome* chr = pop.at( index );

    // Put the first 32 bits (X) into a string
    std::string xstr = GetString( chr, 1 );

    // Get x value by converting from IEEE 754 into decimal
    float x = GetFloat32_IEEE754( xstr );

    // Put the next 32 bits (Y) into a string
    std::string ystr = GetString( chr, 2 );

    // Get y value by converting from IEEE 754 into decimal
    float y = GetFloat32_IEEE754( ystr );
    double fitness = CalculateFitnessFunction<float>( x, y );

    // Return the chromosome fitness
    xv = x;
    yv = y;

    return fitness;
}

// Get fitness of selected chromosome according to Gray coding
double Population::CalcChromosomeFitnessGray(
        const int& index,
        float& xv,
        float& yv )
{
    // Get the chromosome elements
    Chromosome* chr = pop.at( index );

    // Put the first 32 bits (X) into a string
    std::string xstr = GetString( chr, 1 );

    // Get x value by converting from Gray into decimal
    float x = GetFloat32_Gray( xstr );

    // Put the next 32 bits (Y) into a string
    std::string ystr = GetString( chr, 2 );

    // Get y value by converting from Gray into decimal
    float y = GetFloat32_Gray( ystr );
    double fitness = CalculateFitnessFunction<float>( x, y );

    // Return the chromosome fitness
    xv = x; yv = y;

    return fitness;
}

// Set the size of the chromosome
void Population::SetChromosomeSize( const int& size )
{
    chrSize = size;
}

/*// Get the 'X' string portion of the chromsome
std::string Population::GetXstring( Chromosome* chr )
{
    std::string xstr;

    for ( int i = 0; i < chrSize / 2; i++ )
    {
        unsigned char value = chr->GetChromosome( i );
        xstr.append( value == 0 ? "0" : "1" );
    }

    return xstr;
}

// Get the 'Y' string portion of the chromsome
std::string Population::GetYstring( Chromosome* chr )
{
    std::string ystr;
    int start = chrSize / 2;

    for ( int i = start; i < chrSize; i++ )
    {
        unsigned char value = chr->GetChromosome( i );
        ystr.append( value == 0 ? "0" : "1" );
    }

    return ystr;
}*/

// Get the 'ith' string portion of the chromsome
std::string Population::GetString( Chromosome* chr, int parNumb )
{
    std::string xstr;
    int start = (parNumb - 1)*32;

    for ( int i = start; i < (start + 32); i++ )
    {
        unsigned char value = chr->GetChromosome( i );
        xstr.append( value == 0 ? "0" : "1" );
    }

    return xstr;
}

// Convert 32-bit binary into the decimal
// IEEE 754 encoding for 32 bit binary string
float Population::GetFloat32_IEEE754( std::string Binary )
{
    int HexNumber = Binary32ToHex( Binary );
    bool negative = (HexNumber & 0x80000000);
    int exponent = (HexNumber & 0x7f800000) >> 23;
    int sign = negative ? -1 : 1;

    // Subtract 127 from the exponent
    exponent -= 127;

    // Convert mantissa into decimal using last 23 bits
    int power = -1;
    float total = 0.0;

    for ( int i = 0; i < 23; i++ )
    {
        int c = Binary[ i + 9 ] - '0';
        total += (float) c * (float) pow( 2.0, power );
        power--;
    }
    total += 1.0;
    float value = sign * (float) pow( 2.0, exponent ) * total;
    return value;
}

// Convert 32-bit gray encoding into the decimal equivalent
float Population::GetFloat32_Gray( std::string Binary )
{
    // Get sign bit
    int sign = Binary.at( 0 ) == '0' ? 1 : -1;

    // Get remaining stringF
    std::string rem = Binary.substr( 1 );
    std::string bin = Gray2Bin( rem );
    long bin_val = Bin2Dec( bin );
    float val = (float) bin_val / (float) divisor_31;
    val *= sign;

    return val;
}

// Convert the 32-bit binary encoding into hexadecimal
int Population::Binary32ToHex( std::string Binary )
{
    std::bitset<32> set(Binary);
    int hex = set.to_ulong();
    return hex;
}

// Calculate the overall fitness, f(x, y)
/*template <typename ... Axes>
double Population::CalculateFitnessFunction( const float& x,

                                             Axes&... axes )
{
    // Rosenbrock: (1-x)^2 + 100(y-x*x)^2
    // (see http://en.wikipedia.org/wiki/Rosenbrock_function)
    constexpr int size = sizeof...(axes)+1;
    std::vector<std::reference_wrapper<const float>> arr = { x, axes ... };

    double fitness = ( pow( (double)( 1.0 - x ), 2 ) ) +
                     100 * ( pow( (double) ( arr[0] - ( x * x ) ), 2 ) ) ;

    return fitness;
}*/
/*double Population::CalculateFitnessFunction( const float& x,
                                             const float& y )
{
    // Rosenbrock: (1-x)^2 + 100(y-x*x)^2
    // (see http://en.wikipedia.org/wiki/Rosenbrock_function)

    double fitness = ( pow( (double)( 1.0 - x ), 2 ) ) +
                     100 * ( pow( (double) ( y - ( x * x ) ), 2 ) ) ;

    return fitness;
}*/
// Get fitness of selected chromosome
double Population::GetChromosomeFitness( const int& index ) const
{
    // Get the chromosome
    Chromosome* chr = pop.at( index );

    return chr->GetFitness();
}

// Copy the contents of the source chromosome into destination
void Population::CopyChromosome( const int& source, const int& dest )
{
    // Get the chromosomes
    Chromosome* chr1 = pop.at( source );
    Chromosome* chr2 = pop.at( dest );

    // Copy elements and fitness of source chromosome
    // into the destination chromosome
    for ( int i = 0; i < chrSize; i++ )
    {
        // Get source chromosome element
        unsigned char value = chr1->GetChromosome( i );
        // Write this element value into the destination element
        chr2->SetChromosome( i, value );
    }

    // Set the destination chromosome fitness
    double fitness = chr1->GetFitness();
    chr2->SetFitness( fitness );
}

// Convert gray encoding into binary
std::string Population::Gray2Bin( std::string gray )
{
    int len = gray.length();
    std::string bin = gray;

    for ( int i = len - 2; i >= 0; i-- )
    {
        int bk = bin.at( i + 1 ) - '0';
        int gi = gray.at( i + 1 ) - '0';

        //якщо там нулик

        if ( bk == 0 )
        {
            bin[ i ] = gi == 1 ? '1' : '0';
        }
        else
        {
            bin[ i ] = gi == 1 ? '0' : '1';
        }
    }

    return bin;
}

// Binary to int
long Population::Bin2Dec( std::string bin )
{
    char * ptr;
    long parsed = strtol( bin.c_str(), & ptr, 2 );

    return parsed;
}
