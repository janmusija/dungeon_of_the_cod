//
// main.cpp
// 2026-10-17
// dungeon_of_the_cod
//

#include <iostream>
#include "worldgen/biome/biome.h"
#include "worldgen/biome/sky_islands.h"
#include <ncurses.h>
#include "render/render.h"
#include "gamedata_def.h"
#include <filesystem>

// compile with
// g++ main.cpp -o dotc -Wall -Wextra

void initialize_wcout(){
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
}

int testmain1(){
    Earth_Terrain t(0);
    t.export_images(0,0,1);
    t.export_images(0,0,4);
    t.export_images(0,0,16);
    Sky_Island_Terrain s(0);
    s.export_images(0,0,1);
    s.export_images(0,0,16);

    Heaven_Terrain h(0);
    h.export_images(0,0,16,"heaven");

    Hell_Terrain hl(0);
    hl.export_images(0,0,16,"hell");

    Outside_Terrain os(0);
    os.export_images(0,0,16,"outside");
    os.export_images(0,0,1,"outside");
    return 0;
}

int main() {
    { // important code
        std::filesystem::path mod = "mods/modthatclosesthegamewhenitopens";
        if (std::filesystem::exists(mod)) {
            return 0;
        }
    }
    { // ensure save directory exists
        std::filesystem::path savedir = "save";
        if (!std::filesystem::exists(savedir)) {
            std::filesystem::create_directory(savedir);
        }
    }
    std::cout << "Create new save or load a preexisting one? (new / load): ";
    std::string s;
    std::string sn;
    bool isloading = 0;
    while (std::cin >> s, s != "new" && s != "load"){
        std::cout << "Enter 'new' or 'load': ";
    }
    if (s == "new") {
        bool awaitname = true;
        while (awaitname){
            std::cout << "Enter name for new save: ";
            std::cin >> sn;
            std::cout << "You chose the name: '" << sn << "'. Is this correct? (y/n)";
            while (std::cin >> s, s != "y" && s != "n"  && s != "yes" && s != "no"  && s != "Y" && s != "N"){
                std::cout << "Enter 'y' or 'n': ";
            }
            if (s == "y" || s == "Y" || s == "yes"){
                std::filesystem::path savedir = "save";
                savedir = savedir / sn;
                if (std::filesystem::exists(savedir)){
                    std::cout << "This is already the name of an existing save! If you want to continue playing that save, relaunch and select it from the load menu instead!\n Are you sure you want to overwrite it instead and start afresh? (y/n)";
                    while (std::cin >> s, s != "y" && s != "n"  && s != "yes" && s != "no"  && s != "Y" && s != "N"){
                        std::cout << "Enter 'y' or 'n': ";
                    }
                    if (s == "y" || s == "Y" || s == "yes") {
                        awaitname = false;
                        std::filesystem::remove_all(savedir); // !!
                    }
                } else {
                awaitname = false;
                }
            }
        }
        std::filesystem::path sd = "save";
        sd = sd / sn;
        if (!std::filesystem::exists(sd)) {
            std::filesystem::create_directory(sd);
        }
        // TK: pick seed (allow player to decide whether to choose or let it be chosen randomly)
    } else if (s == "load"){
        isloading = 1;
        std::filesystem::path savedir = "save";
        std::cout << "Existing saves:\n";
        for (const auto & entry : std::filesystem::directory_iterator(savedir)) std::cout << entry.path().filename() << std::endl;
        std::cout << "which to load?\n";
        while (true){
            std::cin >> s;
            std::filesystem::path sd = savedir;
            sd = sd / s;
            if (std::filesystem::exists(sd)) {;
                break;
                sn = s;
            }else {
            std::cout << "Enter one of the savenames above (without quotes): ";
            }
        }
        // TK ? 
    }
    initialize_wcout();
    initscr();
    GAMEDAT g(0); // TK: seed; either loaded from save or given by new game creation
    g.savename = sn;
    // handle loading of save data if relevant
    
    // have player decide and load starting chunk / player's current position (depends based on if new save or loading)

    // then, gameloop: alternate between ticking the game and rendering. When g needs player input, instead getch() then (if necessary) rerender. 

    { // temp
    g.load_chunk("a");
    g.camera_chunk = &g.LOADED_CHUNKS["a"];
    g.render_game();
    getch();
    }
    endwin();
    return 0;
}

int testmain2(){
    initialize_wcout();
    initscr();
    register_color_pairs();

    printw("Hello World!");
    Fancy_Char a(L'a',3);
    std::wstring cp437 = L" \u263a\u263b\u2665\u2666\u2663\u2660\u2022\u25d8\u25cb\u25d9\u2642\u2640\u266a\u266b\u263c\u25ba\u25c4\u2195\u203c\u00b6\u00a7\u25ac\u21a8\u2191\u2193\u2192\u2190\u221f\u2194\u25b2\u25bc\u0020\u0021\u0022\u0023\u0024\u0025\u0026\u0027\u0028\u0029\u002a\u002b\u002c\u002d\u002e\u002f\u0030\u0031\u0032\u0033\u0034\u0035\u0036\u0037\u0038\u0039\u003a\u003b\u003c\u003d\u003e\u003f\u0040\u0041\u0042\u0043\u0044\u0045\u0046\u0047\u0048\u0049\u004a\u004b\u004c\u004d\u004e\u004f\u0050\u0051\u0052\u0053\u0054\u0055\u0056\u0057\u0058\u0059\u005a\u005b\u005c\u005d\u005e\u005f\u0060\u0061\u0062\u0063\u0064\u0065\u0066\u0067\u0068\u0069\u006a\u006b\u006c\u006d\u006e\u006f\u0070\u0071\u0072\u0073\u0074\u0075\u0076\u0077\u0078\u0079\u007a\u007b\u007c\u007d\u007e\u2302\u00c7\u00fc\u00e9\u00e2\u00e4\u00e0\u00e5\u00e7\u00ea\u00eb\u00e8\u00ef\u00ee\u00ec\u00c4\u00c5\u00c9\u00e6\u00c6\u00f4\u00f6\u00f2\u00fb\u00f9\u00ff\u00d6\u00dc\u00a2\u00a3\u00a5\u20a7\u0192\u00e1\u00ed\u00f3\u00fa\u00f1\u00d1\u00aa\u00ba\u00bf\u2310\u00ac\u00bd\u00bc\u00a1\u00ab\u00bb\u2591\u2592\u2593\u2502\u2524\u2561\u2562\u2556\u2555\u2563\u2551\u2557\u255d\u255c\u255b\u2510\u2514\u2534\u252c\u251c\u2500\u253c\u255e\u255f\u255a\u2554\u2569\u2566\u2560\u2550\u256c\u2567\u2568\u2564\u2565\u2559\u2558\u2552\u2553\u256b\u256a\u2518\u250c\u2588\u2584\u258c\u2590\u2580\u03b1\u00df\u0393\u03c0\u03a3\u03c3\u00b5\u03c4\u03a6\u0398\u03a9\u03b4\u221e\u03c6\u03b5\u2229\u2261\u00b1\u2265\u2264\u2320\u2321\u00f7\u2248\u00b0\u2219\u00b7\u221a\u207f\u00b2\u25a0\u00a0";
    std::wstring cp437mod = L"\u00a4\u263a\u263b\u2665\u2666\u2663\u2660\u2022\u25d8\u25cb\u25d9\u2642\u2640\u266a\u266b\u263c\u25ba\u25c4\u2195\u203c\u00b6\u00a7\u25ac\u21a8\u2191\u2193\u2192\u2190\u221f\u2194\u25b2\u25bc\u0020\u0021\u0022\u0023\u0024\u0025\u0026\u0027\u0028\u0029\u002a\u002b\u002c\u002d\u002e\u002f\u0030\u0031\u0032\u0033\u0034\u0035\u0036\u0037\u0038\u0039\u003a\u003b\u003c\u003d\u003e\u003f\u0040\u0041\u0042\u0043\u0044\u0045\u0046\u0047\u0048\u0049\u004a\u004b\u004c\u004d\u004e\u004f\u0050\u0051\u0052\u0053\u0054\u0055\u0056\u0057\u0058\u0059\u005a\u005b\u005c\u005d\u005e\u005f\u0060\u0061\u0062\u0063\u0064\u0065\u0066\u0067\u0068\u0069\u006a\u006b\u006c\u006d\u006e\u006f\u0070\u0071\u0072\u0073\u0074\u0075\u0076\u0077\u0078\u0079\u007a\u007b\u007c\u007d\u007e\u2302\u00c7\u00fc\u00e9\u00e2\u00e4\u00e0\u00e5\u00e7\u00ea\u00eb\u00e8\u00ef\u00ee\u00ec\u00c4\u00c5\u00c9\u00e6\u00c6\u00f4\u00f6\u00f2\u00fb\u00f9\u00ff\u00d6\u00dc\u00a2\u00a3\u00a5\u20a7\u0192\u00e1\u00ed\u00f3\u00fa\u00f1\u00d1\u00aa\u00ba\u00bf\u2310\u00ac\u00bd\u00bc\u00a1\u00ab\u00bb\u2591\u2592\u2593\u2502\u2524\u2561\u2562\u2556\u2555\u2563\u2551\u2557\u255d\u255c\u255b\u2510\u2514\u2534\u252c\u251c\u2500\u253c\u255e\u255f\u255a\u2554\u2569\u2566\u2560\u2550\u256c\u2567\u2568\u2564\u2565\u2559\u2558\u2552\u2553\u256b\u256a\u2518\u250c\u2588\u2584\u258c\u2590\u2580\u03b1\u00df\u0393\u03c0\u03a3\u03c3\u00b5\u03c4\u03a6\u0398\u03a9\u03b4\u221e\u03c6\u03b5\u2229\u2261\u00b1\u2265\u2264\u2320\u2321\u00f7\u2248\u00b0\u2219\u00b7\u221a\u207f\u00b2\u25a0\u20ac";
    for (int i = 0; i<16*16; i++){
        if (i < cp437mod.length()){
        render_char(1+(i%16),2+(i/16),Fancy_Char(cp437mod[i],1));
        }
    }
    refresh();

    refresh();
    getch();
    endwin();
    std::wcout << cp437mod;
    return 0;
}