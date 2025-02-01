/**
 * @file
 * @license   commercial
 * @copyright Embetech sp. z o.o.
 * @version   1.0.4
 * @purpose   embeNET API
 * @brief     embeNET Node Diagnostic API
 */

#ifndef EMBENET_NODE_DIAG_H_
#define EMBENET_NODE_DIAG_H_

#include "node_defs.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Duty cycle information
 */
typedef struct {
  uint64_t timeOverall; ///< Overall time of activity in microseconds
  uint64_t timeTx;      ///< Time spent on frame transmission in microseconds
  uint64_t timeRx;      ///< Time spent on listening or receiving in microseconds
  uint64_t timeActive;  ///< Time spent on active state in microseconds
} EMBENET_NODE_DIAG_DutyCycleRawData;

/**
 * Queue counters
 */
typedef struct {

  unsigned alert; ///< Number of times the packet reception queue reached the 'alert' condition during the last 1000 superframes. When the number of
                  ///< packets in the packet reception queue reaches the alerting threshold value, the 'alert' condition is signaled.Such a superframe
                  ///< is then counted.The value of queueAlertCnt is the number of such superframes in the last 1000 superframes.It gives information
                  ///< about peak packet queue usage.

  unsigned overflow; ///< Number of times the packet reception queue was overflown during the last 1000 superframes. When the packet reception queue
                     ///< is overflown it cannot store any more packets and subsequent incoming packets are dropped. When that happens in a given
                     ///< superframe, such a superframe is then counted. The value of queueOverflowCnt is the number of such superframes in the last
                     ///< 1000 superframes. It gives information about packet queue failures.
} EMBENET_NODE_DIAG_QueueCounters;

/**
 * Neighbor role
 */
typedef enum {
  EMBENET_NODE_DIAG_NEIGHBOR_ROLE_PARENT = 0,
  EMBENET_NODE_DIAG_NEIGHBOR_ROLE_CHILD = 1,
  EMBENET_NODE_DIAG_NEIGHBOR_ROLE_UNRELATED = 2,
} EMBENET_NODE_DIAG_NeighborRole;

/**
 * Neighbor diagnostic information
 */
typedef struct {
  uint64_t eui;                        ///< 0 if entry is inactive
  int8_t rssi;                         ///< 127 denotes, that rssi could not be obtained
  EMBENET_NODE_DIAG_NeighborRole role; ///< neighbor role
} EMBENET_NODE_DIAG_NeighborInfo;

/**
 * Cell role
 */
typedef enum {
  EMBENET_NODE_DIAG_CELL_ROLE_NONE = 0,
  EMBENET_NODE_DIAG_CELL_ROLE_ADV = 1,
  EMBENET_NODE_DIAG_CELL_ROLE_AUTO_DOWN = 2,
  EMBENET_NODE_DIAG_CELL_ROLE_AUTO_UP = 3,
  EMBENET_NODE_DIAG_CELL_ROLE_AUTO_UP_DOWN = 4,
  EMBENET_NODE_DIAG_CELL_ROLE_MANAGED = 5,
  EMBENET_NODE_DIAG_CELL_ROLE_APP = 6,
} EMBENET_NODE_DIAG_CellRole;

/**
 * Cell type
 */
typedef enum {
  EMBENET_NODE_DIAG_CELL_TYPE_NONE = 0,
  EMBENET_NODE_DIAG_CELL_TYPE_TX = 1,
  EMBENET_NODE_DIAG_CELL_TYPE_RX = 2,
  EMBENET_NODE_DIAG_CELL_TYPE_TXRX = 3,
} EMBENET_NODE_DIAG_CellType;

/**
 * Cell diagnostic information
 */
typedef struct {
  EMBENET_NODE_DIAG_CellRole role; ///< EMBENET_NODE_DIAG_CELL_ROLE_NONE if entry is inactive
  EMBENET_NODE_DIAG_CellType type; ///< EMBENET_NODE_DIAG_CELL_TYPE_NONE if entry is inactive
  uint16_t pdr;                    ///< expressed in 0.01% unit
  uint8_t slotOffset;              ///< slot offset
  uint8_t channelOffset;           ///< channel offset
  uint64_t companionEui;           ///< companion EUI
} EMBENET_NODE_DIAG_CellInfo;

/**
 * Return if node operates as ROOT.
 *
 * @retval true - node operates as root
 * @retval false - node does not operate as root
 */
bool EMBENET_NODE_DIAG_IsRoot(void);

/**
 * Returns parent EUI.
 *
 * @warning Aborts when called on an uninitialized stack.
 * @return parent EUI, EMBENET_EUI64_INVALID if could not obtain parent EUI
 */
EMBENET_EUI64 EMBENET_NODE_DIAG_GetParentEUI64(void);

/**
 * Returns parent RSSI.
 *
 * @warning Aborts when called on an uninitialized stack.
 * @return parent RSSI, INT8_MAX if RSSI is not available
 */
int8_t EMBENET_NODE_DIAG_GetParentRSSI(void);

/**
 * Returns parent PDR.
 *
 * @warning Aborts when called on an uninitialized stack.
 * @return current Packet Delivery Rate to parent expressed in 0.01% units (0..10000), 0 if it is not possible to obtain
 */
uint16_t EMBENET_NODE_DIAG_GetParentPDR(void);

/**
 * Return node's DAGRank.
 *
 * @warning Aborts when called on an uninitialized stack.
 * @return node's DAGRank, UINT16_MAX if it is not possible to obtain
 */
uint16_t EMBENET_NODE_DIAG_GetDAGRank(void);

/**
 * Returns sum of managed TX cells to parent node.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return up cells count, 0 if it is not possible to obtain
 */
unsigned EMBENET_NODE_DIAG_GetUpCells(void);

/**
 * Returns uplink packet rate.
 *
 * @note Packet rate is averaged through all managed cells to parent node.
 * @note It is defined as the rate of used cells to all passed cells to parent node.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return up packet rate, 0 if it is not possible to obtain
 */
uint16_t EMBENET_NODE_DIAG_GetUpPacketRate(void);

/**
 * Returns sum of RX cells from child nodes.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return down cells count, 0 if it is not possible to obtain
 */
unsigned EMBENET_NODE_DIAG_GetDownCells(void);

/**
 * Returns downlink packet rate.
 *
 * @note Packet rate is averaged through all downlink autonomous cells (autonomous cells to listen for packets from parent).
 * @note It is defined as the rate of used cells to all passed cells from parent node.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return up packet rate in 0.01% unit, 0 if it is not possible to obtain
 */
uint16_t EMBENET_NODE_DIAG_GetDownPacketRate(void);

/**
 * Returns radio ready state duty cycle.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return radio READY state duty cycle in 0.01% unit, 0 if it is not possible to obtain
 */
uint16_t EMBENET_NODE_DIAG_GetRadioReadyDutyCycle(void);

/**
 * Returns radio TX duty cycle.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return radio TX state duty cycle in 0.01% unit, 0 if it is not possible to obtain
 */
uint16_t EMBENET_NODE_DIAG_GetRadioTxDutyCycle(void);

/**
 * Returns radio RX duty cycle.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return radio RX state duty cycle in 0.01% unit, 0 if it is not possible to obtain
 */
uint16_t EMBENET_NODE_DIAG_GetRadioRxDutyCycle(void);

/**
 * Returns radio duty cycle RAW data.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return @ref EMBENET_NODE_DIAG_DutyCycleRawData, zeroed structure if it is not possible to obtain
 */
EMBENET_NODE_DIAG_DutyCycleRawData EMBENET_NODE_DIAG_GetRadioDutyCycleRaw(void);

/**
 * Returns queue overflow and alarm threshold counters.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return @ref EMBENET_NODE_DIAG_QueueCounters, zeroed structure if it is not possible to obtain
 */
EMBENET_NODE_DIAG_QueueCounters EMBENET_NODE_DIAG_GetQueueThresholdAndOverflowCounters(void);

/**
 * Returns neighbor count.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return neighbors count that are active, 0 if it is not possible to obtain
 */
unsigned EMBENET_NODE_DIAG_GetNeighborCount(void);

/**
 * Returns neighbor information.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] index - should be in range of <0, EMBENET_NODE_DIAG_GetNeighborCount()-1>
 * @return @ref EMBENET_NODE_DIAG_NeighborInfo, zeroed structure if it is not possible to obtain
 */
EMBENET_NODE_DIAG_NeighborInfo EMBENET_NODE_DIAG_GetNeighborInfo(unsigned index);

/**
 * Returns active communication cells count.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return active cells count, if it is not possible to obtain
 */
unsigned EMBENET_NODE_DIAG_GetCellsCount(void);

/**
 * Returns cell information.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] index - should be in range of <0, EMBENET_NODE_DIAG_GetCellsCount()-1>
 * @return @ref EMBENET_NODE_DIAG_CellInfo, zeroed structure if it is not possible to obtain
 */
EMBENET_NODE_DIAG_CellInfo EMBENET_NODE_DIAG_GetCellInfo(unsigned index);

/**
 * Returns slotframe length in slots count.
 *
 * @note Multiply @ref EMBENET_NODE_DIAG_GetSlotframeLength() by @ref EMBENET_NODE_DIAG_GetSlotDurationUs() to get slotframe length.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return slots count in superframe, 0 if it is not possible to obtain
 */
unsigned EMBENET_NODE_DIAG_GetSlotframeLength(void);

/**
 * Returns slot duration in microseconds.
 *
 * @note Multiply @ref EMBENET_NODE_DIAG_GetSlotframeLength() by @ref EMBENET_NODE_DIAG_GetSlotDurationUs() to get slotframe length.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return slot duration, 0 if it is not possible to obtain
 */
unsigned EMBENET_NODE_DIAG_GetSlotDurationUs(void);

#ifdef __cplusplus
}
#endif

#endif /* EMBENET_NODE_DIAG_H_ */
