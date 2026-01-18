// default include provided during app creation
#include <zephyr/kernel.h>

#include <stdbool.h>

#include <zephyr/device.h>

#include <zephyr/drivers/uart.h>
#include <zephyr/usb/usb_device.h>

#define CDC_NODE DT_NODELABEL(cdc_acm_uart0)

const struct device *cdc = DEVICE_DT_GET(CDC_NODE);
const char m[] = "Hello from USB Dongle";

// default main application thread
int main(void)
{
        if (usb_enable(NULL) != 0)
        {
                return 0;
        }

        while(true)
        {
                for(size_t i = 0; i < sizeof(m); i++)
                {
                        uart_poll_out(cdc, m[i]);
                }
                k_sleep(K_SECONDS(3));
        }

        // should not get here
        return 0;
}
