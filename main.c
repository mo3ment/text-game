#include "raylib.h"
#include <string.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Rectangle game_screen = {0, 0, 800, 800};

    InitWindow(game_screen.width, game_screen.height, "Browser VN");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    typedef struct letter_pos {
        int x;
        int y;
        int size;
    } letter_pos;

    int size = 20;    

    char* strings[26] = {
                         "The rain fell softly, a gentle lullaby for the restless\nnight.",
                         "He couldn't shake the feeling that someone was watch-\ning him.",
                         "Her heart raced as she opened the mysterious letter.",
                         "The forest was eerily quiet, save for the occasional\nrustle of leaves.",
                         "She stared at the photograph, lost in memories.",
                         "A cat meowed, breaking the silence of the empty alley.",
                         "His footsteps echoed in the empty corridor.",
                         "The candle flickered, casting dancing shadows on the\nwalls.",
                         "She took a deep breath, steadying herself before the\nbig presentation.",
                         "The old house creaked with every gust of wind.",
                         "He found solace in the rhythmic crashing of the waves.",
                         "She whispered a silent prayer, hoping for a miracle.",
                         "The city lights sparkled like a sea of stars.",
                         "He couldn't help but laugh at the absurdity of it all.",
                         "The garden was overgrown, a testament to years of\nneglect.",
                         "She felt a chill run down her spine.",
                         "His hands trembled as he held the ancient artifact.",
                         "The sunset painted the sky with vibrant colors.",
                         "She danced alone, lost in her own world.",
                         "The distant thunder rumbled ominously.",
                         "He leaned against the tree, contemplating his next\nmove.",
                         "She wore a dress the color of the ocean.",
                         "The library was a haven of quiet and knowledge.",
                         "He watched as the snowflakes drifted gently to the\nground.",
                         "Her laughter was infectious, filling the room with joy.",
                         "The mountain peak was shrouded in mist, mysterious\nand alluring."
                        };

    int string_format[26][2] = {0}; // string_number, string_y_pos

    string_format[0][1] = MeasureText("0000000000", size);

    int string_number = 0;
    float counter = 0;
    int letter_count = 0;
    int next_page_string = 0;
    bool is_text_rolling = false;
    bool debug_lines_enabled = false;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here

        if ((IsKeyPressed(KEY_SPACE) && string_number < 26) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && string_number < 26))
        {
            if (!is_text_rolling)
            {
                is_text_rolling = true;
                letter_count = 0;
                string_number++;
            }
            else
            {
                letter_count = strlen(strings[string_number-1]);
                is_text_rolling = false;
            }
        }

        if (IsKeyPressed(KEY_LEFT_CONTROL))
        {
            debug_lines_enabled = !debug_lines_enabled;
        }

        if (is_text_rolling)
        {
            counter += GetFrameTime();  

            if (counter >= .01f)
            {
                letter_count++;
                counter = 0;
                if (letter_count > strlen(strings[string_number-1]))
                {
                    letter_count = strlen(strings[string_number-1]);
                    is_text_rolling = false;
                }
            }
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);

            DrawRectangleLinesEx(game_screen, 3.f, WHITE);

                for (int i = 0; i < string_number - next_page_string; i++)
                {

                    if (string_format[i][1] >= game_screen.width - MeasureText("0000000000", size))
                    {
                        next_page_string += i;

                        string_format[0][1] = MeasureText("0000000000", size);

                        break;
                    }

                    if (i == string_number - next_page_string - 1 )
                    {
                        DrawText(TextSubtext(strings[next_page_string+i], 0, letter_count), MeasureText("0000000000", size), string_format[i][1], size, WHITE);
                    }
                    else
                    {
                        DrawText(strings[next_page_string+i], MeasureText("0000000000", size), string_format[i][1], size, WHITE);
                    }

                    string_format[i+1][1] = string_format[i][1] + 2*1.1*size;
                    
                    for (int j = 0; j < strlen(strings[next_page_string+i]); j++)
                    {
                        if (strings[next_page_string+i][j] == '\n')
                        {
                            string_format[i+1][1] += 1.1*size;
                        }
                    }

                }

                if (debug_lines_enabled)
                {
                    DrawLine(MeasureText("0000000000", size), 0, MeasureText("0000000000", size), game_screen.height, WHITE);
                    DrawLine(game_screen.width - MeasureText("0000000000", size), 0, game_screen.width - MeasureText("0000000000", size), game_screen.height, WHITE);
                }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}