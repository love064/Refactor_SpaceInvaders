#pragma once
#include <stdexcept>
#include <print>
#include "Application.h"

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

disable warnings and static analysis on external files, check the forums for how to do that.

Recheck all noexcpets (allocation of memory = except) ie. emplace_back is allocation*/

// REMOVE: ENUMS
// REMOVE: WARING SUPRESSION. 
//TODO: ADD: FUNCTION OVERLOADS (REMOVE STATIC_CAST). 
//TODO: SIMPLIFY: LEADERBAORD IF TIME. 
// GUT PROJECTILE, CHANGE INTO TWO VECTORS. 
// CHANGE TYPES TO AVOID STATIC_CAST (DONT USE INT). 
// GO OVER ALL USES OF INT REPLACE WITH BETTER TYPE (UNSIGNED FOR POSITIVES). 
// REMOVE HELPER FUNCTIONS GETPOSI(), REPLACE WITH BETTER FUNCSTION OVERLOADS. 
// CHNAGE NAMES (CLASS= CAPTIAL, OTHERWISE LOWERCASE EG. Stars = stars)
//TODO: go over structs and change into class (see what can be private/public)
// REMOVE ALL magic variables ("strigns also count")

int main(void) {   
    try {
        Application application;
        while (!WindowShouldClose()) { 
            application.run();
        }     
    }
    catch (const std::invalid_argument& e) {
        std::println("invalid argument: {}", e.what());
    }
    catch (const std::out_of_range& e) {
        std::println("Out of range: {}", e.what());
    }
    catch (const std::runtime_error& e) {
        std::println("Runtime error: {}", e.what());
    }
    catch (...) {
        std::println("Unknown exception!");
    }
    return 0;
}
