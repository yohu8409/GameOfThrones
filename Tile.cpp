// CS1300 Spring 2019
// Author: YongQi Yu
// Recitation: 207 – Shipra Behera
// Cloud9 Workspace Editor Link: https://ide.c9.io/yohu8409/csci-1300_recitation
// Project 3 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Tile.h"
using namespace std;

Tile::Tile(){
    owner = "NONE";
    name = "NULL";
    place = '-';
    money = 0;
    army = 0;
    points = 0;
    dragonGlass = false;
}

Tile::Tile(string newOwner, string newName, char newPlace ,int newMoney, int newArmy, int newPoints , bool newDragonGlass){
    owner = newOwner;
    name = newName;
    place = newPlace;
    money = newMoney;
    army = newArmy;
    points = newPoints;
    dragonGlass = newDragonGlass;
}

string Tile::getOwner(){
    return owner;
}

void Tile::setOwner(string newOwner){
    owner = newOwner;
}

char Tile::getPlace(){
    return place;
}

void Tile::setPlace(char newLetter){
    place = newLetter;
}

string Tile::getName(){
    return name;
}

void Tile::setName(string newName){
    name = newName;
}

int Tile::getMoney(){
    return money;
}

void Tile::setMoney(int newMoney){
    money = newMoney;
}

int Tile::getArmy(){
    return army;
}

void Tile::setArmy(int newArmy){
    army = newArmy;
}

int Tile::getPoints(){
    return points;
}

void Tile::setPoints(int newPoints){
    points = newPoints;
}

bool Tile::getDragonGlass(){
    return dragonGlass;
}

void Tile::setDragonGlass(bool newDragonGlass){
    dragonGlass = newDragonGlass;
}

void Tile::printStat(){
    cout << "Owner: " << owner << endl;
    cout << "Name: " << name << endl;
    cout << "Place: " << place << endl;
    cout << "Money: " << money << endl;
    cout << "Army: " << army << endl;
    cout << "Points: " << points << endl;
    cout << "Dragon Glass: " << dragonGlass << endl;
    cout << endl << endl;
}

int Tile::getRow(){
    return row;
}

int Tile::getColumn(){
    return column;
}

void Tile::setColumn(int num){
    column = num + 1;
}

void Tile::setRow(int num){
    row = num + 1;
}