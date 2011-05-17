/***************************************************************************
 *   Copyright (C) 2009 - 2010 by Simon Qian <SimonQian@SimonQian.com>     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>

#include "../versaloon_include.h"
#include "../versaloon.h"
#include "../versaloon_internal.h"
#include "usbtoxxx.h"
#include "usbtoxxx_internal.h"

RESULT usbtoi2c_init(uint8_t interface_index)
{
	return usbtoxxx_init_command(USB_TO_I2C, interface_index);
}

RESULT usbtoi2c_fini(uint8_t interface_index)
{
	return usbtoxxx_fini_command(USB_TO_I2C, interface_index);
}

RESULT usbtoi2c_config(uint8_t interface_index, uint16_t kHz, 
						uint16_t byte_interval, uint16_t max_dly)
{
	uint8_t buff[6];
	
#if PARAM_CHECK
	if (interface_index > 7)
	{
		LOG_BUG(ERRMSG_INVALID_INTERFACE_NUM, interface_index);
		return ERROR_FAIL;
	}
#endif
	
	SET_LE_U16(&buff[0], kHz);
	SET_LE_U16(&buff[2], byte_interval);
	SET_LE_U16(&buff[4], max_dly);
	
	return usbtoxxx_conf_command(USB_TO_I2C, interface_index, 
								 buff, sizeof(buff));
}

RESULT usbtoi2c_read(uint8_t interface_index, uint16_t chip_addr, 
						uint8_t *data, uint16_t data_len, uint8_t stop, 
						bool nacklast)
{
#if PARAM_CHECK
	if (interface_index > 7)
	{
		LOG_BUG(ERRMSG_INVALID_INTERFACE_NUM, interface_index);
		return ERROR_FAIL;
	}
#endif
	
	if (data_len > (versaloon_buf_size - 6 - 4))
	{
		LOG_BUG(ERRMSG_INVALID_VALUE, data_len, "I2C data size too large");
		return ERROR_FAIL;
	}
	
	versaloon_cmd_buf[0] = (chip_addr >> 0) & 0xFF;
	SET_LE_U16(&versaloon_cmd_buf[1], data_len);
	versaloon_cmd_buf[3] = stop;
	versaloon_cmd_buf[4] = nacklast ? 1 : 0;
	memset(&versaloon_cmd_buf[5], 0, data_len);
	
	return usbtoxxx_in_command(USB_TO_I2C, interface_index, versaloon_cmd_buf, 
							   data_len + 5, data_len, data, 0, data_len, 0);
}

RESULT usbtoi2c_write(uint8_t interface_index, uint16_t chip_addr, 
						uint8_t *data, uint16_t data_len, uint8_t stop)
{
#if PARAM_CHECK
	if (interface_index > 7)
	{
		LOG_BUG(ERRMSG_INVALID_INTERFACE_NUM, interface_index);
		return ERROR_FAIL;
	}
#endif
	
	if (data_len > (versaloon_buf_size - 6 - 4))
	{
		LOG_BUG(ERRMSG_INVALID_VALUE, data_len, "I2C data size too large");
		return ERROR_FAIL;
	}
	
	versaloon_cmd_buf[0] = (chip_addr >> 0) & 0xFF;
	SET_LE_U16(&versaloon_cmd_buf[1], data_len);
	versaloon_cmd_buf[3] = stop;
	memcpy(&versaloon_cmd_buf[4], data, data_len);
	
	return usbtoxxx_out_command(USB_TO_I2C, interface_index, versaloon_cmd_buf, 
								data_len + 4, 0);
}
