#include <array>
#include <raylib.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <bits/ostream.tcc>

struct BlockData {
    float x, y;
    Texture2D texture;
};

void DrawTextureOnSquareSimple(const Texture2D &texture, float posX, float posY, float size, Color tint)
{
    Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    Rectangle destRec = { posX, posY, size, size };
    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, tint);
}

bool AlreadyInVector(const std::vector<BlockData> &placedBlock, BlockData position) {
    for (auto & block : placedBlock) {
        if (block.x == position.x && block.y == position.y) {
            return true;
        }
    }
    return false;
}

void PlaceBlocks(const std::vector<BlockData> &placedBlocks) {
    for (auto & placedBlock : placedBlocks) {
        DrawTextureOnSquareSimple(placedBlock.texture, placedBlock.x, placedBlock.y, 100, WHITE);
    }
}

int main() {
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "2D Minecraft");

    SetTargetFPS(165);

    Texture2D grassBlock = LoadTexture("C:/Users/ankit/CLionProjects/raylib game/Textures/grass.png");

    std::vector<BlockData> placedBlocks;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLUE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            BlockData newBlockPosition = {roundf((mousePos.x - 50)/100)*100 , roundf((mousePos.y - 50)/100)*100, grassBlock};

            if (!AlreadyInVector(placedBlocks, newBlockPosition)) {
                placedBlocks.push_back(newBlockPosition);
                std::cout << "placed block at " << newBlockPosition.x << " " << newBlockPosition.y << std::endl;
            }
        }

        PlaceBlocks(placedBlocks);

        EndDrawing();
    }
    UnloadTexture(grassBlock);
    CloseWindow();
    return 0;
}

