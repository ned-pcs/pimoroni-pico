#pragma once

#include "hardware/i2c.h"
#include "hardware/gpio.h"

// commands and constants
#define SGP30_REQ_FEATURES 0x0020  // The required feature set
#define SGP30_CRC_SEED     0x31    // CRC Seed
#define SGP30_CRC_BASE     0xFF    // Base value for calculating CRC

namespace pimoroni {

  class SGP30 {
    //--------------------------------------------------
    // Constants
    //--------------------------------------------------
  public:
    static const uint8_t DEFAULT_I2C_ADDRESS  = 0x58;
    static const uint8_t DEFAULT_SDA_PIN      = 20;
    static const uint8_t DEFAULT_SCL_PIN      = 21;

    /***** More public constants here *****/

  private:
    /***** Private constants here *****/
    const uint16_t SOFT_RESET                 = 0x0006;
    const uint16_t INIT_AIR_QUALITY           = 0x2003;
    const uint16_t MEASURE_AIR_QUALITY        = 0x2008;
    const uint16_t GET_BASELINE               = 0x2015;
    const uint16_t SET_BASELINE               = 0x201e;
    const uint16_t SET_HUMIDITY               = 0x2061;
    const uint16_t MEASURE_TEST               = 0x2032;
    const uint16_t GET_FEATURE_SET_VERSION    = 0x202f;
    const uint16_t MEASURE_RAW_SIGNALS        = 0x2050;
    const uint16_t GET_SERIAL_ID              = 0x3682;

    //--------------------------------------------------
    // Variables
    //--------------------------------------------------
  private:
    i2c_inst_t *i2c   = i2c0;

    // interface pins with our standard defaults where appropriate
    int8_t address    = DEFAULT_I2C_ADDRESS;
    int8_t sda        = DEFAULT_SDA_PIN;
    int8_t scl        = DEFAULT_SCL_PIN;

    /***** More variables here *****/


    //--------------------------------------------------
    // Constructors/Destructor
    //--------------------------------------------------
  public:
    SGP30() {}

    SGP30(i2c_inst_t *i2c, uint8_t sda, uint8_t scl) :
      i2c(i2c), sda(sda), scl(scl) {}


    //--------------------------------------------------
    // Methods
    //--------------------------------------------------
  public:
    bool init(); //This should be present in all drivers

    // uint8_t command(uint8_t command_name, uint8_t parameters/*=None*/);
    // Get the unique ID from the chip and store locally
    bool retrieve_unique_id();
    // Return the 48-bit unique ID to the caller
    uint64_t get_unique_id();

    bool start_measurement(bool wait_for_setup);
    bool get_air_quality(uint16_t * eCO2, uint16_t * TVOC);
    bool get_air_quality_raw(uint16_t * rawH2, uint16_t * rawEthanol);

    bool soft_reset();

    bool get_baseline(uint16_t *eco2, uint16_t *tvoc);
    void set_baseline(uint16_t eco2, uint16_t tvoc);
    bool set_humidity(uint32_t absolute_humidity);

    // The most recent Total Volatile Organic Compounds in ppb and equivalent CO2 in ppm
    // uint16_t TVOC;
    // uint16_t eCO2;

    // The raw TVOC and eCO2 values - only really for chip testing
    // uint16_t rawTVOC;
    // uint16_t rawEthanol;

    // The 48-bit unique serial number for this chip, retrieved on init
    uint16_t serial_number[3];

  private:
    /***** Private methods here *****/
    bool write_global(uint16_t reg, uint16_t delayms);
    bool write_reg(uint16_t reg, uint16_t delayms);
    bool write_reg_1_word(uint16_t reg, uint16_t delayms, uint16_t value);
    bool write_reg_2_words(uint16_t reg, uint16_t delayms, uint16_t value1, uint16_t value2);
    bool read_reg_1_word(uint16_t reg, uint16_t delayms, uint16_t * value);
    bool read_reg_2_words(uint16_t reg, uint16_t delayms, uint16_t * value1, uint16_t * value2);
    bool read_reg_3_words(uint16_t reg, uint16_t delayms, uint16_t * value1, uint16_t * value2, uint16_t * value3);

    // bool readWordFromCommand(uint8_t command[], uint8_t commandLength,
    //                          uint16_t delay, uint16_t *readdata = NULL,
    //                          uint8_t readlen = 0);
    // uint8_t generateCRC(uint8_t data[], uint8_t datalen);
    //
    uint8_t calculate_crc(uint16_t value);
    uint8_t calculate_crc(uint8_t value1, uint8_t value2);

  };

}
