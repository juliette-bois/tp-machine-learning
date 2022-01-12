#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdlib.h>
#include <stdbool.h>

// Type décrivant une Color au format RGB.
typedef struct Color
{
  int r;
  int g;
  int b;
} Color;

// Type décrivant les coordonnées d'un pixel dans une image.
typedef struct Coord
{
  int x;
  int y;
} Coord;


// Type décrivant une Image.
typedef struct Image
{
  int w;
  int h;
  int maxIntensity;
  Color* data;
} Image;

// Type décrivant un itérateur sur les pixels d'une image.
typedef struct ImageIterator
{
  int x;
  int y;
} ImageIterator;

// Initialise une image à partir d'un fichier au format PPM.
void im_init( Image* im, const char* filename );

// Écrit une image dans un fichier
void im_write( Image* im, const char* filename );

// Libère la mémoire occupée par une image
void im_free( Image* im );

// Consulter/modifier un pixel.
Color im_get( Image* im, Coord pos );
void im_set( Image* im, Coord pos, Color c );

////////////////////////////////////////////////////
//
// Service d'itération sur les pixels s'une image.

// Initialisation.
void iter_init( Image* im, ImageIterator* it );

// Test si l'itérateur est terminé.
bool iter_ended( Image* im, ImageIterator* it );

// Retourne les coordonnées du prochain pixel et passe au suivant.
Coord iter_next( Image* im, ImageIterator* it );


////////////////////////////////////////////////////
//
// Fonctions utilitaires pour manipulers les Colors
//

// Test si deux Colors sont égales.
bool Color_equals( Color a, Color b );

// Retourne un entier représentant la "distance" entre deux Colors.
int Color_diff( Color a, Color b );

#endif

