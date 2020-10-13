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

int* convert(string rotor) {
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

int* rotorWheels(){
    string w1 = "PEZUOHXSCVFMTBGLRINQJWAYDK", w2 = "ZOUESYDKFWPCIQXHMVBLGNJRAT", w3 = "EHRVXGAOBQUSIMZFLYNWKTPDJC", w4 = "IMETCGFRAYSQBZXWLHKDVUPOJN", w5 = "QWERTZUIOASDFGHJKPYXCVBNML";
    int *rot1_for, *rot1_bac, *rot2_for, *rot2_bac, *rot3_for, *rot3_bac, *rot4_for, *rot4_bac, *rot5_for, *rot5_bac;
    //int **rotors_forwards, **rotors_backwards;

    rot1_for, rot1_bac = convert(w1);
    rot2_for, rot2_bac = convert(w2);
    rot3_for, rot3_bac = convert(w3);
    rot4_for, rot4_bac = convert(w4);
    rot5_for, rot5_bac = convert(w5);

    //rotors_forwards = {rot1_for, rot2_for, rot3_for, rot4_for, rot5_for};

    int i = 0;
    int select;
    string taken;
    char temp;
    while (i < 3){
        cout << "Choose which rotor to use for position " << i << " (1 to 5).\n";
        cin >> select;
        temp = select + '0';
        if (taken.find(temp) == -1){
            if (select < 6 && select > 0){
                taken.push_back(temp);
                i += 1;
            } else {
                cout << "Invalid number.\n";
            }
        } else {
            cout << "Rotors can only be used once.\n";
        }
    }

    //return rotors_forwards[taken[0]-1], rotors_forwards[taken[0]-1]
    return;
}

class Enigma {
public:
    int *rotor1_f, *rotor1_b, *rotor2_f, *rotor2_b, *rotor3_f, *rotor3_b; 
    pair <char, char> plugs[10];
    int offset1 = 0, offset2 = 0, offset3 = 0;
    int plug_count = 0;
};

int main(){

    return 0;
}