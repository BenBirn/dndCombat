#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include "Spell.h"

Spell::Spell() {
    
}

Spell::Spell(int lv, std::unordered_set<std::string> clses, std::string a, int r, int d, int s, int t, bool c) {
    lvl = lv;
    classes = clses;
    AOE = a;
    range = r;
    dice = d;
    sides = s;
    saveType = t;
    conc = c;
}

std::unordered_map<std::string, Spell> initSpells() {
    Spell acidSplash = Spell(0, {"artificer", "sorcerer", "wizard"}, "target", 60, 1, 6, 1, false);
    Spell chillTouch = Spell(0, {"sorcerer", "warlock", "wizard"}, "target", 120, 1, 8, -1, false);
    Spell eldritchBlast = Spell(0, {"warlock"}, "target", 120, 1, 10, -1, false);
    Spell fireBolt = Spell(0, {"artificer", "sorcerer", "wizard"}, "target", 120, 1, 10, -1, false);
    Spell frostbite = Spell(0, {"artificer", "druid", "sorcerer", "warlock", "wizard"}, "target", 60, 1, 6, 2, false);
    Spell infestation = Spell(0, {"druid", "sorcerer", "warlock", "wizard"}, "target", 30, 1, 6, 2, false);
    Spell lightningLure = Spell(0, {"artificer", "sorcerer", "warlock", "wizard"}, "target", 15, 1, 8, 0, false);
    Spell mindSliver = Spell(0, {"sorcerer", "warlock", "wizard"}, "target", 60, 1, 6, 3, false);
    Spell poisonSpray = Spell(0, {"artificer", "druid", "sorcerer", "warlock", "wizard"}, "target", 10, 1, 12, 2, false);
    Spell primalSavagery = Spell(0, {"druid"}, "target", 5, 1, 10, -1, false);
    Spell produceFlame = Spell(0, {"druid"}, "target", 30, 1, 8, -1, false);
    Spell rayOfFrost = Spell(0, {"artificer", "sorcerer", "wizard"}, "target", 60, 1, 8, -1, false);
    Spell sacredFlame = Spell(0, {"cleric"}, "target", 60, 1, 8, 1, false);
    Spell shockingGrasp = Spell(0, {"artificer", "sorcerer", "wizard"}, "target", 5, 1, 8, -1, false);
    Spell swordBurst = Spell(0, {"artificer", "sorcerer", "warlock", "wizard"}, "radius", 0, 1, 6, 1, false);
    Spell thornWhip = Spell(0, {"artificer", "druid"}, "target", 30, 1, 6, -1, false);
    Spell thunderclap = Spell(0, {"artificer", "bard", "druid", "sorcerer", "warlock", "wizard"}, "radius", 0, 1, 6, 2, false);
    Spell tollTheDead = Spell(0, {"cleric", "warlock", "wizard"}, "target", 60, 1, 12, 4, false);
    Spell viciousMockery = Spell(0, {"bard"}, "target", 60, 1, 4, 4, false);
    Spell wordOfRadiance = Spell(0, {"cleric"}, "radius", 0, 1, 6, 2, false);
    
    Spell armorOfAgathys = Spell(1, {"warlock"}, "", 0, 0, 0, -1, false);
    Spell armsOfHadar = Spell(1, {"warlock"}, "radius", 0, 2, 6, 0, false);
    Spell bane = Spell(1, {"bard", "cleric"}, "multitarget", 30, 0, 0, 5, true);
    Spell bless = Spell(1, {"cleric", "paladin"}, "multitarget", 30, 0, 0, 0, true);
    Spell burningHands = Spell(1, {"sorcerer", "wizard"}, "cone", 15, 3, 6, 1, false);
    Spell catapult = Spell(1, {"artificer", "sorcerer", "wizard"}, "target", 150, 3, 8, 1, false);
    // Spell causeFear
    Spell chaosBolt = Spell(1, {"sorcerer"}, "target", 120, 3, 8, -1, false);
    Spell chromaticOrb = Spell(1, {"sorcerer", "wizard"}, "target", 90, 3, 8, -1, false);
    // Spell command
    // Spell cureWounds
    Spell dissWhispers = Spell(1, {"bard"}, "target", 60, 3, 6, 4, false);
    // Spell ensStrike
    // Spell entangle
    Spell faerieFire = Spell(1, {"artificer", "bard", "druid"}, "cube", 60, 0, 0, 1, true);
    Spell frostFingers = Spell(1, {"wizard"}, "cone", 15, 2, 8, 2, false);
    Spell guidingBolt = Spell(1, {"cleric"}, "target", 120, 4, 6, -1, false);
    // Spell hailOfThonrns
    // Spell healingWord
    Spell hex = Spell(1, {"warlock"}, "target", 90, 0, 0, -1, true);
    Spell huntersMark = Spell(1, {"ranger"}, "target", 90, 0, 0, -1, true);
    // Spell iceKnife
    // Spell mageArmor
    Spell magicMissile = Spell(1, {"sorcerer", "wizard"}, "multitarget", 120, 3, 4, -1, false);
    Spell rayOfSickness = Spell(1, {"sorcerer", "wizard"}, "target", 60, 2, 8, -1, false);
    // Spell searingSmite
    // Spell shield
    // Spell shieldOfFaith
    Spell tashasCausticBrew = Spell(1, {"artificer", "sorcerer", "wizard"}, "line", 30, 2, 4, 1, true);
    Spell tashasHideousLaughter = Spell(1, {"bard", "wizard"}, "target", 30, 0, 0, 4, true);
    // Spell thunderSmite
    Spell thunderwave = Spell(1, {"bard", "druid", "sorcerer", "wizard"}, "cube", 0, 2, 8, 2, false);
    Spell witchBolt = Spell(1, {"warlock"}, "target", 30, 1, 12, -1, true);
    // Spell wrathSmite
    // Spell zephyrStrike
    
    Spell aganazzarsScorcher = Spell(2, {"sorcerer", "wizard"}, "line", 30, 3, 8, 1, false);
    Spell melfsAcidArrow = Spell(2, {"wizard"}, "target", 90, 6, 4, -1, false);
    Spell rimesBindingIce = Spell(2, {"sorcerer", "wizard"}, "cone", 30, 3, 8, 2, false);
    Spell scorchingRay = Spell(2, {"sorcerer", "wizard"}, "target", 120, 2, 6, -1, false);
    Spell shatter = Spell(2, {"bard", "sorcerer", "warlock", "wizard"}, "radius", 90, 3, 8, 2, false);
    Spell snillocsSnowballStorm = Spell(2, {"sorcerer", "wizard"}, "radius", 90, 3, 6, 1, false);
    Spell witherAndBloom = Spell(2, {"druid", "sorcerer", "wizard"}, "radius", 60, 2, 6, 2, false);
    
    Spell conjureBarrage = Spell(3, {"ranger"}, "cone", 60, 3, 8, 1, false);
    Spell eruptingEarth = Spell(3, {"druid", "sorcerer", "wizard"}, "cube", 120, 3, 12, 1, false);
    Spell fireball = Spell(3, {"sorcerer", "wizard"}, "radius", 150, 8, 6, 1, false);
    Spell lightningBolt = Spell(3, {"sorcerer", "wizard"}, "line", 100, 8, 6, 1, false);
    Spell thunderStep = Spell(3, {"sorcerer", "warlock", "wizard"}, "radius", 90, 3, 10, 2, false);
    Spell tidalWave = Spell(3, {"druid", "sorcerer", "wizard"}, "rect", 120, 4, 8, 1, false);
    
    Spell blight = Spell(4, {"druid", "sorcerer", "warlock", "wizard"}, "target", 30, 8, 8, 2, false);
    Spell iceStorm = Spell(4, {"druid", "sorcerer", "wizard"}, "radius", 300, 6, 8, 1, false);
    Spell raulothimsPsychicLance = Spell(4, {"bard", "sorcerer", "warlock", "wizard"}, "target", 120, 7, 6, 3, false);
    Spell vitriolicSphere = Spell(4, {"sorcerer", "wizard"}, "radius", 150, 15, 4, 1, false);
    
    Spell coneOfCold = Spell(5, {"sorcerer", "wizard"}, "cone", 60, 8, 8, 2, false);
    Spell destructiveWave = Spell(5, {"paladin"}, "radius", 0, 10, 6, 2, false);
    Spell flameStrike = Spell(5, {"cleric"}, "radius", 60, 8, 6, 1, false);
    Spell negativeEnergyFlood = Spell(5, {"warlock", "wizard"}, "target", 60, 5, 12, 2, false);
    Spell steelWindStrike = Spell(5, {"ranger", "wizard"}, "multitarget", 30, 6, 10, -1, false);
    Spell synapticStatic = Spell(5, {"bard", "sorcerer", "warlock", "wizard"}, "radius", 120, 8, 6, 3, false);
    
    Spell chainLightning = Spell(6, {"sorcerer", "wizard"}, "multitarget", 150, 10, 8, 1, false);
    Spell circleOfDeath = Spell(6, {"sorcerer", "warlock", "wizard"}, "radius", 150, 8, 6, 2, false);
    Spell disintegrate = Spell(6, {"sorcerer", "wizard"}, "target", 60, 10, 6, 1, false);
    Spell harm = Spell(6, {"cleric"}, "target", 60, 14, 6, 2, false);
    Spell otilukesFreezingSphere = Spell(6, {"wizard"}, "radius", 300, 10, 6, 2, false);
    
    Spell fingerOfDeath = Spell(7, {"sorcerer", "warlock", "wizard"}, "target", 60, 7, 8, 2, false);
    Spell fireStorm = Spell(7, {"cleric", "druid", "sorcerer",}, "cube", 150, 7, 10, 1, false);
    Spell prismaticSpray = Spell(7, {"sorcerer", "wizard"}, "cone", 60, 10, 6, 1, false);
    
    Spell abiDalzimsHorridWilting = Spell(8, {"sorcerer", "wizard"}, "cube", 150, 12, 8, 2, false);
    Spell feeblemind = Spell(8, {"bard", "druid", "warlock", "wizard"}, "target", 150, 4, 6, 3, false);
    Spell sunburst = Spell(8, {"druid", "sorcerer", "wizard"}, "radius", 150, 12, 6, 2, false);
    
    Spell meteorSwarm = Spell(9, {"sorcerer", "wizard"}, "radius", 5280, 40, 6, 1, false);
    Spell psychicScream = Spell(9, {"bard", "sorcerer", "warlock", "wizard"}, "multitarget", 90, 14, 6, 3, false);
    
    
    std::unordered_map<std::string, Spell> spells = {
        {"acid splash", acidSplash}, {"chill touch", chillTouch}, {"eldritch blast", eldritchBlast},
        {"fire bolt", fireBolt}, {"frostbite", frostbite}, {"infestation", infestation},
        {"lightning lure", lightningLure}, {"mind sliver", mindSliver}, {"poison spray", poisonSpray},
        {"primal savagery", primalSavagery}, {"ray of frost", rayOfFrost}, {"sacred flame", sacredFlame},
        {"shocking grasp", shockingGrasp}, {"sword burst", swordBurst}, {"thunderclap", thunderclap},
        {"toll the dead", tollTheDead}, {"vicious mockery", viciousMockery}, {"word of radiance", wordOfRadiance},
        {"armor of agathys", armorOfAgathys}, {"arms of hadar", armsOfHadar}, {"bane", bane}, {"bless", bless},
        {"burning hands", burningHands}, {"catapult", catapult}, {"chaos bolt", chaosBolt},
        {"chromatic orb", chromaticOrb}, {"dissonant whispers", dissWhispers}, {"faerie fire", faerieFire},
        {"guiding bolt", guidingBolt}, {"hex", hex}, {"hunters mark", huntersMark}, {"magic missile", magicMissile},
        {"ray of sickness", rayOfSickness}, {"tasha's caustic brew", tashasCausticBrew}, {"frost fingers", frostFingers},
        {"tasha's hideous laughter", tashasHideousLaughter}, {"thunderwave", thunderwave}, {"witch bolt", witchBolt},
        {"aganazzar's scorcher", aganazzarsScorcher}, {"melf's acid arrow", melfsAcidArrow}, 
        {"rime's binding ice", rimesBindingIce}, {"scorching ray", scorchingRay}, {"shatter", shatter},
        {"snilloc's snowball storm", snillocsSnowballStorm}, {"wither and bloom", witherAndBloom},
        {"erupting earth", eruptingEarth}, {"fireball", fireball}, {"lightning bolt", lightningBolt},
        {"thunder step", thunderStep}, {"tidal wave", tidalWave}, {"blight", blight}, {"ice storm", iceStorm},
        {"raulothim's psychic lance", raulothimsPsychicLance}, {"vitriolic sphere", vitriolicSphere},
        {"cone of cold", coneOfCold}, {"destructive wave", destructiveWave}, {"flame strike", flameStrike},
        {"negative energy flood", negativeEnergyFlood}, {"steel wind strike", steelWindStrike},
        {"synaptic static", synapticStatic}, {"chain lightning", chainLightning}, {"circle of death", circleOfDeath},
        {"disintegrate", disintegrate}, {"harm", harm}, {"otiluke's freezing sphere", otilukesFreezingSphere},
        {"finger of death", fingerOfDeath}, {"fire storm", fireStorm}, {"prismatic spray", prismaticSpray},
        {"abi-dalzims horrid wilting", abiDalzimsHorridWilting}, {"feeblemind", feeblemind}, {"sunburst", sunburst},
        {"conjure barrage", conjureBarrage}, {"meteor swarm", meteorSwarm}, {"psychic scream", psychicScream}
    };
    
    return spells;
}