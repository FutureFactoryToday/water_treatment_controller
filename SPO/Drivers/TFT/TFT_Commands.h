/**
  ******************************************************************************
  * @file    TFT_Commands.h
  * @brief   This file contains all commands for ILI9486
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TFT_Commands_H_
#define _TFT_Commands_H_

/*Includes */
#include "main.h"

#define ILI_NOP 0x00
#define ILI_SOFT_RESET 0x01
#define ILI_READ_ID 0x04
#define ILI_READ_ERR_NUM 0x05
#define ILI_READ_STATUS 0x09
#define ILI_READ_POWER_MODE 0x0A
#define ILI_READ_MADCTL 0x0B
#define ILI_READ_PIXEL_FORMAT 0x0C
#define ILI_READ_IMAGE_MODE 0x0D
#define ILI_READ_SIGNAL_MODE 0x0E
#define ILI_READ_SELF_DIAG 0x0F
#define ILI_SLEEP_IN 0x10
#define ILI_SLEEP_OUT 0x11
#define ILI_PARTIAL_ON 0x12
#define ILI_NORMAL_MODE 0x13
#define ILI_INV_OFF 0x20
#define ILI_INV_ON 0x21
#define ILI_DISPLAY_OFF 0x28
#define ILI_DISPLAY_ON 0x29
#define ILI_SET_COL_ADR 0x2A
#define ILI_SET_PAGE_ADR 0x2B
#define ILI_MEM_WR 0x2C
#define ILI_MEM_RD 0x2E
#define ILI_PART_AREA 0x30
#define ILI_VERT_SCROL_DEF 0x33
#define ILI_TEAR_OFF 0x34
#define ILI_TEAR_ON 0x35
#define ILI_MEM_ACCESS_CONTR 0x36
#define ILI_VERT_SCROL_START_ADR 0x37
#define ILI_IDLE_OFF 0x38
#define ILI_IDLE_ON 0x39
#define ILI_INTERFACE_PIXEL_FORMAT 0x3A
#define ILI_MEM_WR_CONT 0x3C
#define ILI_MEM_RD_CONT 0x3E
#define ILI_WR_TEAR_SCAN_LINE 0x44
#define ILI_RD_TEAR_SCAN_LINE 0x45
#define ILI_WR_BRIGH_VAL 0x51
#define ILI_RD_BRIGH_VAL 0x52
#define ILI_WR_CTRL_VAL 0x53
#define ILI_RD_CTRL_VAL 0x54
#define ILI_WR_CABC_VAL 0x55
#define ILI_RD_CABC_VAL 0x56
#define ILI_WR_CABC_MIN 0x5E
#define ILI_RD_CABC_MIN 0x5F
#define ILI_RD_FIRST_CHECKSUM 0xAA
#define ILI_RD_CONT_CHECKSUM 0xAF
#define ILI_RD_ID1 0xDA
#define ILI_RD_ID2 0xDB
#define ILI_RD_ID3 0xDC



#endif /* __TFT_Commands_H__ */

