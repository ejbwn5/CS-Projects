LCALL mainAdd
end:  JMP end
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
CALL genRand
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
CALL divide
LDAI 32
LDBRAM $R
ADDA
STA $framesTillEnemyShoot
CALL genRand
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
CALL divide
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
CALL genRand
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
JMP loopdn5
loopcnt5: LDARAM $rand
STA $N
LDAI 7
STA $D
CALL divide
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
CALL genRand
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
JCI loopcnt6
JMP loopdn6
loopcnt6: LDARAM $rand
STA $N
LDAI 7
STA $D
CALL divide
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
CALL genRand
LDARAM $y
LDBI 1
ADDA
STA $y
JMP loopstart6
loopdn6: LDARAM $level
STA $maxLevelAlien
LDAI 3
PUSHA
LDARAM $maxLevelAlien
MOVAB
POPA
CMP
JCI ifcnt1
JMP ifskp1
ifcnt1: LDAI 3
STA $maxLevelAlien
ifskp1: LDARAM $rand
STA $N
LDARAM $maxLevelAlien
STA $D
CALL divide
LDARAM $R
STA $invadersRow1Type
CALL genRand
LDARAM $rand
STA $N
CALL divide
LDARAM $R
STA $invadersRow2Type
CALL genRand
LDARAM $rand
STA $N
CALL divide
LDARAM $R
STA $invadersRow3Type
CALL genRand
goBack: LDARAM $rand
STA $N
LDAI 8
STA $D
CALL divide
LDAI 32
LDBRAM $R
ADDA
STA $framesTillEnemyShoot
CALL genRand
loopstart17: LDAI 1
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI loopdn17
CALL clearScreen
LDAIO
STA $io
LDARAM $io
STA $N
LDAI 2
STA $D
CALL divide
LDARAM $Q
STA $N
LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
JZI ifcnt3
JMP ifskp3
ifcnt3: LDAI 0
PUSHA
LDARAM $playerX
MOVAB
POPA
CMP
JCI ifcnt2
JMP ifskp2
ifcnt2: LDARAM $playerX
LDBI 1
SUBA
STA $playerX
ifskp2: ifskp3: CALL divide
LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
JZI ifcnt5
JMP ifskp5
ifcnt5: LDARAM $playerX
PUSHA
LDAI 87
MOVAB
POPA
CMP
JCI ifcnt4
JMP ifskp4
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
CALL divide
LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
JZI ifcnt6
JMP ifskp6
ifcnt6: LDAI 1
STA $shoot
ifskp6: LDARAM $shoot
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp8
LDARAM $shootLast
PUSHA
LDAI 1
MOVAB
POPA
CMP
JZI ifskp7
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
CALL addBullet
ifskp7: ifskp8: LDARAM $framesTillEnemyShoot
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifcnt19
JMP ifskp19
ifcnt19: LDARAM $rand
STA $N
LDAI 8
STA $D
CALL divide
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
JCI ifcnt9
JMP ifskp9
ifcnt9: LDAI 1
STA $framesTillEnemyShoot
ifskp9: CALL genRand
LDAI 1
STA $newBullDir
LDARAM $rand
STA $N
LDAI 9
STA $D
CALL divide
LDARAM $R
LDBCMA invadersRow3
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp18
LDARAM $R
STA $multx
LDAI 10
STA $multy
LDARAM $invaderX
PUSHA
CALL mult
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
JZI ifcnt11
JMP ifskp11
ifcnt11: LDAI 1
STA $newBullSpd
JMP if2skp11
ifskp11: LDARAM $invadersRow3Type
PUSHA
LDAI 1
MOVAB
POPA
CMP
JZI ifcnt10
JMP ifskp10
ifcnt10: LDAI 2
STA $newBullSpd
JMP if2skp10
ifskp10: LDAI 3
STA $newBullSpd
if2skp10: if2skp11: CALL addBullet
JMP if2skp18
ifskp18: LDARAM $R
LDBCMA invadersRow2
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp17
LDARAM $R
STA $multx
LDAI 10
STA $multy
LDAI 14
LDBRAM $invaderX
SUBA
PUSHA
CALL mult
MOVAB
POPA
ADDA
STA $newBullX
LDAI 21
STA $newBullY
LDARAM $invadersRow2Type
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifcnt13
JMP ifskp13
ifcnt13: LDAI 1
STA $newBullSpd
JMP if2skp13
ifskp13: LDARAM $invadersRow2Type
PUSHA
LDAI 1
MOVAB
POPA
CMP
JZI ifcnt12
JMP ifskp12
ifcnt12: LDAI 2
STA $newBullSpd
JMP if2skp12
ifskp12: LDAI 3
STA $newBullSpd
if2skp12: if2skp13: CALL addBullet
JMP if2skp17
ifskp17: LDARAM $R
LDBCMA invadersRow1
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp16
LDARAM $R
STA $multx
LDAI 10
STA $multy
LDARAM $invaderX
PUSHA
CALL mult
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
JZI ifcnt15
JMP ifskp15
ifcnt15: LDAI 1
STA $newBullSpd
JMP if2skp15
ifskp15: LDARAM $invadersRow1Type
PUSHA
LDAI 1
MOVAB
POPA
CMP
JZI ifcnt14
JMP ifskp14
ifcnt14: LDAI 2
STA $newBullSpd
JMP if2skp14
ifskp14: LDAI 3
STA $newBullSpd
if2skp14: if2skp15: CALL addBullet
ifskp16: if2skp17: if2skp18: ifskp19: LDAI 0
STA $bulletSearch
loopstart10: LDARAM $bulletSearch
PUSHA
LDAI 10
MOVAB
POPA
CMP
JCI loopcnt10
JMP loopdn10
loopcnt10: LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDAI 255
MOVAB
POPA
CMP
JZI ifskp44
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
MOVAB
POPA
CMP
JZI ifcnt42
JMP ifskp42
ifcnt42: LDAI 128
STA $multy
LDARAM $y
STA $multx
CALL mult
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
JCI ifcnt26
JMP ifskp26
ifcnt26: LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
PUSHA
LDACMA playerY
LDBI 8
ADDA
MOVAB
POPA
CMP
JCI ifcnt22
JMP ifskp22
ifcnt22: LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDARAM $playerX
MOVAB
POPA
CMP
JCI ifskp21
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
JCI ifcnt20
JMP ifskp20
ifcnt20: JMP playerHit
ifskp20: ifskp21: ifskp22: JMP if2skp26
ifskp26: LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
PUSHA
LDACMA playerY
MOVAB
POPA
CMP
JCI ifskp25
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
JCI ifskp24
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
JCI ifcnt23
JMP ifskp23
ifcnt23: JMP playerHit
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
JMP if2skp42
ifskp42: LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
PUSHA
LDAI 30
MOVAB
POPA
CMP
JCI ifcnt41
JMP ifskp41
ifcnt41: LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
PUSHA
LDAI 24
MOVAB
POPA
CMP
JCI ifskp30
LDAI 0
STA $invaderInd
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
JCI loopcnt7
JMP loopdn7
loopcnt7: LDARAM $invaderInd
LDBCMA invadersRow3
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp29
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDARAM $x2
MOVAB
POPA
CMP
JCI ifskp28
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
JCI ifskp27
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
JMP nextBullet
ifskp27: ifskp28: ifskp29: LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
LDARAM $x2
LDBI 10
ADDA
STA $x2
JMP loopstart7
loopdn7: ifskp30: LDAI 22
PUSHA
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
MOVAB
POPA
CMP
JCI ifskp35
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
PUSHA
LDAI 17
MOVAB
POPA
CMP
JCI ifskp34
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
JCI loopcnt8
JMP loopdn8
loopcnt8: LDARAM $invaderInd
LDBCMA invadersRow2
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp33
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDARAM $x2
MOVAB
POPA
CMP
JCI ifskp32
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
JCI ifskp31
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
LDBCMA invadersRow2
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
LDBRAM $invadersRow2Type
ADDA
STA $score
JMP nextBullet
ifskp31: ifskp32: ifskp33: LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
LDARAM $x2
LDBI 10
ADDA
STA $x2
JMP loopstart8
loopdn8: ifskp34: ifskp35: LDAI 15
PUSHA
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
MOVAB
POPA
CMP
JCI ifskp40
LDARAM $bulletSearch
LDBCMA bulletsY
ADDC
LDARAMC
PUSHA
LDAI 10
MOVAB
POPA
CMP
JCI ifskp39
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
JCI loopcnt9
JMP loopdn9
loopcnt9: LDARAM $invaderInd
LDBCMA invadersRow1
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp38
LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDARAM $x2
MOVAB
POPA
CMP
JCI ifskp37
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
JCI ifskp36
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
LDBCMA invadersRow1
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
JMP nextBullet
ifskp36: ifskp37: ifskp38: LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
LDARAM $x2
LDBI 10
ADDA
STA $x2
JMP loopstart9
loopdn9: ifskp39: ifskp40: ifskp41: LDAI 128
STA $multy
LDARAM $y
STA $multx
CALL mult
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
MOVAC
VRCC
LDARAM $bulletSearch
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
JCI ifcnt43
JMP ifskp43
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
JMP loopstart10
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
CALL mult
STA $y
LDAI 0
STA $invaderInd
loopstart11: LDARAM $invaderInd
PUSHA
LDAI 9
MOVAB
POPA
CMP
JCI loopcnt11
JMP loopdn11
loopcnt11: LDARAM $invaderInd
LDBCMA invadersRow1
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp45
LDARAM $invaderInd
LDBCMA invadersRow1Col
ADDC
LDARAMC
STA $col
LDARAM $invadersRow1Type
STA $alienType
CALL drawInvader
ifskp45: LDARAM $x
LDBI 10
ADDA
STA $x
LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
JMP loopstart11
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
JCI loopcnt12
JMP loopdn12
loopcnt12: LDARAM $invaderInd
LDBCMA invadersRow2
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp46
LDARAM $invaderInd
LDBCMA invadersRow2Col
ADDC
LDARAMC
STA $col
LDARAM $invadersRow2Type
STA $alienType
CALL drawInvader
ifskp46: LDARAM $x
LDBI 10
ADDA
STA $x
LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
JMP loopstart12
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
JCI loopcnt13
JMP loopdn13
loopcnt13: LDARAM $invaderInd
LDBCMA invadersRow3
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp47
LDARAM $invaderInd
LDBCMA invadersRow3Col
ADDC
LDARAMC
STA $col
LDARAM $invadersRow3Type
STA $alienType
CALL drawInvader
ifskp47: LDARAM $x
LDBI 10
ADDA
STA $x
LDARAM $invaderInd
LDBI 1
ADDA
STA $invaderInd
JMP loopstart13
loopdn13: LDAI 63
STA $col
LDACMA playerY
STA $y
LDARAM $playerX
STA $x
CALL drawPlayer
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
CALL drawNum
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
JCI loopcnt15
JMP loopdn15
loopcnt15: LDAI 0
STA $x
loopstart14: LDARAM $x
PUSHA
LDAI 7
MOVAB
POPA
CMP
JCI loopcnt14
JMP loopdn14
loopcnt14: LDAI 0
PUSHA
LDARAM $x2
LDBCMA heartSprite
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt48
JMP ifskp48
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
LDBI 1
ADDA
STA $y2
JMP loopstart14
loopdn14: LDARAM $y2
LDBI 121
ADDA
STA $y2
LDARAM $y
LDBI 1
ADDA
STA $y
JMP loopstart15
loopdn15: LDAI 16
STA $col
LDAI 0
STA $padNumWith2Zeroes
LDAI 10
STA $drawX
LDAI 1
STA $drawY
LDARAM $lives
STA $num2Draw
CALL drawNum
FLIP
LDAI 0
STA $y
loopstart16: LDARAM $y
PUSHA
LDAI 9
MOVAB
POPA
CMP
JCI loopcnt16
JMP loopdn16
loopcnt16: LDARAM $y
LDBCMA invadersRow1
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp49
JMP notNextLevel
ifskp49: LDARAM $y
LDBCMA invadersRow2
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp50
JMP notNextLevel
ifskp50: LDARAM $y
LDBCMA invadersRow3
ADDC
LDARAMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp51
JMP notNextLevel
ifskp51: LDARAM $y
LDBI 1
ADDA
STA $y
JMP loopstart16
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
JCI ifcnt52
JMP ifskp52
ifcnt52: LDAI 0
STA $amt
ifskp52: LDARAM $amt
PUSHA
LDARAM $invaderFrameCounter
MOVAB
POPA
CMP
JCI ifcnt56
JMP ifskp56
ifcnt56: LDAI 0
STA $invaderFrameCounter
LDARAM $invaderDir
PUSHA
LDAI 1
MOVAB
POPA
CMP
JZI ifcnt55
JMP ifskp55
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
JZI ifcnt53
JMP ifskp53
ifcnt53: LDAI 0
STA $invaderDir
ifskp53: JMP if2skp55
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
JZI ifcnt54
JMP ifskp54
ifcnt54: LDAI 1
STA $invaderDir
ifskp54: if2skp55: ifskp56: JMP loopstart17
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
JCI ifcnt57
JMP ifskp57
ifcnt57: LDAI 0
STA $bulletSearch
loopstart18: LDARAM $bulletSearch
PUSHA
LDAI 9
MOVAB
POPA
CMP
JCI loopcnt18
JMP loopdn18
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
JMP loopstart18
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
JCI loopcnt19
JMP loopdn19
loopcnt19: CALL clearScreen
FLIP
LDARAM $y
LDBI 1
ADDA
STA $y
JMP loopstart19
loopdn19: JMP goBack
ifskp57: CALL clearScreen
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
CALL drawNum
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
JCI loopcnt21
JMP loopdn21
loopcnt21: LDAI 0
STA $x
loopstart20: LDARAM $x
PUSHA
LDAI 7
MOVAB
POPA
CMP
JCI loopcnt20
JMP loopdn20
loopcnt20: LDAI 0
PUSHA
LDARAM $x2
LDBCMA heartSprite
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt58
JMP ifskp58
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
JMP loopstart20
loopdn20: LDARAM $y2
LDBI 121
ADDA
STA $y2
LDARAM $y
LDBI 1
ADDA
STA $y
JMP loopstart21
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
CALL drawNum
FLIP
LDAIO
STA $io
loopstart22: LDARAM $io
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI loopdn22
LDAIO
STA $io
JMP loopstart22
loopdn22: loopstart23: LDARAM $io
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI loopcnt23
JMP loopdn23
loopcnt23: LDAIO
STA $io
JMP loopstart23
loopdn23: JMP reset
LDAI 0
RET
RET
genRand: LDAI 239
STA $multx
LDARAM $rand
STA $multy
CALL mult
LDBCMA randAdd
ADDA
STA $rand
RET
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
JCI loopcnt25
JMP loopdn25
loopcnt25: LDAI 0
STA $a
loopstart24: LDARAM $a
PUSHA
LDAI 100
MOVAB
POPA
CMP
JCI loopcnt24
JMP loopdn24
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
JMP loopstart24
loopdn24: LDARAM $c
LDBI 28
ADDA
STA $c
LDARAM $b
LDBI 1
ADDA
STA $b
JMP loopstart25
loopdn25: RET
RET
addBullet: LDAI 0
STA $bulletSearch
loopstart26: LDARAM $bulletSearch
PUSHA
LDAI 10
MOVAB
POPA
CMP
JCI loopcnt26
JMP loopdn26
loopcnt26: LDARAM $bulletSearch
LDBCMA bulletsX
ADDC
LDARAMC
PUSHA
LDAI 255
MOVAB
POPA
CMP
JZI ifcnt59
JMP ifskp59
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
JMP loopstart26
loopdn26: RET
RET
mult: LDARAM $multx
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifcnt61
JMP ifskp61
ifcnt61: LDAI 0
RET
JMP if2skp61
ifskp61: LDARAM $multy
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifcnt60
JMP ifskp60
ifcnt60: LDAI 0
RET
ifskp60: if2skp61: LDARAM $multy
PUSHA
LDARAM $multx
MOVAB
POPA
CMP
JCI ifcnt62
JMP ifskp62
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
JCI loopcnt27
JMP loopdn27
loopcnt27: LDARAM $multacc
LDBRAM $multy
ADDA
STA $multacc
LDARAM $multx
LDBI 1
SUBA
STA $multx
JMP loopstart27
loopdn27: LDARAM $multacc
RET
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
JCI loopdn28
LDARAM $Q
LDBI 1
ADDA
STA $Q
LDARAM $R
LDBRAM $D
SUBA
STA $R
JMP loopstart28
loopdn28: RET
RET
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
JCI loopcnt30
JMP loopdn30
loopcnt30: LDAI 0
STA $drawX
loopstart29: LDARAM $drawX
PUSHA
LDAI 9
MOVAB
POPA
CMP
JCI loopcnt29
JMP loopdn29
loopcnt29: LDARAM $alienType
PUSHA
LDAI 1
MOVAB
POPA
CMP
JZI ifcnt67
JMP ifskp67
ifcnt67: LDARAM $drawPos
LDBCMA invader
ADDC
LDACMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp63
LDARAM $drawAddr
LDBRAM $x
ADDA
VMARA
LDARAM $col
MOVAC
VRCC
ifskp63: JMP if2skp67
ifskp67: LDARAM $alienType
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifcnt66
JMP ifskp66
ifcnt66: LDARAM $drawPos
LDBCMA invader2
ADDC
LDACMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp64
LDARAM $drawAddr
LDBRAM $x
ADDA
VMARA
LDARAM $col
MOVAC
VRCC
ifskp64: JMP if2skp66
ifskp66: LDARAM $drawPos
LDBCMA invader3
ADDC
LDACMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp65
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
JMP loopstart29
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
JMP loopstart30
loopdn30: RET
RET
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
CALL mult
STA $drawAddr
loopstart32: LDARAM $drawY
PUSHA
LDAI 8
MOVAB
POPA
CMP
JCI loopcnt32
JMP loopdn32
loopcnt32: LDAI 0
STA $drawX
loopstart31: LDARAM $drawX
PUSHA
LDAI 13
MOVAB
POPA
CMP
JCI loopcnt31
JMP loopdn31
loopcnt31: LDARAM $drawY
PUSHA
LDAI 4
MOVAB
POPA
CMP
JCI ifcnt69
JMP ifskp69
ifcnt69: LDARAM $drawPos
LDBCMA player
ADDC
LDACMC
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifskp68
LDARAM $drawAddr
LDBRAM $x
ADDA
VMARA
LDARAM $col
MOVAC
VRCC
ifskp68: JMP if2skp69
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
JMP loopstart31
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
JMP loopstart32
loopdn32: RET
RET
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
JCI loopcnt34
JMP loopdn34
loopcnt34: LDAI 0
STA $drawX
loopstart33: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
JCI loopcnt33
JMP loopdn33
loopcnt33: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numZero
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt70
JMP ifskp70
ifcnt70: LDARAM $singleCounter
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
JMP loopstart33
loopdn33: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
JMP loopstart34
loopdn34: LDARAM $drawAddr
LDBCMA invaderYDiff
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
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
JCI loopcnt36
JMP loopdn36
loopcnt36: LDAI 0
STA $drawX
loopstart35: LDARAM $drawX
PUSHA
LDAI 4
MOVAB
POPA
CMP
JCI loopcnt35
JMP loopdn35
loopcnt35: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numOne
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt71
JMP ifskp71
ifcnt71: LDARAM $singleCounter
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
JMP loopstart35
loopdn35: LDARAM $drawAddr
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
JMP loopstart36
loopdn36: LDARAM $drawAddr
LDBCMA invaderYDiff
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
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
JCI loopcnt38
JMP loopdn38
loopcnt38: LDAI 0
STA $drawX
loopstart37: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
JCI loopcnt37
JMP loopdn37
loopcnt37: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numTwo
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt72
JMP ifskp72
ifcnt72: LDARAM $singleCounter
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
JMP loopstart37
loopdn37: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
JMP loopstart38
loopdn38: LDARAM $drawAddr
LDBCMA invaderYDiff
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
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
JCI loopcnt40
JMP loopdn40
loopcnt40: LDAI 0
STA $drawX
loopstart39: LDARAM $drawX
PUSHA
LDAI 4
MOVAB
POPA
CMP
JCI loopcnt39
JMP loopdn39
loopcnt39: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numThree
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt73
JMP ifskp73
ifcnt73: LDARAM $singleCounter
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
JMP loopstart39
loopdn39: LDARAM $drawAddr
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
JMP loopstart40
loopdn40: LDARAM $drawAddr
LDBCMA invaderYDiff
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
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
JCI loopcnt42
JMP loopdn42
loopcnt42: LDAI 0
STA $drawX
loopstart41: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
JCI loopcnt41
JMP loopdn41
loopcnt41: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numFour
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt74
JMP ifskp74
ifcnt74: LDARAM $singleCounter
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
JMP loopstart41
loopdn41: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
JMP loopstart42
loopdn42: LDARAM $drawAddr
LDBCMA invaderYDiff
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
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
JCI loopcnt44
JMP loopdn44
loopcnt44: LDAI 0
STA $drawX
loopstart43: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
JCI loopcnt43
JMP loopdn43
loopcnt43: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numFive
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt75
JMP ifskp75
ifcnt75: LDARAM $singleCounter
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
JMP loopstart43
loopdn43: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
JMP loopstart44
loopdn44: LDARAM $drawAddr
LDBCMA invaderYDiff
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
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
JCI loopcnt46
JMP loopdn46
loopcnt46: LDAI 0
STA $drawX
loopstart45: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
JCI loopcnt45
JMP loopdn45
loopcnt45: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numSix
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt76
JMP ifskp76
ifcnt76: LDARAM $singleCounter
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
JMP loopstart45
loopdn45: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
JMP loopstart46
loopdn46: LDARAM $drawAddr
LDBCMA invaderYDiff
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
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
JCI loopcnt48
JMP loopdn48
loopcnt48: LDAI 0
STA $drawX
loopstart47: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
JCI loopcnt47
JMP loopdn47
loopcnt47: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numSeven
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt77
JMP ifskp77
ifcnt77: LDARAM $singleCounter
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
JMP loopstart47
loopdn47: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
JMP loopstart48
loopdn48: LDARAM $drawAddr
LDBCMA invaderYDiff
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
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
JCI loopcnt50
JMP loopdn50
loopcnt50: LDAI 0
STA $drawX
loopstart49: LDARAM $drawX
PUSHA
LDAI 5
MOVAB
POPA
CMP
JCI loopcnt49
JMP loopdn49
loopcnt49: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numEight
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt78
JMP ifskp78
ifcnt78: LDARAM $singleCounter
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
JMP loopstart49
loopdn49: LDARAM $drawAddr
LDBI 123
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
JMP loopstart50
loopdn50: LDARAM $drawAddr
LDBCMA invaderYDiff
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
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
JCI loopcnt52
JMP loopdn52
loopcnt52: LDAI 0
STA $drawX
loopstart51: LDARAM $drawX
PUSHA
LDAI 4
MOVAB
POPA
CMP
JCI loopcnt51
JMP loopdn51
loopcnt51: LDAI 0
PUSHA
LDARAM $singleCounter
LDBCMA numNine
ADDC
LDACMC
MOVAB
POPA
CMP
JCI ifcnt79
JMP ifskp79
ifcnt79: LDARAM $singleCounter
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
JMP loopstart51
loopdn51: LDARAM $drawAddr
LDBI 124
ADDA
STA $drawAddr
LDARAM $drawY
LDBI 1
ADDA
STA $drawY
JMP loopstart52
loopdn52: LDARAM $drawAddr
LDBCMA invaderYDiff
SUBA
STA $drawAddr
LDARAM $drawAddr
LDBI 5
SUBA
STA $drawAddr
RET
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
JZI ifcnt80
JMP ifskp80
ifcnt80: CALL zero
CALL zero
ifskp80: LDARAM $num2Draw
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
JZI ifcnt82
JMP ifskp82
ifcnt82: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifcnt81
JMP ifskp81
ifcnt81: CALL zero
RET
ifskp81: ifskp82: loopstart53: LDAI 0
PUSHA
LDARAM $Q
MOVAB
POPA
CMP
JCI loopcnt53
JMP loopdn53
loopcnt53: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifcnt83
JMP ifskp83
ifcnt83: CALL zero
JMP drawNumAgain
ifskp83: LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
JZI ifcnt84
JMP ifskp84
ifcnt84: CALL one
JMP drawNumAgain
ifskp84: LDARAM $R
PUSHA
LDAI 2
MOVAB
POPA
CMP
JZI ifcnt85
JMP ifskp85
ifcnt85: CALL two
JMP drawNumAgain
ifskp85: LDARAM $R
PUSHA
LDAI 3
MOVAB
POPA
CMP
JZI ifcnt86
JMP ifskp86
ifcnt86: CALL three
JMP drawNumAgain
ifskp86: LDARAM $R
PUSHA
LDAI 4
MOVAB
POPA
CMP
JZI ifcnt87
JMP ifskp87
ifcnt87: CALL four
JMP drawNumAgain
ifskp87: LDARAM $R
PUSHA
LDAI 5
MOVAB
POPA
CMP
JZI ifcnt88
JMP ifskp88
ifcnt88: CALL five
JMP drawNumAgain
ifskp88: LDARAM $R
PUSHA
LDAI 6
MOVAB
POPA
CMP
JZI ifcnt89
JMP ifskp89
ifcnt89: CALL six
JMP drawNumAgain
ifskp89: LDARAM $R
PUSHA
LDAI 7
MOVAB
POPA
CMP
JZI ifcnt90
JMP ifskp90
ifcnt90: CALL seven
JMP drawNumAgain
ifskp90: LDARAM $R
PUSHA
LDAI 8
MOVAB
POPA
CMP
JZI ifcnt91
JMP ifskp91
ifcnt91: CALL eight
JMP drawNumAgain
JMP if2skp91
ifskp91: CALL nine
if2skp91: drawNumAgain: LDARAM $Q
STA $N
CALL divide
JMP loopstart53
loopdn53: LDARAM $R
PUSHA
LDAI 0
MOVAB
POPA
CMP
JZI ifcnt92
JMP ifskp92
ifcnt92: CALL zero
RET
ifskp92: LDARAM $R
PUSHA
LDAI 1
MOVAB
POPA
CMP
JZI ifcnt93
JMP ifskp93
ifcnt93: CALL one
RET
ifskp93: LDARAM $R
PUSHA
LDAI 2
MOVAB
POPA
CMP
JZI ifcnt94
JMP ifskp94
ifcnt94: CALL two
RET
ifskp94: LDARAM $R
PUSHA
LDAI 3
MOVAB
POPA
CMP
JZI ifcnt95
JMP ifskp95
ifcnt95: CALL three
RET
ifskp95: LDARAM $R
PUSHA
LDAI 4
MOVAB
POPA
CMP
JZI ifcnt96
JMP ifskp96
ifcnt96: CALL four
RET
ifskp96: LDARAM $R
PUSHA
LDAI 5
MOVAB
POPA
CMP
JZI ifcnt97
JMP ifskp97
ifcnt97: CALL five
RET
ifskp97: LDARAM $R
PUSHA
LDAI 6
MOVAB
POPA
CMP
JZI ifcnt98
JMP ifskp98
ifcnt98: CALL six
RET
ifskp98: LDARAM $R
PUSHA
LDAI 7
MOVAB
POPA
CMP
JZI ifcnt99
JMP ifskp99
ifcnt99: CALL seven
RET
ifskp99: LDARAM $R
PUSHA
LDAI 8
MOVAB
POPA
CMP
JZI ifcnt100
JMP ifskp100
ifcnt100: CALL eight
RET
JMP if2skp100
ifskp100: CALL nine
if2skp100: RET
RET
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
