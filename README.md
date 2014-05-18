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

[Many][other1] [other][other2] [projects][other3] have created
[wrappers][other4] for SDL in C++, and I've never used any of them, even
though I've ported large C++ game engines of commercial studios to SDL.
Most C++ wrappers attempt to wrap the entire API of SDL, which means
they almost always end up with one or more of these problems:

 * Not having complete or up-to-date API coverge.
 * Not having good documentation.
 * Requiring re-learning the SDL API if you've used the C API before.
 * Adding another chunky dependency on top of SDL.
 * Complicating debugging by adding more layers between you and the API.
 * Introducing bugs by adding more complexity.

SDL is used by [a large number of commercial games][games], and has a
thriving community of contributors. Odds are that your C++ wrapper of
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

 * `reset(handle)` takes over the given handle, cleaning up any previous
   handle attached to this object.
 * `get()` returns the handle.
 * `detach()` returns the handle, and tells the object to not clean up
   the handle when the object is destroyed.

The API is self-contained:

 * Two .hpp files, that you can optionally concatenate together.
 * Everything lives in `#define`s prefixed with `JPT_` or in a namespace
   named `jpt`.
 * It builds with any modern C++ (preferably C++11) compiler, no weird
   build options or external dependencies (but you supply the SDL.)

[other1]: http://sdlpp.sourceforge.net/
[other2]: http://sdlmm.sourceforge.net/
[other3]: http://home.gna.org/aml/sdl/
[other4]: https://code.google.com/p/sdlxx/
[games]: http://libsdl.org/index.php
