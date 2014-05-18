# Mini SDL C++

A minimalist library for cleaner SDL in C++.

## Getting started

Copy the two `.hpp` files into your project, then slap the following two lines
into your relevant source file:

```cpp
#include "MiniSDL.hpp"
using namespace jpt;
```

Then look up the wrapper you need in [MiniSDL.hpp](MiniSDL.hpp).

## Motivation

Many other projects (e.g. [SDLPP][sdlpp], [RAGE::SDL][ragesdl],
[SDLmm][sdlmm], [sdlxx][sdlxx]) provide C++ wrappers for SDL, and I've
never used any of them even though I've ported large C++ game engines of
commercial studios to SDL. Most wrappers attempt to wrap the entire API
of SDL, which means they almost always end up with one or more of these
problems:

 * Not having complete or up-to-date API coverage.
 * Not having good documentation.
 * Requiring re-learning the SDL API if you've used the C API before.
 * Adding another chunky dependency on top of SDL.
 * Complicating debugging by adding more layers between you and the API.
 * Introducing bugs by adding more complexity.

SDL is used by [a large number of commercial games][sdl-games], and has
a thriving community of contributors. Odds are that your C++ wrapper of
the day can't say the same.

In my opinion, SDL's API is straight forward and does not need to be
C++ified. The one frustration with using SDL when writing C++ is that
you need to manually manage object lifecycles and can't use nice
C++-isms like having a SDL object that is destroyed when your stack
frame ends or embedding them in a `std::unique_ptr`.


## Solution

Enter MiniSDLCPP!

All MiniSDLCPP does is manage the lifecycle of your objects. With a
[simple wrapper](ManagedCHandle.hpp) that knows how to clean up a C
handle (like a pointer) and a [set of typedefs](MiniSDL.hpp) to
configure ManagedCHandle for all relevant SDL types, we have everything
we need.

`ManagedCHandle` is even better with C++11, where it supports move
semantics.

The API is simple:

 * `obj.reset(handle)` takes over the given handle, cleaning up any
   previous handle attached to this object.
 * `obj.get()` returns the handle.
 * `obj.detach()` returns the handle, and tells the object to not clean
   up the handle when the object is destroyed.

The API is self-contained:

 * Two .hpp files that you can optionally concatenate together.
 * Everything lives in the `jpt` namespace or has a `JPT_` prefix.
 * It builds with any modern C++ (preferably C++11) compiler, no weird
   build options or external dependencies (but you supply the SDL.)

[sdlpp]: http://sdlpp.sourceforge.net/
[sdlmm]: http://sdlmm.sourceforge.net/
[ragesdl]: http://home.gna.org/aml/sdl/
[sdlxx]: https://code.google.com/p/sdlxx/
[sdl-games]: http://libsdl.org/index.php
