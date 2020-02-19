// CS1300 Spring 2019
// Author: YongQi Yu
// Recitation: 207 – Shipra Behera
// Cloud9 Workspace Editor Link: https://ide.c9.io/yohu8409/csci-1300_recitation
// Project 3 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Tile{
    private:
        string owner;
        string name;
        char place;
        int row;
        int column;
        int money;
        int army;
        int points;
        bool dragonGlass;
    public:
        Tile();
        Tile(string newOwner, string newName, char newPlace ,int newMoney, int newArmy, int newPoints , bool newDragonGlass);
        string getOwner();
        void setOwner(string newOwner);
        char getPlace();
        void setPlace(char newLetter);
        string getName();
        void setName(string newName);
        int getMoney();
        void setMoney(int newMoney);
        int getArmy();
        void setArmy(int newArmy);
        int getPoints();
        void setPoints(int newPoints);
        bool getDragonGlass();
        void setDragonGlass(bool newDragonGlass);
        void setRow(int num);
        void setColumn(int num);
        int getRow();
        int getColumn();
    
        
        void printStat();
        
};