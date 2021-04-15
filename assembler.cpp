// Shane Brown UIN: 827002065

#include <iostream>
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

string removeCommentsAndWhitespace(string s1) {
    for (long unsigned int i = 0; i < s1.length(); i++) {
        if (s1[i] == '/') {
            s1.erase(i, s1.length()); // Erasing any comment within the line
        }
    }
    //Erase whitespace in line
    s1.erase(remove(s1.begin(), s1.end(), ' '), s1.end());
    return s1;
}

bool isLabel(string s1) {
    if (s1[0] == '(' && s1[s1.length()-1] == ')') {
        return true;
    }
    return false;
}

bool SymTableContains(string s1, map<string, int> &ST) {
    map<string, int>::iterator it;
            for (it = ST.begin(); it != ST.end(); it++) {
                if (s1 == it->first) {
                    return true;
                }
            }
            return false;
}

bool isInstruction(string s1) {
    if (s1.empty() || s1[0] == '/') {
        return false;
    }
    return true;
}

bool isNotNumber(string s1) {
    for (long unsigned int i = 0; i < s1.length(); i++) {
        if (!isdigit(s1[i])) {
            return true; //NOT a number
        }
    }
    return false; //IS a number
}

bool isValidAInstruction(string s1) {
    if (s1[0] != '@') { // Has to start with @
        return false;
    }
    return true; // otherwise, true
}

bool isValidCInstruction(string s1) {
    bool equalsign = false; bool semicolon = false;
    for (long unsigned int i = 0; i < s1.length(); i++) {
        if (s1[i] == '=') {
            equalsign = true;
        }
        if (s1[i] == ';') {
            semicolon = true;
        }
    }
    if (!isValidAInstruction(s1) && (!isLabel(s1))) {
        return true;
    }

    if (equalsign == false && semicolon == false) {
        return false;
    }
    return true;
}

string toBinary15Bit(int s1) {  
    int number = s1;
    int count = 0;
    string binary;

    while(count != 15) {
        if (number != 0) {
            binary = (number % 2 == 0 ? "0" : "1") + binary;
            number = number / 2;
            count++;
        }
        else if (number == 0) {
            binary = "0" + binary;
            count++;
        }
    }
    return binary;
}

string aInstruction(string s1, map<string, int> ST) {
    string dropAt = s1.substr(1,s1.length()-1); // Remove @
    string binary;
    int addr;
    if (!isNotNumber(s1)) {
        int num = stoi(dropAt);
        if (num > 0) {
            binary = toBinary15Bit(num);
            return ("0" + binary);
        }
    }
    //In Symbol Table
    addr = ST[dropAt];
    binary = toBinary15Bit(addr);
    return ("0" + binary);

}

string cInstruction(string s1, map<string,string> compTable, map<string,string> destTable, map<string,string> jumpTable) {
    vector<string> v1;
    string prefix = "111";
    string dest = "";
    string comp = "";
    string jump = "";

   bool equalsign = false; bool semicolon = false;
    for (long unsigned int i = 0; i < s1.length(); i++) {
        if (s1[i] == '=') {
            equalsign = true;
        }
        if (s1[i] == ';') {
            semicolon = true;
        }
    }

if (equalsign == true && semicolon == false) {
    //dest and comp
    long unsigned int equalPos = s1.find("=");
    if (equalPos != string::npos) {
        v1.push_back(s1.substr(0, equalPos)); //dest
        v1.push_back(s1.substr(equalPos+1, s1.length()-equalPos-1)); //comp
    }
    dest = destTable[v1[0]];
    comp = compTable[v1[1]];
    jump = "000";
}
else if (equalsign == false && semicolon == true) {
    //comp and jump
    long unsigned int semicolonPos = s1.find(";");
    if (semicolonPos != string::npos) {
        v1.push_back(s1.substr(0, semicolonPos)); //dest
        v1.push_back(s1.substr(semicolonPos+1, s1.length()-semicolonPos-1)); //jump
    }
    dest = "000";
    comp = compTable[v1[0]];
    jump = jumpTable[v1[1]];
}
else if (equalsign == true && semicolon == true) {
    //dest, comp, and jump
    long unsigned int equalPos = s1.find("=");
    long unsigned int semicolonPos = s1.find(";");
    if (equalPos != string::npos) {
        v1.push_back(s1.substr(0, equalPos)); //dest
        if (semicolonPos != string::npos) {
            v1.push_back(s1.substr(equalPos+1, semicolonPos-equalPos-1)); //comp
            v1.push_back(s1.substr(semicolonPos+1, s1.length()-semicolonPos-1)); //jump
        }
    }
    dest = destTable[v1[0]];
    comp = compTable[v1[1]];
    jump = jumpTable[v1[2]];
}

else { // if no "=" or ";"
    v1.push_back(s1);
    dest = "000";
    jump = "000";
    comp = compTable[v1[0]];
}
    return (prefix + comp + dest + jump);
}

map<string, int> createSymbolTable(string inputFileName) {
    //Add the Predefined symbols
    map<string, int> SymTable;
    SymTable.insert({"SP", 0});
    SymTable.insert({"LCL", 1});
    SymTable.insert({"ARG",2});
    SymTable.insert({"THIS", 3});
    SymTable.insert({"THAT", 4});
    SymTable.insert({"R0", 0});
    SymTable.insert({"R1", 1});
    SymTable.insert({"R2", 2});
    SymTable.insert({"R3", 3});
    SymTable.insert({"R4", 4});
    SymTable.insert({"R5", 5});
    SymTable.insert({"R6", 6});
    SymTable.insert({"R7", 7});
    SymTable.insert({"R8", 8});
    SymTable.insert({"R9", 9});
    SymTable.insert({"R10", 10});
    SymTable.insert({"R11", 11});
    SymTable.insert({"R12", 12});
    SymTable.insert({"R13", 13});
    SymTable.insert({"R14", 14});
    SymTable.insert({"R15", 15});
    SymTable.insert({"SCREEN", 16384});
    SymTable.insert({"KBD", 24576});

    int pc = 0;
    ifstream iss(inputFileName); // opening the input file

    //Check if the file opened correctly
    if (!iss.is_open()) {
        cout << "Error: File could not open." << endl;
        exit(1);
    }

    //LABELS
    string currLine;
    string clean;
    string label;
    while(getline(iss, currLine)) {
        clean = removeCommentsAndWhitespace(currLine);
        if (isLabel(clean)) {
            // remove parentheses
            label = clean.substr(1, clean.length()-2);
            //make sure not in symbol table
            if (!SymTableContains(label, SymTable)) {
                SymTable.insert({label, pc});
            }
        }
        if (isInstruction(clean)) {
            pc++;
        }
    }
    iss.close();

    //VARIABLES
    ifstream iss2(inputFileName);
    int nextaddr = 16;
    string aInstructionVal;
    while(getline(iss2, currLine)) {
        clean = removeCommentsAndWhitespace(currLine);
        if (isValidAInstruction(clean)) {
            aInstructionVal = clean.substr(1, clean.length()-1);
            if (isNotNumber(aInstructionVal) && !SymTableContains(aInstructionVal, SymTable)) {
                // add to symbol table
                SymTable.insert({aInstructionVal, nextaddr});
                nextaddr++;
            }
        }
    }
    return SymTable;
}

map<string, string> createCompTable(string inputFileName) {
    map<string, string> compTable;
    //COMP Table
    //a=0
    compTable.insert({"0", "0101010"});
    compTable.insert({"1", "0111111"});
    compTable.insert({"-1", "0111010"});
    compTable.insert({"D", "0001100"});
    compTable.insert({"A", "0110000"});
    compTable.insert({"!D", "0001101"});
    compTable.insert({"!A", "0110001"});
    compTable.insert({"-D", "0001111"});
    compTable.insert({"-A", "0110011"});
    compTable.insert({"D+1", "0011111"});
    compTable.insert({"A+1", "0110111"});
    compTable.insert({"D-1", "0001110"});
    compTable.insert({"A-1", "0110010"});
    compTable.insert({"D+A", "0000010"});
    compTable.insert({"D-A", "0010011"});
    compTable.insert({"A-D", "0000111"});
    compTable.insert({"D&A", "0000000"});
    compTable.insert({"D|A", "0010101"});
    
    //a=1
    compTable.insert({"M", "1110000"});
    compTable.insert({"!M", "1110001"});
    compTable.insert({"-M", "1110011"});
    compTable.insert({"M+1", "1110111"});
    compTable.insert({"M-1", "1110010"});
    compTable.insert({"D+M", "1000010"});
    compTable.insert({"D-M", "1010011"});
    compTable.insert({"M-D", "1000111"});
    compTable.insert({"D&M", "1000000"});
    compTable.insert({"D|M", "1010101"});
    return compTable;
}

map<string, string> createDestTable(string inputFileName) {
    map<string, string> destTable;
    //DEST Table
    destTable.insert({"M", "001"});
    destTable.insert({"D", "010"});
    destTable.insert({"MD", "011"});
    destTable.insert({"A", "100"});
    destTable.insert({"AM", "101"});
    destTable.insert({"AD", "110"});
    return destTable;
}

map<string, string> createJumpTable(string inputFileName) {
    map<string, string> jumpTable;

    //JUMP Table
    jumpTable.insert({"JGT", "001"});
    jumpTable.insert({"JEQ", "010"});
    jumpTable.insert({"JGE", "011"});
    jumpTable.insert({"JLT", "100"});
    jumpTable.insert({"JNE", "101"});
    jumpTable.insert({"JLE", "110"});
    jumpTable.insert({"JMP", "111"});
    return jumpTable;
}

int main(int argc, char *argv[]) {
    string inputFile;
    string outputFile;

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " [Input File]" << endl;
        exit(1);
    }

    inputFile = argv[1];

    //Variables and Labels
    map<string, int> symbolTable = createSymbolTable(inputFile);
    //instructions
    map<string, string> compTable = createCompTable(inputFile);
    map<string, string> destTable = createDestTable(inputFile);
    map<string, string> jumpTable = createJumpTable(inputFile);

    ifstream asmFile(inputFile); // open file
    if (!asmFile.is_open()) {
        cout << "Error: File could not open." << endl;
        exit(1);
    }
    outputFile = inputFile.substr(0, inputFile.length()-4) + ".hack";
    ofstream binaryOut(outputFile);

    string currentLine, cleanLine, binary;
    while (getline(asmFile, currentLine)) {
        cleanLine = removeCommentsAndWhitespace(currentLine);
        if (cleanLine.empty()) {
            continue;
        }
        if (isValidAInstruction(cleanLine)) {
            binary = aInstruction(cleanLine, symbolTable);
            binaryOut << binary << endl;
            continue;
        }
        if (isValidCInstruction(cleanLine)) {
            binary = cInstruction(cleanLine, compTable, destTable, jumpTable);
            binaryOut << binary << endl;
            continue;
        }
    }
asmFile.close();
binaryOut.close();
}