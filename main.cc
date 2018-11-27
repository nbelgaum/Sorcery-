#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "display.h"
#include "player.h"
#include "graphicsdisplay.h"


using namespace std;

int main(int argc, const char * argv[]) {
    Player * p1, * p2;
    string name_1, name_2, winner;   // Names of the two players and the final winner
    string cmd;              // The command the active player will take
    ifstream fin_1, fin_2, fin;   // To read the the name of the cards from the file if provided and init commands
    bool isTesting = false, isInit = false, isGrpahics = false, isDeck1 = false, isDeck2 = false;  // To keep count of if testing is on,
                                                                                                   // initial file was provided and if decks were provided
    bool isBonus = false;
    vector<string> p1_deck, p2_deck;
    bool p1_turn = true, wasQuit = false;
    GraphicsDisplay * gd;
    
    if (argc > 1) {
        for(int i = 1; i < argc; i++) {
            string flag = argv[i];
            if(flag == "-enablebonus") {
                isBonus = true;
            } else if (flag == "-testing") {
                isTesting = true;
            } else if (flag == "-graphics") {
                isGrpahics = true;
                gd = new GraphicsDisplay();
            } else if (flag == "-init") {
                i++;
                string file = argv[i];
                fin.open(file);
                if(fin.fail()) {
                    cerr << "The file could not be opened" << endl;
                } else {
                    isInit = true;
                }
            } else if (flag == "-deck1")  {
                i++;
                string deck1 = argv[i];
                fin_1.open(deck1);
                if(fin_1.fail()) {
                    cerr << "The file could not be opened" << endl;
                } else {
                    isDeck1 = true;
                }
            } else if (flag == "-deck2") {
                i++;
                string deck2 = argv[i];
                fin_2.open(deck2);
                if(fin_2.fail()) {
                    cerr << "The file could not be opened" << endl;
                } else {
                    isDeck2 = true;
                }
            } else if (flag == "and") {
                // do nothing
            } else {
                cerr << "Wrong flag" << endl;
            }
        }
    }
    
    if (isInit) {                 // Checking if a file has been provided to initialise the game
        fin >> name_1 >> name_2;
    } else {
        cout << "Please enter  the names of the players" << endl;
        cin >> name_1 >> name_2;
    }
    
    string line;
    string word;
    if (isDeck1) {     // Checking if a deck has been provided to initialise the player with
        string line;
        while(getline(fin_1, line)) {
            istringstream iss(line);
            iss >> word;
            p1_deck.emplace_back(word);
        }
    } else {
        ifstream in;
        in.open("default.deck");
        while(getline(in, line)) {
            istringstream iss(line);
            iss >> word;
            p1_deck.emplace_back(word);
        }
    }
    
    if (isDeck2) {
        while(getline(fin_2, line)) {        // Checking if a deck has been provided to initialise the player with
            istringstream iss(line);
            iss >> word;
            p2_deck.emplace_back(word);
        }
    } else {
        ifstream in;
        in.open("default.deck");
        while(getline(in, line)) {
            istringstream iss(line);
            iss >> word;
            p2_deck.emplace_back(word);
            
        }
    }
    
    if(!isTesting) {                                     // Checking if testing mode is on so that
                                                         // shuffling of deck takes place or not
        srand(time(0));                                  // Seeding the randomization
        random_shuffle(p1_deck.begin(), p1_deck.end());   
        random_shuffle(p2_deck.begin(), p2_deck.end());
    }
    
    p1 = new Player(name_1, p1_deck, isBonus);
    p2 = new Player(name_2, p2_deck, isBonus);
    p1->setOpponent(p2);
    p2->setOpponent(p1);
    p1->myStart();
    if(isGrpahics) {
        gd->drawHand(p1);
    }
    
    cout << "Start Entering command" << endl;
    
    while(true) {
        if(fin >> cmd) {
            // Do nothing
        } else {
            cin >> cmd;
        }
        
        if (cmd == "help") {
            cout << "Commands: help -- Display this message." << endl;
            cout << "          end -- End the current player’s turn." << endl;
            cout << "          quit -- End the game." << endl;
            cout << "          attack minion other-minion -- Orders minion to attack other-minion." << endl;
            cout << "          attack minion -- Orders minion to attack the opponent." << endl;
            cout << "          play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
            cout << "          use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player." << endl;
            cout << "          inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
            cout << "          hand -- Describe all cards in your hand." << endl;
            cout << "          board -- Describe all cards on the board." << endl;
        } else if (cmd == "end") {
            if(p1_turn) {
                p1->myEnd();
                p1_turn = false;
                p2->myStart();
                if(isGrpahics) {
                    gd->drawHand(p2);
                }
            } else {
                p2->myEnd();
                p1_turn = true;
                p1->myStart();
                if(isGrpahics) {
                    gd->drawHand(p1);
                }
            }
            
        } else if (cmd == "quit") {
            wasQuit = true;
            break;
        } else if (cmd == "draw") {
            if (!isTesting) {
                cout << "Testing mode is off" << endl;
            } else {
                if(p1_turn) {
                    p1->drawCard();
                    if(isGrpahics) {
                        gd->drawHand(p1);
                    }
                    
                } else {
                    p2->drawCard();
                    if(isGrpahics) {
                        gd->drawHand(p2);
                    }
                    
                }
            }
        } else if (cmd == "discard") {
            if (!isTesting) {
                cout << "Testing mode is off" << endl;
            } else {
                int index;
                cin >> index;
                if(p1_turn) {
                    p1->discard(index);
                    if(isGrpahics) {
                        gd->drawHand(p1);
                    }
                    
                } else {
                    p2->discard(index);
                    if(isGrpahics) {
                        gd->drawHand(p2);
                    }
                    
                }
            }
        } else if (cmd == "attack") {
            if(isInit) {
                int myIndex, enemyIndex;
                if(fin >> myIndex && fin >> enemyIndex) {
                    if(p1_turn) {
                        p1->attackMinion(myIndex, enemyIndex);
                    } else {
                        p2->attackMinion(myIndex, enemyIndex);
                    }
                } else {
                    fin.ignore();
                    fin.clear();
                    if(p1_turn) {
                        p1->attackPlayer(myIndex);
                    } else {
                        p2->attackPlayer(myIndex);
                    }
                }
            } else {
                int choice;
                cout << "Enter 1 to attack player and 2 to attack a minion" << endl;
                cin >> choice;
                if(choice == 1) {
                    cout << "Enter the minion index with whom you want to attack" << endl;
                    int index;
                    cin >> index;
                    if(p1_turn) {
                        p1->attackPlayer(index);
                        if(p2->isPlayerDead()) {
                            winner = p1->getMyName();
                            break;
                        }
                    } else {
                        p2->attackPlayer(index);
                        if(p1->isPlayerDead()) {
                            winner = p2->getMyName();
                            break;
                        }
                    }
                } else {
                    cout << "Enter the your minion index and the enemy minion index you want to attack" << endl;
                    int myIndex, oppIndex;
                    cin >> myIndex >> oppIndex;
                    if(p1_turn) {
                        p1->attackMinion(myIndex, oppIndex);
                    } else {
                        p2->attackMinion(myIndex, oppIndex);
                    }
                }
            }
            
        } else if (cmd == "play") {
            if(isInit) {
                int myIndex, playerNo;
                char enemyIndex;
                if(fin >> myIndex && fin >> playerNo && fin >> enemyIndex) {
                    if(p1_turn) {
                        p1->play(myIndex, playerNo, enemyIndex, isTesting);
                        if(isGrpahics) {
                            gd->drawHand(p1);
                        }
                        
                    } else {
                        p2->play(myIndex, playerNo, enemyIndex, isTesting);
                        if(isGrpahics) {
                            gd->drawHand(p2);
                        }
                        
                    }
                } else {
                    fin.ignore();
                    fin.clear();
                    if(p1_turn) {
                        p1->play(myIndex, isTesting);
                        if(isGrpahics) {
                            gd->drawHand(p1);
                        }
                    } else {
                        p2->play(myIndex, isTesting);
                        if(isGrpahics) {
                            gd->drawHand(p2);
                        }
                    }
                }
                
            } else {
                int choice;
                cout << "Enter 1 to just play a card and 2 to play a card on a target" << endl;
                cin >> choice;
                if(choice == 1) {
                    cout << "Enter the index of the card in your hand to play" << endl;
                    int index;
                    cin >> index;
                    if(p1_turn) {
                        p1->play(index, isTesting);
                        if(isGrpahics) {
                            gd->drawHand(p1);
                        }
                    } else {
                        p2->play(index, isTesting);
                        if(isGrpahics) {
                            gd->drawHand(p2);
                        }
                    }
                } else {
                    cout << "Enter the index of the card in your hand to play, the player number and the target index" << endl;
                    int myIndex, player_no;
                    char oppIndex;
                    cin >> myIndex >> player_no >> oppIndex;
                    if(p1_turn) {
                        p1->play(myIndex, player_no, oppIndex, isTesting);
                        if(isGrpahics) {
                            gd->drawHand(p1);
                        }
                    } else {
                        p2->play(myIndex, player_no, oppIndex, isTesting);
                        if(isGrpahics) {
                            gd->drawHand(p2);
                        }
                    }
                }
            }
            
        } else if (cmd == "use") {
            if(isInit) {
                int minIndex, playerNo;
                char enemyIndex;
                if(fin >> minIndex && fin >> playerNo && fin >> enemyIndex) {
                    if(p1_turn) {
                        p1->use(minIndex, playerNo, enemyIndex, isTesting);
                    } else {
                        p2->use(minIndex, playerNo, enemyIndex, isTesting);
                    }
                } else {
                    fin.ignore();
                    fin.clear();
                    if(p1_turn) {
                        p1->use(minIndex, isTesting);
                    } else {
                        p2->use(minIndex, isTesting);
                    }
                }
                
            } else {
                int choice;
                cout << "Enter 1 to just use a minion and 2 to use the minion on a target" << endl;
                cin >> choice;
                if(choice == 1) {
                    cout << "Enter the index of the minion whose ability you want to use" << endl;
                    int index;
                    cin >> index;
                    if(p1_turn) {
                        p1->use(index, isTesting);
                    } else {
                        p2->use(index, isTesting);
                    }
                } else {
                    cout << "Enter the index of the minion whose ability you want to use, the player number and your target index" << endl;
                    int myIndex, player_no;
                    char oppIndex;
                    cin >> myIndex >> player_no >> oppIndex;
                    if(p1_turn) {
                        p1->use(myIndex, player_no, oppIndex, isTesting);
                    } else {
                        p2->use(myIndex, player_no, oppIndex, isTesting);
                    }
                }
            }
            
        } else if (cmd == "describe") {
            int minIndex;
            cout << "Enter the index of the minion you want to inspect" << endl;
            if(cin >> minIndex) {
                if(p1_turn) {
                    inspectMinion(p1, minIndex);
                    if(isGrpahics) {
                        gd->inspectMinion(p1, minIndex);
                    }
                } else {
                    inspectMinion(p2, minIndex);
                    if(isGrpahics) {
                        gd->inspectMinion(p2, minIndex);
                    }
                }
            }
            
        } else if (cmd == "hand") {
            if(p1_turn) {
                displayHand(p1);
                if(isGrpahics) {
                    gd->drawHand(p1);
                }
            } else {
                displayHand(p2);
                if(isGrpahics) {
                    gd->drawHand(p2);
                }
            }
        } else if (cmd == "board") {
            displayBoard(p1, p2);
            if(isGrpahics) {
                gd->drawBoard(p1, p2);
            }
        } else if(cmd == "bonus") {
            string turn;
            cout << "Should the bonus be turned on or off" << endl;
            cin >> turn;
            if(turn == "on") {
                p1->setBonus(true);
                p2->setBonus(true);
            } else {
                p1->setBonus(false);
                p2->setBonus(false);
            }
        } else {
            cout << "Wrong command" << endl;
        }
        
    }
    
    if(!wasQuit) {                                      // Checking if the game was not quit
        cout << "The winner is :" << winner << endl;    // so that the winner can be anounced
    }
    
    delete p1;
    delete p2;
    
    if(isGrpahics) {
        delete gd;
    }
    
    return 0;
    
}

