LCALL mainAdd
end:  JMP end
nine_loc: .DA nine
eight_loc: .DA eight
seven_loc: .DA seven
six_loc: .DA six
five_loc: .DA five
four_loc: .DA four
three_loc: .DA three
two_loc: .DA two
one_loc: .DA one
drawNum_loc: .DA drawNum
mainAdd:  .DA main
eightNinetySix:  .DW 3 128
fortyThousand:  .DW 156 64
numZero: .DA numZeroLoc
numOne: .DA numOneLoc
numTwo: .DA numTwoLoc
numThree: .DA numThreeLoc
numFour: .DA numFourLoc
numFive: .DA numFiveLoc
numSix: .DA numSixLoc
numSeven: .DA numSevenLoc
numEight: .DA numEightLoc
numNine: .DA numNineLoc
main: LDAI 1
STA $num
LDAI 0
STA $num2
LDAI 0
STA $series
LDAI 0
STA $counter
LDAI 0
STA $padNumWith2Zeroes
loopstart0: LDAI 1
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI loopdn0
LDAI 16
STA $col
CALL clearScreen
LDAI 75
STA $drawX
LDAI 50
STA $drawY
LDARAM $num
STA $num2Draw
 LCALL drawNum_loc
LDAI 4
STA $col
LDAI 75
STA $drawX
LDAI 32
STA $drawY
LDARAM $series
STA $num2Draw
 LCALL drawNum_loc
LDAI 20
STA $col
LDAI 75
STA $drawX
LDAI 15
STA $drawY
LDARAM $counter
STA $num2Draw
 LCALL drawNum_loc
FLIP
LDARAM $counter
LDBI 1
ADDA
STA $counter
LDARAM $series
LDBRAM $counter
ADDA
STA $series
LDACMA fortyThousand
PUSHA
LDARAM $num
MOVAB
POPA
CMP
JCI ifcnt0
JMP ifskp0
ifcnt0: LDAI 1
STA $num
LDAI 0
STA $num2
JMP if2skp0
ifskp0: LDARAM $num2
STA $temp
LDARAM $num
STA $num2
LDARAM $num
LDBRAM $temp
ADDA
STA $num
if2skp0: JMP loopstart0
loopdn0: LDAI 0
RET
clearScreen: LDAI 0
STA $b
LDAI 0
STA $c
loopstart2: LDARAM $b
PUSHA
LDAI 75
MOVAB
POPA
CMP
JCI loopcnt2
JMP loopdn2
loopcnt2: LDAI 0
STA $a
loopstart1: LDARAM $a
PUSHA
LDAI 100
MOVAB
POPA
CMP
JCI loopcnt1
JMP loopdn1
loopcnt1: LDARAM $c
VMARA
LDAI 0
MOVAC
VRCC
LDARAM $c
LDBI 1
ADDA
STA $c
LDARAM $a
LDBI 1
ADDA
STA $a
JMP loopstart1
loopdn1: LDARAM $c
LDBI 28
ADDA
STA $c
LDARAM $b
LDBI 1
ADDA
STA $b
JMP loopstart2
loopdn2: RET
mult: LDARAM $multx
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifcnt2
JMP ifskp2
ifcnt2: LDAI 0
RET
JMP if2skp2
ifskp2: LDARAM $multy
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifcnt1
JMP ifskp1
ifcnt1: LDAI 0
RET
ifskp1: if2skp2: LDARAM $multy
PUSHA
LDARAM $multx
MOVAB
POPA
CMP
JCI ifcnt3
JMP ifskp3
ifcnt3: LDARAM $multx
STA $multtemp
LDARAM $multy
STA $multx
LDARAM $multtemp
STA $multy
ifskp3: LDAI 0
STA $multacc
loopstart3: LDAI 0
PUSHA
LDARAM $multx
MOVAB
POPA
CMP
JCI loopcnt3
JMP loopdn3
loopcnt3: LDARAM $multacc
LDBRAM $multy
ADDA
STA $multacc
LDARAM $multx
LDBI 1
SUBA
STA $multx
JMP loopstart3
loopdn3: LDARAM $multacc
RET
divide: LDAI 0
STA $Q
LDARAM $N
STA $R
loopstart4: LDARAM $R
PUSHA
LDARAM $D
MOVAB
POPA
CMP
JCI loopdn4
LDARAM $Q
LDBI 1
ADDA
STA $Q
LDARAM $R
LDBRAM $D
SUBA
STA $R
JMP loopstart4
loopdn4: RET
zero: LDARAM $drawAddr
LDBI 1
SUBA
STA $drawAddr
LDAI 0
STA $singleCounter
LDAI 0
STA $drawY
loopstart6: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
JCI loopcnt6
 RJMP loopdn6
loopcnt6: LDAI 0
STA $drawX
loopstart5: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
JCI loopcnt5
 RJMP loopdn5
loopcnt5: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numZero
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt4
 RJMP ifskp4
ifcnt4: LDARAM $singleCounter
LDBCMA numZero
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
CALL mult
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp4: LDARAM $singleCounter
LDBI 1
ADDA
STA $singleCounter
LDARAM $drawAddr
LDBI 1
ADDA
STA $drawAddr
LDARAM $drawX
LDBI 1
ADDA
STA $drawX
JMP loopstart5
loopdn5: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
JMP loopstart6
loopdn6: LDARAM $drawAddr
LDBCMA eightNinetySix
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
one: LDAI 0
STA $singleCounter
LDAI 0
STA $drawY
loopstart8: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt8
 RJMP loopdn8
loopcnt8: LDAI 0
STA $drawX
loopstart7: LDARAM $drawX
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt7
 RJMP loopdn7
loopcnt7: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numOne
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt5
 RJMP ifskp5
ifcnt5: LDARAM $singleCounter
LDBCMA numOne
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
CALL mult
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp5: LDARAM $singleCounter
LDBI 1
ADDA
STA $singleCounter
LDARAM $drawAddr
LDBI 1
ADDA
STA $drawAddr
LDARAM $drawX
LDBI 1
ADDA
STA $drawX
 RJMP loopstart7
loopdn7: LDARAM $drawAddr
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart8
loopdn8: LDARAM $drawAddr
LDBCMA eightNinetySix
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
two: LDARAM $drawAddr
LDBI 1
SUBA
STA $drawAddr
LDAI 0
STA $singleCounter
LDAI 0
STA $drawY
loopstart10: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt10
 RJMP loopdn10
loopcnt10: LDAI 0
STA $drawX
loopstart9: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt9
 RJMP loopdn9
loopcnt9: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numTwo
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt6
 RJMP ifskp6
ifcnt6: LDARAM $singleCounter
LDBCMA numTwo
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
CALL mult
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp6: LDARAM $singleCounter
LDBI 1
ADDA
STA $singleCounter
LDARAM $drawAddr
LDBI 1
ADDA
STA $drawAddr
LDARAM $drawX
LDBI 1
ADDA
STA $drawX
 RJMP loopstart9
loopdn9: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart10
loopdn10: LDARAM $drawAddr
LDBCMA eightNinetySix
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
three: LDAI 0
STA $singleCounter
LDAI 0
STA $drawY
loopstart12: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt12
 RJMP loopdn12
loopcnt12: LDAI 0
STA $drawX
loopstart11: LDARAM $drawX
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt11
 RJMP loopdn11
loopcnt11: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numThree
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt7
 RJMP ifskp7
ifcnt7: LDARAM $singleCounter
LDBCMA numThree
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
CALL mult
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp7: LDARAM $singleCounter
LDBI 1
ADDA
STA $singleCounter
LDARAM $drawAddr
LDBI 1
ADDA
STA $drawAddr
LDARAM $drawX
LDBI 1
ADDA
STA $drawX
 RJMP loopstart11
loopdn11: LDARAM $drawAddr
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart12
loopdn12: LDARAM $drawAddr
LDBCMA eightNinetySix
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
four: LDARAM $drawAddr
LDBI 1
SUBA
STA $drawAddr
LDAI 0
STA $singleCounter
LDAI 0
STA $drawY
loopstart14: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt14
 RJMP loopdn14
loopcnt14: LDAI 0
STA $drawX
loopstart13: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt13
 RJMP loopdn13
loopcnt13: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numFour
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt8
 RJMP ifskp8
ifcnt8: LDARAM $singleCounter
LDBCMA numFour
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
CALL mult
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp8: LDARAM $singleCounter
LDBI 1
ADDA
STA $singleCounter
LDARAM $drawAddr
LDBI 1
ADDA
STA $drawAddr
LDARAM $drawX
LDBI 1
ADDA
STA $drawX
 RJMP loopstart13
loopdn13: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart14
loopdn14: LDARAM $drawAddr
LDBCMA eightNinetySix
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
five: LDARAM $drawAddr
LDBI 1
SUBA
STA $drawAddr
LDAI 0
STA $singleCounter
LDAI 0
STA $drawY
loopstart16: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt16
 RJMP loopdn16
loopcnt16: LDAI 0
STA $drawX
loopstart15: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt15
 RJMP loopdn15
loopcnt15: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numFive
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt9
 RJMP ifskp9
ifcnt9: LDARAM $singleCounter
LDBCMA numFive
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
CALL mult
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp9: LDARAM $singleCounter
LDBI 1
ADDA
STA $singleCounter
LDARAM $drawAddr
LDBI 1
ADDA
STA $drawAddr
LDARAM $drawX
LDBI 1
ADDA
STA $drawX
 RJMP loopstart15
loopdn15: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart16
loopdn16: LDARAM $drawAddr
LDBCMA eightNinetySix
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
six: LDARAM $drawAddr
LDBI 1
SUBA
STA $drawAddr
LDAI 0
STA $singleCounter
LDAI 0
STA $drawY
loopstart18: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt18
 RJMP loopdn18
loopcnt18: LDAI 0
STA $drawX
loopstart17: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt17
 RJMP loopdn17
loopcnt17: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numSix
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt10
 RJMP ifskp10
ifcnt10: LDARAM $singleCounter
LDBCMA numSix
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
CALL mult
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp10: LDARAM $singleCounter
LDBI 1
ADDA
STA $singleCounter
LDARAM $drawAddr
LDBI 1
ADDA
STA $drawAddr
LDARAM $drawX
LDBI 1
ADDA
STA $drawX
 RJMP loopstart17
loopdn17: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart18
loopdn18: LDARAM $drawAddr
LDBCMA eightNinetySix
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
seven: LDARAM $drawAddr
LDBI 1
SUBA
STA $drawAddr
LDAI 0
STA $singleCounter
LDAI 0
STA $drawY
loopstart20: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt20
 RJMP loopdn20
loopcnt20: LDAI 0
STA $drawX
loopstart19: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt19
 RJMP loopdn19
loopcnt19: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numSeven
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt11
 RJMP ifskp11
ifcnt11: LDARAM $singleCounter
LDBCMA numSeven
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
CALL mult
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp11: LDARAM $singleCounter
LDBI 1
ADDA
STA $singleCounter
LDARAM $drawAddr
LDBI 1
ADDA
STA $drawAddr
LDARAM $drawX
LDBI 1
ADDA
STA $drawX
 RJMP loopstart19
loopdn19: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart20
loopdn20: LDARAM $drawAddr
LDBCMA eightNinetySix
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
eight: LDARAM $drawAddr
LDBI 1
SUBA
STA $drawAddr
LDAI 0
STA $singleCounter
LDAI 0
STA $drawY
loopstart22: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt22
 RJMP loopdn22
loopcnt22: LDAI 0
STA $drawX
loopstart21: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt21
 RJMP loopdn21
loopcnt21: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numEight
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt12
 RJMP ifskp12
ifcnt12: LDARAM $singleCounter
LDBCMA numEight
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
CALL mult
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp12: LDARAM $singleCounter
LDBI 1
ADDA
STA $singleCounter
LDARAM $drawAddr
LDBI 1
ADDA
STA $drawAddr
LDARAM $drawX
LDBI 1
ADDA
STA $drawX
 RJMP loopstart21
loopdn21: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart22
loopdn22: LDARAM $drawAddr
LDBCMA eightNinetySix
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
nine: LDAI 0
STA $singleCounter
LDAI 0
STA $drawY
loopstart24: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt24
 RJMP loopdn24
loopcnt24: LDAI 0
STA $drawX
loopstart23: LDARAM $drawX
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt23
 RJMP loopdn23
loopcnt23: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numNine
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt13
 RJMP ifskp13
ifcnt13: LDARAM $singleCounter
LDBCMA numNine
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
CALL mult
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp13: LDARAM $singleCounter
LDBI 1
ADDA
STA $singleCounter
LDARAM $drawAddr
LDBI 1
ADDA
STA $drawAddr
LDARAM $drawX
LDBI 1
ADDA
STA $drawX
 RJMP loopstart23
loopdn23: LDARAM $drawAddr
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart24
loopdn24: LDARAM $drawAddr
LDBCMA eightNinetySix
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
drawNum: LDARAM $drawY
STA $multx
LDAI 128
STA $multy
CALL mult
LDBRAM $drawX
ADDA
STA $drawAddr
LDARAM $padNumWith2Zeroes
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt14
 RJMP ifskp14
ifcnt14: CALL zero
CALL zero
ifskp14: LDARAM $num2Draw
STA $N
LDAI 10
STA $D
CALL divide
LDARAM $Q
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt16
 RJMP ifskp16
ifcnt16: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt15
 RJMP ifskp15
ifcnt15: CALL zero
RET
ifskp15: ifskp16: loopstart25: LDAI 0
PUSHA
LDARAM $Q
MOVAB
POPA
CMP
 RJCI loopcnt25
 RJMP loopdn25
loopcnt25: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt17
 RJMP ifskp17
ifcnt17: CALL zero
 RJMP drawNumAgain
ifskp17: LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt18
 RJMP ifskp18
ifcnt18: LCALL one_loc
 RJMP drawNumAgain
ifskp18: LDARAM $R
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt19
 RJMP ifskp19
ifcnt19: LCALL two_loc
 RJMP drawNumAgain
ifskp19: LDARAM $R
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJZI ifcnt20
 RJMP ifskp20
ifcnt20: LCALL three_loc
 RJMP drawNumAgain
ifskp20: LDARAM $R
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJZI ifcnt21
 RJMP ifskp21
ifcnt21: LCALL four_loc
 RJMP drawNumAgain
ifskp21: LDARAM $R
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJZI ifcnt22
 RJMP ifskp22
ifcnt22: LCALL five_loc
 RJMP drawNumAgain
ifskp22: LDARAM $R
PUSHA
LDAI 6
MOVAB
POPA
CMP
 RJZI ifcnt23
 RJMP ifskp23
ifcnt23: LCALL six_loc
 RJMP drawNumAgain
ifskp23: LDARAM $R
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJZI ifcnt24
 RJMP ifskp24
ifcnt24: LCALL seven_loc
 RJMP drawNumAgain
ifskp24: LDARAM $R
PUSHA
LDAI 8
MOVAB
POPA
CMP
 RJZI ifcnt25
 RJMP ifskp25
ifcnt25: LCALL eight_loc
 RJMP drawNumAgain
 RJMP if2skp25
ifskp25: LCALL nine_loc
if2skp25: drawNumAgain: LDARAM $Q
STA $N
CALL divide
 RJMP loopstart25
loopdn25: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt26
 RJMP ifskp26
ifcnt26: CALL zero
RET
ifskp26: LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt27
 RJMP ifskp27
ifcnt27: LCALL one_loc
RET
ifskp27: LDARAM $R
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt28
 RJMP ifskp28
ifcnt28: LCALL two_loc
RET
ifskp28: LDARAM $R
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJZI ifcnt29
 RJMP ifskp29
ifcnt29: LCALL three_loc
RET
ifskp29: LDARAM $R
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJZI ifcnt30
 RJMP ifskp30
ifcnt30: LCALL four_loc
RET
ifskp30: LDARAM $R
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJZI ifcnt31
 RJMP ifskp31
ifcnt31: LCALL five_loc
RET
ifskp31: LDARAM $R
PUSHA
LDAI 6
MOVAB
POPA
CMP
 RJZI ifcnt32
 RJMP ifskp32
ifcnt32: LCALL six_loc
RET
ifskp32: LDARAM $R
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJZI ifcnt33
 RJMP ifskp33
ifcnt33: LCALL seven_loc
RET
ifskp33: LDARAM $R
PUSHA
LDAI 8
MOVAB
POPA
CMP
 RJZI ifcnt34
 RJMP ifskp34
ifcnt34: LCALL eight_loc
RET
 RJMP if2skp34
ifskp34: LCALL nine_loc
if2skp34: RET
numZeroLoc: .DW 0 0
.DW 0 3
.DW 0 3
.DW 0 2
.DW 0 0
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 3
.DW 0 0
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 3
.DW 0 1
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 3
.DW 0 1
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 3
.DW 0 1
.DW 0 3
.DW 0 2
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 3
.DW 0 3
.DW 0 1
.DW 0 0
numOneLoc: .DW 0 0
.DW 0 0
.DW 0 2
.DW 0 2
.DW 0 0
.DW 0 1
.DW 0 3
.DW 0 2
.DW 0 1
.DW 0 2
.DW 0 2
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 2
numTwoLoc: .DW 0 0
.DW 0 1
.DW 0 3
.DW 0 2
.DW 0 1
.DW 0 1
.DW 0 3
.DW 0 1
.DW 0 1
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 3
.DW 0 1
.DW 0 0
.DW 0 1
.DW 0 3
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 3
.DW 0 3
.DW 0 3
.DW 0 2
numThreeLoc: .DW 0 0
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 3
.DW 0 2
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 3
.DW 0 3
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 3
.DW 0 1
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 3
.DW 0 3
.DW 0 0
numFourLoc: .DW 0 0
.DW 0 0
.DW 0 0
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 3
.DW 0 3
.DW 0 1
.DW 0 0
.DW 0 2
.DW 0 2
.DW 0 3
.DW 0 1
.DW 0 0
.DW 0 3
.DW 0 0
.DW 0 3
.DW 0 1
.DW 0 2
.DW 0 3
.DW 0 3
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 3
.DW 0 0
numFiveLoc: .DW 0 0
.DW 0 3
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 3
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 3
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 3
.DW 0 2
.DW 0 3
.DW 0 2
.DW 0 0
.DW 0 3
.DW 0 1
.DW 0 0
.DW 0 3
.DW 0 3
.DW 0 2
.DW 0 0
numSixLoc: .DW 0 0
.DW 0 2
.DW 0 3
.DW 0 2
.DW 0 0
.DW 0 1
.DW 0 3
.DW 0 0
.DW 0 3
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 3
.DW 0 2
.DW 0 1
.DW 0 3
.DW 0 0
.DW 0 3
.DW 0 2
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 3
.DW 0 0
numSevenLoc: .DW 0 2
.DW 0 3
.DW 0 3
.DW 0 3
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 3
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 3
.DW 0 2
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 0
numEightLoc: .DW 0 0
.DW 0 2
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 1
.DW 0 3
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 1
.DW 0 3
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 1
.DW 0 3
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 1
.DW 0 3
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 3
.DW 0 0
numNineLoc: .DW 0 0
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 3
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 3
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 3
.DW 0 3
.DW 0 1
.DW 0 2
.DW 0 3
.DW 0 0
.DW 0 3
.DW 0 3
.DW 0 0
