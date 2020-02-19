#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <string>
#include <ctime>
#include <vector>
#include "Map.cpp"
using namespace std;

Hero updateHero(Hero myHero , Tile place){
    int num = 0;
    myHero.addOwnerShip(place);
    num = myHero.getMoney() + place.getMoney();
    myHero.setMoney(num);
    num = myHero.getArmy() + place.getArmy();
    myHero.setArmy(num);
    num = myHero.getPoints() + place.getPoints();
    myHero.setPoints(num);
    return myHero;
} // updates the Hero's stats based on what Tile they land on

void displayMap(int row , int column){
    Map m1;
    char miniMap[7][7];
    int x = column - 1;
    int y = row - 1;
    m1.readMap("map.txt");
    
    for(int i = 0; i < 7; i++){  //sets all the spaces in the character array as an underline
        for(int k = 0; k < 7; k++){
            miniMap[i][k] = '_';
        }
    }
    
    for(int i = (y - 3); i <= (y + 3); i++){ //sets the characters from the GOT map into the array
            for(int k = (x - 3); k <= (x + 3); k++){
                    if(i < 0 || i >= 25 || k < 0 || k >= 16){ // skips over the spaces that does not exist
                        
                    }
                    else{
                        Tile t1 = m1.getTile(i , k); 
                        switch(t1.getPlace()){
                            case 'w':
                                miniMap[i - (y - 3)][k - (x - 3)] = '~';
                                break;
                            case 'p':
                                miniMap[i - (y - 3)][k - (x - 3)] = '*';
                                break;
                            default:
                                miniMap[i - (y - 3)][k - (x - 3)] = t1.getPlace();
                                break;
                        }
                        
                    }
            }
        
    }
    
    cout << endl << endl;
    
    for(int i = 0; i < 7; i++){ //prints the mini map that the player will see while bracketing the space they're on
        for(int k = 0; k < 7; k++){
            if(i == 3 && k == 3){
                cout << " [" << miniMap[i][k] << "] ";
            }
            else{
            cout << miniMap[i][k];
                if(i != 3 || k != 2){
                      cout << "  ";
                  }
                
            }
        }
        cout << endl;
    }
} // displays the map based on your row and column

void displayDirections(){
    cout << "Which direction do you want to travel? (Answer in the number associated with the choices)" << endl;
    cout << "1. North" << endl;
    cout << "2. East" << endl;
    cout << "3. South" << endl;
    cout << "4. West" << endl;
} //displays the choices for north, south, west, and east

void displayEncounterChoices(string name){
    cout << "You have encountered another Hero, " << name << ", what would you like to do?" << endl;
    cout << "1) Speech" << endl;
    cout << "2) Buy them outright" << endl;
    cout << "3) Battle" << endl;
}

void displayTravelChoices(){
    cout << "What would you like to do? (Answer in the number associated with the choices)" << endl;
    cout << "1. Travel (move in any direction 1 space)" << endl;
    cout << "2. Rest (remain where you are and all warrior in party will increase strength by 1)" << endl;
    cout << "3. Consult with the Gods (remain where you are and all warrior in party will increase their morale by 1)" << endl;
} //displays the choices of travel , rest , or talk to gods

void displayHeros(){
    cout << "Please choose from the following heroes: (Type in the number of the hero)" << endl;
    cout << "1. Cersei Lannister" << endl;
    cout << "2. Stannis Baratheon" << endl;
    cout << "3. Jon Snow" << endl;
    cout << "4. Sansa Stark" << endl;
    cout << "5. Euron Greyjoy" << endl;
    cout << "6. Daenerys Targaryen" << endl;
} // displays all the heros you can choose from

int randDirection(){
    return (rand() % 4) + 1; //returns a random number between 1 and 4
} //returns a random direction that the NPC and free warriors will go

int randWarrior(int num){
    return (rand() % num); //returns a random number between 1 and 4
}

int randRow() // returns a random row
{   
	return rand() % 25; // returns a random number between 0 and 24
}

int randColumn() //returns a random column
{   
	return rand() % 16; // returns a random number between 0 and 15
}

bool generateProbility(double x)
{
    return (x < (rand() % 100)) ? false : true;
}

bool randomEvent()
{
    return (30 < (rand() % 100)) ? false : true;
}

bool game(int num , string player){
    srand ( time(NULL) );
    Hero myHero = Hero();
    Tile place = Tile();
    int turn = 0;
    Map gameData;
    gameData.readWarriors("warriors.txt");
    gameData.readHeros("heros.txt");
    gameData.readMap("map.txt");
    double probability;
    vector<Warrior> warriors;
    vector<Hero> NPC;
    Warrior store;
    bool result;
    
    //sets the dragon glass in 5 random land tiles
    for(int i = 0; i < 5; i++){
        int randomRow = 0; // this row and column is a water tile
        int randomColumn = 16;
        
        while(gameData.getTile(randomRow , randomColumn).getPlace() != 'p'){ // since I set it as the water tile first, it will run then use random numbers
            randomRow = randRow();
            randomColumn = randColumn();
        }
        Tile t1 = gameData.getTile(randomRow , randomColumn);
        t1.setDragonGlass(true);
        gameData.setTile(t1 , randomRow, randomColumn);
    }
    
    if(num == 7){
        //selects the stats of the hero
        int choice;
        myHero.setName("Self");
        cout << "Your Grace " << player << ", you have chosen to go on this journey alone." << endl;
        cout << "Please provide starting values for your adventure." << endl;
        
        cout << "How much points would you like for your money (Enter from 0 to 10000): " << endl;
        cin >> choice;
        while(choice > 10000 || choice < 0){
            cout << "ERROR: PLEASE CHOOSE FROM 0 TO 10000" << endl;
            cin >> choice;
                        
        }
        
        myHero.setMoney(choice);
        
                
        cout << "How much points would you like for your influence (Enter from 0 to 10000): " << endl;
        cin >> choice;
            while(choice > 10000 || choice < 0){
                cout << "ERROR: PLEASE CHOOSE FROM 0 TO 10000" << endl;
                cin >> choice;
            }
        
        myHero.setInfluence(choice);
                    
                    
        cout << "How large would you like for your army size (Enter from 0 to 10000): " << endl;
        cin >> choice;
            while(choice > 10000 || choice < 0){
                cout << "ERROR: PLEASE CHOOSE FROM 0 TO 10000" << endl;
                cin >> choice;
            }
        
        myHero.setArmy(choice);
                   
            
        cout << "Which row would you like to begin (1-25):" << endl;
        cin >> choice;
            while(choice > 25 || choice < 1){
                cout << "ERROR: PLEASE CHOOSE FROM 1 TO 25" << endl;
                cin >> choice;
            }
            
        myHero.setRow(choice);    
            
        cout << "Which column would you like to begin (1-16):" << endl;
        cin >> choice;
            while(choice > 16 || choice < 1){
                cout << "ERROR: PLEASE CHOOSE FROM 1 TO 16" << endl;
                cin >> choice;
            }
        
        
        
        myHero.setColumn(choice);
        
        place = gameData.getTile(myHero.getRow() - 1 , myHero.getColumn() - 1);
        
        if(place.getPlace() == 'w'){
            myHero.setShip(true);
        }
    } // lets the player create his own character
    else{
    myHero = gameData.getHero(num - 1);
        
    } // sets the chosen hero as the hero that the player controls
    
    
    
    //sets the heros for the NPC in the vector
    for (int i = 0; i < 6; i++){
            
            if(i != (num - 1)){
              
                NPC.push_back(gameData.getHero(i));
                
            }
            
        } 
    
    place = gameData.getTile(myHero.getRow() - 1 , myHero.getColumn() - 1); //sets the place into a tile

    //Updates the heros based on where they start
    myHero = updateHero(myHero , place);

    
    //Updates the heros based on where they start
    for (int i = 0; i < NPC.size(); i++){
        
        place = gameData.getTile(NPC[i].getRow() - 1 , NPC[i].getColumn() - 1);
        NPC[i] =  updateHero(NPC[i] , place);
    }
    
    
    //sets all the warriors who are free into the vector
    for (int i = 0; i < 14; i++){
        Warrior w1 = gameData.getWarrior(i);
        if(w1.getFreedom() == true){
            warriors.push_back(w1);
        }
    } 
    
    
    
    //sets the free warriors in random places
    for (int i = 0; i < 7; i++){
        if(warriors[i].getShip() == false){
        
            int randomRow = 0;
            int randomColumn = 16;
            
                while(gameData.getTile(randomRow , randomColumn).getPlace() != 'p'){
                    randomRow = randRow();
                    randomColumn = randColumn();
                    for (int k = 0; k < NPC.size(); k++){
                        if(( randomRow == NPC[k].getRow() && randomColumn == NPC[k].getColumn() ) || (randomRow == myHero.getRow() && randomColumn == myHero.getColumn())){
                            randomRow = 0;
                            randomColumn = 16;
                        }
                    }
                }
            
            warriors[i].setRow(randomRow + 1);
            warriors[i].setColumn(randomColumn + 1);
        }
        else{
            int randomRow = 0;
            int randomColumn = 0;
            
                while(gameData.getTile(randomRow , randomColumn).getPlace() != 'w'){
                    randomRow = randRow();
                    randomColumn = randColumn();
                    for (int k = 0; k < NPC.size(); k++){
                        if(( randomRow == NPC[k].getRow() && randomColumn == NPC[k].getColumn() ) || (randomRow == myHero.getRow() && randomColumn == myHero.getColumn())){
                            randomRow = 0;
                            randomColumn = 0;
                        }
                    }
                }
                
                warriors[i].setRow(randomRow);
                warriors[i].setColumn(randomColumn);
        }
    }
    
    bool game = true;
    bool whiteWalkers = false;
while(game == true && whiteWalkers == false){
    displayMap(myHero.getRow() , myHero.getColumn()); // display map of where the hero is
    int choice = 0;
    int loop = 0;
    bool check = false;
    bool trial = false;
    displayTravelChoices();
    
    while(trial == false){
    
    cin >> choice;
    
        switch(choice){
            case 1:
                
                displayDirections();
                while(check == false){
                    cin >> loop;
                    switch(loop){
                        case 1:
                            if((myHero.getRow() - 1) <= 0 || (myHero.getRow() - 1) >= 26){
                                cout << "Cannot move out of the map, choose again" << endl;
                                
                            }
                            else{
                                place = gameData.getTile(myHero.getRow() - 2 , myHero.getColumn() - 1);
                                if(place.getPlace() == 'w'){
                                    if(myHero.getShip() == true || myHero.warriorShip() == true){
                                        myHero.setRow(myHero.getRow() - 1);
                                        check = true;
                                    }
                                    else{
                                        cout << "Do not have ship to move to water tile. Choose a different Direction" << endl;
                                        
                                    }
                                }
                                else{
                                    myHero.setRow(myHero.getRow() - 1);
                                    check = true;
                                }
                            }
                            break;
                        case 2:
                            if((myHero.getColumn() + 1) <= 0 || (myHero.getColumn() + 1) >= 17){
                                cout << "Cannot move out of the map, choose again" << endl;
                            }
                            else{
                                place = gameData.getTile(myHero.getRow() - 1 , myHero.getColumn());
                                if(place.getPlace() == 'w'){
                                    if(myHero.getShip() == true || myHero.warriorShip() == true){
                                        myHero.setColumn(myHero.getColumn() + 1);
                                        check = true;
                                    }
                                    else{
                                        cout << "Do not have ship to move to water tile. Choose a different Direction" << endl;
                                    }
                                }
                                else{
                                    myHero.setColumn(myHero.getColumn() + 1);
                                    check = true;
                                }
                                
                            }
                            break;
                        case 3:
                            if((myHero.getRow() + 1) <= 0 || (myHero.getRow() + 1) >= 26){
                                cout << "Cannot move out of the map, choose again" << endl;
                               
                            }
                            else{
                                place = gameData.getTile(myHero.getRow(), myHero.getColumn() - 1);
                                if(place.getPlace() == 'w'){
                                    if(myHero.getShip() == true || myHero.warriorShip() == true){
                                        myHero.setRow(myHero.getRow() + 1);
                                        check = true;
                                    }
                                    else{
                                        cout << "Do not have ship to move to water tile. Choose a different Direction" << endl;
            
                                    }
                                }
                                else{
                                    myHero.setRow(myHero.getRow() + 1);
                                    check = true;
                                }
                                
                            }
                            break;
                        case 4:
                            if((myHero.getColumn() - 1) <= 0 || (myHero.getColumn() - 1) >= 17){
                                cout << "Cannot move out of the map, choose again" << endl;
                               
                            }
                            else{
                                place = gameData.getTile(myHero.getRow() - 1 , myHero.getColumn() - 2);
                                if(place.getPlace() == 'w'){
                                    if(myHero.getShip() == true || myHero.warriorShip() == true){
                                        myHero.setColumn(myHero.getColumn() - 1);
                                        check = true;
                                    }
                                    else{
                                        cout << "Do not have ship to move to water tile. Choose a different Direction" << endl;
                                       
                                    }
                                }
                                else{
                                    myHero.setColumn(myHero.getColumn() - 1);
                                    check = true;
                                }
                            }
                            break;
                        default:
                            cout << "ERROR, TRY AGAIN" << endl;
                            check = false;
                            break;
                    } // moves the hero to which ever direction they want while checking if they have ship and within borders
                }
                
                trial = true;
                break;
            case 2:
                for (int i = 0; i < 4; i++){
                    Warrior w1 = myHero.getWarrior(i);
                    if(w1.getName() != "NULL"){
                        w1.setStrength(w1.getStrength() + 1);
                        myHero.setWarrior(i , w1);
                    }
                }
                trial = true;
                break;
            case 3:
                for (int i = 0; i < 4; i++){
                    Warrior w1 = myHero.getWarrior(i);
                    if(w1.getName() != "NULL"){
                        w1.setMorale(w1.getMorale() + 1);
                        myHero.setWarrior(i , w1);
                    }
                }
                trial = true;
                break;
            default:
                cout << "ERROR, TRY AGAIN" << endl;
                trial = false;
                break;
        } //gives the choice of whether to move or rest or consult
        
    } //Gives the user the choice to move, rest , or talk to god

    
    for (int i = 0; i < NPC.size(); i++){
        bool test = false;
        bool test1 = true;
        Hero tHero = NPC[i];
            while(test == false){
                choice = randDirection();
                    switch(choice){
                        case 1:
                            if((tHero.getRow() - 1) <= 0 || (tHero.getRow() - 1) >= 26){
                                test1 = false;
                            }
                            else{
                                place = gameData.getTile(tHero.getRow() - 2 , tHero.getColumn() - 1);
                                if(place.getPlace() == 'w'){
                                    if(tHero.getShip() == true || tHero.warriorShip() == true){
                                        tHero.setRow(tHero.getRow() - 1);
                                        test = true;
                                    }
                                    else{
                                        test1 = false;
                                    }
                                }
                                else{
                                    tHero.setRow(tHero.getRow() - 1);
                                    test = true;
                                }
                            }
                            break;
                        case 2:
                            if((tHero.getColumn() + 1) <= 0 || (tHero.getColumn() + 1) >= 17){
                                test1 = false;
                            }
                            else{
                                place = gameData.getTile(tHero.getRow() - 1 , tHero.getColumn());
                                if(place.getPlace() == 'w'){
                                    if(tHero.getShip() == true || tHero.warriorShip() == true){
                                        tHero.setColumn(tHero.getColumn() + 1);
                                        test = true;
                                    }
                                    else{
                                        test1 = false;
                                    }
                                }
                                else{
                                    tHero.setColumn(tHero.getColumn() + 1);
                                    test = true;
                                }
                                
                            }
                            break;
                        case 3:
                            if((tHero.getRow() + 1) <= 0 || (tHero.getRow() + 1) >= 26){
                                 test1 = false;
                            }
                            else{
                                place = gameData.getTile(tHero.getRow(), tHero.getColumn() - 1);
                                if(place.getPlace() == 'w'){
                                    if(tHero.getShip() == true || tHero.warriorShip() == true){
                                        tHero.setRow(tHero.getRow() + 1);
                                        test = true;
                                    }
                                    else{
                                        test1 = false;
                                    }
                                }
                                else{
                                    tHero.setRow(tHero.getRow() + 1);
                                    test = true;
                                }
                                
                            }
                            break;
                        case 4:
                            if((tHero.getColumn() - 1) <= 0 || (tHero.getColumn() - 1) >= 17){
                                test1 = false;
                            }
                            else{
                                place = gameData.getTile(tHero.getRow() - 1 , tHero.getColumn() - 2);
                                if(place.getPlace() == 'w'){
                                    if(tHero.getShip() == true || tHero.warriorShip() == true){
                                        tHero.setColumn(tHero.getColumn() - 1);
                                        test = true;
                                    }
                                    else{
                                        test1 = false;
                                    }
                                }
                                else{
                                    tHero.setColumn(tHero.getColumn() - 1);
                                    test = true;
                                }
                            }
                            break;
                        default:
                            test1 = false;
                            break;
                    } // moves the hero to which ever direction they want while checking if they have ship and within borders
                
            
            }
        NPC[i] = tHero;
    } //sets the NPCs to a random direction
    
    
    
    for (int i = 0; i < warriors.size(); i++){
        bool check = false;
        Warrior tWarriors = warriors[i];
            while(check = false){
                choice = randDirection();
                    switch(choice){
                        case 1:
                            if((tWarriors.getRow() - 1) <= 0 || (tWarriors.getRow() - 1) >= 26){
                                check = false;
                            }
                            else{
                                place = gameData.getTile(tWarriors.getRow() - 2 , tWarriors.getColumn() - 1);
                                if(place.getPlace() == 'w'){
                                    if(tWarriors.getShip() == true){
                                        tWarriors.setRow(tWarriors.getRow() - 1);
                                        check = true;
                                    }
                                    else{
                                        check = false;
                                    }
                                }
                                else{
                                    tWarriors.setRow(tWarriors.getRow() - 1);
                                    check = true;
                                }
                            }
                            break;
                        case 2:
                            if((tWarriors.getColumn() + 1) <= 0 || (tWarriors.getColumn() + 1) >= 17){
                                check = false;
                            }
                            else{
                                place = gameData.getTile(tWarriors.getRow() - 1 , tWarriors.getColumn());
                                if(place.getPlace() == 'w'){
                                    if(tWarriors.getShip() == true){
                                        tWarriors.setColumn(tWarriors.getColumn() + 1);
                                        check = true;
                                    }
                                    else{
                                        check = false;
                                    }
                                }
                                else{
                                    tWarriors.setColumn(tWarriors.getColumn() + 1);
                                    check = true;
                                }
                                
                            }
                            break;
                        case 3:
                            if((tWarriors.getRow() + 1) <= 0 || (tWarriors.getRow() + 1) >= 26){
                                   check = false;
                            }
                            else{
                                place = gameData.getTile(tWarriors.getRow(), tWarriors.getColumn() - 1);
                                if(place.getPlace() == 'w'){
                                    if(tWarriors.getShip() == true){
                                        tWarriors.setRow(tWarriors.getRow() + 1);
                                        check = true;
                                    }
                                    else{
                                       check = false;
                                    }
                                }
                                else{
                                    tWarriors.setRow(tWarriors.getRow() + 1);
                                    check = true;
                                }
                                
                            }
                            break;
                        case 4:
                            if((tWarriors.getColumn() - 1) <= 0 || (tWarriors.getColumn() - 1) >= 17){
                               check = false;
                            }
                            else{
                                place = gameData.getTile(tWarriors.getRow() - 1 , tWarriors.getColumn() - 2);
                                if(place.getPlace() == 'w'){
                                    if(tWarriors.getShip() == true){
                                        tWarriors.setColumn(tWarriors.getColumn() - 1);
                                        check = true;
                                    }
                                    else{
                                        check = false;
                                    }
                                }
                                else{
                                    tWarriors.setColumn(tWarriors.getColumn() - 1);
                                    check = true;
                                }
                            }
                            break;
                        default:
                            check = false;
                            break;
                    } // moves the hero to which ever direction they want while checking if they have ship and within borders
                
            
            }
        warriors[i] = tWarriors;
    } //sets the warriors to a random direction
    
    for (int i = 0; i < NPC.size(); i++){
        if(abs(myHero.getRow() - NPC[i].getRow()) <= 2 && abs(myHero.getColumn() - NPC[i].getColumn()) <= 2){
            displayEncounterChoices(NPC[i].getName());
            vector<Warrior> soldiers;
            bool check = false;
            bool empty = false;
            bool empty1 = false;
            int power;
            int power1;
            cin >> choice;
            while(check == false){
                check = true;
                    switch(choice){
                        case 1:
                            probability = (1.0 - (NPC[i].getWarrior(0).getMorale() / 100.0)) * (myHero.getInfluence() / 1600.0);
                            if(probability < 0){
                                probability = 0;
                            }
                            probability = probability * 100;
                            if(generateProbility(probability)){
                                cout << NPC[i].getName() << " has retired" << endl;
                                myHero.setMoney(myHero.getMoney() + NPC[i].getMoney());
                                myHero.setInfluence(myHero.getInfluence() + NPC[i].getInfluence());
                                myHero.setArmy(myHero.getArmy() + NPC[i].getArmy());
                                myHero.setPoints(myHero.getPoints() + NPC[i].getPoints());
                                for (int k = 0; k < NPC[i].getSizeOfOwnedPlaces(); k++){
                                    myHero.addOwnerShip(NPC[i].getOwnedPlaces(k));
                                } //adds all the location of the places that the heros owned
                                for (int p = 0; p < 4; p++){
                                    if(NPC[i].getWarriorName(p) != "NULL"){
                                        soldiers.push_back(NPC[i].getWarrior(p));
                                    }
                                    if(myHero.getWarriorName(p) != "NULL"){
                                        soldiers.push_back(myHero.getWarrior(p));
                                    }
                                }
                                    if(soldiers.size() <= 4){
                                        if(soldiers.size() != 0){
                                            for (int t = 0; t < soldiers.size(); t++){
                                                myHero.setWarrior(t , soldiers[t]);
                                            }
                                        }
                                    } //sets the warriors of the loser into the winner
                                    else{
                                        for (int v = 0; v < 4; v++){
                                            for (int t = 0; t < soldiers.size(); t++){
                                                cout << "Your party is full. Choose who you want as your warriors" << endl;
                                                cout << t + 1 << ") " << soldiers[t].getName() << endl;
                                            }   
                                            cout << endl;
                                            cout << "Hero " << v + 1 << ":"; 
                                            cin >> loop;
                                            cout << endl;
                                            myHero.setWarrior(v , soldiers[loop - 1]);
                                            soldiers.erase(soldiers.begin() + (loop - 1));
                                        } //lets you choose what warriors to add in your team
                                        for (int v = 0; v < soldiers.size(); v++){
                                            soldiers[v].setRow(NPC[i].getRow());
                                            soldiers[v].setColumn(NPC[i].getColumn());
                                            warriors.push_back(soldiers[v]);
                                        }
                                    }
                                    
                                
                                
                                NPC.erase(NPC.begin() + i);
                                
                            } // adds all of the stats of the other opponent into your hero
                            else{
                                cout << "You lose but you escaped with half of your influence points" << endl;
                                myHero.setInfluence(myHero.getInfluence() / 2);
                                cout << "Influence: " << myHero.getInfluence() << endl;
                            }
                            break;
                        case 2:
                            probability = (1.0 - (NPC[i].getWarrior(0).getLoyalty() / 100.0)) * (myHero.getMoney() / 17800.0);
                            if(probability < 0){
                                probability = 0;
                            }
                            probability = probability * 100;
                            if(generateProbility(probability)){
                                cout << NPC[i].getName() << " has retired" << endl;
                                myHero.setMoney(myHero.getMoney() + NPC[i].getMoney());
                                myHero.setInfluence(myHero.getInfluence() + NPC[i].getInfluence());
                                myHero.setArmy(myHero.getArmy() + NPC[i].getArmy());
                                myHero.setPoints(myHero.getPoints() + NPC[i].getPoints());
                                for (int k = 0; k < NPC[i].getSizeOfOwnedPlaces(); k++){
                                    myHero.addOwnerShip(NPC[i].getOwnedPlaces(k));
                                } //adds all the location of the places that the heros owned
                                for (int p = 0; p < 4; p++){
                                    if(NPC[i].getWarriorName(p) != "NULL"){
                                        soldiers.push_back(NPC[i].getWarrior(p));
                                    }
                                    if(myHero.getWarriorName(p) != "NULL"){
                                        soldiers.push_back(myHero.getWarrior(p));
                                    }
                                }
                                
                                    if(soldiers.size() <= 4){
                                        if(soldiers.size() != 0){
                                            for (int t = 0; t < soldiers.size(); t++){
                                                myHero.setWarrior(t , soldiers[t]);
                                            }
                                        }
                                    } //sets the warriors of the loser into the winner
                                    else{
                                        for (int v = 0; v < 4; v++){
                                            for (int t = 0; t < soldiers.size(); t++){
                                            cout << "Your party is full. Choose who you want as your warriors" << endl;
                                            cout << t + 1 << ") " << soldiers[t].getName() << endl;
                                        }   
                                            cout << endl;
                                            cout << "Hero " << v + 1 << ":"; 
                                            cin >> loop;
                                            cout << endl;
                                            myHero.setWarrior(v , soldiers[loop - 1]);
                                            soldiers.erase(soldiers.begin() + (loop - 1));
                                        } //lets you choose what warriors to add in your team
                                        for (int v = 0; v < soldiers.size(); v++){
                                            soldiers[v].setRow(NPC[i].getRow());
                                            soldiers[v].setColumn(NPC[i].getColumn());
                                            warriors.push_back(soldiers[v]);
                                        }
                                    }
                                    
                                
                                
                                NPC.erase(NPC.begin() + i);
                                
                            } // adds all of the stats of the other opponent into your hero
                            else{
                                cout << "You lose but you escaped with half of your money" << endl;
                                myHero.setMoney(myHero.getMoney() / 2);
                                cout << "Money: " << myHero.getMoney() << endl;
                            }
                            break;
                        case 3:
                            if(NPC[i].getWarriorSize() == 0){
                                empty = true;
                            }
                            if(myHero.getWarriorSize() == 0){
                                empty1 = true;
                            }
                            if(empty == true && empty1 == false){
                                //you win
                                cout << NPC[i].getName() << " has retired" << endl;
                                myHero.setMoney(myHero.getMoney() + NPC[i].getMoney());
                                myHero.setInfluence(myHero.getInfluence() + NPC[i].getInfluence());
                                myHero.setArmy(myHero.getArmy() + NPC[i].getArmy());
                                myHero.setPoints(myHero.getPoints() + NPC[i].getPoints());
                                for (int k = 0; k < NPC[i].getSizeOfOwnedPlaces(); k++){
                                    myHero.addOwnerShip(NPC[i].getOwnedPlaces(k));
                                } //adds all the location of the places that the heros owned
                                for (int p = 0; p < 4; p++){
                                    if(NPC[i].getWarriorName(p) != "NULL"){
                                        soldiers.push_back(NPC[i].getWarrior(p));
                                    }
                                    if(myHero.getWarriorName(p) != "NULL"){
                                        soldiers.push_back(myHero.getWarrior(p));
                                    }
                                }
                                
                                    if(soldiers.size() <= 4){
                                        if(soldiers.size() != 0){
                                            for (int t = 0; t < soldiers.size(); t++){
                                                myHero.setWarrior(t , soldiers[t]);
                                            }
                                        }
                                    } //sets the warriors of the loser into the winner
                                    else{
                                        for (int v = 0; v < 4; v++){
                                            for (int t = 0; t < soldiers.size(); t++){
                                            cout << "Your party is full. Choose who you want as your warriors" << endl;
                                            cout << t + 1 << ") " << soldiers[t].getName() << endl;
                                            }   
                                            cout << endl;
                                            cout << "Hero " << v + 1 << ":"; 
                                            cin >> loop;
                                            cout << endl;
                                            myHero.setWarrior(v , soldiers[loop - 1]);
                                            soldiers.erase(soldiers.begin() + (loop - 1));
                                        } //lets you choose what warriors to add in your team
                                        for (int v = 0; v < soldiers.size(); v++){
                                            soldiers[v].setRow(NPC[i].getRow());
                                            soldiers[v].setColumn(NPC[i].getColumn());
                                            warriors.push_back(soldiers[v]);
                                        }
                                    }
                                    
                                
                                
                                NPC.erase(NPC.begin() + i);
                                
                            }
                            if(empty1 == true && empty == false){
                                //you lose
                                cout << "Game Over" << endl;
                                game = false;
                            }
                            if(empty1 == true && empty == true){
                                //tie, both escape nothing happens
                                cout << "Tied, Both escaped, nothing happened" << endl;
                            }
                            if(empty1 == false && empty == false){
                                cout << "Who would you like to fight in your stead?" << endl;
                                for (int q = 0; q < myHero.getWarriorSize(); q++){
                                    cout << q + 1 << ") " << myHero.getWarriorName(q) << endl;
                                }
                                cin >> loop;
                                
                                power = myHero.getArmy() * myHero.getWarrior(loop - 1).getStrength();
                                power1 = NPC[i].getArmy() * NPC[i].getWarrior(randWarrior(NPC[i].getWarriorSize())).getStrength();
                                
                                if(power >= power1){
                                        cout << NPC[i].getName() << " has retired" << endl;
                                        myHero.setMoney(myHero.getMoney() + NPC[i].getMoney());
                                        myHero.setInfluence(myHero.getInfluence() + NPC[i].getInfluence());
                                        myHero.setArmy(myHero.getArmy() + NPC[i].getArmy());
                                        myHero.setPoints(myHero.getPoints() + NPC[i].getPoints());
                                        for (int k = 0; k < NPC[i].getSizeOfOwnedPlaces(); k++){
                                            myHero.addOwnerShip(NPC[i].getOwnedPlaces(k));
                                        } //adds all the location of the places that the heros owned
                                        for (int p = 0; p < 4; p++){
                                            if(NPC[i].getWarriorName(p) != "NULL"){
                                                soldiers.push_back(NPC[i].getWarrior(p));
                                            }
                                            if(myHero.getWarriorName(p) != "NULL"){
                                                soldiers.push_back(myHero.getWarrior(p));
                                            }
                                        }
                                        
                                            if(soldiers.size() <= 4){
                                                if(soldiers.size() != 0){
                                                    for (int t = 0; t < soldiers.size(); t++){
                                                        myHero.setWarrior(t , soldiers[t]);
                                                    }
                                                }
                                            } //sets the warriors of the loser into the winner
                                            else{
                                                for (int v = 0; v < 4; v++){
                                                    for (int t = 0; t < soldiers.size(); t++){
                                                    cout << "Your party is full. Choose who you want as your warriors" << endl;
                                                    cout << t + 1 << ") " << soldiers[t].getName() << endl;
                                                }   
                                                    cout << endl;
                                                    cout << "Hero " << v + 1 << ":"; 
                                                    cin >> loop;
                                                    cout << endl;
                                                    myHero.setWarrior(v , soldiers[loop - 1]);
                                                    soldiers.erase(soldiers.begin() + (loop - 1));
                                                } //lets you choose what warriors to add in your team
                                                for (int v = 0; v < soldiers.size(); v++){
                                                    soldiers[v].setRow(NPC[i].getRow());
                                                    soldiers[v].setColumn(NPC[i].getColumn());
                                                    warriors.push_back(soldiers[v]);
                                                }
                                            }
                                            
                                        
                                        
                                        NPC.erase(NPC.begin() + i);
                                }
                                else{
                                    //you lose
                                    cout << "Game Over" << endl;
                                    game = false;
                                }
                            }
                            break;
                        default:
                            cout << "ERROR, choose again" << endl;
                            check = false;
                            break;
                    }   
                    
            }
        }
    } // checks and solves the encounters of the main hero
    
    if(game == false){
        break;
    }
    
    
    for (int i = 0; i < NPC.size(); i++){
        vector<Warrior> soldiers;
        int power , power1;
        bool empty = false;
        bool empty1 = false;
        for (int l = i; l < NPC.size(); l++){
            int p = l + 1;
            if(p == NPC.size()){
                break;
            }
            if(abs(NPC[i].getRow() - NPC[p].getRow()) <= 2 && abs(NPC[i].getColumn() - NPC[p].getColumn()) <= 2){
                if(NPC[i].getWarriorSize() == 0){
                    empty = true;
                }
                if(NPC[p].getWarriorSize() == 0){
                    empty1 = true;
                }
                if(empty == true && empty1 == false){
                    //you win
                    cout << NPC[p].getName() << " has retired" << endl;
                    NPC[i].setMoney(NPC[i].getMoney() + NPC[p].getMoney());
                    NPC[i].setInfluence(NPC[i].getInfluence() + NPC[p].getInfluence());
                    NPC[i].setArmy(NPC[i].getArmy() + NPC[p].getArmy());
                    NPC[i].setPoints(NPC[i].getPoints() + NPC[p].getPoints());
                    for (int k = 0; k < NPC[p].getSizeOfOwnedPlaces(); k++){
                        NPC[i].addOwnerShip(NPC[p].getOwnedPlaces(k));
                    } //adds all the location of the places that the heros owned
                    for (int t = 0; t < 4; t++){
                        if(NPC[p].getWarriorName(t) != "NULL"){
                            soldiers.push_back(NPC[p].getWarrior(t));
                        }
                        if(NPC[i].getWarriorName(t) != "NULL"){
                            soldiers.push_back(NPC[i].getWarrior(t));
                        }
                    }
                    
                        if(soldiers.size() <= 4){
                            if(soldiers.size() != 0){
                                for (int t = 0; t < soldiers.size(); t++){
                                    myHero.setWarrior(t , soldiers[t]);
                                }
                            }
                        } //sets the warriors of the loser into the winner
                        else{
                            for (int v = 0; v < 4; v++){
                                NPC[i].setWarrior(v , soldiers[v]);
                                soldiers.erase(soldiers.begin() + v);
                            } //lets you choose what warriors to add in your team
                            for (int v = 0; v < soldiers.size(); v++){
                                soldiers[v].setRow(NPC[p].getRow());
                                soldiers[v].setColumn(NPC[p].getColumn());
                                warriors.push_back(soldiers[v]);
                            }
                        }
                        
                    
                    
                    NPC.erase(NPC.begin() + p);
                    
                }
                if(empty1 == true && empty == false){
                    cout << NPC[i].getName() << " has retired" << endl;
                    NPC[p].setMoney(NPC[p].getMoney() + NPC[i].getMoney());
                    NPC[p].setInfluence(NPC[i].getInfluence() + NPC[p].getInfluence());
                    NPC[p].setArmy(NPC[i].getArmy() + NPC[p].getArmy());
                    NPC[p].setPoints(NPC[i].getPoints() + NPC[p].getPoints());
                    for (int k = 0; k < NPC[i].getSizeOfOwnedPlaces(); k++){
                        NPC[p].addOwnerShip(NPC[i].getOwnedPlaces(k));
                    } //adds all the location of the places that the heros owned
                    for (int t = 0; t < 4; t++){
                        if(NPC[p].getWarriorName(t) != "NULL"){
                            soldiers.push_back(NPC[p].getWarrior(t));
                        }
                        if(NPC[i].getWarriorName(t) != "NULL"){
                            soldiers.push_back(NPC[i].getWarrior(t));
                        }
                    }
                    
                        if(soldiers.size() <= 4){
                            if(soldiers.size() != 0){
                                for (int t = 0; t < soldiers.size(); t++){
                                    myHero.setWarrior(t , soldiers[t]);
                                }
                            }
                        } //sets the warriors of the loser into the winner
                        else{
                            for (int v = 0; v < 4; v++){
                                NPC[p].setWarrior(v , soldiers[v]);
                                soldiers.erase(soldiers.begin() + v);
                            } //lets you choose what warriors to add in your team
                            for (int v = 0; v < soldiers.size(); v++){
                                soldiers[v].setRow(NPC[i].getRow());
                                soldiers[v].setColumn(NPC[i].getColumn());
                                warriors.push_back(soldiers[v]);
                            }
                        }
                        
                    
                    
                    NPC.erase(NPC.begin() + i);
                    
                    
                }
                if(empty1 == true && empty == true){
                    //tie, both escape nothing happens
                    NPC[i].setArmy(NPC[i].getArmy() / 2);
                    NPC[p].setArmy(NPC[p].getArmy() / 2);
                }
                if(empty1 == false && empty == false){
                    power = NPC[i].getArmy() * NPC[i].getWarrior(randWarrior(NPC[i].getWarriorSize())).getStrength();
                    power1 = NPC[p].getArmy() * NPC[p].getWarrior(randWarrior(NPC[p].getWarriorSize())).getStrength();
                    if(power >= power1){
                        cout << NPC[p].getName() << " has retired" << endl;
                        NPC[i].setMoney(NPC[i].getMoney() + NPC[p].getMoney());
                        NPC[i].setInfluence(NPC[i].getInfluence() + NPC[p].getInfluence());
                        NPC[i].setArmy(NPC[i].getArmy() + NPC[p].getArmy());
                        NPC[i].setPoints(NPC[i].getPoints() + NPC[p].getPoints());
                        for (int k = 0; k < NPC[p].getSizeOfOwnedPlaces(); k++){
                            NPC[i].addOwnerShip(NPC[p].getOwnedPlaces(k));
                        } //adds all the location of the places that the heros owned
                        for (int t = 0; t < 4; t++){
                            if(NPC[p].getWarriorName(t) != "NULL"){
                                soldiers.push_back(NPC[p].getWarrior(t));
                            }
                            if(NPC[i].getWarriorName(t) != "NULL"){
                                soldiers.push_back(NPC[i].getWarrior(t));
                            }
                        }
                        
                            if(soldiers.size() <= 4){
                                if(soldiers.size() != 0){
                                    for (int t = 0; t < soldiers.size(); t++){
                                        myHero.setWarrior(t , soldiers[t]);
                                    }
                                }
                            } //sets the warriors of the loser into the winner
                            else{
                                for (int v = 0; v < 4; v++){
                                    NPC[i].setWarrior(v , soldiers[v]);
                                    soldiers.erase(soldiers.begin() + v);
                                } //lets you choose what warriors to add in your team
                                for (int v = 0; v < soldiers.size(); v++){
                                    soldiers[v].setRow(NPC[p].getRow());
                                    soldiers[v].setColumn(NPC[p].getColumn());
                                    warriors.push_back(soldiers[v]);
                                }
                        }
                        
                    
                    
                    NPC.erase(NPC.begin() + p);
                    
                    }
                    else{
                        cout << NPC[i].getName() << " has retired" << endl;
                        NPC[p].setMoney(NPC[p].getMoney() + NPC[i].getMoney());
                        NPC[p].setInfluence(NPC[i].getInfluence() + NPC[p].getInfluence());
                        NPC[p].setArmy(NPC[i].getArmy() + NPC[p].getArmy());
                        NPC[p].setPoints(NPC[i].getPoints() + NPC[p].getPoints());
                        for (int k = 0; k < NPC[i].getSizeOfOwnedPlaces(); k++){
                            NPC[p].addOwnerShip(NPC[i].getOwnedPlaces(k));
                        } //adds all the location of the places that the heros owned
                        for (int t = 0; t < 4; t++){
                            if(NPC[p].getWarriorName(t) != "NULL"){
                                soldiers.push_back(NPC[p].getWarrior(t));
                            }
                            if(NPC[i].getWarriorName(t) != "NULL"){
                                soldiers.push_back(NPC[i].getWarrior(t));
                            }
                        }
                        
                            if(soldiers.size() <= 4){
                                if(soldiers.size() != 0){
                                    for (int t = 0; t < soldiers.size(); t++){
                                        myHero.setWarrior(t , soldiers[t]);
                                    }
                                }
                            } //sets the warriors of the loser into the winner
                            else{
                                for (int v = 0; v < 4; v++){
                                    NPC[p].setWarrior(v , soldiers[v]);
                                    soldiers.erase(soldiers.begin() + v);
                                } //lets you choose what warriors to add in your team
                                for (int v = 0; v < soldiers.size(); v++){
                                    soldiers[v].setRow(NPC[i].getRow());
                                    soldiers[v].setColumn(NPC[i].getColumn());
                                    warriors.push_back(soldiers[v]);
                                }
                            }
                            
                        
                        
                        NPC.erase(NPC.begin() + i);
                    }
                }
            }
        }
        
    } // checks and solves the encounters of the other heros
    
 
    
    for (int i = 0; i < warriors.size(); i++){
        char ans;
        if(abs(myHero.getRow() - warriors[i].getRow()) <= 2 && abs(myHero.getColumn() - warriors[i].getColumn()) <= 2){
            cout << "There is a warrior named " << warriors[i].getName() << " nearby. Would you like to recruit? (Y/N)" << endl;
            cin >> ans;
            while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N'){
                cout << "ERROR, please try again" << endl;
                cin >> ans;
            }
            if(ans == 'y' || ans == 'Y'){
                if(myHero.getWarriorSize() == 4){
                    for (int k = 0; k < 4; k++){
                        cout << "Since your party is full. Who would you like to replace?" << endl; 
                        cout << k + 1 << ") " << myHero.getWarrior(k).getName() << endl;
                    }
                    cin >> choice;
                    warriors.push_back(myHero.getWarrior(choice - 1));
                    myHero.setWarrior(choice - 1 , warriors[i]);
                }
                else{
                    myHero.setWarrior(myHero.getWarriorSize() , warriors[i]);
                }
                warriors.erase(warriors.begin() + i);   
            }
        }
    } // adds the nearby warrior into the main heros team if desired
    
   
    
    for (int i = 0; i < warriors.size(); i++){
        for (int k = 0; k < NPC.size(); k++){
            if(abs(NPC[k].getRow() - warriors[i].getRow()) <= 2 && abs(NPC[k].getColumn() - warriors[i].getColumn()) <= 2){
                if(NPC[k].getWarriorSize() != 4){
                    NPC[k].setWarrior(NPC[k].getWarriorSize() , warriors[i]);
                    warriors.erase(warriors.begin() + i);
                }
            }
        }
    } // adds the nearby warrior into the NPC heros party
  
    
    place = gameData.getTile(myHero.getRow() - 1 , myHero.getColumn() - 1);
    
    if(place.getPlace() <= 'Z' && place.getPlace() >= 'A'){
        if(myHero.checkFirstCity(place)){
            char ans;
            cout << "You have arrived in " << place.getName() << ". Do you want to listen to rumours? (Y/N)" << endl;
            cin >> ans;
            while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N'){
                cout << "ERROR, please try again" << endl;
                cin >> ans;
            }
            if(ans == 'y' || ans == 'Y'){
                int distance = 1000;
                int test;
                for (int i = 0; i < NPC.size(); i++){
                    test = abs(myHero.getRow() - NPC[i].getRow()) + abs(myHero.getColumn() - NPC[i].getColumn());
                    if (test < distance){
                        distance = test;
                    }
                }
                cout << "The closest hero is " << distance << " moves away" << endl;
            }
            cout << "You have arrived in " << place.getName() << ". Do you want to buy more knights? 20 units of money for 1 knight. (Y/N)" << endl;
            cin >> ans;
            while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N'){
                cout << "ERROR, please try again" << endl;
                cin >> ans;
            }
            if(ans == 'y' || ans == 'Y'){
                if(myHero.getMoney() - 20 < 0){
                    cout << "Not enough money" << endl;
                }
                else{
                myHero.setMoney(myHero.getMoney() - 20);
                myHero.setArmy(myHero.getArmy() + 1);
                cout << "One knight added" << endl;
                }
            }
        }
        myHero.addCity(place);
    } // if it is your first time arriving in a city, give these options
  
    if(myHero.checkOwnerShip(place)){ //checks if its their first time there
        for (int i = 0; i < NPC.size(); i++){
            if(NPC[i].checkOwnerShip(place) == false){
                NPC[i].eraseOwnerShip(place);
            }
        }
        myHero = updateHero(myHero , place);
    } //updates the hero's location and stores all the points
    
    for (int i = 0; i < NPC.size(); i++){
        place = gameData.getTile(NPC[i].getRow() - 1 , NPC[i].getColumn() - 1);
    
        if(NPC[i].checkOwnerShip(place)){
            for (int k = 0; k < NPC.size(); k++){
                if(NPC[k].checkOwnerShip(place) == false){
                    NPC[k].eraseOwnerShip(place);
                }
                if(myHero.checkOwnerShip(place) == false){
                    myHero.eraseOwnerShip(place);
                }
            }
            NPC[i] = updateHero(NPC[i] , place);
        }
    } //updates the NPC's location and stores all the points
   
    place = gameData.getTile(myHero.getRow() - 1 , myHero.getColumn() - 1);
    
    if(place.getDragonGlass() == true && myHero.getWarriorSize() != 0){
        cout << "Great news! You have stumbled upon Dragonglass. Which warrior do you want to equip it with? (Type in the number next to the name)" << endl;
        for (int i = 0; i < myHero.getWarriorSize(); i++){
                cout << i + 1 << ") " << myHero.getWarriorName(i) << endl;
        }
        cin >> choice;
        while(choice < 1 || choice > myHero.getWarriorSize()){
            cout << "Choose number between 1 and 4" << endl;
            cin >> choice;
        }
        while(myHero.getWarrior(choice - 1).getDragonGlass() == true){
            cout << "This hero already has Dragonglass, try another one." << endl;
            cin >> choice;
        }
        store = myHero.getWarrior(choice - 1);
        store.setDragonGlass(true);
        myHero.setWarrior(choice - 1 , store);
        place.setDragonGlass(false);
        gameData.setTile(place , myHero.getRow() - 1 , myHero.getColumn() - 1);
    } //If you land on a place with dragonglass, gives you the option to choose which warrior to have it
   
    for (int i = 0; i < NPC.size(); i++){
        place = gameData.getTile(NPC[i].getRow() - 1 , NPC[i].getColumn() - 1);
        if(place.getDragonGlass() == true && NPC[i].getWarriorSize() != 0){
            for (int k = 0; k < NPC[i].getWarriorSize(); i++){
                if(NPC[i].getWarrior(k).getDragonGlass() == false){
                    store = NPC[i].getWarrior(k);
                    store.setDragonGlass(true);
                    NPC[i].setWarrior(k, store);
                    place.setDragonGlass(false);
                    gameData.setTile(place , NPC[i].getRow() - 1 , NPC[i].getColumn() - 1);
                    break;
                }
            }
        }
    } //If a NPC lands on dragonglass, automatically gives it to one of the warriors
  
    
    if(warriors.size() != 0){
        for (int i = 0; i < warriors.size(); i++){
            place = gameData.getTile(warriors[i].getRow() - 1 , warriors[i].getColumn() - 1);
            if(place.getDragonGlass() == true && warriors[i].getDragonGlass() == false){
             
                warriors[i].setDragonGlass(true);
                place.setDragonGlass(false);
                gameData.setTile(place, warriors[i].getRow() - 1 , warriors[i].getColumn() - 1);
            }
        } //If a warrior lands on dragonglass, adds it to him/her
    }
    if(randomEvent()){
        choice = randDirection();
        cout << endl;
        switch(choice){
            case 1: // drought
                cout << "There has not been rain for days and the your party has very little food" << endl;
                cout << "All warriors' Morale and Strength dropped by 10" << endl;
                for (int i = 0; i < myHero.getWarriorSize(); i++){
                    store = myHero.getWarrior(i);
                    store.setMorale(store.getMorale() - 10);
                    store.setStrength(store.getStrength() - 10);
                    myHero.setWarrior(i , store);
                } //drops the stats of the warriors
                break;
            case 2: // deserters
                cout << "The campaign has been long. Your soldiers are tired and sad." << endl;
                cout << "Army size and loyalty of warriors go down by 10" << endl;
                myHero.setArmy(myHero.getArmy() - 10);
                for (int i = 0; i < myHero.getWarriorSize(); i++){
                    store = myHero.getWarrior(i);
                    store.setLoyalty(store.getLoyalty() - 10);
                    myHero.setWarrior(i , store);
                } // drops loyalty
                break; 
            case 3: // Jackpot
                cout << "Your hero deeds have won the hearts of many nobles and wealthy benefactors." << endl;
                cout << "Money doubled." << endl;
                myHero.setMoney(myHero.getMoney() * 2); //doubles the money
                break;
            case 4: //Kindness
                cout << "You have decided to offer shelter for some refugees" << endl;
                cout << "Army and Warrior loyalty increase by 10" << endl;
                myHero.setArmy(myHero.getArmy() + 10);
                for (int i = 0; i < myHero.getWarriorSize(); i++){
                    store = myHero.getWarrior(i);
                    store.setLoyalty(store.getLoyalty() + 10);
                    myHero.setWarrior(i , store);
                } // adds the loyalty
                break;
        }
    } // triggers the random events for every turn
  
    if(game == false){
        cout << "Game Over" << endl;
        break;
    }
    turn++;
    
    if(turn == 10){
        Warrior Dragon = Warrior("Dragon" , "NULL" , 180 , 100 , 80 , false , false , false , 1 , 1);
        Hero storage;
        int idx = 100;
        char letter;
        if(true){
            if(myHero.getName() == "Daenerys Targaryen"){
                storage = myHero;
            }
                for (int i = 0; i < NPC.size(); i++){
                    if(NPC[i].getName() == "Daenerys Targaryen"){
                        storage = NPC[i];
                        idx = i;
                    }
                }
                
                storage.setArmy(storage.getArmy() + 5000);
                
                if(storage.getWarriorSize() == 4){
                    store = storage.getWarrior(3);
                    Dragon.setStrength(Dragon.getStrength() + store.getStrength() * 0.1);
                    Dragon.setLoyalty(Dragon.getLoyalty() + store.getLoyalty() * 0.1);
                    Dragon.setMorale(Dragon.getMorale() + store.getMorale() * 0.1);
                    storage.setWarrior(3 , Dragon);
                } // sets the dragon as Daenerys warrior
                else{
                    for (int i = 0; i < 4; i++){
                        if(storage.getWarriorName(i) == "NULL"){
                            storage.setWarrior(i , Dragon);
                        }
                    }
                }
                if(idx == 100){
                    myHero = storage;
                }
                else{
                    NPC[idx] = storage;
                }
        } // Daenerys event
        cout << "Daenerys got Dragons" << endl;
        
        if(true){
            idx = 100;
            if(myHero.getName() == "Stannis Baratheon"){
                storage = myHero;
            }
            for (int i = 0; i < NPC.size(); i++){
                    if(NPC[i].getName() == "Stannis Baratheon"){
                        storage = NPC[i];
                        idx = i;
                    }
                }
            for (int i = 0; i < storage.getWarriorSize(); i++){
                store = storage.getWarrior(i);
                store.setRow(storage.getRow());
                store.setColumn(storage.getColumn());
                warriors.push_back(store);
            } // lets all the warriors roam free
            if(idx == 100){
                cout << "Stannis has been consumed by demons and died" << endl;
                cout << "Game Over" << endl;
                game = false;
            }
            else{
                cout << "Stannis has retired. Press F to pay respects" << endl;
                cin >> letter;
                while(letter != 'f' && letter != 'F'){
                    cout << "Have you no respect!? Press F to pay respects" << endl;
                    cin >> letter;
                }
                cout << "Mood" << endl;
            }
            
        } // Stannis event
        
        if(true){
            for (int i = 0; i < NPC.size(); i++){
                for (int k = 0; k < NPC[i].getWarriorSize(); i++){
                    Warrior blank = Warrior();
                    if(NPC[i].getWarriorName(k) == "Arya Stark"){
                        store = NPC[i].getWarrior(k);
                        NPC[i].setWarrior(k , blank);
                    }
                }
            } // finds Arya within the NPCs and erase
            for (int i = 0; i < myHero.getWarriorSize(); i++){
                Warrior blank = Warrior();
                if(myHero.getWarriorName(i) == "Arya Stark"){
                        store = myHero.getWarrior(i);
                        myHero.setWarrior(i , blank);
                }
            } //finds Arya in the main hero and erase
            for (int i = 0; i < warriors.size(); i++){
                if(warriors[i].getName() == "Arya Stark"){
                        store = warriors[i];
                        warriors.erase(warriors.begin() + i);
                    }
            } //finds Arya in the free warriors and erase
            if(myHero.getName() == "Sansa Stark"){
                if(myHero.getWarriorSize() != 4){
                    cout << "You have recruited a warrior named Arya Stark" << endl;
                    myHero.setWarrior(myHero.getWarriorSize() , store);
                }
                else{
                    cout << "There is a warrior named Arya Stark who wants to follow you, Sansa Stark. Would you like to recruit? (Y/N)" << endl;
                    cin >> letter;
                    while(letter != 'y' && letter != 'Y' && letter != 'n' && letter != 'N'){
                        cout << "ERROR, please try again" << endl;
                        cin >> letter;
                    }
                    if(letter == 'y' || letter == 'Y'){
                        for (int k = 0; k < 4; k++){
                            cout << "Since your party is full. Who would you like to replace?" << endl; 
                            cout << k + 1 << ") " << myHero.getWarrior(k).getName() << endl;
                        }
                        cin >> choice;
                        warriors.push_back(myHero.getWarrior(choice - 1));
                        myHero.setWarrior(choice - 1 , store);
                    }
                }
            }
            for (int i = 0; i < NPC.size(); i++){
                if(NPC[i].getName() == "Sansa Stark"){
                    if(NPC[i].getWarriorSize() != 4){
                        NPC[i].setWarrior(NPC[i].getWarriorSize() , store);
                    }
                    else{
                        warriors.push_back(NPC[i].getWarrior(3));
                        NPC[i].setWarrior(3 , store);
                    }
                }
            }
        } // Sansa Event
        cout << "Sansa has recruited Arya" << endl;
        
        if(true){
            if(myHero.getName() == "Cersei Lannister"){
                for (int i = 0; i < myHero.getWarriorSize(); i++){
                    Warrior blank = Warrior();
                    if(myHero.getWarriorName(i) == "Jaime Lannister"){
                        warriors.push_back(myHero.getWarrior(i));
                        myHero.setWarrior(i , blank);
                    }
                }
            } // Cersei loses Jaime
            for (int k = 0; k < NPC.size(); k++){
                if(NPC[k].getName() == "Cersei Lannister"){
                    for (int i = 0; i < NPC[k].getWarriorSize(); i++){
                        Warrior blank = Warrior();
                            if(NPC[k].getWarriorName(i) == "Jaime Lannister"){
                                warriors.push_back(NPC[k].getWarrior(i));
                                NPC[k].setWarrior(i , blank);
                            }
                    }
                }
            } // NPC Cersei loses Jaime
            
        } // Cerseis Event
        
        cout << "Cerseis lost Jaime, Jaime is now free" << endl;
    } // all specific events that happen at turn 10
    
    if(turn >= 50 || myHero.getArmy() >= 2000 || myHero.getSizeOfOwnedPlaces() >= 200 || myHero.getPoints() >= 400 || NPC.size() == 0){
        char answer;
        int whiteCounter = 5;
        double powerScore = 0.0;
        int counter = 0;
        double finalBattle;
        cout << "Sad news! The White Walkers are coming. Would you like to battle them now? (Y/N)" << endl;
        cin >> answer;
        while(answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N'){
                cout << "ERROR, please try again" << endl;
                cin >> answer;
            }
        if(answer == 'y' || answer == 'Y'){
            if(myHero.getArmy() > 10000){
                myHero.setArmy(10000);
            }
            if(myHero.getInfluence() > 10000){
                myHero.setInfluence(10000);
            }
            if(myHero.getMoney() > 10000){
                myHero.setMoney(10000);
            }
            
            for (int i = 0; i < myHero.getSizeOfOwnedPlaces(); i++){
                place = myHero.getOwnedPlaces(i);
                if(place.getPlace() <= 'Z' && place.getPlace() >= 'A'){
                    counter++;
                }
            }
            
            for (int i = 0; i < myHero.getWarriorSize(); i++){
                store = myHero.getWarrior(i);
                if(store.getMorale() > 100){
                    store.setMorale(100);
                }
                powerScore += (counter + 1) * (myHero.getInfluence() / 50);
                powerScore += (store.getStrength() * (store.getMorale() / 50));
                if(store.getDragonGlass() == true){
                    powerScore = powerScore + 10000;
                }
            } // adds to the power score base on warrior strength and morale and dragonglass
            
            
            powerScore += myHero.getArmy();
            
            finalBattle = 1 - exp((0 - powerScore) / 30000);
            
            finalBattle = finalBattle * 100;

            for (int i = 0; i < 3; i++){
                if(generateProbility(finalBattle)){
                    cout << "Congratulations, you won!!!" << endl;
                    whiteWalkers = true;
                    game = true;
                    break;
                }
                else{
                    cout << "Unfortunately, you have lost the Battle" << endl;
                    game = false;
                }
            }
        }
        else{
            cout << "You have " << whiteCounter << " turns left before the inevitable." << endl;
            if(whiteCounter == 0){
                cout << "You have failed as a hero. Game Over" << endl;
                game = false;
            }
        }
        whiteCounter--;
    } // Battle with the white walkers
    

}
    if(game == false){
        return false;
    }
    if(whiteWalkers == true){
            ofstream myfile;
            myfile.open("resultsGOT.txt" , ios::app);
            if(myfile.is_open()){
                int nameWidth = 12;
                char separator = ' ';
                myfile << endl;
                myfile << left << setw(nameWidth) << setfill(separator) << player;
                myfile << left << setw(nameWidth) << setfill(separator) << myHero.getName();
                myfile << left << setw(nameWidth) << setfill(separator) << myHero.getPoints();
                
            }
            myfile.close();
        return true;
    }
    
}

int main(){
    string player;
    int choice = 7;
    char ans;
    char answer = 'y';
    cout << "Welcome to the G A M E of T H R O N E S!" << endl;
    cout << "State your name, Your Grace: ";
    getline(cin, player);
    while(answer == 'Y' || answer == 'y'){
    cout << "Would you like to choose a hero " << player << ", Your Grace?(Y/N): ";
    cin >> ans;
    while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N'){
                cout << "Error , try again" << endl;
                cin >> ans;
     }
    if (ans == 'Y' || ans == 'y'){
        displayHeros();
        cin >> choice;
        
        while(choice >= 7 || choice <= 0){
            cout << "ERROR: PLEASE CHOOSE FROM 1 TO 6" << endl;
            cin >> choice;
        }
        
    } // chooses the hero
    
    
        bool result = game(choice , player);
        if(result == true){
            //adds the name and score to the winner table in a separate file
            cout << "You have beat the game. Would you like to start again? (Y/N)" << endl;
            cin >> answer;
            while(answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N'){
                cout << "Error , try again" << endl;
                cin >> answer;
            }
        }
        else{
            cout << "You have lost the game. Would you like to start again? (Y/N)" << endl;
            cin >> answer;
            while(answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N'){
                cout << "Error , try again" << endl;
                cin >> answer;
            }
        }
    
    }

    
    
    
}