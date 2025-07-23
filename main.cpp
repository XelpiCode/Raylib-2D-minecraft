#include <array>
#include <raylib.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <bits/ostream.tcc>

void DrawTextureOnSquareSimple(const Texture2D &texture, float posX, float posY, float size, Color tint)
{
    Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    Rectangle destRec = { posX, posY, size, size };
    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, tint);
}

bool AlreadyInVector(const std::vector<std::array<float, 2>> &placedBlock, std::array<float, 2> position) {
    for (auto & block : placedBlock) {
        if (block[0] == position[0] && block[1] == position[1]) {
            return true;
        }
    }
    return false;
}

void PlaceBlocks(const std::vector<std::array<float, 2>> &placedBlocks, const Texture2D &texture) {
    for (auto & placedBlock : placedBlocks) {
        DrawTextureOnSquareSimple(texture, placedBlock[0], placedBlock[1], 100, WHITE);
    }
}


int main() {
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "2D Minecraft");

    SetTargetFPS(165);

    Texture2D grassBlock = LoadTexture("C:/Users/ankit/CLionProjects/raylib game/Textures/grass.png");

    std::vector<std::array<float, 2>> placedBlocks;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLUE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            std::array<float, 2> newBlockPosition = {roundf((mousePos.x - 50)/100)*100 , roundf((mousePos.y - 50)/100)*100 };

            if (!AlreadyInVector(placedBlocks, newBlockPosition)) {
                placedBlocks.push_back(newBlockPosition);
                std::cout << "placed block at " << newBlockPosition[0] << " " << newBlockPosition[1] << std::endl;
            }
        }

        PlaceBlocks(placedBlocks, grassBlock);

        EndDrawing();
    }
    UnloadTexture(grassBlock);
    CloseWindow();
    return 0;
}

