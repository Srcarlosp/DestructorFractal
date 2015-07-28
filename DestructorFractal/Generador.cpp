#include "Generador.h"
#include "Constantes.h"
#include "ziggurat.h"

circle * randGenerator(float mu, float sigma)
{
    //////pseudorandom normal distributed float between 0 and 1//////
    //Implementation of the Zigurat algorithm
    float fn[128];
    int i;
    uint32_t kn[128];
    uint32_t seed;
    float wn[128];
    
    circle *list_circles = new circle[NUM_CIRCLES];
    
    //pseudorandom initialization
    time_t t;
    
    srand((unsigned) time(&t));
    r4_nor_setup ( kn, fn, wn );
    
    //pseudorandom seed
    seed = rand();
    
    for (i = 0; i < NUM_CIRCLES; i++) {

        //Truncated normal distribution between 0 and 0.25 for the radius
        do{
            num = r4_nor ( &seed, kn, fn, wn );
            list_circles[i].radius = ( sigma * num ) + mu;

        }while(num > 0 && num < 0.25);
        
        //Uniform distribution between 0 and 1 for the centers
        list_circles[i].center.x = r4_uni ( &seed );
        list_circles[i].center.y = r4_uni ( &seed ); 
        //printf ( " %14f\t%14f\n%14f\n", list_circles[i].radio, list_circles[i].center.x, list_circles[i].center.y );
    }
    
    return list_circles;
}