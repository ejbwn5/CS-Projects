LCALL mainAdd
end:  JMP end
mainAdd:  .DA main
main: LDAI 0
STA $offset
loopstart0: LDAI 1
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI loopdn0
CALL draw
FLIP
LDARAM $offset
LDBI 1
ADDA
STA $offset
JMP loopstart0
loopdn0: LDAI 0
RET
RET
draw: LDAI 0
STA $y
LDAI 0
STA $addr
loopstart2: LDARAM $y
PUSHA
LDAI 75
MOVAB
POPA
CMP
JCI loopcnt2
JMP loopdn2
loopcnt2: LDAI 0
STA $x
loopstart1: LDARAM $x
PUSHA
LDAI 100
MOVAB
POPA
CMP
JCI loopcnt1
JMP loopdn1
loopcnt1: LDARAM $addr
VMARA
LDARAM $x
LDBRAM $y
ADDA
LDBRAM $offset
ADDA
MOVAC
VRCC
LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $x
LDBI 1
ADDA
STA $x
JMP loopstart1
loopdn1: LDARAM $addr
LDBI 28
ADDA
STA $addr
LDARAM $y
LDBI 1
ADDA
STA $y
JMP loopstart2
loopdn2: RET
RET
