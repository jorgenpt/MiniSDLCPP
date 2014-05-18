/* Copyright (C) 2014 Jørgen P. Tjernø <jorgenpt@gmail.com>
 * MiniSDLCPP is licensed under the zlib license, which can be found in the LICENSE file.
 */

#pragma once

#include <SDL2/SDL.h>
#include <memory>

namespace jpt
{
    namespace SDL
    {
        template <typename Type, void (*Deleter)(Type)>
        struct CDeleter
        {
            void operator() (Type arg) { Deleter(arg); }
        };

        typedef CDeleter<SDL_Cursor*, &SDL_FreeCursor> ManagedCursorDeleter;
        typedef std::unique_ptr<SDL_Cursor, ManagedCursorDeleter> ManagedCursor;
        typedef CDeleter<SDL_GLContext, &SDL_GL_DeleteContext> ManagedGLContextDeleter;
        typedef std::unique_ptr<void, ManagedGLContextDeleter> ManagedGLContext;
        typedef CDeleter<SDL_Window*, &SDL_DestroyWindow> ManagedWindowDeleter;
        typedef std::unique_ptr<SDL_Window, ManagedWindowDeleter> ManagedWindow;

        typedef CDeleter<SDL_Texture*, &SDL_DestroyTexture> ManagedTextureDeleter;
        typedef std::unique_ptr<SDL_Texture, ManagedTextureDeleter> ManagedTexture;
        typedef CDeleter<SDL_PixelFormat*, &SDL_FreeFormat> ManagedPixelFormatDeleter;
        typedef std::unique_ptr<SDL_PixelFormat, ManagedPixelFormatDeleter> ManagedPixelFormat;
        typedef CDeleter<SDL_Palette*, &SDL_FreePalette> ManagedPaletteDeleter;
        typedef std::unique_ptr<SDL_Palette, ManagedPaletteDeleter> ManagedPalette;
        typedef CDeleter<SDL_Surface*, &SDL_FreeSurface> ManagedSurfaceDeleter;
        typedef std::unique_ptr<SDL_Surface, ManagedSurfaceDeleter> ManagedSurface;
        typedef CDeleter<SDL_Renderer*, &SDL_DestroyRenderer> ManagedRendererDeleter;
        typedef std::unique_ptr<SDL_Renderer, ManagedRendererDeleter> ManagedRenderer;

        typedef CDeleter<SDL_RWops*, &SDL_FreeRW> ManagedRWopsDeleter;
        typedef std::unique_ptr<SDL_RWops, ManagedRWopsDeleter> ManagedRWops;

        typedef CDeleter<SDL_Joystick*, &SDL_JoystickClose> ManagedJoystickDeleter;
        typedef std::unique_ptr<SDL_Joystick, ManagedJoystickDeleter> ManagedJoystick;
        typedef CDeleter<SDL_Haptic*, &SDL_HapticClose> ManagedHapticDeleter;
        typedef std::unique_ptr<SDL_Haptic, ManagedHapticDeleter> ManagedHaptic;
        typedef CDeleter<SDL_GameController*, &SDL_GameControllerClose> ManagedGameControllerDeleter;
        typedef std::unique_ptr<SDL_GameController, ManagedGameControllerDeleter> ManagedGameController;


        /* I've omitted wrapping SDL_mutex, SDL_sem and SDL_cond because
         * wrapping threading primitives seems unwise.
         *
         * TODO: SDL_AudioDeviceID - it's not a pointer, so it needs a little
         *       bit of jiggering.
         */
    }
}
