LCALL mainAdd
end:  JMP end
mainAdd:  .DA main
main: LDAI 0
STA $offset
LDAI 0
STA $offset2
LDAI 0
STA $offset3
LDAI 0
STA $timer
loopstart0: LDAI 1
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI loopdn0
LDARAM $timer
PUSHA
LDAI 10
MOVAB
POPA
CMP
JCI ifcnt2
JMP ifskp2
ifcnt2: CALL draw1
JMP if2skp2
ifskp2: LDARAM $timer
PUSHA
LDAI 20
MOVAB
POPA
CMP
JCI ifcnt1
JMP ifskp1
ifcnt1: CALL draw2
JMP if2skp1
ifskp1: LDARAM $timer
PUSHA
LDAI 30
MOVAB
POPA
CMP
JCI ifcnt0
JMP ifskp0
ifcnt0: CALL draw3
JMP if2skp0
ifskp0: CALL draw4
if2skp0: if2skp1: if2skp2: FLIP
LDARAM $offset
LDBI 1
ADDA
STA $offset
LDARAM $timer
LDBI 1
ADDA
STA $timer
LDAI 39
PUSHA
LDARAM $timer
MOVAB
POPA
CMP
JCI ifcnt3
JMP ifskp3
ifcnt3: LDAI 0
STA $timer
ifskp3: JMP loopstart0
loopdn0: LDAI 0
RET
draw1: LDAI 0
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
draw2: LDAI 0
STA $y
LDAI 0
STA $addr
LDAI 0
STA $col
loopstart4: LDARAM $y
PUSHA
LDAI 75
MOVAB
POPA
CMP
JCI loopcnt4
JMP loopdn4
loopcnt4: LDAI 0
STA $x
loopstart3: LDARAM $x
PUSHA
LDAI 100
MOVAB
POPA
CMP
JCI loopcnt3
JMP loopdn3
loopcnt3: LDARAM $addr
VMARA
LDARAM $col
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
JMP loopstart3
loopdn3: LDARAM $addr
LDBI 28
ADDA
STA $addr
LDARAM $y
LDBI 1
ADDA
STA $y
LDARAM $col
LDBI 3
ADDA
STA $col
JMP loopstart4
loopdn4: RET
draw3: LDAI 0
STA $y
LDAI 0
STA $addr
loopstart6: LDARAM $y
PUSHA
LDAI 75
MOVAB
POPA
CMP
JCI loopcnt6
JMP loopdn6
loopcnt6: LDAI 0
STA $x
loopstart5: LDARAM $x
PUSHA
LDAI 100
MOVAB
POPA
CMP
JCI loopcnt5
JMP loopdn5
loopcnt5: LDARAM $addr
VMARA
LDARAM $x
LDBRAM $x
ADDA
LDBRAM $y
ADDA
LDBRAM $offset2
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
JMP loopstart5
loopdn5: LDARAM $addr
LDBI 28
ADDA
STA $addr
LDARAM $y
LDBI 1
ADDA
STA $y
JMP loopstart6
loopdn6: LDARAM $offset2
LDBI 4
SUBA
STA $offset2
RET
draw4: LDAI 0
STA $y
LDAI 0
STA $addr
LDAI 0
STA $col
loopstart8: LDARAM $y
PUSHA
LDAI 75
MOVAB
POPA
CMP
JCI loopcnt8
 RJMP loopdn8
loopcnt8: LDAI 0
STA $x
loopstart7: LDARAM $x
PUSHA
LDAI 100
MOVAB
POPA
CMP
JCI loopcnt7
 RJMP loopdn7
loopcnt7: LDARAM $addr
VMARA
LDARAM $x
LDBRAM $offset
ADDA
LDBRAM $col
ADDA
LDBRAM $offset3
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
JMP loopstart7
loopdn7: LDARAM $addr
LDBI 28
ADDA
STA $addr
LDARAM $y
LDBI 1
ADDA
STA $y
LDARAM $col
LDBI 32
ADDA
STA $col
JMP loopstart8
loopdn8: LDARAM $offset3
LDBI 32
ADDA
STA $offset3
RET
