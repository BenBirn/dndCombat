#include <iostream>
#include <string>
#include <vector>
#include "Class.h"
#include "Spell.h"
#include "Weapon.h"

#pragma once

void invalid(std::string s);

int roll(int qty, int sides);

int mod(int attr);

class PC{
    
public:
    Class cls;
    int prof;
    int HP;
    int AC;
    int spd;
    std::vector<float> resAndImm;
    std::vector<int> abilities;
    std::string name;
    Weapon wep;
    std::string team;
    
    int x;
    int y;
    int advToHit;
    int advToBeHit;
    int init;
    int reaction;
    
    
public:
    
    // Constructors/Destructors
    
    PC();
    
    PC(std::string name, std::string cl, int lv, int H, int A, int sp, int st, int d, int co, int i, int w, int ch, Weapon we);
    
    int attacks() const;
    
    // Manipulation Procedures
    void rollInit();
    void attack(PC& C, Weapon W, std::vector<PC> chars, std::string grid);
    void castTarget(Spell s, std::string spell, std::string grid, PC& P, std::vector<PC> &chars);
    void castRadius(Spell s, std::string spell, std::string grid, int x, int y, std::vector<PC> &PCs);
    void castLine(Spell s, std::string spell, std::string direction, std::string grid, std::vector<PC> &PCs);
    void castCone(Spell s, std::string spell, std::string direction, std::string grid, std::vector<PC> &PCs);
    void spellAttack(PC& C, int dice, int sides);
    void spellSave(bool half, PC& C, int ablty, int dice, int sides, std::vector<PC> &chars);
    void initMonkFist();
    
    // Overriden Operators
    
    friend std::ostream& operator<<(std::ostream& stream, PC C);
    friend bool operator==(const PC& A, const PC& B);
};

void moveChar(std::string& grid, PC& C, int x, int y);

int dist(PC& a, PC& b);

bool cmpInit(const PC& A, const PC& B);