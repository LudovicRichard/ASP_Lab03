/*
 * init.c
 *
 *  Created on: 21 mars 2012
 *      Author: Evangelina Lolivier-Exler
 *      Basic functions of initialization of the REPTAR board
 */

/**
 * FILE: init.c
 * 
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-03-07
 */
#include "bits.h"
#include "stddefs.h"
#include "gpio.h"
#include "padconf.h"
#include "lcd.h"
#include "prcm.h"

/* BEGIN: added by students */
#include "init.h"
#include "intc.h"
#include "timer.h"
#include "lcd_toolbox.h"
#include "timer_toolbox.h"
#include "students_tools.h"

#include "react_game.h"

#define INTC_ILR(m) (0x100 + (0x4 * (m)))
/* END:   added by students */

vulong PadConfVal=0;
vulong PadConfValLED=0;      // GPIO_141 & GPIO_143
vulong PadConfValSW=0;       // GPIO_140 & GPIO_142

extern unsigned long isr;    //link to isr in file int_arm.S

void GPIO_init (void)
{
    // initialization sequence: software reset
    GPIO5_REG(SYSCONFIG) |= BIT1;
    while ((GPIO5_REG(SYSSTATUS)&BIT0)==0);
    
    // completer le code...........
    /* BEGIN: added by students */
    GPIO5_REG(OMAP_GPIO_OE) &= ~(BIT13 | BIT15);
    GPIO5_REG(OMAP_GPIO_OE) |=  (BIT12 | BIT14);
    GPIO5_REG(OMAP_GPIO_DEBOUNCE_EN)  |= (BIT12 | BIT14);
    GPIO5_REG(OMAP_GPIO_DEBOUNCE_VAL) |= 1;
    /* END:   added by students */
    
    /* System Control Module: PAD Configuration */

    // completer le code...........
    
    //LED
    PadConfValLED=    
        MXMode4// mode à définir (MXMode...)
        |PULLUDENABLE_OFF
        |PULLTYPESELECT_UP
        |INPUTENABLE_OFF
        |OFFENABLE_ON
        |OFFOUTENABLE_OUT
        |OFFOUTVALUE_HI
        |OFFPULLUDENABLE_OFF
        |OFFPULLTYPESELECT_UP
        |WAKEUPENABLE_OFF;

    
    //SW
    PadConfValSW=    
        MXMode4// mode à définir (MXMode...)
        |PULLUDENABLE_ON
        |PULLTYPESELECT_DWN
        |INPUTENABLE_ON
        |OFFENABLE_ON
        |OFFOUTENABLE_IN
        |OFFOUTVALUE_HI
        |OFFPULLUDENABLE_ON
        |OFFPULLTYPESELECT_DWN
        |WAKEUPENABLE_OFF;

    /* BEGIN: added by students */
    SET_REG32(CONTROL_PADCONF_MCBSP3_DX)   = (PadConfValLED << 16) | PadConfValSW;
    SET_REG32(CONTROL_PADCONF_MCBSP3_CLKX) = (PadConfValLED << 16) | PadConfValSW;
    /* END:   added by students */
}

void lcd_init (void)
{
    /* Clock configuration */
    // select DSS1_ALWON_FCLK frequency: DPLL4 divided by 2
    DSS_CM_REG(CM_CLKSEL)&=~DDS1_FIELD_MSK;
    DSS_CM_REG(CM_CLKSEL)|=PER_M4X2;
    // enable functional clock
    DSS_CM_REG(CM_FCLKEN)|= BIT0;
    // enable interfaces clocks (L3 and L4)  (must always be enable for access to the config registers)
    DSS_CM_REG(CM_ICLKEN)|= BIT0;



    /* System Control Module: PAD Configuration */

    // OUTPUT CONFIGURATION
    PadConfVal=0;

    PadConfVal    = MXMode0 |PULLUDENABLE_OFF
                  |PULLTYPESELECT_UP
                  |INPUTENABLE_OFF
                  |OFFENABLE_ON
                  |OFFOUTENABLE_OUT
                  |OFFOUTVALUE_LOW
                  |OFFPULLUDENABLE_OFF
                  |OFFPULLTYPESELECT_UP
                  |WAKEUPENABLE_OFF;

    /* DSS_PCLK (15:0) and HSYNC (31:16) */
    SET_REG32(CONTROL_PADCONF_DSS_PCLK)=PadConfVal|(PadConfVal<<16);
    /* VSYNC (15:0) and ACBIAS (31:16) */
    SET_REG32(CONTROL_PADCONF_DSS_VSYNC)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA0 (15:0) and DSS_DATA1 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA0)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA2 (15:0) and DSS_DATA3 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA2)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA4 (15:0) and DSS_DATA5 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA4)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA6 (15:0) and DSS_DATA7 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA6)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA8 (15:0) and DSS_DATA9 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA8)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA10 (15:0) and DSS_DATA11 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA10)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA12 (15:0) and DSS_DATA13 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA12)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA14 (15:0) and DSS_DATA15 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA14)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA16 (15:0) and DSS_DATA17 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA16)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA18 (15:0) and DSS_DATA19 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA18)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA20 (15:0) and DSS_DATA21 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA20)=PadConfVal|(PadConfVal<<16);
    /* DSS_DATA22 (15:0) and DSS_DATA23 (31:16) */
    SET_REG32(CONTROL_PADCONF_DATA22)=PadConfVal|(PadConfVal<<16);

    /* Display Subsystem (DSS) Configuration */
    DSS_REG(SYSCONFIG)|=BIT1;    // software reset
    while ((DSS_REG(SYSSTATUS)&BIT0)==0); // WAIT FOR RESET DONE

    // capacitive display parameters
    LCD_REG(timing_h)=0x0090097F; /* Horizontal timing */
    LCD_REG(timing_v)=0x00B00401; /* Vertical timing */
    LCD_REG(pol_freq)=0x00003000; /* Pol Freq */

    LCD_REG(divisor)=0x00010002;  /* 33Mhz Pixel Clock */
    LCD_REG(size_lcd)=0x01df031f; /* 800x480 */
    LCD_REG(control)|= (0x01<<TFTSTN_SHIFT);    /* panel_type: TFT */
    LCD_REG(control)|= (0x03<<DATALINES_SHIFT); /* data_lines: 24 Bit RGB */
    /* GPOUT0 AND GPOUT1: bypass mode */
    LCD_REG(control)|= BIT16;    // GPOUT1
    LCD_REG(control)|= BIT15;    // GPOUT0
    LCD_REG(config)= (0x02<<FRAME_MODE_SHIFT);  /* load_mode: Frame Mode */
    LCD_REG(default_color0)=SPLASH_SOLID_COLOR; /* ORANGE */
    LCD_REG(gfx_attributes)|= (0x6<<GFX_FORMAT_SHIFT); /* GRAPHICS FORMAT: RGB16 */
    LCD_REG(gfx_preload)=0x60;                  // preload for TFT display
    LCD_REG(gfx_ba0)=FRAME_BUFFER_ADDR;         // graphics base address
    LCD_REG(gfx_size)|= (479<<GFX_SIZEY_SHIFT); /* number of lines of the graphics window */
    LCD_REG(gfx_size)|= 799;                    /* number of pixels per line of the graphics window */
    LCD_REG(gfx_attributes)|= BIT0;             // graphics layer enable
    LCD_REG(control)|= BIT5;                    // go LCD -> the HW can update the internal registers

}

//--------------------------------------------------------------------------
// interrupt_init
//
// This function initializes interrupt controller (INTC) and the GPIO�interrupts
//
void interrupt_init (void)
{
    /* Pointer to the RAM IRQ vector */
    vulong *IRQ_ram_vector_ptr1;
    /* Pointer to the ISR */
    vulong *IRQ_ram_vector_ptr2;


    // software reset
    
    /* BEGIN: added by students */
    MPU_INTC_REG(SYSCONFIG) |= BIT1;
    while ((MPU_INTC_REG(SYSSTATUS) & BIT0) == 0);
    /* END:   added by students */

    /* Interrupt Vector Initialization */
    // Set Exception vectors table at address 0x8ff64000
    asm("ldr r0, =0x8FF64000");
    asm("mcr p15, 0, r0, c12, c0, 0");

    IRQ_ram_vector_ptr1=(vulong *)0x8FF64018;   //IRQ vector address: 0x8ff64000 + 18 (Vectors table + offset)  (see page 3555 of the DM37 TRM)
    *IRQ_ram_vector_ptr1=0xE59FF018;            // write the instruction asm("ldr pc,[pc,#0x20]") at the IRQ vector address
                                                // asm("ldr pc,[pc,#0x20]") => pc=[0x8FF64038]

    IRQ_ram_vector_ptr2=(vulong *)0x8FF64038;   // IRQ vector address (see page 3557 of the DM37 TRM)
                                                // when an IRQ arrives, the PC charge the content of the address pointed by IRQ_ram_vector_ptr2
    *IRQ_ram_vector_ptr2=(unsigned long) &isr;  // jump to the ISR when an IRQ arrives
    
    /* BEGIN: added by students */
    // GPIO IRQ Configuration
    GPIO5_REG(OMAP_GPIO_IRQENABLE1)   |= BIT12;
    GPIO5_REG(OMAP_GPIO_RISINGDETECT) |= BIT12;
    GPIO5_REG(OMAP_GPIO_IRQSTATUS1)   |= BIT12;

    // IRQ Configuration
    MPU_INTC_REG(INTC_ILR(33))   &= ~BIT0;
    
    MPU_INTC_REG(INTC_MIR1)      &= ~BIT1;
    MPU_INTC_REG(INTC_CONTROL)   |=  BIT0;

    asm("mrs r1,     cpsr");
    asm("bic r1,     r1,  #0x80");
    asm("msr cpsr_c, r1");
    /* END:   added by students */
}

/* BEGIN: added by students */
//--------------------------------------------------------------------------
// timer_init
//
// This function initializes the timer
//
void timer_init (void)
{
    // initialization sequence: software reset
    GPT1_REG(TIOCP_CFG) |= BIT1;
    while ((GPT1_REG(TISTAT) & BIT0) == 0);

    // Configuration of the timer
    WKUP_CM_REG(CM_CLKSEL) &= ~BIT0;         // Source Clock is 32K_FCLK
    WKUP_CM_REG(CM_ICLKEN) |= (BIT0 | BIT2); // Enable interface Clock, 32k Sync Timer Interface Clock
    WKUP_CM_REG(CM_FCLKEN) |=  BIT0;         // Enable GPTIMER1
}

/**
 * Routine called when interruption is reported.
 */
void isr_handler ()
{
    /* DONE in step 3 + 5 */
    react_game_isr();

    GPIO5_REG(OMAP_GPIO_IRQSTATUS1) |= BIT12;
    MPU_INTC_REG(INTC_CONTROL)      |= BIT0;
}
/* END:   added by students */
