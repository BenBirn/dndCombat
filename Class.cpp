#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "Class.h"
#include "Weapon.h"

Class::Class() {
    
}

Class::Class(std::string n, int l) {
    name = n;
    lvl = l;
    saveProf = {false, false, false, false, false, false};
    ss = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    scA = -1;
    rageBonus = indom = 0;
    evasion = false;
}

// Access functions
std::string Class::getName() const {
    return name;
}

// Manipulation procedures
void Class::initFeatures(int intl) {
    // Fighter
    if (name == "fighter") {
        saveProf[0] = saveProf[2] = true;
        sWind = 1;
        if (lvl >= 17) {
            actSurge = 2;
        } else if (lvl >= 2) {
            actSurge = 1;
        } else {
            actSurge = 0;
        }
        if (lvl >= 17) {
            indom = 3;
        } else if (lvl >= 13) {
            indom = 2;
        } else if (lvl >= 9) {
            indom = 1;
        }
    }

    // Barbarian
    if (name == "barbarian") {
        saveProf[0] = saveProf[2] = true;
        if (lvl >= 16) {
            rageBonus = 4;
        } else if (lvl >= 9) {
            rageBonus = 3;
        } else {
            rageBonus = 2;
        }
        if (lvl >= 17) {
            extraCrit = 3;
        } else if (lvl >= 13) {
            extraCrit = 2;
        } else if (lvl >= 9) {
            extraCrit = 1;
        }
    }
    
    // Rogue
    if (name == "rogue") {
        saveProf[1] = saveProf[3] = true;
        if (lvl >= 7) {
            evasion = true;
        }
        if (lvl >= 15) {
            saveProf[4] = true;
        }
    }
    
    // Monk
    if (name == "monk") {
        saveProf[0] = saveProf[1] = true;
        ki = 0;
        if (lvl >= 2) {
            ki = lvl;
        }
        if (lvl >= 7) {
            evasion = true;
        }
        if (lvl >= 14) {
            saveProf[2] = saveProf[3] = saveProf[4] = saveProf[5] = true;
        }
    }
    
    // Paladin
    if (name == "paladin") {
        saveProf[4] = saveProf[5] = true;
        layOnHands = 5 * lvl;
    }
    
    // Artificer
    if (name == "artificer" && lvl >= 7) {
        flashOfGenius = (intl / 2) - 5;
    } else {
        flashOfGenius = 0;
    }
    
    // Caster Spells
    if (name == "artificer" || name == "wizard") {
        scA = 3;
    } else if (name == "cleric" || name == "druid" || name == "ranger") {
        scA = 4;
    } else if (name == "bard" || name == "paladin" || name == "sorcerer" || name == "warlock") {
        scA = 5;
    }

    // Full Casters
    if (name == "wizard" || name == "sorcerer" || name == "druid" || name == "cleric" || name == "bard") {
        ss[0] = 1;
        ss[1] = 2;
        if (lvl >= 2) {
            ss[1] = 3;
        }
        if (lvl >= 3) {
            ss[1] = 4;
            ss[2] = 2;
        }
        if (lvl >= 4) {
            ss[2] = 3;
        }
        if (lvl >= 5) {
            ss[3] = 2;
        }
        if (lvl >= 6) {
            ss[3] = 3;
        }
        if (lvl >= 7) {
            ss[4] = 1;
        }
        if (lvl >= 8) {
            ss[4] = 2;
        }
        if (lvl >= 9) {
            ss[4] = 3;
            ss[5] = 1;
        }
        if (lvl >= 10) {
            ss[5] = 2;
        }
        if (lvl >= 11) {
            ss[6] = 1;
        }
        if (lvl >= 13) {
            ss[7] = 1;
        }
        if (lvl >= 15) {
            ss[8] = 1;
        }
        if (lvl >= 17) {
            ss[9] = 1;
        }
        if (lvl >= 18) {
            ss[5] = 3;
        }
        if (lvl >= 19) {
            ss[6] = 2;
        }
        if (lvl >= 20) {
            ss[7] = 2;
        }
    }
    
    // Half Casters
    if (name == "artificer" || name == "paladin" || name == "ranger") {
        if (name == "artificer") {
            ss[0] = 1;
            ss[1] = 2;
        } else {
            ss[0] = 0;
        }
        if (lvl >= 2) {
            ss[1] = 2;
        }
        if (lvl >= 3) {
            ss[1] = 3;
        }
        if (lvl >= 5) {
            ss[1] = 4;
            ss[2] = 2;
        }
        if (lvl >= 7) {
            ss[2] = 3;
        }
        if (lvl >= 9) {
            ss[3] = 2;
        }
        if (lvl >= 11) {
            ss[3] = 3;
        }
        if (lvl >= 13) {
            ss[4] = 1;
        }
        if (lvl >= 15) {
            ss[4] = 2;
        }
        if (lvl >= 17) {
            ss[4] = 3;
            ss[5] = 1;
        }
        if (lvl >= 19) {
            ss[5] = 2;
        }
    }
    
    // Warlock
    if (name == "warlock") {
        if (lvl <= 17) {
            ss[5] = 4;
        } else if (lvl <= 11) {
            ss[5] = 3;
        } else if (lvl <= 9) {
            ss[5] = 2;
        } else if (lvl <= 7) {
            ss[4] = 2;
        } else if (lvl <= 5) {
            ss[3] = 2;
        } else if (lvl <= 3) {
            ss[2] = 2;
        } else if (lvl == 2) {
            ss[1] = 2;
        } else {
            ss[1] = 1;
        }
    }
}

/*Class& Class::operator=(const Class& C) {
    if (this != &C) {
        Class temp = C;
        std::swap(name, (*this).name);
        std::swap(lvl, (*this).lvl);
    }
    return *this;
}*/