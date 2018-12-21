#The program generated currently does not work correctly. This is just an example on how to use the generating functions
#include <iostream>
#include <vector>
#include <cstdint>
#include <iomanip>

using program = std::vector<uint8_t>;

void singleReg(program& prog, uint8_t opcode, uint8_t reg0) {
  prog.push_back(opcode);
  prog.push_back(reg0);
}

void doubleReg(program& prog, uint8_t opcode, uint8_t reg0, uint8_t reg1) {
  singleReg(prog, opcode, reg0);
  prog.push_back(reg1);
}

void tripleReg(program& prog, uint8_t opcode, uint8_t reg0, uint8_t reg1, uint8_t reg2) {
  doubleReg(prog, opcode, reg0, reg1);
  prog.push_back(reg2);
}

void loadi32(program& prog, uint8_t reg0, uint32_t val) {
  singleReg(prog, 0b1, reg0);
  for(uint8_t i=0; i<4; ++i) {
    prog.push_back( (val>>i*8) & 0xFF );
  }
}

namespace op {
  uint8_t LOADI32=0b1, STORE=0b10, LOAD=0b11;
  uint8_t ZERO=0b100, NEGATE=0b101, ADD=0b110, SUB=0b111, RANDOM=0b1000;
  uint8_t MUL=0b1001, DIV=0b1010, MODULO=0b1011, INC=0b1100, DEC=0b1101;
  uint8_t ABS=0b1110, FLOOR=0b1111;
  uint8_t BEQ=0b10000, BNEQ=0b10001, BLT=0b10010, BGEQ=0b10011, JMP=0b10100;
  uint8_t BAND=0b10101, BOR=0b10110, BXOR=0b10111, BNOT=0b11000;
  uint8_t HALT=0b11001;
}

void printProg(program& prog) {
  std::cout << std::setbase(16) << std::setfill('0') << std::setw(2);
  for(auto b : prog) {
    std::cout << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(b);
  }
  std::cout << std::endl;
  std::cout << std::setbase(10);
}

int main(int argc, char* argv[]) {
  program p;

  loadi32(p, 0, 65536);
  doubleReg(p, op::STORE, 0, 0);
  doubleReg(p, op::INC, 1, 0);
  doubleReg(p, op::INC, 2, 1);
  doubleReg(p, op::INC, 3, 2);

  auto index = p.size();
  
  doubleReg(p, op::LOAD, 4, 2);
  doubleReg(p, op::STORE, 0, 4);
  doubleReg(p, op::LOAD, 4, 3);
  doubleReg(p, op::STORE, 1, 4);
  
  loadi32(p, 4, 2048);
  singleReg(p, op::JMP, 4);

  printProg(p);
  return 0;
}
