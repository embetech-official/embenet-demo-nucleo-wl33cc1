/**
 * @file
 * @license   Commercial
 * @copyright Embetech sp. z o.o.
 * @version   1.2.5
 * @purpose   embeNET MQTT-SN client
 * @brief     MQTT-SN topic manager API
 *
 */

#ifndef MQTTSN_TOPIC_MANAGER_H_
#define MQTTSN_TOPIC_MANAGER_H_

#include "mqttsn_client.h"
#include <embenet/node.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup mqttsn_topic_manager MQTT-SN Topic Manager
 *
 *  This module implements the MQTT-SN topic manager which helps in registration of topics and subscribing to topics.
 *
 *  @{
 */

/**
 * Structure describing a managed topic
 */
typedef struct {
  /// The topic name to register.
  char topicName[MQTTSN_MAX_TOPIC_NAME_LENGTH];
  /// The callback function to call when a message is received on this topic. NULL if the topic is not subscribed, only registered for publishing
  MQTTSNOnPublishReceived onPublishReceived;
  // The QoS subscription level for the topic. Ignored if the topic is not subscribed.
  MQTTSNPacketQoS subscribeQos;
} MQTTSNManagedTopic;

typedef void (*MQTTSNTopicManagerDone)(void);

/**
 * Structure describing the policy for the topic manager
 */
typedef struct {
  /// The minimum period to wait before next topic registration or subscription
  uint32_t minDelayPeriodMs;
  /// The maximum period to wait before next topic registration or subscription
  uint32_t maxDelayPeriodMs;
} MQTTSNTopicManagerPolicy;

typedef enum {
  MQTTSN_TOPIC_MANAGER_STATE_IDLE,
  MQTTSN_TOPIC_MANAGER_STATE_REGISTERING_TOPICS,
  MQTTSN_TOPIC_MANAGER_STATE_SUBSCRIBING_TOPICS,
  MQTTSN_TOPIC_MANAGER_STATE_DONE
} MQTTSNTopicManagerState;

typedef struct {
  /// The MQTT-SN client to use for topic registration and subscription
  MQTTSNClient *client;
  /// The list of topics to register and subscribe
  MQTTSNManagedTopic const *topics;
  /// The number of topics in the list
  size_t topicsCount;
  /// The number of topics to subscribe
  size_t subscriptionCount;
  /// The current state of the topic manager
  MQTTSNTopicManagerState state;
  /// The index of the currently processed topic
  size_t currentTopicIndex;
  /// The callback to call when all topics are registered and subscribed
  MQTTSNTopicManagerDone onDone;
  /// The policy for the topic manager
  MQTTSNTopicManagerPolicy policy;
  /// The worker task handle
  EMBENET_TaskId task;
} MQTTSNTopicManager;

/**
 * @brief Initializes the MQTT-SN topic manager
 *
 * @param[in] manager The MQTT-SN topic manager to initialize
 * @param[in] client The MQTT-SN client to use for topic registration and subscription
 */
void MQTTSN_TOPIC_MANAGER_Init(MQTTSNTopicManager *manager, MQTTSNClient *client);

/**
 * @brief Deinitialize the MQTT-SN topic manager
 *
 * @param[in] manager The MQTT-SN topic manager to deinitialize
 */
void MQTTSN_TOPIC_MANAGER_Deinit(MQTTSNTopicManager *manager);

/**
 * @brief Registers a list of topics
 *
 * This function registers a list of topics for publishing and subscribing. The topics are registered in the order they are provided.
 * First all topics are registers. Next the topics that have an 'onPublishReceived' callback are subscribed.
 * A policy can be provided to control the delay between topic registrations and the number of retries.
 *
 * @param[in] manager The MQTT-SN topic manager
 * @param[in] topics The list of topics to register and subscribe
 * @param[in] topicsCount The number of topics in the list
 * @param[in] policy The policy for the topic manager. If NULL, the default policy is used
 * @param[in] onDone The callback to call when all topics are registered and subscribed. Can be NULL.
 *
 */
void MQTTSN_TOPIC_MANAGER_RegisterTopics(MQTTSNTopicManager *manager, MQTTSNManagedTopic const *topics, size_t topicsCount,
                                         MQTTSNTopicManagerPolicy const *policy, MQTTSNTopicManagerDone onDone);

/**
 * @brief Cancels the current topic manager operation
 *
 * This function cancels the current topic manager operation.
 *
 * @param[in] manager The MQTT-SN topic manager
 */
void MQTTSN_TOPIC_MANAGER_Cancel(MQTTSNTopicManager *manager);

/**
 * @brief Prepares the topics for registration and subscription
 *
 * This function updates the topic names using the following rules:
 * Each  is replaced with the node UID in hexadecimal format
 */
void MQTTSN_TOPIC_MANAGER_PrepareTopics(MQTTSNManagedTopic *topics, size_t topicsCount);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // MQTTSN_TOPIC_MANAGER_H_
