#!/usr/bin/env python
import smbus

I2C_SLAVE  = 0x0703
I2C_TENBIT = 0x0704

gyroAddress = 0x68
tenBitAddress = 0

i2c = smbus.SMBus(2)

i2c.write_i2c_block_data(gyroAddress, 0,[0])
print i2c.read_byte(gyroAddress)