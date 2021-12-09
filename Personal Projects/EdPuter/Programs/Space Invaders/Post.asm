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
drawNum_loc: .DA drawNum
drawPlayer_loc: .DA drawPlayer
drawInvader_loc: .DA drawInvader
mult_loc: .DA mult
addBullet_loc: .DA addBullet
clearScreen_loc: .DA clearScreen
divide_loc: .DA divide
genRand_loc: .DA genRand
mainAdd:  .DA main
mid:  .DW 17 178
invaderYDiff:  .DW 3 128
playerY:  .DW 0 63
randAdd:  .DW 1 201
threeninefour:  .DW 1 138
invader: .DA invaderLoc
invader2: .DA invader2Loc
invader3: .DA invader3Loc
player: .DA playerLoc
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
heartSprite: .DA heartSpriteLoc
invaderColorChoices: .DA invaderColorChoicesLoc
bulletsX: .DW &bulletsX[10]
bulletsY: .DW &bulletsY[10]
bulletsDir: .DW &bulletsDir[10]
bulletsSpd: .DW &bulletsSpd[10]
invadersRow1: .DW &invadersRow1[9]
invadersRow2: .DW &invadersRow2[9]
invadersRow3: .DW &invadersRow3[9]
invadersRow1Col: .DW &invadersRow1Col[9]
invadersRow2Col: .DW &invadersRow2Col[9]
invadersRow3Col: .DW &invadersRow3Col[9]
main: LDAI 0
STA $rand
LDAIO
STA $io
loopstart0: LDARAM $io
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI loopcnt0
JMP loopdn0
loopcnt0: LDAIO
STA $io
JMP loopstart0
loopdn0: loopstart1: LDARAM $io
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI loopdn1
LDARAM $rand
LDBI 1
ADDA
STA $rand
LDAIO
STA $io
JMP loopstart1
loopdn1: reset: LDAI 0
STA $score
LDAI 1
STA $level
 LCALL genRand_loc
LDAI 2
STA $lives
genNewLevel: LDARAM $lives
LDBI 1
ADDA
STA $lives
LDAI 5
PUSHA
LDARAM $lives
MOVAB
POPA
CMP
JCI ifcnt0
JMP ifskp0
ifcnt0: LDAI 5
STA $lives
ifskp0: LDAI 0
STA $invaderFrameCounter
LDARAM $rand
STA $N
LDAI 8
STA $D
 LCALL divide_loc
LDAI 32
LDBRAM $R
ADDA
STA $framesTillEnemyShoot
 LCALL genRand_loc
LDAI 0
STA $y
loopstart2: LDARAM $y
PUSHA
LDAI 10
MOVAB
POPA
CMP
JCI loopcnt2
JMP loopdn2
loopcnt2: LDARAM $y
LDBCMA bulletsX
ADDC
PUSHC
LDAI 255
POPC
STARAMC
LDARAM $y
LDBCMA bulletsY
ADDC
PUSHC
LDAI 255
POPC
STARAMC
LDARAM $y
LDBCMA bulletsDir
ADDC
PUSHC
LDAI 0
POPC
STARAMC
LDARAM $y
LDBI 1
ADDA
STA $y
JMP loopstart2
loopdn2: LDAI 1
STA $invaderDir
LDAI 0
STA $invaderX
LDAI 45
STA $playerX
LDAI 0
STA $y
LDAI 0
STA $shoot
LDAI 0
STA $shootLast
loopstart3: LDARAM $y
PUSHA
LDAI 9
MOVAB
POPA
CMP
JCI loopcnt3
JMP loopdn3
loopcnt3: LDARAM $y
LDBCMA invadersRow1
ADDC
PUSHC
LDAI 1
POPC
STARAMC
LDARAM $y
LDBCMA invadersRow2
ADDC
PUSHC
LDAI 1
POPC
STARAMC
LDARAM $y
LDBCMA invadersRow3
ADDC
PUSHC
LDAI 1
POPC
STARAMC
LDARAM $y
LDBI 1
ADDA
STA $y
JMP loopstart3
loopdn3: LDAI 0
STA $y
loopstart4: LDARAM $y
PUSHA
LDAI 9
MOVAB
POPA
CMP
JCI loopcnt4
JMP loopdn4
loopcnt4: LDARAM $rand
STA $N
LDAI 7
STA $D
 LCALL divide_loc
LDARAM $y
LDBCMA invadersRow1Col
ADDC
PUSHC
LDARAM $R
LDBCMA invaderColorChoices
ADDC
LDACMC
POPC
STARAMC
 LCALL genRand_loc
LDARAM $y
LDBI 1
ADDA
STA $y
JMP loopstart4
loopdn4: LDAI 0
STA $y
loopstart5: LDARAM $y
PUSHA
LDAI 9
MOVAB
POPA
CMP
JCI loopcnt5
 RJMP loopdn5
loopcnt5: LDARAM $rand
STA $N
LDAI 7
STA $D
 LCALL divide_loc
LDARAM $y
LDBCMA invadersRow2Col
ADDC
PUSHC
LDARAM $R
LDBCMA invaderColorChoices
ADDC
LDACMC
POPC
STARAMC
 LCALL genRand_loc
LDARAM $y
LDBI 1
ADDA
STA $y
JMP loopstart5
loopdn5: LDAI 0
STA $y
loopstart6: LDARAM $y
PUSHA
LDAI 9
MOVAB
POPA
CMP
 RJCI loopcnt6
 RJMP loopdn6
loopcnt6: LDARAM $rand
STA $N
LDAI 7
STA $D
 LCALL divide_loc
LDARAM $y
LDBCMA invadersRow3Col
ADDC
PUSHC
LDARAM $R
LDBCMA invaderColorChoices
ADDC
LDACMC
POPC
STARAMC
 LCALL genRand_loc
LDARAM $y
LDBI 1
ADDA
STA $y
 RJMP loopstart6
loopdn6: LDARAM $level
STA $maxLevelAlien
LDAI 3
PUSHA
LDARAM $maxLevelAlien
MOVAB
POPA
CMP
 RJCI ifcnt1
 RJMP ifskp1
ifcnt1: LDAI 3
STA $maxLevelAlien
ifskp1: LDARAM $rand
STA $N
LDARAM $maxLevelAlien
STA $D
 LCALL divide_loc
LDARAM $R
STA $invadersRow1Type
 LCALL genRand_loc
LDARAM $rand
STA $N
 LCALL divide_loc
LDARAM $R
STA $invadersRow2Type
 LCALL genRand_loc
LDARAM $rand
STA $N
 LCALL divide_loc
LDARAM $R
STA $invadersRow3Type
 LCALL genRand_loc
goBack: LDARAM $rand
STA $N
LDAI 8
STA $D
 LCALL divide_loc
LDAI 32
LDBRAM $R
ADDA
STA $framesTillEnemyShoot
 LCALL genRand_loc
loopstart17: LDAI 1
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI loopdn17l0
 LCALL clearScreen_loc
LDAIO
STA $io
LDARAM $io
STA $N
LDAI 2
STA $D
 LCALL divide_loc
LDARAM $Q
STA $N
LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt3
 RJMP ifskp3
ifcnt3: LDAI 0
PUSHA
LDARAM $playerX
MOVAB
POPA
CMP
 RJCI ifcnt2
 RJMP ifskp2
ifcnt2: LDARAM $playerX
LDBI 1
SUBA
STA $playerX
ifskp2: ifskp3: LCALL divide_loc
LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt5
 RJMP ifskp5
ifcnt5: LDARAM $playerX
PUSHA
LDAI 87
MOVAB
POPA
CMP
 RJCI ifcnt4
 RJMP ifskp4
ifcnt4: LDARAM $playerX
LDBI 1
ADDA
STA $playerX
ifskp4: ifskp5: LDARAM $Q
STA $N
LDARAM $shoot
STA $shootLast
LDAI 0
STA $shoot
 LCALL divide_loc
LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt6
 RJMP ifskp6
ifcnt6: LDAI 1
STA $shoot
ifskp6: LDARAM $shoot
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp8
LDARAM $shootLast
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifskp7
LDARAM $playerX
LDBI 6
ADDA
STA $newBullX
LDACMA playerY
LDBI 1
SUBA
STA $newBullY
LDAI 255
STA $newBullDir
LDAI 2
STA $newBullSpd
 LCALL addBullet_loc
ifskp7: ifskp8: LDARAM $framesTillEnemyShoot
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt19
 RJMP ifskp19
ifcnt19: LDARAM $rand
STA $N
LDAI 8
STA $D
 LCALL divide_loc
LDAI 16
LDBRAM $R
ADDA
LDBRAM $level
SUBA
STA $framesTillEnemyShoot
LDAI 50
PUSHA
LDARAM $framesTillEnemyShoot
MOVAB
POPA
CMP
 RJCI ifcnt9
 RJMP ifskp9
ifcnt9: LDAI 1
STA $framesTillEnemyShoot
ifskp9: LCALL genRand_loc
LDAI 1
RJMP loopstart17l33skp
loopstart17l33: RJMP loopstart17
loopstart17l33skp: STA $newBullDir
LDARAM $rand
STA $N
LDAI 9
STA $D
 LCALL divide_loc
LDARAM $R
LDBCMA invadersRow3
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp18
LDARAM $R
STA $multx
LDAI 10
STA $multy
LDARAM $invaderX
PUSHA
 LCALL mult_loc
MOVAB
POPA
ADDA
LDBI 6
ADDA
STA $newBullX
LDAI 29
STA $newBullY
LDARAM $invadersRow3Type
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt11
 RJMP ifskp11
ifcnt11: LDAI 1
STA $newBullSpd
 RJMP if2skp11
ifskp11: LDARAM $invadersRow3Type
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt10
 RJMP ifskp10
ifcnt10: LDAI 2
STA $newBullSpd
 RJMP if2skp10
ifskp10: LDAI 3
STA $newBullSpd
if2skp10: if2skp11: LCALL addBullet_loc
 RJMP if2skp18
ifskp18: LDARAM $R
LDBCMA invadersRow2
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp17
LDARAM $R
STA $multx
LDAI 10
STA $multy
LDAI 14
LDBRAM $invaderX
RJMP loopdn17l0skp
loopdn17l0: RJMP loopdn17l11
loopdn17l0skp: SUBA
PUSHA
 LCALL mult_loc
MOVAB
POPA
ADDA
STA $newBullX
LDAI 21
STA $newBullY
LDARAM $invadersRow2Type
RJMP goBackl34skp
goBackl34: RJMP goBack
goBackl34skp: PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt13
 RJMP ifskp13
ifcnt13: LDAI 1
STA $newBullSpd
 RJMP if2skp13
ifskp13: LDARAM $invadersRow2Type
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt12
 RJMP ifskp12
ifcnt12: LDAI 2
STA $newBullSpd
 RJMP if2skp12
ifskp12: LDAI 3
STA $newBullSpd
if2skp12: if2skp13: LCALL addBullet_loc
 RJMP if2skp17
ifskp17: LDARAM $R
LDBCMA invadersRow1
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp16
LDARAM $R
STA $multx
LDAI 10
STA $multy
LDARAM $invaderX
PUSHA
 LCALL mult_loc
MOVAB
POPA
ADDA
LDBI 6
ADDA
STA $newBullX
LDAI 14
STA $newBullY
LDARAM $invadersRow1Type
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt15
 RJMP ifskp15
ifcnt15: LDAI 1
STA $newBullSpd
 RJMP if2skp15
ifskp15: LDARAM $invadersRow1Type
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt14
 RJMP ifskp14
ifcnt14: LDAI 2
STA $newBullSpd
 RJMP if2skp14
ifskp14: LDAI 3
STA $newBullSpd
if2skp14: if2skp15: LCALL addBullet_loc
ifskp16: if2skp17: if2skp18: ifskp19: LDAI 0
STA $bulletSearch
loopstart10: LDARAM $bulletSearch
PUSHA
LDAI 10
MOVAB
POPA
CMP
 RJCI loopcnt10
 RJMP loopdn10l1
loopcnt10: LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDAI 255
MOVAB
POPA
CMP
 RJZI ifskp44l2
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
STA $x
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
STA $y
LDARAM $bulletSearch
LDBCMA bulletsDir
ADDC
LDARAMC
STA $dir
LDARAM $dir
PUSHA
LDAI 1
RJMP loopstart17l29skp
loopstart17l29: RJMP loopstart17l33
loopstart17l29skp: MOVAB
POPA
CMP
 RJZI ifcnt42
 RJMP ifskp42
ifcnt42: LDAI 128
STA $multy
LDARAM $y
STA $multx
 LCALL mult_loc
STA $y
LDARAM $y
LDBRAM $x
ADDA
VMARA
LDAI 12
MOVAC
VRCC
LDARAM $y
LDBI 128
RJMP loopstart10l30skp
loopstart10l30: RJMP loopstart10
loopstart10l30skp: SUBA
STA $y
LDARAM $y
LDBRAM $x
ADDA
VMARA
LDAI 8
MOVAC
VRCC
LDARAM $y
LDBI 128
SUBA
STA $y
LDARAM $y
LDBRAM $x
ADDA
VMARA
LDAI 8
MOVAC
VRCC
LDARAM $y
LDBI 128
SUBA
STA $y
LDARAM $y
LDBRAM $x
ADDA
VMARA
LDAI 4
MOVAC
VRCC
LDARAM $y
LDBI 128
SUBA
STA $y
LDARAM $y
LDBRAM $x
ADDA
VMARA
LDAI 4
MOVAC
VRCC
LDACMA playerY
LDBI 1
ADDA
PUSHA
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
MOVAB
POPA
CMP
 RJCI ifcnt26
 RJMP ifskp26
RJMP loopdn17l11skp
loopdn17l11: RJMP loopdn17l19
loopdn17l11skp: ifcnt26: LDARAM $bulletSearch
LDBCMA bulletsY
RJMP goBackl31skp
goBackl31: RJMP goBackl34
goBackl31skp: ADDC
LDARAMC
PUSHA
LDACMA playerY
LDBI 8
ADDA
MOVAB
POPA
CMP
 RJCI ifcnt22
 RJMP ifskp22
ifcnt22: LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDARAM $playerX
MOVAB
POPA
CMP
 RJCI ifskp21
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDARAM $playerX
LDBI 13
ADDA
MOVAB
POPA
CMP
 RJCI ifcnt20
 RJMP ifskp20
ifcnt20: RJMP playerHitl3
ifskp20: ifskp21: ifskp22: RJMP if2skp26
ifskp26: LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
PUSHA
LDACMA playerY
MOVAB
POPA
CMP
 RJCI ifskp25
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDARAM $playerX
LDBI 5
ADDA
MOVAB
POPA
CMP
 RJCI ifskp24
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDARAM $playerX
LDBI 8
ADDA
MOVAB
POPA
CMP
 RJCI ifcnt23
 RJMP ifskp23
ifcnt23: RJMP playerHitl4
ifskp23: ifskp24: ifskp25: if2skp26: LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
PUSHC
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
PUSHA
LDARAM $bulletSearch
LDBCMA bulletsSpd
ADDC
LDARAMC
MOVAB
POPA
ADDA
POPC
STARAMC
 RJMP if2skp42l5
ifskp42: LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
RJMP loopdn10l1skp
loopdn10l1: RJMP loopdn10l12
loopdn10l1skp: LDARAMC
PUSHA
LDAI 30
MOVAB
POPA
CMP
 RJCI ifcnt41
 RJMP ifskp41l6
ifcnt41: LDARAM $bulletSearch
LDBCMA bulletsY
RJMP ifskp44l2skp
ifskp44l2: RJMP ifskp44l13
ifskp44l2skp: ADDC
LDARAMC
PUSHA
LDAI 24
MOVAB
POPA
CMP
 RJCI ifskp30
LDAI 0
RJMP loopstart17l26skp
loopstart17l26: RJMP loopstart17l29
loopstart17l26skp: STA $invaderInd
LDARAM $invaderX
LDBI 2
ADDA
STA $x2
LDAI 24
STA $y2
loopstart7: LDARAM $invaderInd
PUSHA
LDAI 9
MOVAB
POPA
CMP
 RJCI loopcnt7
 RJMP loopdn7
loopcnt7: LDARAM $invaderInd
LDBCMA invadersRow3
RJMP loopstart10l16skp
loopstart10l16: RJMP loopstart10l30
loopstart10l16skp: ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp29
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDARAM $x2
MOVAB
POPA
CMP
 RJCI ifskp28
LDARAM $x2
LDBI 8
ADDA
PUSHA
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
MOVAB
POPA
CMP
 RJCI ifskp27
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
PUSHC
LDAI 255
POPC
STARAMC
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
PUSHC
LDAI 255
POPC
STARAMC
LDARAM $invaderInd
LDBCMA invadersRow3
ADDC
PUSHC
LDAI 0
POPC
STARAMC
LDARAM $score
LDBRAM $level
ADDA
LDBRAM $invadersRow3Type
ADDA
STA $score
RJMP goBackl27skp
goBackl27: RJMP goBackl31
goBackl27skp: RJMP loopdn17l19skp
loopdn17l19: RJMP loopdn17l25
loopdn17l19skp:  RJMP nextBulletl7
ifskp27: ifskp28: ifskp29: LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
LDARAM $x2
LDBI 10
ADDA
STA $x2
 RJMP loopstart7
loopdn7: ifskp30: LDAI 22
PUSHA
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
MOVAB
POPA
CMP
 RJCI ifskp35
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
PUSHA
LDAI 17
MOVAB
POPA
CMP
 RJCI ifskp34
LDAI 0
STA $invaderInd
LDAI 9
LDBRAM $invaderX
SUBA
STA $x2
LDAI 17
STA $y2
loopstart8: LDARAM $invaderInd
PUSHA
LDAI 9
MOVAB
POPA
CMP
 RJCI loopcnt8
 RJMP loopdn8
loopcnt8: LDARAM $invaderInd
RJMP playerHitl3skp
playerHitl3: RJMP playerHitl14
playerHitl3skp: LDBCMA invadersRow2
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp33
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDARAM $x2
MOVAB
POPA
CMP
 RJCI ifskp32
LDARAM $x2
LDBI 8
ADDA
PUSHA
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
MOVAB
POPA
CMP
 RJCI ifskp31
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
PUSHC
LDAI 255
POPC
RJMP playerHitl4skp
playerHitl4: RJMP playerHitl15
playerHitl4skp: STARAMC
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
PUSHC
LDAI 255
POPC
STARAMC
LDARAM $invaderInd
LDBCMA invadersRow2
ADDC
PUSHC
RJMP loopdn10l12skp
loopdn10l12: RJMP loopdn10l20
loopdn10l12skp: LDAI 0
POPC
STARAMC
LDARAM $score
LDBRAM $level
ADDA
LDBRAM $level
RJMP if2skp42l5skp
if2skp42l5: RJMP if2skp42
if2skp42l5skp: ADDA
LDBRAM $invadersRow2Type
ADDA
RJMP ifskp44l13skp
RJMP loopstart17l23skp
loopstart17l23: RJMP loopstart17l26
loopstart17l23skp: ifskp44l13: RJMP ifskp44
ifskp44l13skp: STA $score
 RJMP nextBullet
ifskp31: ifskp32: ifskp33: LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
LDARAM $x2
LDBI 10
RJMP ifskp41l6skp
ifskp41l6: RJMP ifskp41
ifskp41l6skp: ADDA
STA $x2
 RJMP loopstart8
loopdn8: ifskp34: ifskp35: LDAI 15
PUSHA
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
MOVAB
POPA
CMP
 RJCI ifskp40
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
RJMP loopstart10l8skp
loopstart10l8: RJMP loopstart10l16
loopstart10l8skp: LDARAMC
PUSHA
LDAI 10
MOVAB
POPA
CMP
 RJCI ifskp39
LDAI 0
STA $invaderInd
LDARAM $invaderX
LDBI 2
ADDA
STA $x2
LDAI 10
STA $y2
loopstart9: LDARAM $invaderInd
PUSHA
LDAI 9
MOVAB
POPA
CMP
 RJCI loopcnt9
 RJMP loopdn9
loopcnt9: LDARAM $invaderInd
LDBCMA invadersRow1
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp38
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDARAM $x2
MOVAB
POPA
CMP
RJMP goBackl24skp
goBackl24: RJMP goBackl27
RJMP loopdn17l25skp
loopdn17l25: RJMP loopdn17l32
loopdn17l25skp: goBackl24skp:  RJCI ifskp37
LDARAM $x2
LDBI 8
ADDA
PUSHA
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
MOVAB
POPA
CMP
 RJCI ifskp36
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
PUSHC
LDAI 255
POPC
STARAMC
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
PUSHC
LDAI 255
POPC
STARAMC
LDARAM $invaderInd
RJMP nextBulletl7skp
nextBulletl7: RJMP nextBullet
nextBulletl7skp: LDBCMA invadersRow1
ADDC
PUSHC
LDAI 0
POPC
STARAMC
LDARAM $score
LDBRAM $level
ADDA
LDBRAM $level
ADDA
LDBRAM $level
ADDA
LDBRAM $invadersRow1Type
ADDA
STA $score
 RJMP nextBullet
ifskp36: ifskp37: ifskp38: LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
LDARAM $x2
LDBI 10
ADDA
STA $x2
 RJMP loopstart9
loopdn9: ifskp39: ifskp40: ifskp41: LDAI 128
STA $multy
LDARAM $y
STA $multx
RJMP playerHitl14skp
playerHitl14: RJMP playerHitl21
playerHitl14skp:  LCALL mult_loc
STA $y
LDARAM $y
LDBRAM $x
ADDA
VMARA
LDAI 48
MOVAC
VRCC
LDARAM $y
LDBI 128
ADDA
STA $y
LDARAM $y
LDBRAM $x
ADDA
VMARA
LDAI 32
MOVAC
VRCC
LDARAM $y
LDBI 128
ADDA
STA $y
LDARAM $y
LDBRAM $x
ADDA
VMARA
LDAI 32
MOVAC
VRCC
LDARAM $y
LDBI 128
ADDA
STA $y
LDARAM $y
LDBRAM $x
ADDA
VMARA
LDAI 16
RJMP playerHitl15skp
playerHitl15: RJMP playerHitl22
playerHitl15skp: MOVAC
VRCC
LDARAM $y
RJMP loopdn10l20skp
loopdn10l20: RJMP loopdn10
loopdn10l20skp: LDBI 128
ADDA
STA $y
LDARAM $y
LDBRAM $x
ADDA
VMARA
LDAI 16
MOVAC
VRCC
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
PUSHC
LDARAM $bulletSearch
RJMP loopstart17l17skp
loopstart17l17: RJMP loopstart17l23
loopstart17l17skp: LDBCMA bulletsY
ADDC
LDARAMC
PUSHA
LDARAM $bulletSearch
LDBCMA bulletsSpd
ADDC
LDARAMC
MOVAB
POPA
SUBA
POPC
STARAMC
if2skp42: LDAI 79
PUSHA
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
MOVAB
POPA
CMP
 RJCI ifcnt43
 RJMP ifskp43
ifcnt43: LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
PUSHC
LDAI 255
POPC
STARAMC
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
PUSHC
LDAI 255
POPC
STARAMC
ifskp43: ifskp44: nextBullet: LDARAM $bulletSearch
LDBI 1
ADDA
STA $bulletSearch
 RJMP loopstart10l8
loopdn10: LDAI 2
LDBRAM $invaderX
ADDA
STA $x
LDAI 10
STA $y
LDAI 128
STA $multx
LDARAM $y
STA $multy
 LCALL mult_loc
STA $y
LDAI 0
STA $invaderInd
loopstart11: LDARAM $invaderInd
PUSHA
LDAI 9
MOVAB
POPA
CMP
 RJCI loopcnt11
 RJMP loopdn11
loopcnt11: LDARAM $invaderInd
RJMP loopdn17l32skp
loopdn17l32: RJMP loopdn17l35
loopdn17l32skp: LDBCMA invadersRow1
ADDC
LDARAMC
PUSHA
LDAI 0
RJMP goBackl18skp
goBackl18: RJMP goBackl24
goBackl18skp: MOVAB
POPA
CMP
 RJZI ifskp45
LDARAM $invaderInd
LDBCMA invadersRow1Col
ADDC
LDARAMC
STA $col
LDARAM $invadersRow1Type
STA $alienType
 LCALL drawInvader_loc
ifskp45: LDARAM $x
LDBI 10
ADDA
STA $x
LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
 RJMP loopstart11
loopdn11: LDAI 9
LDBRAM $invaderX
SUBA
STA $x
LDARAM $y
LDBCMA invaderYDiff
ADDA
STA $y
LDAI 0
STA $invaderInd
loopstart12: LDARAM $invaderInd
PUSHA
LDAI 9
MOVAB
POPA
CMP
 RJCI loopcnt12
 RJMP loopdn12
loopcnt12: LDARAM $invaderInd
LDBCMA invadersRow2
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp46
LDARAM $invaderInd
LDBCMA invadersRow2Col
ADDC
LDARAMC
STA $col
LDARAM $invadersRow2Type
STA $alienType
 LCALL drawInvader_loc
ifskp46: LDARAM $x
LDBI 10
ADDA
RJMP playerHitl21skp
playerHitl21: RJMP playerHitl28
playerHitl21skp: STA $x
LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
 RJMP loopstart12
loopdn12: LDAI 2
LDBRAM $invaderX
ADDA
STA $x
LDARAM $y
LDBCMA invaderYDiff
ADDA
STA $y
LDAI 0
STA $invaderInd
loopstart13: LDARAM $invaderInd
PUSHA
LDAI 9
MOVAB
POPA
CMP
 RJCI loopcnt13
 RJMP loopdn13
loopcnt13: LDARAM $invaderInd
LDBCMA invadersRow3
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp47
LDARAM $invaderInd
LDBCMA invadersRow3Col
ADDC
LDARAMC
STA $col
LDARAM $invadersRow3Type
STA $alienType
 LCALL drawInvader_loc
ifskp47: LDARAM $x
RJMP playerHitl22skp
playerHitl22: RJMP playerHit
playerHitl22skp: LDBI 10
ADDA
STA $x
LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
 RJMP loopstart13
loopdn13: LDAI 63
STA $col
LDACMA playerY
STA $y
LDARAM $playerX
STA $x
 LCALL drawPlayer_loc
LDAI 20
STA $col
LDAI 1
STA $padNumWith2Zeroes
LDAI 93
STA $drawX
LDAI 2
STA $drawY
LDARAM $score
STA $num2Draw
RJMP loopstart17l9skp
loopstart17l9: RJMP loopstart17l17
loopstart17l9skp:  LCALL drawNum_loc
LDAI 0
STA $y
LDAI 0
STA $x2
LDAI 129
STA $y2
loopstart15: LDARAM $y
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt15
 RJMP loopdn15
loopcnt15: LDAI 0
STA $x
loopstart14: LDARAM $x
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt14
 RJMP loopdn14
loopcnt14: LDAI 0
PUSHA
LDARAM $x2
LDBCMA heartSprite
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt48
 RJMP ifskp48
ifcnt48: LDARAM $y2
VMARA
LDARAM $x2
LDBCMA heartSprite
ADDC
LDACMC
MOVAC
VRCC
ifskp48: LDARAM $x
LDBI 1
ADDA
STA $x
LDARAM $x2
LDBI 1
ADDA
STA $x2
LDARAM $y2
RJMP loopdn17l35skp
loopdn17l35: RJMP loopdn17
loopdn17l35skp: LDBI 1
ADDA
STA $y2
 RJMP loopstart14
loopdn14: LDARAM $y2
LDBI 121
ADDA
STA $y2
LDARAM $y
LDBI 1
ADDA
STA $y
 RJMP loopstart15
loopdn15: LDAI 16
STA $col
RJMP goBackl10skp
goBackl10: RJMP goBackl18
goBackl10skp: LDAI 0
STA $padNumWith2Zeroes
LDAI 10
STA $drawX
LDAI 1
STA $drawY
LDARAM $lives
STA $num2Draw
 LCALL drawNum_loc
FLIP
LDAI 0
STA $y
loopstart16: LDARAM $y
PUSHA
LDAI 9
MOVAB
POPA
CMP
 RJCI loopcnt16
 RJMP loopdn16
loopcnt16: LDARAM $y
LDBCMA invadersRow1
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp49
 RJMP notNextLevel
ifskp49: LDARAM $y
LDBCMA invadersRow2
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp50
 RJMP notNextLevel
ifskp50: LDARAM $y
LDBCMA invadersRow3
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp51
 RJMP notNextLevel
RJMP playerHitl28skp
playerHitl28: RJMP playerHit
playerHitl28skp: ifskp51: LDARAM $y
LDBI 1
ADDA
STA $y
 RJMP loopstart16
loopdn16: LDARAM $level
LDBI 1
ADDA
STA $level
JMP genNewLevel
notNextLevel: LDARAM $invaderFrameCounter
LDBI 1
ADDA
STA $invaderFrameCounter
LDARAM $framesTillEnemyShoot
LDBI 1
SUBA
STA $framesTillEnemyShoot
LDAI 12
LDBRAM $level
SUBA
STA $amt
LDAI 14
PUSHA
LDARAM $amt
MOVAB
POPA
CMP
 RJCI ifcnt52
 RJMP ifskp52
ifcnt52: LDAI 0
STA $amt
ifskp52: LDARAM $amt
PUSHA
LDARAM $invaderFrameCounter
MOVAB
POPA
CMP
 RJCI ifcnt56
 RJMP ifskp56
ifcnt56: LDAI 0
STA $invaderFrameCounter
LDARAM $invaderDir
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt55
 RJMP ifskp55
ifcnt55: LDARAM $invaderX
LDBI 1
ADDA
STA $invaderX
LDARAM $invaderX
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJZI ifcnt53
 RJMP ifskp53
ifcnt53: LDAI 0
STA $invaderDir
ifskp53: RJMP if2skp55
ifskp55: LDARAM $invaderX
LDBI 1
SUBA
STA $invaderX
LDARAM $invaderX
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt54
 RJMP ifskp54
ifcnt54: LDAI 1
STA $invaderDir
ifskp54: if2skp55: ifskp56: RJMP loopstart17l9
loopdn17: playerHit: LDARAM $lives
LDBI 1
SUBA
STA $lives
LDAI 0
PUSHA
LDARAM $lives
MOVAB
POPA
CMP
 RJCI ifcnt57
 RJMP ifskp57
ifcnt57: LDAI 0
STA $bulletSearch
loopstart18: LDARAM $bulletSearch
PUSHA
LDAI 9
MOVAB
POPA
CMP
 RJCI loopcnt18
 RJMP loopdn18
loopcnt18: LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
PUSHC
LDAI 255
POPC
STARAMC
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
PUSHC
LDAI 255
POPC
STARAMC
LDARAM $bulletSearch
LDBCMA bulletsDir
ADDC
PUSHC
LDAI 0
POPC
STARAMC
LDARAM $bulletSearch
LDBI 1
ADDA
STA $bulletSearch
 RJMP loopstart18
loopdn18: LDAI 45
STA $playerX
LDAI 0
STA $y
loopstart19: LDARAM $y
PUSHA
LDAI 50
MOVAB
POPA
CMP
 RJCI loopcnt19
 RJMP loopdn19
loopcnt19: LCALL clearScreen_loc
FLIP
LDARAM $y
LDBI 1
ADDA
STA $y
 RJMP loopstart19
loopdn19: RJMP goBackl10
ifskp57: LCALL clearScreen_loc
LDAI 20
STA $col
LDAI 1
STA $padNumWith2Zeroes
LDAI 93
STA $drawX
LDAI 2
STA $drawY
LDARAM $score
STA $num2Draw
 LCALL drawNum_loc
LDAI 0
STA $y
LDAI 0
STA $x2
LDAI 129
STA $y2
loopstart21: LDARAM $y
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt21
 RJMP loopdn21
loopcnt21: LDAI 0
STA $x
loopstart20: LDARAM $x
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt20
 RJMP loopdn20
loopcnt20: LDAI 0
PUSHA
LDARAM $x2
LDBCMA heartSprite
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt58
 RJMP ifskp58
ifcnt58: LDARAM $y2
VMARA
LDARAM $x2
LDBCMA heartSprite
ADDC
LDACMC
MOVAC
VRCC
ifskp58: LDARAM $x
LDBI 1
ADDA
STA $x
LDARAM $x2
LDBI 1
ADDA
STA $x2
LDARAM $y2
LDBI 1
ADDA
STA $y2
 RJMP loopstart20
loopdn20: LDARAM $y2
LDBI 121
ADDA
STA $y2
LDARAM $y
LDBI 1
ADDA
STA $y
 RJMP loopstart21
loopdn21: LDAI 16
STA $col
LDAI 0
STA $padNumWith2Zeroes
LDAI 10
STA $drawX
LDAI 1
STA $drawY
LDARAM $lives
STA $num2Draw
 LCALL drawNum_loc
FLIP
LDAIO
STA $io
loopstart22: LDARAM $io
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI loopdn22
LDAIO
STA $io
 RJMP loopstart22
loopdn22: loopstart23: LDARAM $io
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI loopcnt23
 RJMP loopdn23
loopcnt23: LDAIO
STA $io
 RJMP loopstart23
loopdn23: JMP reset
LDAI 0
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
loopstart25: LDARAM $b
PUSHA
LDAI 75
MOVAB
POPA
CMP
 RJCI loopcnt25
 RJMP loopdn25
loopcnt25: LDAI 0
STA $a
loopstart24: LDARAM $a
PUSHA
LDAI 100
MOVAB
POPA
CMP
 RJCI loopcnt24
 RJMP loopdn24
loopcnt24: LDARAM $c
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
 RJMP loopstart24
loopdn24: LDARAM $c
LDBI 28
ADDA
STA $c
LDARAM $b
LDBI 1
ADDA
STA $b
 RJMP loopstart25
loopdn25: RET
addBullet: LDAI 0
STA $bulletSearch
loopstart26: LDARAM $bulletSearch
PUSHA
LDAI 10
MOVAB
POPA
CMP
 RJCI loopcnt26
 RJMP loopdn26
loopcnt26: LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDAI 255
MOVAB
POPA
CMP
 RJZI ifcnt59
 RJMP ifskp59
ifcnt59: LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
PUSHC
LDARAM $newBullX
POPC
STARAMC
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
PUSHC
LDARAM $newBullY
POPC
STARAMC
LDARAM $bulletSearch
LDBCMA bulletsDir
ADDC
PUSHC
LDARAM $newBullDir
POPC
STARAMC
LDARAM $bulletSearch
LDBCMA bulletsSpd
ADDC
PUSHC
LDARAM $newBullSpd
POPC
STARAMC
RET
ifskp59: LDARAM $bulletSearch
LDBI 1
ADDA
STA $bulletSearch
 RJMP loopstart26
loopdn26: RET
mult: LDARAM $multx
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt61
 RJMP ifskp61
ifcnt61: LDAI 0
RET
 RJMP if2skp61
ifskp61: LDARAM $multy
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt60
 RJMP ifskp60
ifcnt60: LDAI 0
RET
ifskp60: if2skp61: LDARAM $multy
PUSHA
LDARAM $multx
MOVAB
POPA
CMP
 RJCI ifcnt62
 RJMP ifskp62
ifcnt62: LDARAM $multx
STA $multtemp
LDARAM $multy
STA $multx
LDARAM $multtemp
STA $multy
ifskp62: LDAI 0
STA $multacc
loopstart27: LDAI 0
PUSHA
LDARAM $multx
MOVAB
POPA
CMP
 RJCI loopcnt27
 RJMP loopdn27
loopcnt27: LDARAM $multacc
LDBRAM $multy
ADDA
STA $multacc
LDARAM $multx
LDBI 1
SUBA
STA $multx
 RJMP loopstart27
loopdn27: LDARAM $multacc
RET
divide: LDAI 0
STA $Q
LDARAM $N
STA $R
loopstart28: LDARAM $R
PUSHA
LDARAM $D
MOVAB
POPA
CMP
 RJCI loopdn28
LDARAM $Q
LDBI 1
ADDA
STA $Q
LDARAM $R
LDBRAM $D
SUBA
STA $R
 RJMP loopstart28
loopdn28: RET
drawInvader: LDAI 0
STA $drawPos
LDAI 0
STA $drawY
LDARAM $y
STA $drawAddr
loopstart30: LDARAM $drawY
PUSHA
LDAI 6
MOVAB
POPA
CMP
 RJCI loopcnt30
 RJMP loopdn30
loopcnt30: LDAI 0
STA $drawX
loopstart29: LDARAM $drawX
PUSHA
LDAI 9
MOVAB
POPA
CMP
 RJCI loopcnt29
 RJMP loopdn29
loopcnt29: LDARAM $alienType
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt67
 RJMP ifskp67
ifcnt67: LDARAM $drawPos
LDBCMA invader
ADDC
LDACMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp63
LDARAM $drawAddr
LDBRAM $x
ADDA
VMARA
LDARAM $col
MOVAC
VRCC
ifskp63: RJMP if2skp67
ifskp67: LDARAM $alienType
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt66
 RJMP ifskp66
ifcnt66: LDARAM $drawPos
LDBCMA invader2
ADDC
LDACMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp64
LDARAM $drawAddr
LDBRAM $x
ADDA
VMARA
LDARAM $col
MOVAC
VRCC
ifskp64: RJMP if2skp66
ifskp66: LDARAM $drawPos
LDBCMA invader3
ADDC
LDACMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp65
LDARAM $drawAddr
LDBRAM $x
ADDA
VMARA
LDARAM $col
MOVAC
VRCC
ifskp65: if2skp66: if2skp67: LDARAM $drawPos
LDBI 1
ADDA
STA $drawPos
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
LDBI 9
SUBA
LDBI 128
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart30
loopdn30: RET
drawPlayer: LDAI 0
STA $drawPos
LDAI 0
STA $drawY
LDARAM $y
LDBRAM $drawY
ADDA
STA $multx
LDAI 128
STA $multy
 LCALL mult_loc
STA $drawAddr
loopstart32: LDARAM $drawY
PUSHA
LDAI 8
MOVAB
POPA
CMP
 RJCI loopcnt32
 RJMP loopdn32
loopcnt32: LDAI 0
STA $drawX
loopstart31: LDARAM $drawX
PUSHA
LDAI 13
MOVAB
POPA
CMP
 RJCI loopcnt31
 RJMP loopdn31
loopcnt31: LDARAM $drawY
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI ifcnt69
 RJMP ifskp69
ifcnt69: LDARAM $drawPos
LDBCMA player
ADDC
LDACMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifskp68
LDARAM $drawAddr
LDBRAM $x
ADDA
VMARA
LDARAM $col
MOVAC
VRCC
ifskp68: RJMP if2skp69
ifskp69: LDARAM $drawAddr
LDBRAM $x
ADDA
VMARA
LDARAM $col
MOVAC
VRCC
if2skp69: LDARAM $drawAddr
LDBI 1
ADDA
STA $drawAddr
LDARAM $drawPos
LDBI 1
ADDA
STA $drawPos
LDARAM $drawX
LDBI 1
ADDA
STA $drawX
 RJMP loopstart31
loopdn31: LDARAM $drawAddr
LDBI 128
ADDA
LDBI 13
SUBA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart32
loopdn32: RET
zero: LDARAM $drawAddr
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
LDBCMA numZero
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt70
 RJMP ifskp70
ifcnt70: LDARAM $singleCounter
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
ifskp70: LDARAM $singleCounter
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
LDBCMA invaderYDiff
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
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt35
 RJMP loopdn35
loopcnt35: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numOne
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt71
 RJMP ifskp71
ifcnt71: LDARAM $singleCounter
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
ifskp71: LDARAM $singleCounter
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
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart36
loopdn36: LDARAM $drawAddr
LDBCMA invaderYDiff
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
LDBCMA numTwo
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt72
 RJMP ifskp72
ifcnt72: LDARAM $singleCounter
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
ifskp72: LDARAM $singleCounter
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
LDBCMA invaderYDiff
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
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt39
 RJMP loopdn39
loopcnt39: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numThree
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt73
 RJMP ifskp73
ifcnt73: LDARAM $singleCounter
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
ifskp73: LDARAM $singleCounter
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
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart40
loopdn40: LDARAM $drawAddr
LDBCMA invaderYDiff
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
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt41
 RJMP loopdn41
loopcnt41: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numFour
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt74
 RJMP ifskp74
ifcnt74: LDARAM $singleCounter
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
ifskp74: LDARAM $singleCounter
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
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart42
loopdn42: LDARAM $drawAddr
LDBCMA invaderYDiff
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
loopstart44: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt44
 RJMP loopdn44
loopcnt44: LDAI 0
STA $drawX
loopstart43: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt43
 RJMP loopdn43
loopcnt43: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numFive
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt75
 RJMP ifskp75
ifcnt75: LDARAM $singleCounter
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
ifskp75: LDARAM $singleCounter
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
 RJMP loopstart43
loopdn43: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart44
loopdn44: LDARAM $drawAddr
LDBCMA invaderYDiff
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
loopstart46: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt46
 RJMP loopdn46
loopcnt46: LDAI 0
STA $drawX
loopstart45: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt45
 RJMP loopdn45
loopcnt45: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numSix
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt76
 RJMP ifskp76
ifcnt76: LDARAM $singleCounter
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
ifskp76: LDARAM $singleCounter
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
 RJMP loopstart45
loopdn45: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart46
loopdn46: LDARAM $drawAddr
LDBCMA invaderYDiff
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
loopstart48: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt48
 RJMP loopdn48
loopcnt48: LDAI 0
STA $drawX
loopstart47: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt47
 RJMP loopdn47
loopcnt47: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numSeven
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt77
 RJMP ifskp77
ifcnt77: LDARAM $singleCounter
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
ifskp77: LDARAM $singleCounter
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
 RJMP loopstart47
loopdn47: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart48
loopdn48: LDARAM $drawAddr
LDBCMA invaderYDiff
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
loopstart50: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt50
 RJMP loopdn50
loopcnt50: LDAI 0
STA $drawX
loopstart49: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJCI loopcnt49
 RJMP loopdn49
loopcnt49: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numEight
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt78
 RJMP ifskp78
ifcnt78: LDARAM $singleCounter
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
ifskp78: LDARAM $singleCounter
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
 RJMP loopstart49
loopdn49: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart50
loopdn50: LDARAM $drawAddr
LDBCMA invaderYDiff
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
loopstart52: LDARAM $drawY
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJCI loopcnt52
 RJMP loopdn52
loopcnt52: LDAI 0
STA $drawX
loopstart51: LDARAM $drawX
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJCI loopcnt51
 RJMP loopdn51
loopcnt51: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numNine
ADDC
LDACMC
MOVAB
POPA
CMP
 RJCI ifcnt79
 RJMP ifskp79
ifcnt79: LDARAM $singleCounter
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
ifskp79: LDARAM $singleCounter
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
 RJMP loopstart51
loopdn51: LDARAM $drawAddr
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
 RJMP loopstart52
loopdn52: LDARAM $drawAddr
LDBCMA invaderYDiff
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
LDARAM $padNumWith2Zeroes
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt80
 RJMP ifskp80
ifcnt80: LCALL zero_loc
 LCALL zero_loc
ifskp80: LDARAM $num2Draw
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
 RJZI ifcnt82
 RJMP ifskp82
ifcnt82: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt81
 RJMP ifskp81
ifcnt81: LCALL zero_loc
RET
ifskp81: ifskp82: loopstart53: LDAI 0
PUSHA
LDARAM $Q
MOVAB
POPA
CMP
 RJCI loopcnt53
 RJMP loopdn53
loopcnt53: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt83
 RJMP ifskp83
ifcnt83: LCALL zero_loc
 RJMP drawNumAgain
ifskp83: LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt84
 RJMP ifskp84
ifcnt84: LCALL one_loc
 RJMP drawNumAgain
ifskp84: LDARAM $R
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt85
 RJMP ifskp85
ifcnt85: LCALL two_loc
 RJMP drawNumAgain
ifskp85: LDARAM $R
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJZI ifcnt86
 RJMP ifskp86
ifcnt86: LCALL three_loc
 RJMP drawNumAgain
ifskp86: LDARAM $R
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJZI ifcnt87
 RJMP ifskp87
ifcnt87: LCALL four_loc
 RJMP drawNumAgain
ifskp87: LDARAM $R
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJZI ifcnt88
 RJMP ifskp88
ifcnt88: LCALL five_loc
 RJMP drawNumAgain
ifskp88: LDARAM $R
PUSHA
LDAI 6
MOVAB
POPA
CMP
 RJZI ifcnt89
 RJMP ifskp89
ifcnt89: LCALL six_loc
 RJMP drawNumAgain
ifskp89: LDARAM $R
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJZI ifcnt90
 RJMP ifskp90
ifcnt90: LCALL seven_loc
 RJMP drawNumAgain
ifskp90: LDARAM $R
PUSHA
LDAI 8
MOVAB
POPA
CMP
 RJZI ifcnt91
 RJMP ifskp91
ifcnt91: LCALL eight_loc
 RJMP drawNumAgain
 RJMP if2skp91
ifskp91: LCALL nine_loc
if2skp91: drawNumAgain: LDARAM $Q
STA $N
 LCALL divide_loc
 RJMP loopstart53
loopdn53: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
 RJZI ifcnt92
 RJMP ifskp92
ifcnt92: LCALL zero_loc
RET
ifskp92: LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
 RJZI ifcnt93
 RJMP ifskp93
ifcnt93: LCALL one_loc
RET
ifskp93: LDARAM $R
PUSHA
LDAI 2
MOVAB
POPA
CMP
 RJZI ifcnt94
 RJMP ifskp94
ifcnt94: LCALL two_loc
RET
ifskp94: LDARAM $R
PUSHA
LDAI 3
MOVAB
POPA
CMP
 RJZI ifcnt95
 RJMP ifskp95
ifcnt95: LCALL three_loc
RET
ifskp95: LDARAM $R
PUSHA
LDAI 4
MOVAB
POPA
CMP
 RJZI ifcnt96
 RJMP ifskp96
ifcnt96: LCALL four_loc
RET
ifskp96: LDARAM $R
PUSHA
LDAI 5
MOVAB
POPA
CMP
 RJZI ifcnt97
 RJMP ifskp97
ifcnt97: LCALL five_loc
RET
ifskp97: LDARAM $R
PUSHA
LDAI 6
MOVAB
POPA
CMP
 RJZI ifcnt98
 RJMP ifskp98
ifcnt98: LCALL six_loc
RET
ifskp98: LDARAM $R
PUSHA
LDAI 7
MOVAB
POPA
CMP
 RJZI ifcnt99
 RJMP ifskp99
ifcnt99: LCALL seven_loc
RET
ifskp99: LDARAM $R
PUSHA
LDAI 8
MOVAB
POPA
CMP
 RJZI ifcnt100
 RJMP ifskp100
ifcnt100: LCALL eight_loc
RET
 RJMP if2skp100
ifskp100: LCALL nine_loc
if2skp100: RET
invaderLoc: .DW 0 0
.DW 0 0
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 0
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 0
.DW 0 1
.DW 0 0
.DW 0 1
.DW 0 0
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 0
.DW 0 1
.DW 0 1
.DW 0 0
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 0
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 0
.DW 0 0
invader2Loc: .DW 0 0
.DW 0 0
.DW 0 0
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 0
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 0
invader3Loc: .DW 0 0
.DW 0 0
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 12
.DW 0 0
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 0
.DW 0 12
.DW 0 12
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 12
.DW 0 12
playerLoc: .DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 1
.DW 0 0
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
heartSpriteLoc: .DW 0 0
.DW 0 16
.DW 0 16
.DW 0 0
.DW 0 16
.DW 0 16
.DW 0 0
.DW 0 16
.DW 0 32
.DW 0 32
.DW 0 16
.DW 0 32
.DW 0 32
.DW 0 16
.DW 0 32
.DW 0 48
.DW 0 48
.DW 0 32
.DW 0 48
.DW 0 48
.DW 0 32
.DW 0 16
.DW 0 32
.DW 0 48
.DW 0 48
.DW 0 48
.DW 0 32
.DW 0 16
.DW 0 0
.DW 0 16
.DW 0 48
.DW 0 48
.DW 0 48
.DW 0 16
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 16
.DW 0 32
.DW 0 16
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 0
.DW 0 16
.DW 0 0
.DW 0 0
.DW 0 0
invaderColorChoicesLoc: .DW 0 12
.DW 0 28
.DW 0 14
.DW 0 29
.DW 0 8
.DW 0 4
.DW 0 24
