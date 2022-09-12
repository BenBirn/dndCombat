#include <cmath>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "Class.h"
#include "PC.h"
#include "Spell.h"
#include "Weapon.h"

// Helper Functions

void invalid(std::string s) {
    bool failed = std::cin.fail();
    std::cin.clear();
    if (std::cin.peek() == EOF || failed) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << s;
}

void moveChar(std::string& grid, PC& C, int x, int y) {
    int pos = 0;
    if (C.x != 0 && C.y != 0) {
        for (int i = 0; i < 2*C.y; i++) {
            pos = grid.find_first_of("\n", pos+1);
        }
        for (int i = 0; i < C.x; i++) {
            pos = grid.find_first_of("|", pos+1);
        }
        grid.replace(pos+1, 2, "  ");
    }
    
    C.x = x;
    C.y = y;
    pos = 0;
    for (int i = 0; i < 2*y; i++) {
        pos = grid.find_first_of("\n", pos+1);
    }
    for (int i = 0; i < x; i++) {
        pos = grid.find_first_of("|", pos+1);
    }
    grid.replace(pos+1, 2, C.name.substr(0, 2));
}

int dist(PC& a, PC& b) {
    return 5 * std::max(abs(a.x - b.x), abs(a.y - b.y));
}

int roll(int qty, int sides) {
    int result = 0;
    for (int i = 0; i < qty; i++) {
        result += ((std::rand() % sides) + 1);
    }
    return result;
}

int rd20(int adv) {
    if (adv > 0) {
        return std::max((std::rand() % 20) + 1, (std::rand() % 20) + 1);
    } else if (adv < 0) {
        return std::min((std::rand() % 20) + 1, (std::rand() % 20) + 1);
    } else {
        return (std::rand() % 20) + 1;
    }
}

int weapDam(PC& C, Weapon W, bool crit) {
    int m = 0;
    if (W.fin) {
        m = std::max(mod(C.abilities[0]), mod(C.abilities[1]));
    } else if (W.range) {
        m = mod(C.abilities[1]);
    } else {
        m = mod(C.abilities[0]);
    }
    
    int mult = 1;
    if (crit) {
        mult = 2;
    }
    int damage = 0;
    if (W.vers) {
        damage = roll(W.qy*mult, W.sds + 2) + m;
    } else {
        damage = roll(W.qy*mult, W.sds) + m;
    }
    
    return std::max(damage, 0);
}

int mod(int attr) {
    return (attr / 2) - 5;
}

bool cmpInit(const PC& A, const PC& B) {
    return A.init < B.init;
}

// Declaration

PC::PC() {
    
}

PC::PC(std::string n, std::string cl, int lv, int H, int A, int sp, int st, int d, int co, int i, int w, int ch, Weapon we) {
    name = n;
    cls = Class(cl, lv);
    prof = ((lv-1) / 4) + 2;
    HP = H;
    AC = A;
    spd = sp;
    resAndImm = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    abilities = {st, d, co, i, w, ch};
    wep = we;
    x = y = 0;
    advToHit = advToBeHit = 0;
    reaction = 1;
    init = roll(1, 20) + mod(abilities[1]);
    if (cls.name == "barbarian" && cls.lvl >= 7) {
        init = std::max(init, roll(1, 20) + mod(abilities[1]));
    }
}

int PC::attacks() const {
    if (cls.lvl < 5) {
        return 1;
    } else if (cls.name == "barbarian" || cls.name == "paladin" || cls.name == "monk") {
        return 2;
    } else if (cls.name != "fighter") {
        return 1;
    } else if (cls.lvl < 11) {
        return 2;
    } else if (cls.lvl < 20) {
        return 3;
    } else {
        return 4;
    }
}

// Combat Functions

void PC::attack(PC& C, Weapon W, std::vector<PC> chars, std::string grid) {
    int r = rd20(advToHit + C.advToBeHit);
    bool crit = false;
    if (r == 20) {
        crit = true;
        std::cout << "A critical hit!" << std::endl;
    }
    if (crit || r + std::max(mod(abilities[0]), mod(abilities[1])) + prof >= C.AC) {
        int d = weapDam(C, W, crit);
        
        // Rogue sneak attack
        if (cls.name == "rogue") {
            bool allyAdj = false;
            for (uint64_t i = 0; i < chars.size(); i++) {
                if (team == chars[i].team && !(*this == chars[i]) && dist(C, chars[i]) <= 5) {
                    allyAdj = true;
                }
            }
            if (advToHit + C.advToBeHit >= 1 || allyAdj) {
                d += roll(((C.cls.lvl+1) / 2)*(crit+1), 6);
            }
        
        // Paladin smite
        } else if (cls.name == "paladin" && (cls.ss[1] || cls.ss[2] || cls.ss[3] || cls.ss[4] || cls.ss[5])) {
            if (cls.lvl >= 11) {
                d += roll(1+crit, 8);
            }
            std::string input;
            if (crit) {
                std::cout << "You rolled a crit! Would you like to add a smite to this attack?" << std::endl;
            } else {
                std::cout << "You hit. Would you like to add a smite to this attack? (y/n)" << std::endl;
            }
            getline(std::cin, input);
            if (input == "y") {
                uint32_t lvl;
                std::cout << "What level smite will you use?" << std::endl;
                std::cin >> lvl;
                while (std::cin.fail() || cls.ss[lvl] == 0) {
                    invalid("You don't have any spell slots of that level\n");
                    std::cin >> lvl;
                }
                cls.ss[lvl]--;
                d += roll((lvl+1)*(crit+1), 8);
            }
        } else if (cls.name == "barbarian" && C.cls.inRage) {
            d += cls.rageBonus;
            if (crit) {
                d += roll(cls.extraCrit, W.sds);
            }
        }
        
        d *= C.resAndImm[W.damType];
        C.HP -= d;
        std::cout << *this << " hit " << C << " for " << d << " damage!" << std::endl;
        std::cout << C << " has " << C.HP << " HP left." << std::endl;
    } else {
        std::cout << *this << "'s attack missed!" << std::endl;
    }
}

void PC::castTarget(Spell s, std::string spell, std::string grid, PC& C, std::vector<PC> &chars) {
    int extra = 0;
    bool half = true;
    if (s.lvl == 0) {
        extra += (C.cls.lvl+1) / 6;
        half = false;
    }
    
    if (s.dice != 0) {
        if (s.saveType == -1) {
            spellAttack(C, s.dice + extra, s.sides);
        } else {
            spellSave(half, C, s.saveType, s.dice + extra, s.sides, chars);
        }
    }
    
    // Secondary effects
    if (spell == "chill touch") {
        // can't heal for round
    } else if (spell == "eldritch blast") {
        // multitarget as lvl up
    } else if (spell == "frostbite") {
        // disadv on next weapon attack
    } else if (spell == "infestation") {
        int move = roll(1, 4);
        if (move == 1) {
            moveChar(grid, C, x, y+1);
        } else if (move == 2) {
            moveChar(grid, C, x, y-1);
        } else if (move == 3) {
            moveChar(grid, C, x+1, y);
        } else {
            moveChar(grid, C, x-1, y);
        }
    } else if (spell == "lightning lure") {
        // 10 ft closer
    } else if (spell == "mind sliver") {
        // -1d4 on next save
    } else if (spell == "ray of frost") {
        // -10 ft speed
    } else if (spell == "sapping sting") {
        // prone
    } else if (spell == "shocking grasp") {
        // no reactions
    } else if (spell == "thorn whip") {
        // 10 ft closer
    } else if (spell == "vicious mockery") {
        // disadv on next attack
    }
    // continue for all spells with secondary effects
}

void PC::castRadius(Spell s, std::string spell, std::string grid, int x, int y, std::vector<PC> &PCs) {
    int radius = 0;
    if (spell == "shatter") {
        radius = 10;
    } else if (spell == "snilloc's snowball storm") {
        radius = 5;
    } else if (spell == "wither and bloom") {
        radius = 10;
        // secondary
    } else if (spell == "fireball") {
        radius = 20;
    } else if (spell == "ice storm") {
        radius = 20;
        // secondary
    } else if (spell == "vitriolic sphere") {
        radius = 20;
        // secondary
    } else if (spell == "flame strike") {
        radius = 10;
    } else if (spell == "synaptic static") {
        radius = 20;
        // secondary
    } else if (spell == "circle of death") {
        radius = 60;
    } else if (spell == "otiluke's freezing sphere") {
        radius = 60;
    } else if (spell == "sunburst") {
        radius = 60;
        // secondary
    }
    
    for (uint64_t i = 0; i < PCs.size(); i++) {
        if (std::sqrt(std::pow(PCs[i].x-x, 2) + std::pow(PCs[i].y-y, 2)) <= (radius/5)+.5) {
            spellSave(true, PCs[i], s.saveType, s.dice, s.sides, PCs);
        }
    }
}

void PC::castLine(Spell s, std::string spell, std::string direction, std::string grid, std::vector<PC> &PCs) {
    std::vector<PC> inRange;
    if (direction == "north") {
        for (uint64_t i = 0; i < PCs.size(); i++) {
            if (PCs[i].x == x && PCs[i].y < y && y - PCs[i].y <= s.range / 5) {
                inRange.push_back(PCs[i]);
            }
        }
    } else if (direction == "northeast") {
        for (uint64_t i = 0; i < PCs.size(); i++) {
            if (PCs[i].x - x == -(PCs[i].y - y) && PCs[i].x - x > 0 && PCs[i].x - x <= s.range / 5) {
                inRange.push_back(PCs[i]);
            }
        }
    } else if (direction == "east") {
        for (uint64_t i = 0; i < PCs.size(); i++) {
            if (PCs[i].x > x && PCs[i].x - x <= s.range / 5 && PCs[i].y == y) {
                inRange.push_back(PCs[i]);
            }
        }
    } else if (direction == "southeast") {
        for (uint64_t i = 0; i < PCs.size(); i++) {
            if (PCs[i].x - x == PCs[i].y - y && PCs[i].x - x > 0 && PCs[i].x - x <= s.range / 5) {
                inRange.push_back(PCs[i]);
            }
        }
    } else if (direction == "south") {
        for (uint64_t i = 0; i < PCs.size(); i++) {
            if (PCs[i].x == x && PCs[i].y > y && PCs[i].y - y <= s.range / 5) {
                inRange.push_back(PCs[i]);
            }
        }
    } else if (direction == "southwest") {
        for (uint64_t i = 0; i < PCs.size(); i++) {
            if (-(PCs[i].x - x) == PCs[i].y - y && PCs[i].y - y > 0 && PCs[i].y - y <= s.range / 5) {
                inRange.push_back(PCs[i]);
            }
        }
    } else if (direction == "west") {
        for (uint64_t i = 0; i < PCs.size(); i++) {
            if (PCs[i].x < x && x - PCs[i].x <= s.range / 5 && PCs[i].y == y) {
                inRange.push_back(PCs[i]);
            }
        }
    } else if (direction == "northwest") {
        for (uint64_t i = 0; i < PCs.size(); i++) {
            if (PCs[i].x - x == PCs[i].y - y && PCs[i].x - x < 0 && -(PCs[i].x - x) <= s.range / 5) {
                inRange.push_back(PCs[i]);
            }
        }
    }
    
    for (uint64_t i = 0; i < inRange.size(); i++) {
        spellSave(true, inRange[i], s.saveType, s.dice, s.sides, PCs);
    }
}

void PC::castCone(Spell s, std::string spell, std::string direction, std::string grid, std::vector<PC> &PCs) {
    std::vector<PC> inRange;
    if (direction == "north") {
        int yDiff = 0;
        for (uint64_t i = 0; i < PCs.size(); i++) {
            yDiff = y - PCs[i].y;
            if (yDiff > 0 && yDiff <= s.range / 5 && abs(x - PCs[i].x) <= yDiff / 2) {
                inRange.push_back(PCs[i]);
            }
        }
    } else if (direction == "east") {
        int xDiff = 0;
        for (uint64_t i = 0; i < PCs.size(); i++) {
            xDiff = PCs[i].x - x;
            if (xDiff > 0 && xDiff <= s.range / 5 && abs(y - PCs[i].y) <= xDiff / 2) {
                inRange.push_back(PCs[i]);
            }
        }
    } else if (direction == "south") {
        int yDiff = 0;
        for (uint64_t i = 0; i < PCs.size(); i++) {
            yDiff = PCs[i].y - y;
            if (yDiff > 0 && yDiff <= s.range / 5 && abs(x - PCs[i].x) <= yDiff / 2) {
                inRange.push_back(PCs[i]);
            }
        }
    } else if (direction == "west") {
        int xDiff = 0;
        for (uint64_t i = 0; i < PCs.size(); i++) {
            xDiff = x - PCs[i].x;
            if (xDiff > 0 && xDiff <= s.range / 5 && abs(y - PCs[i].y) <= xDiff / 2) {
                inRange.push_back(PCs[i]);
            }
        }
    }
    
    for (uint64_t i = 0; i < inRange.size(); i++) {
        spellSave(true, inRange[i], s.saveType, s.dice, s.sides, PCs);
    }
}

void PC::spellAttack(PC& C, int dice, int sides) {
    if (rd20(0) + prof + mod(abilities[cls.scA]) >= C.AC) {
        int d = roll(dice, sides);
        C.HP -= d;
        std::cout << *this << " hit " << C << " for " << d << " damage!" << std::endl;
        std::cout << C << " has " << C.HP << " HP left." << std::endl;
    } else {
        std::cout << *this << "'s attack missed!" << std::endl;
    }
}

void PC::spellSave(bool half, PC& C, int ablty, int dice, int sides, std::vector<PC> &chars) {
    int dam = roll(dice, sides);
    bool fail = false;
    int DC = 8 + prof + mod(abilities[cls.scA]);
    int roll = rd20(0);
    // Aura of Protection check
    for (uint64_t i = 0; i < chars.size(); i++) {
        if (chars[i].cls.name == "paladin" && chars[i].cls.lvl >= 6 && C.team == chars[i].team) {
            if (dist(C, chars[i]) <= 10 || (chars[i].cls.lvl >= 18 && dist(C, chars[i]) <= 30)) {
                roll += mod(chars[i].abilities[5]);
            }
        }
    }
    // Flash of Genius check
    int total = roll + mod(C.abilities[ablty]) + C.cls.saveProf[ablty]*C.prof;
    for (uint64_t i = 0; i < chars.size(); i++) {
        if (chars[i].cls.name == "artificer" && chars[i].cls.flashOfGenius > 0 && C.team == chars[i].team && dist(C, chars[i]) <= 30) {
            std::string input;
            std::cout << C << " would roll a " << total << " on their save.";
            std::cout << " Would " << chars[i] << " like to use a Flash of Genius to increase it by ";
            std::cout << mod(chars[i].abilities[3]) << "? (" << chars[i].cls.flashOfGenius << " uses left) (y/n)" << std::endl;
            getline(std::cin, input);
            if (input == "y") {
                total += mod(chars[i].abilities[3]);
                chars[i].cls.flashOfGenius--;
            }
        }
    }
    if (total < DC) {
        fail = true;
    }
    
    // Reroll prompts
    if (fail) {
        if (C.cls.indom) {
            std::string ans;
            std::cout << C << "failed their save. Would they like to reroll? (y/n), (" << C.cls.indom << " use(s))" << std::endl;
            std::cin >> ans;
            if (ans == "y") {
                C.cls.indom--;
                if (rd20(0) + mod(C.abilities[ablty]) + C.cls.saveProf[ablty]*C.prof >= DC) {
                    fail = false;
                    std::cout << "You succeeded!" << std::endl;
                } else {
                    std::cout << "You still failed." << std::endl;
                }
            }
        } else if (C.cls.name == "monk" && C.cls.lvl >= 14 && C.cls.ki) {
            std::string ans;
            std::cout << C << "failed their save. Would they like to reroll? (y/n), (costs 1 ki, " << C.cls.ki << " ki remaining)" << std::endl;
            std::getline(std::cin, ans);
            if (ans == "y") {
                C.cls.ki--;
                if (rd20(0) + mod(C.abilities[ablty]) + C.cls.saveProf[ablty]*C.prof >= DC) {
                    fail = false;
                    std::cout << "You succeeded!" << std::endl;
                } else {
                    std::cout << "You still failed." << std::endl;
                }
            }
        }
    }
    
    if (!half && !fail) {
        std::cout << C << " succeeded their save and took no damage." << std::endl;
        return;
    }
    bool triggerEvasion = (ablty == 1 && C.cls.evasion);
    if (fail && triggerEvasion) {
        C.HP -= (dam / 2);
        std::cout << C << " failed their save and took " << dam / 2 << " damage due to evasion." << std::endl;
    } else if (fail && !triggerEvasion) {
        C.HP -= dam;
        std::cout << C << " failed their save and took " << dam << " damage." << std::endl;
    } else if (!fail && triggerEvasion) {
        std::cout << C << " succeeded their save and took no damage due to evasion." << std::endl;
    } else if (!fail && !triggerEvasion) {
        C.HP -= (dam / 2);
        std::cout << C << " succeeded their save and took " << dam / 2 << " damage." << std::endl;
    }
}

void PC::initMonkFist() {
    if (cls.name == "monk" && wep.sds == 1) {
        if (cls.lvl >= 17) {
            wep.sds = 10;
        } else if (cls.lvl >= 11) {
            wep.sds = 8;
        } else if (cls.lvl >= 5) {
            wep.sds = 6;
        } else {
            wep.sds = 4;
        }
    }
}

// Overriden Operators

std::ostream& operator<<(std::ostream& stream, PC C) {
    return stream << C.name;
}

bool operator==(const PC& A, const PC& B) {
    return A.name == B.name;
}