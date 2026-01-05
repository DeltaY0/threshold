#pragma once

#include "defines.h"
#include "logger.h"
#include <string>
#include <sstream>
#include <SDL3/SDL.h>

namespace y {

enum class ErrType
{
    Generic = 0,
    SDL,
    Asset,    // Missing textures, models, sounds
    Render,   // Shader compilation, GL context
    Physics,  // Collision setup failures
    Audio,    // Mixer init, playback errors
    Logic     // Game rule violations
};

class Error
{
    private:
    ErrType type;
    std::string msg;
    std::string filepath;
    std::string lineno;

    public:
    // Main Constructor
    Error(ErrType type, const std::string& msg, const std::string& file,
          const std::string& line)
        : type(type), msg(msg), filepath(file), lineno(line) {
        log_error();
    }

    std::string get_type_label() const {
        switch(type) {
            case ErrType::SDL:
                return "SDL";
            case ErrType::Asset:
                return "ASSET";
            case ErrType::Render:
                return "RENDER";
            case ErrType::Physics:
                return "PHYSICS";
            case ErrType::Audio:
                return "AUDIO";
            case ErrType::Logic:
                return "LOGIC";
            default:
                return "GENERAL";  // Generic has no prefix
        }
    }

    // Helper: Capture SDL Errors automatically
    static Error from_SDL(const std::string& file, const std::string& line) {
        const char* err = SDL_GetError();
        std::string msg =
            (err && *err) ? std::string(err) : "Unknown SDL Error";
        return Error(ErrType::SDL, msg, file, line);
    }

    // clang-format off
    void log_error() {
        LOGFMT(
            PROJNAME,
            get_type_label(),
            "(", filepath, ":", lineno, ") => ",
            msg
        )
    }

    // clang-format on
};
}  // namespace y

// --------------------------------------------------------------------------
// MACROS
// --------------------------------------------------------------------------

// 1. Generic Throw (Default to Generic type)
// Usage: Y_THROW("Health cannot be < 0");
#define YTHROW(msg) \
    throw y::Error(y::ErrType::Generic, msg, __FILENAME__, STR(__LINE__))

// 2. Typed Throw (Specify custom category)
// Usage: Y_THROW_T(y::ErrType::Asset, "Texture not found: wall.png");
#define YTHROWT(type, msg) \
    throw y::Error(type, msg, __FILENAME__, STR(__LINE__))

// 3. SDL Check (Void functions)
// Usage: Y_SDL_CHECK(SDL_Init(...));
#define YSDLCHECK(call)                                        \
    if(!(call)) {                                              \
        throw y::Error::from_SDL(__FILENAME__, STR(__LINE__)); \
    }

// 4. SDL Pointer Check (Returns ptr or nullptr)
// Usage: auto* win = Y_SDL_PTR(SDL_CreateWindow(...));
#define YSDLPTR(call)                                              \
    ([&]() {                                                       \
        auto* ptr = (call);                                        \
        if(!ptr) {                                                 \
            throw y::Error::from_SDL(__FILENAME__, STR(__LINE__)); \
        }                                                          \
        return ptr;                                                \
    }())

#define nothingggg 1