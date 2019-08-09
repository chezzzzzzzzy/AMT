; This program displays your full name and admission number on the first line of the LCD. The program is being placed in a while loop to emulate a string of words scrolling through continuously. 


; Chester Yee (1718476) and Fang Chen Hao (1718009) 
; DCPE/FT/3A/01

		LIST P=18F97J60			; directive to define processor
		#include <P18F97J60.INC>	; processor specific variable definition
		config XINST = OFF
		config FOSC = HS
		config WDT = OFF
		
		org  0x0000			; set program origin to 0x0000
Display	   	db "Chester Yee P1718476 ",0	; store string in memory location
	    
		org  0x0050			
		total	equ 0x50		; assign variable named total to 0x50
		size1	equ 0x58		; assign variable named size1 to 0x58
		size2	equ 0x66		; assign variable named size2 to 0x66
		count1	equ 0x74		; assign variable named count1 to 0x74
		count2 	equ 0x82		; assign variable named count2 to 0x82

		org	0x0100			; set program origin to 0x0100
MAIN
		call	VARinit			; initialise variable
		call	LCDinit			; initialise lcd
		call	SetPointer		; assign string to word register
		call	ReadArraySize		; get the size of the array

loop1		
		call	CopyValue		; copy value from one file register to another file register
		call	loop2

		bra loop1

	
VARinit		clrf	total			; clear file, total = 0x00
		clrf	size1			; clear file, size1 = 0x00
		clrf	size2			; clear file, size2 = 0x00
		clrf	count1			; clear file, count1 = 0x00
		clrf	count2			; clear file, count2 = 0x00
		return

ReadArraySize		
		tblrd	*+			; read table with post increment
		TSTFSZ	TABLAT			; skip the next instruction if TABLAT is equal to zero
		goto	IncSize			; increase size of array by 1
		call	SetPointer		; assign string to word register
		return
		
IncSize		movlw	D'1'			; assign decimal value of 1 into word register
		addwf	total			; add value in word register to file register and assign it to FR			
		bra	ReadArraySize		; branch to ReadArraySize
		
CopyValue	movff	total,size1		; copy value from total file register to size1 file register
		movff	count2,count1		; copy value from count2 file register to count1 file register
		return
				
		
loop2		movff	total,size2		; copy value from total file register to size2 file register
		call	loop3
		call	DELAY2			; delay is used to allow the string to be printed character by character at a resonable speed
		incf	count1			; store the number of time the loop has been looped
		movff	count1,count2		; copy value from count1 file register to count2 file register
		call	SetRow1		
		call	SetPointer	
				
IncPointer	incf	TBLPTRL			
		DECFSZ	count2			; decrease count2 if its not equal to 0
		bra	IncPointer		; branch to IncPointer if count2 is equal to 0
		DECFSZ	size1			; decrease size1 if its not equal to 0
		bra	loop2			; branch to loop2 if size1 is equal to 0
		return

	
loop3		tblrd	*+			; read table with post increment
		TSTFSZ size2			; skip the next instruction if size2 is equal to zero
		goto	IfNotEmpty		
		return
		
		
IfNotEmpty	call	IfNotEnd
		call	SetPointer
		bra	loop3			; branch to loop3
		
IfNotEnd	TSTFSZ TABLAT			; skip next instruction if TABLAT is equal to zero
		goto	PrintString
		return

		
PrintString	decf	size2
		movff	TABLAT,LATE
		call	LCDSET
		bra	loop3			; branch to loop3
		
		
SetRow1		call LCDRS_0
		movlw 0x80			; set 0x80 to word register
		movwf LATE,0			; assign word register to file register
		call LCDEN_1			
		call LCDEN_0
		return
				
SetPointer	
		movlw	UPPER Display		; assign string to word register, flexibility to allow user to enter a longer string to be displayed on a 32bit display
		movwf	TBLPTRU			; assign word register to file register
		movlw	HIGH Display		; assign string to word register, flexibility to allow user to enter a longer string to be displayed on a 32bit display	  	  
		movwf	TBLPTRH			; assign word register to file register			  
		movlw	LOW Display		; assign string to word register, flexibility to allow user to enter a longer string to be displayed on a 32bit display	  		  
		movwf	TBLPTRL			; assign word register to file register			  
	
		return
		
LCDinit		clrf TRISE,0			; clear TRISE file register
		movlw B'11111000'		; move binary value into word register
		movwf TRISH,0			; move binary value from word register to TRISH
		bcf LATH,LATH1,0		; bit clear file, LATH1 = 0
		call LCDEN_0			
		call LCDRS_0
		
		call LCDRS_0				
		movlw 0x30			; move hex value into word register
		movwf LATE,0			; move hex value from word register to LATE, access bank 0
		call LCDEN_1
		call LCDEN_0
		
		call LCDRS_0
		movlw 0x30			; move hex value into word register
		movwf LATE,0			; move hex value from word register to LATE, access bank 0
		call LCDEN_1
		call LCDEN_0
		
		call LCDRS_0
		movlw 0x30			; move hex value into word register
		movwf LATE,0			; move hex value from word register to LATE, access bank 0
		call LCDEN_1
		call LCDEN_0
				
		call LCDRS_0
		movlw 0x38			; move hex value into word register
		movwf LATE,0			; move hex value from word register to LATE, access bank 0
		call LCDEN_1
		call LCDEN_0
		
		call LCDRS_0
		movlw 0x10			; move hex value into word register
		movwf LATE,0			; move hex value from word register to LATE, access bank 0
		call LCDEN_1
		call LCDEN_0
		
		call LCDRS_0
		movlw 0x0F			; move hex value into word register
		movwf LATE,0			; move hex value from word register to LATE, access bank 0
		call LCDEN_1
		call LCDEN_0
		

		call LCDRS_0
		movlw 0x06			; move hex value into word register
		movwf LATE,0			; move hex value from word register to LATE, access bank 0
		call LCDEN_1
		call LCDEN_0

		call LCDRS_0
		movlw 0x01			; move hex value into word register
		movwf LATE,0			; move hex value from word register to LATE, access bank 0
		call LCDEN_1
		call LCDEN_0

		call DELAY
		
		call SetRow1
		Return

		
LCDEN_0		bcf LATH,LATH0,0	    	; clear LATH0 = 0
		call DELAY
		return
		
LCDEN_1		bsf LATH,LATH0,0	   	; clear LATH0 = 0
		call DELAY
		return
		
LCDRS_0		bcf LATH,LATH2,0	  	; clear LATH2 = 0
		call DELAY
		return
		
LCDRS_1		bsf LATH,LATH2,0	  	; clear LATH2 = 0
		call DELAY
		return

LCDSET		
		call LCDRS_1
		call LCDEN_1
		call LCDEN_0
		return
		
		
DELAY2
		movlw	 0x10		
		Movwf 0x02,0	
		
LDELAY1	    	decf	0x03,1,0		; Inner Loop 		[ 1 cy ]
		bnz   LDELAY1			;           		[ 2 cy ]
		decf  0x01,1,0			; Outer Loop 		[ 1 cy ]
		bnz	LDELAY1			;                   	[ 2 cy ]
		decf  0x02,1,0			; Outer Loop 		[ 1 cy ]
		bnz	LDELAY1			;  		
		RETURN

DELAY
		MOVLW 8				; Copy 8 to W
		MOVWF 0X15			; Copy W into L2
		
LOOP2	        MOVLW 255			; Copy 255 into W
		MOVWF 0X14			; Copy W into L1
		 
LOOP1		decfsz 0X14,F                   ; Decrement L1. If 0 Skip next instruction
		GOTO LOOP1			; ELSE Keep counting down
		decfsz 0X15,F                   ; Decrement L2. If 0 Skip next instruction
		GOTO LOOP2			; ELSE Keep counting down		

		RETURN
		
			
		END




