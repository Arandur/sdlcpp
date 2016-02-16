#pragma once

#include "SDL.h"

#include <cstdint>
#include <string>
#include <memory>

namespace sdlcpp
{
class SDL
{
  struct sdl_deleter
  {
    void operator () (SDL_Window* p) const noexcept { SDL_DestroyWindow (p); }
    void operator () (SDL_Renderer* p) const noexcept { SDL_DestroyRenderer (p); }
    void operator () (SDL_Surface* p) const noexcept { SDL_FreeSurface (p); }
    void operator () (SDL_Texture* p) const noexcept { SDL_DestroyTexture (p); }
  };
public:

  using window_ptr = std::unique_ptr<SDL_Window, sdl_deleter>;
  using renderer_ptr = std::unique_ptr<SDL_Renderer, sdl_deleter>;
  using surface_ptr = std::unique_ptr<SDL_Surface, sdl_deleter>;
  using texture_ptr = std::unique_ptr<SDL_Texture, sdl_deleter>;

  SDL (uint32_t flags = 0);
  virtual ~SDL () noexcept;

  static auto create_window (
      const std::string&, int, int, int, int, uint32_t) ->
  window_ptr;

  static auto create_renderer (
      window_ptr::pointer, int, uint32_t) ->
  renderer_ptr;

  static auto create_surface_from_bmp (
      const std::string&) ->
  surface_ptr;

  static auto create_texture_from_bmp (
      renderer_ptr::pointer, const std::string&) ->
  texture_ptr;

  static void render_texture (
      texture_ptr::pointer, renderer_ptr::pointer, int, int);

  static void render_texture (
      texture_ptr::pointer, renderer_ptr::pointer, int, int, int, int);
};
}
