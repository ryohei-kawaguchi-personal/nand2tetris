// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.
(DRAWING_LOOP)
    @KBD
    D=M
    @ONKBD
    D;JEQ   // D=0ならばCLOOPへJUMP
    @draw_value
    M=-1

    (DRAWING)
        @r
        M=0
        @32
        D=A
        @R0
        M=D
        (RLOOP)
            @c
            M=0

            // r*32
            @r
            D=M
            @R1
            M=D
            @Mult
            0;JMP
            (CLOOP)
                // M[draw_address]=SCREEN+c+r*32
                @SCREEN
                D=A
                @c
                D=D+M
                @R2
                D=D+M
                @draw_address
                M=D

                // draw
                @draw_value
                D=M
                @draw_address
                A=M
                M=D

                @c
                MD=M+1  // M[c]++
                @32
                D=A-D   // D=32-M[c]
                @CLOOP
                D;JGT   // D>0 つまり、 32>M[c]ならば、CLOOPへJUMP
            @r
            MD=M+1  // M[r]++
            @256
            D=A-D   // D=256-M[r]
            @RLOOP  // D>0 つまり、 256>M[r]ならば、RLOOPへJUMP
            D;JGT
    @DRAWING_LOOP
    0;JMP

(ONKBD)
@draw_value
M=0
@DRAWING
0;JMP

(Mult)
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
        D;JGE   // D>=0 つまり、 M[i]>=R1ならば、STOREへJUMP

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
        @CLOOP
        0;JMP