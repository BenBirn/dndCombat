#include <iostream>
#include <string>
#include <unordered_map>

#pragma once

class Weapon{
  
public:
    int qy;
    int sds;
    int dist;
    int damType;
    bool fin;
    bool vers;
    bool range;

public:
    
    Weapon();
    
    Weapon(int q, int s, int d, int t, bool f, bool v, bool r);

};

std::unordered_map<std::string, Weapon> initWeapons();