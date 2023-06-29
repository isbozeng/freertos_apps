#include <uxr/client/transport.h>

#include <rmw_microxrcedds_c/config.h>

#include "gd32f4xx_libopt.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifdef RMW_UXRCE_TRANSPORT_CUSTOM

// --- micro-ROS Transports ---
#define UART_DMA_BUFFER_SIZE 2048

static uint8_t dma_buffer[UART_DMA_BUFFER_SIZE];
static size_t dma_head = 0, dma_tail = 0;

bool freertos_serial_open(struct uxrCustomTransport * transport){
    // /* configure DMA usart tx mode */    
    dma_single_data_parameter_struct dma_init_struct;
    dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
    dma_init_struct.memory0_addr = NULL;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
    dma_init_struct.number = 0;
    dma_init_struct.periph_addr = 0x40011004;//USART_DATA(USART1) ;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
    dma_init_struct.circular_mode = DMA_CIRCULAR_MODE_DISABLE;
    dma_single_data_mode_init(DMA1, DMA_CH7, &dma_init_struct);
    /* configure DMA mode */
    dma_channel_subperipheral_select(DMA1, DMA_CH7, DMA_SUBPERI4);



    /* configure DMA usart rx mode */
    dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
    dma_init_struct.memory0_addr = (uint32_t)dma_buffer;
    dma_init_struct.number = UART_DMA_BUFFER_SIZE;
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_single_data_mode_init(DMA1, DMA_CH2, &dma_init_struct);
    /* configure DMA mode */
    dma_channel_subperipheral_select(DMA1, DMA_CH2, DMA_SUBPERI4);
    nvic_irq_enable(DMA1_Channel2_IRQn, 5, 0);
    dma_interrupt_enable(DMA1, DMA_CH2, DMA_CHXCTL_FTFIE);
    dma_channel_enable(DMA1, DMA_CH2);
    usart_dma_receive_config(USART0, USART_DENR_ENABLE);
    return true;
}

bool freertos_serial_close(struct uxrCustomTransport * transport){
    /* deinitialize DMA channel7(USART0 tx) */
    dma_deinit(DMA1, DMA_CH7);
    /* deinitialize DMA channel2(USART0 rx) */    
    dma_deinit(DMA1, DMA_CH2);
    return true;
}

size_t freertos_serial_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err){
    
    dma_memory_address_config(DMA1, DMA_CH7, DMA_MEMORY_0, (uint32_t)buf);
    dma_transfer_number_config(DMA1, DMA_CH7, len);
    dma_channel_enable(DMA1, DMA_CH7); 
    usart_dma_transmit_config(USART0, USART_DENT_ENABLE); 
    while (RESET == dma_flag_get(DMA1, DMA_CH7, DMA_INTF_FTFIF)){
        osDelay(1);
    }
    dma_flag_clear(DMA1, DMA_CH7, DMA_INTF_FTFIF);
    dma_channel_disable(DMA1, DMA_CH7);
    return len;
}

size_t freertos_serial_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err){
    __disable_irq();
    dma_tail = UART_DMA_BUFFER_SIZE - dma_transfer_number_get(DMA1, DMA_CH2);
    __enable_irq();

    size_t wrote = 0;
    while ((dma_head != dma_tail) && (wrote < len)){
        buf[wrote] = dma_buffer[dma_head];
        dma_head = (dma_head + 1) % UART_DMA_BUFFER_SIZE;
        wrote++;
    }
    
    return wrote;
}

#endif //RMW_UXRCE_TRANSPORT_CUSTOM
