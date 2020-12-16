/*
 * MCP9600_cfg.h
 *
 *  Created on: 14-Dec-2020
 *      Author: Mrunal Ahirao
 * Description: This file has inclusions of driver related files and macros for driver related config
 */

#ifndef MCP9600_CFG_H_
#define MCP9600_CFG_H_

#include "lpi2c_driver.h" /* I2C driver for NXP S32K142*/
#include "lpi2c1.h"
#include <stdint.h>



typedef enum{
  SUCCESS,
  FAILURE
}t_MCP_Status;


#define I2C_TMOUT			    200

/* wrapper functions will help in making library platform independent */
/* Driver wrapper functions */

/**
 Description: This function writes data on I2C bus.
 Parameters(in): uint8_t *ptrToData: This is pointer to databuff which is to be written on I2C bus.
 Parameters(out): None
 Return Value: t_MCP_Status: SUCCESS or FAILURE
 */
t_MCP_Status I2C_Write(uint8_t *ptrToData);

/**
 Description: This function writes data on I2C bus.
 Parameters(in): uint8_t *ptrToData: This is pointer to databuff which is to be written on I2C bus.
		 uint32_t size: This is number of bytes to be read from I2C bus.
 Parameters(out): None
 Return Value: t_MCP_Status: SUCCESS or FAILURE
 */
t_MCP_Status I2C_Read(uint8_t *ptrToRxBuf,uint32_t size);

#endif /* MCP9600_CFG_H_ */
