#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <random>
#include <string>
#include <utility>
#include <iostream>
#include <vector>

using namespace std;

/*
Plan B in case I cant get rotorWheels() and convert() working.

int rotor1_f[26] = [15, 4, 25, 20, 14, 7, 23, 18, 2, 21, 5, 12, 19, 1, 6, 11, 17, 8, 13, 16, 9, 22, 0, 24, 3, 10];
int rotor2_f[26] = [25, 14, 20, 4, 18, 24, 3, 10, 5, 22, 15, 2, 8, 16, 23, 7, 12, 21, 1, 11, 6, 13, 9, 17, 0, 19];
int rotor3_f[26] = [4, 7, 17, 21, 23, 6, 0, 14, 1, 16, 20, 18, 8, 12, 25, 5, 11, 24, 13, 22, 10, 19, 15, 3, 9, 2];
int rotor4_f[26] = [8, 12, 4, 19, 2, 6, 5, 17, 0, 24, 18, 16, 1, 25, 23, 22, 11, 7, 10, 3, 21, 20, 15, 14, 9, 13];
int rotor5_f[26] = [16, 22, 4, 17, 19, 25, 20, 8, 14, 0, 18, 3, 5, 6, 7, 9, 10, 15, 24, 23, 2, 21, 1, 13, 12, 11];
int rotor1_b[26] = [];
int rotor2_b[26] = [];
int rotor3_b[26] = [];
int rotor4_b[26] = [];
int rotor5_b[26] = [];
*/

//Global variables:
const string master = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//                     01234567890123456789012345
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
    //int *plugs_forwards, *plugs_backwards;
    vector<int> plugs_forwards, plugs_backwards;
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
        char answer, a, b;
        int temp;
        vector<char> taken = {};
        cout << "Change Plugs? (y/n)" << "\n";
        cin >> answer;
        if(answer == 'y'){
            cout << "Enter the number of plugs you want to use. (0 to 10)" << "\n";
            cin >> temp;
            if(temp > 10 || temp < 0){
                cout << "Invalid number entered." << "\n";
                return;
            }
            for(int i = 0; i < temp; i++){
                cout << "Plug " << i << "\n";
                cout << "Enter first letter in pair. (A-Z)" << "\n";
                cin >> a;
                cout << "Enter second letter in pair. (A-Z)" << "\n";
                cin >> b;
                if( (int)a > 90 || (int)a < 65 || (int)b > 90 || (int)b < 65){
                    cout << "Invalid character entered." << "\n";
                    return;
                }
                for(int j = 0; j < taken.size(); j++){
                    if(a == taken[j] || b == taken[j]){
                        cout << "Character already in use." << "\n";
                        plugs_forwards = {};
                        plugs_backwards = {};
                        return;
                    }
                }
                plugs_forwards.push_back(master.find(a));
                plugs_backwards.push_back(master.find(b));
                taken.push_back(a);
                taken.push_back(b);
            }
            plug_count = temp;
        }
        cout << "Swap rotors? (y/n)" << "\n";
        //Left off here.
        return;
    }
};

int main(){

    return 0;
}