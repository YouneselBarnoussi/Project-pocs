#include <iomanip>
#include <Box2D/Box2D.h>
#include <iostream>
#include <SDL.h>

b2World* world;

const int MET2PIX = 80; // 640 / 80 = 8

const int WIDTH = 640;
const int HEIGHT = 480;

const int SCALED_WIDTH = WIDTH / MET2PIX; // 4 | 3
const int SCALED_HEIGHT = HEIGHT / MET2PIX;

using namespace std;

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("FirstGame", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    world = new b2World(b2Vec2(0.0f, 9.81f));

    // cartesian origin
    float ground_x = 0.0f;
    float ground_y = 0.0f;

    // start ground point
    b2Vec2 startpoint;
    startpoint.x = -1.5f;
    startpoint.y = 0;

    // end ground point
    b2Vec2 endpoint;
    endpoint.x = 1.5;
    endpoint.y = 0;

    // LineGround
    b2BodyDef myGroundDef;
    myGroundDef.type = b2_staticBody;
    myGroundDef.position.Set(ground_x, ground_y); // set the starting position x and y cartesian
    myGroundDef.angle = 0;

    b2Body* groundLineBody = world->CreateBody(&myGroundDef);

    b2EdgeShape edgeShape;
    edgeShape.SetTwoSided( startpoint, endpoint ); // length -> coordinate vector from to vector

    b2FixtureDef edgeFixtureDef;
    edgeFixtureDef.shape = &edgeShape;
    groundLineBody->CreateFixture(&edgeFixtureDef);

    SDL_Surface* tmp_sprites = SDL_CreateRGBSurface(0, 50, 50, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);;

    if(!tmp_sprites)
        return EXIT_FAILURE;

    SDL_Texture* texture_box = SDL_CreateTextureFromSurface(renderer, tmp_sprites);
    SDL_FreeSurface(tmp_sprites);

    // cartesian origin box
    float x_box = 0;
    float y_box= 2.5f;

    // size of box
    float w_box = 0.5;
    float h_box = 0.5;

    // Box
    SDL_Rect box;
    b2Body* Body;

    b2BodyDef boxBodyDef;
    boxBodyDef.type = b2_dynamicBody;
    boxBodyDef.angle = 45;
    boxBodyDef.position.Set(x_box, y_box);

    Body = world->CreateBody(&boxBodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(w_box / 2.0f, h_box / 2.0f); // will be 0.5 x 0.5

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;
    Body->CreateFixture(&fixtureDef);

    // box: convert Metres back to Pixels for width and height
    box.w = w_box * MET2PIX;
    box.h = h_box * MET2PIX;

    // point to center of box for angle
    SDL_Point center;
    center.x = box.w * 0.5f;
    center.y = box.h - (box.w * 0.5);

    bool close_game = false;
    SDL_Event event;

    // The game Loop
    while(close_game != true)
    {
        b2Vec2 pos = Body->GetPosition(); // Body = Body from box
        float angle = Body->GetAngle();

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                close_game = true;

            else if(event.key.keysym.sym == SDLK_ESCAPE)
                close_game = true;
        }

        box.x = ((SCALED_WIDTH / 2.0f) + pos.x) * MET2PIX;
        box.y = (-(SCALED_HEIGHT / 2.0f) + pos.y) * MET2PIX;

        cout << "X of box:" << setprecision(20) << box.x << endl;
        cout << "Y of box:" << setprecision(20) << box.y << endl;

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);

        // Draw ground platform
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
        SDL_RenderDrawLine(renderer, ((SCALED_WIDTH / 2.0f) + edgeShape.m_vertex1.x) * MET2PIX, ((SCALED_HEIGHT / 2.0f) + edgeShape.m_vertex1.y) * MET2PIX, ((SCALED_WIDTH / 2.0f) + edgeShape.m_vertex2.x) * MET2PIX, ((SCALED_HEIGHT / 2.0f) + edgeShape.m_vertex2.y) * MET2PIX);

        // Draw our Box
        SDL_RenderCopyEx(renderer, texture_box, NULL, &box, angle, &center, SDL_FLIP_NONE);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);

        world->Step(1.0f / 60.0f, 6.0f, 2.0f); // update

    }

    delete world;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}