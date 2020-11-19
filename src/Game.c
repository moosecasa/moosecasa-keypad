#include "Game.h"
#include "config/configuration.h"

struct internal{
    bool m_bRunning;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
};
static int Init(struct CGame* GameClass,const char* title, int xpos, int ypos, int width, int height, int flags)
{
    //attempt to initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        #ifdef DEBUG
        printf("SDL init success\n");
        #endif
        //init the window
        GameClass->vt->private->m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (GameClass->vt->private->m_pWindow != 0) //window init success
        { 
            #ifdef DEBUG
            printf("window creation success\n");
            #endif
            GameClass->vt->private->m_pRenderer = SDL_CreateRenderer(GameClass->vt->private->m_pWindow, -1, 0);
            if(GameClass->vt->private->m_pRenderer != 0) // renderer init success
            {
                SDL_SetRenderDrawColor(GameClass->vt->private->m_pRenderer, 255, 0, 0, 255);
            }
            else
            {   
                printf("Renderer init failed \n");
                return false;
            }
        }
        else
        {
            printf("window init fail \n");
            return false;
        }
    }
    else
    {
        printf("SDL init fail\n");
        return false;
    }
    #ifdef DEBUG
    printf("init success\n");
    #endif
    GameClass->vt->private->m_bRunning = true; // everything initiated successfully, start the main loop

    return true;        
}

bool Running(struct CGame* self)
{ 
    return self->vt->private->m_bRunning;
}

void Update(struct CGame* self)
{

}

void Render(struct CGame* self)
{
    SDL_RenderClear(self->vt->private->m_pRenderer); //clear the renderer to draw colour
    SDL_RenderPresent(self->vt->private->m_pRenderer); // draw to the screen
}

void HandleEvents(struct CGame* self)
{
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                self->vt->private->m_bRunning = false;
            break;
            default:
            break;
        }
    }
}

void LoadResources(struct CGame* self)
{
    struct Config* cfg = ParseConfig("config.cfg");
    free(cfg);
    cfg = NULL;
}

void Clean(struct CGame* self)
{
    #ifdef DEBUG
    printf("cleaning game\n");
    #endif
    SDL_DestroyWindow(self->vt->private->m_pWindow);
    SDL_DestroyRenderer(self->vt->private->m_pRenderer);
    SDL_Quit();
}

int CGameInit(struct CGame* GameClass){
    if(GameClass == NULL){
        GameClass = malloc(sizeof(struct CGame));
    }
    if(GameClass->vt == NULL){
        GameClass->vt = malloc(sizeof(struct GameVT));
    }
    if(GameClass->vt->private == NULL){
        GameClass->vt->private = malloc(sizeof(struct internal));
    }
    GameClass->vt->Init = &Init;
    GameClass->vt->Running = &Running;
    GameClass->vt->Update = &Update;
    GameClass->vt->Render = &Render;
    GameClass->vt->HandleEvents = &HandleEvents;
    GameClass->vt->Clean = &Clean;
    GameClass->vt->LoadResources = &LoadResources;
    GameClass->vt->private->m_bRunning = false;
    
    return true;
}

int CGameDestroy(struct CGame** GameClass)
{
    if(GameClass == NULL)
    {return false;}
    if((*GameClass) != NULL){
        if((*GameClass)->vt != NULL)
        {
            if((*GameClass)->vt->private != NULL){
                free((*GameClass)->vt->private);
                (*GameClass)->vt->private = NULL;
            }
            free((*GameClass)->vt);
            (*GameClass)->vt = NULL;
        }
        free((*GameClass));
        (*GameClass) = NULL;
    }
    return true;
}

