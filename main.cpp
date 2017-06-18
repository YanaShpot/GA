#include <iostream>
#include <sstream>
#include <string>
#include <genestr.h>
#include <vector>
#include "Chromosome.h"
using namespace std;


int main(int argc, char *argv[])
{

    vector<string> v;
    string myArr[] = {"Hello, World!"};
    v.insert(v.begin(),myArr,myArr+12);
    GeneStr* genestr = new GeneStr("Hello world!");
    cout<<genestr->CalcCost("Hello world!")<<endl;

    delete genestr;

    Chromosome* chr = new Chromosome(v);
    cout<<chr->CalcCost(v);

    // std::string s = "Hello world!";
    //cout<<(int)s[0]<<endl;



    return 0;
}
