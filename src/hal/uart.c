/* uart.c
 * 
 * Copyright (c) 2011 The ottos project.
 *
 * This work is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 * 
 * This work is distributed in the hope that it will be useful, but without
 * any warranty; without even the implied warranty of merchantability or
 * fitness for a particular purpose. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *
 *  Created on: Nov 18, 2011
 *      Author: Matthias Schmid <ramsondon@gmail.com>
 */

/*
 BAUD RATE: 115200
 DATA: 8 bit
 PARITY: none
 STOP: 1bit
 FLOW CONTROL: none (Critical)
 */

#include <arch/arm/omap353x_uart.h>
#include <arch/arm/omap353x_intc.h>
#include <ottos/types.h>
#include <bits.h>

#include "uart.h"
#include "../kernel/intc/irq.h"

/* UART software reset */
#define UART_SOFTRESET(uart_mem_addr_ptr) (*(uart_mem_addr_ptr + \
  UART_SYSC_REG/sizeof(mem_address_t)) |= (1<<1))

/* UART reset done */
#define UART_RESETDONE(uart_mem_addr_ptr) (int)(*(uart_mem_addr_ptr + \
  UART_SYSS_REG/sizeof(mem_address_t)) & (1<<0))

#define UART_BAUDRATE_MASK_LSB 0x00FF

/*
 * Private Functions
 */
static void uart_software_reset(mem_address_t* uart_base_addr);
static void uart_disable(mem_address_t* uart_base_addr);
static void uart_switch_lcr_mode(mem_address_t* uart_base_addr,
                                 unsigned int lcr_mode);
static void uart_set_protocol_data_len(mem_address_t* uart_base_addr,
                                       unsigned short len);
static void uart_set_protocol_stop_bit(mem_address_t* uart_base_addr,
                                       unsigned short nb_stop);
static void uart_set_protocol_parity(mem_address_t* uart_base_addr,
                                     unsigned int parity);


/*
 * Software Reset and disabling UART unit, to access DLL, DHL register.
 */
void uart_reset(mem_address_t* uart_base_addr) {

  /* reset UART */
  uart_software_reset(uart_base_addr);

  /* disable UART to enable access DLL, DLH registers (for setting baudrate) */
  uart_disable(uart_base_addr);
}

/*
 * Initiates a software reset of UART uart_base_addr
 */
static void uart_software_reset(mem_address_t* uart_base_addr) {

  int busy_wait = 0;
  /*
   * To clear the UART registers we have to set the SOFTRESET bit of SYSC_REG
   * to 1.
   */UART_SOFTRESET(uart_base_addr);

  /*
   * If the SOFTRESET bit is 1 then we have to busy wait until the RESETDONE bit
   * in SYSS_REG equals 1.
   */
  while (busy_wait != 1) {
    busy_wait = UART_RESETDONE(uart_base_addr);
  }
}

/*
 * Disables the UART instance
 */
static void uart_disable(mem_address_t* uart_base_addr) {
  *(uart_base_addr + UART_MDR1_REG / sizeof(mem_address_t))
      = UART_MDR1_MODE_SELECT_DISABLE;
}

static void uart_switch_lcr_mode(mem_address_t* uart_base_addr,
                                 unsigned int lcr_mode) {
  *(uart_base_addr + UART_LCR_REG / sizeof(mem_address_t)) = lcr_mode;
}

void uart_switch_to_config_mode_a(mem_address_t* uart_base_addr) {
  uart_switch_lcr_mode(uart_base_addr, UART_LCR_MODE_CONFIG_A);
}

void uart_switch_to_config_mode_b(mem_address_t* uart_base_addr) {
  uart_switch_lcr_mode(uart_base_addr, UART_LCR_MODE_CONFIG_B);
}

void uart_switch_to_register_operational_mode(mem_address_t* uart_base_addr) {
  uart_switch_lcr_mode(uart_base_addr, UART_LCR_MODE_REG_OP);
}

/* Table for Baudrate settings in OMAP353x Ref manual (p.2716) */
void uart_set_baudrate(mem_address_t* uart_base_addr, int baudrate) {

  /* set least significant bits */
  *(uart_base_addr + UART_DLL_REG / sizeof(mem_address_t)) = (baudrate
      & UART_BAUDRATE_MASK_LSB);

  /* set most significatn bits*/
  *(uart_base_addr + UART_DLH_REG / sizeof(mem_address_t)) = (baudrate >> 8);
}

void uart_set_mode(mem_address_t* uart_base_addr, int uart_mode) {
  *(uart_base_addr + UART_MDR1_REG / sizeof(mem_address_t)) = uart_mode;
}

static void uart_set_protocol_data_len(mem_address_t* uart_base_addr,
                                       unsigned short len) {

  switch (len) {
    case UART_PROTOCOL_DATA_LENGTH_5:
      CLEAR_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_CHAR_LEN_0)
      ;
      CLEAR_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_CHAR_LEN_1)
      ;
      break;
    case UART_PROTOCOL_DATA_LENGTH_6:
      SET_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_CHAR_LEN_0)
      ;
      CLEAR_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_CHAR_LEN_1)
      ;
      break;
    case UART_PROTOCOL_DATA_LENGTH_7:
      CLEAR_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_CHAR_LEN_0)
      ;
      SET_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_CHAR_LEN_1)
      ;
      break;
    case UART_PROTOCOL_DATA_LENGTH_8:
    default:
      SET_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_CHAR_LEN_0)
      ;
      SET_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_CHAR_LEN_1)
      ;
      break;
  }
}

static void uart_set_protocol_stop_bit(mem_address_t* uart_base_addr,
                                       unsigned short nb_stop) {
  switch (nb_stop) {
    case UART_PROTOCOL_NB_STOP_1:
      CLEAR_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_NB_STOP)
      ;
      break;
    case UART_PROTOCOL_NB_STOP_2:
    default:
      SET_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_NB_STOP)
      ;
      break;
  }
}

static void uart_set_protocol_parity(mem_address_t* uart_base_addr,
                                     unsigned int parity) {
  // TODO(ramsondon@gmail.com) Implement more parity types
  // check partiy_type_1 and parity_type_2 arguments

  switch (parity) {
    case UART_PROTOCOL_PARITY_NONE:
    default:
      CLEAR_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_PARITY_EN)
      ;
      break;
  }
}

void uart_set_protocol_format(mem_address_t* uart_base_addr,
                              uart_protocol_format_t protocol) {

  /* clear LCR DIV and BREAK field */
  CLEAR_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_DIV_EN);
  CLEAR_BIT((uart_base_addr + UART_LCR_REG/sizeof(mem_address_t)), UART_LCR_BREAK_EN);

  /* set baudrate */
  //  uart_set_baudrate(uart_base_addr, protocol.baudrate);
  /* set the character length for this protocol */
  uart_set_protocol_data_len(uart_base_addr, protocol.datalen);
  /* configure stop bits */
  uart_set_protocol_stop_bit(uart_base_addr, protocol.stopbit);
  /* configure parity options */
  uart_set_protocol_parity(uart_base_addr, protocol.parity);
}

void uart_set_flow_control(mem_address_t* uart_base_addr, uint8_t flow_control) {
  *(uart_base_addr + UART_EFR_REG / sizeof(mem_address_t)) = flow_control;
}

void uart_enable_enhanced_func(mem_address_t* uart_base_addr) {
  SET_BIT((uart_base_addr + UART_EFR_REG/sizeof(mem_address_t)),
      UART_EFR_ENHANCED_EN);
}

void uart_enable_tcr(mem_address_t* uart_base_addr) {
  SET_BIT((uart_base_addr + UART_MCR_REG/sizeof(mem_address_t)),
      UART_MCR_TCR_TLR);
}

/*
 * Returns 1 if the UART FIFO is full, else 0.
 */
int uart_fifo_is_full(mem_address_t* uart_base_addr) {
  return (int) (*(uart_base_addr + UART_SSR_REG / sizeof(mem_address_t)) & (1
      << UART_SSR_TX_FIFO_FULL));
}

/*
 *
 *
 * DMA is disabled
 */
void uart_init_fifo(mem_address_t* uart_base_addr) {

  // TODO:(ramsondon@gmail.com) save LCR state
  uart_switch_to_config_mode_b(uart_base_addr);

  // TODO:(ramsondon@gmail.com) save EFR ENHANCED
  uart_enable_enhanced_func(uart_base_addr);

  uart_switch_to_config_mode_a(uart_base_addr);

  // TODO:(ramsondon@gmail.com save MCR TCR_TLR
  uart_enable_tcr(uart_base_addr);

  // transmission+receive = 8chars
  CLEAR_BIT((uart_base_addr + UART_FCR_REG/sizeof(mem_address_t)), UART_FCR_RX_FIFO_TRIG_1);
  CLEAR_BIT((uart_base_addr + UART_FCR_REG/sizeof(mem_address_t)), UART_FCR_RX_FIFO_TRIG_2);
  CLEAR_BIT((uart_base_addr + UART_FCR_REG/sizeof(mem_address_t)), UART_FCR_TX_FIFO_TRIG_1);
  CLEAR_BIT((uart_base_addr + UART_FCR_REG/sizeof(mem_address_t)), UART_FCR_TX_FIFO_TRIG_2);

  // enable fifo 60 bytes
  // FIXME: seems not working although DLH and DLL are 0x0 both (clock is not runnig)
  SET_BIT((uart_base_addr + UART_FCR_REG/sizeof(mem_address_t)),UART_FCR_FIFO_EN);

  // XXX: do nothing wit DMA mode? (omap353x ref man p.2733)

  uart_switch_to_config_mode_b(uart_base_addr);

  // TODO:(ramsondon@gmail.com) set FIFO TRIGGER DMA to RX/TX 4 spaces
  *(uart_base_addr + UART_TLR_REG / sizeof(mem_address_t)) = 0x0000044;

  SET_BIT((uart_base_addr + UART_SCR_REG/sizeof(mem_address_t)), UART_SCR_RX_TRIG_GRANU1);
  SET_BIT((uart_base_addr + UART_SCR_REG/sizeof(mem_address_t)), UART_SCR_TX_TRIG_GRANU1);
  CLEAR_BIT((uart_base_addr + UART_SCR_REG/sizeof(mem_address_t)), UART_SCR_DMA_MODE_CTL);

  // TODO: disable DMA mode

  // TODO:(ramsondon@gmail.com) restore EFR enhanced flag

  // TODO: uart_switch_to_config_mode_a(uart_base_addr);
  // TODO: restore MCR TCR_TLR register flag
  // TODO: restore LCR value

}

/*
 * clear interrupts and set sleep mode
 */
void uart_clear_interrupts(mem_address_t* uart_base_addr) {

  /* clear IER and goto SLEEP MODE */
  *(uart_base_addr + UART_IER_REG / sizeof(mem_address_t)) = 0x0;
}

void uart_enable_loopback(mem_address_t* uart_base_addr) {
  *(uart_base_addr + UART_MCR_REG / sizeof(mem_address_t))
      |= UART_MCR_LOOPBACK_EN;
}

/*
 * The Mode Registers must be configured after the configuration of the
 * DLL_REG, DLH_REG, LCR_REG registers
 */
void uart_init(mem_address_t* uart_base_addr, int uart_mode,
               struct uart_protocol_format_t protocol, uint8_t flowcontrol) {

  uart_reset(uart_base_addr);

  /* switch to config mode b to write to EFR and LCR */
  uart_switch_to_config_mode_b(uart_base_addr);

  /* change the baudrate and clocksettings */
  uart_set_baudrate(uart_base_addr, protocol.baudrate);

  /* set flow control flags */
  uart_set_flow_control(uart_base_addr, flowcontrol);

  /* set protocol format */
  uart_set_protocol_format(uart_base_addr, protocol);

  /* load the new UART mode */
  uart_set_mode(uart_base_addr, uart_mode);
}

/*
 * Returns 1 if uart read fifo queue is empty.
 * If the Queue has at least one character the result will be 1.
 */
int uart_is_empty_read_queue(mem_address_t* uart_base_addr) {
  int status = (int) READ_BIT((uart_base_addr +
          UART_LSR_REG/sizeof(mem_address_t)), UART_LSR_RX_FIFO_E);
  return (status == 0);
}

/*
 * Returns 1 if uart transmission fifo queue is empty.
 * If the Queue has at least one character the result will be 1.
 */
int uart_is_empty_write_queue(mem_address_t* uart_base_addr) {
  int status = (int) READ_BIT((uart_base_addr +
          UART_LSR_REG/sizeof(mem_address_t)), UART_LSR_TX_FIFO_E);
  return (status == 0);
}

/* writes one character to the UART device */
void uart_write(mem_address_t* uart_base_addr, char* buffer) {
  *(uart_base_addr + UART_THR_REG/sizeof(mem_address_t)) = *buffer;
}

/* reads one character from the UART device */
void uart_read(mem_address_t* uart_base_addr, char* buffer) {
  *buffer = *(uart_base_addr + UART_RHR_REG/sizeof(mem_address_t));
}