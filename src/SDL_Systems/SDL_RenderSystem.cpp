//
// Created by niels on 05/03/18.
//

#include "../../include/SDL_Systems/SDL_RenderSystem.h"

namespace SDL_Systems {

    SDL_RenderSystem::SDL_RenderSystem(World *world, int screen_width, int screen_height, Systems::TimerSystem *timer) :
            RenderSystem(world, screen_width, screen_height, timer) {
        // Initialze SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL not initialized! Error: " << SDL_GetError() << std::endl;
        } else {
            // Create the window
            window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                      screen_width, screen_height, SDL_WINDOW_SHOWN);
            if (window == nullptr) {
                std::cout << "Window could not be created! Error: " << SDL_GetError() << std::endl;
            } else {
                // Initialize renderer vsync: | SDL_RENDERER_PRESENTVSYNC
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                if (renderer == nullptr) {
                    std::cout << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
                } else {
                    if (SDL_RenderSetScale(renderer, 1, 1) < 0) {
                        std::cout << "Error setting renderer scale. Error: " << SDL_GetError() << std::endl;
                    } else {
                        // Initialize renderer color
                        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                        // Initialize image loader
                        int imgFlags = IMG_INIT_PNG;
                        if (!(IMG_Init(imgFlags) & imgFlags)) {
                            std::cout << "SDL_image failed to initialize! Error: " << IMG_GetError() << std::endl;
                        }

                        //Initialize SDL_ttf
                        if (TTF_Init() == -1) {
                            std::cout << "SDL_image failed to initialize! Error: " << TTF_GetError() << std::endl;
                        }
                    }
                }
            }
        }
    }

    void SDL_RenderSystem::update() {
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(renderer);

        std::map<entityID, Entity *> *to_render[2] = {&entities, &foreground};

        std::vector<Entity *> render_text;

        for (auto list : to_render) {
            for (auto it : *list) {
                auto e = it.second; // get entity
                if (e->hasComponentType(RENDER_COMPONENT)) {
                    auto *rc = e->getComponentByType<SDL_RenderComponent>(RENDER_COMPONENT);
                    if (rc->visible) {
                        SDL_Rect position = getPosition(e);

                        double x_offset = rc->x_render_offset * tile_width;
                        double y_offset = rc->y_render_offset * tile_width;
                        position.x = (int) (position.x - x_offset);
                        position.y = (int) (position.y - y_offset);

                        SDL_Rect clip = getClip(e);

                        position.w = (int) floor(clip.w * rc->scale);
                        position.h = (int) floor(clip.h * rc->scale);

                        if (e->hasComponentType(PLAYER_COMPONENT) || e->hasComponentType(TEXT_COMPONENT))
                            render_text.push_back(e);

                        SDL_RenderCopy(renderer, rc->texture, &clip, &position);
                    }
                }
            }
        }

        for (auto e : render_text) {
            if (e->hasComponentType(PLAYER_COMPONENT))
                renderPlayerComponent(e);

            if (e->hasComponentType(TEXT_COMPONENT))
                renderText(e);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_Rect SDL_RenderSystem::getPosition(Entity *e) {
        SDL_Rect position = SDL_Rect();
        if (e->hasComponentType(POSITION_COMPONENT)) {
            auto *p = e->getComponentByType<PositionComponent>(POSITION_COMPONENT);

            auto x = (int) floor(p->x * tile_width);
            auto y = (int) floor(p->y * tile_width);

            if (e->hasComponentType(MOVABLE_COMPONENT)) {
                auto *mc = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
                if (mc->state == MOVING && mc->animate) {
                    mc->time += 2.f / 1000.f; // timer.getTimerStep() / 1000.f for fps independent movement
                    //std::cout << "step: " << timer->getTimerStep() << std::endl;

                    double t = mc->time * mc->speed;

                    if (t >= 1) {
                        mc->time = 0;
                        t = 1;
                        mc->state = IDLE;
                    }

                    if (p->x - mc->x_prev != 0)
                        x = (int) (mc->x_prev * tile_width + (p->x - mc->x_prev) * t * tile_width);
                    if (p->y - mc->y_prev != 0)
                        y = (int) (mc->y_prev * tile_width + (p->y - mc->y_prev) * t * tile_width);
                }
            }

            position = {x + x_screen_offset, y + y_screen_offset, tile_width, tile_width};
        }
        return position;
    }

    SDL_Rect SDL_RenderSystem::getClip(Entity *e) {
        auto *rc = e->getComponentByType<SDL_RenderComponent>(RENDER_COMPONENT);
        SDL_Rect clip = SDL_Rect();
        if (!rc->clips.empty()) {
            if (rc->clips.size() != 1) {
                if (rc->count > rc->animation_speed) {
                    rc->current_frame = (rc->current_frame + 1) % rc->animation_length;
                    rc->count = 0;
                } else
                    rc->count++;
                if (e->hasComponentType(MOVABLE_COMPONENT)) {
                    auto *mc = e->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);

                    rc->frame_offset = rc->direction_offsets[mc->current_dir - 1];
                    if (e->hasComponentType(AI_COMPONENT)) {
                        auto *ac = e->getComponentByType<AIComponent>(AI_COMPONENT);
                        if (ac->state == FLEE)
                            rc->frame_offset = (int) rc->clips.size() - 10;
                        if (ac->state == RETURN)
                            rc->frame_offset = (int) rc->clips.size() - 8;
                    }

                    if (mc->current_dir != STOP)
                        clip = *rc->clips[rc->current_frame + rc->frame_offset];
                    else
                        clip = *rc->clips[0];
                } else
                    clip = *rc->clips[rc->current_frame];
            } else {
                clip = *rc->clips[0];
            }
        }
        return clip;
    }

    void SDL_RenderSystem::renderPlayerComponent(Entity *e) {
        auto *player_component = e->getComponentByType<SDL_PlayerComponent>(PLAYER_COMPONENT);

        std::ostringstream stringStream;
        stringStream << "Score: " << player_component->score;
        std::string score_text = stringStream.str();

        stringStream.clear();
        stringStream.str("");
        stringStream << "Lives: " << player_component->lives;
        std::string lives_text = stringStream.str();

        stringStream.clear();
        stringStream.str("");
        stringStream << player_component->level;
        std::string level_text = stringStream.str();

        player_component->score_texture->setText(score_text, *player_component->color);
        SDL_Texture *score = player_component->score_texture->getTexture();

        player_component->lives_texture->setText(lives_text, *player_component->color);
        SDL_Texture *lives = player_component->lives_texture->getTexture();

        player_component->level_texture->setText(level_text, *player_component->color);
        SDL_Texture *level = player_component->level_texture->getTexture();

        int w, h = 0;
        SDL_QueryTexture(score, nullptr, nullptr, &w, &h);
        SDL_Rect score_pos = {5 + x_screen_offset, world_height + y_screen_offset + 5, w, h};

        SDL_QueryTexture(lives, nullptr, nullptr, &w, &h);
        int test = world_width - w - 5 + x_screen_offset;
        SDL_Rect lives_pos = {test, world_height + y_screen_offset + 5, w, h};

        SDL_QueryTexture(level, nullptr, nullptr, &w, &h);
        int x = (world_width + 2 * x_screen_offset) / 2 - w / 2;
        SDL_Rect level_pos = {x, world_height + y_screen_offset + 5, w, h};

        SDL_RenderCopy(renderer, score, nullptr, &score_pos);
        SDL_RenderCopy(renderer, lives, nullptr, &lives_pos);
        SDL_RenderCopy(renderer, level, nullptr, &level_pos);
    }

    void SDL_RenderSystem::renderText(Entity *e) {
        auto *tc = e->getComponentByType<SDL_TextComponent>(TEXT_COMPONENT);

        tc->texture->setText(tc->text, *tc->color);

        SDL_Texture *text = tc->texture->getTexture();

        int w, h = 0;
        SDL_QueryTexture(text, nullptr, nullptr, &w, &h);
        int x = (world_width + 2 * x_screen_offset) / 2 - w / 2;
        int y = (world_height + 2 * y_screen_offset) / 2 - h / 2;
        SDL_Rect score_pos = {x, y, w, h};

        SDL_RenderCopy(renderer, text, nullptr, &score_pos);
    }

    void SDL_RenderSystem::addEntity(Entity *e) {
        if (e->hasComponentType(PLAYER_INPUT_COMPONENT) && !entityInSystem(e->id)) {
            foreground[e->id] = e;
            return;
        }
        if (e->hasComponentType(AI_COMPONENT) && !entityInSystem(e->id)) {
            foreground[e->id] = e;
            return;
        }
        System::addEntity(e);
    }

    void SDL_RenderSystem::removeEntity(entityID id) {
        if (foreground.find(id) != foreground.end()) {
            auto it = foreground.find(id);
            foreground.erase(it);
            return;
        }
        System::removeEntity(id);
    }

    bool SDL_RenderSystem::entityInSystem(entityID id) {
        if (foreground.find(id) != foreground.end())
            return true;
        return System::entityInSystem(id);
    }

    SDL_RenderSystem::~SDL_RenderSystem() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        window = nullptr;
        renderer = nullptr;
        IMG_Quit();
        SDL_Quit();
        TTF_Quit();
    }

};