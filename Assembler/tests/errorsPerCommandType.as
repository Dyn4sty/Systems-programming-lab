;arithmetic no space after command
H: add$5,$4,$3
;arithmetic no space after label
X:add $5, $3, $28
;arithmetic invalid registers:
Y: and $55, $1, $0
Z: or $-1, $2, $3
damn: add $1, or, $2
ohNo: add $5, "or", $2
ayeNo: add 21, $5, $29
;arithmetic excessive arguments:
J: add $1, $2, $3, $4
excessiveWithComma: add $2, $3, $2,
;arithmetic missing arguments:
missing: add $1, $2
missingWithComma: add $3, $5, 


;conditional no space after command
L: bne$5,$4,Z
;conditional invalid registers:
T: bne $55, $1, loop
V: bne $-1, $2, damn
damn13: bne $1, or, why
ohNo5: bne $5, "or", X
ayeNo44: bne 21, $5, xmen
registerInstead123: bne $3, $5, $2
;conditional excessive arguments:
m: bne $1, $2, loop, shmoop
excessiveWithComma2: bne $2, $3, doop,
;conditional missing arguments:
missing13: bne $1, $2
missingWithComma232: bne $3, $5, 


;copy no space after command
H3: move$5,$4
;copy no space after label
X1:move $5, $3
;copy invalid registers:
Y1: move $55, $1
Z1: mvhi $-1, $2
damn32: mvlo $1, or
ohNo12: move $5, "or"
ayeNo3: move 21, $5
;copy excessive arguments:
J31: move $1, $2, $3
excessiveWithComma: move $2, $3,
;copy missing arguments:
missing43: move $1
missingWithComma65: move $3,


;arithmeticI no space after command
H33: addi$5,-45,$3
;arithmeticI no space after label
X332:addi $5, -45, $28
;arithmeticI invalid registers:
Y31: andi $55, -45, $0
Z3123: ori $-1, -45, $3
damnf: addi $1, or, $2
ohNoa: addi $5, "or", $2
ayeNoz: addi 21, 45, $29
outOfRange2: addi $2, 34563456346546, $29
outOfRangeToo2: ori $2, -23452345234523452, $20
outOfRangeCloseToMin31: ori $3, -32769, $21
outOfRangeCloseToMax1: ori $3, 32768, $15
outOfRangeLimitOfIntMax12: ori $3, 2147483648, $13
outOfRangeLimitOfIntMin32: ori $10, -2147483649, $14 
;arithmeticI excessive arguments:
J44: addi $1, 55, $3, $4
excessiveWithComma55: addi $2, 3, $2,
;arithmeticI missing arguments:
missing12: addi $1, 2
missingWithComma24: addi $3, 5, 


;call no space after command
H554: call$5,$4,Z
;call invalid argument:
Y45: call 1loop
call $22
ayeNo134: call "xmen"
;call excessive arguments:
J121: call loop, shmoop
excessiveWithComma0: call doop,
;call missing arguments:
missingz: call 
missingWithCommaz: call , 
;jmp illegal register:
jojozz: jmp $-2
joji12: jmp $33

;stop excessive arguments:
lastOnes45: stop 555
Iswear5454: stop hi
