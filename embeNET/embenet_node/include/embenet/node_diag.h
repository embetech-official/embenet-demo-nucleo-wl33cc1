/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   embeNET API
 * @brief     embeNET Node Diagnostic API
 */
#pragma once
#ifndef EMBENET_NODE_DIAG_H_
#define EMBENET_NODE_DIAG_H_

#include <embenet/node_defs.h>

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Raw radio duty cycle counters.
 */
typedef struct {
  uint64_t timeOverall; ///< Total time of radio activity in microseconds.
  uint64_t timeTx;      ///< Time spent transmitting frames in microseconds.
  uint64_t timeRx;      ///< Time spent listening or receiving in microseconds.
  uint64_t timeActive;  ///< Time spent in the ACTIVE radio state in microseconds.
} EMBENET_NODE_DIAG_DutyCycleRawData;

/**
 * @brief Packet queue health counters measured over the last 1000 superframes.
 */
typedef struct {
  unsigned alert;    ///< Number of superframes in which the reception queue reached the alert threshold.
                     ///< A high value indicates peak queue pressure but no packet loss yet.
  unsigned overflow; ///< Number of superframes in which the reception queue overflowed and incoming packets were dropped.
                     ///< A non-zero value indicates packet loss.
} EMBENET_NODE_DIAG_QueueCounters;

/**
 * @brief Role of a neighbor relative to this node.
 */
typedef enum {
  EMBENET_NODE_DIAG_NEIGHBOR_ROLE_PARENT = 0,    ///< The neighbor is this node's current parent.
  EMBENET_NODE_DIAG_NEIGHBOR_ROLE_CHILD = 1,     ///< The neighbor is a child of this node.
  EMBENET_NODE_DIAG_NEIGHBOR_ROLE_UNRELATED = 2, ///< The neighbor has no routing relationship with this node.
} EMBENET_NODE_DIAG_NeighborRole;

/**
 * @brief Diagnostic information for a single neighbor entry.
 */
typedef struct {
  uint64_t eui;                        ///< EUI-64 of the neighbor; 0 if the entry is inactive.
  int8_t rssi;                         ///< Last measured RSSI in dBm; INT8_MAX (127) if RSSI is unavailable.
  EMBENET_NODE_DIAG_NeighborRole role; ///< Role of this neighbor relative to the local node.
} EMBENET_NODE_DIAG_NeighborInfo;

/**
 * @brief Role of a TSCH schedule cell.
 */
typedef enum {
  EMBENET_NODE_DIAG_CELL_ROLE_NONE = 0,         ///< Entry is inactive.
  EMBENET_NODE_DIAG_CELL_ROLE_ADV = 1,          ///< Advertisement cell.
  EMBENET_NODE_DIAG_CELL_ROLE_AUTO_DOWN = 2,    ///< Autonomous downlink cell.
  EMBENET_NODE_DIAG_CELL_ROLE_AUTO_UP = 3,      ///< Autonomous uplink cell.
  EMBENET_NODE_DIAG_CELL_ROLE_AUTO_UP_DOWN = 4, ///< Autonomous bidirectional cell.
  EMBENET_NODE_DIAG_CELL_ROLE_MANAGED = 5,      ///< Managed cell negotiated via 6top.
  EMBENET_NODE_DIAG_CELL_ROLE_APP = 6,          ///< Application-defined cell.
} EMBENET_NODE_DIAG_CellRole;

/**
 * @brief Direction of a TSCH schedule cell.
 */
typedef enum {
  EMBENET_NODE_DIAG_CELL_TYPE_NONE = 0, ///< Entry is inactive.
  EMBENET_NODE_DIAG_CELL_TYPE_TX = 1,   ///< Transmit cell.
  EMBENET_NODE_DIAG_CELL_TYPE_RX = 2,   ///< Receive cell.
  EMBENET_NODE_DIAG_CELL_TYPE_TXRX = 3, ///< Shared TX/RX cell.
} EMBENET_NODE_DIAG_CellType;

/**
 * @brief Diagnostic information for a single TSCH schedule cell.
 */
typedef struct {
  EMBENET_NODE_DIAG_CellRole role; ///< Cell role; @ref EMBENET_NODE_DIAG_CELL_ROLE_NONE if the entry is inactive.
  EMBENET_NODE_DIAG_CellType type; ///< Cell direction; @ref EMBENET_NODE_DIAG_CELL_TYPE_NONE if the entry is inactive.
  uint16_t pdr;                    ///< Packet Delivery Rate expressed in 0.01% units (0..10000).
  uint8_t slotOffset;              ///< Slot offset within the slotframe.
  uint8_t channelOffset;           ///< Channel offset.
  uint64_t companionEui;           ///< EUI-64 of the cell's companion node (peer for TX, source for RX).
} EMBENET_NODE_DIAG_CellInfo;

/**
 * @brief Returns whether the node is operating as a root node.
 *
 * @retval true  the node is operating as a root node
 * @retval false the node is not operating as a root node
 */
bool EMBENET_NODE_DIAG_IsRoot(void);

/**
 * @brief Returns the EUI-64 of the current parent node.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return EUI-64 of the parent node, or `EMBENET_EUI64_INVALID` if the parent EUI-64 is not available.
 */
EMBENET_EUI64 EMBENET_NODE_DIAG_GetParentEUI64(void);

/**
 * @brief Returns the RSSI of the last frame received from the parent node.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Parent RSSI in dBm, or INT8_MAX if the RSSI is not available.
 */
int8_t EMBENET_NODE_DIAG_GetParentRSSI(void);

/**
 * @brief Returns the Packet Delivery Rate (PDR) to the parent node.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return PDR expressed in 0.01% units (0..10000), or 0 if not available.
 */
uint16_t EMBENET_NODE_DIAG_GetParentPDR(void);

/**
 * @brief Returns the node's RPL DAGRank.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return DAGRank value, or UINT16_MAX if not available.
 */
uint16_t EMBENET_NODE_DIAG_GetDAGRank(void);

/**
 * @brief Returns the total number of managed uplink TX cells to the parent node.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Number of uplink cells, or 0 if not available.
 */
unsigned EMBENET_NODE_DIAG_GetUpCells(void);

/**
 * @brief Returns the uplink packet utilization rate.
 *
 * @note Averaged across all managed uplink cells to the parent node.
 * @note Defined as the ratio of used cells to total elapsed cells, expressed in 0.01% units.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Uplink packet rate in 0.01% units (0..10000), or 0 if not available.
 */
uint16_t EMBENET_NODE_DIAG_GetUpPacketRate(void);

/**
 * @brief Returns the total number of autonomous downlink RX cells from child nodes.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Number of downlink cells, or 0 if not available.
 */
unsigned EMBENET_NODE_DIAG_GetDownCells(void);

/**
 * @brief Returns the downlink packet utilization rate.
 *
 * @note Averaged across all autonomous downlink cells (cells used to listen for packets from the parent).
 * @note Defined as the ratio of used cells to total elapsed cells, expressed in 0.01% units.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Downlink packet rate in 0.01% units (0..10000), or 0 if not available.
 */
uint16_t EMBENET_NODE_DIAG_GetDownPacketRate(void);

/**
 * @brief Returns the radio READY state duty cycle.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Radio READY state duty cycle in 0.01% units (0..10000), or 0 if not available.
 */
uint16_t EMBENET_NODE_DIAG_GetRadioReadyDutyCycle(void);

/**
 * @brief Returns the radio TX state duty cycle.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Radio TX state duty cycle in 0.01% units (0..10000), or 0 if not available.
 */
uint16_t EMBENET_NODE_DIAG_GetRadioTxDutyCycle(void);

/**
 * @brief Returns the radio RX state duty cycle.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Radio RX state duty cycle in 0.01% units (0..10000), or 0 if not available.
 */
uint16_t EMBENET_NODE_DIAG_GetRadioRxDutyCycle(void);

/**
 * @brief Returns raw radio duty cycle counters.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return @ref EMBENET_NODE_DIAG_DutyCycleRawData structure; all fields are zero if the data is not available.
 */
EMBENET_NODE_DIAG_DutyCycleRawData EMBENET_NODE_DIAG_GetRadioDutyCycleRaw(void);

/**
 * @brief Returns packet queue alert and overflow counters.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return @ref EMBENET_NODE_DIAG_QueueCounters structure; all fields are zero if the data is not available.
 */
EMBENET_NODE_DIAG_QueueCounters EMBENET_NODE_DIAG_GetQueueThresholdAndOverflowCounters(void);

/**
 * @brief Returns the number of active neighbors.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Number of currently active neighbor entries, or 0 if not available.
 */
unsigned EMBENET_NODE_DIAG_GetNeighborCount(void);

/**
 * @brief Returns diagnostic information for a neighbor by index.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] index neighbor index in the range [0, @ref EMBENET_NODE_DIAG_GetNeighborCount() - 1]
 *
 * @return @ref EMBENET_NODE_DIAG_NeighborInfo for the requested neighbor; zeroed structure if the index is out of range.
 */
EMBENET_NODE_DIAG_NeighborInfo EMBENET_NODE_DIAG_GetNeighborInfo(unsigned index);

/**
 * @brief Returns the number of active TSCH schedule cells.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Number of currently active schedule cell entries, or 0 if not available.
 */
unsigned EMBENET_NODE_DIAG_GetCellsCount(void);

/**
 * @brief Returns diagnostic information for a schedule cell by index.
 *
 * @warning Aborts when called on an uninitialized stack.
 *
 * @param[in] index cell index in the range [0, @ref EMBENET_NODE_DIAG_GetCellsCount() - 1]
 *
 * @return @ref EMBENET_NODE_DIAG_CellInfo for the requested cell; zeroed structure if the index is out of range.
 */
EMBENET_NODE_DIAG_CellInfo EMBENET_NODE_DIAG_GetCellInfo(unsigned index);

/**
 * @brief Returns the slotframe length in number of slots.
 *
 * @note Multiply by @ref EMBENET_NODE_DIAG_GetSlotDurationUs() to obtain the slotframe duration in microseconds.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Number of slots per slotframe, or 0 if not available.
 */
unsigned EMBENET_NODE_DIAG_GetSlotframeLength(void);

/**
 * @brief Returns the duration of a single TSCH slot in microseconds.
 *
 * @note Multiply by @ref EMBENET_NODE_DIAG_GetSlotframeLength() to obtain the slotframe duration in microseconds.
 * @warning Aborts when called on an uninitialized stack.
 *
 * @return Slot duration in microseconds, or 0 if not available.
 */
unsigned EMBENET_NODE_DIAG_GetSlotDurationUs(void);

#ifdef __cplusplus
}
#endif

#endif
