/**
 * @file
 * @license   Apache License, Version 2.0
 * @copyright Embetech sp. z o.o.
 * @version   1.0.0
 * @purpose   embeNET Node port
 * @brief     BSP implementation
 */

#ifndef EMBENET_INTERRUPT_PRIORITIES_H
#define EMBENET_INTERRUPT_PRIORITIES_H

/**
 * @brief Interrupt priority order.
 */
enum {
    INTERRUPT_PRIORITY_RADIO = 1,
    INTERRUPT_PRIORITY_TIMER = 1,
};

/**
 * @brief Interrupt subpriority order.
 */
enum {
    INTERRUPT_SUBPRIORITY_RADIO = 0,
    INTERRUPT_SUBPRIORITY_TIMER = 1,
};


#endif /* EMBENET_INTERRUPT_PRIORITIES_H */
