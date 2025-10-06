#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <iostream>
#include <vector>
#include <utility>

#define RAYBLACK      (Color){ 20, 20, 20, 255 }        // Black

struct SoundData {
	std::string label;
	std::string path;
	Sound sound;
	bool loaded;
};

struct soundSlot {
	int active;
	bool dropdown;
};


int main()
{
	InitWindow(800, 600, "raySoundBoard");
	InitAudioDevice();

	//all our data
	std::vector<SoundData> sounds = {
		{"Howl", "resources/howl.mp3", {}, false},
		{"thunderclap", "resources/thunderclap.mp3", {}, false},
		{"priceisright", "resources/priceisright.mp3", {}, false},
		{"laughter", "resources/laughter.mp3", {}, false},
		{"wilhelm", "resources/wilhelm.mp3", {}, false},
		{"buffy", "resources/buffy.mp3", {}, false},
		{"rimshot", "resources/rimshot.mp3", {}, false},
		{"careless_whisper", "resources/careless_whisper.mp3", {}, false},
		{"chosen", "resources/chosen.mp3", {}, false},
		{"consequences", "resources/consequences.mp3", {}, false},
		{"ohmaigaa", "resources/ohmaigaa.mp3", {}, false},
		{"OHMYGOD", "resources/OHMYGOD.mp3", {}, false},
		{"riser", "resources/riser.mp3", {}, false},
		{"roundabout", "resources/roundabout.mp3", {}, false},
		{"slidewhistle", "resources/slidewhistle.mp3", {}, false},
		{"suspense_1", "resources/suspense_1.mp3", {}, false},
		{"theremin", "resources/theremin.mp3", {}, false},
		{"lizard", "resources/lizard.mp3", {}, false},
		{"womanscream", "resources/womanscream.mp3", {}, false}
	};
	std::vector<soundSlot> soundSlots(15, {0, false});
	const char* selection_string = "Howl;Thunder;priceisright;laughter;wilhelm;buffy;rimshot;careless_whisper;chosen;consequences;ohmaigaa;OHMYGOD;riser;roundabout;slidewhistle;suspense_1;theremin;lizard;womanscream";
	bool aimeemode = false; 

	//loads all sounds into memory at startup
	for (int i = 0; i < sounds.size(); i++) {
		sounds[i].sound = LoadSound(sounds[i].path.c_str());
		sounds[i].loaded = true;
	}

	for (int i = 0; i < soundSlots.size(); i++) {
		soundSlots[i].active = i;
	}
	//main loop
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYBLACK);

		if (aimeemode) {
			for (int i = 0; i < soundSlots.size(); i++) {
				soundSlots[i].active = 17; // Set all slots to "lizard"
			};
		}

		//Buttons and dropdowns and sounds logic
		for (int i = 0; i < soundSlots.size(); i++) {
				int col = i % 5;
				int row = i / 5;

    			float x = 50 + row + row * 240;
    			float y = 50 + col * 60;

    			if (GuiDropdownBox((Rectangle){x, y, 100, 40}, selection_string, &soundSlots[i].active, soundSlots[i].dropdown)) {
        			soundSlots[i].dropdown = !soundSlots[i].dropdown;
    			}

    			if (GuiButton((Rectangle){x + 110, y, 100, 40}, sounds[soundSlots[i].active].label.c_str())) {
        			PlaySound(sounds[soundSlots[i].active].sound);
    			}
		}
		if (GuiCheckBox((Rectangle){660, 350, 20, 20}, "Aimee Mode", &aimeemode)) {
			// Toggle Aimee Mode
		}

		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();
	return (0);
};

