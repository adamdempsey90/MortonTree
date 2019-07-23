#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <bitset>
#include "morton.h"
#include "patch.h"

//using namespace std;
void print_binary(int bit) {

    char bitstr[33] = {0};
    for( int b = 0; b < 32; b++  ) {
        if(bit & (1 << (31-b))) bitstr[b] = '1';
        else  bitstr[b] = '0';
    }
    std::cout << bitstr << "\n";
}
//
//void depth_first(Patch *tree) {
//    /* Start at root */
//    unsigned int indx = 0;
//
//
//}
//
//unsigned int get_parent(unsigned int indx) {
//    // Take off last two bits 
//    return indx >> 2;
//} 
//unsigned int right_neighbor(unsigned int indx) {
//    /********
//     * 00 01 
//     * 10 11
//     * ******
//     */
//    // if 00 or 10 then right neighbor is 01 or 11
//    // return indx + 1
//    // if 01 or 11 then it is right neighbor of parent 00 10
//    // You go up until your parent is 00 or 10
//
//}
//unsigned int left_neighbor(unsigned int indx) {
//    /********
//     * 00 01 
//     * 10 11
//     * ******
//     */
//    // if 01 or 11 then right neighbor is 00 or 10
//    // return indx - 1
//    // if 00 or 10 then it is left neighbor of parent 01 11
//    // You go up until your parent is 11 or 01
//
//}
//
//void level_indices(unsigned short lvl, unsigned int *list) {
//    return;
//}
//
//
//void build_tree(unsigned short depth) {
//    unsigned short lvl;
//
//    unsigned int ntot = 0;
//    for(lvl=0; lvl <= depth; lvl++) ntot += pow(4,lvl);
//
//    bool *mask;
//    mask = new bool[ntot];
//    Patch *tree;
//    tree = new Patch[ntot];
//
//
//    
//
//    delete[] tree;
//    delete[] mask;
//    return;
//}
//

int main(int argc, char *argv[]) {

    int n[3];
    n[0] = (argc > 1) ? atoi(argv[1]) : 1;
    n[1] = (argc > 2) ? atoi(argv[2]) : 1;
    n[2] = (argc > 3) ? atoi(argv[3]) : 1;

    double ext[2] = {0., 1.};

    /*
    for(int i=0;i<3;i++) {
        std::cout << n[i] << " ";
    }
    std::cout << std::endl;
    */

    Patch *domain = new Patch(n,ext,ext,ext);
    //domain->print();
    //std::cout << domain->ntot << "\n";


    int depth = 4;
    int npatches = 0; 
    for(int lvl = 0; lvl <=depth; lvl++) {
        npatches += pow(4,lvl);
   //     std::cout << "Depth " << lvl << ", "<< npatches << " Patches, " << ", dynamic range: " << pow(2,lvl) << "\n";
    }

    std::cout << "Total patches: " << npatches  << "\n";

    bool *mask;
    mask = new bool[npatches];
    std::memset(mask,true,sizeof(bool)*npatches);


    //Patch *grid;
    //grid  = new Patch[npatches];


    //std::cout << sizeof(bool) << "\n";
    //std::cout << sizeof(Patch) << "\n";
    //std::cout << "Mask size: " << sizeof(bool)*npatches/1e6 << " MB\n";
    //std::cout << "unfilled hash size: " << sizeof(Patch)*npatches/1e6 << " MB\n";



    int cindx[4] = {0x00, 0x01, 0x02, 0x03};
    for(int i=0;i<4;i++) {
        std::cout << std::bitset<2>(cindx[i]) << "\n";
    }

    //int bit = cindx[1]; 
    //std::cout << std::bitset<4>(bit) << "\n";
    //bit |= cindx[2];
    //std::cout << std::bitset<4>(bit) << "\n";
    /*
    for(int i=0;i<4;i++) {
        bit = cindx[i] >> 1;
        std::cout << std::bitset<4>(bit) << "\n";
    }

    */


    unsigned int nx =  8;

    unsigned int *datx, *daty, *datz,*dat;
    datx = new unsigned int[nx*nx*nx];
    daty = new unsigned int[nx*nx*nx];
    datz = new unsigned int[nx*nx*nx];
    dat = new unsigned int[nx*nx*nx];
    
    unsigned int x,y,z,indx;
    unsigned int cmax = 0;
    for( z = 0 ; z < nx; z++) {
        std::cout << z << "\n";
        for(y = 0 ; y < nx; y++) {
            for(x = 0 ; x < nx; x++) {
                indx = index_from_coords(x,y,z);
                dat[indx] = indx;
                datx[indx] = x;
                daty[indx] = y;
                datz[indx] = z;
                //std::cout << "(" << x << ", " << y << "), " << indx << "\n";
            }
        }
    }

    unsigned int point[3] = {5,3,6};
    unsigned int ixp, iyp, izp, ixm, iym, izm; 


    /*
    indx = index_from_coords(point[0],point[1],point[2]);
    ixp  = index_from_coords(point[0]+1,point[1],point[2]);
    iyp  = index_from_coords(point[0],point[1]+1,point[2]);
    izp  = index_from_coords(point[0],point[1],point[2]+1);
    ixm  = index_from_coords(point[0]-1,point[1],point[2]);
    iym  = index_from_coords(point[0],point[1]-1,point[2]);
    izm  = index_from_coords(point[0],point[1],point[2]-1);

    std::cout << "(" << point[0]  << ", " << point[1]  << ", " << point[2]  << ")\n";
    std::cout << "(" << datx[ixp] << ", " << daty[ixp] << ", " << datz[ixp] << ")\n";
    std::cout << "(" << datx[iyp] << ", " << daty[iyp] << ", " << datz[iyp] << ")\n";
    std::cout << "(" << datx[izp] << ", " << daty[izp] << ", " << datz[izp] << ")\n";
    std::cout << "(" << datx[ixm] << ", " << daty[ixm] << ", " << datz[ixm] << ")\n";
    std::cout << "(" << datx[iym] << ", " << daty[iym] << ", " << datz[iym] << ")\n";
    std::cout << "(" << datx[izm] << ", " << daty[izm] << ", " << datz[izm] << ")\n";
    */

    std::ofstream myfile;
    myfile.open ("ex.txt");

    for(indx=0;indx<nx*nx*nx;indx++) {
        myfile << datx[indx];
        myfile << " " << daty[indx];
        myfile << " " << datz[indx];
        myfile << "\n";
        //std::cout << indx << "," << dat[indx] <<  ", (" << datx[indx] << ", " << datx[indx] << ")\n" ;
    }
    myfile.close();




    delete domain;
//    delete[] grid;
    delete[] mask;
    return 1;
}
