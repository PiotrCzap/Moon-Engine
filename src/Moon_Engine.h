#ifndef MOON_ENGINE_H
#define MOON_ENGINE_H

#include "raylib.h"

#define MAX_NAME_LEN 32
#define MAX_OBJECTS  128

// ======================================================================
// Components
// ======================================================================

typedef struct ObjectTransform
{
    float pos_x, pos_y, pos_z;
    float size_x, size_y, size_z;
} ObjectTransform;

typedef struct SpriteRenderer
{
    int graphic;
    Texture2D sprite;   // albo int, jeśli na razie trzymasz tylko numer
    Color color;        // zamiast int, żeby od razu pasowało do raylib
} SpriteRenderer;


typedef struct Category
{
    const char name[MAX_NAME_LEN];
} Category;

typedef struct GameObject
{
    int ID;
    char name[MAX_NAME_LEN];
    int visible;
    int active;

    ObjectTransform transform;
    SpriteRenderer renderer;
} GameObject;



#endif