#include <iostream>
#include "patch.h"

Patch::Patch() {
    nx = 1;
    ny = 1;
    nz = 1;
    ntot = nx*ny*nz;
    xmin = 0.;
    xmax = 1.;
    ymin = 0.;
    ymax = 1.;
    zmin = 0.;
    zmax = 1.;
    dx = (xmax-xmin)/(double)nx;
    dy = (ymax-zmin)/(double)ny;
    dz = (zmax-ymin)/(double)nz;
}

Patch::Patch(int n[3], double xlims[2], double ylims[2], double zlims[2]) {
    set_dims(n,xlims,ylims,zlims);
}
void Patch::set_dims(int n[3], double xlims[2], double ylims[2], double zlims[2]) {
    nx = n[0];
    ny = n[1];
    nz = n[2];
    ntot = nx*ny*nz;
    xmin = xlims[0];
    xmax = xlims[1];
    ymin = ylims[0];
    ymax = ylims[1];
    zmin = zlims[0];
    zmax = zlims[1];
    dx = (xmax-xmin)/(double)nx;
    dy = (ymax-zmin)/(double)ny;
    dz = (zmax-ymin)/(double)nz;
    return;
}
void Patch::create_fields(void) {
    xm = new double[nx+1];
    xc = new double[nx];
    ym = new double[ny+1];
    yc = new double[ny];
    zm = new double[nz+1];
    zc = new double[nz];
    for(int i=0;i<=nx;i++) {
        xm[i] = xmin + dx*i;
    }
    for(int i=0;i<nx;i++) {
        xc[i] = .5*(xm[i] + xm[i+1]); 
    }
    for(int i=0;i<=ny;i++) {
        ym[i] = ymin + dy*i;
    }
    for(int i=0;i<ny;i++) {
        yc[i] = .5*(ym[i] + ym[i+1]); 
    }
    for(int i=0;i<=nz;i++) {
        zm[i] = zmin + dz*i;
    }
    for(int i=0;i<nz;i++) {
        zc[i] = .5*(zm[i] + zm[i+1]); 
    }

    cons = new double[nx*ny*nz*5];
    prim = new double[nx*ny*nz*5];
    memset(cons, 0., ntot*sizeof(double)*5);
    memset(prim, 0., ntot*sizeof(double)*5);
}
Patch::~Patch() {
    delete xm;
    delete ym;
    delete zm;
    delete xc;
    delete yc;
    delete zc;
    delete cons;
    delete prim;
}
void Patch::print(void) { 
    std::cout << "(" << nx << "," << ny << "," << nz << ")\n"; 
    std::cout << "xm: (";
    for(int i=0; i<=nx;i++) {
        std::cout << xm[i] << ", ";
    }
    std::cout << ")\n";
    std::cout << "xc ";
    for(int i=0; i<nx;i++) {
        std::cout << xc[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "ym ";
    for(int i=0; i<=ny;i++) {
        std::cout << ym[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "yc ";
    for(int i=0; i<ny;i++) {
        std::cout << yc[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "zm ";
    for(int i=0; i<=nz;i++) {
        std::cout << zm[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "zc ";
    for(int i=0; i<nz;i++) {
        std::cout << zc[i] << ", ";
    }
    std::cout << std::endl;
}
