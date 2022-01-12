#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "image.h"


#define TAILLETAMPON 256

void im_init( Image* im, const char* filename )
{

  int i,n;
  int r,g,b;
  char tampon[ TAILLETAMPON ];
  char tmpname[ TAILLETAMPON ];
  FILE* f;
  int retCode;

  size_t l = strlen( filename );
  if ( strcmp( filename+l-3, "ppm" ) != 0 )
    {
      // on regarde si la fonction ``convert`` est installée
      retCode = system( "which convert 2>/dev/null" );
      if ( retCode == 0 )
        {
          printf( "# Conversion au format ppm\n" );
          strcpy( tmpname, filename );
          strcpy( tmpname+l-3, "ppm" );
          //sprintf( tampon, "convert %s -compress none %s", filename, tmpname );
          system( tampon );
          filename = tmpname;
          printf( "# Fichier ``%s`` créé.\n", filename );
        }
      else
        {
          fprintf( stderr, "Format du ficher \'%s\' non géré, utilisez .ppm\n", filename );
          exit( EXIT_FAILURE );
        }
    }



  // Ouverture du fichier et vérification du format.
  f = fopen( filename, "r" );
  fgets( tampon, TAILLETAMPON, f );
  if ( tampon[0] != 'P' || tampon[1] != '3' )
    {
      fclose( f );
      fprintf( stderr, "Fichier %s invalide\n", filename );
      exit( EXIT_FAILURE );
    }

  // Lecture des caractéristiques de l'image.
  // Le format étant relativement flexible, c'est la partie la plus compliquée à
  // parser !
  im->w = 0;
  im->h = 0;
  im->maxIntensity = 0;
  while ( im->maxIntensity == 0 )
    {
      tampon[0] = '#';
      while ( tampon[0] == '#' )
        {
          fgets( tampon, TAILLETAMPON, f );
        }

      char* token = strtok( tampon, " " );
      while ( token )
        {
          //printf( "w=%d, h=%d, m=%d, s=%s\n", im->w, im->h, im->maxIntensity, token );
          if ( im->w == 0 ) 
            {
              im->w = atoi( token );
            }
          else if ( im->h == 0 )
            {
              im->h = atoi( token );
            }
          else if ( im->maxIntensity == 0 )
            {
              im->maxIntensity = atoi( token );
            } 
          token = strtok( NULL, " " );
          //printf( "token = %s\n", token );
        }
    }
  printf( "# Format de l'image : %dx%d\n", im->w, im->h );

  // Lecteur des Colors des pixels
  im->data = (Color*) malloc( im->w * im->h * sizeof( Color ) );
  n = im->w * im->h;
  for ( i=0; i<n; ++i )
    {
      fscanf( f, "%d", &r );
      fscanf( f, "%d", &g );
      fscanf( f, "%d", &b );
      fflush( f );
      im->data[i].r = r;
      im->data[i].g = g;
      im->data[i].b = b;
      //printf( "# pixel %d : %d %d %d \n", i, r, g, b );
    }
  fclose( f );
}

void im_write( Image* im, const char* filename )
{
  int i, n;
  FILE* f = fopen( filename, "w" );
  fprintf( f, "P3\n" );
  fprintf( f, "%d %d %d\n", im->w, im->h, im->maxIntensity );
  n = im->w * im->h;
  for ( i=0; i<n; ++i )
    {
      fprintf( f, "%d %d %d\n", im->data[i].r, im->data[i].g, im->data[i].b );
    }
  fclose( f );
}

void im_free( Image* im )
{
  free( im->data );
}

Color im_get( Image* im, Coord pos )
{
  int i = ( im->w * pos.y ) + pos.x;
  return im->data[ i ];
}

void im_set( Image* im, Coord pos, Color c )
{
  int i = ( im->w * pos.y ) + pos.x;
  im->data[ i ] = c;
}

void iter_init( Image* im, ImageIterator* it )
{
  (void) im;
  it->x = 0;
  it->y = 0;
}

bool iter_ended( Image* im, ImageIterator* it )
{
  return it->y == im->h;
}

Coord iter_next( Image* im, ImageIterator* it )
{
  Coord c;
  c.x = it->x;
  c.y = it->y;
  it->x += 1;
  if ( it->x == im->w )
    {
      it->x = 0;
      it->y += 1;
    }
  return c;
}


bool Color_equals( Color a, Color b )
{
  return ( a.r == b.r ) && ( a.g == b.g ) && ( a.b == b.b );
}

int Color_diff( Color a, Color b )
{
  int dr, dg, db;
  dr = a.r - b.r;
  dg = a.g - b.g;
  db = a.b - b.b;
  return dr*dr + dg*dg + db*db;
}


