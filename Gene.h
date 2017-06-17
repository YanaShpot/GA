#pragma once
#include <string>

template <class T>
class Gene
{

public:
    Gene(){}
    //Gene(int len);
    Gene(T code, int len);
    virtual ~Gene() = default;
    T GetCode(){
        return m_code;
    }
    int CalcCost();

protected:
    int m_len = 1;
    std::string m_code;
    //T GenerRandGene(int len);
    template<int i>
    std::string GenerRandGene(const char alleles[i],int len);

    //T construct();

};


#include "Gene_impl.hpp"
