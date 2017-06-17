#include "Gene.h"
#include <cstdlib>
#include <sstream>


/*Gene<T>::Gene()
{
    construct();
}

Gene::Gene(int l) {
    m_len = l;
    construct();
}*/
template<class T>
Gene<T>::Gene(T code, int len) {
    m_code = code;
    m_len = len;
}

/*void Gene:: construct(){
    m_code = GenerRandGene(m_len);
}*/
template<typename T>
template<int s>
std::string Gene<T>::GenerRandGene(const char alleles[s],int len) {
    std::stringstream ss;

    for (int i = 0; i < len; ++i) {
        ss << alleles[rand() % (s - 1)];
    }
    return ss.str();
}


