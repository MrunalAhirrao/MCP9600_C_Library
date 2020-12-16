/*
 * MCP9600.c
 *
 *  Created on: 14-Dec-2020
 *      Author: Mrunal Ahirao
 * Description: This file has function definition for functionalities provided by MCP9600.
 */

#include "MCP9600.h"

static t_MCP_Status setRegPtrRd(uint8_t RegPtrAddr);
static t_MCP_Status setRegPtrWr(uint8_t *ptrToRegData);


/* MCP9600 public functions */

/**
 Description: This function reads the thermocouple temperature in degree celsius.
 Parameters(in): None
 Parameters(out): None
 Return Value: temperature in degree celsius.
 */
float MCP_Read_ThermoCoup_Temp(void)
{
  float temp = 0;
  uint8_t buff[2];
  if(SUCCESS == setRegPtrRd((uint8_t)TH_TEMP_REG_ADDR))
  {
      if(SUCCESS == I2C_Read(buff, 2))
      {
	  /*Convert Temperature data*/
	  if((buff[0] & 0x80) == 0x80) //if temperature is less than 0
	  {
	      temp = ((buff[0]*16)+(buff[1]/16));
	      temp = temp - 4096;
	  }else{
	      temp = ((buff[0]*16)+(buff[1]/16)); //if temperature is greater than 0
	  }
      }
  }
  return temp;
}

/**
 Description: This function reads the thermocouple junction temperature in degree celsius.
 Parameters(in): None
 Parameters(out): None
 Return Value: temperature in degree celsius.
 */
float MCP_Read_ThermoCoupJunc_Temp(void)
{
  float temp = 0;
  uint8_t buff[2];
  if(SUCCESS == setRegPtrRd((uint8_t)JD_TEMP_REG_ADDR))
  {
      if(SUCCESS == I2C_Read(buff, 2))
      {
	  /*Convert Temperature data*/
	  if((buff[0] & 0x80) == 0x80) //if temperature is less than 0
	  {
	      temp = ((buff[0]*16)+(buff[1]/16));
	      temp = temp - 4096;
	  }else{
	      temp = ((buff[0]*16)+(buff[1]/16)); //if temperature is greater than 0
	  }
      }
  }
  return temp;
}

/**
 Description: This function reads the cold junction temperature in degree celsius.
 Parameters(in): None
 Parameters(out): None
 Return Value: temperature in degree celsius.
 */
float MCP_Read_ColdJunc_Temp(void)
{
  float temp = 0;
  uint8_t buff[2];
  if(SUCCESS == setRegPtrRd((uint8_t)CD_TEMP_REG_ADDR))
  {
      if(SUCCESS == I2C_Read(buff, 2))
      {
	  /*Convert Temperature data*/
	  if((buff[0] & 0x80) == 0x80) //if temperature is less than 0
	  {
	      temp = ((buff[0]*16)+(buff[1]/16));
	      temp = temp - 4096;
	  }else{
	      temp = ((buff[0]*16)+(buff[1]/16)); //if temperature is greater than 0
	  }
      }
  }
  return temp;
}

/**
 Description: This function reads raw ADC value
 Parameters(in): None
 Parameters(out): None
 Return Value: ADC value.
 */
int32_t MCP_Read_ADC(void)
{
  int32_t adcVal = 0;
  uint8_t buff[3];
  if(SUCCESS == setRegPtrRd((uint8_t)RAW_ADC_DATA_REG_ADDR))
  {
      if(SUCCESS == I2C_Read(buff, 3))
      {
	  adcVal = (buff[0]<<24|buff[1]<<16|buff[2]<<8);
	  if(buff[0] & 0x800000) // if ADC reading is less than 0 mVs
	  {
	      adcVal = adcVal|0xFF000000;
	  }
      }
  }
  return adcVal;
}

/**
 Description: This function reads status register
 Parameters(in): None
 Parameters(out): None
 Return Value: status register value.
 */
uint8_t MCP_Read_Status_Reg(void)
{
  uint8_t statusReg = 0;
  if(SUCCESS == setRegPtrRd((uint8_t)STAT_REG_ADDR))
  {
      I2C_Read(&statusReg, 1);
  }
  return statusReg;
}

/**
 Description: This function reads the sensor configuration register
 Parameters(in): None
 Parameters(out): None
 Return Value: sensor configuration register value.
 */
uint8_t MCP_Read_Sens_Cfg(void)
{
  uint8_t sensCfgReg = 0;
  if(SUCCESS == setRegPtrRd((uint8_t)TH_SENS_CFG_REG_ADDR))
  {
      I2C_Read(&sensCfgReg, 1);
  }
  return sensCfgReg;
}

/**
 Description: This function sets the sensor configuration register
 Parameters(in): uint8_t SensorCfg: The sensor configuration to be written.
 Parameters(out): None
 Return Value: t_MCP_Status: SUCCESS or FAILURE
 */
t_MCP_Status MCP_Set_Sens_Cfg(uint8_t SensorCfg)
{
  t_MCP_Status status = SUCCESS;
  uint8_t buff[2],ReadbackVal;

  /* prepare buffer with register pointer address and register data */
  buff[0] = (uint8_t)TH_SENS_CFG_REG_ADDR;
  buff[1] = SensorCfg;

  if(SUCCESS == setRegPtrWr(buff))
  {
      if(SUCCESS!= I2C_Read(&ReadbackVal, 1))
      {
	status = FAILURE;
      }else if(SensorCfg != ReadbackVal) status = FAILURE;

  }else status = FAILURE;

  return status;
}

/**
 Description: This function reads the device configuration register
 Parameters(in): None
 Parameters(out): None
 Return Value: device configuration register value.
 */
uint8_t MCP_Read_DevCfg_Reg(void)
{
  uint8_t devCfgReg = 0;
  if(SUCCESS == setRegPtrRd((uint8_t)DEVICE_CFG_REG_ADDR))
  {
      I2C_Read(&devCfgReg, 1);
  }
  return devCfgReg;
}

/**
 Description: This function sets the device configuration register
 Parameters(in): uint8_t DevCfg: The device configuration to be written.
 Parameters(out): None
 Return Value: t_MCP_Status: SUCCESS or FAILURE
 */
t_MCP_Status MCP_Set_DevCfg_Reg(uint8_t DevCfg)
{
  t_MCP_Status status = SUCCESS;
  uint8_t buff[2],ReadbackVal;

  /* prepare buffer with register pointer address and register data */
  buff[0] = (uint8_t)DEVICE_CFG_REG_ADDR;
  buff[1] = DevCfg;

  if(SUCCESS == setRegPtrWr(buff))
  {
      if(SUCCESS!= I2C_Read(&ReadbackVal, 1))
      {
	status = FAILURE;
      }else if(DevCfg != ReadbackVal) status = FAILURE;

  }else status = FAILURE;

  return status;
}

/**
 Description: This function reads the alert limit temperature register
 Parameters(in): Alert Limit Temperature register number to be read
 Parameters(out): None
 Return Value: temperature in degree celsius.
 */
float MCP_Read_AlertLimit_Reg(uint8_t AlertRegAddr)
{
  float temp = 0;
  uint8_t buff[2];
  if(SUCCESS == setRegPtrRd(AlertRegAddr))
  {
      if(SUCCESS == I2C_Read(buff, 2))
      {
	  /*Convert Temperature data*/
	  if((buff[0] & 0x80) == 0x80) //if temperature is less than 0
	  {
	      temp = ((buff[0]*16)+(buff[1]/16));
	      temp = temp - 4096;
	  }else{
	      temp = ((buff[0]*16)+(buff[1]/16)); //if temperature is greater than 0
	  }
      }
  }
  return temp;
}

/**
 Description: This function sets the alert limit temperature register
 Parameters(in): uint8_t AlertRegAddr: The alert limit register address
		 uint16_t val: The value to be written in alert limit register
 Parameters(out): None
 Return Value: t_MCP_Status: SUCCESS or FAILURE
 */
t_MCP_Status MCP_Set_AlertLimit_Reg(uint8_t AlertRegAddr,uint16_t val)
{
  t_MCP_Status status = SUCCESS;
  uint8_t buff[2],buff2[2];

  /* Check if given address is within limits */
  if((AlertRegAddr == TEMP_ALERT1_LIMIT_REG_ADDR)||(AlertRegAddr == TEMP_ALERT2_LIMIT_REG_ADDR)||(AlertRegAddr == TEMP_ALERT3_LIMIT_REG_ADDR)||(AlertRegAddr == TEMP_ALERT4_LIMIT_REG_ADDR))
  {
    buff[0] = AlertRegAddr;
    buff[1] = val;

    /* Check if register value was written correctly */
    if(SUCCESS == setRegPtrWr(buff))
    {
	I2C_Read(buff2, 2);

	if((buff[1] != buff2[0]) || (buff[2] != buff2[1]))
	{
	  status = FAILURE;
	}
    }else status = FAILURE;

  }else status = FAILURE;

  return status;
}

/**
 Description: This function reads the Hysteresis Alert register
 Parameters(in): uint8_t AlertHysRegAddr: The address of Hysteresis Alert register
 Parameters(out): None
 Return Value: Hysteresis Alert register value.
 */
uint8_t MCP_Read_AlertHys_Reg(uint8_t AlertHysRegAddr)
{
  uint8_t alertHysReg = 0;

  /* Check if given address is within limits */
  if((AlertHysRegAddr == ALERT1_HYS_REG_ADDR)||(AlertHysRegAddr == ALERT2_HYS_REG_ADDR)||(AlertHysRegAddr == ALERT3_HYS_REG_ADDR)||(AlertHysRegAddr == ALERT4_HYS_REG_ADDR))
  {
    if(SUCCESS == setRegPtrRd((uint8_t)AlertHysRegAddr))
    {
	I2C_Read(&alertHysReg, 1);
    }
  }
  return alertHysReg;
}

/**
 Description: This function set the Hysteresis Alert register
 Parameters(in): uint16_t AlertHysAddr: This is the Alert Hysteris register address
	         uint8_t alertHysVal: This the value to be written to Alert Hystersis Register.
 Parameters(out): None
 Return Value: t_MCP_Status: SUCCESS or FAILURE
 */
t_MCP_Status MCP_Set_AlertHys_Reg(uint16_t AlertHysAddr,uint8_t alertHysVal)
{
  t_MCP_Status status = SUCCESS;
  uint8_t buff[2],ReadbackVal;

  /* Check if given address is within limits */
  if((AlertHysAddr == ALERT1_HYS_REG_ADDR)||(AlertHysAddr == ALERT2_HYS_REG_ADDR)||(AlertHysAddr == ALERT3_HYS_REG_ADDR)||(AlertHysAddr == ALERT4_HYS_REG_ADDR))
  {
      buff[0] = AlertHysAddr;
      buff[1] = alertHysVal;

      if(SUCCESS == setRegPtrWr(buff))
      {
	  if(SUCCESS != I2C_Read(&ReadbackVal, 1))
	  {
	      status = FAILURE;
	  }
	  else if(buff[1]!=ReadbackVal)
	  {
	    status = FAILURE;
	  }

      }else status = FAILURE;

  }else status = FAILURE;

  return status;
}

/**
 Description: This function reads the Alert config register
 Parameters(in): uint16_t AlertCfgAddr: The address of alert config register
 Parameters(out): None
 Return Value: Alert config register value
 */
uint8_t MCP_Read_AlertCfg_Reg(uint8_t AlertCfgAddr)
{
  uint8_t alertcfgReg = 0;
  /* Check if given address is within limits */
  if((AlertCfgAddr == ALERT1_CFG_REG_ADDR)||(AlertCfgAddr == ALERT2_CFG_REG_ADDR)||(AlertCfgAddr == ALERT3_CFG_REG_ADDR)||(AlertCfgAddr == ALERT4_CFG_REG_ADDR))
  {
    if(SUCCESS == setRegPtrRd((uint8_t)AlertCfgAddr))
    {
      I2C_Read(&alertcfgReg, 1);
    }
  }
  return alertcfgReg;
}

/**
 Description: This function set the Alert Config register
 Parameters(in): uint16_t AlertCfgAddr: This is the Alert config register address
	         uint8_t AlertCfgVal: This is the value to be written to Alert Config Register.
 Parameters(out): None
 Return Value: t_MCP_Status: SUCCESS or FAILURE
 */
t_MCP_Status MCP_Set_AlertCfg_Reg(uint8_t AlertCfgAddr,uint8_t AlertCfgVal)
{
  t_MCP_Status status = SUCCESS;
  uint8_t buff[2],ReadbackVal;

  /* Check if given address is within limits */
  if((AlertCfgAddr == ALERT1_CFG_REG_ADDR)||(AlertCfgAddr == ALERT2_CFG_REG_ADDR)||(AlertCfgAddr == ALERT3_CFG_REG_ADDR)||(AlertCfgAddr == ALERT4_CFG_REG_ADDR))
  {
     buff[0] = AlertCfgAddr;
     buff[1] = AlertCfgVal;

     if(SUCCESS!=setRegPtrWr(buff))
     {
	 if(SUCCESS != I2C_Read(&ReadbackVal, 1))
	 {
	  status = FAILURE;

	 }else if(buff[1]!=ReadbackVal) status = FAILURE;

     }else status = FAILURE;

  }else status = FAILURE;

  return status;
}

/**
 Description: This function reads the Device ID register
 Parameters(in): None
 Parameters(out): None
 Return Value: Device ID register value
 */
uint16_t MCP_Read_DevID_Reg(void)
{
  uint16_t devIDReg = 0;

  if(SUCCESS == setRegPtrRd((uint8_t)DEVICE_ID_REG_ADDR))
  {
    I2C_Read((uint8_t*)&devIDReg, 2);
  }

  return devIDReg;
}

/* MCP9600 public functions */

/*-------------------------------------------------------------------------------------------------------------------------------------*/

/* MCP9600 private functions */

/**
 Description: This function sets Register pointer with given address
 Parameters(in): uint8_t RegPtrAddr: Address of register
 Parameters(out): None
 Return Value: t_MCP_Status: SUCCESS or FAILURE.
 */
static t_MCP_Status setRegPtrRd(uint8_t RegPtrAddr)
{
  return I2C_Write(&RegPtrAddr);
}

/**
 Description: This function sets Register pointer with given address and Register with data of register.
 Parameters(in): uint8_t *ptrToRegData: This is pointer to buffer with following data pattern:
		 index0 = Register address
		 index1..n = Data to be stored to register.
 Parameters(out): None
 Return Value: t_MCP_Status: SUCCESS or FAILURE.
 */
static t_MCP_Status setRegPtrWr(uint8_t *ptrToRegData)
{
  return I2C_Write(ptrToRegData);
}
