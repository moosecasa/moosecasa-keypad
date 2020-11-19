#ifndef __GAME_H__
#define __GAME_H__
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
typedef struct CGame{
    struct GameVT* vt;    
} tGame;

typedef struct GameVT
{
    int (*Init)(struct CGame *self, const char* title, int xpos, int ypos, int width, int height, int flags);
    bool (*Running)(struct CGame *self);
    void (*Update)(struct CGame *self);
    void (*Render)(struct CGame *self);
    void (*HandleEvents)(struct CGame *self);
    void (*LoadResources)(struct CGame *self);
    void (*Clean)(struct CGame *self);
    struct internal *private;
} vtGame;


int CGameInit(struct CGame *self);
int CGameDestroy(struct CGame **self);


#endif //end __GAME_H__