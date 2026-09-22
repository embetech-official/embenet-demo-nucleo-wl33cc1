/**
 * @file
 * @license   See LICENSE.txt
 * @copyright Embetech sp. z o.o.
 * @version   1.1.1
 * @purpose   embeNET API
 * @brief     embeNET Node Trace API
 */
#pragma once
#ifndef EMBENET_NODE_TRACE_H_
#define EMBENET_NODE_TRACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @defgroup embenet_node_port_api_TRACE Trace functions
 * Provides interface for user-defined trace handles on important network events
 * @{
 */
/**
 * @brief Direction of a TSCH cell event.
 */
typedef enum {
  EMBENET_TRACE_CELL_EVENT_TX, ///< Transmit event.
  EMBENET_TRACE_CELL_EVENT_RX, ///< Receive event.
} EMBENET_TRACE_CellEvent;

/**
 * @brief Role of a TSCH schedule cell.
 */
typedef enum {
  EMBENET_TRACE_CELL_ROLE_ADV,          ///< Advertisement cell.
  EMBENET_TRACE_CELL_ROLE_AUTO_UP,      ///< Autonomous uplink cell.
  EMBENET_TRACE_CELL_ROLE_AUTO_DOWN,    ///< Autonomous downlink cell.
  EMBENET_TRACE_CELL_ROLE_AUTO_UPDOWN,  ///< Autonomous bidirectional cell.
  EMBENET_TRACE_CELL_ROLE_AUTO_MANAGED, ///< Managed cell negotiated via 6top.
} EMBENET_TRACE_CellRole;

/**
 * @brief Direction of a TSCH schedule cell.
 */
typedef enum {
  EMBENET_TRACE_CELL_TYPE_TX,   ///< Transmit cell.
  EMBENET_TRACE_CELL_TYPE_RX,   ///< Receive cell.
  EMBENET_TRACE_CELL_TYPE_TXRX, ///< Shared TX/RX cell.
} EMBENET_TRACE_CellType;

/**
 * @brief IEEE 802.15.4 frame type.
 */
typedef enum {
  EMBENET_TRACE_FRAME_TYPE_BEACON, ///< Beacon frame.
  EMBENET_TRACE_FRAME_TYPE_DATA,   ///< Data frame.
  EMBENET_TRACE_FRAME_TYPE_ACK,    ///< Acknowledgement frame.
} EMBENET_TRACE_FrameType;

/**
 * @brief Link-layer telemetry reported for each TX or RX event.
 */
typedef struct {
  EMBENET_TRACE_CellEvent cellEvent; ///< Whether the event was a TX or RX.
  EMBENET_TRACE_CellRole cellRole;   ///< Role of the cell in which the event occurred.
  EMBENET_TRACE_FrameType frameType; ///< Type of the frame involved.
  unsigned channelOffset;            ///< Channel offset of the cell.
  unsigned slotOffset;               ///< Slot offset of the cell within the slotframe.
  int8_t rssiOrTxPower;              ///< RSSI in dBm for RX events; TX power in dBm for TX events.
  unsigned length;                   ///< Frame length in bytes.
  uint64_t asn;                      ///< Absolute Slot Number at which the event occurred.
  uint64_t src;                      ///< EUI-64 of the frame source.
  uint64_t dst;                      ///< EUI-64 of the frame destination.
  uint64_t node;                     ///< EUI-64 of the local node.
} EMBENET_TRACE_LinkLayerTelemetry;

/**
 * @brief Called immediately after the stack has started.
 * @note Called from @ref EMBENET_NODE_Proc context.
 * @param[in] eui EUI-64 of the local node.
 */
typedef void (*EMBENET_TRACE_Started)(uint64_t eui);

/**
 * @brief Called immediately after the node synchronizes to a network.
 * @note Called from ISR context.
 * @param[in] panid PAN ID of the network the node synchronized to.
 */
typedef void (*EMBENET_TRACE_Synchronized)(uint16_t panid);

/**
 * @brief Called immediately after the node loses synchronization.
 * @note Called from ISR context.
 */
typedef void (*EMBENET_TRACE_Desynchronized)(void);

/**
 * @brief Called when a unicast transmission did not receive an acknowledgement.
 * @note Called from ISR context.
 * @param[in] linkLocalDestinationEui link-local EUI-64 of the intended next-hop recipient.
 * @param[in] destinationEui EUI-64 of the final destination.
 * @param[in] attempt transmission attempt number (1-based).
 */
typedef void (*EMBENET_TRACE_PacketNoAck)(uint64_t linkLocalDestinationEui, uint64_t destinationEui, uint8_t attempt);

/**
 * @brief Called when a managed cell transmission did not receive an acknowledgement.
 * @note Called from ISR context.
 * @param[in] linkLocalDestinationEui link-local EUI-64 of the intended next-hop recipient.
 */
typedef void (*EMBENET_TRACE_ManagedPacketNoAck)(uint64_t linkLocalDestinationEui);

/**
 * @brief Called when all transmission attempts for a packet have been exhausted and the packet is discarded.
 * @note Called from ISR context.
 * @param[in] linkLocalDestinationEui link-local EUI-64 of the intended next-hop recipient.
 * @param[in] destinationEui EUI-64 of the final destination.
 */
typedef void (*EMBENET_TRACE_PacketNotDelivered)(uint64_t linkLocalDestinationEui, uint64_t destinationEui);

/**
 * @brief Called after the node has fully joined a network via a parent.
 *
 * This is called once a parent has been selected, autonomous cells have been scheduled,
 * and the mandatory managed cells have been successfully negotiated.
 *
 * @note Called from @ref EMBENET_NODE_Proc context.
 * @param[in] parentEui EUI-64 of the selected parent node.
 */
typedef void (*EMBENET_TRACE_Joined)(uint64_t parentEui);

/**
 * @brief Called each time the node corrects its clock to the network time source.
 * @param[in] us time correction applied, expressed in microseconds (positive = clock was slow, negative = clock was fast).
 */
typedef void (*EMBENET_TRACE_SyncCorrection)(int32_t us);

/**
 * @brief Called when a new parent node is selected.
 * @note Called from @ref EMBENET_NODE_Proc context.
 * @param[in] parentEui EUI-64 of the newly selected parent (native endianness).
 */
typedef void (*EMBENET_TRACE_ParentSelected)(uint64_t parentEui);

/**
 * @brief Called when the current parent node is considered lost.
 * @note Called from @ref EMBENET_NODE_Proc context.
 * @param[in] parentEui EUI-64 of the lost parent node.
 */
typedef void (*EMBENET_TRACE_ParentLost)(uint64_t parentEui);

/**
 * @brief Called each time a new neighbor is added to the neighbor registry.
 * @note Called from @ref EMBENET_NODE_Proc context.
 * @param[in] neighborEui EUI-64 of the newly added neighbor.
 * @param[in] rssi averaged RSSI of the neighbor in dBm.
 */
typedef void (*EMBENET_TRACE_NeighborAdded)(uint64_t neighborEui, int8_t rssi);

/**
 * @brief Called each time a neighbor is removed from the neighbor registry.
 *
 * A neighbor may be removed due to prolonged inactivity or because the registry is full.
 *
 * @note Called from @ref EMBENET_NODE_Proc context.
 * @param[in] neighborEui EUI-64 of the removed neighbor.
 */
typedef void (*EMBENET_TRACE_NeighborRemoved)(uint64_t neighborEui);

/**
 * @brief Called each time the node's RPL rank changes.
 * @note Called from @ref EMBENET_NODE_Proc context.
 * @param[in] rank new DAGRank value.
 */
typedef void (*EMBENET_TRACE_RankUpdate)(uint16_t rank);

/**
 * @brief Called each time the number of packets in the packet queue changes.
 * @note May be called from ISR context or from @ref EMBENET_NODE_Proc context.
 * @param[in] length current number of packets in the queue.
 */
typedef void (*EMBENET_TRACE_QueueLength)(size_t length);

/**
 * @brief Called each time the radio transitions between sleep and active states.
 * @note May be called from ISR context.
 * @param[in] active true if the radio has just been activated; false if it has just been put to sleep.
 */
typedef void (*EMBENET_TRACE_RadioActivity)(bool active);

/**
 * @brief Called at the start of each TSCH slot.
 * @note May be called from ISR context.
 */
typedef void (*EMBENET_TRACE_SlotStart)(void);

/**
 * @brief Called when a frame is transmitted or received.
 * @note Called from ISR context.
 * @param[in] linkLayerTelemetry pointer to the telemetry data for this event; valid only for the duration of the callback.
 */
typedef void (*EMBENET_TRACE_LinkLayerEvent)(EMBENET_TRACE_LinkLayerTelemetry const *linkLayerTelemetry);

/**
 * @brief Called each time the stack has an idle period with no scheduled activity.
 * @param[in] asn Absolute Slot Number of the first free slot.
 * @param[in] startNwkTime network timestamp at which the free period starts, in microseconds.
 * @param[in] durationUs duration of the free period in microseconds.
 */
typedef void (*EMBENET_TRACE_OnFreeSlots)(uint64_t asn, uint64_t startNwkTime, uint32_t durationUs);

/**
 * @brief Called on entry to and exit from each active TSCH slot (only when the node is synchronized).
 * @note Called from ISR context.
 * @param[in] enters true when the slot starts; false when the slot ends.
 */
typedef void (*EMBENET_TRACE_OnSlotStartEnd)(bool enters);

/**
 * @brief Called on entry to and exit from MAC layer processing routines.
 * @note Radio ISR execution is not included.
 * @note Called from @ref EMBENET_NODE_Proc context.
 * @param[in] enters true when entering the MAC routine; false when leaving.
 */
typedef void (*EMBENET_TRACE_OnMacRoutine)(bool enters);

/**
 * @brief Called on entry to and exit from each radio API call.
 * @note Covers only @c TxEnable, @c RxEnable, @c TxNow and @c RxNow.
 * @note Called from ISR context.
 * @param[in] enters true when entering the radio API function; false when leaving.
 */
typedef void (*EMBENET_TRACE_OnRadioApiUsed)(bool enters);

/**
 * @brief Called on entry to and exit from the radio ISR.
 * @note Called from ISR context.
 * @param[in] enters true when entering the ISR; false when leaving.
 */
typedef void (*EMBENET_TRACE_OnRadioIsr)(bool enters);

/**
 * @brief Set of trace callbacks.
 *
 * Set any field to NULL to disable that particular trace event.
 * The pointed-to structure must remain valid until @ref EMBENET_NODE_SetTraceHandlers is called again or the stack is deinitialized.
 */
typedef struct {
  EMBENET_TRACE_Started onStarted;                       ///< Called when the stack has started.
  EMBENET_TRACE_Synchronized onSynchronized;             ///< Called when the node synchronizes to a network.
  EMBENET_TRACE_Desynchronized onDesynchronized;         ///< Called when the node loses synchronization.
  EMBENET_TRACE_PacketNoAck onPacketNoAck;               ///< Called when a unicast transmission is not acknowledged.
  EMBENET_TRACE_ManagedPacketNoAck onManagedPacketNoAck; ///< Called when a managed cell transmission is not acknowledged.
  EMBENET_TRACE_PacketNotDelivered onPacketNotDelivered; ///< Called when a packet is dropped after all retransmission attempts fail.
  EMBENET_TRACE_Joined onJoined;                         ///< Called when the node has fully joined via a parent.
  EMBENET_TRACE_SyncCorrection onSyncCorrection;         ///< Called each time a clock correction is applied.
  EMBENET_TRACE_ParentSelected onParentSelected;         ///< Called when a new parent is selected.
  EMBENET_TRACE_ParentLost onParentLost;                 ///< Called when the current parent is lost.
  EMBENET_TRACE_NeighborAdded onNeighborAdded;           ///< Called when a neighbor is added to the registry.
  EMBENET_TRACE_NeighborRemoved onNeighborRemoved;       ///< Called when a neighbor is removed from the registry.
  EMBENET_TRACE_RankUpdate onRankUpdate;                 ///< Called when the node's RPL rank changes.
  EMBENET_TRACE_QueueLength onQueueLength;               ///< Called when the packet queue depth changes.
  EMBENET_TRACE_LinkLayerEvent onLinkLayerEvent;         ///< Called on each link-layer TX or RX event.
  EMBENET_TRACE_OnFreeSlots onFreeSlots;                 ///< Called when the stack enters an idle period.
  EMBENET_TRACE_OnSlotStartEnd onSlotStartEnd;           ///< Called at the start and end of each active TSCH slot.
  EMBENET_TRACE_OnMacRoutine onMacRoutine;               ///< Called on entry to and exit from MAC routines.
  EMBENET_TRACE_OnRadioApiUsed onRadioApiUsed;           ///< Called on entry to and exit from radio API functions.
  EMBENET_TRACE_OnRadioIsr onRadioIsr;                   ///< Called on entry to and exit from the radio ISR.
} EMBENET_NODE_TraceHandlers;

/**
 * @brief Installs trace handlers.
 *
 * Replaces the currently active set of trace handlers. May be called at any time after @ref EMBENET_NODE_Init.
 * The pointed-to structure must remain valid until this function is called again or @ref EMBENET_NODE_Deinit is called.
 *
 * @param[in] traceHandlers pointer to the trace handler structure; may be NULL to disable all trace callbacks.
 */
void EMBENET_NODE_SetTraceHandlers(EMBENET_NODE_TraceHandlers const *traceHandlers);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
