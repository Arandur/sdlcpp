#include "sdl_except.h"

#include "SDL.h"

namespace sdlcpp
{
SDL_Error::SDL_Error () :
  exception (),
  msg (SDL_GetError ())
{}

SDL_Error::SDL_Error (const std::string& m) :
  exception (),
  msg (m + ": " + SDL_GetError ())
{}

SDL_Error::~SDL_Error ()
{}

auto SDL_Error::what () const noexcept ->
const char*
{
  return msg.c_str ();
}
}
