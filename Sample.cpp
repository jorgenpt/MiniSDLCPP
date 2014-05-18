#include "MiniSDL.hpp"

using namespace jpt;

class Game
{
    static constexpr int MAX_FRAME_EVENTS = 100;

public:
    bool openWindow()
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        mWindow.reset(SDL_CreateWindow("MinSDLCPP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL));
        mRunning = (mWindow.get() != nullptr);
        if (running())
        {
            mContext.reset(SDL_GL_CreateContext(mWindow.get()));
            mRunning = (mContext.get() != nullptr);
        }

        return mRunning;
    }

    bool running() { return mRunning; }

    void update()
    {
        SDL_Event event;
        int numEvents = 0;
        while (SDL_PollEvent(&event) && numEvents < MAX_FRAME_EVENTS)
        {
            numEvents++;
            switch (event.type)
            {
                case SDL_QUIT:
                    mRunning = false;
            }
        }
    }

    void render() {}

private:
    SDL::ManagedWindow mWindow;
    SDL::ManagedGLContext mContext;
    bool mRunning;
};

int main()
{
    Game game;
    game.openWindow();

    while (game.running())
    {
        game.update();
        game.render();
    }

    return 0;
}
