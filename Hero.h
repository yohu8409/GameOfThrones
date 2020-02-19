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
#include "Warrior.cpp"
#include "Tile.cpp"

class Hero{
    private:
        bool life = true;
        string name;
        int money;
        int influence;
        int army;
        int points;
        Warrior fighters[4];
        int row;
        int column;
        bool ship;
        vector<Tile> ownedPlaces;
        vector<Tile> firstCities;
    public:
        Hero();
        Hero(string newName, int newMoney , int newInfluence , int newArmy , int newPoints , Warrior newFighters[4] , int newRow , int newColumn , bool newShip);
        bool getLife();// returns whether or not the hero has died
        void setLife(bool newLife);
        string getName();
        void setName(string newName);
        int getMoney();
        void setMoney(int num);
        int getInfluence();
        void setInfluence(int num);
        int getArmy();
        void setArmy(int num);
        int getPoints();
        void setPoints(int num);
        string getWarriorName(int idx);
        void setWarriorName(int idx , string newName);
        Warrior getWarrior(int idx);
        void setWarrior(int idx , Warrior newWarrior);
        int getRow();
        void setRow(int num);
        int getColumn();
        void setColumn(int num);
        bool getShip();
        void setShip(bool newShip);
        void printStat();
        bool warriorShip();
        void addOwnerShip(Tile place);
        bool checkOwnerShip(Tile place);
        void eraseOwnerShip(Tile place);
        int getSizeOfOwnedPlaces();
        Tile getOwnedPlaces(int idx);
        int getWarriorSize();
        void addCity(Tile place);
        bool checkFirstCity(Tile place);
        int getSizeOfFirstCities();
};