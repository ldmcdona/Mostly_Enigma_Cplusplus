#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <random>
#include <string>
#include <utility>
#include <iostream>

using namespace std;

//Global variables:
string master = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int* covert(string rotor) {
    int rotor_forwards[26], rotor_backwards[26];
    char rotor_value;
    int master_value;
    for(int i = 0; i < 26; i++){
        rotor_value = rotor[i];
        master_value = master.find(rotor_value);
        rotor_forwards[i] = master_value;
        rotor_backwards[master_value] = i;
    }

    return rotor_forwards, rotor_backwards;
}

int** rotorWheels(){
    string w1 = "PEZUOHXSCVFMTBGLRINQJWAYDK", w2 = "ZOUESYDKFWPCIQXHMVBLGNJRAT", w3 = "EHRVXGAOBQUSIMZFLYNWKTPDJC", w4 = "IMETCGFRAYSQBZXWLHKDVUPOJN", w5 = "QWERTZUIOASDFGHJKPYXCVBNML";

    return;
}

class Enigma {
public:
    string rotor1_f, rotor1_b, rotor2_f, rotor2_b, rotor3_f, rotor3_b; 
    pair <char, char> plugs[10];
    int offset1 = 0, offset2 = 0, offset3 = 0;
    int plug_count = 0;
};

int main(){

    return 0;
}