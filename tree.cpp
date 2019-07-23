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
    uint maxlevel = 16;
    double dims = 3;
    double xmin, xmax;
    double ymin, ymax;
    double zmin, zmax;

    private:
    Mesh<N,value> mesh;


    public:
    Domain(double ext[6]);
    Domain(void);
    void get_neighbors(morton<N> key, morton<N> *list);
    void get_level(morton<N> key);
    void split(morton<N> key);
    void merge(morton<N> key);
};

template <size_t N, typename value>
Domain::Domain(void) {
    xmin = 0.;
    xmax = 0.;
    ymin = 0.;
    ymax = 0.;
    zmin = 0.;
    zmax = 0.;

    mesh.insert({0,nullptr});

}




