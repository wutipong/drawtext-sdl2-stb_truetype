#include "texture.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

SDL_Texture *CreateTextureFromCodePoint(SDL_Renderer *renderer,
                                        const stbtt_fontinfo &info,
                                        wchar_t &codepoint, const float &scale,
                                        const SDL_Color &color, int &advance,
                                        SDL_Rect &dst) {
  int bearing;

  auto format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);

  stbtt_GetCodepointHMetrics(&info, static_cast<int>(codepoint), &advance,
                             &bearing);
  advance = static_cast<int>(roundf(advance * scale));
  bearing = static_cast<int>(roundf(bearing * scale));

  int c_x1, c_y1, c_x2, c_y2;
  stbtt_GetCodepointBitmapBox(&info, static_cast<int>(codepoint), scale, scale,
                              &c_x1, &c_y1, &c_x2, &c_y2);
  int y = c_y1;

  int width = c_x2 - c_x1;
  int height = c_y2 - c_y1;

  unsigned char *bitmap =
      new unsigned char[static_cast<size_t>(width) * height];

  stbtt_MakeCodepointBitmap(&info, bitmap, width, height, width, scale, scale,
                            static_cast<int>(codepoint));

  auto surface = SDL_CreateRGBSurfaceWithFormat(
      0, width, height, format->BitsPerPixel, format->format);

  SDL_LockSurface(surface);

  for (int sy = 0; sy < height; sy++) {
    for (int sx = 0; sx < width; sx++) {
      unsigned char &alpha = bitmap[sy * width + sx];

      auto pixel = reinterpret_cast<Uint32 *>(surface->pixels) +
                   (sy * (surface->pitch / sizeof(Uint32)) + sx);

      *pixel = SDL_MapRGBA(format, color.r, color.g, color.b, alpha);
    }
  }

  delete[] bitmap;

  SDL_UnlockSurface(surface);

  auto texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture != nullptr) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  }

  dst = {bearing, static_cast<int>(y), width, height};

  SDL_FreeFormat(format);
  SDL_FreeSurface(surface);

  return texture;
}

SDL_Texture *CreateTextureFromIndex(SDL_Renderer *renderer,
                                    const stbtt_fontinfo &info,
                                    const int &index, const float &scale,
                                    const SDL_Color &color, int &advance,
                                    SDL_Rect &dst) {
  int bearing;

  auto format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);

  stbtt_GetGlyphHMetrics(&info, index, &advance, &bearing);

  advance = static_cast<int>(roundf(advance * scale));
  bearing = static_cast<int>(roundf(bearing * scale));

  int c_x1, c_y1, c_x2, c_y2;
  stbtt_GetGlyphBitmapBox(&info, index, scale, scale, &c_x1, &c_y1, &c_x2,
                          &c_y2);
  int y = c_y1;

  int width = c_x2 - c_x1;
  int height = c_y2 - c_y1;

  unsigned char *bitmap =
      new unsigned char[static_cast<size_t>(width) * height];

  stbtt_MakeGlyphBitmap(&info, bitmap, width, height, width, scale, scale,
                        index);

  auto surface = SDL_CreateRGBSurfaceWithFormat(
      0, width, height, format->BitsPerPixel, format->format);

  SDL_LockSurface(surface);

  for (int sy = 0; sy < height; sy++) {
    for (int sx = 0; sx < width; sx++) {
      unsigned char &alpha = bitmap[sy * width + sx];

      auto pixel = reinterpret_cast<Uint32 *>(surface->pixels) +
                   (sy * (surface->pitch / sizeof(Uint32)) + sx);

      *pixel = SDL_MapRGBA(format, color.r, color.g, color.b, alpha);
    }
  }

  delete[] bitmap;

  SDL_UnlockSurface(surface);

  auto texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture != nullptr) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  }

  dst = {c_x1, y, width, height};

  SDL_FreeFormat(format);
  SDL_FreeSurface(surface);

  return texture;
}