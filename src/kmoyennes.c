#include <stdio.h>
#include "image.h"
#include "kmoyennes.h"
#include <math.h>


int main( int argc, const char** argv )
{ 
  Image im;
  int k;
  const char* f;
 

  if ( argc < 2 ) 
    {
      fprintf( stderr, "Usage: %s image [k]\n" , argv[0] );
      exit( EXIT_FAILURE );
    }
  f = argv[1];
  k = (argc < 3 ) ? 3 : atoi( argv[2] );
  (void) k; // cette ligne permet d'éviter un warning indiquant que la
            // variable $k$ n'est pas utilisée. À retirer.


  im_init( &im, f ); // construit l'image à partir d'un fichier
  black_white_image( &im );
 
  im_write( &im, "out.ppm" );
  im_free( &im );

  return 0;
}

bool is_dark(Color col){
  return col.r + col.g + col.b < 382;
}


void black_white_image( Image* im ){
  ImageIterator iter;
  Coord c;
  iter_init(im, &iter);

  while (! iter_ended(im, &iter)){
    c = iter_next(im, &iter);
    Color color = im_get(im, c);
    if (is_dark(color)){
      im_set(im, c, black);
    }
    else{
      im_set(im, c, white);
    }
  }
}

int indice_nearest(Color colorim, Array arr){
    ImageIterator iter;
    Coord c;
    iter_init(arr.array, &iter);
    float mindiff = 900.0;
    int indice = -1;
    while (! iter_ended(arr.array, &iter)){
        c = iter_next(arr.array, &iter);
        Color color = im_get(arr.array, c);
        float foo = (sqrtf((float)(colorim.b * colorim.b - color.b * color.b)) + sqrtf((float)(colorim.r * colorim.r - color.r * color.r)) + sqrtf((float)(colorim.g * colorim.g - color.g * color.g);
        if (foo < mindiff){
            mindiff = foo;
            indice = c;
        }
    }
    return indice;
}

Array create_groups( Image* im, Array arr ){
    ImageIterator iter;
    Coord c;
    iter_init(im, &iter);
    // new k
    Array newk;
    initArray(&newk,0);
    //color groups
    Array colorgroups;
    initArray(&colorgroups,arr.size);
}

void color_image( Image* im, int k ){
    Array array;
    initArray(&array, size);
    while ( array.size != create_groups(im, array).size ){

    }

}