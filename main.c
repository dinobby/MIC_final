// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

#include <xc.h>
#include <htc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define _XTAL_FREQ 10000

#define row1 LATCbits.LATC4
#define row2 LATBbits.LATB1
#define row3 LATBbits.LATB2
#define row4 LATBbits.LATB3
#define row5 LATBbits.LATB4
#define row6 LATBbits.LATB5
#define row7 LATCbits.LATC5
#define row8 LATCbits.LATC6

#define btn_left PORTAbits.RA3
#define btn_right PORTAbits.RA4

int generate_enemy(){
//    srand(time(NULL) );
    int min = 1;
    int max = 6;
    int x = rand() % (max - min + 1) + min;
    return x;
}

char init_board[8] = {
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111    
};

char lr_board[2] = {
    0b11111011,
    0b11110001    
};

int plane;

void shift(void){
    init_board[0] = init_board[1];
    init_board[1] = init_board[2];
    init_board[2] = init_board[3];
    init_board[3] = init_board[4];
    init_board[4] = init_board[5];
    init_board[5] = init_board[6];
    init_board[6] = init_board[7];
    if (rand() % (2)){
        int x = generate_enemy();
        init_board[7] = 0b11111111 - (int) pow((double) 2,x);
    }
    else{
        init_board[7] = 0b11111111;
    }
}

char led_pos[8] = {
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111
};

void shift2(void){
    led_pos[7] = led_pos[6];
    led_pos[6] = led_pos[5];
    led_pos[5] = led_pos[4];
    led_pos[4] = led_pos[3];
    led_pos[3] = led_pos[2];
    led_pos[2] = led_pos[1];
    led_pos[1] = led_pos[0];
    if (rand() % (2)){
        int x = generate_enemy();
        led_pos[0] = 0b11111111 - (int) pow((double) 2,x);
    }
    else{
        led_pos[0] = 0b11111111;
    }
    
}

void main(void) {
    TRISA3 = 1;
    TRISA4 = 1;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0xff;
    int j = 0;
    
    while(1){
//        LATD = 0;
//        row1 = 1;
//        row2 = 0;
//        row3 = 0;
//        row4 = 0;
//        row5 = 0;
//        row6 = 0;
//        row7 = 0;
//        row8 = 0;
//        
//        LATD = (init_board[0] & led_pos[0]);
//         __delay_ms(100);
//        row1 = 0;
//        
//        row2 = 1;
//        LATD = (init_board[1] & led_pos[1]);
//        __delay_ms(100);
//        LATD = 0;
//        row2 = 0;
//         
//        row3 = 1;
//        LATD = (init_board[2] & led_pos[2]);
//        __delay_ms(100);
//        LATD = 0;
//        row3 = 0;
//
//        row4 = 1;
//        LATD = (init_board[3] & led_pos[3]);
//        __delay_ms(100);
//        LATD = 0;
//        row4 = 0;
//
//        row5 = 1;
//        LATD = (init_board[4] & led_pos[4]);
//        __delay_ms(100);
//        LATD = 0;
//        row5 = 0;
//        
//        row6 = 1;
//        LATD = (init_board[5] & led_pos[5]);
//        __delay_ms(100);
//        LATD = 0;
//        row6 = 0;
//
//        row7 = 1;
//        LATD = (init_board[6] & led_pos[6] & lr_board[0]);
//        __delay_ms(100);
//        LATD = 0;
//        row7 = 0;
//
        row8 = 1;
        LATD = (init_board[7] & led_pos[7] & lr_board[1]) ;
//        __delay_ms(100);
//        LATD = 0;
//        row8 = 0;
//        
//       __delay_ms(100);
//       
       if(RA4 == 0){
               lr_board[0] = ~lr_board[0];
               lr_board[0] = lr_board[0] << 1;
               lr_board[0] = ~lr_board[0];
               lr_board[1] = ~lr_board[1];
               lr_board[1] = lr_board[1] << 1;
               lr_board[1] = ~lr_board[1];
               __delay_ms(100000);
           }
       j++;
       if (j > 200){
          // __delay_ms(1000);
//           shift();

//           else if(!btn_left & btn_right){
//               lr_board[0] = lr_board[0]>>1;
//               lr_board[1] = lr_board[1]>>1;    
//               //__delay_ms(1000);
//           }
           //shift2();
           j = 0;
           
       }
       
//    row4 = 1;
//    LATD = led_pos[3];
//    __delay_ms(10);
//    row5 = 1;
//    LATD = led_pos[4];
//    __delay_ms(10);
//    row6 = 1;
//    LATD = led_pos[5];
//    __delay_ms(10);
//    row7 = 1;
//    LATD = led_pos[6];
//    __delay_ms(10);
//    row8 = 1;
//    LATD = led_pos[7];
//    __delay_ms(10);
    }
    return;
}
