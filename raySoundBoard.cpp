#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <iostream>

//credit to Raysan's Audio Stream Effects example for this algorithm
static void AudioProcessEffectLPF(void *buffer, unsigned int frames)
{
    static float low[2] = { 0.0f, 0.0f };
    static const float cutoff = 70.0f/44100.0f; // 70 Hz lowpass filter
    const float k = cutoff/(cutoff + 0.1591549431f); // RC filter formula

    // Converts the buffer data before using it
    float *bufferData = (float *)buffer;
    for (unsigned int i = 0; i < frames*2; i += 2)
    {
        const float l = bufferData[i];
        const float r = bufferData[i + 1];

        low[0] += k*(l - low[0]);
        low[1] += k*(r - low[1]);
        bufferData[i] = low[0];
        bufferData[i + 1] = low[1];
    }
}

int main()
{
	InitWindow(800, 600, "raySoundBoard");
	InitAudioDevice();

	Sound howl = LoadSound("./resources/howl.mp3");
	Music music = LoadMusicStream("./resources/Beethovenstrqrt4cminor.mp3");
	bool is_playing = false;
	bool lpf = false;
	bool lpf_attached = false;
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		UpdateMusicStream(music);
		SetMusicVolume(music, 1.0);
		DrawText("Hello, World!", 320, 300, 32, GRAY);
		if (GuiButton((Rectangle){50,50,100,40}, "Play Sound"))
		{
			PlaySound(howl);
		}

		if (GuiButton((Rectangle){50,100,100,40}, "Play Music"))
		{
			std::cout << "Pressed!" << std::endl;
			if(is_playing)
			{
				is_playing = false;
				StopMusicStream(music);
			}
			else
			{
				is_playing = true;
				PlayMusicStream(music);
			}

		}
		GuiCheckBox((Rectangle){200,100,20,20}, "LPF", &lpf);
		if (lpf)
		{
			if (!lpf_attached)
			{
				AttachAudioStreamProcessor(music.stream, AudioProcessEffectLPF);
				lpf_attached = true;
			}
		}
		else
		{
			if (lpf_attached)
			{
				DetachAudioStreamProcessor(music.stream, AudioProcessEffectLPF);
				lpf_attached = false;
			}
		}
		EndDrawing();
	}
	UnloadMusicStream(music);
	UnloadSound(howl);
	CloseAudioDevice();
	CloseWindow();
	return (0);
};

