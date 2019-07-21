#include "morton.h"

class Patch {
    double xmin, xmax;
    double ymin, ymax;
    double zmin, zmax;
    double dx, dy, dz;
    double *xm,*ym,*zm;
    double *xc,*yc,*zc;
    double *cons, *prim;
public:
    int nx,ny,nz, ntot;
    unsigned int gindx, lindx;
public:
    Patch(void);
    Patch(int n[3], double xlims[2], double ylims[2], double zlims[2]);
    ~Patch(void);
    void print(void);
    void set_dims(int n[3], double xlims[2], double ylims[2], double zlims[2]);
    void create_fields(void);
    void set_glindx(void);
    void get_glindx(void);
};
