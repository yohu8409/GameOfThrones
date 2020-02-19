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
#include "Warrior.h"


Warrior::Warrior(){
    name = "NULL";
    leader = "";
    strength = 0;
    loyalty = 0;
    morale = 0;
    freedom = false;
    ship = false;
    dragonGlass = false;
    row = 0;
    column = 0;
}

Warrior::Warrior(string newName , string newLeader , int newStrength , int newLoyalty , int newMorale , bool newFreedom , bool newShip , bool newDragonGlass , int newRow , int newColumn){
     leader = newLeader;
     name = newName;
     strength = newStrength;
     loyalty = newLoyalty;
     morale = newMorale;
     freedom = newFreedom;
     ship = newShip;
     dragonGlass = newDragonGlass;
     row = newRow;
     column = newColumn;
}

string Warrior::getName(){
    return name;
}
        
void Warrior::setName(string newName){
    name = newName;
}
double Warrior::getStrength(){
    return strength;
}

void Warrior::setStrength(int newStrength){
    strength = newStrength;
}
double Warrior::getLoyalty(){
    return loyalty;
}

void Warrior::setLoyalty(int newLoyalty){
    loyalty = newLoyalty;
}

double Warrior::getMorale(){
    return morale;
}

void Warrior::setMorale(int newMorale){
    morale = newMorale;
}

bool Warrior::getFreedom(){
    return freedom;
}

void Warrior::setFreedom(bool ans){
    freedom = ans;
}

bool Warrior::getShip(){
    return ship;
}

void Warrior::setShip(bool ans){
    ship = ans;
}

bool Warrior::getDragonGlass(){
    return dragonGlass;
}

void Warrior::setDragonGlass(bool ans){
    dragonGlass = ans;
}

int Warrior::getRow(){
    return row;
}
    
void Warrior::setRow(int num){
    row = num;
}

int Warrior::getColumn(){
    return column;
}
void Warrior::setColumn(int num){
    column = num;
}

string Warrior::getLeader(){
    return leader;
}

void Warrior::setLeader(string newLeader){
    leader = newLeader;
}

void Warrior::printStat(){
    cout << "Name: " << name << endl;
    cout << "Strength: " << strength << endl;
    cout << "Loyalty: " << loyalty << endl;
    cout << "Morale: " << morale << endl;
    cout << "Freedom: " << freedom << endl;
    cout << "Ship: " << ship << endl;
    cout << "DragonGlass: " << dragonGlass << endl;
    cout << "Row , Column: " << row << " , " << column << endl;
}
