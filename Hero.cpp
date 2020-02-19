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
#include "Hero.h"

Hero::Hero(){
    name = "";
    for (int i = 0; i < 4; i++){
        fighters[i] = Warrior();
    }
    money = 0;
    influence = 0;
    army = 0;
    points = 0;
    row = 0;
    column = 0;
    ship = false;
}

Hero::Hero(string newName, int newMoney , int newInfluence , int newArmy , int newPoints , Warrior newFighters[4] , int newRow , int newColumn , bool newShip){
    name = newName;
    money = newMoney;
    influence = newInfluence;
    army = newArmy;
    points = newPoints;
    row = newRow;
    column = newColumn;
    ship = newShip;
    for (int i = 0; i < 4; i++){
        fighters[i] = newFighters[i];
    }
    
}

bool Hero::getLife(){
    return life;
}

void Hero::setLife(bool newLife){
    life = newLife;
}


string Hero::getName(){
    return name;
}

void Hero::setName(string newName){
    name = newName;
}

int Hero::getMoney(){
    return money;
}

void Hero::setMoney(int num){
    money = num;
}

int Hero::getInfluence(){
    return influence;
}

void Hero::setInfluence(int num){
    influence = num;
}

int Hero::getArmy(){
    return army;
}

void Hero::setArmy(int num){
    army = num;
}

int Hero::getPoints(){
    return points;
}

void Hero::setPoints(int num){
    points = num;
}

string Hero::getWarriorName(int idx){
    if (idx >= 0 && idx < 5){
        return fighters[idx].getName();
    }
    else{
        return "ERROR";
    }
}

void Hero::setWarriorName(int idx , string newName){
    if (idx >= 0 && idx < 5){
        fighters[idx].setName(newName);
    }
}

Warrior Hero::getWarrior(int idx){
    if (idx >= 0 && idx <= 5){
        return fighters[idx];
    }
}

void Hero::setWarrior(int idx , Warrior newWarrior){
    if (idx >= 0 && idx <= 5){
        fighters[idx] = newWarrior;
    }
}

int Hero::getRow(){
    return row;
}

void Hero::setRow(int num){
    row = num;
}

int Hero::getColumn(){
    return column;
}

void Hero::setColumn(int num){
    column = num;
}

bool Hero::getShip(){
    return ship;
}

void Hero::setShip(bool newShip){
    ship = newShip;
}

bool Hero::warriorShip(){
    for (int i = 0; i < 4; i++){
        if(fighters[i].getShip() == true){
            return true;
        }
    }
    return false;
}

void Hero::printStat(){
        cout << "Name: " << name << endl;
        cout << "Money: " << money << endl;
        cout << "Influence: " << influence << endl;
        cout << "Army: " << army << endl;
        cout << "Points: " << points << endl;
        cout << "Warrior 1: " << fighters[0].getName() << endl;
        cout << "Warrior 2: " << fighters[1].getName() << endl;
        cout << "Warrior 3: " << fighters[2].getName() << endl;
        cout << "Warrior 4: " << fighters[3].getName() << endl;;
        cout << "Row: " << row << endl;
        cout << "Column: " << column << endl;
        cout << "Ship: " << ship << endl;
}

void Hero::addOwnerShip(Tile place){
    ownedPlaces.push_back(place);
}

bool Hero::checkOwnerShip(Tile place){
    for (int i = 0; i < ownedPlaces.size(); i++){
        if(ownedPlaces[i].getRow() == place.getRow() && ownedPlaces[i].getColumn() == place.getColumn()){
            return false;
        }
    }
    return true;
}

void Hero::eraseOwnerShip(Tile place){
    for (int i = 0; i < ownedPlaces.size(); i++){
        if(ownedPlaces[i].getRow() == place.getRow() && ownedPlaces[i].getColumn() == place.getColumn()){
            points = points - ownedPlaces[i].getPoints();
            ownedPlaces.erase(ownedPlaces.begin() + i);
        }
    }
}

Tile Hero::getOwnedPlaces(int idx){
    return ownedPlaces[idx];
}

int Hero::getSizeOfOwnedPlaces(){
    return ownedPlaces.size();
}

int Hero::getWarriorSize(){
    int num = 0;
    for (int p = 0; p < 4; p++){
        if(fighters[p].getName() != "NULL"){
            num++;
        }
    }
    return num;
}

void Hero::addCity(Tile place){
    firstCities.push_back(place);
}

bool Hero::checkFirstCity(Tile place){
    for (int i = 0; i < firstCities.size(); i++){
        if(firstCities[i].getRow() == place.getRow() && firstCities[i].getColumn() == place.getColumn()){
            return false;
        }
    }
    return true;
}

int Hero::getSizeOfFirstCities(){
    return firstCities.size();
}