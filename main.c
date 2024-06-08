#include "raylib.h"
#include <string.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Rectangle game_screen = {0, 0, 1000, 1000};

    InitWindow(game_screen.width, game_screen.height, "Browser VN");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    typedef struct letter_pos {
        int x;
        int y;
        int size;
    } letter_pos;

    int size = 30;    

    Font bread_font = LoadFont("MSGOTHIC.TTF");

    char* strings[22] = {
                         "It's getting dark again. The sun slowly melts into\nthe ground and takes back the light it gave to the\nvillage. What a shame, I think to myself.",
                         "\"That rounds off my day, pretty much.\"",
                         "I've never really been a night owl. Alexander always\nteases me for it, saying that is because I'm afraid\nof the dark.",
                         "After involuntarily yawning, I decide it's best for\nme to go to sleep.",
                         "Sleep... it's one of those weird things I can't wrap\nmy head around. Coming up for excuses to stay up, I\nentertain these thoughts of mine.",
                         "\"I wake up as tired as the night before.\"",
                         "Tea occasionally helps, but not enough for me to\nconsistently get a good night's sleep. Mom and dad used\nto say that I rolled around a lot in my sleep, hehe.",
                         "But that was a long time ago. A lot has changed\nsince then. Yeah...",
                         "\"...\"",
                         "This time around, it isn't mom and dad walking in\nand out of the house, but rather Alexander and Danica.",
                         "In a sense, nothing hadn't changed. If the house\nhad a mind of its own, it couldn't tell the\ndifference. Of course not.",
                         "To it, there's always been three pairs of legs\nexiting and entering the house, using it for company.",
                         "But to me, it will never be the same. The people\nthat called it home are no longer with us. All of them.",
                         "\"Except for me, duh.\"",
                         "\"...\"",
                         "\".......\"",
                         "\".........................................\"",
                         "I wonder if that is the case sometimes. I mean...",
                         "I've changed since then. There's no doubt about it.\nWhilst I'm still in one shape, I died along with them.",
                         "In the darkest of days.. when I feel the most alone\nin this house...",
                         "When my headache reminds me to not peer into the dark...",
                         "\"I wish I wasn't spared.\""
                        };

    int string_format[22][2] = {0}; // string_number, string_y_pos

    string_format[0][1] = MeasureTextEx(bread_font, "0000000", size, 0).x;

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

        if ((IsKeyPressed(KEY_SPACE) && string_number < 22) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && string_number < 22))
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

            //DrawRectangleLinesEx(game_screen, 3.f, WHITE);

                for (int i = 0; i < string_number - next_page_string; i++)
                {

                    if (string_format[i][1] >= game_screen.width - MeasureText("0000000", size))
                    {
                        next_page_string += i;

                        string_format[0][1] = MeasureText("0000000", size);

                        break;
                    }

                    if (i == string_number - next_page_string - 1 )
                    {
                        DrawTextEx(bread_font, TextSubtext(strings[next_page_string+i], 0, letter_count), (Vector2) { MeasureTextEx(bread_font, "0000000", size, 0).x, string_format[i][1] }, size, 0, WHITE);
                    }
                    else
                    {
                        DrawTextEx(bread_font, strings[next_page_string+i], (Vector2) { MeasureTextEx(bread_font, "0000000", size, 0).x, string_format[i][1] }, size, 0, WHITE);
                    }

                    string_format[i+1][1] = string_format[i][1] + 2*32;
                    
                    for (int j = 0; j < strlen(strings[next_page_string+i]); j++)
                    {
                        if (strings[next_page_string+i][j] == '\n')
                        {
                            string_format[i+1][1] += 32;
                        }
                    }

                }

                if (debug_lines_enabled)
                {
                    DrawLine(MeasureTextEx(bread_font, "0000000", size, 0).x, 0, MeasureTextEx(bread_font, "0000000", size, 0).x, game_screen.height, WHITE);
                    DrawLine(game_screen.width - MeasureTextEx(bread_font, "0000000", size, 0).x, 0, game_screen.width - MeasureTextEx(bread_font, "0000000", size, 0).x, game_screen.height, WHITE);
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