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
zero_loc: .DA zero
divide_loc: .DA divide
getDist_loc: .DA getDist
getOppositeDir_loc: .DA getOppositeDir
isValidSpace_loc: .DA isValidSpace
refreshInput_loc: .DA refreshInput
mult_loc: .DA mult
drawRect_loc: .DA drawRect
drawNum_loc: .DA drawNum
drawPlayer_loc: .DA drawPlayer
drawGhost_loc: .DA drawGhost
drawDots_loc: .DA drawDots
drawMap_loc: .DA drawMap
calcOrangeTarget_loc: .DA calcOrangeTarget
calcBlueTarget_loc: .DA calcBlueTarget
calcPinkTarget_loc: .DA calcPinkTarget
calcRedTarget_loc: .DA calcRedTarget
mainAdd:  .DA main
houseExitX:  .DW 0 49
houseExitY:  .DW 0 30
maxInt:  .DW 255 255
eightNinetySix:  .DW 3 128
randAdd:  .DW 1 201
timeMultiplier:  .DW 0 105
timeMultiplier2:  .DW 0 75
timeMultiplier3:  .DW 1 44
dotsPos: .DA dotsPosLoc
map: .DA mapLoc
legalSpaces: .DA legalSpacesLoc
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
redTarg: .DW &redTarg[2]
blueTarg: .DW &blueTarg[2]
pinkTarg: .DW &pinkTarg[2]
orangeTarg: .DW &orangeTarg[2]
redPos: .DW &redPos[2]
bluePos: .DW &bluePos[2]
pinkPos: .DW &pinkPos[2]
orangePos: .DW &orangePos[2]
dotExist: .DW &dotExist[164]
main: LDAI 0
STA $ghostMode
LDAI 0
STA $stage
LDAI 49
STA $playerX
LDAI 53
STA $playerY
LDAI 0
STA $lastDir
LDAI 0
STA $pacmanMouth
LDAI 0
STA $frameCounter
LDAI 3
STA $redDir
LDAI 3
STA $blueDir
LDAI 3
STA $pinkDir
LDAI 3
STA $orangeDir
LDAI 0
LDBCMA redPos
ADDC
PUSHC
LDAI 49
POPC
STARAMC
LDAI 1
LDBCMA redPos
ADDC
PUSHC
LDAI 29
POPC
STARAMC
LDAI 0
LDBCMA pinkPos
ADDC
PUSHC
LDAI 49
POPC
STARAMC
LDAI 1
LDBCMA pinkPos
ADDC
PUSHC
LDAI 35
POPC
STARAMC
LDAI 0
LDBCMA bluePos
ADDC
PUSHC
LDAI 45
POPC
STARAMC
LDAI 1
LDBCMA bluePos
ADDC
PUSHC
LDAI 35
POPC
STARAMC
LDAI 0
LDBCMA orangePos
ADDC
PUSHC
LDAI 53
POPC
STARAMC
LDAI 1
LDBCMA orangePos
ADDC
PUSHC
LDAI 35
POPC
STARAMC
 LCALL calcRedTarget_loc
 LCALL calcPinkTarget_loc
 LCALL calcBlueTarget_loc
 LCALL calcOrangeTarget_loc
LDAI 0
STA $blueReleased
LDAI 0
STA $orangeReleased
LDAI 0
STA $x
loopstart0: LDARAM $x
PUSHA
LDAI 164
MOVAB
POPA
CMP
JCI loopcnt0
JMP loopdn0
loopcnt0: LDARAM $x
LDBCMA dotExist
ADDC
PUSHC
LDAI 1
POPC
STARAMC
LDARAM $x
LDBI 1
ADDA
STA $x
JMP loopstart0
loopdn0: LDAI 0
STA $eaten
LDAI 0
STA $score
LDAI 0
STA $pacmanDir
 LCALL drawMap_loc
 LCALL drawDots_loc
LDAI 0
LDBCMA redPos
ADDC
LDARAMC
STA $x
LDAI 1
LDBCMA redPos
ADDC
LDARAMC
STA $y
LDAI 48
STA $col
 LCALL drawGhost_loc
LDAI 0
LDBCMA bluePos
ADDC
LDARAMC
STA $x
LDAI 1
LDBCMA bluePos
ADDC
LDARAMC
STA $y
LDAI 15
STA $col
 LCALL drawGhost_loc
LDAI 0
LDBCMA pinkPos
ADDC
LDARAMC
STA $x
LDAI 1
LDBCMA pinkPos
ADDC
LDARAMC
STA $y
LDAI 59
STA $col
 LCALL drawGhost_loc
LDAI 0
LDBCMA orangePos
ADDC
LDARAMC
STA $x
LDAI 1
LDBCMA orangePos
ADDC
LDARAMC
STA $y
LDAI 52
STA $col
 LCALL drawGhost_loc
 LCALL drawPlayer_loc
LDAI 95
STA $drawX
LDAI 0
STA $drawY
LDAI 20
STA $col
LDAI 1
STA $padNumWith1Zeroes
LDARAM $score
STA $num2Draw
 LCALL drawNum_loc
FLIP
LDAIO
STA $io
loopstart1: LDARAM $io
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI loopcnt1
JMP loopdn1
loopcnt1: LDAIO
STA $io
JMP loopstart1
loopdn1: loopstart7: LDAI 1
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI loopdn7l0
LDAI 65
STA $x
LDAI 0
STA $y
LDAI 35
STA $dx
LDAI 7
STA $dy
LDAI 0
STA $col
 LCALL drawRect_loc
LDAI 128
STA $multx
LDARAM $playerY
STA $multy
 LCALL mult_loc
LDBRAM $playerX
ADDA
STA $addr
LDAI 0
STA $x
loopstart2: LDARAM $x
PUSHA
LDAI 164
MOVAB
POPA
CMP
 RJCI loopcnt2
 RJMP loopdn2
loopcnt2: LDARAM $x
LDBCMA dotExist
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp1
LDARAM $x
LDBCMA dotsPos
ADDC
LDACMC
PUSHA
LDARAM $addr
MOVAB
POPA
CMP
 RJZI ifcnt0
 RJMP ifskp0
ifcnt0: LDARAM $x
LDBCMA dotExist
ADDC
PUSHC
LDAI 0
POPC
STARAMC
LDARAM $eaten
LDBI 1
ADDA
STA $eaten
LDARAM $score
LDBI 1
ADDA
STA $score
 RJMP dotCheckExit
ifskp0: ifskp1: LDARAM $x
LDBI 1
ADDA
STA $x
 RJMP loopstart2
loopdn2: dotCheckExit: LDAI 0
STA $moved
 LCALL refreshInput_loc
LDARAM $playerX
STA $testX
LDARAM $playerY
STA $testY
LDARAM $up
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp3
tryUp: LDARAM $testY
LDBI 1
SUBA
STA $testY
 LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp2
LDARAM $playerY
LDBI 1
SUBA
STA $playerY
LDAI 1
STA $lastDir
LDAI 1
STA $moved
LDAI 1
STA $pacmanDir
ifskp2: ifskp3: LDARAM $moved
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt6
 RJMP ifskp6
ifcnt6: LDARAM $playerX
STA $testX
LDARAM $playerY
STA $testY
LDARAM $dn
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp5
tryDn: LDARAM $testY
LDBI 1
ADDA
STA $testY
 LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp4
LDARAM $playerY
LDBI 1
ADDA
STA $playerY
LDAI 3
STA $lastDir
LDAI 1
STA $moved
LDAI 3
STA $pacmanDir
ifskp4: ifskp5: ifskp6: LDARAM $moved
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt9
 RJMP ifskp9
ifcnt9: LDARAM $playerX
STA $testX
LDARAM $playerY
STA $testY
LDARAM $rt
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp8
tryRt: LDARAM $testX
LDBI 1
ADDA
STA $testX
 LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp7
LDARAM $playerX
LDBI 1
ADDA
STA $playerX
LDAI 2
STA $lastDir
LDAI 1
STA $moved
LDAI 2
STA $pacmanDir
ifskp7: ifskp8: ifskp9: LDARAM $moved
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt12
 RJMP ifskp12
ifcnt12: LDARAM $playerX
STA $testX
LDARAM $playerY
STA $testY
LDARAM $lf
RJMP loopdn7l0skp
loopdn7l0: RJMP loopdn7l1
loopdn7l0skp: PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp11
tryLf: LDARAM $testX
LDBI 1
SUBA
STA $testX
 LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp10
LDARAM $playerX
LDBI 1
SUBA
STA $playerX
LDAI 4
STA $lastDir
LDAI 1
STA $moved
LDAI 4
STA $pacmanDir
ifskp10: ifskp11: ifskp12: LDARAM $moved
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt17
 RJMP ifskp17
ifcnt17: LDARAM $lastDir
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp16
LDARAM $playerX
STA $testX
LDARAM $playerY
STA $testY
LDAI 1
STA $up
LDARAM $lastDir
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt13
 RJMP ifskp13
ifcnt13: LDAI 0
STA $lastDir
 RJMP tryUp
ifskp13: LDARAM $lastDir
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt14
 RJMP ifskp14
ifcnt14: LDAI 0
STA $lastDir
 RJMP tryRt
ifskp14: LDARAM $lastDir
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJZI ifcnt15
 RJMP ifskp15
ifcnt15: LDAI 0
STA $lastDir
 RJMP tryDn
ifskp15: LDAI 0
STA $lastDir
 RJMP tryLf
ifskp16: ifskp17: LDAI 0
LDBCMA redPos
ADDC
LDARAMC
PUSHA
LDAI 20
MOVAB
POPA
CMP
 RJZI ifcnt19
 RJMP ifskp19
ifcnt19: LDAI 0
LDBCMA redPos
ADDC
PUSHC
LDAI 78
POPC
STARAMC
 RJMP if2skp19
ifskp19: LDAI 0
LDBCMA redPos
ADDC
LDARAMC
PUSHA
LDAI 78
MOVAB
POPA
CMP
 RJZI ifcnt18
 RJMP ifskp18
ifcnt18: LDAI 0
LDBCMA redPos
ADDC
PUSHC
LDAI 20
POPC
STARAMC
ifskp18: if2skp19: LDAI 0
LDBCMA bluePos
ADDC
LDARAMC
PUSHA
LDAI 20
MOVAB
POPA
CMP
 RJZI ifcnt21
 RJMP ifskp21
ifcnt21: LDAI 0
LDBCMA bluePos
ADDC
PUSHC
LDAI 78
POPC
STARAMC
 RJMP if2skp21
ifskp21: LDAI 0
LDBCMA bluePos
ADDC
LDARAMC
PUSHA
LDAI 78
MOVAB
POPA
CMP
 RJZI ifcnt20
 RJMP ifskp20
ifcnt20: LDAI 0
LDBCMA bluePos
ADDC
PUSHC
LDAI 20
POPC
STARAMC
ifskp20: if2skp21: LDAI 0
LDBCMA orangePos
ADDC
LDARAMC
PUSHA
LDAI 20
MOVAB
POPA
CMP
 RJZI ifcnt23
 RJMP ifskp23
ifcnt23: LDAI 0
LDBCMA orangePos
ADDC
PUSHC
LDAI 78
POPC
STARAMC
 RJMP if2skp23
ifskp23: LDAI 0
LDBCMA orangePos
ADDC
LDARAMC
PUSHA
LDAI 78
MOVAB
POPA
CMP
 RJZI ifcnt22
 RJMP ifskp22
ifcnt22: LDAI 0
LDBCMA orangePos
ADDC
PUSHC
LDAI 20
POPC
STARAMC
ifskp22: if2skp23: LDAI 0
LDBCMA pinkPos
ADDC
RJMP loopdn7l1skp
loopdn7l1: RJMP loopdn7l2
loopdn7l1skp: LDARAMC
PUSHA
LDAI 20
MOVAB
POPA
CMP
 RJZI ifcnt25
 RJMP ifskp25
ifcnt25: LDAI 0
LDBCMA pinkPos
ADDC
PUSHC
LDAI 78
POPC
STARAMC
 RJMP if2skp25
ifskp25: LDAI 0
LDBCMA pinkPos
ADDC
LDARAMC
PUSHA
LDAI 78
MOVAB
POPA
CMP
 RJZI ifcnt24
 RJMP ifskp24
ifcnt24: LDAI 0
LDBCMA pinkPos
ADDC
PUSHC
LDAI 20
POPC
STARAMC
ifskp24: if2skp25: LDARAM $playerX
PUSHA
LDAI 20
MOVAB
POPA
CMP
 RJZI ifcnt27
 RJMP ifskp27
ifcnt27: LDAI 78
STA $playerX
 RJMP if2skp27
ifskp27: LDARAM $playerX
PUSHA
LDAI 78
MOVAB
POPA
CMP
 RJZI ifcnt26
 RJMP ifskp26
ifcnt26: LDAI 20
STA $playerX
ifskp26: if2skp27: LDACMA maxInt
STA $dist
LDARAM $redDir
STA $dirForOpp
 LCALL getOppositeDir_loc
STA $dirForOpp
LDAI 0
STA $e
loopstart3: LDARAM $e
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt3
 RJMP loopdn3
loopcnt3: LDARAM $e
PUSHA
LDARAM $dirForOpp
MOVAB
POPA
CMP
 RJZI ifskp34
LDAI 0
LDBCMA redPos
ADDC
LDARAMC
STA $testX
LDAI 1
LDBCMA redPos
ADDC
LDARAMC
STA $testY
LDARAM $e
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt30
 RJMP ifskp30
ifcnt30: LDARAM $testY
LDBI 1
SUBA
STA $testY
 RJMP if2skp30
ifskp30: LDARAM $e
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt29
 RJMP ifskp29
ifcnt29: LDARAM $testX
LDBI 1
ADDA
STA $testX
 RJMP if2skp29
ifskp29: LDARAM $e
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt28
 RJMP ifskp28
ifcnt28: LDARAM $testY
LDBI 1
ADDA
STA $testY
 RJMP if2skp28
ifskp28: LDARAM $testX
LDBI 1
SUBA
STA $testX
if2skp28: if2skp29: if2skp30: LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp33
LDARAM $e
PUSHA
LDARAM $redDir
MOVAB
POPA
CMP
 RJZI ifskp31
 LCALL calcRedTarget_loc
ifskp31: LDARAM $testX
STA $a
LDAI 0
LDBCMA redTarg
ADDC
LDARAMC
STA $c
LDARAM $testY
STA $b
LDAI 1
LDBCMA redTarg
ADDC
LDARAMC
STA $d
 LCALL getDist_loc
STA $temp
LDARAM $temp
PUSHA
LDARAM $dist
MOVAB
POPA
CMP
 RJCI ifcnt32
 RJMP ifskp32
ifcnt32: LDARAM $temp
STA $dist
LDARAM $e
STA $redDir
ifskp32: ifskp33: ifskp34: LDARAM $e
LDBI 1
ADDA
STA $e
 RJMP loopstart3
loopdn3: LDACMA maxInt
STA $dist
LDARAM $pinkDir
STA $dirForOpp
 LCALL getOppositeDir_loc
STA $dirForOpp
LDAI 0
STA $e
loopstart4: LDARAM $e
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt4
 RJMP loopdn4
loopcnt4: LDARAM $e
PUSHA
LDARAM $dirForOpp
RJMP loopdn7l2skp
loopdn7l2: RJMP loopdn7l3
loopdn7l2skp: MOVAB
POPA
CMP
 RJZI ifskp41
LDAI 0
LDBCMA pinkPos
ADDC
LDARAMC
STA $testX
LDAI 1
LDBCMA pinkPos
ADDC
LDARAMC
STA $testY
LDARAM $e
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt37
 RJMP ifskp37
ifcnt37: LDARAM $testY
LDBI 1
SUBA
STA $testY
 RJMP if2skp37
ifskp37: LDARAM $e
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt36
 RJMP ifskp36
ifcnt36: LDARAM $testX
LDBI 1
ADDA
STA $testX
 RJMP if2skp36
ifskp36: LDARAM $e
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt35
 RJMP ifskp35
ifcnt35: LDARAM $testY
LDBI 1
ADDA
STA $testY
 RJMP if2skp35
ifskp35: LDARAM $testX
LDBI 1
SUBA
STA $testX
if2skp35: if2skp36: if2skp37: LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp40
LDARAM $e
PUSHA
LDARAM $pinkDir
MOVAB
POPA
CMP
 RJZI ifskp38
 LCALL calcPinkTarget_loc
ifskp38: LDARAM $testX
STA $a
LDAI 0
LDBCMA pinkTarg
ADDC
LDARAMC
STA $c
LDARAM $testY
STA $b
LDAI 1
LDBCMA pinkTarg
ADDC
LDARAMC
STA $d
 LCALL getDist_loc
STA $temp
LDARAM $temp
PUSHA
LDARAM $dist
MOVAB
POPA
CMP
 RJCI ifcnt39
 RJMP ifskp39
ifcnt39: LDARAM $temp
STA $dist
LDARAM $e
STA $pinkDir
ifskp39: ifskp40: ifskp41: LDARAM $e
LDBI 1
ADDA
STA $e
 RJMP loopstart4
loopdn4: LDACMA maxInt
STA $dist
LDARAM $blueDir
STA $dirForOpp
 LCALL getOppositeDir_loc
STA $dirForOpp
LDAI 0
STA $e
loopstart5: LDARAM $e
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt5
 RJMP loopdn5
loopcnt5: LDARAM $e
PUSHA
LDARAM $dirForOpp
MOVAB
POPA
CMP
 RJZI ifskp48
LDAI 0
LDBCMA bluePos
ADDC
LDARAMC
STA $testX
LDAI 1
LDBCMA bluePos
ADDC
LDARAMC
STA $testY
LDARAM $e
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt44
 RJMP ifskp44
ifcnt44: LDARAM $testY
LDBI 1
SUBA
STA $testY
 RJMP if2skp44
ifskp44: LDARAM $e
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt43
 RJMP ifskp43
ifcnt43: LDARAM $testX
LDBI 1
ADDA
STA $testX
 RJMP if2skp43
ifskp43: LDARAM $e
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt42
 RJMP ifskp42
ifcnt42: LDARAM $testY
LDBI 1
ADDA
STA $testY
 RJMP if2skp42
ifskp42: LDARAM $testX
LDBI 1
SUBA
STA $testX
if2skp42: if2skp43: if2skp44: LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp47
LDARAM $e
PUSHA
LDARAM $blueDir
MOVAB
POPA
CMP
 RJZI ifskp45
 LCALL calcBlueTarget_loc
ifskp45: LDARAM $testX
STA $a
RJMP loopdn7l3skp
loopdn7l3: RJMP loopdn7l4
loopdn7l3skp: LDAI 0
LDBCMA blueTarg
ADDC
LDARAMC
STA $c
LDARAM $testY
STA $b
LDAI 1
LDBCMA blueTarg
ADDC
LDARAMC
STA $d
 LCALL getDist_loc
STA $temp
LDARAM $temp
PUSHA
LDARAM $dist
MOVAB
POPA
CMP
 RJCI ifcnt46
 RJMP ifskp46
ifcnt46: LDARAM $temp
STA $dist
LDARAM $e
STA $blueDir
ifskp46: ifskp47: ifskp48: LDARAM $e
LDBI 1
ADDA
STA $e
 RJMP loopstart5
loopdn5: LDACMA maxInt
STA $dist
LDARAM $orangeDir
STA $dirForOpp
 LCALL getOppositeDir_loc
STA $dirForOpp
LDAI 0
STA $e
loopstart6: LDARAM $e
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt6
 RJMP loopdn6
loopcnt6: LDARAM $e
PUSHA
LDARAM $dirForOpp
MOVAB
POPA
CMP
 RJZI ifskp55
LDAI 0
LDBCMA orangePos
ADDC
LDARAMC
STA $testX
LDAI 1
LDBCMA orangePos
ADDC
LDARAMC
STA $testY
LDARAM $e
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt51
 RJMP ifskp51
ifcnt51: LDARAM $testY
LDBI 1
SUBA
STA $testY
 RJMP if2skp51
ifskp51: LDARAM $e
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt50
 RJMP ifskp50
ifcnt50: LDARAM $testX
LDBI 1
ADDA
STA $testX
 RJMP if2skp50
ifskp50: LDARAM $e
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt49
 RJMP ifskp49
ifcnt49: LDARAM $testY
LDBI 1
ADDA
STA $testY
 RJMP if2skp49
ifskp49: LDARAM $testX
LDBI 1
SUBA
STA $testX
if2skp49: if2skp50: if2skp51: LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp54
LDARAM $e
PUSHA
LDARAM $orangeDir
MOVAB
POPA
CMP
 RJZI ifskp52
 LCALL calcOrangeTarget_loc
ifskp52: LDARAM $testX
STA $a
LDAI 0
LDBCMA orangeTarg
ADDC
LDARAMC
STA $c
LDARAM $testY
STA $b
LDAI 1
LDBCMA orangeTarg
ADDC
LDARAMC
STA $d
 LCALL getDist_loc
STA $temp
LDARAM $temp
PUSHA
LDARAM $dist
MOVAB
POPA
CMP
 RJCI ifcnt53
 RJMP ifskp53
ifcnt53: LDARAM $temp
STA $dist
LDARAM $e
STA $orangeDir
ifskp53: ifskp54: ifskp55: LDARAM $e
LDBI 1
ADDA
STA $e
 RJMP loopstart6
loopdn6: LDAI 0
LDBCMA redPos
ADDC
LDARAMC
STA $testX
LDAI 1
LDBCMA redPos
ADDC
LDARAMC
STA $testY
LDARAM $redDir
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt58
 RJMP ifskp58
ifcnt58: LDARAM $testY
LDBI 1
SUBA
STA $testY
 RJMP if2skp58
ifskp58: LDARAM $redDir
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt57
 RJMP ifskp57
ifcnt57: LDARAM $testX
LDBI 1
ADDA
STA $testX
 RJMP if2skp57
ifskp57: LDARAM $redDir
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt56
RJMP loopdn7l4skp
loopdn7l4: RJMP loopdn7l5
loopdn7l4skp:  RJMP ifskp56
ifcnt56: LDARAM $testY
LDBI 1
ADDA
STA $testY
 RJMP if2skp56
ifskp56: LDARAM $testX
LDBI 1
SUBA
STA $testX
if2skp56: if2skp57: if2skp58: LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp59
LDAI 0
LDBCMA redPos
ADDC
PUSHC
LDARAM $testX
POPC
STARAMC
LDAI 1
LDBCMA redPos
ADDC
PUSHC
LDARAM $testY
POPC
STARAMC
ifskp59: LDAI 0
LDBCMA bluePos
ADDC
LDARAMC
STA $testX
LDAI 1
LDBCMA bluePos
ADDC
LDARAMC
STA $testY
LDARAM $blueDir
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt62
 RJMP ifskp62
ifcnt62: LDARAM $testY
LDBI 1
SUBA
STA $testY
 RJMP if2skp62
ifskp62: LDARAM $blueDir
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt61
 RJMP ifskp61
ifcnt61: LDARAM $testX
LDBI 1
ADDA
STA $testX
 RJMP if2skp61
ifskp61: LDARAM $blueDir
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt60
 RJMP ifskp60
ifcnt60: LDARAM $testY
LDBI 1
ADDA
STA $testY
 RJMP if2skp60
ifskp60: LDARAM $testX
LDBI 1
SUBA
STA $testX
if2skp60: if2skp61: if2skp62: LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp63
LDAI 0
LDBCMA bluePos
ADDC
PUSHC
LDARAM $testX
POPC
STARAMC
LDAI 1
LDBCMA bluePos
ADDC
PUSHC
LDARAM $testY
POPC
STARAMC
ifskp63: LDAI 0
LDBCMA pinkPos
ADDC
LDARAMC
STA $testX
LDAI 1
LDBCMA pinkPos
ADDC
LDARAMC
STA $testY
LDARAM $pinkDir
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt66
 RJMP ifskp66
ifcnt66: LDARAM $testY
LDBI 1
SUBA
STA $testY
 RJMP if2skp66
ifskp66: LDARAM $pinkDir
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt65
 RJMP ifskp65
ifcnt65: LDARAM $testX
LDBI 1
ADDA
STA $testX
 RJMP if2skp65
ifskp65: LDARAM $pinkDir
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt64
 RJMP ifskp64
ifcnt64: LDARAM $testY
LDBI 1
ADDA
STA $testY
 RJMP if2skp64
ifskp64: LDARAM $testX
LDBI 1
SUBA
STA $testX
if2skp64: if2skp65: if2skp66: LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp67
LDAI 0
LDBCMA pinkPos
ADDC
PUSHC
LDARAM $testX
POPC
STARAMC
LDAI 1
LDBCMA pinkPos
ADDC
PUSHC
LDARAM $testY
POPC
STARAMC
ifskp67: LDAI 0
LDBCMA orangePos
ADDC
LDARAMC
STA $testX
LDAI 1
LDBCMA orangePos
ADDC
LDARAMC
STA $testY
LDARAM $orangeDir
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt70
 RJMP ifskp70
ifcnt70: LDARAM $testY
RJMP loopdn7l5skp
loopdn7l5: RJMP loopdn7l6
loopdn7l5skp: LDBI 1
SUBA
STA $testY
 RJMP if2skp70
ifskp70: LDARAM $orangeDir
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt69
 RJMP ifskp69
ifcnt69: LDARAM $testX
LDBI 1
ADDA
STA $testX
 RJMP if2skp69
ifskp69: LDARAM $orangeDir
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt68
 RJMP ifskp68
ifcnt68: LDARAM $testY
LDBI 1
ADDA
STA $testY
 RJMP if2skp68
ifskp68: LDARAM $testX
LDBI 1
SUBA
STA $testX
if2skp68: if2skp69: if2skp70: LCALL isValidSpace_loc
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp71
LDAI 0
LDBCMA orangePos
ADDC
PUSHC
LDARAM $testX
POPC
STARAMC
LDAI 1
LDBCMA orangePos
ADDC
PUSHC
LDARAM $testY
POPC
STARAMC
ifskp71: LDARAM $blueReleased
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt73
 RJMP ifskp73
ifcnt73: LDARAM $eaten
PUSHA
LDAI 20
MOVAB
POPA
CMP
 RJZI ifcnt72
 RJMP ifskp72
ifcnt72: LDAI 0
LDBCMA bluePos
ADDC
PUSHC
LDACMA houseExitX
POPC
STARAMC
LDAI 1
LDBCMA bluePos
ADDC
PUSHC
LDACMA houseExitY
POPC
STARAMC
LDAI 1
STA $blueReleased
ifskp72: ifskp73: LDARAM $orangeReleased
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt75
 RJMP ifskp75
ifcnt75: LDARAM $eaten
PUSHA
LDAI 55
MOVAB
POPA
CMP
 RJZI ifcnt74
 RJMP ifskp74
ifcnt74: LDAI 0
LDBCMA orangePos
ADDC
PUSHC
LDACMA houseExitX
POPC
STARAMC
LDAI 1
LDBCMA orangePos
ADDC
PUSHC
LDACMA houseExitY
POPC
STARAMC
LDAI 1
STA $orangeReleased
ifskp74: ifskp75: LDARAM $ghostMode
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifskp84
LDARAM $frameCounter
LDBI 1
ADDA
STA $frameCounter
LDARAM $ghostMode
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt83
 RJMP ifskp83
ifcnt83: LDARAM $stage
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt77
 RJMP ifskp77
ifcnt77: LDARAM $frameCounter
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJZI ifcnt76
 RJMP ifskp76
ifcnt76: LDAI 0
LDBCMA pinkPos
ADDC
PUSHC
LDACMA houseExitX
POPC
STARAMC
LDAI 1
LDBCMA pinkPos
ADDC
PUSHC
LDACMA houseExitY
POPC
STARAMC
ifskp76: ifskp77: LDARAM $stage
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJCI ifcnt80
 RJMP ifskp80
ifcnt80: LDACMA timeMultiplier
PUSHA
LDARAM $frameCounter
MOVAB
POPA
CMP
 RJCI ifcnt78
 RJMP ifskp78
ifcnt78: LDAI 1
STA $ghostMode
LDAI 0
STA $frameCounter
ifskp78: RJMP if2skp80
ifskp80: LDACMA timeMultiplier2
PUSHA
LDARAM $frameCounter
MOVAB
POPA
CMP
 RJCI ifcnt79
 RJMP ifskp79
ifcnt79: LDAI 1
RJMP loopdn7l6skp
loopdn7l6: RJMP loopdn7
loopdn7l6skp: STA $ghostMode
LDAI 0
STA $frameCounter
ifskp79: if2skp80: RJMP if2skp83
ifskp83: LDARAM $stage
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJCI ifcnt82
 RJMP ifskp82
ifcnt82: LDACMA timeMultiplier3
PUSHA
LDARAM $frameCounter
MOVAB
POPA
CMP
 RJCI ifcnt81
 RJMP ifskp81
ifcnt81: LDAI 0
STA $ghostMode
LDAI 0
STA $frameCounter
LDARAM $stage
LDBI 1
ADDA
STA $stage
ifskp81: ifskp82: if2skp83: ifskp84: LCALL drawMap_loc
 LCALL drawDots_loc
LDAI 0
LDBCMA redPos
ADDC
LDARAMC
STA $x
LDAI 1
LDBCMA redPos
ADDC
LDARAMC
STA $y
LDAI 48
STA $col
 LCALL drawGhost_loc
LDAI 0
LDBCMA bluePos
ADDC
LDARAMC
STA $x
LDAI 1
LDBCMA bluePos
ADDC
LDARAMC
STA $y
LDAI 15
STA $col
 LCALL drawGhost_loc
LDAI 0
LDBCMA pinkPos
ADDC
LDARAMC
STA $x
LDAI 1
LDBCMA pinkPos
ADDC
LDARAMC
STA $y
LDAI 59
STA $col
 LCALL drawGhost_loc
LDAI 0
LDBCMA orangePos
ADDC
LDARAMC
STA $x
LDAI 1
LDBCMA orangePos
ADDC
LDARAMC
STA $y
LDAI 52
STA $col
 LCALL drawGhost_loc
 LCALL drawPlayer_loc
LDAI 95
STA $drawX
LDAI 0
STA $drawY
LDAI 20
STA $col
LDAI 1
STA $padNumWith1Zeroes
LDARAM $score
STA $num2Draw
 LCALL drawNum_loc
FLIP
LDARAM $pacmanMouth
LDBI 1
ADDA
STA $pacmanMouth
LDAI 5
PUSHA
LDARAM $pacmanMouth
MOVAB
POPA
CMP
 RJCI ifcnt85
 RJMP ifskp85
ifcnt85: LDAI 0
STA $pacmanMouth
ifskp85: JMP loopstart7
loopdn7: LDAI 0
RET
drawDots: LDAI 0
STA $x
loopstart8: LDARAM $x
PUSHA
LDAI 164
MOVAB
POPA
CMP
 RJCI loopcnt8
 RJMP loopdn8
loopcnt8: LDARAM $x
LDBCMA dotExist
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp86
LDARAM $x
LDBCMA dotsPos
ADDC
LDACMC
VMARA
LDAI 63
MOVAC
VRCC
ifskp86: LDARAM $x
LDBI 1
ADDA
STA $x
 RJMP loopstart8
loopdn8: RET
drawTargets: LDAI 128
STA $multx
LDAI 1
LDBCMA redTarg
ADDC
LDARAMC
STA $multy
 LCALL mult_loc
PUSHA
LDAI 0
LDBCMA redTarg
ADDC
LDARAMC
MOVAB
POPA
ADDA
STA $addr
LDARAM $addr
VMARA
LDAI 48
MOVAC
VRCC
LDAI 128
STA $multx
LDAI 1
LDBCMA blueTarg
ADDC
LDARAMC
STA $multy
 LCALL mult_loc
PUSHA
LDAI 0
LDBCMA blueTarg
ADDC
LDARAMC
MOVAB
POPA
ADDA
STA $addr
LDARAM $addr
VMARA
LDAI 15
MOVAC
VRCC
LDAI 128
STA $multx
LDAI 1
LDBCMA pinkTarg
ADDC
LDARAMC
STA $multy
 LCALL mult_loc
PUSHA
LDAI 0
LDBCMA pinkTarg
ADDC
LDARAMC
MOVAB
POPA
ADDA
STA $addr
LDARAM $addr
VMARA
LDAI 55
MOVAC
VRCC
LDAI 128
STA $multx
LDAI 1
LDBCMA orangeTarg
ADDC
LDARAMC
STA $multy
 LCALL mult_loc
PUSHA
LDAI 0
LDBCMA orangeTarg
ADDC
LDARAMC
MOVAB
POPA
ADDA
STA $addr
LDARAM $addr
VMARA
LDAI 52
MOVAC
VRCC
RET
drawMap: LDAI 0
STA $a
loopstart9: LDARAM $a
PUSHA
LDAI 97
MOVAB
POPA
CMP
 RJCI loopcnt9
 RJMP loopdn9
loopcnt9: LDAI 5
STA $multx
LDARAM $a
STA $multy
 LCALL mult_loc
STA $addr
LDARAM $addr
LDBCMA map
ADDC
LDACMC
STA $x
LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $addr
LDBCMA map
ADDC
LDACMC
STA $y
LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $addr
LDBCMA map
ADDC
LDACMC
STA $dx
LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $addr
LDBCMA map
ADDC
LDACMC
STA $dy
LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $addr
LDBCMA map
ADDC
LDACMC
STA $col
 LCALL drawRect_loc
LDARAM $a
LDBI 1
ADDA
STA $a
 RJMP loopstart9
loopdn9: RET
isValidSpace: LDAI 128
STA $multx
LDARAM $testY
STA $multy
 LCALL mult_loc
LDBRAM $testX
ADDA
STA $testAddr
LDAI 0
STA $a
LDAI 48
STA $col
loopstart12: LDARAM $a
PUSHA
LDAI 45
MOVAB
POPA
CMP
 RJCI loopcnt12
 RJMP loopdn12
loopcnt12: LDAI 4
STA $multx
LDARAM $a
STA $multy
 LCALL mult_loc
STA $addr
LDARAM $addr
LDBCMA legalSpaces
ADDC
LDACMC
STA $x
LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $addr
LDBCMA legalSpaces
ADDC
LDACMC
STA $y
LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $addr
LDBCMA legalSpaces
ADDC
LDACMC
STA $dx
LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $addr
LDBCMA legalSpaces
ADDC
LDACMC
STA $dy
LDARAM $y
STA $multx
LDAI 128
STA $multy
 LCALL mult_loc
LDBRAM $x
ADDA
STA $addr
LDAI 0
STA $c
loopstart11: LDARAM $c
PUSHA
LDARAM $dy
MOVAB
POPA
CMP
 RJCI loopcnt11
 RJMP loopdn11
loopcnt11: LDAI 0
STA $b
loopstart10: LDARAM $b
PUSHA
LDARAM $dx
MOVAB
POPA
CMP
 RJCI loopcnt10
 RJMP loopdn10
loopcnt10: LDARAM $addr
PUSHA
LDARAM $testAddr
MOVAB
POPA
CMP
 RJZI ifcnt87
 RJMP ifskp87
ifcnt87: LDAI 1
RET
ifskp87: LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $b
LDBI 1
ADDA
STA $b
 RJMP loopstart10
loopdn10: LDARAM $addr
LDBI 128
ADDA
LDBRAM $dx
SUBA
STA $addr
LDARAM $c
LDBI 1
ADDA
STA $c
 RJMP loopstart11
loopdn11: LDARAM $a
LDBI 1
ADDA
STA $a
 RJMP loopstart12
loopdn12: LDAI 0
RET
drawRect: LDARAM $y
STA $multx
LDAI 128
STA $multy
 LCALL mult_loc
LDBRAM $x
ADDA
STA $addr
LDAI 0
STA $c
loopstart14: LDARAM $c
PUSHA
LDARAM $dy
MOVAB
POPA
CMP
 RJCI loopcnt14
 RJMP loopdn14
loopcnt14: LDAI 0
STA $b
loopstart13: LDARAM $b
PUSHA
LDARAM $dx
MOVAB
POPA
CMP
 RJCI loopcnt13
 RJMP loopdn13
loopcnt13: LDARAM $addr
VMARA
LDARAM $col
MOVAC
VRCC
LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $b
LDBI 1
ADDA
STA $b
 RJMP loopstart13
loopdn13: LDARAM $addr
LDBI 128
ADDA
LDBRAM $dx
SUBA
STA $addr
LDARAM $c
LDBI 1
ADDA
STA $c
 RJMP loopstart14
loopdn14: RET
refreshInput: LDAIO
STA $io
LDARAM $io
STA $N
LDAI 2
STA $D
 LCALL divide_loc
LDARAM $Q
STA $N
LDAI 0
STA $up
LDAI 0
STA $dn
LDAI 0
STA $lf
LDAI 0
STA $rt
LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt88
 RJMP ifskp88
ifcnt88: LDAI 1
STA $up
ifskp88: LCALL divide_loc
LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt89
 RJMP ifskp89
ifcnt89: LDAI 1
STA $rt
ifskp89: LDARAM $Q
STA $N
 LCALL divide_loc
LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt90
 RJMP ifskp90
ifcnt90: LDAI 1
STA $dn
ifskp90: LDARAM $Q
STA $N
 LCALL divide_loc
LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt91
 RJMP ifskp91
ifcnt91: LDAI 1
STA $lf
ifskp91: RET
drawGhost: LDAI 128
STA $multx
LDARAM $y
STA $multy
 LCALL mult_loc
LDBRAM $x
ADDA
STA $addr
LDARAM $addr
LDBI 129
SUBA
STA $addr
LDAI 0
STA $a
loopstart16: LDARAM $a
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJCI loopcnt16
 RJMP loopdn16
loopcnt16: LDAI 0
STA $b
loopstart15: LDARAM $b
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJCI loopcnt15
 RJMP loopdn15
loopcnt15: LDARAM $addr
VMARA
LDARAM $col
MOVAC
VRCC
LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $b
LDBI 1
ADDA
STA $b
 RJMP loopstart15
loopdn15: LDARAM $addr
LDBI 125
ADDA
STA $addr
LDARAM $a
LDBI 1
ADDA
STA $a
 RJMP loopstart16
loopdn16: RET
drawPlayer: LDAI 128
STA $multx
LDARAM $playerY
STA $multy
 LCALL mult_loc
LDBRAM $playerX
ADDA
STA $addr
LDARAM $addr
LDBI 129
SUBA
STA $addr
LDAI 0
STA $a
loopstart18: LDARAM $a
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJCI loopcnt18
 RJMP loopdn18
loopcnt18: LDAI 0
STA $b
loopstart17: LDARAM $b
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJCI loopcnt17
 RJMP loopdn17
loopcnt17: LDARAM $a
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt95
 RJMP ifskp95
ifcnt95: LDARAM $b
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt94
 RJMP ifskp94
ifcnt94: LDARAM $pacmanDir
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt93
 RJMP ifskp93
ifcnt93: LDAI 2
PUSHA
LDARAM $pacmanMouth
MOVAB
POPA
CMP
 RJCI ifcnt92
 RJMP ifskp92
ifcnt92: RJMP skipPacmanPixel
ifskp92: ifskp93: ifskp94: ifskp95: LDARAM $a
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt102
 RJMP ifskp102
ifcnt102: LDARAM $b
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt98
 RJMP ifskp98
ifcnt98: LDARAM $pacmanDir
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJZI ifcnt97
 RJMP ifskp97
ifcnt97: LDAI 2
PUSHA
LDARAM $pacmanMouth
MOVAB
POPA
CMP
 RJCI ifcnt96
 RJMP ifskp96
ifcnt96: RJMP skipPacmanPixel
ifskp96: ifskp97: ifskp98: LDARAM $b
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt101
 RJMP ifskp101
ifcnt101: LDARAM $pacmanDir
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt100
 RJMP ifskp100
ifcnt100: LDAI 2
PUSHA
LDARAM $pacmanMouth
MOVAB
POPA
CMP
 RJCI ifcnt99
 RJMP ifskp99
ifcnt99: RJMP skipPacmanPixel
ifskp99: ifskp100: ifskp101: ifskp102: LDARAM $a
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt106
 RJMP ifskp106
ifcnt106: LDARAM $b
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt105
 RJMP ifskp105
ifcnt105: LDARAM $pacmanDir
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJZI ifcnt104
 RJMP ifskp104
ifcnt104: LDAI 2
PUSHA
LDARAM $pacmanMouth
MOVAB
POPA
CMP
 RJCI ifcnt103
 RJMP ifskp103
ifcnt103: RJMP skipPacmanPixel
ifskp103: ifskp104: ifskp105: ifskp106: LDARAM $addr
VMARA
LDAI 60
MOVAC
VRCC
skipPacmanPixel: LDARAM $addr
LDBI 1
ADDA
STA $addr
LDARAM $b
LDBI 1
ADDA
STA $b
 RJMP loopstart17
loopdn17: LDARAM $addr
LDBI 125
ADDA
STA $addr
LDARAM $a
LDBI 1
ADDA
STA $a
 RJMP loopstart18
loopdn18: RET
calcRedTarget: LDARAM $ghostMode
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt107
 RJMP ifskp107
ifcnt107: LDAI 0
LDBCMA redTarg
ADDC
PUSHC
LDAI 75
POPC
STARAMC
LDAI 1
LDBCMA redTarg
ADDC
PUSHC
LDAI 2
POPC
STARAMC
RET
ifskp107: LDARAM $ghostMode
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt108
 RJMP ifskp108
ifcnt108: LDAI 0
LDBCMA redTarg
ADDC
PUSHC
LDARAM $playerX
POPC
STARAMC
LDAI 1
LDBCMA redTarg
ADDC
PUSHC
LDARAM $playerY
POPC
STARAMC
ifskp108: RET
calcPinkTarget: LDARAM $ghostMode
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt109
 RJMP ifskp109
ifcnt109: LDAI 0
LDBCMA pinkTarg
ADDC
PUSHC
LDAI 23
POPC
STARAMC
LDAI 1
LDBCMA pinkTarg
ADDC
PUSHC
LDAI 2
POPC
STARAMC
RET
ifskp109: LDARAM $ghostMode
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt116
 RJMP ifskp116
ifcnt116: LDAI 0
LDBCMA pinkTarg
ADDC
PUSHC
LDARAM $playerX
POPC
STARAMC
LDAI 1
LDBCMA pinkTarg
ADDC
PUSHC
LDARAM $playerY
POPC
STARAMC
LDARAM $pacmanDir
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp115
LDARAM $pacmanDir
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt111
 RJMP ifskp111
ifcnt111: LDAI 1
LDBCMA pinkTarg
ADDC
PUSHC
LDAI 1
LDBCMA pinkTarg
ADDC
LDARAMC
LDBI 16
SUBA
POPC
STARAMC
LDAI 76
PUSHA
LDAI 1
LDBCMA pinkTarg
ADDC
LDARAMC
MOVAB
POPA
CMP
 RJCI ifcnt110
 RJMP ifskp110
ifcnt110: LDAI 1
LDBCMA pinkTarg
ADDC
PUSHC
LDAI 1
LDBCMA pinkTarg
ADDC
LDARAMC
LDBI 75
ADDA
POPC
STARAMC
ifskp110: LDAI 0
LDBCMA pinkTarg
ADDC
PUSHC
LDAI 0
LDBCMA pinkTarg
ADDC
LDARAMC
LDBI 16
SUBA
POPC
STARAMC
RET
ifskp111: LDARAM $pacmanDir
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt112
 RJMP ifskp112
ifcnt112: LDAI 0
LDBCMA pinkTarg
ADDC
PUSHC
LDAI 0
LDBCMA pinkTarg
ADDC
LDARAMC
LDBI 16
ADDA
POPC
STARAMC
RET
ifskp112: LDARAM $pacmanDir
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJZI ifcnt113
 RJMP ifskp113
ifcnt113: LDAI 1
LDBCMA pinkTarg
ADDC
PUSHC
LDAI 1
LDBCMA pinkTarg
ADDC
LDARAMC
LDBI 16
ADDA
POPC
STARAMC
RET
ifskp113: LDARAM $pacmanDir
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJZI ifcnt114
 RJMP ifskp114
ifcnt114: LDAI 0
LDBCMA pinkTarg
ADDC
PUSHC
LDAI 0
LDBCMA pinkTarg
ADDC
LDARAMC
LDBI 16
SUBA
POPC
STARAMC
ifskp114: ifskp115: ifskp116: RET
getOppositeDir: LDARAM $dirForOpp
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt117
 RJMP ifskp117
ifcnt117: LDAI 2
RET
ifskp117: LDARAM $dirForOpp
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt118
 RJMP ifskp118
ifcnt118: LDAI 3
RET
ifskp118: LDARAM $dirForOpp
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt119
 RJMP ifskp119
ifcnt119: LDAI 0
RET
ifskp119: LDARAM $dirForOpp
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJZI ifcnt120
 RJMP ifskp120
ifcnt120: LDAI 1
RET
ifskp120: LDAI 5
RET
calcBlueTarget: LDARAM $ghostMode
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt121
 RJMP ifskp121
ifcnt121: LDAI 0
LDBCMA blueTarg
ADDC
PUSHC
LDAI 79
POPC
STARAMC
LDAI 1
LDBCMA blueTarg
ADDC
PUSHC
LDAI 70
POPC
STARAMC
RET
ifskp121: LDARAM $ghostMode
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt128
 RJMP ifskp128
ifcnt128: LDAI 0
LDBCMA blueTarg
ADDC
PUSHC
LDARAM $playerX
POPC
STARAMC
LDAI 1
LDBCMA blueTarg
ADDC
PUSHC
LDARAM $playerY
POPC
STARAMC
LDARAM $pacmanDir
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp127
LDARAM $pacmanDir
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt123
 RJMP ifskp123
ifcnt123: LDAI 1
LDBCMA blueTarg
ADDC
PUSHC
LDAI 1
LDBCMA blueTarg
ADDC
LDARAMC
LDBI 8
SUBA
POPC
STARAMC
LDAI 76
PUSHA
LDAI 1
LDBCMA blueTarg
ADDC
LDARAMC
MOVAB
POPA
CMP
 RJCI ifcnt122
 RJMP ifskp122
ifcnt122: LDAI 1
LDBCMA blueTarg
ADDC
PUSHC
LDAI 1
LDBCMA blueTarg
ADDC
LDARAMC
LDBI 75
ADDA
POPC
STARAMC
ifskp122: LDAI 0
LDBCMA blueTarg
ADDC
PUSHC
LDAI 0
LDBCMA blueTarg
ADDC
LDARAMC
LDBI 8
SUBA
POPC
STARAMC
 RJMP blueTargNextStep
ifskp123: LDARAM $pacmanDir
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt124
 RJMP ifskp124
ifcnt124: LDAI 0
LDBCMA blueTarg
ADDC
PUSHC
LDAI 0
LDBCMA blueTarg
ADDC
LDARAMC
LDBI 8
ADDA
POPC
STARAMC
 RJMP blueTargNextStep
ifskp124: LDARAM $pacmanDir
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJZI ifcnt125
 RJMP ifskp125
ifcnt125: LDAI 1
LDBCMA blueTarg
ADDC
PUSHC
LDAI 1
LDBCMA blueTarg
ADDC
LDARAMC
LDBI 8
ADDA
POPC
STARAMC
 RJMP blueTargNextStep
ifskp125: LDARAM $pacmanDir
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJZI ifcnt126
 RJMP ifskp126
ifcnt126: LDAI 0
LDBCMA blueTarg
ADDC
PUSHC
LDAI 0
LDBCMA blueTarg
ADDC
LDARAMC
LDBI 8
SUBA
POPC
STARAMC
ifskp126: ifskp127: blueTargNextStep: LDAI 0
LDBCMA blueTarg
ADDC
LDARAMC
PUSHA
LDAI 0
LDBCMA redPos
ADDC
LDARAMC
MOVAB
POPA
SUBA
STA $dx
LDAI 1
LDBCMA blueTarg
ADDC
LDARAMC
PUSHA
LDAI 1
LDBCMA redPos
ADDC
LDARAMC
MOVAB
POPA
SUBA
STA $dy
LDAI 0
LDBCMA blueTarg
ADDC
PUSHC
LDAI 0
LDBCMA blueTarg
ADDC
LDARAMC
LDBRAM $dx
ADDA
POPC
STARAMC
LDAI 1
LDBCMA blueTarg
ADDC
PUSHC
LDAI 1
LDBCMA blueTarg
ADDC
LDARAMC
LDBRAM $dy
ADDA
POPC
STARAMC
ifskp128: RET
calcOrangeTarget: LDARAM $ghostMode
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt129
 RJMP ifskp129
ifcnt129: LDAI 0
LDBCMA orangeTarg
ADDC
PUSHC
LDAI 19
POPC
STARAMC
LDAI 1
LDBCMA orangeTarg
ADDC
PUSHC
LDAI 70
POPC
STARAMC
RET
ifskp129: LDARAM $ghostMode
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt131
 RJMP ifskp131
ifcnt131: LDAI 0
LDBCMA orangePos
ADDC
LDARAMC
STA $a
LDARAM $playerX
STA $c
LDAI 1
LDBCMA orangePos
ADDC
LDARAMC
STA $b
LDARAM $playerY
STA $d
 LCALL getDist_loc
STA $a
LDARAM $a
PUSHA
LDAI 225
MOVAB
POPA
CMP
 RJCI ifcnt130
 RJMP ifskp130
ifcnt130: LDAI 0
LDBCMA orangeTarg
ADDC
PUSHC
LDAI 19
POPC
STARAMC
LDAI 1
LDBCMA orangeTarg
ADDC
PUSHC
LDAI 70
POPC
STARAMC
 RJMP if2skp130
ifskp130: LDAI 0
LDBCMA orangeTarg
ADDC
PUSHC
LDARAM $playerX
POPC
STARAMC
LDAI 1
LDBCMA orangeTarg
ADDC
PUSHC
LDARAM $playerY
POPC
STARAMC
if2skp130: ifskp131: RET
getDist: LDARAM $a
PUSHA
LDARAM $c
MOVAB
POPA
CMP
 RJCI ifcnt132
 RJMP ifskp132
ifcnt132: LDARAM $a
STA $temp
LDARAM $c
STA $a
LDARAM $temp
STA $c
ifskp132: LDARAM $b
PUSHA
LDARAM $d
MOVAB
POPA
CMP
 RJCI ifcnt133
 RJMP ifskp133
ifcnt133: LDARAM $b
STA $temp
LDARAM $d
STA $b
LDARAM $temp
STA $d
ifskp133: LDARAM $a
LDBRAM $c
SUBA
STA $multx
LDARAM $multx
STA $multy
 LCALL mult_loc
STA $a
LDARAM $b
LDBRAM $d
SUBA
STA $multx
LDARAM $multx
STA $multy
LDARAM $a
PUSHA
 LCALL mult_loc
MOVAB
POPA
ADDA
RET
genRand: LDAI 239
STA $multx
LDARAM $rand
STA $multy
 LCALL mult_loc
LDBCMA randAdd
ADDA
STA $rand
RET
clearScreen: LDAI 0
STA $b
LDAI 0
STA $c
loopstart20: LDARAM $b
PUSHA
LDAI 75
MOVAB
POPA
CMP
 RJCI loopcnt20
 RJMP loopdn20
loopcnt20: LDAI 0
STA $a
loopstart19: LDARAM $a
PUSHA
LDAI 100
MOVAB
POPA
CMP
 RJCI loopcnt19
 RJMP loopdn19
loopcnt19: LDARAM $c
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
 RJMP loopstart19
loopdn19: LDARAM $c
LDBI 28
ADDA
STA $c
LDARAM $b
LDBI 1
ADDA
STA $b
 RJMP loopstart20
loopdn20: RET
mult: LDARAM $multx
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt135
 RJMP ifskp135
ifcnt135: LDAI 0
RET
 RJMP if2skp135
ifskp135: LDARAM $multy
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt134
 RJMP ifskp134
ifcnt134: LDAI 0
RET
ifskp134: if2skp135: LDARAM $multy
PUSHA
LDARAM $multx
MOVAB
POPA
CMP
 RJCI ifcnt136
 RJMP ifskp136
ifcnt136: LDARAM $multx
STA $multtemp
LDARAM $multy
STA $multx
LDARAM $multtemp
STA $multy
ifskp136: LDAI 0
STA $multacc
loopstart21: LDAI 0
PUSHA
LDARAM $multx
MOVAB
POPA
CMP
 RJCI loopcnt21
 RJMP loopdn21
loopcnt21: LDARAM $multacc
LDBRAM $multy
ADDA
STA $multacc
LDARAM $multx
LDBI 1
SUBA
STA $multx
 RJMP loopstart21
loopdn21: LDARAM $multacc
RET
divide: LDAI 0
STA $Q
LDARAM $N
STA $R
loopstart22: LDARAM $R
PUSHA
LDARAM $D
MOVAB
POPA
CMP
 RJCI loopdn22
LDARAM $Q
LDBI 1
ADDA
STA $Q
LDARAM $R
LDBRAM $D
SUBA
STA $R
 RJMP loopstart22
loopdn22: RET
zero: LDARAM $drawAddr
LDBI 1
SUBA
STA $drawAddr
LDAI 0
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
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt23
 RJMP loopdn23
loopcnt23: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numZero
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt137
 RJMP ifskp137
ifcnt137: LDARAM $singleCounter
LDBCMA numZero
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
 LCALL mult_loc
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp137: LDARAM $singleCounter
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
LDBI 123
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
one: LDAI 0
STA $singleCounter
LDAI 0
STA $drawY
loopstart26: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt26
 RJMP loopdn26
loopcnt26: LDAI 0
STA $drawX
loopstart25: LDARAM $drawX
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt25
 RJMP loopdn25
loopcnt25: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numOne
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt138
 RJMP ifskp138
ifcnt138: LDARAM $singleCounter
LDBCMA numOne
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
 LCALL mult_loc
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp138: LDARAM $singleCounter
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
 RJMP loopstart25
loopdn25: LDARAM $drawAddr
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart26
loopdn26: LDARAM $drawAddr
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
loopstart28: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt28
 RJMP loopdn28
loopcnt28: LDAI 0
STA $drawX
loopstart27: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt27
 RJMP loopdn27
loopcnt27: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numTwo
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt139
 RJMP ifskp139
ifcnt139: LDARAM $singleCounter
LDBCMA numTwo
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
 LCALL mult_loc
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp139: LDARAM $singleCounter
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
 RJMP loopstart27
loopdn27: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart28
loopdn28: LDARAM $drawAddr
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
loopstart30: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt30
 RJMP loopdn30
loopcnt30: LDAI 0
STA $drawX
loopstart29: LDARAM $drawX
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt29
 RJMP loopdn29
loopcnt29: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numThree
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt140
 RJMP ifskp140
ifcnt140: LDARAM $singleCounter
LDBCMA numThree
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
 LCALL mult_loc
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp140: LDARAM $singleCounter
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
 RJMP loopstart29
loopdn29: LDARAM $drawAddr
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart30
loopdn30: LDARAM $drawAddr
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
loopstart32: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt32
 RJMP loopdn32
loopcnt32: LDAI 0
STA $drawX
loopstart31: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt31
 RJMP loopdn31
loopcnt31: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numFour
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt141
 RJMP ifskp141
ifcnt141: LDARAM $singleCounter
LDBCMA numFour
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
 LCALL mult_loc
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp141: LDARAM $singleCounter
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
 RJMP loopstart31
loopdn31: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart32
loopdn32: LDARAM $drawAddr
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
loopstart34: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt34
 RJMP loopdn34
loopcnt34: LDAI 0
STA $drawX
loopstart33: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt33
 RJMP loopdn33
loopcnt33: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numFive
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt142
 RJMP ifskp142
ifcnt142: LDARAM $singleCounter
LDBCMA numFive
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
 LCALL mult_loc
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp142: LDARAM $singleCounter
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
 RJMP loopstart33
loopdn33: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart34
loopdn34: LDARAM $drawAddr
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
loopstart36: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt36
 RJMP loopdn36
loopcnt36: LDAI 0
STA $drawX
loopstart35: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt35
 RJMP loopdn35
loopcnt35: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numSix
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt143
 RJMP ifskp143
ifcnt143: LDARAM $singleCounter
LDBCMA numSix
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
 LCALL mult_loc
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp143: LDARAM $singleCounter
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
 RJMP loopstart35
loopdn35: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart36
loopdn36: LDARAM $drawAddr
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
loopstart38: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt38
 RJMP loopdn38
loopcnt38: LDAI 0
STA $drawX
loopstart37: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt37
 RJMP loopdn37
loopcnt37: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numSeven
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt144
 RJMP ifskp144
ifcnt144: LDARAM $singleCounter
LDBCMA numSeven
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
 LCALL mult_loc
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp144: LDARAM $singleCounter
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
 RJMP loopstart37
loopdn37: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart38
loopdn38: LDARAM $drawAddr
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
loopstart40: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt40
 RJMP loopdn40
loopcnt40: LDAI 0
STA $drawX
loopstart39: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt39
 RJMP loopdn39
loopcnt39: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numEight
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt145
 RJMP ifskp145
ifcnt145: LDARAM $singleCounter
LDBCMA numEight
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
 LCALL mult_loc
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp145: LDARAM $singleCounter
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
 RJMP loopstart39
loopdn39: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart40
loopdn40: LDARAM $drawAddr
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
loopstart42: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt42
 RJMP loopdn42
loopcnt42: LDAI 0
STA $drawX
loopstart41: LDARAM $drawX
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt41
 RJMP loopdn41
loopcnt41: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numNine
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt146
 RJMP ifskp146
ifcnt146: LDARAM $singleCounter
LDBCMA numNine
ADDC
LDACMC
STA $multx
LDARAM $col
STA $multy
 LCALL mult_loc
LDARAM $drawAddr
VMARA
LDARAM $multacc
MOVAC
VRCC
ifskp146: LDARAM $singleCounter
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
 RJMP loopstart41
loopdn41: LDARAM $drawAddr
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart42
loopdn42: LDARAM $drawAddr
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
 LCALL mult_loc
LDBRAM $drawX
ADDA
STA $drawAddr
LDARAM $padNumWith1Zeroes
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt147
 RJMP ifskp147
ifcnt147: LCALL zero_loc
ifskp147: LDARAM $num2Draw
STA $N
LDAI 10
STA $D
 LCALL divide_loc
LDARAM $Q
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt149
 RJMP ifskp149
ifcnt149: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt148
 RJMP ifskp148
ifcnt148: LCALL zero_loc
RET
ifskp148: ifskp149: loopstart43: LDAI 0
PUSHA
LDARAM $Q
MOVAB
POPA
CMP
 RJCI loopcnt43
 RJMP loopdn43
loopcnt43: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt150
 RJMP ifskp150
ifcnt150: LCALL zero_loc
 RJMP drawNumAgain
ifskp150: LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt151
 RJMP ifskp151
ifcnt151: LCALL one_loc
 RJMP drawNumAgain
ifskp151: LDARAM $R
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt152
 RJMP ifskp152
ifcnt152: LCALL two_loc
 RJMP drawNumAgain
ifskp152: LDARAM $R
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJZI ifcnt153
 RJMP ifskp153
ifcnt153: LCALL three_loc
 RJMP drawNumAgain
ifskp153: LDARAM $R
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJZI ifcnt154
 RJMP ifskp154
ifcnt154: LCALL four_loc
 RJMP drawNumAgain
ifskp154: LDARAM $R
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJZI ifcnt155
 RJMP ifskp155
ifcnt155: LCALL five_loc
 RJMP drawNumAgain
ifskp155: LDARAM $R
PUSHA
LDAI 6
MOVAB
POPA
CMP
 RJZI ifcnt156
 RJMP ifskp156
ifcnt156: LCALL six_loc
 RJMP drawNumAgain
ifskp156: LDARAM $R
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJZI ifcnt157
 RJMP ifskp157
ifcnt157: LCALL seven_loc
 RJMP drawNumAgain
ifskp157: LDARAM $R
PUSHA
LDAI 8
MOVAB
POPA
CMP
 RJZI ifcnt158
 RJMP ifskp158
ifcnt158: LCALL eight_loc
 RJMP drawNumAgain
 RJMP if2skp158
ifskp158: LCALL nine_loc
if2skp158: drawNumAgain: LDARAM $Q
STA $N
 LCALL divide_loc
 RJMP loopstart43
loopdn43: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt159
 RJMP ifskp159
ifcnt159: LCALL zero_loc
RET
ifskp159: LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt160
 RJMP ifskp160
ifcnt160: LCALL one_loc
RET
ifskp160: LDARAM $R
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt161
 RJMP ifskp161
ifcnt161: LCALL two_loc
RET
ifskp161: LDARAM $R
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJZI ifcnt162
 RJMP ifskp162
ifcnt162: LCALL three_loc
RET
ifskp162: LDARAM $R
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJZI ifcnt163
 RJMP ifskp163
ifcnt163: LCALL four_loc
RET
ifskp163: LDARAM $R
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJZI ifcnt164
 RJMP ifskp164
ifcnt164: LCALL five_loc
RET
ifskp164: LDARAM $R
PUSHA
LDAI 6
MOVAB
POPA
CMP
 RJZI ifcnt165
 RJMP ifskp165
ifcnt165: LCALL six_loc
RET
ifskp165: LDARAM $R
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJZI ifcnt166
 RJMP ifskp166
ifcnt166: LCALL seven_loc
RET
ifskp166: LDARAM $R
PUSHA
LDAI 8
MOVAB
POPA
CMP
 RJZI ifcnt167
 RJMP ifskp167
ifcnt167: LCALL eight_loc
RET
 RJMP if2skp167
ifskp167: LCALL nine_loc
if2skp167: RET
dotsPosLoc: .DW 4 22
.DW 4 25
.DW 4 28
.DW 4 31
.DW 4 34
.DW 4 37
.DW 4 40
.DW 4 43
.DW 4 46
.DW 4 52
.DW 4 55
.DW 4 58
.DW 4 61
.DW 4 64
.DW 4 67
.DW 4 70
.DW 4 73
.DW 4 76
.DW 5 162
.DW 5 174
.DW 5 180
.DW 5 192
.DW 7 22
.DW 7 34
.DW 7 46
.DW 7 52
.DW 7 64
.DW 7 76
.DW 8 150
.DW 8 153
.DW 8 156
.DW 8 159
.DW 8 162
.DW 8 165
.DW 8 168
.DW 8 171
.DW 8 174
.DW 8 177
.DW 8 180
.DW 8 183
.DW 8 186
.DW 8 189
.DW 8 192
.DW 8 195
.DW 8 198
.DW 8 201
.DW 8 204
.DW 10 22
.DW 10 34
.DW 10 40
.DW 10 58
.DW 10 64
.DW 10 76
.DW 11 150
.DW 11 153
.DW 11 156
.DW 11 159
.DW 11 162
.DW 11 168
.DW 11 171
.DW 11 174
.DW 11 180
.DW 11 183
.DW 11 186
.DW 11 192
.DW 11 195
.DW 11 198
.DW 11 201
.DW 11 204
.DW 13 34
.DW 13 64
.DW 14 162
.DW 14 192
.DW 16 34
.DW 16 64
.DW 17 162
.DW 17 192
.DW 19 34
.DW 19 64
.DW 20 162
.DW 20 192
.DW 22 34
.DW 22 64
.DW 23 150
.DW 23 153
.DW 23 156
.DW 23 159
.DW 23 162
.DW 23 165
.DW 23 168
.DW 23 171
.DW 23 174
.DW 23 180
.DW 23 183
.DW 23 186
.DW 23 189
.DW 23 192
.DW 23 195
.DW 23 198
.DW 23 201
.DW 23 204
.DW 25 22
.DW 25 34
.DW 25 46
.DW 25 52
.DW 25 64
.DW 25 76
.DW 26 153
.DW 26 162
.DW 26 165
.DW 26 168
.DW 26 171
.DW 26 174
.DW 26 180
.DW 26 183
.DW 26 186
.DW 26 189
.DW 26 192
.DW 26 201
.DW 28 25
.DW 28 34
.DW 28 40
.DW 28 58
.DW 28 64
.DW 28 73
.DW 29 150
.DW 29 153
.DW 29 156
.DW 29 159
.DW 29 162
.DW 29 168
.DW 29 171
.DW 29 174
.DW 29 180
.DW 29 183
.DW 29 186
.DW 29 192
.DW 29 195
.DW 29 198
.DW 29 201
.DW 29 204
.DW 31 22
.DW 31 46
.DW 31 52
.DW 31 76
.DW 32 150
.DW 32 153
.DW 32 156
.DW 32 159
.DW 32 162
.DW 32 165
.DW 32 168
.DW 32 171
.DW 32 174
.DW 32 177
.DW 32 180
.DW 32 183
.DW 32 186
.DW 32 189
.DW 32 192
.DW 32 195
.DW 32 198
.DW 32 201
.DW 32 204
mapLoc: .DW 0 19
.DW 0 5
.DW 0 61
.DW 0 64
.DW 0 2
.DW 0 20
.DW 0 6
.DW 0 59
.DW 0 62
.DW 0 3
.DW 0 21
.DW 0 7
.DW 0 27
.DW 0 3
.DW 0 0
.DW 0 21
.DW 0 10
.DW 0 3
.DW 0 15
.DW 0 0
.DW 0 24
.DW 0 16
.DW 0 54
.DW 0 3
.DW 0 0
.DW 0 51
.DW 0 7
.DW 0 27
.DW 0 3
.DW 0 0
.DW 0 33
.DW 0 10
.DW 0 3
.DW 0 6
.DW 0 0
.DW 0 45
.DW 0 10
.DW 0 3
.DW 0 6
.DW 0 0
.DW 0 51
.DW 0 10
.DW 0 3
.DW 0 6
.DW 0 0
.DW 0 63
.DW 0 10
.DW 0 3
.DW 0 6
.DW 0 0
.DW 0 75
.DW 0 10
.DW 0 3
.DW 0 15
.DW 0 0
.DW 0 33
.DW 0 19
.DW 0 3
.DW 0 42
.DW 0 0
.DW 0 24
.DW 0 22
.DW 0 9
.DW 0 3
.DW 0 0
.DW 0 39
.DW 0 19
.DW 0 3
.DW 0 6
.DW 0 0
.DW 0 42
.DW 0 22
.DW 0 6
.DW 0 3
.DW 0 0
.DW 0 51
.DW 0 22
.DW 0 9
.DW 0 3
.DW 0 0
.DW 0 57
.DW 0 19
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 63
.DW 0 19
.DW 0 3
.DW 0 42
.DW 0 0
.DW 0 66
.DW 0 22
.DW 0 9
.DW 0 3
.DW 0 0
.DW 0 60
.DW 0 34
.DW 0 20
.DW 0 3
.DW 0 0
.DW 0 19
.DW 0 27
.DW 0 12
.DW 0 5
.DW 0 0
.DW 0 19
.DW 0 34
.DW 0 20
.DW 0 3
.DW 0 0
.DW 0 39
.DW 0 28
.DW 0 21
.DW 0 3
.DW 0 0
.DW 0 45
.DW 0 25
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 51
.DW 0 25
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 39
.DW 0 31
.DW 0 3
.DW 0 15
.DW 0 0
.DW 0 57
.DW 0 31
.DW 0 3
.DW 0 15
.DW 0 0
.DW 0 43
.DW 0 32
.DW 0 13
.DW 0 7
.DW 0 2
.DW 0 44
.DW 0 33
.DW 0 11
.DW 0 5
.DW 0 0
.DW 0 42
.DW 0 40
.DW 0 15
.DW 0 3
.DW 0 0
.DW 0 19
.DW 0 39
.DW 0 12
.DW 0 5
.DW 0 0
.DW 0 68
.DW 0 27
.DW 0 12
.DW 0 5
.DW 0 0
.DW 0 68
.DW 0 39
.DW 0 12
.DW 0 5
.DW 0 0
.DW 0 21
.DW 0 46
.DW 0 27
.DW 0 3
.DW 0 0
.DW 0 51
.DW 0 46
.DW 0 27
.DW 0 3
.DW 0 0
.DW 0 36
.DW 0 52
.DW 0 27
.DW 0 3
.DW 0 0
.DW 0 21
.DW 0 49
.DW 0 3
.DW 0 6
.DW 0 0
.DW 0 24
.DW 0 52
.DW 0 3
.DW 0 6
.DW 0 0
.DW 0 21
.DW 0 58
.DW 0 12
.DW 0 3
.DW 0 0
.DW 0 21
.DW 0 61
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 21
.DW 0 64
.DW 0 57
.DW 0 3
.DW 0 0
.DW 0 39
.DW 0 55
.DW 0 3
.DW 0 6
.DW 0 0
.DW 0 42
.DW 0 58
.DW 0 6
.DW 0 3
.DW 0 0
.DW 0 45
.DW 0 61
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 51
.DW 0 58
.DW 0 3
.DW 0 6
.DW 0 0
.DW 0 54
.DW 0 58
.DW 0 6
.DW 0 3
.DW 0 0
.DW 0 57
.DW 0 55
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 45
.DW 0 49
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 51
.DW 0 49
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 66
.DW 0 58
.DW 0 12
.DW 0 3
.DW 0 0
.DW 0 75
.DW 0 49
.DW 0 3
.DW 0 6
.DW 0 0
.DW 0 72
.DW 0 52
.DW 0 3
.DW 0 6
.DW 0 0
.DW 0 75
.DW 0 61
.DW 0 3
.DW 0 3
.DW 0 0
.DW 0 20
.DW 0 38
.DW 0 12
.DW 0 1
.DW 0 2
.DW 0 31
.DW 0 39
.DW 0 1
.DW 0 6
.DW 0 2
.DW 0 20
.DW 0 44
.DW 0 11
.DW 0 1
.DW 0 2
.DW 0 20
.DW 0 26
.DW 0 12
.DW 0 1
.DW 0 2
.DW 0 31
.DW 0 27
.DW 0 1
.DW 0 6
.DW 0 2
.DW 0 20
.DW 0 32
.DW 0 11
.DW 0 1
.DW 0 2
.DW 0 20
.DW 0 56
.DW 0 3
.DW 0 1
.DW 0 2
.DW 0 76
.DW 0 56
.DW 0 3
.DW 0 1
.DW 0 2
.DW 0 67
.DW 0 44
.DW 0 12
.DW 0 1
.DW 0 2
.DW 0 67
.DW 0 38
.DW 0 1
.DW 0 6
.DW 0 2
.DW 0 68
.DW 0 38
.DW 0 11
.DW 0 1
.DW 0 2
.DW 0 67
.DW 0 32
.DW 0 12
.DW 0 1
.DW 0 2
.DW 0 67
.DW 0 26
.DW 0 1
.DW 0 6
.DW 0 2
.DW 0 68
.DW 0 26
.DW 0 11
.DW 0 1
.DW 0 2
.DW 0 49
.DW 0 6
.DW 0 1
.DW 0 9
.DW 0 2
.DW 0 48
.DW 0 31
.DW 0 3
.DW 0 2
.DW 0 20
.DW 0 25
.DW 0 11
.DW 0 7
.DW 0 4
.DW 0 2
.DW 0 37
.DW 0 11
.DW 0 7
.DW 0 4
.DW 0 2
.DW 0 55
.DW 0 11
.DW 0 7
.DW 0 4
.DW 0 2
.DW 0 67
.DW 0 11
.DW 0 7
.DW 0 4
.DW 0 2
.DW 0 25
.DW 0 20
.DW 0 7
.DW 0 1
.DW 0 2
.DW 0 67
.DW 0 20
.DW 0 7
.DW 0 1
.DW 0 2
.DW 0 43
.DW 0 20
.DW 0 13
.DW 0 1
.DW 0 2
.DW 0 49
.DW 0 21
.DW 0 1
.DW 0 6
.DW 0 2
.DW 0 37
.DW 0 20
.DW 0 1
.DW 0 13
.DW 0 2
.DW 0 38
.DW 0 26
.DW 0 6
.DW 0 1
.DW 0 2
.DW 0 55
.DW 0 26
.DW 0 6
.DW 0 1
.DW 0 2
.DW 0 61
.DW 0 20
.DW 0 1
.DW 0 13
.DW 0 2
.DW 0 37
.DW 0 38
.DW 0 1
.DW 0 7
.DW 0 2
.DW 0 61
.DW 0 38
.DW 0 1
.DW 0 7
.DW 0 2
.DW 0 43
.DW 0 44
.DW 0 13
.DW 0 1
.DW 0 2
.DW 0 49
.DW 0 45
.DW 0 1
.DW 0 6
.DW 0 2
.DW 0 25
.DW 0 50
.DW 0 3
.DW 0 1
.DW 0 2
.DW 0 28
.DW 0 50
.DW 0 4
.DW 0 7
.DW 0 2
.DW 0 37
.DW 0 50
.DW 0 7
.DW 0 1
.DW 0 2
.DW 0 55
.DW 0 50
.DW 0 7
.DW 0 1
.DW 0 2
.DW 0 67
.DW 0 50
.DW 0 4
.DW 0 7
.DW 0 2
.DW 0 71
.DW 0 50
.DW 0 3
.DW 0 1
.DW 0 2
.DW 0 25
.DW 0 62
.DW 0 19
.DW 0 1
.DW 0 2
.DW 0 37
.DW 0 56
.DW 0 1
.DW 0 6
.DW 0 2
.DW 0 43
.DW 0 56
.DW 0 13
.DW 0 1
.DW 0 2
.DW 0 49
.DW 0 57
.DW 0 1
.DW 0 6
.DW 0 2
.DW 0 55
.DW 0 62
.DW 0 19
.DW 0 1
.DW 0 2
.DW 0 61
.DW 0 56
.DW 0 1
.DW 0 6
.DW 0 2
legalSpacesLoc: .DW 0 22
.DW 0 65
.DW 0 55
.DW 0 1
.DW 0 23
.DW 0 17
.DW 0 54
.DW 0 1
.DW 0 34
.DW 0 9
.DW 0 1
.DW 0 51
.DW 0 22
.DW 0 8
.DW 0 25
.DW 0 1
.DW 0 22
.DW 0 9
.DW 0 1
.DW 0 15
.DW 0 64
.DW 0 8
.DW 0 1
.DW 0 52
.DW 0 22
.DW 0 47
.DW 0 25
.DW 0 1
.DW 0 52
.DW 0 47
.DW 0 25
.DW 0 1
.DW 0 20
.DW 0 35
.DW 0 21
.DW 0 1
.DW 0 58
.DW 0 35
.DW 0 21
.DW 0 1
.DW 0 52
.DW 0 8
.DW 0 25
.DW 0 1
.DW 0 76
.DW 0 9
.DW 0 1
.DW 0 15
.DW 0 23
.DW 0 23
.DW 0 11
.DW 0 1
.DW 0 65
.DW 0 23
.DW 0 11
.DW 0 1
.DW 0 46
.DW 0 9
.DW 0 1
.DW 0 8
.DW 0 52
.DW 0 9
.DW 0 1
.DW 0 8
.DW 0 40
.DW 0 18
.DW 0 1
.DW 0 6
.DW 0 58
.DW 0 18
.DW 0 1
.DW 0 6
.DW 0 41
.DW 0 23
.DW 0 6
.DW 0 1
.DW 0 52
.DW 0 23
.DW 0 6
.DW 0 1
.DW 0 46
.DW 0 24
.DW 0 1
.DW 0 5
.DW 0 52
.DW 0 24
.DW 0 1
.DW 0 5
.DW 0 40
.DW 0 29
.DW 0 19
.DW 0 1
.DW 0 40
.DW 0 30
.DW 0 1
.DW 0 17
.DW 0 58
.DW 0 30
.DW 0 1
.DW 0 17
.DW 0 41
.DW 0 41
.DW 0 17
.DW 0 1
.DW 0 35
.DW 0 53
.DW 0 29
.DW 0 1
.DW 0 46
.DW 0 48
.DW 0 1
.DW 0 5
.DW 0 52
.DW 0 48
.DW 0 1
.DW 0 5
.DW 0 22
.DW 0 48
.DW 0 1
.DW 0 6
.DW 0 76
.DW 0 48
.DW 0 1
.DW 0 6
.DW 0 23
.DW 0 53
.DW 0 3
.DW 0 1
.DW 0 73
.DW 0 53
.DW 0 3
.DW 0 1
.DW 0 22
.DW 0 59
.DW 0 12
.DW 0 1
.DW 0 65
.DW 0 59
.DW 0 12
.DW 0 1
.DW 0 25
.DW 0 54
.DW 0 1
.DW 0 5
.DW 0 40
.DW 0 54
.DW 0 1
.DW 0 5
.DW 0 58
.DW 0 54
.DW 0 1
.DW 0 5
.DW 0 73
.DW 0 54
.DW 0 1
.DW 0 5
.DW 0 40
.DW 0 59
.DW 0 7
.DW 0 1
.DW 0 52
.DW 0 59
.DW 0 7
.DW 0 1
.DW 0 22
.DW 0 60
.DW 0 1
.DW 0 5
.DW 0 46
.DW 0 60
.DW 0 1
.DW 0 5
.DW 0 52
.DW 0 60
.DW 0 1
.DW 0 5
.DW 0 76
.DW 0 60
.DW 0 1
.DW 0 5
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
