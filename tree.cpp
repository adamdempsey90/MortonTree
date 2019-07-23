#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#include <cmath>
#include <bitset>
#include <map>
//#include "morton.h"

#define BITSIZE 64

using uint = unsigned int;
template <size_t N>
using morton = std::bitset<N>;

template <size_t N>
class compare {
    public:
        bool operator()(const morton<N> &a, const morton<N> &b) const 
        {
            return a.to_ullong() < b.to_ullong();
        }

};

template <size_t N, typename value>
using Mesh = std::map<morton<N>, value *, compare<N>>; 

template <size_t N, typename value>
class Domain {

    protected:
    morton<N> root = 0;
    double xmin, xmax;
    double ymin, ymax;
    double zmin, zmax;

    private:
    Mesh<N,value> mesh;


    public:
    Domain()
};
