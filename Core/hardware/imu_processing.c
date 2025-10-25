#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>



#include "ICM42688.h"
#include "delay.h"
#include "main.h"
#include "usart.h"
#include "main_bitmap_bin.h"
#include "imu_processing.h"

// extern imu_fifo_t imu_fifo;

static uint8_t rawIMUData[512] = {0};
uint8_t dummy[17] = {0};

// Function to combine two bytes into a 16-bit integer
int16_t combine_bytes(uint8_t low, uint8_t high) {
    return (int16_t)((high << 8) | low);
}

uint16_t combine_bytes_uint(uint8_t low, uint8_t high) {
    return (uint16_t)((high << 8) | low);
}

// Write to register function (updated to take uint8_t value)
void write_reg_imu(uint8_t reg, uint8_t data) {

}

// Read from register function
uint8_t read_reg_imu(uint8_t reg) {

}

// void processData(uint8_t *data, int data_length, imu_data_t* outputData) {

// }



void readIMU() {

}

// Start measurement function
void start_measure() {
    write_reg_imu(ICM42688_REG_BANK_SEL, 0x00);   // Select register bank 0
    write_reg_imu(ICM42688_PWR_MGMT0, 0x0F);      // Enable measurements
}

// Initialization function for IMU
void init_imu(int rate) {


}

void initFPGA(){
    U1_printf("[INIT] Initializing FPGA Binary\n");
    uint8_t dummy[4] = {0};
    HAL_GPIO_WritePin(FPGA_RST_GPIO_Port, FPGA_RST_Pin, GPIO_PIN_RESET);
    SysTick_Delay_Ms(100);
    HAL_GPIO_WritePin(FPGA_RST_GPIO_Port, FPGA_RST_Pin, GPIO_PIN_SET);
    SysTick_Delay_Ms(100);
    HAL_GPIO_WritePin(FPGA_CS_GPIO_Port, FPGA_CS_Pin, GPIO_PIN_RESET);
    SysTick_Delay_Ms(100);
    HAL_GPIO_WritePin(FPGA_CS_GPIO_Port, FPGA_CS_Pin, GPIO_PIN_SET);
    SysTick_Delay_Ms(100);
        //8 byte empty data
    for (int i=0;i<2;i++){
        // spi_write_blocking(spi1, dummy, sizeof(dummy));
        HAL_SPI_Transmit(&hspi1, dummy,  1, 1000);
    }
    HAL_SPI_Transmit(&hspi1, FPGA_BINARY, (uint16_t)sizeof(FPGA_BINARY),1000);

}