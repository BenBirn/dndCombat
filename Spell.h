#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

#pragma once

class Spell{
  
public:
    int lvl;
    std::unordered_set<std::string> classes;
    std::string AOE;
    int range;
    int dice;
    int sides;
    int saveType;
    bool conc;

public:
    
    Spell();
    
    Spell(int lv, std::unordered_set<std::string> clses, std::string a, int r, int dice, int sides, int t, bool c);

};

std::unordered_map<std::string, Spell> initSpells();