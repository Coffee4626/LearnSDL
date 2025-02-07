#include "gameBase.h"
#include "loadMedia.h"
#include "InputHandle.h"

using namespace std;

const char* WINDOW_TITLE = "Test";

//Class ball/ray to fly at a certain direction at game start

//Class mirror/panel to bounce the ball at point of impact 

//Class endpoint for game score

//given a number of panels, player must move and rotate the panels to bounce the ball to endpoint

//Class wall/obstable to prevent ball from reaching the endpoint

//Physics to handle the point of impact and angle of deflection

//Texture and sprites for the panels and the ball


void drawSomething(SDL_Window* window, SDL_Renderer* renderer) 
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH - 400;
    filled_rect.y = SCREEN_HEIGHT - 150;
    filled_rect.w = 320;
    filled_rect.h = 100;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(renderer, &filled_rect);
}

int main(int argc, char* argv[])
{
    //Initialize
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);

    //Xóa màn hình
    SDL_RenderClear(renderer);

    //Main loop



    //Hiện bản vẽ ra màn hình
    //Khi chạy tại môi trường bình thường
    SDL_RenderPresent(renderer);
    //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
    //SDL_UpdateWindowSurface(window);

    //Đợi phím bất kỳ trước khi đóng môi trường đồ họa và kết thúc chương trình
    quitSDL(window, renderer);
    return 0;
}


