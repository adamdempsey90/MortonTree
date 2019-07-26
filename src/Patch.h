
#define NP 32
#define NTP NP*NP
#define NGHX 2
#define real double

class Patch2D {
    /* Patches contain all information for 
     * evolving the fluid equations forward in 
     * time.
     * They are a fixed size determined by the problem/hardware
     * e.g. in 2D they can be 32^2 to fill 1 threadblock (1024 threads)
     * and in 3D they can be 8^3 (512 threads) or 10^3 (1000 threads).
     * These include the ghost cells.
     * 
     * Communication with other patches is done through the Domain class.
     * The Domain class also sets the boundary/initial conditions of
     * a patch.
     */

    private:
        real xm1[NP+1], xm2[NP+1];
        real xc1[NP], xc2[NP];
        real dx1[NP], dx2[NP];
        real cons[NTP*5];
        real prim[NTP*5];
        bool mask[NTP];
        real intenergy[NTP];
        real *scalars;


        real xmin, xmax, ymin, ymax;
    public:
        Patch2D();
        ~Patch2D();
        void fill_ghosts(); 
        void set_domain(real xmin, real xmax, real ymin, real ymax);
        void fill_arrays();
        void cons_to_prim();
        void prim_to_cons();

/* Copy data to/from device */
        void host_to_dev();
        void dev_to_host();

        real evolve(); // returns new dt 

        void integrate();



};
