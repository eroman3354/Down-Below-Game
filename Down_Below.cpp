#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
#define WIDTH1 13 // dimensions of rooms
#define HEIGHT1 7
#define WIDTH2 1
#define HEIGHT2 7
int MAX_EXP = 5; //in order to change max experience in multiple functions

class HERO{
public:
    std::string name;
    int attack;
    int defense;
    int health;
    int exp; // when it reaches MAX_EXP, you level up
    int x; // x coordinate
    int y; // y coordinate

    void levelUp();
    void playerPosition(int width, int height);
};

class ENEMY{
public:
    std::string name;
    int attack;
    int defense;
    int health;
    int exp_reward;
    int x; // x coordinate
    int y; // y coordinate
};

struct OBJECT{
    char symbol; //symbol that prints on the map
    int x;
    int y;

    //objectCollision(HERO h); // add a function that makes player position go back to previous state (change this struct to a class)
};

void delay(float x);

void fight(HERO &h, ENEMY &e);

void generateRoom(int width, int height, HERO &h, ENEMY &e, OBJECT &o);

void fightAnimation();

void swordAnimation();

void deathAnimation();

void treasureAnimation();

void printRules();

void singleplayer(); //storymode

void versus(); //two player versus mode

int main(void)
{
    system("clear");
    std::cout << "Welcome to...\n";
    delay(2);
    srand(unsigned(time(NULL)));

    while(true){
        //print out main menu
        system("clear");
        std::cout << "* * * * * * * * * * * * * * *\n";
        std::cout << "*  ,---.         ,--.       *\n";
        std::cout << "*  |    \\        |   )      *\n";
        std::cout << "*  |     |       |--:       *\n";
        std::cout << "*  |    / OWN    |   )ELOW  *\n";
        std::cout << "*  '---'         '--'       *\n";
        std::cout << "* * * * * * * * * * * * * * *\n\n";
        delay(2);
        std::cout << "Singleplayer        (enter s)\n";
        std::cout << "Versus              (enter v)\n";
        std::cout << "Rules/Instructions  (enter r)\n";
        char gamemode;
        std::cin.get(gamemode);
        while(gamemode != 's' && gamemode != 'v' && gamemode != 'r'){
            std::cin.clear();
            while(std::cin.get() != '\n'){}
            system("clear");
            std::cout << "* * * * * * * * * * * * * * *\n";
            std::cout << "*  ,---.         ,--.       *\n";
            std::cout << "*  |    \\        |   )      *\n";
            std::cout << "*  |     |       |--:       *\n";
            std::cout << "*  |    / OWN    |   )ELOW  *\n";
            std::cout << "*  '---'         '--'       *\n";
            std::cout << "* * * * * * * * * * * * * * *\n\n";
            std::cout << "Invalid input! Select your gamemode.\n\n";
            std::cout << "Singleplayer        (enter s)\n";
            std::cout << "Versus              (enter v)\n";
            std::cout << "Rules/Instructions  (enter r)\n";
            std::cin.get(gamemode);

        }
        std::cin.clear();
        while(std::cin.get() != '\n'){}
        switch(gamemode){
            case 's':
                singleplayer();
                break;
            case 'v':
                versus();
                break;
            case 'r':
                printRules();
                break;
        }
    }

    return 0;
}

void singleplayer() // singleplayer story mode
{
    HERO Hero;
    Hero.attack = 2;
    Hero.defense = 0;
    Hero.health = 6;
    Hero.exp = 0;
    MAX_EXP = 5;
    system("clear");
    std::cout << "Enter your name: ";
    std::getline(std::cin, Hero.name);
    system("clear");
    std::cout << "Welcome, " << Hero.name << "!\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    std::cout << "You wake up in a cold puddle, your vision slowly returning. As you sit up, you try to make out the little you can see of your surroundings.\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    std::cout << "It's a dark, windowless room with nothing but a decaying wood chair, some sort of circular vase, and the narrow door.\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    std::cout << "The last thing you remember before waking up here was coming across some sort of treasure...\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    std::cout << "Wait a minute, did that vase just move?\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    // set necessary objects and structures for desired map generation and fighting
    Hero.x = WIDTH1 / 2;
    Hero.y = HEIGHT1 / 2;
    ENEMY Blob;
    Blob.x = WIDTH1 - 1;
    Blob.y = HEIGHT1 - 1;
    Blob.name = "Blob";
    Blob.attack = 1;
    Blob.defense = 0;
    Blob.health = 3;
    Blob.exp_reward = 5;
    OBJECT Door;
    Door.x = 0;
    Door.y = HEIGHT1 / 2;
    Door.symbol = '#';
    bool room_key = 0;
    bool fight_complete = 0;
    while(true){
        system("clear");
        generateRoom(WIDTH1, HEIGHT1, Hero, Blob, Door);
        Hero.playerPosition(WIDTH1, HEIGHT1);
        // hero-object & hero-enemy interactions
        if(Hero.x == Blob.x && Hero.y == Blob.y){
            if(fight_complete == 0){
                fight(Hero, Blob);
                std::cout << "* You obtained the room key *\n";
                std::cout << "\n(Hit enter to continue)\n";
                while(std::cin.get() != '\n'){}
                system("clear");
                fight_complete = 1;
                room_key = 1;
            }
            else if(fight_complete == 1){
                std::cout << "The defeated blob lies on the floor.\n";
                std::cout << "\n(Hit enter to continue)\n";
                while(std::cin.get() != '\n'){}

            }
        }
        if(Hero.x == Door.x && Hero.y == Door.y){
            system("clear");
            if(room_key == 0){
                std::cout << "The door is locked.\n";
                std::cout << "\n(Hit enter to continue)\n";
                while(std::cin.get() != '\n'){}
            }
            else if(room_key == 1){
                break;
            }
        }
    }    
    system("clear");
    std::cout << "That was pretty easy, but you need to get out before more of those things show up.\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    std::cout << "You try to exit through the door, but it's locked. Use the room key? (y/n)\n";
    char use_key;
    std::cin.get(use_key);
    while(use_key != 'y' && use_key != 'n'){
        while(std::cin.get() != '\n'){}
        system("clear");
        std::cout << "Invalid input! Use the room key? (y/n)\n";
        std::cin.get(use_key);
    }
    while(std::cin.get() != '\n'){}
    Blob.exp_reward = 2;
    while(use_key == 'n'){ //player didn't use key and continues to wait in room until another fight
        system("clear");
        std::cout << "You sit down and wait in the room until another one of those things shows up.\n";
        std::cout << "\n(Hit enter to continue)\n";
        while(std::cin.get() != '\n'){}
        system("clear");
        fight(Hero, Blob);
        std::cout << "Now would you like to exit the room? (y/n)\n";
        std::cin.get(use_key);
        while(use_key != 'y' && use_key != 'n'){
            system("clear");
            std::cout << "Invalid input! Use the room key? (y/n)\n";
            while(std::cin.get() != '\n'){}
        }
        while(std::cin.get() != '\n'){}
    }
    system("clear");
    std::cout << "You exit the room, and are greeted by a long, dank corridor which seemingly has no end.\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    std::cout << "Nothing to do but walk, you suppose\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}

    //map of corridor
    ENEMY NoEnemy;
    OBJECT NoObject;
    NoEnemy.x = -1; // declare empty enemy for generateRoom() function
    NoEnemy.y = -1;
    NoObject.x = -1; // declare empty object for generateRoom() function
    NoObject.y = -1;

    int repeat_corridor = 0;
    char turn_back;
    do{
        Hero.x = 0;
        Hero.y = 0;
        while(true){
            system("clear");
            generateRoom(WIDTH2, HEIGHT2, Hero, NoEnemy, NoObject);
            Hero.playerPosition(WIDTH2, HEIGHT2);
            if(Hero.y == HEIGHT2 - 1){
                break;
            }
        } 
        system("clear");
        if(repeat_corridor == 2){
            fight(Hero, Blob);
            repeat_corridor = 0;
        }
        std::cout << "You've been walking for a while now, and there's still no end in sight. Turn back? (y/n)\n";
        std::cin.get(turn_back);
        while(turn_back != 'y' && turn_back != 'n'){
            while(std::cin.get() != '\n'){}
            system("clear");
            std::cout << "Invalid input! Turn back? (y/n)\n";
            std::cin.get(turn_back);
        }
        while(std::cin.get() != '\n'){}
        if(turn_back == 'y'){
            system("clear");
            break;
        }
        else if(turn_back == 'n'){
            system("clear");
            std::cout << "You continue down the path.\n";
            std::cout << "\n(Hit enter to continue)\n";
            while(std::cin.get() != '\n'){}
            system("clear");
            repeat_corridor++;
        }
    }
    while(turn_back == 'n');
    std::cout << "You start walking back the way you came.\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    std::cout << "You see the door, but it looks different from the way you left it, and there's a figure in front.\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    std::cout << "The figure is a moving mannequin! And it's guarding the door!\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    ENEMY Mannequin;
    Mannequin.name = "Manny Quin";
    Mannequin.attack = 3;
    Mannequin.defense = 1;
    Mannequin.health = 5;
    Mannequin.exp_reward = 6;
    fight(Hero, Mannequin);

    std::cout << "With nothing left blocking your way you continue on, opening the door.\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    std::cout << "Although, you have an uneasy feeling as the door swings open...\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    std::cout << "You peek through the door and something shiny catches your eye.\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    std::cout << "Treasure!\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");

    //setup the room
    ENEMY Mimic;
    Mimic.name = "Derek the Mimic";
    Mimic.attack = 3;
    Mimic.defense = 2;
    Mimic.health = 4;
    Mimic.exp_reward = 5;
    Hero.x = 1;
    Hero.y = HEIGHT1 / 2;
    Mimic.x = WIDTH1 - 1;
    Mimic.y = HEIGHT1 / 2;
    fight_complete = 0;

    while(true){
        system("clear");
        generateRoom(WIDTH1, HEIGHT1, Hero, Mimic, Door);
        Hero.playerPosition(WIDTH1, HEIGHT1);
        // hero-object & hero-enemy interactions
        if(Hero.x == Mimic.x && Hero.y == Mimic.y){
            if(fight_complete == 0){
                fight(Hero, Mimic);
                std::cout << "* You obtained the treasure *\n";
                std::cout << "\n(Hit enter to continue)\n";
                while(std::cin.get() != '\n'){}
                system("clear");
                treasureAnimation(); // treasure animation
                std::cout << "\n(Hit enter to continue)\n";
                while(std::cin.get() != '\n'){}
                system("clear");

                //temporary break while game is incomplete
                break;
                fight_complete = 1;
            }
            else if(fight_complete == 1){
                std::cout << "Mm mm mm, treasure.\n";
                std::cout << "\n(Hit enter to continue)\n";
                while(std::cin.get() != '\n'){}
            }
        }
        if(Hero.x == Door.x && Hero.y == Door.y){
            system("clear");
            if(fight_complete == 0){
                std::cout << "But that treasure looks so nice...\n";
                std::cout << "\n(Hit enter to continue)\n";
                while(std::cin.get() != '\n'){}
            }
            else if(fight_complete == 1){
                break;
            }
        }
    }    

    std::cout << "End of written storyline.\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
}

void versus() // two player versus mode
{
    system("clear");
    HERO Player1;
    HERO Player2;
    Player1.attack = 3;
    Player1.defense = 1;
    Player1.health = 10;
    Player2.attack = 3;
    Player2.defense = 1;
    Player2.health = 10;
    std::cout << "Welcome to versus mode!\n\nRemember to hide your inputs!\n\n";
    std::cout << "Enter Player 1's name: ";
    std::getline(std::cin, Player1.name);
    std::cout << "enter Player 2's name: ";
    std::getline(std::cin, Player2.name);
    //enter battle code here
    system("clear");
    int player1_health = Player1.health;
    int player2_health = Player2.health;
    std::cout << Player1.name << " vs " << Player2.name << "\n";
    delay(2);
    system("clear");
    swordAnimation();
    while(player2_health > 0 && player1_health > 0){
        std::cout << Player1.name << "'s health:                       " << Player2.name << "'s health\n";
        std::cout << "   " << player1_health << "/" << Player1.health << "                                " << player2_health << "/" << Player2.health << "\n\n";
        std::cout << Player1.name << ", choose your next move!\n\n";
        std::cout << "Attack (enter 'a')\n";
        std::cout << "Counter (enter 'c')\n";
        std::cout << "Heal (enter 'h')\n";
        char hero_move;
        std::cin.get(hero_move);
        while(hero_move != 'a' && hero_move != 'c' && hero_move != 'h'){
            system("clear");
            std::cin.clear();
            while(std::cin.get() != '\n'){}
            std::cout << "Invalid input!\n";
            std::cout << Player1.name << ", choose your next move!\n\n";
            std::cout << "Attack  \tCounter \tHeal\n";
            std::cout << "Enter: a\tEnter: c\tEnter: h\n\n";
            std::cin.get(hero_move);
        }
        std::cin.clear();
        while(std::cin.get() != '\n'){}
        system("clear");

        std::cout << "Pass the device to " << Player2.name << "\n\n";
        std::cout << "(Hit enter when you are ready)\n";
        while(std::cin.get() != '\n'){}
        system("clear");

        //player2 move
        std::cout << Player2.name << "'s health:                       " << Player1.name << "'s health\n";
        std::cout << "   " << player2_health << "/" << Player2.health << "                                " << player1_health << "/" << Player1.health << "\n\n";
        std::cout << Player2.name << ", choose your next move!\n\n";
        std::cout << "Attack (enter 'a')\n";
        std::cout << "Counter (enter 'c')\n";
        std::cout << "Heal (enter 'h')\n";
        char hero2_move;
        std::cin.get(hero2_move);
        while(hero2_move != 'a' && hero2_move != 'c' && hero2_move != 'h'){
            system("clear");
            std::cin.clear();
            while(std::cin.get() != '\n'){}
            std::cout << "Invalid input!\n";
            std::cout << Player2.name << ", choose your next move!\n\n";
            std::cout << "Attack  \tCounter \tHeal\n";
            std::cout << "Enter: a\tEnter: c\tEnter: h\n\n";
            std::cin.get(hero2_move);
        }
        std::cin.clear();
        while(std::cin.get() != '\n'){}
        system("clear");

        std::cout << "Share the device with " << Player1.name << "\n\n";
        std::cout << "(Hit enter when you are ready to view this round's results)\n";
        while(std::cin.get() != '\n'){}
        system("clear");

        int enemy_move = rand() % 3;
        switch(hero2_move){
            case 'a':
                //enemy attacks
                if(hero_move == 'a'){
                    std::cout << "You attacked each other!\n";
                    if(Player1.attack >= Player2.defense && Player2.attack >= Player1.defense)
                    {
                        player2_health = player2_health - (Player1.attack - Player2.defense);
                        player1_health = player1_health - (Player2.attack - Player1.defense);
                    }
                    else if(Player1.attack >= Player2.defense){
                        player2_health = player2_health - (Player1.attack - Player2.defense);
                    }
                    else if(Player2.attack >= Player1.defense){
                        player1_health = player1_health - (Player2.attack - Player1.defense);
                    }
                }
                else if(hero_move == 'c'){
                    std::cout << Player1.name << " countered " << Player2.name << "'s attack!\n";
                    player2_health = player2_health - Player1.attack;
                }
                else if(hero_move == 'h'){
                    std::cout << Player1.name << " healed +1 HP, but got hit by " << Player2.name << "'s attack!\n";
                    if(player1_health < Player1.health){
                        player1_health = player1_health + 1;
                    }
                    if(Player2.attack >= Player1.defense)
                    {
                        player1_health = player1_health - (Player2.attack - Player1.defense);
                    }
                    else if(Player2.attack < Player1.defense){}
                }
                break;
            case 'c':
                //Player2 counters
                if(hero_move == 'a'){
                    std::cout << Player1.name << " attacked, but " << Player2.name << " countered!\n";
                    player1_health = player1_health - Player2.attack;
                }
                else if(hero_move == 'c'){
                    std::cout << "You both countered nothing and fell in an unending build up of anticipation! (-1 HP)\n";
                    player1_health = player1_health - 1;
                    player2_health = player2_health - 1;
                }
                else if(hero_move == 'h'){
                    std::cout << Player1.name << " healed +1 HP! " << Player2.name << " attempted to counter, but stubbed their toe. (-1 HP)\n";
                    if(player1_health < Player1.health){
                        player1_health = player1_health + 1;
                    }
                    player2_health = player2_health - 1;
                }
                break;
            case 'h':
                //Player2 heals
                if(hero_move == 'a'){
                    std::cout << Player2.name << " healed +1 HP! " << Player1.name << " hit them right after.\n";
                    if(player2_health < Player2.health){
                        player2_health = player2_health + 1;
                    }
                    if(Player1.attack >= Player2.defense)
                    {
                        player2_health = player2_health - (Player1.attack - Player2.defense);
                    }
                    else if(Player1.attack < Player2.defense){}
                }
                else if(hero_move == 'c'){
                    std::cout << Player2.name << " healed +1 HP! " << Player1.name << " countered nothing and fell on their face. fool. (-1 HP)\n";
                    if(player2_health < Player2.health){
                        player2_health = player2_health + 1;
                    }
                    player1_health = player1_health - 1;
                }
                else if(hero_move == 'h'){
                    std::cout << "Both of you healed +1 HP!\n";
                    if(player2_health < Player2.health){
                        player2_health = player2_health + 1;
                    }
                    if(player1_health < Player1.health){
                        player1_health = player1_health + 1;
                    }
                }
                break;
            default:
                std::cout << "ERROR\n";
                break;
        }
        std::cout << "\n(Hit enter to continue)\n";
        while(std::cin.get() != '\n'){}
        system("clear");
    }

    //exp gain at the end
    if(player2_health <= 0 && player1_health <= 0){
        std::cout << "It's a tie! You both went down fighting.\n";
    }
    else if(player2_health <= 0){
        fightAnimation();
        std::cout << "Good job " << Player1.name << "! You defeated " << Player2.name << "!\n";
    }
    else if(player1_health <= 0){
        fightAnimation();
        std::cout << "Good job " << Player2.name << "! You defeated " << Player1.name << "!\n";
    }

    delay(3);
    system("clear");
}

void HERO::levelUp()
{
    int upgrade;
    char stat;
    system("clear");
    std::cout << "Level up!\n\n";
    std::cout << "Select which stat to upgrade.\n\n";
    std::cout << "Attack? \tDefense?\tHealth?\n";
    std::cout << "Enter: a\tEnter: d\tEnter: h\n\n";
    std::cin.get(stat);
    while(stat != 'a' && stat != 'd' && stat != 'h'){
        system("clear");
        std::cin.clear();
        while(std::cin.get() != '\n'){}
        std::cout << "Invalid input!\n";
        std::cout << "Select which stat to upgrade.\n\n";
        std::cout << "Attack? \tDefense?\tHealth?\n";
        std::cout << "Enter: a\tEnter: d\tEnter: h\n\n";
        std::cin.get(stat);
    }
    std::cin.clear();
    while(std::cin.get() != '\n'){}
    system("clear");
    switch(stat){
        case 'a':
            attack = attack + 1;
            std::cout << "* Attack +1 *\n";
            break;
        case 'd':
            defense = defense + 1;
            std::cout << "* Defense +1 *\n";
            break;
        case 'h':
            health = health + 2;
            std::cout << "* Health +2 *\n";

            break;
        default:
            std::cout << "ERROR\n";
            break;
    }
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    exp = exp % MAX_EXP;
    MAX_EXP += 1; // increase required exp after level up
}

void printRules()
{
    system("clear");
    std::cout << "General Rules:\n";
    std::cout << "- Do not hit enter unless prompted for input\n";
    std::cout << "- Use WASD + Enter to input movement during map portions\n";

    std::cout << "\nCombat Rules:\n";
    std::cout << "- There are three combat options: attack, counter, and heal\n";
    std::cout << "- If both players attack at the same time, both attacks hit\n";
    std::cout << "- An attack will damage the other player unless it is countered\n";
    std::cout << "- If a player counters anything but an attack, they lose 1 HP\n";
    std::cout << "- Healing gives the player +1, but leaves them vulnerable to an attack\n";
    std::cout << "- Attack damage is negated by opposition's defense, unless it is a \n  counterattack\n\n";
    std::cout << "Hit enter to return to main menu\n";
    while(std::cin.get() != '\n'){}
}

void fight(HERO &h, ENEMY &e)
{
    system("clear");
    int hero_health = h.health;
    int enemy_health = e.health;
    swordAnimation(); //animation to indicate fight
    std::cout << "You have entered a fight with " << e.name << "\n\n";
    std::cout << "\n(Hit enter to continue)\n";
    while(std::cin.get() != '\n'){}
    system("clear");
    while(enemy_health > 0 && hero_health > 0){
        std::cout << "Your health:        " << std::setw(19) << e.name << "'s health\n";
        std::cout << "   " << hero_health << "/" << h.health << "                              " << std::setw(2) << enemy_health << "/" << e.health << "\n\n";
        std::cout << "Choose your next move!\n\n";
        std::cout << "Attack   (enter 'a')\n";
        std::cout << "Counter  (enter 'c')\n";
        std::cout << "Heal     (enter 'h')\n";
        // get next move input
        char hero_move;
        std::cin.get(hero_move);
        while(hero_move != 'a' && hero_move != 'c' && hero_move != 'h'){
            system("clear");
            std::cin.clear();
            while(std::cin.get() != '\n'){}
            std::cout << "Invalid input!\n";
            std::cout << "Attack   (enter 'a')\n";
            std::cout << "Counter  (enter 'c')\n";
            std::cout << "Heal     (enter 'h')\n";
            std::cin.get(hero_move);
        }
        std::cin.clear();
        while(std::cin.get() != '\n'){}
        system("clear");

        //enemy move is random
        int enemy_move = rand() % 3;
        switch(enemy_move){
            case 0: //enemy attacks scenarios
                if(hero_move == 'a'){
                    std::cout << "You and " << e.name << " attacked each other!\n";
                    if(h.attack >= e.defense && e.attack >= h.defense)
                    {
                        enemy_health = enemy_health - (h.attack - e.defense);
                        hero_health = hero_health - (e.attack - h.defense);
                    }
                    else if(h.attack >= e.defense){
                        enemy_health = enemy_health - (h.attack - e.defense);
                    }
                    else if(e.attack >= h.defense){
                        hero_health = hero_health - (e.attack - h.defense);
                    }
                }
                else if(hero_move == 'c'){
                    std::cout << "You countered " << e.name << "'s attack!\n";
                    enemy_health = enemy_health - h.attack;
                }
                else if(hero_move == 'h'){
                    std::cout << "You healed +1 HP, but got hit by " << e.name << "'s attack!\n";
                    if(hero_health < h.health){
                        hero_health = hero_health + 1;
                    }
                    if(e.attack >= h.defense)
                    {
                        hero_health = hero_health - (e.attack - h.defense);
                    }
                    else if(e.attack < h.defense){}
                }
                break;
            case 1: // enemy counters scenarios
                if(hero_move == 'a'){
                    std::cout << "You attacked, but " << e.name << " countered!\n";
                    hero_health = hero_health - e.attack;
                }
                else if(hero_move == 'c'){
                    std::cout << "You both countered nothing and fell in an unending build up of anticipation! (-1 HP)\n";
                    hero_health = hero_health - 1;
                    enemy_health = enemy_health - 1;
                }
                else if(hero_move == 'h'){
                    std::cout << "You healed +1 HP! " << e.name << " attempted to counter, but stubbed their toe losing 1 HP.\n";
                    if(hero_health < h.health){
                        hero_health = hero_health + 1;
                    }
                    enemy_health = enemy_health - 1;
                }
                break;
            default: // enemy heals scenarios
                if(hero_move == 'a'){
                    std::cout << e.name << " healed +1 HP! You hit them right after.\n";
                    if(enemy_health < e.health){
                        enemy_health = enemy_health + 1;
                    }
                    if(h.attack >= e.defense)
                    {
                        enemy_health = enemy_health - (h.attack - e.defense);
                    }
                    else if(h.attack < e.defense){}
                }
                else if(hero_move == 'c'){
                    std::cout << e.name << " healed +1 HP! You countered nothing, and tripped getting into your stance. (-1 HP)\n";
                    if(enemy_health < e.health){
                        enemy_health = enemy_health + 1;
                    }
                    hero_health = hero_health - 1;
                }
                else if(hero_move == 'h'){
                    std::cout << "Both of you healed +1 HP!\n";
                    if(enemy_health < e.health){
                        enemy_health = enemy_health + 1;
                    }
                    if(hero_health < h.health){
                        hero_health = hero_health + 1;
                    }
                }
                break;
        }
        std::cout << "\n(Hit enter to continue)\n";
        while(std::cin.get() != '\n'){}
        system("clear");
    }

    //exp gain at the end
    if(enemy_health <= 0){
        fightAnimation();
        std::cout << "Good job! You defeated " << e.name << "!\n";
        std::cout << "You gained " << e.exp_reward << " exp!\n";
        h.exp = h.exp + e.exp_reward;
        std::cout << "You are now at " << h.exp << "/" << MAX_EXP << " experience points\n";
    }
    //game over if battle is lost
    else if(hero_health <= 0){
        deathAnimation();
        std::cout << "Game over! You lose!\n";
        std::cout << "\n(Hit enter to continue)\n";
        while(std::cin.get() != '\n'){}
        main();
    }

    //level up?
    if(h.exp >= MAX_EXP){
        std::cout << "\n(Hit enter to continue)\n";
        while(std::cin.get() != '\n'){}
        h.levelUp();
    }
    else{
        std::cout << "\n(Hit enter to continue)\n";
        while(std::cin.get() != '\n'){}
    }
    system("clear");
}

void HERO::playerPosition(int width, int height) //update player position based on wasd input
{
    std::string input;
    std::getline(std::cin, input);
    std::cin.clear();
    if(input == "w"){
        if(y == (height - 1)){
            //do nothing -- wall barrier;
        }
        else{
            y = y + 1;
        }
    }
    else if(input == "s"){
        if(y == 0){
            //do nothing;
        }
        else{
            y = y - 1;
        }
    }
    else if(input == "a"){
        if(x == 0){
            //do nothing;
        }
        else{
            x = x - 1;
        }
    }
    else if(input == "d"){
        if(x == (width - 1)){
            //do nothing;
        }
        else{
            x = x + 1;
        }
    }
}

void generateRoom(int width, int height, HERO &h, ENEMY &e, OBJECT &o)
{
    for(int i = 0; i < (width + 2); i++){
        std::cout << "~";
    }
    std::cout << std::endl;
    //insert for loop that is able to print the one block map using the coordinates of the player
    for(int i = 0; i < height; i++){
        std::cout << "|";
        for(int j = 0; j < width; j++){
            if(h.x == j && h.y == (height - 1 - i)){
                std::cout << "o"; //print player icon
            }
            else if(e.x == j && e.y == (height - 1 - i)){
                std::cout << "*"; //print enemy icon
            }
            else if(o.x == j && o.y == (height - 1 - i)){
                std::cout << o.symbol; //print object icon based on what I declare it to be
            }
            else
                std::cout << " ";
        }
        std::cout << "|\n";
    }
    for(int i = 0; i < (width + 2); i++){
        std::cout << "~";
    }
    std::cout << "\n\n(wasd + enter to move)\n";
}

void fightAnimation()
{
    std::cout << "    ( \")         \n";
    std::cout << "    <|--,=    x___    \n";
    std::cout << "    / \\       /\\ /\\   \n\n";
    delay(0.5);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|--,=-   x___    \n";
    std::cout << "    / \\       /\\ /\\   \n\n";
    delay(0.02);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|--,= -  x___    \n";
    std::cout << "    / \\       /\\ /\\   \n\n";
    delay(0.02);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|--,=  - x___    \n";
    std::cout << "    / \\       /\\ /\\   \n\n";
    delay(0.02);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|--,=   -x___    \n";
    std::cout << "    / \\       /\\ /\\   \n\n";
    delay(0.02);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|--,=    x___    \n";
    std::cout << "    / \\       /\\ /\\   \n\n";
    delay(0.1);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|--,=    0000    \n";
    std::cout << "    / \\       00 00   \n\n";
    delay(0.05);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|--,=   0 0  00   \n";
    std::cout << "    / \\      0  0 0   \n\n";
    delay(0.05);
    system("clear");
    std::cout << "    ( \")    0    \n";
    std::cout << "    <|--,=      .  0    \n";
    std::cout << "    / \\      0   .   \n\n";
    delay(0.05);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|--,=      \n";
    std::cout << "    / \\         \n\n";
    delay(0.2);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|--        \n";
    std::cout << "    / \\,=       \n\n";
    delay(0.2);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|--        \n";
    std::cout << "    / \\         \n\n";
    delay(0.1);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|\\        \n";
    std::cout << "    / \\         \n\n";
    delay(0.1);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|>        \n";
    std::cout << "    / \\         \n\n";
    delay(0.5);
    system("clear");
    std::cout << "    ( ,,)         \n";
    std::cout << "    <|>      \n";
    std::cout << "    / \\         \n\n";
    delay(1);
    system("clear");
    std::cout << "    ( \")         \n";
    std::cout << "    <|>      \n";
    std::cout << "    / \\         \n\n";
    delay(0.1);
    system("clear");
    std::cout << "   ('=')         \n";
    std::cout << "    <|>      \n";
    std::cout << "    / \\         \n\n";
    delay(1);
    system("clear");
}

void swordAnimation()
{
    system("clear");
    std::cout << "       ^            ^ \n";
    std::cout << "     /0/            \\0\\ \n";
    std::cout << "    /0/              \\0\\ \n";
    std::cout << "   /0/                \\0\\ \n";
    std::cout << " -/0/_                _\\0\\- \n";
    std::cout << "  /                      \\ \n";
    std::cout << " /                        \\ \n";
    delay(0.7);
    system("clear");
    std::cout << "          ^    ^ \n";
    std::cout << "          \\0\\/0/ \n";
    std::cout << "           \\/0/ \n";
    std::cout << "           /0/\\ \n";
    std::cout << "         -/0/\\0\\- \n";
    std::cout << "          /    \\ \n";
    std::cout << "         /      \\ \n";
    delay(0.7);
    system("clear");
    std::cout << "       ^            ^ \n";
    std::cout << "     /0/            \\0\\ \n";
    std::cout << "    /0/              \\0\\ \n";
    std::cout << "   /0/                \\0\\ \n";
    std::cout << " -/0/_                _\\0\\- \n";
    std::cout << "  /                      \\ \n";
    std::cout << " /                        \\ \n";
    delay(0.7);
    system("clear");
    std::cout << "          ^    ^ \n";
    std::cout << "          \\0\\/0/ \n";
    std::cout << "           \\/0/ \n";
    std::cout << "           /0/\\ \n";
    std::cout << "         -/0/\\0\\- \n";
    std::cout << "          /    \\ \n";
    std::cout << "         /      \\ \n";
    delay(0.7);
    system("clear");
    std::cout << "       ^            ^ \n";
    std::cout << "     /0/            \\0\\ \n";
    std::cout << "    /0/              \\0\\ \n";
    std::cout << "   /0/                \\0\\ \n";
    std::cout << " -/0/_                _\\0\\- \n";
    std::cout << "  /                      \\ \n";
    std::cout << " /                        \\ \n";
    delay(0.7);
    system("clear");
}

void deathAnimation()
{
    system("clear");
    std::cout << "      ----- \n";
    std::cout << "    /  O Q  \\ \n";
    std::cout << "   (         ) \n";
    std::cout << "    \\  ===  / \n";
    std::cout << "      ----- \n";
    delay(1);
    system("clear");
    std::cout << "      ----- \n";
    std::cout << "    /  > <  \\ \n";
    std::cout << "   (      '  ) \n";
    std::cout << "    \\  ~~~  / \n";
    std::cout << "      ----- \n";
    delay(0.1);
    system("clear");
    std::cout << "      ----- \n";
    std::cout << "    /  O O  \\ \n";
    std::cout << "   (      ,  ) \n";
    std::cout << "    \\  ~~~  / \n";
    std::cout << "      ----- \n";
    delay(0.1);
    system("clear");
    std::cout << "      ----- \n";
    std::cout << "    /  O O  \\ \n";
    std::cout << "   (         ) \n";
    std::cout << "    \\  ~~~' / \n";
    std::cout << "      ----- \n";
    delay(0.1);
    system("clear");
    std::cout << "      ----- \n";
    std::cout << "    /  O O  \\ \n";
    std::cout << "   (         ) \n";
    std::cout << "    \\  ~~~, / \n";
    std::cout << "      ----- \n";
    delay(0.1);
    system("clear");
    std::cout << "      ----- \n";
    std::cout << "    /  O O  \\ \n";
    std::cout << "   (         ) \n";
    std::cout << "    \\  ~~~  / \n";
    std::cout << "      -----'\n";
    delay(0.1);
    system("clear");
    std::cout << "      ----- \n";
    std::cout << "    /  - -  \\ \n";
    std::cout << "   (         ) \n";
    std::cout << "    \\  ~~~  / \n";
    std::cout << "      ----- \n";
    delay(0.1);
    system("clear");
    std::cout << "      ----- \n";
    std::cout << "    /  O O  \\ \n";
    std::cout << "   (         ) \n";
    std::cout << "    \\  ~~~  / \n";
    std::cout << "      ----- \n";
    delay(1);
    system("clear");
    std::cout << "      ----- \n";
    std::cout << "    /  X X  \\ \n";
    std::cout << "   (         ) \n";
    std::cout << "    \\  ===  / \n";
    std::cout << "      ----- \n";
    delay(2);
    system("clear");
}

void treasureAnimation()
{
    system("clear");
    std::cout << "\n\n  ________ \n"
              << " /~~.~`~`~\\ \n"
              << "/__________\\ \n"
              << "|__________| \n";
    delay(1);
    system("clear");
    std::cout << "\n\n  ________ \n"
              << " /~~.~`~`~\\ \n"
              << ";==========; \n"
              << "|__________| \n";
    delay(0.05);
    system("clear");
    std::cout << "\n\n _,.====.,_ \n"
              << "(__________) \n"
              << "/$__$*__$__\\ \n"
              << "|__________| \n";
    delay(0.1);
    system("clear");
    std::cout << "\n _,.====.,_ \n"
              << "(__________) \n"
              << " / * $ $* \\ \n"
              << "/$__$*__$__\\ \n"
              << "|__________| \n";
    delay(0.1);
    system("clear");
    std::cout << "  ________ \n"
              << " |        | \n"
              << " |________| \n"
              << " / * $ $* \\ \n"
              << "/$__$*__$__\\ \n"
              << "|__________| \n";
}

void delay(float x) // delay for x seconds
{
    int time = x * 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    fflush(stdin);
}