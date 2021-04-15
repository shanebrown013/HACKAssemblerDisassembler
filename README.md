# HACKAssemblerDisassembler

Using C++, I built a HACK assembler and disassembler that can read in input files (in HACK language) and it will convert into its corresponding HACK language. The assembler will read in the symbolic HACK assembly language and convert it into HACK machine code. In addition, the disassembler does the opposite and reads a 15-bit binary number and converts it back into the symbolic assembly language


To run my program, frist compile with g++ (g++ assembler.cpp and g++ disassembler.cpp), then type "./a.out [inputFileName].txt". A file will be generated with the correct content. The assembler generates a .hack file and the disassembler generates a .asm file. I included the test files, but *PUT THEM IN THE SAME DIRECTORY TO RUN THEM.*
