#pragma once
#include <stdexcept>
#include <print>
#include "Application.h"

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
