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
#include "Map.h"
using namespace std;


int split(string s , char n, string my_array[], int num){
    char w; // declare as w as a char
    int counter = 1; // set counter as int and set it equal to 1
    int y = s.length() - 1; // set y equal to the length of the string minus 1
    int i = 0; // delcare int i and put it equal to 0
    string empty = ""; // creates a string where the char can go into in order to store into the array
    if (s.empty()){// if the string is empty, run code
        counter = 0; // set counter as 0
        }
    if (s[0] == n){ // if the first char is the delimiter, run code
            i = 1; // set i as 1 so it skips the first char
        }
    if (s[y] == n){ // if the last char is the delimiter, run code
        y = y - 1;  // minus 1 from the length of string so it doesn't run the last char
    }
    while ( i <= y ){ // while i is less or equal to y, run code
        w = s[i];// set the individual letters to w
        if (w != n){ // if w is not equal to the delimiter, run code
            empty += w; // adds w to the empty string
        }
        else{
            my_array[counter - 1] = empty; // stores the string to the array
            empty = ""; // make the string empty again for the next space in the array
            counter++; // add 1 to the counter
            if (s[i + 1] == n){ // if the delimiter appears twice in a row, ignore
                i = i + 1;
            }
        }
        i = i + 1; // add 1 to i
    
    }
    my_array[counter - 1] = empty; // add the last string to the array
    
    if (counter > num){ // if the array is smaller than expected, return -1
        counter =  -1;
    }
    
    return counter; // returns counter as the number of times the string has split
     
} //splits the string into sub strings

Tile readCities(string fileName , char c){
    Tile t1 = Tile();
    ifstream myfile;
    myfile.open(fileName);
    string line = "";
    string test;
    string storage[5];
    int k = 0;
    if (myfile.is_open()){
        while(getline(myfile, line)){
            split(line , ',' , storage , 5);
            test = storage[0];
            if(test[0] == c){
                t1.setPlace(test[0]);
                t1.setName(storage[1]);
                t1.setMoney(stoi(storage[2]));
                t1.setArmy(stoi(storage[3]));
                t1.setPoints(stoi(storage[4]));
            }
         k++;   
        }
        return t1;
    }
} //reads the cities file and returns a Tile with all the properties of the city


Map::Map(){
    for (int i = 0; i < 25; i++){
        for (int k = 0; k < 16; k++){
            map[i][k] = Tile();
        }
    }
} // constructor

void Map::readMap(string fileName){    //stores all the characters in the map into the array of the map
    ifstream myfile;
    myfile.open(fileName);
    string line = "";
    string storage[16];
    int row = 0;
    if (myfile.is_open()){
        while(getline(myfile, line)){
            split(line , ',' , storage , 16);
            
            for (int i = 0; i < 16; i++){
                string test = storage[i];
                switch(test[0]){
                    case 'w':
                        //sets the stats associating with the water into the tiles class
                        map[row][i].setPlace('w'); 
                        map[row][i].setPoints(1); 
                        map[row][i].setMoney(10);
                        map[row][i].setRow(row);
                        map[row][i].setColumn(i);
                        break;
                    case 'p':
                        //sets the stats associating with the land tiles
                        map[row][i].setPlace('p'); 
                        map[row][i].setPoints(2);
                        map[row][i].setMoney(20);
                        map[row][i].setArmy(10);
                        map[row][i].setRow(row);
                        map[row][i].setColumn(i);
                        break;
                    default:
                        //sets the cities assocating with the City tiles
                        map[row][i] = readCities("cities.txt" , test[0]);
                        map[row][i].setRow(row);
                        map[row][i].setColumn(i);
                        break;
                }
            }
            row++;
        }
        
    }
} //reads the map and store all the values of it into the function

void Map::printTiles(){
    for (int i = 0; i < 25; i++){
        for (int k = 0; k < 16; k++){
            cout << map[i][k].getPlace() << " ";
        }
        cout << endl;
    }
} // tests to see if the tiles are being stored properly

void Map::readWarriors(string fileName){
    //reads the warrior file and puts all the values in their respective variables
    //also puts the unowned warriors randomly on the map
    ifstream myfile;
    myfile.open(fileName);
    string line = "";
    string storage[7];
    int i = 0;
    if (myfile.is_open()){
        while(getline(myfile, line)){
            split(line , ',' , storage , 7);
                allFighters[i].setName(storage[0]);
                allFighters[i].setStrength(stoi(storage[1]));
                allFighters[i].setLoyalty(stoi(storage[2]));
                allFighters[i].setMorale(stoi(storage[3]));
                
                if(storage[4] == "yes"){
                    allFighters[i].setFreedom(true); 
                }
                else{
                    allFighters[i].setFreedom(false);
                }
                
                
                if(storage[5] == "yes"){
                    allFighters[i].setShip(true); 
                }
                else{
                    allFighters[i].setShip(false);
                }
                
                
                if(storage[6] == "yes"){
                    allFighters[i].setDragonGlass(true); 
                }
                else{
                    allFighters[i].setDragonGlass(false);
                }
                
                i++;
            
        }
            
    }
    
} //reads the Warrior file and stores all of the stat in to the array created in the map header

void Map::printWarriors(){
    for (int i = 0; i < 14; i++){
        cout << "Warrior: " << allFighters[i].getName() << endl;
        cout << "Strength: " << allFighters[i].getStrength() << endl;
        cout << "Loyalty: " << allFighters[i].getLoyalty() << endl;
        cout << "Morale: " << allFighters[i].getMorale() << endl;
        cout << "Freedom: " << allFighters[i].getFreedom() << endl;
        cout << "Ship: " << allFighters[i].getShip() << endl;
        cout << "Dragon Glass: " << allFighters[i].getDragonGlass() << endl;
        cout << endl << endl;
    }
} // tests to print if all the Warriors are properly being stored through the readWarriors function

void Map::readHeros(string fileName){
    ifstream myfile;
    myfile.open(fileName);
    string line = "";
    string storage[11];
    int i = 0;
    if (myfile.is_open()){
        while(getline(myfile, line)){
            split(line , ',' , storage , 11);
                allHeros[i].setName(storage[0]);
                allHeros[i].setMoney(stoi(storage[1]));
                allHeros[i].setInfluence(stoi(storage[2]));
                allHeros[i].setArmy(stoi(storage[3]));
                allHeros[i].setRow(stoi(storage[8]));
                allHeros[i].setColumn(stoi(storage[9]));

                if(storage[10] == "yes"){
                    allHeros[i].setShip(true); 
                }
                else{
                    allHeros[i].setShip(false);
                }
                
                for (int k = 4; k < 8; k++){
                    if(storage[k] != "NULL"){
                        for (int p = 0; p < 14; p++){
                            if(storage[k] == allFighters[p].getName()){
                                allHeros[i].setWarrior((k - 4) , allFighters[p]);
                            }
                        }
                    }
                    else{
                        allHeros[i].setWarriorName((k - 4) , "NULL");
                    }
                }
                
                
                i++;
            
        }
            
    }
} //reads the heros file and stores all of the stat in to the array created in the map header

void Map::printHeroStat(){
    for(int i = 0; i < 6; i++){
        cout << "Hero: " << allHeros[i].getName() << endl;
        cout << "Money: " << allHeros[i].getMoney() << endl;
        cout << "Influence: " << allHeros[i].getInfluence() << endl;
        cout << "Army: " << allHeros[i].getArmy() << endl;
        cout << "Warrior 1: " << allHeros[i].getWarriorName(0) << endl;
        cout << "Warrior 2: " << allHeros[i].getWarriorName(1) << endl;
        cout << "Warrior 3: " << allHeros[i].getWarriorName(2) << endl;
        cout << "Warrior 4: " << allHeros[i].getWarriorName(3) << endl;
        cout << "Row: " << allHeros[i].getRow() << endl;
        cout << "Column: " << allHeros[i].getColumn() << endl;
        cout << "Ship: " << allHeros[i].getShip() << endl;
        cout << endl << endl;
    }
} // checks to see if all the heros are properly being stored through the readHeros function

Hero Map::getHero(int idx){
    return allHeros[idx];
}

void Map::setHero(int idx , Hero H){
    allHeros[idx] = H;
}

Tile Map::getTile(int row , int column){
    return map[row][column];
}

void Map::setTile(Tile t1 , int row , int column){
    map[row][column] = t1;
}

Warrior Map::getWarrior(int idx){
    return allFighters[idx];
}

void Map::setWarrior(int idx , Warrior w1){
    allFighters[idx] = w1;
}