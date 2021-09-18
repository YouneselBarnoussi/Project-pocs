#include <chrono>
#include <string>
#include <Box2D/Box2D.h>
#include <iostream>
#include <SDL.h>

using namespace std;

int main(int argc, char *args[]) {

    //Utility
    const float HALF = 0.5f;
    const float DOUBLE = 2.0f;
    const float INVERT = -1.0f;
    const float FRAMES_PER_SECOND = 60.0f;

    //Box2D
    const int PHYSICS_POSITION_ITERATIONS = 8;
    const int PHYSICS_VELOCITY_ITERATIONS = 12;

    const float WORLD_UNIT = 2.0f;
    const float WORLD_WIDTH = 80.0f;
    const float WORLD_HEIGHT = 60.0f;
    const float WORLD_TIME_RESOLUTION = 1.0f / FRAMES_PER_SECOND;
    const float WORLD_TIME_ELAPSED_ZERO = 0.0f;
    const float WORLD_GRAVITY_ZERO = 0.0f;
    const float WORLD_SLOW_MOTION_FACTOR = 10.0f;

    //SDL
    const float SCREEN_WIDTH = 1280;
    const float SCREEN_HEIGHT = 720;
    const char *SCREEN_TITLE = "POC Box2D C++";

    const float PIXELS_PER_METER_X = SCREEN_WIDTH / WORLD_WIDTH;
    const float PIXELS_PER_METER_Y = SCREEN_HEIGHT / WORLD_HEIGHT;

    const unsigned char COLOR_TERMINALGREEN_R = 64;
    const unsigned char COLOR_TERMINALGREEN_G = 192;
    const unsigned char COLOR_TERMINALGREEN_B = 64;
    const unsigned char COLOR_TERMINALGREEN_A = 255;

    const unsigned char COLOR_BLACK_R = 0;
    const unsigned char COLOR_BLACK_G = 0;
    const unsigned char COLOR_BLACK_B = 0;
    const unsigned char COLOR_BLACK_A = 255;

    const string TEXT_MESSAGE_BOTTOM = "(S)low Debug (P)ause (ESC)ape";

    //Box2D
    const float BODY_DENSITY_PERFECT_SOLID = 1.0f;
    const float BODY_RESTITUTION_PERFECT_BOUNCE = 1.0f;
    const float BODY_FRICTION_ZERO = 0.0f;
    const float BODY_DAMPING_ZERO = 0.0f;
    const float BODY_MASS_ZERO = 0.0f;

    const float BALL_RADIUS = WORLD_UNIT * HALF;
    const float BALL_START_POSITION_X = 4.0f;
    const float BALL_START_POSITION_Y = -30.0f;
    const float BALL_START_VELOCITY_X = 40.0f;
    const float BALL_START_VELOCITY_Y = 0.0f;
    const float BALL_NUDGE_FACTOR = 12.0f;

    const float WALL_THICKNESS = WORLD_UNIT;

    b2Vec2 *gravity = new b2Vec2(WORLD_GRAVITY_ZERO, WORLD_GRAVITY_ZERO);
    b2World *world = new b2World(*gravity);
    world->SetContinuousPhysics(true);


    //Ball
    b2BodyDef *ballBodyDef = new b2BodyDef();
    ballBodyDef->type = b2_dynamicBody;
    ballBodyDef->position.Set(BALL_START_POSITION_X, BALL_START_POSITION_Y);
    ballBodyDef->linearVelocity.Set(BALL_START_VELOCITY_X, BALL_START_VELOCITY_Y);

    b2MassData *ballBodyMassData = new b2MassData();
    ballBodyMassData->mass = BODY_MASS_ZERO;

    b2Body *ballBody = world->CreateBody(ballBodyDef);
    ballBody->SetBullet(true);
    ballBody->SetMassData(ballBodyMassData);
    ballBody->SetLinearDamping(BODY_DAMPING_ZERO);

    b2CircleShape *ballFixtureShape = new b2CircleShape();
    ballFixtureShape->m_radius = BALL_RADIUS;

    b2FixtureDef *ballFixtureDef = new b2FixtureDef();
    ballFixtureDef->shape = ballFixtureShape;
    ballFixtureDef->density = BODY_DENSITY_PERFECT_SOLID;
    ballFixtureDef->restitution = BODY_RESTITUTION_PERFECT_BOUNCE;
    ballFixtureDef->friction = BODY_FRICTION_ZERO;

    //Right Wall
    b2BodyDef *wallRightBodyDef = new b2BodyDef();
    wallRightBodyDef->type = b2_staticBody;
    wallRightBodyDef->position.Set(WORLD_WIDTH - (WORLD_UNIT * HALF), (WORLD_HEIGHT * HALF) * INVERT);

    b2Body *wallRightBody = world->CreateBody(wallRightBodyDef);

    b2PolygonShape *wallRightFixtureShape = new b2PolygonShape();
    wallRightFixtureShape->SetAsBox(WALL_THICKNESS, WORLD_HEIGHT);

    b2FixtureDef *wallRightFixtureDef = new b2FixtureDef();
    wallRightFixtureDef->shape = wallRightFixtureShape;
    wallRightFixtureDef->density = BODY_DENSITY_PERFECT_SOLID;

    b2Fixture *wallRightFixture = wallRightBody->CreateFixture(wallRightFixtureDef);

    //Left Wall
    b2BodyDef *wallLeftBodyDef = new b2BodyDef();
    wallLeftBodyDef->type = b2_staticBody;
    wallLeftBodyDef->position.Set(WORLD_UNIT * HALF, (WORLD_HEIGHT * HALF) * INVERT);

    b2Body *wallLeftBody = world->CreateBody(wallLeftBodyDef);

    b2PolygonShape *wallLeftFixtureShape = new b2PolygonShape();
    wallLeftFixtureShape->SetAsBox(WALL_THICKNESS, WORLD_HEIGHT);

    b2FixtureDef *wallLeftFixtureDef = new b2FixtureDef();
    wallLeftFixtureDef->shape = wallLeftFixtureShape;
    wallLeftFixtureDef->density = BODY_DENSITY_PERFECT_SOLID;

    b2Fixture *wallLeftFixture = wallLeftBody->CreateFixture(wallLeftFixtureDef);

    //Top Wall
    b2BodyDef *wallTopBodyDef = new b2BodyDef();
    wallTopBodyDef->type = b2_staticBody;
    wallTopBodyDef->position.Set(WORLD_WIDTH * HALF, (WORLD_UNIT * HALF) * INVERT);

    b2Body *wallTopBody = world->CreateBody(wallTopBodyDef);

    b2PolygonShape *wallTopFixtureShape = new b2PolygonShape();
    wallTopFixtureShape->SetAsBox(WORLD_WIDTH, WALL_THICKNESS);

    b2FixtureDef *wallTopFixtureDef = new b2FixtureDef();
    wallTopFixtureDef->shape = wallTopFixtureShape;
    wallTopFixtureDef->density = BODY_DENSITY_PERFECT_SOLID;

    b2Fixture *wallTopFixture = wallTopBody->CreateFixture(wallTopFixtureDef);

    //Bottom Wall
    b2BodyDef wallBottomBodyDef;
    wallBottomBodyDef.type = b2_staticBody;
    wallBottomBodyDef.position.Set(WORLD_WIDTH * HALF, (WORLD_HEIGHT - (WORLD_UNIT * HALF)) * INVERT);

    b2Body *wallBottomBody = world->CreateBody(&wallBottomBodyDef);

    b2PolygonShape wallBottomFixtureShape;
    wallBottomFixtureShape.SetAsBox(WORLD_WIDTH, WALL_THICKNESS);

    b2FixtureDef wallBottomFixtureDef;
    wallBottomFixtureDef.shape = &wallBottomFixtureShape;
    wallBottomFixtureDef.density = BODY_DENSITY_PERFECT_SOLID;

    wallBottomBody->CreateFixture(&wallBottomFixtureDef);

    //Ball Sprite
    float ballShapeRadius = ballBody->GetFixtureList()[0].GetShape()->m_radius;
    SDL_Rect *ballSprite = new SDL_Rect();
    ballSprite->x = ballBody->GetPosition().x * PIXELS_PER_METER_X;
    ballSprite->y = ballBody->GetPosition().y * PIXELS_PER_METER_Y * INVERT;
    ballSprite->w = (int) (ballShapeRadius * DOUBLE * PIXELS_PER_METER_X);
    ballSprite->h = (int) (ballShapeRadius * DOUBLE * PIXELS_PER_METER_Y);

    //Right Wall Sprite
    b2Vec2 *wallRightBodyVertice = &(((b2PolygonShape *) wallRightBody->GetFixtureList()[0].GetShape())->m_vertices[0]);
    float wallRightShapeWidth = std::abs(wallRightBodyVertice->x * DOUBLE);
    float wallRightShapeHeight = std::abs(wallRightBodyVertice->y * DOUBLE);
    SDL_Rect *wallRightSprite = new SDL_Rect();
    wallRightSprite->w = (int) (wallRightShapeWidth * PIXELS_PER_METER_X);
    wallRightSprite->h = (int) (wallRightShapeHeight * PIXELS_PER_METER_Y);
    wallRightSprite->x = (wallRightBody->GetPosition().x - (wallRightShapeWidth * HALF)) * PIXELS_PER_METER_X;
    wallRightSprite->y =
            ((wallRightBody->GetPosition().y + (wallRightShapeHeight * HALF)) * PIXELS_PER_METER_Y) * INVERT;

    //Left Wall Sprite
    b2Vec2 *wallLeftBodyVertice = &(((b2PolygonShape *) wallLeftBody->GetFixtureList()[0].GetShape())->m_vertices[0]);
    float wallLeftShapeWidth = std::abs(wallLeftBodyVertice->x * DOUBLE);
    float wallLeftShapeHeight = std::abs(wallLeftBodyVertice->y * DOUBLE);
    SDL_Rect *wallLeftSprite = new SDL_Rect();
    wallLeftSprite->w = (int) (wallLeftShapeWidth * PIXELS_PER_METER_X);
    wallLeftSprite->h = (int) (wallLeftShapeHeight * PIXELS_PER_METER_Y);
    wallLeftSprite->x = (wallLeftBody->GetPosition().x - (wallLeftShapeWidth * HALF)) * PIXELS_PER_METER_X;
    wallLeftSprite->y = ((wallLeftBody->GetPosition().y + (wallLeftShapeHeight * HALF)) * PIXELS_PER_METER_Y) * INVERT;

    //Top Wall Sprite
    b2Vec2 *wallTopBodyVertice = &(((b2PolygonShape *) wallTopBody->GetFixtureList()[0].GetShape())->m_vertices[0]);
    float wallTopShapeWidth = std::abs(wallTopBodyVertice->x * DOUBLE);
    float wallTopShapeHeight = std::abs(wallTopBodyVertice->y * DOUBLE);
    SDL_Rect *wallTopSprite = new SDL_Rect();
    wallTopSprite->w = (int) (wallTopShapeWidth * PIXELS_PER_METER_X);
    wallTopSprite->h = (int) (wallTopShapeHeight * PIXELS_PER_METER_Y);
    wallTopSprite->x = (wallTopBody->GetPosition().x - (wallTopShapeWidth * HALF)) * PIXELS_PER_METER_X;
    wallTopSprite->y = ((wallTopBody->GetPosition().y + (wallTopShapeHeight * HALF)) * PIXELS_PER_METER_Y) * INVERT;

    //Bottom Wall Sprite
    b2Vec2 *wallBottomBodyVertice = &(((b2PolygonShape *) wallBottomBody->GetFixtureList()[0].GetShape())->m_vertices[0]);
    float wallBottomShapeWidth = std::abs(wallBottomBodyVertice->x * DOUBLE);
    float wallBottomShapeHeight = std::abs(wallBottomBodyVertice->y * DOUBLE);
    SDL_Rect *wallBottomSprite = new SDL_Rect();
    wallBottomSprite->w = (int) (wallBottomShapeWidth * PIXELS_PER_METER_X);
    wallBottomSprite->h = (int) (wallBottomShapeHeight * PIXELS_PER_METER_Y);
    wallBottomSprite->x = (wallBottomBody->GetPosition().x - (wallBottomShapeWidth * HALF)) * PIXELS_PER_METER_X;
    wallBottomSprite->y =
            ((wallBottomBody->GetPosition().y + (wallBottomShapeHeight * HALF)) * PIXELS_PER_METER_Y) * INVERT;

    //Initialize Display
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could not initialize display: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
            SCREEN_TITLE,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            (int) SCREEN_WIDTH, (int) SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );
    if (window == nullptr) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderTarget = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_SOFTWARE
    );
    if (renderTarget == nullptr) {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    //Initialize Clock
    std::chrono::steady_clock clock;
    float deltaTime = WORLD_TIME_ELAPSED_ZERO;
    std::chrono::steady_clock::time_point lastTick = clock.now();
    std::chrono::steady_clock::time_point thisTick;

    //Initialize Input
    const Uint8 *keyState;
    SDL_Event event;

    // //Enter Game Loop
    bool quitFlag = false;
    while (quitFlag == false) {

        thisTick = clock.now();
        std::chrono::duration<float> timeElapsedSinceLastTick = thisTick - lastTick;
        deltaTime += timeElapsedSinceLastTick.count();
        lastTick = thisTick;

        while (deltaTime >= WORLD_TIME_RESOLUTION) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        quitFlag = true;
                        break;
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            quitFlag = true;
                        }
                        break;
                }

                keyState = SDL_GetKeyboardState(NULL);
                b2Vec2 nudgedVelocity = ballBody->GetLinearVelocity();

                if (keyState[SDL_SCANCODE_UP]) { nudgedVelocity.y += BALL_NUDGE_FACTOR; }
                if (keyState[SDL_SCANCODE_DOWN]) { nudgedVelocity.y -= BALL_NUDGE_FACTOR; }
                if (keyState[SDL_SCANCODE_LEFT]) { nudgedVelocity.x -= BALL_NUDGE_FACTOR; }
                if (keyState[SDL_SCANCODE_RIGHT]) { nudgedVelocity.x += BALL_NUDGE_FACTOR; }
                ballBody->SetLinearVelocity(nudgedVelocity);
            }

            if (keyState[SDL_SCANCODE_P]) {
                do {
                    SDL_PollEvent(&event);
                    lastTick = clock.now();
                } while (keyState[SDL_SCANCODE_P]);
            }

            world->Step(deltaTime / (keyState[SDL_SCANCODE_S] ? WORLD_SLOW_MOTION_FACTOR : 1.0f),
                        PHYSICS_VELOCITY_ITERATIONS, PHYSICS_POSITION_ITERATIONS);

            ballSprite->x = (int) ((ballBody->GetPosition().x - ballBody->GetFixtureList()[0].GetShape()->m_radius) *
                                   PIXELS_PER_METER_X);
            ballSprite->y = ((int) ((ballBody->GetPosition().y + ballBody->GetFixtureList()[0].GetShape()->m_radius) *
                                    PIXELS_PER_METER_Y)) * INVERT;

            deltaTime -= WORLD_TIME_RESOLUTION;

        }

        //Render Screen
        SDL_SetRenderDrawColor(
                renderTarget,
                COLOR_BLACK_R,
                COLOR_BLACK_G,
                COLOR_BLACK_B,
                COLOR_BLACK_A
        );
        SDL_RenderClear(renderTarget);

        SDL_SetRenderDrawColor(
                renderTarget,
                COLOR_TERMINALGREEN_R,
                COLOR_TERMINALGREEN_G,
                COLOR_TERMINALGREEN_B,
                COLOR_TERMINALGREEN_A
        );

        SDL_RenderFillRect(renderTarget, wallRightSprite);
        SDL_RenderFillRect(renderTarget, wallLeftSprite);
        SDL_RenderFillRect(renderTarget, wallTopSprite);
        SDL_RenderFillRect(renderTarget, wallBottomSprite);
        SDL_RenderFillRect(renderTarget, ballSprite);

        SDL_RenderPresent(renderTarget);
    }


    SDL_DestroyRenderer(renderTarget);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}