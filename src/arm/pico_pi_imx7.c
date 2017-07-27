/*
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>
#include <mraa/common.h>
#include <mraa_internal_types.h>

#include "arm/pico_pi_imx7.h"
#include "common.h"
#include "mraa_internal.h"

static const mraa_pincapabilities_t gpio_cap =  { .valid = 1u, .gpio = 1u, };
static const mraa_pincapabilities_t i2c_cap =   { .valid = 1u, .i2c = 1u };
static const mraa_pincapabilities_t pwm_cap =   { .valid = 1u, .pwm = 1u };
static const mraa_pincapabilities_t spi_cap =   { .valid = 1u, .spi = 1u };
static const mraa_pincapabilities_t uart_cap =  { .valid = 1u, .uart = 1u };
static const mraa_pincapabilities_t power_cap = { .valid = 1u };

void 
technexion_add_gpio(mraa_board_t *b, const char *name, int pin, int gpio_number) {
    b->pins[pin].capabilities = gpio_cap;
    if (gpio_number >= 0) {
        b->pins[pin].gpio.pinmap = gpio_number;
    }
    b->gpio_count++;
    snprintf(b->pins[pin].name, MRAA_PIN_NAME_SIZE, "%s", name);
}

void
technexion_add_power_pin(mraa_board_t *b, const char *name, int pin) {
    b->pins[pin].capabilities = power_cap;
    strncpy(b->pins[pin].name, name, MRAA_PIN_NAME_SIZE);
}

void
technexion_add_i2c_bus(mraa_board_t *b, const char *name, int scl_pin, int sda_pin, int bus_no) {
    b->i2c_bus[b->i2c_bus_count].bus_id = bus_no;
    b->i2c_bus[b->i2c_bus_count].sda = scl_pin;
    b->i2c_bus[b->i2c_bus_count].scl = sda_pin;  
    b->i2c_bus[b->i2c_bus_count].name = strdup(name);

    b->i2c_bus_count++;

    snprintf(b->pins[scl_pin].name, MRAA_PIN_NAME_SIZE, "%s_SCL", name);
    b->pins[scl_pin].capabilities = i2c_cap;

    snprintf(b->pins[sda_pin].name, MRAA_PIN_NAME_SIZE, "%s_SDA", name);
    b->pins[sda_pin].capabilities = i2c_cap;
}

void
technexion_add_uart(mraa_board_t *b, const char *name, int rx_pin, int tx_pin, int rts_pin, int cts_pin, const char *devpath) {
    b->uart_dev[b->uart_dev_count].rx = rx_pin;
    b->uart_dev[b->uart_dev_count].tx = tx_pin;
    b->uart_dev[b->uart_dev_count].device_path = devpath;
    b->uart_dev[b->uart_dev_count].name = strdup(name);
    b->uart_dev_count ++;

    b->pins[rx_pin].capabilities = uart_cap;
    b->pins[tx_pin].capabilities = uart_cap;

    snprintf(b->pins[rx_pin].name, MRAA_PIN_NAME_SIZE, "%s_RX", name);
    snprintf(b->pins[tx_pin].name, MRAA_PIN_NAME_SIZE, "%s_TX", name);

    if (rts_pin >= 0) {
        b->pins[rts_pin].capabilities = uart_cap;
        snprintf(b->pins[rts_pin].name, MRAA_PIN_NAME_SIZE, "%s_RTS", name);
    }
    if (cts_pin >= 0) {
        b->pins[cts_pin].capabilities = uart_cap;
        snprintf(b->pins[cts_pin].name, MRAA_PIN_NAME_SIZE, "%s_CTS", name);
    }
}

void
technexion_add_spi_bus(mraa_board_t *b, const char *name, int miso_pin, int mosi_pin, int sclk_pin, int cs_pin, int bus_number) {
    b->spi_bus[b->spi_bus_count].bus_id = bus_number;
    b->spi_bus[b->spi_bus_count].slave_s = 0;
    b->spi_bus[b->spi_bus_count].cs = cs_pin;
    b->spi_bus[b->spi_bus_count].mosi = mosi_pin;
    b->spi_bus[b->spi_bus_count].miso = miso_pin;
    b->spi_bus[b->spi_bus_count].sclk = sclk_pin;
    b->spi_bus[b->spi_bus_count].name = strdup(name);

    b->spi_bus_count ++;

    b->pins[miso_pin].capabilities = spi_cap;
    snprintf(b->pins[miso_pin].name, MRAA_PIN_NAME_SIZE, "%s_MISO", name);
    b->pins[mosi_pin].capabilities = spi_cap;
    snprintf(b->pins[mosi_pin].name, MRAA_PIN_NAME_SIZE, "%s_MOSI", name);
    b->pins[sclk_pin].capabilities = spi_cap;
    snprintf(b->pins[sclk_pin].name, MRAA_PIN_NAME_SIZE, "%s_SCLK", name);
    if (cs_pin >= 0) {
        b->pins[cs_pin].capabilities = spi_cap;
        snprintf(b->pins[cs_pin].name, MRAA_PIN_NAME_SIZE, "%s_CS", name);
    }
}

void
technexion_add_pwm(mraa_board_t *b, const char *name, int pin, int number) {
    b->pins[pin].capabilities = pwm_cap;
    b->pwm_dev[b->pwm_dev_count].index = number;
    b->pwm_dev[b->pwm_dev_count].name = strdup(name);
    b->pwm_dev_count++;

    snprintf(b->pins[pin].name, MRAA_PIN_NAME_SIZE, "%s", name);
}

/* pins 1-40 are raspberry pi style connector on PI baseboard 
   pins 41-56 is the Mikrobus connector on the PI baseboard
*/

#define PICO_PI_JP1_BASE 40
#define PICO_PI_JP2_BASE 48

static const char *pico_imx7_name = "Pico Pi iMX7";

mraa_board_t*
mraa_pico_pi_imx7(void)
{
    mraa_board_t* b = (mraa_board_t*)calloc(1, sizeof(mraa_board_t));

    if (b == NULL) {
        return NULL;
    }
    b->phy_pin_count = 57;
    b->platform_name = pico_imx7_name;
    b->pins = (mraa_pininfo_t*) calloc(b->phy_pin_count, sizeof(mraa_pininfo_t));
    if (b->pins == NULL) {
        free(b);
        return NULL;
    }
    b->no_bus_mux = 1;

    /* TODO: fix all GPIO / bus numbers */

    /* 40-pin Raspberry PI style connector */
    /* pins 16, 18, 38, 40 omitted since MRAA does not (yet?) support CAN buses */
    technexion_add_power_pin(b, "3V3", 1);
    technexion_add_power_pin(b, "5V", 2);
    technexion_add_i2c_bus(b, "PI_I2C1", 3, 5, 0);
    technexion_add_power_pin(b, "5V", 4);
    technexion_add_power_pin(b, "GND", 6);
    technexion_add_uart(b, "PI_UART", 8, 10, 7, 12, "/dev/ttymxc5");
    technexion_add_power_pin(b, "GND", 9);

    technexion_add_pwm(b, "PI_PWM_P11", 11, 0);
    technexion_add_gpio(b, "PI_GPIO_P13", 13, 35);

    technexion_add_power_pin(b, "3V3", 17);
    technexion_add_power_pin(b, "GND", 20);

    technexion_add_spi_bus(b, "PI_SPI", 19, 21, 23, 24, 2);
    technexion_add_gpio(b, "PI_GPIO_P22", 22, -1);
    technexion_add_power_pin(b, "GND", 25);

    technexion_add_i2c_bus(b, "PI_I2C2", 27, 28, 1);
    technexion_add_gpio(b, "PI_GPIO3", 29, 33);
    technexion_add_power_pin(b, "GND", 30);
    technexion_add_gpio(b, "PI_GPIO_P31", 31, 34);
    technexion_add_gpio(b, "PI_GPIO_P32", 32, -1);
    technexion_add_pwm(b, "PI_PWM2", 33, 1);
    technexion_add_power_pin(b, "GND", 34);
    technexion_add_gpio(b, "PI_GPIO_P35", 35, 32);
    technexion_add_gpio(b, "PI_GPIO_P36", 36, 39);
    technexion_add_gpio(b, "PI_GPIO_P37", 37, 37);
    technexion_add_power_pin(b, "GND", 39);

    /* Mikrobus connector, starting at pin index 41 for left side, and 49 for right side */
    technexion_add_gpio(b, "MBUS_RESET", 42, 25);
    technexion_add_spi_bus(b, "MBUS_SPI", 45, 46, 44, 43, 2);
    technexion_add_power_pin(b, "3V3", 47);
    technexion_add_power_pin(b, "GND", 48);
    
    technexion_add_pwm(b, "MBUS_PWM", 49, 2);
    technexion_add_gpio(b, "MBUS_RESET", 50, 26);
    technexion_add_uart(b, "MBUS_UART", 51, 52, -1, -1, "/dev/ttymxc5");
    technexion_add_i2c_bus(b, "MBUS_I2C", 53, 54, 0);
    technexion_add_power_pin(b, "5V", 55);
    technexion_add_power_pin(b, "GND", 56);
    b->def_i2c_bus = 0;

    /* This pointer is unused, but having it NULL would make i2c functions fail */
    b->adv_func = (mraa_adv_func_t*) calloc(1, sizeof(mraa_adv_func_t));

    return b;
}
