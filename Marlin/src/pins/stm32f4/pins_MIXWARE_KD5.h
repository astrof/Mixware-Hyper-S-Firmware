/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#if NOT_TARGET(STM32F4, STM32F4xx)
  #error "Oops! Select an STM32F4 board in 'Tools > Board.'"
#elif HOTENDS > 1 || E_STEPPERS > 1
  #error "MIXWARE KD5 supports up to 1 hotends / E-steppers."
#elif HAS_FSMC_TFT
  #error "MIXWARE KD5 doesn't support FSMC-based TFT displays."
#endif

#define BOARD_INFO_NAME "Mixware Hyper-S V1.0"

// USB Flash Drive support
#define HAS_OTG_USB_HOST_SUPPORT

// Avoid conflict with TIMER_TONE
#define STEP_TIMER                            10

// Use one of these or SDCard-based Emulation will be used
#define FLASH_EEPROM_EMULATION                  // Use Flash-based EEPROM emulation
#define FLASH_EEPROM_LEVELING
#define FLASH_ADDRESS_START               0x080E0000
#define MARLIN_EEPROM_SIZE                0x1000  // 4KB

//
// Servos
//
#define SERVO0_PIN                          PD0   // Enable BLTOUCH

//
// Limit Switches
//
#define X_DIAG_PIN                          PD15
#define Y_DIAG_PIN                          PD2
#define Z_DIAG_PIN                          PC8
#define E0_DIAG_PIN                         PC4
#define E1_DIAG_PIN                         PE7

//
#define X_STOP_PIN                          PC8
#define Y_STOP_PIN                          PA4
#define Z_MIN_PIN                           PC1
#define Z2_MIN_PIN                          PA15
//#define Z_MAX_PIN                           PE0

//
// Steppers
//
#define X_ENABLE_PIN                        PE2
#define X_STEP_PIN                          PE6
#define X_DIR_PIN                           PD1
#ifndef X_CS_PIN
  #define X_CS_PIN                          PD7
#endif

#define Y_ENABLE_PIN                        PE7
#define Y_STEP_PIN                          PD9
#define Y_DIR_PIN                           PB12
#ifndef Y_CS_PIN
  #define Y_CS_PIN                          PD8
#endif

#define Z_ENABLE_PIN                        PD6
#define Z_STEP_PIN                          PE4
#define Z_DIR_PIN                           PD3
#ifndef Z_CS_PIN
  #define Z_CS_PIN                          PD13
#endif

#define E0_ENABLE_PIN                       PE1
#define E0_STEP_PIN                         PE3
#define E0_DIR_PIN                          PE5
#ifndef E0_CS_PIN
  #define E0_CS_PIN                         PD14
#endif

//
// Software SPI pins for TMC2130 stepper drivers
// This board only supports SW SPI for stepper drivers
//
#if HAS_TMC_SPI
  #define TMC_USE_SW_SPI
#endif
#if ENABLED(TMC_USE_SW_SPI)
  #if !defined(TMC_SW_MOSI) || TMC_SW_MOSI == -1
    #define TMC_SW_MOSI                     PD14
  #endif
  #if !defined(TMC_SW_MISO) || TMC_SW_MISO == -1
    #define TMC_SW_MISO                     PD1
  #endif
  #if !defined(TMC_SW_SCK) || TMC_SW_SCK == -1
    #define TMC_SW_SCK                      PD0
  #endif
#endif

#if HAS_TMC_UART
  //
  // Software serial
  // No Hardware serial for steppers
  //
  #define X_SERIAL_TX_PIN                   PD7
  #define X_SERIAL_RX_PIN                   PD7

  #define Y_SERIAL_TX_PIN                   PD8
  #define Y_SERIAL_RX_PIN                   PD8

  #define Z_SERIAL_TX_PIN                   PD13
  #define Z_SERIAL_RX_PIN                   PD13

  #define E0_SERIAL_TX_PIN                  PD14
  #define E0_SERIAL_RX_PIN                  PD14

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE                    19200
#endif

//
// Temperature Sensors
//
#define TEMP_0_PIN                          PB0   // TH1
#define TEMP_BED_PIN                        PB1   // TB1

//
// Heaters / Fans
//
#define HEATER_0_PIN                        PB9   // HEATER1
#define HEATER_BED_PIN                      PD12   // HOT BED

#define FAN_PIN                             PA3   // FAN
//#define FAN1_PIN                            PD1  // FAN1

#define NOT_FAN_PIN                         PA2
#define BOARD_FAN_PIN                       PB11
#define MLED1_PIN                           PB6
#define MLED2_PIN                           PB7
#define MLED3_PIN                           PB10
//
// Thermocouples
//
//#define MAX6675_SS_PIN            HEATER_0_PIN  // TC1 - CS1

//
// Misc. Functions
//
#define MT_DET_1_PIN                        PE0
#define MT_DET_PIN_INVERTING                false // LVGL UI filament RUNOUT PIN STATE

#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN                MT_DET_1_PIN
#endif

//#define LED_PIN                           PB2

// Random Info
#define USB_SERIAL              -1  // USB Serial
#define WIFI_SERIAL              3  // USART3
#define MKS_WIFI_MODULE_SERIAL   1  // USART1
#define MKS_WIFI_MODULE_SPI      2  // SPI2

#define WIFI_IO0_PIN                      PC13  // MKS ESP WIFI IO0 PIN
#define WIFI_IO1_PIN                      PC7   // MKS ESP WIFI IO1 PIN
#define WIFI_RESET_PIN                    PE9   // MKS ESP WIFI RESET PIN

#ifndef SDCARD_CONNECTION
  // #define SDCARD_CONNECTION              ONBOARD
#endif

//
// Onboard SD card
//
// detect pin dont work when ONBOARD and NO_SD_HOST_DRIVE disabled
#if SD_CONNECTION_IS(ONBOARD)
  #define CUSTOM_SPI_PINS                         // TODO: needed because is the only way to set SPI3 for SD on STM32 (by now)
  #if ENABLED(CUSTOM_SPI_PINS)
    #define ENABLE_SPI3
    #define SD_SS_PIN                       -1
    #define SDSS                            PC9
    #define SD_SCK_PIN                      PC10
    #define SD_MISO_PIN                     PC11
    #define SD_MOSI_PIN                     PC12
    #define SD_DETECT_PIN                   PD12
  #endif
#endif

//
// LCD SD
//
#if SD_CONNECTION_IS(LCD)
  #define CUSTOM_SPI_PINS
  #if ENABLED(CUSTOM_SPI_PINS)
    #define ENABLE_SPI1
    #define SDSS                            PE10
    #define SD_SCK_PIN                      PA5
    #define SD_MISO_PIN                     PA6
    #define SD_MOSI_PIN                     PA7
    #define SD_DETECT_PIN                   PE12
  #endif
#endif

//
// LCD / Controller
#define SPI_FLASH
#define HAS_SPI_FLASH                          1
#define SPI_DEVICE                             3
#define SPI_FLASH_SIZE                 0x1000000
#if ENABLED(SPI_FLASH)
  #define W25QXX_CS_PIN                     PB8//PB12
  #define W25QXX_MOSI_PIN                   PB5//PC3
  #define W25QXX_MISO_PIN                   PB4//PC2
  #define W25QXX_SCK_PIN                    PB3//PB13
#endif

/**
 *                _____                                             _____
 *   (BEEPER)PC5 | · · | PE13(BTN_ENC)             (SPI1 MISO) PA6 | · · | PA5 (SPI1 SCK)
 *  (LCD_EN)PD13 | · · | PC6(LCD_RS)                 (BTN_EN1) PE8 | · · | PE10 (SPI1 CS)
 *  (LCD_D4)PE14 | · ·   PE15(LCD_D5)               (BTN_EN2) PE11 | · ·   PA7 (SPI1 MOSI)
 *  (LCD_D6)PD11 | · · | PD10(LCD_D7)               (SPI1_RS) PE12 | · · | RESET
 *           GND | · · | 5V                                    GND | · · | 3.3V
 *                ￣￣￣                                             ￣￣￣
 *                EXP1                                               EXP2
 */

#if ANY(TFT_COLOR_UI, TFT_LVGL_UI, TFT_CLASSIC_UI)
  #ifndef TOUCH_CALIBRATION_X
    #define TOUCH_CALIBRATION_X           -17253
  #endif
  #ifndef TOUCH_CALIBRATION_Y
    #define TOUCH_CALIBRATION_Y            11579
  #endif
  #ifndef TOUCH_OFFSET_X
    #define TOUCH_OFFSET_X                   514
  #endif
  #ifndef TOUCH_OFFSET_Y
    #define TOUCH_OFFSET_Y                   -24
  #endif
  #ifndef TOUCH_ORIENTATION
    #define TOUCH_ORIENTATION    TOUCH_LANDSCAPE
  #endif

  #define TFT_CS_PIN                        PD11
  #define TFT_SCK_PIN                       PA5
  #define TFT_MISO_PIN                      PA6
  #define TFT_MOSI_PIN                      PA7
  #define TFT_DC_PIN                        PD10
  #define TFT_RST_PIN                       PC6
  #define TFT_A0_PIN                  TFT_DC_PIN

  #define TFT_RESET_PIN                     PC6
  #define TFT_BACKLIGHT_PIN                 PD13

  #define TOUCH_BUTTONS_HW_SPI
  #define TOUCH_BUTTONS_HW_SPI_DEVICE          1

  #define LCD_BACKLIGHT_PIN                 PD13
  #ifndef TFT_WIDTH
    #define TFT_WIDTH                        480
  #endif
  #ifndef TFT_HEIGHT
    #define TFT_HEIGHT                       320
  #endif

  #define TOUCH_CS_PIN                      PE14  // SPI1_NSS
  #define TOUCH_SCK_PIN                     PA5   // SPI1_SCK
  #define TOUCH_MISO_PIN                    PA6   // SPI1_MISO
  #define TOUCH_MOSI_PIN                    PA7   // SPI1_MOSI

  #define BEEPER_PIN                        PC5

  #define LCD_READ_ID                       0xD3
  #define LCD_USE_DMA_SPI

  #define TFT_BUFFER_SIZE                  14400

#elif HAS_SPI_LCD
  #define BEEPER_PIN                        PC5
  #define BTN_ENC                           PE13
  #define LCD_PINS_ENABLE                   PD13
  #define LCD_PINS_RS                       PC6
  #define BTN_EN1                           PE8
  #define BTN_EN2                           PE11
  #define LCD_BACKLIGHT_PIN                 -1

  // MKS MINI12864 and MKS LCD12864B; If using MKS LCD12864A (Need to remove RPK2 resistor)
  #if ENABLED(MKS_MINI_12864)
    //#define LCD_BACKLIGHT_PIN             -1
    //#define LCD_RESET_PIN                 -1
    #define DOGLCD_A0                       PD11
    #define DOGLCD_CS                       PE15
    //#define DOGLCD_SCK                    PA5
    //#define DOGLCD_MOSI                   PA7

    // Required for MKS_MINI_12864 with this board
    //#define MKS_LCD12864B
    //#undef SHOW_BOOTSCREEN

  #else // !MKS_MINI_12864

    #define LCD_PINS_D4                     PE14
    #if ENABLED(ULTIPANEL)
      #define LCD_PINS_D5                   PE15
      #define LCD_PINS_D6                   PD11
      #define LCD_PINS_D7                   PD10
    #endif

    #define BOARD_ST7920_DELAY_1    DELAY_NS(96)
    #define BOARD_ST7920_DELAY_2    DELAY_NS(48)
    #define BOARD_ST7920_DELAY_3    DELAY_NS(600)

  #endif // !MKS_MINI_12864
#endif // HAS_SPI_LCD
