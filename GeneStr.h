#pragma once
#include "Gene.h"
#include <string>


class GeneStr: public Gene<std::string>
{
public:
    GeneStr();
    GeneStr(unsigned int len);
    GeneStr(std::string code);
    int CalcCost(std::string resGene);
    void MutateStr(unsigned int probability);
private:
    static const int size = 53;
    static const char alleles[size];
    void construct();

};

