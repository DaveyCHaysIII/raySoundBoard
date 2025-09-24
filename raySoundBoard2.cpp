#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

// Example sound list
std::vector<std::pair<std::string, std::string>> sounds = {
    {"Howl", "./resources/howl.mp3"},
    {"Beethoven", "./resources/Beethovenstrqrt4cminor.mp3"}
};

struct SoundSlot {
    int dropdownIndex;   // index of chosen sound, -1 = unassigned
    bool editMode;       // raygui dropdown state
    std::string label;   // button label
    Sound sound;         // loaded sound
    bool assigned;       // has a sound been chosen?
};

int main() {
    InitWindow(800, 600, "Soundboard Example");
    InitAudioDevice();

    // Preload all sounds once
    std::vector<Sound> loadedSounds;
    for (auto &p : sounds) {
        loadedSounds.push_back(LoadSound(p.second.c_str()));
    }

    // Initialize 15 slots, all unassigned
    std::vector<SoundSlot> slots(15);
    for (int i = 0; i < 15; i++) {
        slots[i].dropdownIndex = -1;
        slots[i].editMode = false;
        slots[i].label = "Unassigned";
        slots[i].assigned = false;
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (float i = 0; i < 15; i++) {
            float x = 50;
            float y = 40 + i * 35;

            // Build dropdown string: "Clap;Snare;Kick;HiHat"
            std::string dropdownItems;
            for (size_t j = 0; j < sounds.size(); j++) {
                dropdownItems += sounds[j].first;
                if (j < sounds.size() - 1) dropdownItems += ";";
            }

            // Dropdown
            if (GuiDropdownBox({x, y, 120, 30}, dropdownItems.c_str(),
                               &slots[i].dropdownIndex, slots[i].editMode)) {
                slots[i].editMode = !slots[i].editMode;
                if (slots[i].dropdownIndex >= 0) {
                    // Update label & assign sound
                    slots[i].label = sounds[slots[i].dropdownIndex].first;
                    slots[i].sound = loadedSounds[slots[i].dropdownIndex];
                    slots[i].assigned = true;
                }
            }

            // Button to play sound
            if (GuiButton({x + 140, y, 120, 30}, slots[i].label.c_str())) {
                if (slots[i].assigned) {
                    PlaySound(slots[i].sound);
                } else {
                    std::cout << "Slot " << i << " is unassigned!\n";
                }
            }
        }

        EndDrawing();
    }

    // Cleanup
    for (auto &s : loadedSounds) {
        UnloadSound(s);
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

