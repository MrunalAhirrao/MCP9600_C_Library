/*
 * MCP9600_cfg.c
 *
 *  Created on: 14-Dec-2020
 *      Author: Mrunal Ahirao
 * Description: This file has mapping between MCP I2C functions and driver functions. This will help in making
 * 		this library platform independent.
 */

#include "MCP9600_cfg.h"

/**
 Description: This function writes data on I2C bus.
 Parameters(in): uint8_t *ptrToData: This is pointer to databuff which is to be written on I2C bus.
 Parameters(out): None
 Return Value: t_MCP_Status: SUCCESS or FAILURE
 */
t_MCP_Status I2C_Write(uint8_t *ptrToData)
{
  t_MCP_Status status = SUCCESS;
  if(STATUS_SUCCESS != LPI2C_DRV_MasterSendDataBlocking(INST_LPI2C1, ptrToData,8, true, I2C_TMOUT))
  {
      status = FAILURE;
  }
  return status;
}

/**
 Description: This function writes data on I2C bus.
 Parameters(in): uint8_t *ptrToData: This is pointer to databuff which is to be written on I2C bus.
		 uint32_t size: This is number of bytes to be read from I2C bus.
 Parameters(out): None
 Return Value: t_MCP_Status: SUCCESS or FAILURE
 */
t_MCP_Status I2C_Read(uint8_t *ptrToRxBuf,uint32_t size)
{
  t_MCP_Status status  = SUCCESS;
  if(STATUS_SUCCESS!= LPI2C_DRV_MasterReceiveDataBlocking(INST_LPI2C1,ptrToRxBuf,size,true,I2C_TMOUT))
  {
    status = FAILURE;
  }
  return status;
}
