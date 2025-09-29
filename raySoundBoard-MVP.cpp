#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <iostream>
#include <vector>
#include <utility>

struct SoundData {
	std::string label;
	std::string path;
	Sound sound;
	bool loaded;
};


int main()
{
	InitWindow(1200, 1000, "raySoundBoard");
	InitAudioDevice();

	std::vector<SoundData> sounds = {
		{"Howl", "resources/howl.mp3", {}, false},
		{"thunderclap", "resources/thunderclap.mp3", {}, false},
		{"priceisright", "resources/priceisright.mp3", {}, false},
		{"laughter", "resources/laughter.mp3", {}, false},
		{"lizard", "resources/lizard.mp3", {}, false},
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
		{"wilhelm", "resources/wilhelm.mp3", {}, false},
		{"womanscream", "resources/womanscream.mp3", {}, false}
	};

	const char* selection_string = "Howl;Thunder;priceisright;laughter;lizard;buffy;rimshot;careless_whisper;chosen;consequences;ohmaigaa;OHMYGOD;riser;roundabout;slidewhistle;suspense_1;theremin;wilhelm;womanscream";
	int active = 0;
	bool dropdown = false;


	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		if (GuiDropdownBox((Rectangle){50,50,100,40}, selection_string, &active, dropdown))
		{
			if(sounds[active].loaded) UnloadSound(sounds[active].sound);
			sounds[active].sound = LoadSound(sounds[active].path.c_str());
			sounds[active].loaded = true;
			dropdown = !dropdown;
		}
		if (GuiButton((Rectangle){160,50,100,40}, sounds[active].label.c_str()))
		{
			PlaySound(sounds[active].sound);
		}

		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();
	return (0);
};

