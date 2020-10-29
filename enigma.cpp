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
    //pair <char, char> plugs[10];
    int *plugs_forwards, *plugs_backwards;
    int offset1 = 0, offset2 = 0, offset3 = 0;
    int plug_count = 0;

    void encode(){
        string output = "";
        string input = "";
        string message = "";
        int letter_index;
        cout << "Enter message >";
        cin >> input;

        //For letter in input,
        for(int i = 0; i < input.length(); i++){
            //Make letter uppercase. 
            //Kinda a stupid way to do this. 
            if( (int)input[i] > 96 && (int)input[i] < 123){
                input[i] = (int)input[i] - 32;
            }
            //If character is an uppercase letter, get it's master index
            if( (int)input[i] > 64 && (int)input[i] < 91){
                letter_index = master.find(input[i]);

                //First we check it against the plugboard
                for(int j = 0; j < plug_count; j++){
                    //Alright, let's pretend plugs is a double index list again.
                    if(plugs_forwards[j] == letter_index)
                        letter_index = plugs_backwards[j];
                }

                //Then we do the big mathematical index dance.
                //This is a bit tricky as the concept of the index is in flux.
                //Basically, there is the input index, and the rotor index.
                //By default, A has an index of 0. From there the rotor maps it to something else. Easy.
                //However, the rotation of the rotor means that an input of A, 0, would actually go to B, 1, before being mapped to something else.
                //And the value it's mapped to isn't in it's 'normal' spot either, it is also affected by the offset.
                //These misaligned indexes work as follows:
                letter_index += offset1;
                if(letter_index > 25){letter_index -= 26;}
                letter_index = rotor1_f[letter_index];
                letter_index -= offset1;
                if(letter_index < 0){letter_index += 26;}

                letter_index += offset2;
                if(letter_index > 25){letter_index -= 26;}
                letter_index = rotor2_f[letter_index];
                letter_index -= offset2;
                if(letter_index < 0){letter_index += 26;}

                letter_index += offset3;
                if(letter_index > 25){letter_index -= 26;}
                letter_index = rotor3_f[letter_index];
                letter_index -= offset3;
                if(letter_index < 0){letter_index += 26;}

                //After the third rotor we go to the opposite input.
                letter_index += 13;
                if(letter_index > 25){letter_index -= 26;}

                //Then we go through the whole thing again in reverse.
                letter_index += offset3;
                if(letter_index > 25){letter_index -= 26;}
                letter_index = rotor3_b[letter_index];
                letter_index -= offset3;
                if(letter_index < 0){letter_index += 26;}

                letter_index += offset2;
                if(letter_index > 25){letter_index -= 26;}
                letter_index = rotor2_b[letter_index];
                letter_index -= offset2;
                if(letter_index < 0){letter_index += 26;}

                letter_index += offset1;
                if(letter_index > 25){letter_index -= 26;}
                letter_index = rotor1_b[letter_index];
                letter_index -= offset1;
                if(letter_index < 0){letter_index += 26;}

                //Then we increment the rotors.
                offset1 += 1;
                if(offset1 > 25){
                    offset1 -= 26;
                    offset2 += 1;
                }
                if(offset2 > 25){
                    offset2 -= 26;
                    offset3 += 1;
                }
                if(offset3 > 25){
                    offset3 -= 26;
                }

                //Then we do the reverse plugs.
                for(int j = 0; j < plug_count; j++){
                    if(plugs_backwards[j] == letter_index)
                        letter_index = plugs_forwards[j];
                }

                //And finally we have our encoded letter.
                message.push_back(master[letter_index]);
            } else {
                //or unencoded grammar.
                message.push_back(input[i]);
            }
        }
        //Done and done.
        cout << "Your encoded message is: " << message << "\n";
        return;
    }

    //Probably gonna simplify this compared to the python version.
    void modify(){
        
        return;
    }
};

int main(){

    return 0;
}