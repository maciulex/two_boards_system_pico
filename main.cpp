#include <stdio.h>

#include "hardware/uart.h"
#include "hardware/structs/spi.h"
#include "hardware/irq.h"
#include "hardware/rtc.h"
#include "hardware/watchdog.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/multicore.h"



#include "registers.cpp"
#include "uart/uart_communication_other_board.cpp"


void loop_core2() {
    printf("Starting uart");
    UART_BETWEEN_BOARDS::add_dataToGet   (UART_BETWEEN_BOARDS::DataType::TIME);
    UART_BETWEEN_BOARDS::add_dataToGet   (UART_BETWEEN_BOARDS::DataType::HARMONOGRAM);

    UART_BETWEEN_BOARDS::add_dataToReport(UART_BETWEEN_BOARDS::DataType::BOOT);
    UART_BETWEEN_BOARDS::add_dataToReport(UART_BETWEEN_BOARDS::DataType::ERROR_CODE);


    UART_BETWEEN_BOARDS::init(true,true,true);
    
    while(1) {
        if (REBOOT_FLAG) {
            watchdog_enable(1,false);
            while(1);
        }
        UART_BETWEEN_BOARDS::checkForRequestedData();
        sleep_ms(50);
    };
}

void loop_core1() {
    while (true) {
        if (REBOOT_FLAG) {
            watchdog_enable(1,false);
            while(1);
        }
        UART_BETWEEN_BOARDS::executeFunctionsToBeExecuted();
        sleep_ms(100);

        // UART_BETWEEN_BOARDS::executeFunctionsToBeExecuted();
    }
}


int main() {
    stdio_init_all();
    multicore_launch_core1(loop_core2);
    loop_core1();
    return 0;
}