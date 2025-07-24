#include <array>
#include <raylib.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <bits/ostream.tcc>
#include <map>

float SnapToGrid(float number) {
    return roundf((number - 50)/100)*100;
}

std::map<std::string, Texture2D> textures;

void loadBlockTextures() {
    textures["grass_block"] = LoadTexture("C:/Users/ankit/CLionProjects/raylib game/Textures/Grass.png");
    textures["dirt_block"] = LoadTexture("C:/Users/ankit/CLionProjects/raylib game/Textures/Dirt.png");
    textures["cobblestone"] = LoadTexture("C:/Users/ankit/CLionProjects/raylib game/Textures/Cobblestone.png");
    textures["oak_log"] = LoadTexture("C:/Users/ankit/CLionProjects/raylib game/Textures/Oak_Log.png");
    textures["oak_plank"] = LoadTexture("C:/Users/ankit/CLionProjects/raylib game/Textures/Oak_Plank.png");
    textures["stone"] = LoadTexture("C:/Users/ankit/CLionProjects/raylib game/Textures/Stone.png");
    textures["leaves"] = LoadTexture("C:/Users/ankit/CLionProjects/raylib game/Textures/Leaves.png");
}

void unloadBlockTextures() {
    for (const auto &pair : textures) {
        UnloadTexture(pair.second);
    }
}

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

bool AlreadyInVector(const std::vector<BlockData> &placedBlock, const BlockData &position) {
    for (auto & block : placedBlock) {
        if (block.x == position.x && block.y == position.y) {
            return true;
        }
    }
    return false;
}

void DrawBlocks(const std::vector<BlockData> &placedBlocks) {
    for (auto & placedBlock : placedBlocks) {
        DrawTextureOnSquareSimple(placedBlock.texture, placedBlock.x, placedBlock.y, 100, WHITE);
    }
}

int placeBlock(std::vector<BlockData>& placedBlocks, BlockData newBlock) {
    if (!AlreadyInVector(placedBlocks, newBlock)) {
        placedBlocks.push_back(newBlock);
        std::cout << "placed block at " << newBlock.x << " " << newBlock.y << std::endl;
        return 0;
    }
    return 1;
}

void BlockTexturesOption(std::vector<BlockData>& placedBlocks) {
    float blocksShown = 0;
    for (const auto &block : textures) {
        BlockData newBlock = { SnapToGrid(650) + blocksShown , SnapToGrid(980), block.second};
        blocksShown += 100;
        placeBlock(placedBlocks, newBlock);
    }
}

void ChangeTexture(const std::vector<BlockData>& placedBlocks, Vector2 mousePos, Texture2D& currentTexture) {
    for (const auto &block : placedBlocks) {
        if (block.x == SnapToGrid(mousePos.x) && block.y == SnapToGrid(mousePos.y)) {
            currentTexture = block.texture;
        }
    }
}

void DeleteBlock(std::vector<BlockData>& placedBlocks, Vector2 mousePos) {
    for (auto it = placedBlocks.begin(); it != placedBlocks.end(); ++it) {
        if (it->x == SnapToGrid(mousePos.x) && it->y == SnapToGrid(mousePos.y)) {
            placedBlocks.erase(it);
            break;
        }
    }
}

int main() {
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "2D Minecraft");

    SetTargetFPS(165);
    loadBlockTextures();

     Texture2D currentTexture = textures["dirt_block"];

    std::vector<BlockData> placedBlocks;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLUE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            BlockData newBlock = {SnapToGrid(mousePos.x) , SnapToGrid(mousePos.y), currentTexture};
            placeBlock(placedBlocks, newBlock);
        }

        if (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            ChangeTexture(placedBlocks, mousePos, currentTexture);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            Vector2 mousePos = GetMousePosition();
            DeleteBlock(placedBlocks, mousePos);
        }


        DrawBlocks(placedBlocks);
        BlockTexturesOption(placedBlocks);

        EndDrawing();
    }
    unloadBlockTextures();
    CloseWindow();
    return 0;
}
