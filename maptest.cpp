#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#include <cmath>
#include <bitset>
#include <map>


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

#define SIZE 8


class Cell {
    double value;
    bool leaf ;
    bool refine = false;

    public:
    Cell(double a) {value = a; leaf=true;};
    double get_value(void) {return value;}
    void set_value(double a) {value = a;};
    bool get_leaf(void) {return leaf;}
    bool get_refine(void) {return refine;}
    void off(void) {refine = false;};
    void on(void) {refine = true;};
};

template<size_t N>
uint key_to_level(morton<N> key) {
    uint lvl = 0;
    
    for(uint i=SIZE-3; i>=1; i-=2) {
        if (key[i] == false && key[i-1]==false) {
            return lvl;
        }
        else {
            lvl += 1;
        }

    }

    return lvl;
}
template<size_t N, typename mtype>
void split(morton<N> key, Mesh<N,mtype> *mesh) {

    uint level = key_to_level(key);
    std::cout << "Splitting " << key.to_string() << ", level " << level << "\n";

    level += 1;
    uint offset = SIZE - 2*level;

    Cell *child = mesh->at(key);
    child->off();
    double value = child->get_value();

    value /= 4;

    child->set_value(value);

    child = new Cell(value);
    key.flip(offset-1);
    mesh->insert({key, child});

    child = new Cell(value);
    key.flip(offset-1); key.flip(offset-2);
    mesh->insert({key, child});

    child = new Cell(value);
    key.flip(offset-1);
    mesh->insert({key, child});
    return;
}

void print_mesh(Mesh<SIZE,Cell> mesh) {
    Cell *curr;
    Mesh<SIZE,Cell>::iterator it;
    for (it=mesh.begin(); it!=mesh.end(); ++it) {
        curr = it->second;
        if (curr->get_leaf()) {
            std::cout << it->first << " => " << curr->get_value() << '\n';
        }
    }
}

int main(int argc, char *argv[]) {
    morton<SIZE> key;

    Mesh<SIZE, Cell> mesh;

    Cell *val = new Cell(1.);
    mesh.insert({key,val});

    val = new Cell(10.);
    key.flip(SIZE-1);
    mesh.insert({key, val});


    val = new Cell(4.);
    key.flip(SIZE-1); key.flip(SIZE-2);
    mesh.insert({key, val});


    val = new Cell(20.);
    key.flip(SIZE-1); 
    mesh.insert({key, val});

    std::cout << "Before split\n";
    print_mesh(mesh);

    std::cout << "After first split\n";

    Mesh<SIZE,Cell>::iterator it;
    for (it=mesh.begin(); it!=mesh.end(); ++it) {
        it->second->on();
    }

    for (it=mesh.begin(); it!=mesh.end(); ++it) {
        if (it->second->get_refine()) {
            split(it->first, &mesh);
        }
    }

    std::cout << "After second split\n";
    for (it=mesh.begin(); it!=mesh.end(); ++it) {
        it->second->on();
    }

    for (it=mesh.begin(); it!=mesh.end(); ++it) {
        if (it->second->get_refine()) {
            split(it->first, &mesh);
        }
    }

    print_mesh(mesh);



        



}
