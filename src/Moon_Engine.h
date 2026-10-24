#ifndef MOON_ENGINE_H
#define MOON_ENGINE_H

#include "raylib.h"

#define MAX_NAME_LEN 32
#define MAX_OBJECTS  128

typedef struct Category
{
    char name[MAX_NAME_LEN];
} Category;

typedef struct ObjectTransform
{
    float x, y, z;
} ObjectTransform;

typedef struct SpriteRenderer
{
    Texture2D sprite;   // albo int, jeśli na razie trzymasz tylko numer
    Color color;        // zamiast int, żeby od razu pasowało do raylib
} SpriteRenderer;

typedef struct GameObject
{
    int  ID;
    char name[MAX_NAME_LEN];
    int  visible;
    int  active;                 // do systemu dodawania (slot wolny/zajęty)

    ObjectTransform transform;   // pozycja obiektu
    SpriteRenderer  renderer;    // wygląd obiektu
} GameObject;

#endif