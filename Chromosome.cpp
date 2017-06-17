#include "Chromosome.h"
#include <string>
#include <iostream>
#include <math.h>
#include "genestr.h"

using namespace std;
Chromosome::Chromosome()
{
}

Chromosome:: Chromosome(vector<std::string> genes) {
    for (int i = 0; i < genes.size(); ++i) {
        m_code.push_back(*(new GeneStr(genes[i])));
    }
    m_length = genes.size();
}
//int Chromosome::CalculateCost(vector) {

//}

void Chromosome:: GetCode() {
    // for (vector<string>::iterator it = m_code.begin();it<m_code.end();++it) {
    //   cout<<*it<<endl;
    // }
}

int Chromosome:: CalcCost(vector<std::string> res) {
    int cost = 0;
    //for (vector<string>::iterator it = res.begin();it < res.end(); ++it) {
    for(int i = 0; i < res.size(); ++i) {
        cost += m_code[i].CalcCost(res[i]);
    }
    return cost;
}
