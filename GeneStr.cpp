#include "GeneStr.h"
#include "Gene.h"
#include <cmath>

GeneStr::GeneStr() {
    m_code = Gene<std::string>::GenerRandGene<size>(alleles,m_len);
    construct();
}

GeneStr::GeneStr(unsigned int len) {
    m_len = len;
    construct();
}
GeneStr::GeneStr(std::string code) {
    m_code = code;
    m_len = code.size();
}

void GeneStr:: construct(){
    m_code = Gene<std::string>::GenerRandGene<size>(alleles,m_len);
}

const char GeneStr::alleles[GeneStr::size] = "abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int GeneStr::CalcCost(std::string resGene) {
    int cost = 0;
    for(int i = 0; i < m_len; ++i) {
        cost += pow(((int)m_code[i] - (int)resGene[i]),2);
    }
    return cost;
}

void GeneStr::MutateStr(unsigned int probability)
{
    if(rand() % (100) < probability) {
        



    }

}
