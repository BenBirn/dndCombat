#include <algorithm>
#include <cstring>
#include <ctime>
#include <limits>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include "Class.h"
#include "PC.h"
#include "Spell.h"
#include "Weapon.h"

using namespace std;

string name, cls, wep;
uint32_t PCs, enemies, col, row;
uint32_t lvl, spd, str, dex, con, intl, wis, cha, HP, AC;
uint32_t x, y;
vector<PC> turn;
vector<bool> dodging;
uint64_t pCount;
uint64_t mCount;
vector<PC> knocked;

unordered_map<string, Weapon> weapons = initWeapons();
unordered_map<string, Spell> spells = initSpells();
unordered_map<string, PC> chars;

string initGrid(int hor, int vert) {
    string grid;
    string nums = "    1  2  3  4  5  6  7  8  9  10";
    string line(3 * (hor+1), '-');
    line = "  " + line;
    
    grid += (nums.substr(0, 3 + 3 * hor));
    for (int i = 10; i < hor; i++) {
        grid += (" " + to_string(i+1)); 
    }
    grid += "\n";
    for (int i = 0; i < vert; i++) {
        grid += (line + "\n");
        grid += to_string(i+1);
        if (i < 9) {
            grid += " ";
        }
        for (int j = 0; j < hor + 1; j++) {
            grid += " | ";
        }
        grid += "\n";
    }
    grid += (line + "\n");
    return grid;
}

bool readFile(ifstream& file, string group, string& grid) {
    if (!file.is_open()) {
        cout << "Unable to open file" << endl;
        return false;
    } else {
        getline(file, name);
        file >> cls >> lvl;
        if (file.fail()) {
            cout << "Invalid file format" << endl;
            return false;
        }
        file >> str >> dex >> con >> intl >> wis >> cha;
        if (file.fail()) {
            cout << "Invalid file format" << endl;
            return false;
        }
        file >> HP >> AC >> spd;
        if (file.fail()) {
            cout << "Invalid file format" << endl;
            return false;
        }
        file >> wep;
        Weapon w = weapons[wep];
        PC C = PC(name, cls, lvl, HP, AC, spd, str, dex, con, intl, wis, cha, w);
        cout << grid << "Where on the grid is " << name << " starting?" << endl;
        cin >> x >> y;
        int line = 3*(col+1)+3;
        while (cin.fail() || x > col || y > row || grid[3+3*col + (2*y-1)*line + 3+x*3] != ' ') {
            if (grid[3+3*col + (2*y-1)*line + 3+x*3] != ' ') {
                invalid("Another character is already there\n");
            } else {
                invalid("Invalid input\n");
            }
            cin >> x >> y;
        }
        moveChar(grid, C, x, y);
        C.cls.initFeatures(intl);
        C.initMonkFist();
        C.team = group;
        turn.push_back(C);
        dodging.push_back(false);
        chars.insert({C.name, C});
    }
    file.close();
    return true;
}

void readInput(string group, string t, string& grid) {
    cout << "Enter " << t << "'s name, class, and level:" << endl;
    cin >> name >> cls >> lvl;
    while (cin.fail()) {
        invalid("Invalid input\n");
        cin >> name >> cls >> lvl >> spd;
    }
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout << "Enter " << t << "'s stats:" << endl;
    cin >> str >> dex >> con >> intl >> wis >> cha;
    while (cin.fail()) {
        invalid("Invalid input\n");
        cin >> str >> dex >> con >> intl >> wis >> cha;
    }
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout << "Enter " << t << "'s HP, AC, and speed:" << endl;
    cin >> HP >> AC >> spd;
    while (cin.fail()) {
        invalid("Invalid input\n");
        cin >> HP >> AC >> spd;
    }
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout << "What weapon does this " << t << " have?" << endl;
    cin >> wep;
    while (cin.fail() || !weapons.count(wep)) {
        invalid("Invalid input\n");
        cin >> wep;
    }
    Weapon w = weapons[wep];
    PC C = PC(name, cls, lvl, HP, AC, spd, str, dex, con, intl, wis, cha, w);
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout << grid << "Where on the grid is this " << t << " starting?" << endl;
    cin >> x >> y;
    int line = 3*(col+1)+3;
    while (cin.fail() || x > col || y > row || grid[3+3*col + (2*y-1)*line + 3+x*3] != ' ') {
        if (grid[3+3*col + (2*y-1)*line + 3+x*3] != ' ') {
            invalid("Another character is already there\n");
        } else {
            invalid("Invalid input\n");
        }
        cin >> x >> y;
    }
    moveChar(grid, C, x, y);
    C.cls.initFeatures(intl);
    C.initMonkFist();
    C.team = group;
    turn.push_back(C);
    dodging.push_back(false);
    chars.insert({C.name, C});
}

bool checkKO(PC& C) {
    if (C.HP <= 0) {
        if (C.team == "monsters") {
            cout << C << " is now dead!" << endl;
            mCount--;
            if (mCount == 0) {
                cout << "The players win the fight!" << endl;
                return true;
            }
        } else {
            cout << C << " has been knocked out" << endl;
            // knocked.push_back(players[getPC(C.name, players)]);
            knocked.push_back(C);
            if (knocked.size() == pCount) {
                cout << "The players lose the fight!" << endl;
                return true;
            }
        }
    }
    return false;
}

// Main
int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "help") == 0) {
        cout << "You can pre-enter character information through files. The file format is:\n"
        << "name\nclass lvl\nstr dex con int wis cha\nHP AC\nweapon\n\n"
        << "Type ./Combat [#PCs] [#enemies] [character files] to use." << endl;
        return 0;
    }
    
    srand(time(0));
    
    cout << "Enter the size of the grid (cols rows):" << endl;
        cin >> col >> row;
        while (cin.fail()) {
            invalid("Invalid input\n");
            cin >> col >> row;
        }
        string grid = initGrid(col, row);
    
    // File reading
    if (argc > 3) {
        PCs = stoi(argv[1]);
        enemies = stoi(argv[2]);
        
        for (uint32_t i = 0; i < PCs; i++) {
            ifstream file(argv[3+i]);
            if (!readFile(file, "players", grid)) {
                return -1;
            }
            pCount++;
        }
        for (uint32_t i = 0; i < enemies; i++) {
            ifstream file(argv[3+PCs+i]);
            if (!readFile(file, "monsters", grid)) {
                return -1;
            }
            mCount++;
        }
        
    // Manual input
    } else if (argc == 1) {
        cout << "Welcome to the D&D combat simulator! To start, it will ask you information\n"
        << "about the player characters and enemies. When a question asks for multiple\n"
        << "inputs, seperate each with a space. Press enter when done.\n" << endl;
        
        cout << "Enter number of player characters and enemies:" << endl;
        cin >> PCs >> enemies;
        while (cin.fail()) {
            invalid("Invalid input\n");
            cin >> PCs >> enemies;
        }
        
        
        for (uint32_t i = 0; i < PCs; i++) {
            readInput("players", "character", grid);
            pCount++;
        }
        for (uint32_t i = 0; i < enemies; i++) {
            readInput("monsters", "enemy", grid);
            mCount++;
        }
    
    } else {
        cout << "Invalid number of arguments" << endl;
        return -1;
    }
    
    sort(turn.begin(), turn.end(), cmpInit);
    cout << endl << "The turn order is: ";
    for (uint64_t i = 0; i < turn.size() - 1; i++) {
        cout << turn[i] << " -> ";
    }
    cout << turn.back() << endl;
    
    unordered_set<string> halfCompass = {"north", "east", "south", "west"};
    unordered_set<string> fullCompass = {"north", "east", "south", "west", "northeast", "northwest", "southeast", "southwest"};
    string whatDo;
    getline(cin, whatDo);
    int action, bonusAction, moves;
    bool disengaged;
    
    // Main loop
    while (true) {
        for (uint64_t i = 0; i < turn.size(); i++) {
            cout << turn[i] << "'s turn!" << endl;
            whatDo = "";
            action = bonusAction = 1;
            turn[i].reaction = 1;
            moves = turn[i].spd / 5;
            disengaged = false;
            // Start of turn checks
            if (turn[i].cls.reckAttack) {
                turn[i].cls.reckAttack = false;
                turn[i].advToHit--;
                turn[i].advToBeHit--;
            }
            if (dodging[i]) {
                dodging[i] = false;
                turn[i].advToBeHit++;
            }
            
            while (whatDo != "end") {
                for (uint64_t j = 0; j < turn.size(); j++) {
                    if (checkKO(turn[j])) {
                        return 0;
                    }
                }
                if (find(knocked.begin(), knocked.end(), turn[i]) != end(knocked)) {
                    if (roll(1, 20) < 10) {
                        cout << turn[i] << " succeded a death save!" << endl;
                    } else {
                        cout << turn[i] << " failed a death save." << endl;
                    }
                    break;
                }
                cout << "What will " << turn[i] << " do?" << endl;
                getline(cin, whatDo);
                
                // Basic actions
                if (whatDo == "grid") {
                    cout << grid;
            } else if (whatDo == "hp" || whatDo == "HP") {
                    cout << "You have " << turn[i].HP << " HP remaining" << endl;
                // Move
                } else if (whatDo == "move") {
                    if (moves == 0) {
                        cout << "You've used all your movement for this turn";
                        continue;
                    }
                    cout << grid;
                    while (moves != 0) {
                        cout << "Where will you move? (move one square at a time)" << endl;
                        cout << "Remaining moves: " << moves << endl;
                        cin >> x >> y;
                        getchar();
                        if (cin.fail()) {
                            invalid("Ending movement\n");
                            break;
                        }
                        if (abs((int)x - (int)turn[i].x) > 1 || x > col || abs((int)y - (int)turn[i].y) > 1 || y > row) {
                            cout << "You can't move there" << endl;
                            continue;
                        }
                        int line = 3*(col+1)+3;
                        if (grid[3+3*col + (2*y-1)*line + 3+x*3] != ' ') {
                            cout << "Another character is already there" << endl;
                            continue;
                        }
                        // Opportunity
                        if (!disengaged) {
                            for (uint64_t j = 0; j < turn.size(); j++) {
                                if (turn[i].team != turn[j].team && dist(turn[i], turn[j]) <= 5 && max(abs((int)turn[j].x - (int)x), abs((int)turn[j].y - (int)y)) > 1) {
                                    if (turn[j].reaction) {
                                        cout << "Will " << turn[j] << " take an opportunity attack? (y/n)" << endl;
                                        getline(cin, whatDo);
                                        if (whatDo == "y") {
                                            turn[j].attack(turn[i], turn[j].wep, turn, grid);
                                            turn[j].reaction--;
                                            if (checkKO(turn[j])) {
                                                return 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        moveChar(grid, turn[i], x, y);
                        moves--;
                        cout << grid;
                    }
                    if (moves == 0) {
                        cout << "You have no more moves" << endl;
                    }
                } else if (whatDo == "dash") {
                    bool bonus = (bonusAction && turn[i].cls.name == "rogue" && turn[i].cls.lvl >= 2);
                    if (turn[i].cls.name == "monk" && turn[i].cls.lvl >= 2 && bonusAction) {
                        cout << "Would you like to spend 1 ki to do this as a bonus action? (y/n)" << endl;
                        getline(cin, whatDo);
                        if (whatDo == "y") {
                            turn[i].cls.ki--;
                            bonus = true;
                        }
                    }
                    if (bonus) {
                        bonusAction--;
                    } else {
                        if (action == 0) {
                            cout << "You already used your action this turn" << endl;
                            continue;
                        }
                        action--;
                    }
                    moves += turn[i].spd;
                    cout << "You can now move twice as far this turn" << endl;
                } else if (whatDo == "dodge") {
                    if (dodging[i]) {
                        cout << "You're already dodging" << endl;
                        continue;
                    }
                    bool bonus = false;
                    if (turn[i].cls.name == "monk" && turn[i].cls.lvl >= 2 && bonusAction) {
                        cout << "Would you like to spend 1 ki to do this as a bonus action? (y/n)" << endl;
                        getline(cin, whatDo);
                        if (whatDo == "y") {
                            turn[i].cls.ki--;
                            bonus = true;
                        }
                    }
                    if (bonus) {
                        bonusAction--;
                    } else {
                        if (action == 0) {
                            cout << "You already used your action this turn" << endl;
                            continue;
                        }
                        action--;
                    }
                    dodging[i] = true;
                    turn[i].advToBeHit--;
                    cout << "You are now dodging" << endl;
                } else if (whatDo == "disengage") {
                    if (disengaged) {
                        cout << "You've already disengaged" << endl;
                        continue;
                    }
                    bool bonus = (bonusAction && turn[i].cls.name == "rogue" && turn[i].cls.lvl >= 2);
                    if (turn[i].cls.name == "monk" && turn[i].cls.lvl >= 2 && bonusAction) {
                        cout << "Would you like to spend 1 ki to do this as a bonus action? (y/n)" << endl;
                        getline(cin, whatDo);
                        if (whatDo == "y") {
                            turn[i].cls.ki--;
                            bonus = true;
                        }
                    }
                    if (bonus) {
                        bonusAction--;
                    } else {
                        if (action == 0) {
                            cout << "You already used your action this turn" << endl;
                            continue;
                        }
                        action--;
                    }
                    disengaged = true;
                    cout << "You are now disengaged" << endl;
                // Weapon attack
                } else if (whatDo == "weapon attack") {
                    if (action == 0) {
                        cout << "You already used your action this turn" << endl;
                        continue;
                    }
                    for (int j = 0; j < turn[i].attacks(); j++) {
                        cout << "Who are you attacking?" << endl;
                        getline(cin, whatDo);
                        if (whatDo == "back") {
                            if (j > 0) {
                                cout << "You already attacked" << endl;
                            } else {
                                action++;
                                break;
                            }
                        }
                        if (cin.fail() || !chars.count(whatDo)) {
                            invalid("Invalid player\n");
                            j--;
                            continue;
                        }
                        PC& attacked = chars[whatDo];
                        if (dist(turn[i], attacked) > 5) {
                            cout << "They're too far away" << endl;
                            j--;
                            continue;
                        }
                        turn[i].attack(attacked, turn[i].wep, turn, grid);
                        if (checkKO(attacked)) {
                            return 0;
                        }
                        if (j + 1 == turn[i].attacks() && turn[i].cls.name == "monk" && bonusAction && turn[i].cls.ki) {
                            cout << "Would you like to spend 1 ki to use Flurry of Blows for two more attacks? (y/n)" << endl;
                            getline(cin, whatDo);
                            if (whatDo == "y") {
                                turn[i].cls.ki--;
                                bonusAction--;
                                j -= 2;
                            }
                        }
                    }
                    action--;
                // Cast spell
                } else if (whatDo == "cast spell") {
                    if (turn[i].cls.ss[0] == 0 && turn[i].cls.name != "paladin" && turn[i].cls.name != "ranger") {
                        cout << "You can't cast spells" << endl;
                        continue;
                    }
                    if (action == 0) {
                        cout << "You already used your action this turn" << endl;
                        continue;
                    }
                    cout << "What spell are you casting?" << endl;
                    getline(cin, whatDo);
                    string name = whatDo;
                    if (!spells.count(whatDo)) {
                        cout << "That spell doesn't exist" << endl;
                        continue;
                    }
                    Spell spell = spells[whatDo];
                    if (!spell.classes.count(turn[i].cls.name)) {
                        cout << "Your class can't cast that spell" << endl;
                        continue;
                    }
                    if (!turn[i].cls.ss[spell.lvl]) {
                        cout << "You have no spell slots left for this spell" << endl;
                        continue;
                    }
                    if (spell.AOE == "target") {
                        cout << "Who is it targeting?" << endl;
                        getline(cin, whatDo);
                        while (cin.fail() || !chars.count(whatDo) || dist(turn[i], chars[whatDo]) > spell.range) {
                            invalid("Invalid player\n");
                            getline(cin, whatDo);
                        }
                        turn[i].castTarget(spell, name, grid, chars[whatDo], turn);
                    } else if (spell.AOE == "radius") {
                        cout << "Where are you centering it?" << endl;
                        cin >> x >> y;
                        while (cin.fail()) {
                            invalid("Invalid location\n");
                            cin >> x >> y;
                        }
                        turn[i].castRadius(spell, name, grid, x, y, turn);
                    } else if (spell.AOE == "line") {
                        cout << "What direction is the line going? (8 compass directions)" << endl;
                        getline(cin, whatDo);
                        while (cin.fail() || !fullCompass.count(whatDo)) {
                            invalid("Enter a compass direction (north, northeast, etc.)\n");
                            getline(cin, whatDo);
                        }
                        turn[i].castLine(spell, name, whatDo, grid, turn);
                    } else if (spell.AOE == "cone") {
                        cout << "What direction is the cone going?" << endl;
                        getline(cin, whatDo);
                        while (cin.fail() || !halfCompass.count(whatDo)) {
                            invalid("Enter a basic compass direction (north, east, etc.)\n");
                            getline(cin, whatDo);
                        }
                        turn[i].castCone(spell, name, whatDo, grid, turn);
                    }
                    if (spell.lvl) turn[i].cls.ss[spell.lvl]--;
                    action--;
                
                // Class specific options
                } else if (turn[i].cls.name == "fighter") {
                    if (whatDo == "second wind") {
                        if (turn[i].cls.sWind == 0) {
                            cout << "You already used your Second Wind" << endl;
                            continue;
                        }
                        if (bonusAction == 0) {
                            cout << "You already used your bonus action this turn" << endl;
                            continue;
                        }
                        turn[i].HP += (roll(1, 10) + turn[i].cls.lvl);
                        bonusAction--;
                        turn[i].cls.sWind--;
                    } else if (whatDo == "action surge") {
                        if (turn[i].cls.actSurge == 0) {
                            cout << "You can't use any more action surges" << endl;
                            continue;
                        }
                        action++;
                        turn[i].cls.actSurge--;
                    }
                } else if (turn[i].cls.name == "barbarian") {
                    if (whatDo == "rage") {
                        if (turn[i].cls.inRage) {
                            cout << "You're already raging" << endl;
                            continue;
                        }
                        if (bonusAction == 0) {
                            cout << "You already used your bonus action this turn" << endl;
                            continue;
                        }
                        turn[i].cls.inRage = true;
                        turn[i].resAndImm[0] = turn[i].resAndImm[1] = turn[i].resAndImm[2] = 0.5;
                        bonusAction--;
                    } else if (whatDo == "reckless attack") {
                        turn[i].cls.reckAttack = true;
                        turn[i].advToHit++;
                        turn[i].advToBeHit++;
                    }
                } else if (turn[i].cls.name == "monk") {
                    if (turn[i].cls.lvl >= 18 && whatDo == "empty body") {
                        // invis + resist
                    }
                } else if (turn[i].cls.name == "paladin") {
                    if (whatDo == "lay on hands") {
                        if (action == 0) {
                            cout << "You already used your action this turn" << endl;
                            continue;
                        }
                        cout << "Who would you like to heal?" << endl;
                        getline(cin, whatDo);
                        while (cin.fail() || !chars.count(whatDo) || dist(turn[i], chars[whatDo]) > 5) {
                            invalid("They're too far away or don't exist\n");
                            getline(cin, whatDo);
                        }
                        cout << "How much would you like to heal them for? (" << turn[i].cls.layOnHands << " HP available)" << endl;
                        uint32_t amount;
                        cin >> amount;
                        while (cin.fail() || amount > turn[i].cls.layOnHands) {
                            invalid("You can't heal for that much\n");
                            cin >> amount;
                        }
                        chars[whatDo].HP += amount;
                        turn[i].cls.layOnHands -= amount;
                        cout << chars[whatDo] << " now has " << chars[whatDo].HP << " HP." << endl;
                        action--;
                    }
                // continued for each class
                } else if (whatDo != "end") {
                    cout << "Invalid option" << endl;
                }
            }
        }
    }
    return 0;
}