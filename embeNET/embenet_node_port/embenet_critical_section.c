/**
 * @file
 * @license   Apache License, Version 2.0
 * @copyright Embetech sp. z o.o.
 * @version   1.0.0
 * @purpose   embeNET Node port
 * @brief     Implementation of critical section interface for embeNET Node
 */


#include <embenet_port/critical_section.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include <cmsis_compiler.h>
#pragma GCC diagnostic pop

static volatile int      irqNestCounter;
static volatile uint32_t previousIrqState;

void EMBENET_CRITICAL_SECTION_Enter(void) {
    uint32_t irqState = __get_PRIMASK();
    __disable_irq();
    if (0 == irqNestCounter) {
        previousIrqState = irqState;
    }
    ++irqNestCounter;
}


void EMBENET_CRITICAL_SECTION_Exit(void) {
    --irqNestCounter;
    if (irqNestCounter < 0) {
        irqNestCounter = 0;
    }
    if (0 == irqNestCounter && 0 == previousIrqState) {
        __enable_irq();
    }
}
