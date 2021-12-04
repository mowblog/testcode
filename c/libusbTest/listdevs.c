/*
 * libusb example program to list devices on the bus
 * Copyright (C) 2007 Daniel Drake <dsd@gentoo.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>


#include <libusb.h>

static void print_devs(libusb_device **devs)
{
	libusb_device *dev;
	int i = 0;
	char *u_manufacturer,*u_product;
	libusb_device_handle *dev_handle;
	int ret;
	
	while ((dev = devs[i++]) != NULL) {
		struct libusb_device_descriptor desc;
		int r = libusb_get_device_descriptor(dev, &desc);
		if (r < 0) {
			fprintf(stderr, "failed to get device descriptor");
			return;
		}
		
		u_manufacturer=(char*)calloc(1,256);
		u_product=(char*)calloc(1,256);
		ret = libusb_open(dev,&dev_handle);
		if(ret < 0) {
			sprintf(u_manufacturer,"NULL(%d)",ret);
			sprintf(u_product,"NULL(%d)",ret);
		}
		else {
			ret = libusb_get_string_descriptor_ascii(dev_handle, desc.iProduct ,u_product, 256);
			if(ret < 0){
				sprintf(u_product, "NULL(%d)",ret);
			}
			ret = libusb_get_string_descriptor_ascii(dev_handle, desc.iManufacturer,u_manufacturer, 256);
			if(ret < 0){
				sprintf(u_manufacturer, "NULL(%d)",ret);
			}
		libusb_close(dev_handle);
		}
		
		printf("%04x:%04x (bus %d, device %d)   %s,%s\n",
			desc.idVendor, desc.idProduct,
			libusb_get_bus_number(dev), libusb_get_device_address(dev),
			u_manufacturer,u_product);
		free(u_manufacturer);
		free(u_product);
	}
}

int main(void)
{
	libusb_device **devs;
	int r;
	ssize_t cnt;

	r = libusb_init(NULL);
	if (r < 0)
		return r;

	cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0)
		return (int) cnt;

	print_devs(devs);
	libusb_free_device_list(devs, 1);

	libusb_exit(NULL);
	return 0;
}

