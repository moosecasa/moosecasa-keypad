#include "Game.h"

int main(int argc, char* argv[])
{
    struct CGame* game = calloc(1,sizeof(struct CGame));
    CGameInit(game);
    game->vt->LoadResources(game);
    #ifdef DEBUG
        game->vt->Init(game,"Testing",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,800,SDL_WINDOW_OPENGL);
    #else
        game->vt->Init(game,"Testing",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,800,SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_OPENGL);
    #endif

    while(game->vt->Running(game)){
        game->vt->HandleEvents(game);
        game->vt->Update(game);
        game->vt->Render(game);
    }

    game->vt->Clean(game);
    CGameDestroy(&game);
    return 0;
}