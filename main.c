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

    InitWindow(game_screen.width, game_screen.height, "When Snow Befalls Summit");

    //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    typedef struct letter_pos {
        int x;
        int y;
        int size;
    } letter_pos;

    int size = 30;    

    Font body_font = LoadFontEx("MSGOTHIC.TTF", 2*size, NULL, 0);

    SetTextureFilter(body_font.texture, TEXTURE_FILTER_ANISOTROPIC_16X);

    const char* caution_header = "CAUTION!";
    const char* caution_body = "This is a work of fiction. Names, characters, busines-\n   ses, places, events, locales, and incidents are\n either the products of the author's imagination or\n   used in a fictitious manner. Any resemblance to\n actual persons, living or dead, or actual events is\n                purely coincidental.";
    const char* control_info = " Before I let you experience the mystery of Planinar\n           village, let me remind you to...\n\n\n\n   Go into Fullscreen Mode using [F11] for a more\n     immersive experience, and press [SPACE] to\n                progress through text.";

    const int strings_size = 26;
    const char* strings[strings_size] = {
                         "It's getting dark again. It only makes sense, it's\
                         \n that time of the day. The sun hides behind the\
                         \nmountains and takes the light with it. One could\
                         \n think the sun was afraid of us.}n",
                         
                         "Hehe... what a silly idea.\n",
                         
                         "\"That rounds off my day, pretty much.\"\n",

                         "I've never really been a night owl. Alexander always\
                         \n teases me for it, saying that is because I'm afraid\
                         \nof the dark.\n",

                         "There is something to it, but I'll never give him the\
                         \n satisfaction of being right. It gets so dark around\
                         \nhere that it's hard to tell if your eyes are open\
                         \n or not. Like you're both awake and asleep, at the\
                         \nsame time.\n",

                         "\"Guh...............................\"\n",

                         "I'm too tired for this.\n",

                         "Sleep... it's one of those weird things I can't wrap\
                         \n my head around. Coming up for excuses to stay up, I\
                         \nentertain these thoughts of mine.\n",

                         "\"I wake up as tired as the night before.\"\n",

                         "Tea occasionally helps, but not enough for me to\
                         \n consistently get a good night's sleep. Mom and dad used\
                         \nto say that I rolled around a lot in my sleep, hehe.\n",

                         "But that was a long time ago. A lot has changed\
                         \n since then. Yeah...\n",

                         "\"...\"\n",

                         "This time around, it isn't mom and dad walking in\
                         \n and out of the house, but rather Alexander and Danica.\n",

                         "In a sense, nothing had changed. If the house\
                         \n had a mind of its own, it couldn't tell the\
                         \ndifference. Of course not.\n",

                         "To it, there's always been three pairs of legs\
                         \n exiting and entering the house, using it for company.\n",

                         "But to me, it will never be the same. The people\
                         \n that called it home are no longer with us. All of them.\n",


                         "\"Except for me, duh.\"\n",

                         "\"...\"\n",

                         "\".......\"\n",

                         "\".........................................\"\n",

                         "I wonder if that is the case sometimes. I mean...\n",

                         "I've changed since then. There's no doubt about it.\
                         \n Whilst I'm still in one shape, I died along with them.\n",

                         "In the darkest of days...",
                         
                         "when I feel the most alone\
                         \n in this house...\n",

                         "When my headache reminds me to not peer into the dark...\n",

                         "\"I wish I wasn't spared.\"\n"
                        };

    int string_format[13][2] = {0}; // string_number, string_y_pos

    string_format[0][1] = MeasureTextEx(body_font, "0000000", size, 0).x;

    int string_number = 0;
    float caution_countdown = 10.f; // 10 sec
    float counter = 0;
    int letter_count = 0;
    int next_page_string = 0;
    bool is_text_rolling = false;
    bool debug_lines_enabled = false;
    float loading_percentage = 0.f;
    float text_opacity = 0;
    bool fade_to_black = false;
    bool control_mode = false;
    int sentence_length = 0;
    float horizontal_padding = 0;

    int game_mode = 0;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here

        switch(game_mode)
        {
            case 0:
            {
                caution_countdown -= GetFrameTime();

                if (IsKeyPressed(KEY_Q))
                {
                    game_mode++;

                    is_text_rolling = true;
                    letter_count = 0;
                    string_number++;
                }

                else if (loading_percentage != 1)
                {
                    loading_percentage += GetFrameTime()/10;

                    if (loading_percentage >= 1.f)
                    {
                        loading_percentage = 1;
                    }
                }

                else if (loading_percentage == 1)
                {
                    if (!fade_to_black)
                    {
                        text_opacity += GetFrameTime();
                        if (text_opacity >= 1)
                        {
                            fade_to_black = true;
                        }
                    }
                    if (fade_to_black)
                    {
                        text_opacity -= GetFrameTime();
                        if (text_opacity < 0)
                        {
                            fade_to_black = false;
                        }
                    }

                    if ((IsKeyPressed(KEY_SPACE) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) && !control_mode)
                    {
                        control_mode = true;
                        fade_to_black = false;
                        text_opacity = 0;
                        loading_percentage = 0;

                        game_mode++;
                    }

                }
                break;
            }

            case 1:
            {
                if (!fade_to_black)
                {
                    text_opacity += GetFrameTime();
                    if (text_opacity >= 1)
                    {
                        fade_to_black = true;
                    }
                }

                if (fade_to_black)
                {
                    text_opacity -= GetFrameTime();
                    if (text_opacity < 0)
                    {
                        fade_to_black = false;
                    }
                }

                if ((IsKeyPressed(KEY_SPACE) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))))
                {
                    game_mode++;

                    is_text_rolling = true;
                    letter_count = 0;
                    //string_number++;
                }
                break;
            }

            case 2:
            {
                if ((IsKeyPressed(KEY_SPACE) && string_number < strings_size) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && string_number < strings_size))
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

                break;
            }
        }

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);

            //DrawRectangleLinesEx(game_screen, 3.f, WHITE);

            switch(game_mode)
            {
                case 0:
                {
                    DrawTextEx(body_font, caution_header, (Vector2) { game_screen.width / 2 - MeasureTextEx(body_font, caution_header, 2*size, 0).x / 2, game_screen.height / 4 - MeasureTextEx(body_font, caution_header, 2*size, 0).y / 2 }, 2*size, 0, WHITE);
                    DrawTextEx(body_font, caution_body, (Vector2) { MeasureTextEx(body_font, "0000000", size, 0).x, game_screen.height / 2 - MeasureTextEx(body_font, caution_body, size, 0).y / 2}, size, 0, WHITE);
                
                    if (loading_percentage < 1)
                    {
                        DrawRectangleLinesEx((Rectangle) { game_screen.width / 4 - 2, (game_screen.height / 4) * 3 - 30 / 2, game_screen.width / 2, 30 }, 2.f, WHITE);
                        DrawRectangle(game_screen.width / 4 - 2, (game_screen.height / 4) * 3 - 30 / 2, loading_percentage * (game_screen.width / 2), 30, WHITE);
                    }

                    else 
                    {
                        DrawTextEx(body_font, "Press [SPACE] to continue", (Vector2) {game_screen.width / 2 - MeasureTextEx(body_font, "Press [SPACE] to continue", size, 0).x / 2, (game_screen.height / 4) * 3 - MeasureTextEx(body_font, "Press [SPACE] to continue", size, 0).y / 2 }, size, 0, Fade(WHITE, text_opacity));
                    }

                    break;
                }

                case 1:
                {
                    DrawTextEx(body_font, control_info, (Vector2) { MeasureTextEx(body_font, "0000000", size, 0).x, game_screen.height / 2 - MeasureTextEx(body_font, control_info, size, 0).y / 2}, size, 0, WHITE);
                    DrawTextEx(body_font, "Press [SPACE] to continue", (Vector2) {game_screen.width / 2 - MeasureTextEx(body_font, "Press [SPACE] to continue", size, 0).x / 2, (game_screen.height / 4) * 3 - MeasureTextEx(body_font, "Press [SPACE] to continue", size, 0).y / 2 }, size, 0, Fade(WHITE, text_opacity));

                    break;
                }

                case 2:
                {
                    for (int i = 0; i < string_number - next_page_string; i++)
                    {
                        if (string_format[i][1] >= game_screen.width - MeasureText("0000000", size))
                        {
                            next_page_string += i;

                            string_format[0][1] = MeasureText("0000000", size);

                            break;
                        }

                        if (i == string_number - next_page_string - 1)
                        {
                            if (horizontal_padding == 0 || i == 0)
                            {
                                DrawTextEx(body_font, TextSubtext(strings[next_page_string+i], 0, letter_count), (Vector2) { MeasureTextEx(body_font, "0000000", size, 0).x, string_format[i][1] }, size, 0, WHITE);
                            }
                            else
                            {
                                DrawTextEx(body_font, TextSubtext(strings[next_page_string+i], 0, letter_count), (Vector2) { MeasureTextEx(body_font, "0000000", size, 0).x + horizontal_padding, string_format[i][1] }, size, 0, WHITE);
                            }
                        }
                        else
                        {
                            if (horizontal_padding == 0)
                            {
                                DrawTextEx(body_font, strings[next_page_string+i], (Vector2) { MeasureTextEx(body_font, "0000000", size, 0).x, string_format[i][1] }, size, 0, WHITE);
                            }
                            else
                            {
                                DrawTextEx(body_font, strings[next_page_string+i], (Vector2) { MeasureTextEx(body_font, "0000000", size, 0).x + horizontal_padding, string_format[i][1] }, size, 0, WHITE);
                            }
                        }

                        string_format[i+1][1] = string_format[i][1] + 2*32;
                        
                        for (int j = 0; j <= strlen(strings[next_page_string+i]); j++)
                        {
                            if (strings[next_page_string+i][j] == '\n')
                            {
                                sentence_length = 0;
                                string_format[i+1][1] += 32;
                            }
                            else if (strings[next_page_string+i][j] == '\0')
                            {
                                if (sentence_length > 1)
                                {
                                    string_format[i+1][1] -= 2*32;
                                    horizontal_padding = MeasureTextEx(body_font, " ", size, 0).x * (sentence_length-1);
                                }
                                else if (sentence_length == 1)
                                {
                                    horizontal_padding = 0;
                                }
                            }
                            sentence_length++;
                        }

                    }

                    if (debug_lines_enabled)
                    {
                        DrawLine(MeasureTextEx(body_font, "0000000", size, 0).x, 0, MeasureTextEx(body_font, "0000000", size, 0).x, game_screen.height, WHITE);
                        DrawLine(game_screen.width - MeasureTextEx(body_font, "0000000", size, 0).x, 0, game_screen.width - MeasureTextEx(body_font, "0000000", size, 0).x, game_screen.height, WHITE);
                    }

                    break;
                }
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