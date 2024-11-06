#include <raylib.h>
#include <raymath.h>

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

void Menu();

int main()
{
    int gameScreenWidth = 800;
    int gameScreenHeight = 450;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN | FLAG_WINDOW_HIGHDPI);
    InitWindow(gameScreenWidth, gameScreenHeight, "Reminder");
    SetWindowMinSize(320, 240);
    SetTargetFPS(60);

    RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

   SetWindowState(FLAG_WINDOW_UNDECORATED);

    while (!WindowShouldClose())
    {
        float scale = MIN((float)GetScreenWidth()/gameScreenWidth, (float)GetScreenHeight()/gameScreenHeight);
        Vector2 mouse = GetMousePosition();
        Vector2 virtualMouse = { 0 };
        virtualMouse.x = (mouse.x - (GetScreenWidth() - (gameScreenWidth*scale))*0.5f)/scale;
        virtualMouse.y = (mouse.y - (GetScreenHeight() - (gameScreenHeight*scale))*0.5f)/scale;
        virtualMouse = Vector2Clamp(virtualMouse, (Vector2){ 0, 0 }, (Vector2){ (float)gameScreenWidth, (float)gameScreenHeight });

        SetMouseOffset(-(GetScreenWidth() - (gameScreenWidth*scale))*0.5f, -(GetScreenHeight() - (gameScreenHeight*scale))*0.5f);
        SetMouseScale(1/scale, 1/scale);
        
        BeginTextureMode(target);
            ClearBackground(DARKGRAY);
            Menu();
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                           (Rectangle){ (GetScreenWidth() - ((float)gameScreenWidth*scale))*0.5f, (GetScreenHeight() - ((float)gameScreenHeight*scale))*0.5f,
                           (float)gameScreenWidth*scale, (float)gameScreenHeight*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();
}

void Menu()
{
    // DrawRectanglePro((Rectangle){ 0, 20, 800, 20}, Vector2Zero(), 0, RAYWHITE);
    DrawCircle(10, 10, 10, RED);
    DrawCircle(30, 10, 10, GREEN);
    DrawCircle(50, 10, 10, BLUE);  

    if (CheckCollisionPointCircle(GetMousePosition(), (Vector2){ 10, 10 }, 10))
    {
        DrawCircle(10, 10, 10, YELLOW);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            CloseWindow();
        }
    }
    else if (CheckCollisionPointCircle(GetMousePosition(), (Vector2){ 30, 10 }, 10))
    {
        DrawCircle(30, 10, 10, YELLOW);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            SetWindowState(FLAG_WINDOW_MINIMIZED);
        }
    }
    else if (CheckCollisionPointCircle(GetMousePosition(), (Vector2){ 50, 10 }, 10))
    {
        DrawCircle(50, 10, 10, YELLOW);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            int monitor = GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
            SetWindowPosition(0, 0);
        }
    }
}