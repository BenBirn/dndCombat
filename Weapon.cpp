#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include "Weapon.h"

Weapon::Weapon() {
    
}

Weapon::Weapon(int q, int s, int d, int t, bool f, bool v, bool r) {
    qy = q;
    sds = s;
    dist = d;
    damType = t;
    fin = f;
    vers = v;
    range = r;
}

std::unordered_map<std::string, Weapon> initWeapons() {
    // Add thrown, handedness
    Weapon club = Weapon(1, 4, 5, 0, false, false, false);
    Weapon dagger = Weapon(1, 4, 5, 1, true, false, false);
    Weapon greatclub = Weapon(1, 8, 5, 0, false, false, false);
    Weapon handaxe = Weapon(1, 6, 5, 2, false, false, false);
    Weapon javelin = Weapon(1, 6, 5, 1, false, false, false);
    Weapon hammer = Weapon(1, 4, 5, 0, false, false, false);
    Weapon mace = Weapon(1, 6, 5, 0, false, false, false);
    Weapon quarterstaff = Weapon(1, 6, 5, 0, false, true, false);
    Weapon sickle = Weapon(1, 4, 5, 2, false, false, false);
    Weapon spear = Weapon(1, 6, 5, 1, false, false, false);
    
    Weapon lCrossbow = Weapon(1, 8, 80, 1, false, false, true);
    Weapon dart = Weapon(1, 4, 20, 1, true, false, true);
    Weapon shortbow = Weapon(1, 6, 80, 1, false, false, true);
    Weapon sling = Weapon(1, 4, 30, 0, false, false, true);
    
    Weapon battleaxe = Weapon(1, 8, 5, 2, false, true, false);
    Weapon flail = Weapon(1, 8, 5, 0, false, false, false);
    Weapon glaive = Weapon(1, 10, 10, 2, false, false, false);
    Weapon greataxe = Weapon(1, 12, 5, 2, false, false, false);
    Weapon greatsword = Weapon(2, 6, 5, 2, false, false, false);
    Weapon halberd = Weapon(1, 10, 10, 2, false, false, false);
    Weapon lance = Weapon(1, 12, 10, 1, false, false, false); // Special
    Weapon longsword = Weapon(1, 8, 5, 2, false, true, false);
    Weapon maul = Weapon(2, 6, 5, 0, false, false, false);
    Weapon morningstar = Weapon(1, 8, 5, 1, false, false, false);
    Weapon pike = Weapon(1, 10, 10, 1, false, false, false);
    Weapon rapier = Weapon(1, 8, 5, 1, true, false, false);
    Weapon scimitar = Weapon(1, 6, 5, 2, true, false, false);
    Weapon shortsword = Weapon(1, 6, 5, 1, true, false, false);
    Weapon trident = Weapon(1, 6, 5, 1, false, false, false);
    Weapon warpick = Weapon(1, 8, 5, 1, false, false, false);
    Weapon warhammer = Weapon(1, 8, 5, 0, false, true, false);
    Weapon whip = Weapon(1, 4, 10, 2, true, false, false);
    
    Weapon blowgun = Weapon(1, 1, 25, 1, false, false, true);
    Weapon haCrossbow = Weapon(1, 6, 30, 1, false, false, true);
    Weapon heCrossbow = Weapon(1, 10, 100, 1, false, false, true);
    Weapon longbow = Weapon(1, 8, 150, 1, false, false, true);
    
    Weapon fist = Weapon(1, 1, 5, 0, false, false, false);
    
    std::unordered_map<std::string, Weapon> weapons = {
        {"club", club}, {"dagger", dagger}, {"greatclub", greatclub}, {"handaxe", handaxe}, {"javelin", javelin},
        {"hammer", hammer}, {"mace", mace}, {"quarterstaff", quarterstaff}, {"sickle", sickle}, {"spear", spear},
        {"light crossbow", lCrossbow}, {"dart", dart}, {"shortbow", shortbow}, {"sling", sling}, {"battleaxe", battleaxe},
        {"flail", flail}, {"glaive", glaive}, {"greataxe", greataxe}, {"greatsword", greatsword}, {"halberd", halberd},
        {"lance", lance}, {"longsword", longsword}, {"maul", maul}, {"morningstar", morningstar}, {"pike", pike},
        {"rapier", rapier}, {"scimitar", scimitar}, {"shortsword", shortsword}, {"trident", trident}, {"warpick", warpick},
        {"warhammer", warhammer}, {"whip", whip}, {"blowgun", blowgun}, {"hand crossbow", haCrossbow},
        {"heavy crossbow", heCrossbow}, {"longbow", longbow}, {"fist", fist}
    };
    
    return weapons;
}