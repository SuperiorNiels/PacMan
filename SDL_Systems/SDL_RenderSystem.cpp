//
// Created by niels on 05/03/18.
//

#include <sstream>
#include "SDL_RenderSystem.h"

SDL_RenderSystem::SDL_RenderSystem(World* world, int screen_width, int screen_height, TimerSystem* timer) :
        RenderSystem(world,screen_width,screen_height,timer)
{
    component_types = {RENDER_COMPONENT};

    // Initialze SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL not initialized! Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        // Create the window
        window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  screen_width, screen_height, SDL_WINDOW_SHOWN);
        if(window == nullptr)
        {
            std::cout << "Window could not be created! Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            // Initialize renderer vsync: | SDL_RENDERER_PRESENTVSYNC
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer == nullptr)
            {
                std::cout << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
            }
            else
            {
                if(SDL_RenderSetScale(renderer,1,1) < 0)
                {
                    std::cout << "Error setting renderer scale. Error: " << SDL_GetError() << std::endl;
                }
                else
                {
                    // Initialize renderer color
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                    // Initialize image loader
                    int imgFlags = IMG_INIT_PNG;
                    if (!(IMG_Init(imgFlags) & imgFlags))
                    {
                        std::cout << "SDL_image failed to initialize! Error: " << IMG_GetError() << std::endl;
                    }

                    //Initialize SDL_ttf
                    if(TTF_Init() == -1)
                    {
                        std::cout << "SDL_image failed to initialize! Error: " << TTF_GetError() << std::endl;
                    }
                }
            }
        }
    }
}

void SDL_RenderSystem::update()
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);

    for (auto &e : entities)
    {
        if (e->hasComponentTypes({POSITION_COMPONENT, RENDER_COMPONENT}))
        {
            auto *rc = e->getComponentByType<SDL_RenderComponent>(RENDER_COMPONENT);
            if (rc->visible)
            {
                SDL_Rect position = getPosition(e);

                //renderBox(&position,e);

                double x_offset = rc->x_render_offset*tile_width;
                double y_offset = rc->y_render_offset*tile_width;
                position.x = (int) (position.x - x_offset);
                position.y = (int) (position.y - y_offset);

                SDL_Rect clip = getClip(e);

                position.w = (int) floor(clip.w * rc->scale);
                position.h = (int) floor(clip.h * rc->scale);

                if(e->hasComponentType(SCORE_COMPONENT))
                    renderScore(e);

                if(e->hasComponentType(LIVES_COMPONENT))
                    renderLives(e);

                SDL_RenderCopy(renderer, rc->texture, &clip, &position);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

SDL_Rect SDL_RenderSystem::getPosition(Entity *e)
{
    SDL_Rect position = SDL_Rect();
    if(e->hasComponentType(POSITION_COMPONENT))
    {
        auto *p = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);

        auto x = (int) floor(p->x * tile_width);
        auto y = (int) floor(p->y * tile_width);

        if(e->hasComponentType(MOVABLE_COMPONENT))
        {
            auto* mc = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            if(mc->state == MOVING)
            {
                mc->time += 1.f / 1000.f; // timer.getTimerStep() / 1000.f for fps independent movement

                double t = mc->time / mc->speed;

                if(t >= 1)
                {
                    mc->time = 0;
                    t = 1;
                    mc->state = IDLE;
                }

                if(p->x - mc->x_prev != 0)
                    x = (int) (mc->x_prev * tile_width + (p->x - mc->x_prev) * t * tile_width);
                if(p->y - mc->y_prev != 0)
                    y = (int) (mc->y_prev * tile_width + (p->y - mc->y_prev) * t * tile_width);
            }
        }

        position = {x + x_screen_offset, y + y_screen_offset, tile_width, tile_width};
    }
    return position;
}

SDL_Rect SDL_RenderSystem::getClip(Entity *e)
{
    auto *rc = e->getComponentByType<SDL_RenderComponent>(RENDER_COMPONENT);
    SDL_Rect clip = SDL_Rect();
    if (!rc->clips.empty())
    {
        clip = *rc->clips[0];
        /*if (e->hasComponentType(MOVABLE_COMPONENT))
        {
            auto *m = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
            rc->frame_offset = rc->direction_offsets[m->current_dir-1];
            if (m->state == MOVING)
                clip = *rc->clips[rc->current_frame + rc->frame_offset];
            // TODO: animation check!!!!
        }
        if (rc->count > rc->animation_speed)
        {
            rc->current_frame = (rc->current_frame + 1) % rc->animation_length;
            rc->count = 0;
        }
        else
            rc->count++;*/
    }
    return clip;
}

void SDL_RenderSystem::renderScore(Entity *e)
{
    auto* sc = e->getComponentByType<SDL_ScoreComponent>(SCORE_COMPONENT);
    SDL_Color text_color = {0xff,0xff,0xff,0};

    std::ostringstream stringStream;
    stringStream << "Score: " << sc->score;
    std::string score_text = stringStream.str();

    sc->texture->setText(score_text, text_color);
    SDL_Texture* text = sc->texture->getTexture();

    int w, h = 0;
    SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
    SDL_Rect score_pos = {5 + x_screen_offset, world_height + y_screen_offset + 5, w , h};

    SDL_RenderCopy(renderer,text, nullptr, &score_pos);
}

void SDL_RenderSystem::renderLives(Entity *e)
{
    auto* lc = e->getComponentByType<SDL_LivesComponent>(LIVES_COMPONENT);

    SDL_Color text_color = {0xff,0xff,0xff,0};

    std::ostringstream stringStream;
    stringStream << "Lives: " << lc->lives;
    std::string lives_text = stringStream.str();

    lc->text->setText(lives_text, text_color);

    SDL_Texture* text = lc->text->getTexture();

    int w, h = 0;
    SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
    int test = world_width - w - 5 + x_screen_offset;
    SDL_Rect score_pos = {test, world_height + y_screen_offset + 5, w , h};

    SDL_RenderCopy(renderer,text, nullptr, &score_pos);
}

void SDL_RenderSystem::renderBox(SDL_Rect* box, Entity* e)
{
    if(e->hasComponentType(AI_COMPONENT))
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
        SDL_RenderDrawRect(renderer, box);
    }
    else if(e->hasComponentType(PLAYER_INPUT_COMPONENT))
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
        SDL_RenderFillRect(renderer, box);
    }
    else if(e->hasComponentType(POINTS_COMPONENT))
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xAB, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, box);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer, box);
    }
}

SDL_RenderSystem::~SDL_RenderSystem()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;
    IMG_Quit();
    SDL_Quit();
}