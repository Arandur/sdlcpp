#pragma once

#include <exception>
#include <string>

namespace sdlcpp
{
class SDL_Error : public std::exception
{
public:
  SDL_Error ();
  SDL_Error (const std::string&);
  virtual ~SDL_Error ();
  virtual auto what () const noexcept ->
  const char*;

protected:

  const std::string msg;
};

class Init_Error : public SDL_Error 
{
public:
  using SDL_Error::SDL_Error;
};
}
