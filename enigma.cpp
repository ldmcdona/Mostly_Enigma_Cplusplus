#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <random>
#include <string>
#include <utility>
#include <iostream>
#include <vector>

using namespace std;

//Global variables:
const string master = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//                     01234567890123456789012345

pair <vector<int>, vector<int>> convert(string rotor) {
    //int rotor_forwards[26], rotor_backwards[26];
    vector<int> rotor_forwards, rotor_backwards;
    for(int i=0; i < 26; i++){
        rotor_forwards.push_back(0);
        rotor_backwards.push_back(0);
    }

    char rotor_value;
    int master_value;
    for(int i = 0; i < 26; i++){
        rotor_value = rotor[i];
        master_value = master.find(rotor_value);
        rotor_forwards[i] = master_value;
        rotor_backwards[master_value] = i;
    }

    cout << "rotor_forwards is size " << rotor_forwards.size() << "\n";

    pair <vector<int>, vector<int>> x;
    x.first = rotor_forwards;
    x.second = rotor_backwards;
    return x;
}

vector<vector<int>> rotorWheels(){
    string w1 = "PEZUOHXSCVFMTBGLRINQJWAYDK", w2 = "ZOUESYDKFWPCIQXHMVBLGNJRAT", w3 = "EHRVXGAOBQUSIMZFLYNWKTPDJC", w4 = "IMETCGFRAYSQBZXWLHKDVUPOJN", w5 = "QWERTZUIOASDFGHJKPYXCVBNML";
    string w[5] = {w1, w2, w3, w4, w5};
    vector<int> rot1_for, rot1_bac, rot2_for, rot2_bac, rot3_for, rot3_bac, rot4_for, rot4_bac, rot5_for, rot5_bac;
    vector<int> r_f[5] = {rot1_for, rot2_for, rot3_for, rot4_for, rot5_for};
    vector<int> r_b[5] = {rot1_bac, rot2_bac, rot3_bac, rot4_bac, rot5_bac};
    vector<vector<int>> rotors_forwards, rotors_backwards;
    pair <vector<int>, vector<int>> r1, r2, r3, r4, r5;
    pair <vector<int>, vector<int>> r[5] = {r1, r2, r3, r4, r5};

    //Something about these for-loops isn't working I think, cause the return from convert should be working now I think.

    for(int i=0; i<5; i++){
        r[i] = convert(w[i]);
    }

    for(int i=0; i<5; i++){
        r_f[i] = r[i].first;
        r_b[i] = r[i].second;
    }

    //cout << "rot1_for is size " << rot1_for.size() << "\n";

    rotors_forwards.push_back(rot1_for);
    rotors_forwards.push_back(rot2_for);
    rotors_forwards.push_back(rot3_for);
    rotors_forwards.push_back(rot4_for);
    rotors_forwards.push_back(rot5_for);

    rotors_backwards.push_back(rot1_bac);
    rotors_backwards.push_back(rot2_bac);
    rotors_backwards.push_back(rot3_bac);
    rotors_backwards.push_back(rot4_bac);
    rotors_backwards.push_back(rot5_bac);

    //return rotors_forwards[taken[0]-1], rotors_forwards[taken[0]-1]
    
    for(int i=0; i<5; i++){
        cout << "Rotors_Forwards is size " << rotors_forwards.size() << "\n";
        cout << "The first rotor in Rotors_Forwards is size " << rotors_forwards[0].size() << "\n";
        cout << "Rotor_f " << i << "\n";
        for(int j=0; j<26; j++){
            cout << rotors_forwards[i][j];
        }
        cout << "\n";
    }

    return rotors_forwards, rotors_backwards;
}

class Enigma {
public:
    //int *rotor1_f, *rotor1_b, *rotor2_f, *rotor2_b, *rotor3_f, *rotor3_b; 
    //pair <char, char> plugs[10];
    //int *plugs_forwards, *plugs_backwards;
    vector<int> plugs_forwards, plugs_backwards;
    vector<vector<int>> rotors_forwards, rotors_backwards = rotorWheels();
    vector<int> rotor1_f, rotor1_b, rotor2_f, rotor2_b, rotor3_f, rotor3_b;
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

    void setup(){

        int i = 1;
        int select;
        int set[3];
        string taken;
        char temp;
        while (i < 4){
            cout << "Choose which rotor to use for position " << i << " (1 to 5).\n";
            cin >> select;
            temp = select + '0';
            if (taken.find(temp) == -1){
                if (select < 6 && select > 0){
                    taken.push_back(temp);
                    set[i-1] = select;
                    i += 1;
                } else {
                    cout << "Invalid number.\n";
                }
            } else {
                cout << "Rotors can only be used once.\n";
            }
        }

        rotor1_f = rotors_forwards[set[0]];
        rotor2_f = rotors_forwards[set[1]];
        rotor3_f = rotors_forwards[set[2]];
        rotor1_b = rotors_backwards[set[0]];
        rotor2_b = rotors_backwards[set[1]];
        rotor3_b = rotors_backwards[set[2]];

        return;
    }

    //Probably gonna simplify this compared to the python version.
    void modify(){
        char answer, a, b;
        int temp, o1, o2, o3;
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
        cin >> answer;
        if(answer == 'y'){
            //Changing how this works because it's stupid.
            //It's smarter to just use a if-nest or something. 
            setup();
        }

        cout << "Set rotor offset? (y/n)" << "\n";
        cin >> answer;
        if(answer == 'y'){
            cout << "Enter offset for rotor 1 (0 to 25)" << "\n";
            cin >> o1;
            cout << "Enter offset for rotor 2 (0 to 25)" << "\n";
            cin >> o2;
            cout << "Enter offset for rotor 3 (0 to 25)" << "\n";
            cin >> o3;
            if(o1 > 25 || o1 < 0 || o2 > 25 || o2 < 0 || o3 > 25 || o3 < 0){
                cout << "Invalid number entered." << "\n";
                return;
            }
            offset1 = o1;
            offset2 = o2;
            offset3 = o3;
        }
        cout << "Modification complete." << "\n";
        return;
    }
};

int main(){
    char command;
    Enigma box;
    box.setup();
    while(true){
        cout << "Enigma Machine.\nEnter E to encode a message.\nEnter M to change the machines settings.\nEnter Q to quit.\n";
        cin >> command;
        if(command == 'E'){
            box.encode();
        }else if(command == 'M'){
            box.modify();
        }else if(command == 'Q'){
            break;
        }else{
            cout << "Invalid Input\n";
        }

    }

    return 0;
}