#pragma once
#include <stdexcept>
#include <print>
#include "pch.h"
#include "Application.h"


#define DISABLE_WARNINGS_FROM_RAYLIB \
    __pragma(warning(push)) \
    /* C26812: The enum type '...' is unscoped. Prefer 'enum class' over 'enum' (Enum.3) */ \
    __pragma(warning(disable : 26812)) \
    /* C26446: Prefer to use gsl::at() instead of unchecked subscript operator (bounds.4). */ \
    __pragma(warning(disable : 26446)) \
    /* C26455: Default constructor is not declared as noexcept */ \
    __pragma(warning(disable : 26455)) \
    /* C26426: Global initializer calls a non-constexpr function */ \
    __pragma(warning(disable : 26426)) \
    /* C26409: Avoid calling new and delete explicitly, use smart pointers */ \
    __pragma(warning(disable : 26409)) \
    /* C26477: Use 'override' instead of base class member name */ \
    __pragma(warning(disable : 26477)) \
    /* C26433: Function can be marked as noexcept */ \
    __pragma(warning(disable : 26433)) \
    /* C26818: Prefer std::vector over C array */ \
    __pragma(warning(disable : 26818)) \
    /* C26440: Function can be declared 'const' */ \
    __pragma(warning(disable : 26440))

/*Window class error checking (none available, don't worry about it)

(window has hardcoded magic values, don't do that. expose the settings)

(window takes int but you never check for negative values. consider taking unsigned)

GitHub -> remember to Push

Collision checking - use the library routines. simplify! delete the complicated collision code

State pattern - let Game own all the things the application needs, instead of placing those resources in the scope of the main function

State pattern - let each State handle their own update, render etc, and notify (perhaps a return on update() when it's time to change to another state)

Exceptions: make sure you catch them before leaving the main scope

Scale the textures on the hard drive instead of doing it every frame (DrawTexturePro vs. DrawTexture)

Consider creating an Animation class to handle timing

Check you project settings. C++Latest, warnings level 4, static analysis with a good ruleset.

disable warnings and static analysis  on external files, check the forums for how to do that.

recheck all noexcpets (allocation of memory = except) ie. emplace_back is allocation*/


int main(void)
{   
    try {
        Application application;

        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            application.run();
        }

        return 0;
    }
    catch (const std::runtime_error& e) {
        std::println("Runtime error: {}", e.what());
    }
    return 0;
}


#define RESTORE_WARNINGS __pragma(warning(pop))