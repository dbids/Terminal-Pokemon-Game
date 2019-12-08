using namespace std;
#include <time.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include "Input_Handling.h"
#include "Attack_Types.h"

//Default constructor which gets a random attack type
Attack_Types::Attack_Types()
{
    int attack_choice = rand() % 10; //Generates random number between 0-9
    switch(attack_choice)
    {
        case 0:
            name = "QuickAttack";
            physical_damage = 8;
            magical_damage = 0;
        break;
        case 1:
            name = "Earthquake";
            physical_damage = 4;
            magical_damage = 13;
        break;
        case 2:
            name = "HyperBeam";
            physical_damage = 0;
            magical_damage = 20;
        break;
        case 3:
            name = "Psychic";
            physical_damage = 7;
            magical_damage = 2;
        break;
        case 4:
            name = "Blizzard";  
            physical_damage = 5;
            magical_damage = 12;
        break;
        case 5:
            name = "Spore";
            physical_damage = 5;
            magical_damage = 5;
        break;
        case 6:
            name = "FireSpin";
            physical_damage = 0;
            magical_damage = 30;
        break;
        case 7:
            name = "Scratch";
            physical_damage = 3;
            magical_damage = 0;
        break;
        case 8:
            name = "Bubble";
            physical_damage = 0;
            magical_damage = 4;
        break;
        default:
            name = "DrillPeck";
            physical_damage = 10;
            magical_damage = 0;
        break;
    }
}

//Constructor for attack_types used by Pikachu and Bulbasaur
Attack_Types::Attack_Types(string& in_name)
{
    static int pikachu_moves = 0;
    static int bulbasaur_moves = 0;
    if (in_name == "Pikachu" && pikachu_moves == 0)
    {
        name = "ThunderShock";
        physical_damage = 6.8;
        magical_damage = 11.1;
        pikachu_moves = 1;
    }
    else if (in_name == "Pikachu" && pikachu_moves == 1)
    {
        name = "ThunderBolt";
        physical_damage = 6.8;
        magical_damage = 11.1;
        pikachu_moves = 0;
    }
    else if (in_name == "Bulbasaur" && bulbasaur_moves == 0)
    {
        name = "LeafStorm";
        physical_damage = 12;
        magical_damage = 12;
        bulbasaur_moves = 0; 
    }
    else if (in_name == "Bulbasaur" && bulbasaur_moves == 1)
    {
        name = "Cut";
        physical_damage = 4;
        magical_damage = 0;
        bulbasaur_moves = 0; 
    }
}

double Attack_Types::getMagDamage()
{
    return magical_damage;
}

double Attack_Types::getPhyDamage()
{
    return physical_damage;
}

string Attack_Types::getName()
{
    return name;
}

//Used for loading
Attack_Types::Attack_Types(std::string& in_name, double in_mag_dmg, double in_phy_dmg)
{
    name = in_name;
    magical_damage = in_mag_dmg;
    physical_damage = in_phy_dmg;
}

//Prints out an image for the attack given the name
void Attack_Types::printAttack()
{
    if (name == "QuickAttack")
    {
        cout << R"( 
[_/~\_/~\  ()  ()                /` \|      /         ;\_/~\_/~\_/~\_]
[\\\\\\\\`-.___             ___.' .-.`.---.|           \\\\\\\\\\\\\\]
[\\\\\\\\\\`\|```-..___,.-'`\| / /   /     |            `\\\\\\\\\\\\]
[\==\\==\\==````````\|``````,`/ /   /   ,  /              \\==\\==\\=]
[==``==``== ````````````````|\ /   /    |\/                \\``==``==]
[/==//==//==//````````,```.'`-;   '     \/                \\\\==\\==\]
[//////////////``,````|\-'  .'   ,   .-'`           ,/     \\\\\\\\\\]
[//////////////.-|\--;`` .-'     |\.'              /      \\\\\\\\\\\]
[/////////////( `"'-.|\ (___,.--'`'             _-'      \\\\\\\\\\\\]
----------------------------------------------------------------------
        )" << '\n';
    }
    else if (name == "Earthquake")
    {
        cout << R"(
|_______________________\\___,-'\:::/`-,___//______________________/:|
|:\_  `    `  \\ \\ \\   \\ /:::_:::_:::\ //   // __//  `    `  _/:::|
|:::\_   `     \\ \\ \\   \/:::/:,:.:\:::\/   // /:::\     `  _/:::::|
|:::::\_    `   \____ \\  /:::/:/:::\:\:::\  // _\:::/   `  _/:::::::|
|:::::::\_      /::::\ \\ \:::\:\:::/:/:::/ // /::::\     _/:::::::_-|
|   ::::::\_  ` \::::/  \\ \:::\:._.:/:::/ // _\::::/ ` _/::::::_-"  |
|"-_   :::::\_   /::::\_.._ \____--____-/_.._/::::\`  _/:::::_-"   _-|
|   "-_   ::::\_ \::::/::::\/::::\/::::\/::::\::::/ _/::::_-"   _-"::|
|      "-_   :::\_`""`\::::/\::::/\::::/\::::/`""`_/:::_-"   _-":::::|
----------------------------------------------------------------------

         )" << '\n';
    }
    else if (name == "HyperBeam")
    {
        cout << R"( 
x""\__\\\\\ __   __   __   __   __   __   __   __   __   __-\---\\\\x
x-) /_ \\\\\/ _\ / _\ / _\ / _\ / _\ / _\ / _\ / _\ / _\ / _\_/\_ \\\x
x -)  \ \\\/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ /__/ / /  __\ \\x
x  -) / /   /-----/   /-----/   /-----/   /-----/   /------/  /---. \x
x   -< < // >----< // >----< // >----< // >----< // >-----<---->---> x
x  -) \ \__ \-----\__ \-----\__ \-----\__ \-----\__-\------\  \__'' /x
x  ) _/ ///\ \__\ \__\ \__\ \__\ \__\ \__\ \__\ \__\ \__\ \_\_  _/ //x
x-) \__/////\__/ \__/-\__/ \__/-\__/ \__/-\__/ \__/-\__/ \__/-\/- ///x
x),,/  /////                                                -/-  ////x
----------------------------------------------------------------------
        )" << '\n';
    }
    else if (name == "Psychic")
    {
        cout << R"( 
}-|  '-,|----/   /  /   / .' . ' _=_ ' . '. \   \  \   \-----|  '-,|-{
} |-,   '   /   /  /   / /     q(-_-)p     \ \   \  \   \    '-,   | {
} |  '-,|   |   |  |  | ;      '_) (_`      ; |  |  |   |    |  '-,| {
} |-,   '   |   \  .  | |      /__/  \      | |  .  /   |    '-,   | {
} |  '-,|    \   \    | ;    _(<_   / )_    ; |    /   /     |  '-,| {
} |-,   '     \   \    \ \  (__\_\_|_/__)  / /    /   /      '-,   | {
} |  '-,| ,,-,-\,-.\,-. ,,-. ,-,-. ,-.-. ,-.. ,-./,-./-.-... |  '-,| {
} |-,   '(( (  (   (   '(   ' (   '   ) '   )'   )   )  ) )))'-,   | {
} |  '-,| \\ \  \   \    \    ,\     /.    /    /   /  / /// |  '-,| {
----------------------------------------------------------------------
        )" << '\n';
    }
    else if (name == "Blizzard")
    {
        cout << R"( 
._._._,-_-___-_,___._..__,' ,' ,' ,' ,'`._._.,-_-___- ,___._..,-_-__|
|   '  '   (    (    '  '/ ,' ,' ,' ,'.`. \       (    (    '  '     |
|-'-'`';      )     ,'--| ,  / ,' ,'`. \ \ |` ;      )     ,'-`-'`-'`|
|      ;   ;;    /\/    | | | | ,'"`. | | | | ;   ;;    /\/          |
|       |  ;`,  ,  `    | | | | `._.' | | | |  |  ;`,  ,  `          |
|       ; |  | |         | \ \ `.,' .' /  ' |  ; |  | |              |
|~`'^`'~; ;,_`,'-=~'`^-.  \ `.`,' ,' ,' ,' / .-; ;  `,'~`'^`'~=-.,__,|
|        |;   |            `.,' ,' ,' ,' ,'     |;   |               |
|^`'~=-.,||,.-=~'`^`'~=-.  ,' ,' ,' ,' ,'  .,.-'||~`'^`'~=-.,__,.-=~'|
----------------------------------------------------------------------
        )" << '\n';
    }
    else if (name == "Spore")
    {
        cout << R"( 
M_\ \_______\**/__\ \_____________A_______;_______/ /__\**/_______/ /M
M  \ \       **    \ \  |   ,--,-/ \---,-/|  ,   / /    **       / / M
M   \ \      **     \ \_|\,'. /|      /|   `/|-./ /     **      / /  M
M    \ \     **    \`.'    /|      ,            `;.     **     / /   M
M    *\ \    **   ,'\   A     A         A   A _ /| `.;  **    / /    M
M\   **\ \   ** ,/                 A       _  / _   /|  ;*   / /*   /M
M \  ** \ \  **/\    \,  ,  ,           A  /    /     `/|*  / /**  / M
M\ \ **  \ \ */   \,            ,     ,             ,/  \* / / ** / /M
M \ \**   \ \/  \,   `.\, ,-      ,       ,   ,/ ,/      \/ /  **/ / M
----------------------------------------------------------------------
        )" << '\n';
    }
    else if (name == "FireSpin")
    {
        cout << R"( 
(___/(_______ =====   ;__;__;____/(___;__;___;  =======  _______)\___)
;  .::::/~\/:: =====  ```````/)`(  \``/)`````` =======  ::\/~\:::..  ;
) .::::/~\/::  ======  ```(``/( ) * ) /(`````   =======  ::\/~\::... (
;.::::/~\/:  =======    ``)\( ,) \#//( ,)/(`` ,   ======  ::\/~\::...;
(::::/~\/  ========   ( `/  )\#(\",(  \\#) )`((   =======  ::\/~\:...)
;:::/~\/:: ========   )\(   (,") ) ) , )/ (  ) \   ======  :::\/~\:..;
)::/~\/::  =======   /  )) . )/  (( # (( , )/   )  ======  ::::\/~\..(
;:/~\/::::  ======  ( * (`\#/(`# ) `#/```#/(  '(  =======  :::::\/~\ ;
(/~\/::::::  ======  \#/ `"!' "#'` "!' `"#' "#/` =======  :::::::\/~\)
----------------------------------------------------------------------
        )" << '\n';
    }
    else if (name == "Scratch")
    {
        cout << R"( 
(_,;_/(_.,'"""`"". ,~""`:. ,~""`:. ,~""`:. ,~""`:. ,'"""`"".,_)\__.,_)
;   .   |      `::|     `:|     `:|     `:|     `:|      `::|        ;
)       |      .::|     .:|     .:|     .:|     .:|      .::|   '    (
;   )   |      .::|`.  .;' `.  .;' `.  .;'.`.  .;'|      .::| ,   )  ;
( ,   ' |      .::|  `.'     `.'     `.'     `.'  |.     .::|.  '  . )
;     , |.     .:|'    ,|                   |.    `|     .::|,' )( .);
) .' ) (`|     .:|    / |                   |`\    |     .:|'  ,    ((
; , ( .  |     .:|   /' \ /\             /\ / `\   |.    .:|(' , ). ;;
(,(. ), ) |    :|',;/'   /  \__/\___/\__/  \   :\;,`|   .:|.,)  (_,),) 
----------------------------------------------------------------------
        )" << '\n';
    }
    else if (name == "Bubble")
    {
        cout << R"( 
{--------------------------------------------------------------------}
{-.:*~*:._.:*~*:._((((}{)  ----=====((((}{)    --=((((}{)            }
{                                          -.:*~*:._.:*~*:._=((((}{) }
{--==((((}{)    --.:*~*:._.:*~*:._(((}{)                             }
{                                        .:*~*:._.:*~*:._=(((}{)     }
{*:._.:*~*:._=(((}{)                                                 }
{                     -.:*~*:._.:*~*:._=((((}{) ----=====((((}{)     }
{                                                                    }
{:*~*:._==((((}{)   ----==((((}{)          -.:*~*:._.:*~*:._=((((}{) }
{---------------------------------------------------------------------
        )" << '\n';
    }
    else if (name == "DrillPeck")
    {
        cout << R"( 
/_____/^  /____/-^/___/^ /___/^^/ A \^^\___\ ^\___\^-\____\  ^\______\
\    /^  /    /-^/   /^ /   /  / ( ) \  \   \ ^\   \^-\    \  ^\     /
/   /^  /    /-^/   /^ /   /  /  / \  \  \   \ ^\   \^-\    \  ^\    \
\  /^  /    /-^/   /  / .=-~~-^- ) ( -^-~~-=. \  \   \^-\    \  ^\   /
/ /^  /    /-^/   /  ~'`'` ` ``'/   \'`'` ` ``'~  \   \^-\    \  ^\  \
\/^  /    /-^/    ~'`'`'`'`'`'`'     '`'`'`'`'`'`'~    \^-\    \  ^\ /
/^  /    /-^/  =',','"='='='='-'-\^/-'-'='='='="',','=  \^-\    \  ^\\
\  /    /-^/  ='`"='-  /  /   "='/:\'="   \  \  -'="`'=  \^-\    \  ^/
/ /    /-^/  '-- /    /^^/    '"/.|.\"'    \^^\    \ --'  \^-\    \  \
----------------------------------------------------------------------
        )" << '\n';
    }
    else if (name == "ThunderShock")
    {
        cout << R"( 
__________________(_((_________)-'_))_________(((_________))_)________
\\  (_ , /\  ,_/          _/  /   \_( ' ,_) ) \_/    \_  \          //
//    '--\ `\--`         /  _/     `(_ , /\  ,_/       \  \_        \\
\\       _\ _\         _/  /          '--\ `\--`        \__ \       //
//       `\ \         / __/              _\ _\             \ \_     \\
\\        _\_\      _/ /                  _\_\              \__\    //
//        `\\      /__/                   `\\                 `\\   \\
\\      -.'.`\.'.-//-.'.`.'.-          -.'.`\\`.'.-       -.'.`.'\' //
----------------------------------------------------------------------
        )" << '\n';
    }
    else if (name == "ThunderBolt")
    {
        cout << R"( 
/(_ , /\  ,_/---//-----_/  /-,--,-/: :\/': :`\/: :\--\_( ' ,_) ) \_/-\
\  '--\ `\--`  //     /  _/ |`;  ' `,'   `.;    `: |  `(_ , /\  ,_/  /
/     _\ _\    \    _/  /   |    |     |  '  |     |.    '--\ `\--`  \
\     `\ \     /   / __/    | :  |     |  :  |     ||       _\ _\    /
/\__   _\_\      _/ /       | :. |  :  |  :  |  :  | \       _\ _\   \
\ \ \  `\\      /__/         \__/: :.. : :.. | :.. |  )  /   _\_\    /
/ /_    `\\    //          \_  _  `---',\___/,\___/ /'   \    _\_\   \
\  / -.'.`\.'.//-.'.`.'.-   /_/    _   `==._ .. . /'    \/    `\\    /
/     -.'.`\.--.'.`.'.-    /     \/ \_      `-::-'      /  -.'.`\\`  \
----------------------------------------------------------------------
        )" << '\n';
    }
    else if (name == "LeafStorm")
    {
        cout << R"( 
{--------------------------------------------------------------------}
{-------=========((((}{)  ----=====((((}{)  --=((((}{)               }
{                                            -------=========((((}{) }
{--==((((}{)          --------====(((}{)                             }
{                                             ------====(((}{)       }
{------====(((}{)    -----==((((}{)                                  }
{                        ------=========((((}{) ----=====((((}{)     }
{                                                                    }
{------=====((((}{)   ----==((((}{)          -------=========((((}{) }
{---------------------------------------------------------------------
        )" << '\n';
    }
    else
    {
        cout << R"(
|____________________________________________________________________\
|    /_   _\ --=  ;  -=- __/ \__  ---  \ / --    /_   _\  -- ; -=- ! /
| --=  \ /  -- __/ \__ --\     / --=-=- ;   HIT!   \ / -- __/ \__  H \
| ----====---- \     /   /_   _\--   ;        -=----      \     /  I /
|     ;  HIT!  /_   _\ --- \ /    __/ \__ --==- ;  -=-    /_   _\  T \
|  __/ \__  ---  \ /  -==-  '  -  \     /    __/ \__ --=--  \ / -= ! /
--------------------------------------------------------------------- 
        )" << '\n';
    }
}