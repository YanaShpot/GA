#pragma once
#include <string>
#include <vector>
#include "Gene.h"
#include "genestr.h"

using namespace std;

class Chromosome
{
public:
    Chromosome();
    Chromosome(vector<std::string> gene);
    void GetCode();
    int CalcCost( vector<std::string> result);


private:

    vector<GeneStr> m_code;
    int m_cost;
    int m_length;

};

