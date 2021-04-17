#include "pch.h"

int main(int argc, char* argv[]) {
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    glm::vec2 velocity = glm::vec2(2.0, -1.6);

    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "Dll check!" << std::endl;
    return 0;
}
