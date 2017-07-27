TechNexion Pico PI iMX7 {#pico_pi_imx7}
=======================

TechNexion PICO PI IMX7 is a Raspberry PI form-factor modular board featuring
- Gbit ethernet
- USB type A host
- USB type C dual role port
- USB micro AB serial connector
- I2S audio with CTIA headphone jack
- IMX7 dual core Cortex-A7 CPU + one Cortex-M4 core CPU
- 512MB or 1GB memory
- 24-bit TTL LCD interface
- MIPI CSI camera interface
- Mikrobus connector
- Raspberry Pi 3 compatible pinheader


This board is also one of the official Android Things Development boards, and
was handed out to visitors at Google IO 2017.


Revision Support
----------------

Only PICO PI rev B1 and later are supported.


Interface notes
---------------


Pin Mapping
-----------

There are two external pinheaders on the PI baseboard.

One is the PI pinheader, compatible with Raspberry PI 3.
The second is a Mikrobus connector.

|-------------|--------------|--------------|-----------|
| MRAA Number | MRAA Name    | Physical Pin | Function  |
|-------------|--------------|--------------|-----------|
| 1           | -            | J8-01        | 3V3 VCC   |
| 2           | -            | J8-02        | 5V VCC    |
| 3           | PI_I2C1      | J8-03        | I2C1 SDA  |
| 4           | -            | J8-04        | 5V VCC    |
| 5           | PI_I2C1      | J8-05        | I2C1 SCL  |
| 6           | -            | J8-06        | GND       |
| 7           | PI_UART      | J8-07        | UART RTS  |
| 8           | PI_UART      | J8-08        | UART TX   |
| 9           | -            | J8-09        | GND       |
| 10          | PI_UART      | J8-10        | UART RX   |
| 11          | PI_PWM1      | J8-11        | PWM(1)    |
| 12          | PI_UART      | J8-12        | UART CTS  |
| 13          | PI_PWM_P13   | J8-13        | PWM(2)    |
| 14          | -            | J8-14        | GND       |
| 15          | PI_PWM_P15   | J8-15        | PWM(3)    |
| 16          | PI_CAN1      | J8-16        | CAN(1) TX |
| 17          | -            | J8-17        | 3V3 VCC   |
| 18          | PI_CAN1      | J8-18        | CAN(1) RX |
| 19          | PI_SPI       | J8-19        | SPI MOSI  |
| 20          | -            | J8-20        | GND       |
| 21          | PI_SPI       | J8-21        | SPI MISO  |
| 22          | PI_GPIO_P22  | J8-22        | GPIO      |
| 23          | PI_SPI       | J8-23        | SPI SCLK  |
| 24          | PI_SPI       | J8-24        | SPI CS0   |
| 25          | -            | J8-25        | GND       |
| 26          | PI_SPI       | J8-26        | SPI CS1   |
| 27          | PI_I2C2      | J8-27        | I2C2 SDA  |
| 28          | PI_I2C2      | J8-28        | I2C2 SCL  |
| 29          | PI_GPIO_P29  | J8-29        | GPIO(5)   |
| 30          | -            | J8-30        | GND       |
| 31          | PI_GPIO_P31  | J8-31        | GPIO(6)   |
| 32          | PI_GPIO_P32  | J8-32        | GPIO(12)  |
| 33          | PI_GPIO_P33  | J8-33        | GPIO(13)  |
| 34          | -            | J8-34        | GND       |
| 35          | PI_GPIO_P35  | J8-35        | GPIO()    |
| 36          | PI_GPIO_P36  | J8-36        | GPIO(16)  |
| 37          | PI_GPIO_P37  | J8-37        | GPIO(26)  |
| 38          | PI_CAN2      | J8-38        | CAN(2) TX |
| 39          | -            | J8-39        | GND       |
| 40          | PI_CAN2      | J8-40        | CAN(2) RX |
|-------------|--------------|--------------|-----------|

Mikrobus connector:

|-------------|--------------|--------------|-----------|
| MRAA Number | MRAA Name    | Physical Pin | Function  |
|-------------|--------------|--------------|-----------|
| 41          | MBUS_AIO     | JP1-1        | AIO       |
| 42          | -            | JP1-2        | RESET     |
| 43          | MBUS_SPI     | JP1-3        | SPI CS    |
| 44          | MBUS_SPI     | JP1-4        | SPI SCLK  |
| 45          | MBUS_SPI     | JP1-5        | SPI MISO  |
| 46          | MBUS_SPI     | JP1-6        | SPI MOSI  |
| 47          | -            | JP1-7        | 3V3 VCC   |
| 48          | -            | JP1-8        | GND       |
| 49          | MBUS_PWM     | JP2-1        | PWM       |
| 50          | MBUS_GPIO    | JP2-2        | GPIO      |
| 51          | MBUS_UART    | JP2-3        | UART RX   |
| 52          | MBUS_UART    | JP2-4        | UART TX   |
| 53          | MBUS_I2C     | JP2-5        | I2C SCL   |
| 54          | MBUS_I2C     | JP2-6        | I2C SDA   |
| 55          | -            | JP2-7        | 5V VCC    |
| 56          | -            | JP2-8        | GND       |
|-------------|--------------|--------------|-----------|

