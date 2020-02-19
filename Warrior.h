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

class Warrior{
    private:
        string leader;
        string name;
        double strength;
        double loyalty;
        double morale;
        bool freedom;
        bool ship;
        bool dragonGlass;
        int row;
        int column;
    public:
        Warrior();
        Warrior(string newName , string newLeader , int newStrength , int newLoyalty , int newMorale , bool newFreedom , bool newShip , bool newDragonGlass , int newRow , int newColumn);
        string getName();
        void setName(string newName);
        double getStrength();
        void setStrength(int newStrength);
        double getLoyalty();
        void setLoyalty(int newLoyalty);
        double getMorale();
        void setMorale(int newMorale);
        bool getFreedom();
        void setFreedom(bool ans);
        bool getShip();
        void setShip(bool ans);
        bool getDragonGlass();
        void setDragonGlass(bool ans);
        int getRow();
        void setRow(int num);
        int getColumn();
        void setColumn(int num);
        string getLeader();
        void setLeader(string newLeader);
        void printStat();
};