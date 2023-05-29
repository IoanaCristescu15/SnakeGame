#ifndef __PROJECT1_H__
#define __PROJECT1_H__

#include <math.h>       /* pow */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>
using namespace std;

//trim function copied from:
//https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/

const std::string WHITESPACE = " \n\r\t\f\v";
 
std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

void rid_trailing_comma(string& s) {
  if (s.find(",") != string::npos){
    int pos = s.find(",");
    s = s.substr(0, pos);
  }

}

struct Line {
    string str; //store actual string value of program line
    int instr; //instruction number
    vector<int> binCodes; //hold actual binary codes
    string command; //store command that we are doing in that line
};

void addi(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void add(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);

void mult(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void div(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void mfhi(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void mflo(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void slt(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void beq(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void bne(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void syscall(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);

void sub(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void sll(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void srl(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void lw(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void sw(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void j(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void jal(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void jr(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void jalr(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);

void li(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void bge(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void bgt(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void ble(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void blt(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void abs(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);



void sgt(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void sge(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void sle(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void seq(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void sne(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void mov(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void mips_and(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void mips_nor(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void mips_or(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void mips_xor(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void mips_xori(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void mips_andi(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void mips_ori(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void mips_not(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);


void ble(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void blt(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void abs(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);
void sra(Line& linus, const unordered_map<string, int>& label_to_instr, const unordered_map<string, int>& reg_to_int);


#endif