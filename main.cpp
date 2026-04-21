/**
 * Author: Aubrey Bedford
 *
 */

#include <iostream>
#include <SDL.h>

using namespace std;

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }



    cout << "Lets cook this maze!" << endl;
    SDL_Quit();
    return 0;
}