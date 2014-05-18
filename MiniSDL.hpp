/* Copyright (C) 2014 Jørgen P. Tjernø <jorgenpt@gmail.com>
 * MiniSDLCPP is licensed under the zlib license, which can be found in the LICENSE file.
 */

#pragma once

#include <SDL2/SDL.h>

#include "ManagedCHandle.hpp"

namespace jpt
{
    namespace SDL
    {
        typedef ManagedCHandle<SDL_Cursor*, &SDL_FreeCursor> ManagedCursor;
        typedef ManagedCHandle<SDL_GLContext, &SDL_GL_DeleteContext> ManagedGLContext;
        typedef ManagedCHandle<SDL_Window*, &SDL_DestroyWindow> ManagedWindow;

        typedef ManagedCHandle<SDL_Texture*, &SDL_DestroyTexture> ManagedTexture;
        typedef ManagedCHandle<SDL_PixelFormat*, &SDL_FreeFormat> ManagedPixelFormat;
        typedef ManagedCHandle<SDL_Palette*, &SDL_FreePalette> ManagedPalette;
        typedef ManagedCHandle<SDL_Surface*, &SDL_FreeSurface> ManagedSurface;
        typedef ManagedCHandle<SDL_Renderer*, &SDL_DestroyRenderer> ManagedRenderer;

        typedef ManagedCHandle<SDL_RWops*, &SDL_FreeRW> ManagedRWops;

        typedef ManagedCHandle<SDL_Joystick*, &SDL_JoystickClose> ManagedJoystick;
        typedef ManagedCHandle<SDL_Haptic*, &SDL_HapticClose> ManagedHaptic;
        typedef ManagedCHandle<SDL_GameController*, &SDL_GameControllerClose> ManagedGameController;

        typedef ManagedCHandle<SDL_AudioDeviceID, &SDL_CloseAudioDevice> ManagedAudioDevice;

        /* I've omitted the following because wrapping threading primitives
         * seems unwise:
         *
         *  typedef ManagedCHandle<SDL_mutex*, &SDL_DestroyMutex> ManagedMutex;
         *  typedef ManagedCHandle<SDL_sem*, &SDL_DestroySemaphore> ManagedSemaphore;
         *  typedef ManagedCHandle<SDL_cond*, &SDL_DestroyCond> ManagedCond;
         */
    }
}
