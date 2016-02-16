#include "sdl_class.h"
#include "sdl_except.h"

namespace sdlcpp
{
SDL::SDL (uint32_t flags)
{
  if (SDL_Init (static_cast<Uint32> (flags)) != 0) {
    throw Init_Error ("SDL_Init");
  }
}

SDL::~SDL () noexcept
{
  SDL_Quit ();
}

auto SDL::create_window (
    const std::string& title,
    int x, int y, int w, int h,
    uint32_t flags) ->
window_ptr
{
  auto ret =
    window_ptr (
        SDL_CreateWindow (
            title.c_str (), x, y, w, h, static_cast<Uint32> (flags)),
        sdl_deleter ());

  if (ret) {
    return ret;
  } else {
    throw SDL_Error ("SDL_CreateWindow");
  }
}

auto SDL::create_renderer (
    window_ptr::pointer win,
    int index, uint32_t flags) ->
renderer_ptr
{
  auto ret =
    renderer_ptr (
        SDL_CreateRenderer (
            win, index, static_cast<Uint32> (flags)),
        sdl_deleter ());

  if (ret) {
    return ret;
  } else {
    throw SDL_Error ("SDL_CreateRenderer");
  }
}

auto SDL::create_surface_from_bmp (
    const std::string& bmp_path) ->
surface_ptr
{
  auto ret =
    surface_ptr (
        SDL_LoadBMP (bmp_path.c_str ()),
        sdl_deleter ());

  if (ret) {
    return ret;
  } else {
    throw SDL_Error ("SDL_LoadBMP");
  }
}

auto SDL::create_texture_from_bmp (
    renderer_ptr::pointer ren, const std::string& bmp_path) ->
texture_ptr
{
  auto ret =
    texture_ptr (
        SDL_CreateTextureFromSurface (
            ren,
            create_surface_from_bmp (bmp_path).get ()),
        sdl_deleter ());

  if (ret) {
    return ret;
  } else {
    throw SDL_Error ("SDL_CreateTextureFromSurface");
  }
}

void SDL::render_texture (
    texture_ptr::pointer tex, renderer_ptr::pointer ren, int x, int y)
{
  int w, h;
  SDL_QueryTexture (tex, nullptr, nullptr, &w, &h);
  render_texture (tex, ren, x, y, w, h);
}

void SDL::render_texture (
    texture_ptr::pointer tex, renderer_ptr::pointer ren, 
    int x, int y, int w, int h)
{
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;
  SDL_RenderCopy (ren, tex, nullptr, &dst);
}
}
