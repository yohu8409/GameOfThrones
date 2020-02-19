// CS1300 Spring 2019
// Author: YongQi Yu
// Recitation: 207 – Shipra Behera
// Cloud9 Workspace Editor Link: https://ide.c9.io/yohu8409/csci-1300_recitation
// Project 3 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;
#include "Hero.cpp"

class Map{
    private:
        Tile map[25][16];
        Warrior allFighters[14];
        Hero allHeros[6];
    public:
        Map();
        void readMap(string fileName);
        void printTiles();
        void readWarriors(string fileName);
        void printWarriors();
        void readHeros(string fileName);
        void printHeroStat();
        Hero getHero(int idx);
        void setHero(int idx , Hero H);
        Tile getTile(int row , int column);
        void setTile(Tile t1 , int row , int column);
        Warrior getWarrior(int idx);
        void setWarrior(int idx , Warrior w1);
};