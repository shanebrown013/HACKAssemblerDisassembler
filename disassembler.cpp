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

map<string, string> createCompTable(string inputFileName) {
    map<string, string> compTable;
    //COMP Table
    //a=0
    compTable.insert({"0101010", "0"});
    compTable.insert({"0111111", "1"});
    compTable.insert({"0111010", "-1"});
    compTable.insert({"0001100", "D"});
    compTable.insert({"0110000", "A"});
    compTable.insert({"0001101", "!D"});
    compTable.insert({"0110001", "!A"});
    compTable.insert({"0001111", "-D"});
    compTable.insert({"0110011", "-A"});
    compTable.insert({"0011111", "D+1"});
    compTable.insert({"0110111", "A+1"});
    compTable.insert({"0001110", "D-1"});
    compTable.insert({"0110010", "A-1"});
    compTable.insert({"0000010", "D+A"});
    compTable.insert({"0010011", "D-A"});
    compTable.insert({"0000111", "A-D"});
    compTable.insert({"0000000", "D&A"});
    compTable.insert({"0010101", "D|A"});
    
    //a=1
    compTable.insert({"1110000", "M"});
    compTable.insert({"1110001", "!M"});
    compTable.insert({"1110011", "-M"});
    compTable.insert({"1110111", "M+1"});
    compTable.insert({"1110010", "M-1"});
    compTable.insert({"1000010", "D+M"});
    compTable.insert({"1010011", "D-M"});
    compTable.insert({"1000111", "M-D"});
    compTable.insert({"1000000", "D&M"});
    compTable.insert({"1010101", "D|M"});
    return compTable;
}

map<string, string> createDestTable(string inputFileName) {
    map<string, string> destTable;
    //DEST Table
    destTable.insert({"", ""});
    destTable.insert({"001", "M"});
    destTable.insert({"010", "D"});
    destTable.insert({"011", "MD"});
    destTable.insert({"100", "A"});
    destTable.insert({"101", "AM"});
    destTable.insert({"110", "AD"});
    return destTable;
}

map<string, string> createJumpTable(string inputFileName) {
    map<string, string> jumpTable;

    //JUMP Table
    jumpTable.insert({"", ""});
    jumpTable.insert({"001", "JGT"});
    jumpTable.insert({"010", "JEQ"});
    jumpTable.insert({"011", "JGE"});
    jumpTable.insert({"100", "JLT"});
    jumpTable.insert({"101", "JNE"});
    jumpTable.insert({"110", "JLE"});
    jumpTable.insert({"111", "JMP"});
    return jumpTable;
}

string binaryToNum(string s1) {
    int number = stoi(s1, nullptr, 2);
    string binaryToASM = to_string(number);
    return binaryToASM;
}

int main(int argc, char *argv[]) {
    string inputFile;
    string outputFile;
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " [Input File]" << endl;
        exit(1);
    }

    //instructions
    map<string, string> compTable = createCompTable(inputFile);
    map<string, string> destTable = createDestTable(inputFile);
    map<string, string> jumpTable = createJumpTable(inputFile);

    inputFile = argv[1];

    ifstream binaryFile(inputFile); // open file
    if (!binaryFile.is_open()) {
        cout << "Error: File could not open." << endl;
        exit(1);
    }
    outputFile = inputFile.substr(0, inputFile.length()-4) + ".asm";
    ofstream asmOut(outputFile);

    string currLine, binaryToASM;
    string comp, dest, jump;

    while (getline(binaryFile, currLine)) {
        if (currLine.substr(0,3) == "111") {
            //C-Instruction
                comp = compTable[currLine.substr(3,7)];
                dest = destTable[currLine.substr(10,3)];
                jump = jumpTable[currLine.substr(13,3)];
                //cases
                if (!dest.empty() && jump.empty()) {
                    //dest and comp
                    asmOut << dest << "=" << comp << endl;
                }
                else if (dest.empty() && (!jump.empty())) {
                    // comp and jump
                    asmOut << comp << ";" << jump << endl;
                }
                else if (!dest.empty() && !jump.empty()) {
                    //dest comp and jump
                    asmOut << dest << "=" << comp << ";" << jump << endl;
                }
                else if (dest.empty() && jump.empty()) { // ONLY comp
                    asmOut << comp << endl;
                }
        } else {
            //A-Instruction
            asmOut << "@";
            binaryToASM = binaryToNum(currLine);
            asmOut << binaryToASM << endl;
        }
    }
}