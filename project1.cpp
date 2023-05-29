#ifndef __PROJECT1_CPP__
#define __PROJECT1_CPP__

#include "project1.h"


int main(int argc, char *argv[]){

    // If there are more or less arguments than the names of the input and output files
    if (argc != 3)
    {
    // Give a useful usage message
        cout << argc << "\n";
        cerr << "Usage: " << argv[0] << " [input file]" << " [output file]" <<"\n";
        exit(1);
    }

    // Open the input file
    ifstream fin(argv[1]);

    vector<Line> program; 
    unordered_map<string, int> label_to_instr;
    unordered_map<string, int> reg_to_int;
    unordered_map<string, int> noLines;
    vector<string> labels; // temporary stores all of the labels to be associated with the next line of code
    int PC = 0; //program counter
    string curLine;

    //used Dr. Szadja's ReadWrite example (from CMSC240 Lab 1) for help with coding this read write piece
    ifstream infileinstr("instruction_parsing.txt"); //read in file for instruction parsing

    if (!infileinstr.is_open()) { //if the infile can't be read, error
        cerr << "Error, the reg parsing file could not be opened\n";
        exit(2);
    }
    string instr_key;
    int instr_value;
    while (infileinstr >> instr_key >> instr_value) {
        noLines[instr_key] = instr_value;
    }
    infileinstr.close();
    cout << "yay\n";

    // Rading the file line by line
    while (getline(fin, curLine)){

        //If there are any comments ignore them
        if (curLine.find("#") != string::npos){
            int pos = curLine.find("#");
            curLine = curLine.substr(0, pos);
        }
        
        //If the are any lines that contain a "." ignore them
        if (curLine.find(".") != string::npos){
            continue;
        }

        //If a label is found
        if (curLine.find(":") != string::npos){
            int pos = curLine.find(":");
            labels.push_back(trim(curLine.substr(0, pos)));
            curLine = curLine.substr(pos+1);
        }

        curLine = trim(curLine);

        //empty lines
        if (curLine.empty())
        {
            continue;
        }


        //For the labels in the vector labels 
        for (int i=0; i<labels.size();i++){
            label_to_instr[labels[i]] = PC;
        }

        //Eliminate the labels added in the hash map
        labels.clear();

        //Add the line to the program vector 
        Line linus;
        linus.str = curLine;
        linus.instr = PC;
        program.push_back(linus);

        int indexOfSpace = linus.str.find(" ");
        string command = linus.str.substr(0,indexOfSpace);
        
        //Increase the program counter
        PC += noLines[command];
    }
    fin.close();

        cout << "yay2\n";


  
    //used Dr. Szadja's ReadWrite example (from CMSC240 Lab 1) for help with coding this read write piece
    ifstream infilereg("regparsing_text.txt"); //read in file for reg parsing

    if (!infilereg.is_open()) { //if the infile can't be read, error
        cerr << "Error, the reg parsing file could not be opened\n";
        exit(2);
    }
    string reg_key;
    int reg_value;
    while (infilereg >> reg_key >> reg_value) {
        reg_to_int[reg_key] = reg_value;
    }
    infilereg.close();
  
    //second pass through, iterate through all of the lines to find the bin codes
    for(int i = 0; i < program.size(); i++) {
        Line linus = program[i];
        cout << linus.str << endl;
        
        int indexOfSpace = linus.str.find(" ");
        linus.command = linus.str.substr(0,indexOfSpace); //does this work for npos, in the case of syscall?
        
        if (linus.command == "addi") addi(program[i], label_to_instr, reg_to_int);
        else if (linus.command=="add") add(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="mult") mult(program[i], label_to_instr,reg_to_int);
        else if (linus.command == "div") div(program[i], label_to_instr, reg_to_int);
        else if (linus.command=="mflo") mflo(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="mfhi") mfhi(program[i], label_to_instr,reg_to_int);
        else if (linus.command=="beq") beq(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="bne") bne(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="syscall") syscall(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="sub") sub(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="sll") sll(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="srl") srl(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="lw") lw(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="sw") sw(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="j") j(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="jal") jal(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="jr") jr(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="slt") slt(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="jalr") jalr(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="li") li(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="bge") bge(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="bgt") bgt(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="sgt") sgt(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="sge") sge(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="sle") sle(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="seq") seq(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="sne") sne(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="mov") mov(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="and") mips_and(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="nor") mips_nor(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="or") mips_or(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="xor") mips_xor(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="sra") sra(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="abs") abs(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="ble") ble(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="blt") blt(program[i],label_to_instr,reg_to_int);

        else if (linus.command=="andi") mips_andi(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="not") mips_not(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="ori") mips_ori(program[i],label_to_instr,reg_to_int);
        else if (linus.command=="xori") mips_xori(program[i],label_to_instr,reg_to_int);

       


        else program[i].binCodes.push_back(1); //so the program will not seg fault later
    }



  //   ifstream ansfilestream("proj1testanswerHEX.txt"); //read in file for reg parsing
  // string temp42;
  // ofstream fountain ("largefileout.txt");

  //   print hex to console
  //   throws a seg fault if one of the commands above was not found
    // for (int i = 0; i < program.size(); i++) {
    //     for (int j = 0; j < program[i].binCodes.size(); j++) {
    //         cout << hex << program[i].binCodes[j] << "\t";
    //       fountain << hex << program[i].binCodes[j] << "\t";
    //     }
    //     //ansfilestream >> temp42;
    //     //cout << temp42 << endl;
    //     cout << endl;
    //   fountain << endl;
    // }

        cout << "yay3\n";

  
    //output to true binary file
    ofstream outfile;
    outfile.open(argv[2],ios::binary); //Open file in default mode (ascii)
    for (int i = 0; i < program.size(); i++) {
        for (int j = 0; j < program[i].binCodes.size(); j++) {
            outfile.write((char *) &program[i].binCodes[j], sizeof(int));//Write to file as true binary
        }
    }
    outfile.close();

    return 0;
}

void addi(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rt;
    int imm = -1;
    ss >> rs; //bad read for command
    ss >> rt >> rs >> imm;

    //if imm is negative, we need to add 2^16 to get it in proper form
    if (imm < 0) {
        imm += static_cast<int>(pow(2,16)); //to make sure the 2s complement works properly
    }

    rid_trailing_comma(rs);
    rid_trailing_comma(rt);

    int opcode = 8 << 26;
    int rs_code = reg_to_int.at(rs) << 21;
    int rt_code = reg_to_int.at(rt) << 16;
    linus.binCodes.push_back(imm + opcode + rs_code + rt_code);

    return;
}

void add(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rd;
    string rt;
    ss >> rs; //bad read for command to get rid of it
    ss >> rd >> rs >> rt;

    if (rs.find(",") != string::npos){
            int pos = rs.find(",");
            rs = rs.substr(0, pos);
    }

    if (rd.find(",") != string::npos){
            int pos = rd.find(",");
            rd = rd.substr(0, pos);
    }

    if (rt.find(",") != string::npos){
            int pos = rt.find(",");
            rt = rt.substr(0, pos);
    }

    rid_trailing_comma(rs);
    rid_trailing_comma(rd);
    rid_trailing_comma(rt);

    int opcode = 0 << 26;
    int shift_amt = 0 << 6;
    int add_code = 32;
    int rs_code = reg_to_int.at(rs) << 21;
    int rd_code = reg_to_int.at(rd) << 11;
    int rt_code = reg_to_int.at(rt) << 16;
    linus.binCodes.push_back(add_code + opcode + rs_code + rd_code + rt_code + shift_amt);

    return;
}


void mult(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rt;
    string comm;

    ss >> comm >> rs >> rt; //read in the instruction line

    rid_trailing_comma(rs);
    rid_trailing_comma(rt);

    int opcode = 0 << 26; //we calculate each part of the machine code separately, then add them together
    int rs_code = reg_to_int.at(rs) << 21;
    int rt_code = reg_to_int.at(rt) << 16;
    int shift_amt = 0 << 6;
    int mult_code = 24;
    
    linus.binCodes.push_back(opcode + rs_code + rt_code + shift_amt + mult_code); //we add the sum of the different parts of the machine code to our list of instructions associated with the target line

    return;
}
void div(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rt;
    string comm;

    ss >> comm >> rs >> rt;

    rid_trailing_comma(rs);
    rid_trailing_comma(rt);

    int opcode = 0 << 26;
    int rs_code = reg_to_int.at(rs) << 21;
    int rt_code = reg_to_int.at(rt) << 16;
    int shift_amt = 0 << 6;
    int arith_code = 26;
    
    linus.binCodes.push_back(opcode + rs_code + rt_code + shift_amt + arith_code);

    return;
}
void mfhi(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rd;
    string comm;

    ss >> comm >> rd;

    int opcode = 0 << 26;
    int rd_code = reg_to_int.at(rd) << 11;
    int arith_code = 16;
    
    linus.binCodes.push_back(opcode + rd_code + arith_code);

    return;
}
void mflo(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
  stringstream ss;
    ss << linus.str;
    string rd;
    string comm;

    ss >> comm >> rd;

    int opcode = 0 << 26;
    int rd_code = reg_to_int.at(rd) << 11;
    int arith_code = 18;
    
    linus.binCodes.push_back(opcode + rd_code + arith_code);

    return;
}

//set on less than
void slt(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string comm;
    string rs;
    string rt;
    string rd;
    ss >> comm >> rd>> rs >> rt; //need to read in command here

    int opcode = 0 << 26;
    int rs_code = reg_to_int.at(rs) << 21;
    int rt_code = reg_to_int.at(rt) << 16;
    int rd_code = reg_to_int.at(rd) << 11;
    int shift_amt = 0;
    int arith_code = 42;

    linus.binCodes.push_back(opcode + rs_code + rt_code + rd_code + shift_amt + arith_code);

    return;
}
void beq(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string comm;
    string rs;
    string rt;
    string label;
    ss >> comm >> rs >> rt >> label; //need to read in command here

    rid_trailing_comma(rs);
    rid_trailing_comma(rt);

    int opcode = 4 << 26;
    int rs_code = reg_to_int.at(rs) << 21;
    int rt_code = reg_to_int.at(rt) << 16;
    
    long currLine = linus.instr + 1; // adding one bc offset taken from next line
    long goalLine = label_to_instr.at(label);
    int offset = goalLine - currLine;
    if (offset <0) {
        offset += static_cast<int>(pow(2,16));

    }

    linus.binCodes.push_back(opcode + rs_code + rt_code + offset);

    return;
}
void bne(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string comm;
    string rs;
    string rt;
    string label;
    ss >> comm >> rs >> rt >> label; //need to read in command here

    rid_trailing_comma(rs);
    rid_trailing_comma(rt);

    int opcode = 5 << 26;
    int rs_code = reg_to_int.at(rs) << 21;
    int rt_code = reg_to_int.at(rt) << 16;
    
    long currLine = linus.instr + 1;
    long goalLine = label_to_instr.at(label);
    int offset = goalLine - currLine;
    if (offset <0) {
        offset += static_cast<int>(pow(2,16));
    }

    linus.binCodes.push_back(opcode + rs_code + rt_code + offset);

    return;
}
void syscall(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    linus.binCodes.push_back(12); //always 12 for syscall
    return;
}

//Sub instruction
void sub(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rd;
    string rt;
    ss >> rs; 

    //The destination, source registers
    ss >> rd >> rs >> rt;

    //Get rid of the commas
    rid_trailing_comma(rs);
    rid_trailing_comma(rd);
    rid_trailing_comma(rt);

    //Bit shift logical according to the MIPS binary converter
    int opcode = 0 << 26;
    int shift_amt = 0 << 6;
    int sub_code = 34;
    int rs_code = reg_to_int.at(rs) << 21;
    int rd_code = reg_to_int.at(rd) << 11;
    int rt_code = reg_to_int.at(rt) << 16;

    //Add the binary code line to the vector
    linus.binCodes.push_back(sub_code + opcode + rs_code + rd_code + rt_code + shift_amt);

    return;
}

//Sll instruction
void sll(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rd;
    int imm = -1;
    ss >> rs; 

    //The destination, source registers
    ss >> rd >> rs >> imm;

    //Get rid of the commas
    rid_trailing_comma(rs);
    rid_trailing_comma(rd);

    //Bit shift logical according to the MIPS binary converter
    int opcode = 0 << 26;
    int shift_amt = 0 << 21;
    int sll_code = 0;
    int rs_code = reg_to_int.at(rs) << 16;
    int rd_code = reg_to_int.at(rd) << 11;
    imm = imm << 6;

    //Add the binary code line to the vector
    linus.binCodes.push_back(sll_code + opcode + rs_code + rd_code + imm + shift_amt);

    return;
}

//Srl instruction
void srl(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rd;
    int imm = -1;
    ss >> rs; 

    //The destination, source registers
    ss >> rd >> rs >> imm;

    //Get rid of the commas
    rid_trailing_comma(rs);
    rid_trailing_comma(rd);

    //Bit shift logical according to the MIPS binary converter
    int opcode = 0 << 26;
    int shift_amt = 0 << 21;
    int srl_code = 2;
    int rs_code = reg_to_int.at(rs) << 16;
    int rd_code = reg_to_int.at(rd) << 11;
    imm = imm << 6;

    //Add the binary code line to the vector
    linus.binCodes.push_back(srl_code + opcode + rs_code + rd_code + imm + shift_amt);

    return;
}

//lw instruction
void lw(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string base;
    ss >> rs; 

    //The destination, source registers
    ss >> rs >> base;


    //Get rid of the commas
    rid_trailing_comma(rs);

    int position = base.find("(");
    string temp = base.substr(0, position);
    int offset = stoi(temp);
    base = base.substr(position+1);
    position = base.find(")");
    base = base.substr(0, position);


    //Bit shift logical according to the MIPS binary converter
    int lw_code = 35;
    int opcode = lw_code << 26;
    int base_code = reg_to_int.at(base) << 21;
    int rs_code = reg_to_int.at(rs) << 16;

    //Add the binary code line to the vector
    linus.binCodes.push_back(opcode + rs_code + base_code + offset);

    return;
}

//sw instruction
void sw(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string base;
    ss >> rs; 

    //The destination, source registers
    ss >> rs >> base;


    //Get rid of the commas
    rid_trailing_comma(rs);

    int position = base.find("(");
    string temp = base.substr(0, position);
    int offset = stoi(temp);
    base = base.substr(position+1);
    position = base.find(")");
    base = base.substr(0, position);


    //Bit shift logical according to the MIPS binary converter
    int sw_code = 43;
    int opcode = sw_code << 26;
    int base_code = reg_to_int.at(base) << 21;
    int rs_code = reg_to_int.at(rs) << 16;

    //Add the binary code line to the vector
    linus.binCodes.push_back(opcode + rs_code + base_code + offset);

    return;
}

//j instruction
void j(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string target;
    ss >> target; 

    //The destination, source registers
    ss >> target;

    //Bit shift logical according to the MIPS binary converter
    int j_code = 2;
    int opcode = j_code << 26;
    int target_code = label_to_instr.at(target);

    //Add the binary code line to the vector
    linus.binCodes.push_back(opcode + target_code);

    return;
}

//jal instruction
void jal(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string target;
    ss >> target; 

    //The destination, source registers
    ss >> target;

    //Bit shift logical according to the MIPS binary converter
    int j_code = 3;
    int opcode = j_code << 26;
    int target_code = label_to_instr.at(target);

    //Add the binary code line to the vector
    linus.binCodes.push_back(opcode + target_code);

    return;
}

//jr instruction
void jr(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    ss >> rs; 

    //The destination, source registers
    ss >> rs;

    //Bit shift logical according to the MIPS binary converter
    int opcode1 = 0 << 26;
    int rs_code = reg_to_int.at(rs) << 21;
    int opcode2 = 0 << 6;
    int jr_code = 8;

    //Add the binary code line to the vector
    linus.binCodes.push_back(opcode1 + rs_code + opcode2 + jr_code);

    return;
}

//jalr instruction
void jalr(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs="";
    string rd="";
    string instruction;
    ss >> instruction; 
  
    //The destination, source registers
    ss >> rd >> rs;
  
    if (rs.empty()){
      rs = rd;
      rd = "$ra";
    }
  
    //Get rid of the commas
    rid_trailing_comma(rs);
    rid_trailing_comma(rd);

    //Bit shift logical according to the MIPS binary converter
    int opcode = 0 << 26;
    int jalr_code = 9;
    int rs_code = reg_to_int.at(rs) << 21;
    int rd_code = reg_to_int.at(rd) << 11;

    //Add the binary code line to the vector
    linus.binCodes.push_back(opcode + rs_code + rd_code + jalr_code);

    return;
}

//li instruction
void li(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
  stringstream ss;
  ss << linus.str;
  string rs;
  string number;
  ss >> rs >> rs >> number;
  
  Line translation;
  translation.str = "addi " + rs + " $zero, " + number;
  addi(translation,label_to_instr,reg_to_int);
  
  linus.binCodes.push_back(translation.binCodes[0]);
  
  return;
}

//bge instruction
void bge(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
  stringstream ss;
  ss << linus.str;
  string comm;
  string rs;
  string rt;
  string label;
  ss >> comm >> rs >> rt >> label; //need to read in command here
  
  Line translation1;
  translation1.str = "slt $at, " + rs + " " + rt;
  slt(translation1,label_to_instr,reg_to_int);  
  linus.binCodes.push_back(translation1.binCodes[0]);

  Line translation2;
  translation2.str = "beq $at, $zero, " + label;
  translation2.instr = linus.instr + 1;
  beq(translation2,label_to_instr,reg_to_int);  
  linus.binCodes.push_back(translation2.binCodes[0]);
  
  return;
}

//bgt instruction
void bgt(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
  stringstream ss;
  ss << linus.str;
  string comm;
  string rs;
  string rt;
  string label;
  ss >> comm >> rs >> rt >> label; //need to read in command here
  
  Line translation1;
  translation1.str = "slt $at, " + rt + " " + rs;
  slt(translation1,label_to_instr,reg_to_int);  
  linus.binCodes.push_back(translation1.binCodes[0]);

  Line translation2;
  translation2.str = "bne $at, $zero, " + label;
  translation2.instr = linus.instr + 1;
  bne(translation2,label_to_instr,reg_to_int);  
  linus.binCodes.push_back(translation2.binCodes[0]);
  
  return;
}

//sgt
//sgt t0 t1 t2 should be translated to:
//slt t0 t2 t1
void sgt(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string comm;
    string rs;
    string rt;
    string rd;
    ss >> comm >> rd>> rs >> rt; //need to read in command here


    Line translation1;
    translation1.str = "slt " + rd + " " + rt + " " + rs;
    slt(translation1,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation1.binCodes[0]);

}

//sge
//sge t0 t1 t2 should be translated to:
//slt t0 t1 t2
//addi at $zero 1
//sub t0 at t0
void sge(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string comm;
    string rs;
    string rt;
    string rd;
    ss >> comm >> rd>> rs >> rt; //need to read in command here


    Line translation1;
    translation1.str = "slt " + rd + " " + rs + " " + rt;
    slt(translation1,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation1.binCodes[0]);

    Line translation2;
    translation2.str = "addi $at $zero 1";
    addi(translation2,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation2.binCodes[0]);

    Line translation3;
    translation3.str = "sub " + rd + " $at " + rd;
    sub(translation3,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation3.binCodes[0]);

}

//sle
//sle should be translated to:
//NOT sgt =>
//sgt t0 t1 t2
//addi at $zero 1
//sub t0 at t0
void sle(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string comm;
    string rs;
    string rt;
    string rd;
    ss >> comm >> rd>> rs >> rt; //need to read in command here


    Line translation1;
    translation1.str = "sgt " + rd + " " + rs + " " + rt;
    sgt(translation1,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation1.binCodes[0]);

    Line translation2;
    translation2.str = "addi $at $zero 1";
    addi(translation2,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation2.binCodes[0]);

    Line translation3;
    translation3.str = "sub " + rd + " $at " + rd;
    sub(translation3,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation3.binCodes[0]);

}

//and
void mips_and(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rd;
    string rt;
    ss >> rs; //bad read for command to get rid of it
    ss >> rd >> rs >> rt;

    rid_trailing_comma(rs);
    rid_trailing_comma(rd);
    rid_trailing_comma(rt);

    int opcode = 0 << 26;
    int shift_amt = 0 << 6;
    int and_code = 36;
    int rs_code = reg_to_int.at(rs) << 21;
    int rd_code = reg_to_int.at(rd) << 11;
    int rt_code = reg_to_int.at(rt) << 16;
    linus.binCodes.push_back(and_code + opcode + rs_code + rd_code + rt_code + shift_amt);

    return;
}



//nor
void mips_nor(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rd;
    string rt;
    ss >> rs; //bad read for command to get rid of it
    ss >> rd >> rs >> rt;

    rid_trailing_comma(rs);
    rid_trailing_comma(rd);
    rid_trailing_comma(rt);

    int opcode = 0 << 26;
    int shift_amt = 0 << 6;
    int and_code = 39;
    int rs_code = reg_to_int.at(rs) << 21;
    int rd_code = reg_to_int.at(rd) << 11;
    int rt_code = reg_to_int.at(rt) << 16;
    linus.binCodes.push_back(and_code + opcode + rs_code + rd_code + rt_code + shift_amt);

    return;
}

//or
void mips_or(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rd;
    string rt;
    ss >> rs; //bad read for command to get rid of it
    ss >> rd >> rs >> rt;

    rid_trailing_comma(rs);
    rid_trailing_comma(rd);
    rid_trailing_comma(rt);

    int opcode = 0 << 26;
    int shift_amt = 0 << 6;
    int and_code = 37;
    int rs_code = reg_to_int.at(rs) << 21;
    int rd_code = reg_to_int.at(rd) << 11;
    int rt_code = reg_to_int.at(rt) << 16;
    linus.binCodes.push_back(and_code + opcode + rs_code + rd_code + rt_code + shift_amt);

    return;
}

//xor
void mips_xor(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rd;
    string rt;
    ss >> rs; //bad read for command to get rid of it
    ss >> rd >> rs >> rt;

    rid_trailing_comma(rs);
    rid_trailing_comma(rd);
    rid_trailing_comma(rt);

    int opcode = 0 << 26;
    int shift_amt = 0 << 6;
    int and_code = 38;
    int rs_code = reg_to_int.at(rs) << 21;
    int rd_code = reg_to_int.at(rd) << 11;
    int rt_code = reg_to_int.at(rt) << 16;
    linus.binCodes.push_back(and_code + opcode + rs_code + rd_code + rt_code + shift_amt);

    return;
}

//seq rd rs rt
//seq should be translated to:
//slt rd rs rt
//sgt at rs rt
//or rd rd at // from sne
//addi at $zero 1
//sub rd at rd
void seq(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string comm;
    string rs;
    string rt;
    string rd;
    ss >> comm >> rd>> rs >> rt; //need to read in command here


    Line translation1;
    translation1.str = "slt " + rd + " " + rs + " " + rt;
    slt(translation1,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation1.binCodes[0]);

    Line translation2;
    translation2.str = "sgt $at " + rs + " " + rt;
    sgt(translation2,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation2.binCodes[0]);

    Line translation3;
    translation3.str = "or " + rd + " " + rd + " $at";
    mips_or(translation3,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation3.binCodes[0]);

    Line translation4;
    translation4.str = "addi $at $zero 1";
    addi(translation4,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation4.binCodes[0]);

    Line translation5;
    translation5.str = "sub " + rd + " $at " + rd;
    sub(translation5,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation5.binCodes[0]);



}


//sne
//sne should be translated to:
//slt rd rs rt
//sgt ra rs rt
//or rd rd ra
void sne(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string comm;
    string rs;
    string rt;
    string rd;
    ss >> comm >> rd>> rs >> rt; //need to read in command here


    Line translation1;
    translation1.str = "slt " + rd + " " + rs + " " + rt;
    slt(translation1,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation1.binCodes[0]);

    Line translation2;
    translation2.str = "sgt $at " + rs + " " + rt;
    sgt(translation2,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation2.binCodes[0]);

    Line translation3;
    translation3.str = "or " + rd + " " + rd + " $at";
    mips_or(translation3,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation3.binCodes[0]);

}

//mov
//mov should be translated as:
//addi rd rs 0
void mov(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string comm;
    string rs;
    string rd;
    ss >> comm >> rd>> rs; //need to read in command here


    Line translation1;
    translation1.str = "addi " + rd + " " + rs + " 0";
    addi(translation1,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation1.binCodes[0]);

}



//xori
void mips_xori(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rt;
    int imm = -1;
    ss >> rs; //bad read for command
    ss >> rt >> rs >> imm;

    //if imm is negative, we need to add 2^16 to get it in proper form
    if (imm < 0) {
        imm += static_cast<int>(pow(2,16)); //to make sure the 2s complement works properly
    }

    rid_trailing_comma(rs);
    rid_trailing_comma(rt);

    int opcode = 14 << 26;
    int rs_code = reg_to_int.at(rs) << 21;
    int rt_code = reg_to_int.at(rt) << 16;
    linus.binCodes.push_back(imm + opcode + rs_code + rt_code);

    return;
}

//andi
void mips_andi(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rt;
    int imm = -1;
    ss >> rs; //bad read for command
    ss >> rt >> rs >> imm;

    //if imm is negative, we need to add 2^16 to get it in proper form
    if (imm < 0) {
        imm += static_cast<int>(pow(2,16)); //to make sure the 2s complement works properly
    }

    rid_trailing_comma(rs);
    rid_trailing_comma(rt);

    int opcode = 12 << 26;
    int rs_code = reg_to_int.at(rs) << 21;
    int rt_code = reg_to_int.at(rt) << 16;
    linus.binCodes.push_back(imm + opcode + rs_code + rt_code);

    return;
}

//ori
void mips_ori(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rt;
    int imm = -1;
    ss >> rs; //bad read for command
    ss >> rt >> rs >> imm;

    //if imm is negative, we need to add 2^16 to get it in proper form
    if (imm < 0) {
        imm += static_cast<int>(pow(2,16)); //to make sure the 2s complement works properly
    }

    rid_trailing_comma(rs);
    rid_trailing_comma(rt);

    int opcode = 13 << 26;
    int rs_code = reg_to_int.at(rs) << 21;
    int rt_code = reg_to_int.at(rt) << 16;
    linus.binCodes.push_back(imm + opcode + rs_code + rt_code);

    return;
}

//not rd rs
//not should be translated as:
//xori rd rs -1
//lol nvm on this extra stuff: //srl at rs 16
                                //xori at at -1
                            //sll at 16
                            //add rd rd at
void mips_not(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string comm;
    string rs;
    string rd;
    ss >> comm >> rd>> rs; //need to read in command here

    //cout << "Tr1" << endl;
    Line translation1;
    translation1.str = "xori " + rd + " " + rs + " -1";
    mips_xori(translation1,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation1.binCodes[0]);

    //cout << "Tr2" << endl;

    //not needed and actually doesn't work
    // Line translation2;
    // translation2.str = "srl $at " + rs + " 16";
    // srl(translation2,label_to_instr,reg_to_int);  
    // linus.binCodes.push_back(translation2.binCodes[0]);

    // //cout << "Tr3" << endl;

    // Line translation3;
    // translation3.str = "xori $at $at -1";
    // mips_xori(translation3,label_to_instr,reg_to_int);  
    // linus.binCodes.push_back(translation3.binCodes[0]);

    // //cout << "Tr4" << endl;

    // Line translation4;
    // translation4.str = "sll $at $at 16";
    // sll(translation4,label_to_instr,reg_to_int);  
    // linus.binCodes.push_back(translation4.binCodes[0]);

    // //cout << "Tr5" << endl;
    // //cout << rd << endl;

    // Line translation5;
    // translation5.str = "add " + rd + " " + rd + " $at";
    // add(translation5,label_to_instr,reg_to_int);  
    // linus.binCodes.push_back(translation5.binCodes[0]);

    //cout << "Tr7" << endl;


}


//sra instruction
void sra(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rd;
    int imm = -1;
    ss >> rs; 

    //The destination, source registers
    ss >>rd >> rs >> imm;

    //Get rid of the commas
    rid_trailing_comma(rs);
    rid_trailing_comma(rd);

    //Bit shift logical according to the MIPS binary converter
    int opcode = 0 << 26;
    int shift_amt = 0 << 21;
    int sra_code = 3;
    int rs_code = reg_to_int.at(rs) << 16;
    int rd_code = reg_to_int.at(rd) << 11;
    imm = imm << 6;

    //Add the binary code line to the vector
    linus.binCodes.push_back(sra_code + opcode + rs_code + rd_code + imm + shift_amt);

    return;
}

//abs
void abs(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
    stringstream ss;
    ss << linus.str;
    string rs;
    string rd;
    string comm;
    ss >>comm >>rd>> rs; //need to read in command here

    Line translation1;
    translation1.str = "sra $at " + rs + " 31";
    sra(translation1,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation1.binCodes[0]);


    Line translation2;
    translation2.str = "xor " +  rs + " " + rs + " $at";
    mips_xor(translation2,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation2.binCodes[0]);


    Line translation3;
    translation3.str = "sub " + rd + " " + rs + " $at";
    sub(translation3,label_to_instr,reg_to_int);  
    linus.binCodes.push_back(translation3.binCodes[0]);

    return;

}

//ble instruction
void ble(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
  stringstream ss;
  ss << linus.str;
  string comm;
  string rs;
  string rt;
  string label;
  ss >> comm >> rs >> rt >> label; //need to read in command here
  
  Line translation1;
  translation1.str = "slt $at, " + rt + " " + rs;
  slt(translation1,label_to_instr,reg_to_int);  
  linus.binCodes.push_back(translation1.binCodes[0]);

  Line translation2;
  translation2.str = "beq $at, $zero, " + label;
  translation2.instr = linus.instr + 1;
  beq(translation2,label_to_instr,reg_to_int);  
  linus.binCodes.push_back(translation2.binCodes[0]);
  
  return;
}

//blt instruction
void blt(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int) {
  stringstream ss;
  ss << linus.str;
  string comm;
  string rs;
  string rt;
  string label;
  ss >> comm >> rs >> rt >> label; //need to read in command here
  
  Line translation1;
  translation1.str = "slt $at, " + rt + " " + rs;
  slt(translation1,label_to_instr,reg_to_int);  
  linus.binCodes.push_back(translation1.binCodes[0]);

  Line translation2;
  translation2.str = "bne $at, $zero, " + label;
  translation2.instr = linus.instr + 1;
  bne(translation2,label_to_instr,reg_to_int);  
  linus.binCodes.push_back(translation2.binCodes[0]);
  
  return;
}



#endif