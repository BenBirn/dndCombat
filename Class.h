#include <iostream>
#include <string>
#include <vector>
#include "Weapon.h"

#pragma once

class Class{
  
public:
    std::string name;
    int lvl;
    std::vector<bool> saveProf;
    std::vector<int> ss;
    int scA;
    
    // Multiple classes
    bool evasion;
    
    // Fighter
    int sWind;
    int actSurge;
    int indom;
    
    // Barbarian
    bool inRage;
    int rageBonus;
    bool dangerSense;
    bool reckAttack;
    int extraCrit;
    
    // Monk
    int ki;
    
    // Paladin
    uint32_t layOnHands;
    
    // Artificer
    int flashOfGenius;
    
    // Monster
    

public:
    
    // Constructors
    Class();
    Class(std::string n, int l);
    
    // Access functions
    std::string getName() const;
    
    // Manipulation Procedures
    void initFeatures(int intl);

    //Class& operator=(const Class& C);
    
};