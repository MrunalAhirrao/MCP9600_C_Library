/*
 * MCP9600.h
 *
 *  Created on: 14-Dec-2020
 *      Author: Mrunal Ahirao
 * Description: This file has macros and function prototypes for functionalities provided by MCP9600.
 */

#ifndef MCP9600_H_
#define MCP9600_H_

#include "MCP9600_cfg.h"

/* MCP9600 register pointer addresses */
#define TH_TEMP_REG_ADDR                    0x0
#define JD_TEMP_REG_ADDR		    0x1
#define CD_TEMP_REG_ADDR	            0x2
#define RAW_ADC_DATA_REG_ADDR               0x3
#define STAT_REG_ADDR                       0x4
#define TH_SENS_CFG_REG_ADDR                0x5
#define DEVICE_CFG_REG_ADDR                 0x6
#define ALERT1_CFG_REG_ADDR                 0x8
#define ALERT2_CFG_REG_ADDR                 0x9
#define ALERT3_CFG_REG_ADDR                 0xA
#define ALERT4_CFG_REG_ADDR                 0xB
#define ALERT1_HYS_REG_ADDR                 0xC
#define ALERT2_HYS_REG_ADDR                 0xD
#define ALERT3_HYS_REG_ADDR                 0xE
#define ALERT4_HYS_REG_ADDR                 0xF
#define TEMP_ALERT1_LIMIT_REG_ADDR          0x10
#define TEMP_ALERT2_LIMIT_REG_ADDR          0x11
#define TEMP_ALERT3_LIMIT_REG_ADDR          0x12
#define TEMP_ALERT4_LIMIT_REG_ADDR          0x13
#define DEVICE_ID_REG_ADDR                  0x20
/* MCP9600 register pointer addresses */


/* MCP9600 public function prototypes */
float MCP_Read_ThermoCoup_Temp(void);
float MCP_Read_ThermoCoupJunc_Temp(void);
float MCP_Read_ColdJunc_Temp(void);
int32_t MCP_Read_ADC(void);
uint8_t MCP_Read_Status_Reg(void);
uint8_t MCP_Read_Sens_Cfg(void);
t_MCP_Status MCP_Set_Sens_Cfg(uint8_t SensorCfg);
uint8_t MCP_Read_DevCfg_Reg(void);
t_MCP_Status MCP_Set_DevCfg_Reg(uint8_t DevCfg);
float MCP_Read_AlertLimit_Reg(uint8_t AlertRegAddr);
t_MCP_Status MCP_Set_AlertLimit_Reg(uint8_t AlertRegAddr,uint16_t val);
uint8_t MCP_Read_AlertHys_Reg(uint8_t AlertHysRegAddr);
t_MCP_Status MCP_Set_AlertHys_Reg(uint16_t AlertHysAddr,uint8_t alertHysVal);
uint8_t MCP_Read_AlertCfg_Reg(uint8_t AlertCfgAddr);
t_MCP_Status MCP_Set_AlertCfg_Reg(uint8_t AlertCfgAddr,uint8_t AlertCfgVal);
uint16_t MCP_Read_DevID_Reg(void);
/* MCP9600 public function prototypes */

#endif /* MCP9600_H_ */
