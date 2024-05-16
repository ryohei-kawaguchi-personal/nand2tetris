// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//// Replace this comment with your code.
@i
M=0
@sum
M=0
(LOOP)
    @i
    D=M
    @R1
    D=D-M   // D=M[i]-R1
    @STORE
    D;JGE   // D>=0 つまり、 M[i]>=R1ならば、ENDへJUMP

    @R0
    D=M
    @sum
    M=M+D

    @i
    M=M+1   // M[i]++
    
    @LOOP
    0;JMP
(STORE)
    @sum
    D=M
    @R2
    M=D //R2に積の結果を出力する
(END)
    @END
    0;JMP