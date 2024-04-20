/**
   @author Eugene Andrienko
   @brief Brightness control for AGAN X230 board
   @file main.c
*/

#include <popt.h>
#include <stdio.h>
#include <stdlib.h>
#include <hidapi/hidapi.h>

#include "config.h"

/**
   AGAN X230 VID
*/
#define VID 0x10c4
/**
   AGAN X230 PID
*/
#define PID 0x83ce
/**
   Command to read brightness from AGAN X230 board
*/
#define READ_CMD  0x04
/**
   Command to write brightness to AGAN X230 board
*/
#define WRITE_CMD 0x06


static int _hidapi_lib_close(hid_device * device);
static int _brightness_read(hid_device * device);
static int _brightness_write(hid_device * device, int brightness);


int main(int argc, const char * argv[])
{
	/* Parse command-line arguments */
	int brightness = -1;
	struct poptOption optionsTable[] = {
		{"brightness", 'b', POPT_ARG_INT, &brightness, 0, "Set brightness value (from 0 to 15)", "BRIGHTNESS"},
		POPT_AUTOHELP
		{NULL, '\0', POPT_ARG_NONE, NULL, 0, NULL, NULL}
	};
	poptContext pContext = poptGetContext(PACKAGE_NAME, argc, argv, optionsTable,
										  POPT_CONTEXT_POSIXMEHARDER);
	int poptResult = 0;
	if((poptResult = poptGetNextOpt(pContext)) < -1)
	{
		fprintf(stderr, "%s: %s\n",
				poptBadOption(pContext, POPT_BADOPTION_NOALIAS),
				poptStrerror(poptResult));
		poptFreeContext(pContext);
		return 1;
	}
	poptFreeContext(pContext);

	/* Connect to AGAN X230 USB HID interface */
	hid_init();
	hid_device * device;
	if((device = hid_open(VID, PID, NULL)) == NULL)
	{
		fprintf(stderr, "Failed to open AGAN X230 2K board\n");
		return 2;
	}

	if(brightness == -1)
	{
		brightness = _brightness_read(device);
		if(brightness != -1)
		{
			fprintf(stdout, "%d\n", brightness);
		}
		else
		{
			if(_hidapi_lib_close(device))
			{
				return 255;
			}
			return 3;
		}
	}
	else if(_brightness_write(device, brightness))
	{
		if(_hidapi_lib_close(device))
		{
			return 255;
		}
		return 4;
	}

	if(_hidapi_lib_close(device))
	{
		return 255;
	}
	return 0;
}

/**
   Close HIDAPI library.

   @param device[in] Initialized device handle from HIDAPI library.
   @return Zero if successfully close value, otherwise non-zero value.
*/
static int _hidapi_lib_close(hid_device * device)
{
	hid_close(device);
	if(hid_exit())
	{
		fprintf(stderr, "Failed to close HIDAPI library. Memory leak is inevitable\n");
		return 1;
	}
	return 0;
}

/**
   Read brightness from device.

   @param device[in] Initialized device handle from HIDAPI library.
   @return Brightness value from AGAN X230 board or -1 on error.
*/
static int _brightness_read(hid_device * device)
{
	unsigned char buffer[2] = {READ_CMD, 0};
	if(hid_get_feature_report(device, buffer, sizeof(buffer)) != sizeof(buffer))
	{
		fprintf(stderr, "Failed to read brightness from AGAN X230 board!\n");
		return -1;
	}
	return buffer[1];
}

/**
   Write brightness to device.

   @param device[in] Initialized device handle from HIDAPI library.
   @param brightness[in] Brightness value to set (from 0 to 15).
   @return Zero on success, otherwise non-zero value will be returned.
*/
static int _brightness_write(hid_device * device, int brightness)
{
	/* For consistency, accept brightness value in same range,
	   as AGAN X230 board returns to us: from 0 to 15.
	*/
	if(brightness < 0)
	{
		brightness = 0;
	}
	else if(brightness > 15)
	{
		brightness = 15;
	}

	/* But, AGAN X230 board accepts brightness value in range from 0 to 240.
	   Only the next values will really change brightness: 0, 16, 32, 48, 64,
	   80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240.

	   So, just multiply given brightness value to 16.
	*/
	unsigned char buffer[2] = {WRITE_CMD, brightness << 4}; /* brightness * 16 */
	if(hid_write(device, buffer, sizeof(buffer)) != sizeof(buffer))
	{
		fprintf(stderr, "Failed to write brightness to AGAN X230 board!\n");
		return -1;
	}
	return 0;
}
