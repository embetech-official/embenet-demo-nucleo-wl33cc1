<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.8" doxygen_gitid="c2fe5c3e4986974eb2a97608b24086683502f07f">
  <compound kind="file">
    <name>gateway_setup_hivemq_edge.md</name>
    <path></path>
    <filename>gateway__setup__hivemq__edge_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>gateway_setup_small_things.md</name>
    <path></path>
    <filename>gateway__setup__small__things_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>readme.md</name>
    <path></path>
    <filename>readme_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>tutorial.md</name>
    <path></path>
    <filename>tutorial_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>mqttsn_client.h</name>
    <path>C:/workspace_embenet/embenet_service_mqttsn/src/include/embenet/</path>
    <filename>mqttsn__client_8h.html</filename>
    <class kind="struct">MQTTSNClientEventHandlers</class>
    <class kind="struct">MQTTSNTopicDescriptor</class>
    <class kind="struct">MQTTSNSessionFlags</class>
    <class kind="struct">MQTTSNQosMsg</class>
    <class kind="struct">MQTTSNClient</class>
    <member kind="define">
      <type>#define</type>
      <name>MQTTSN_MAX_TOPIC_NAME_LENGTH</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gae61253812b29c9a2cd953fe3c5c50aa4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MQTTSN_MAX_MESSAGE_LENGTH</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga0af3deef95f8c44278c2de078b5dbf3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MQTTSN_MAX_CLIENT_ID_LENGTH</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gaad17603bc71b25a4d1d31923d14cbe55</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MQTTSN_CLIENT_MAX_TOPICS_TO_SUBSCRIBE</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gab9014ab0174f26a9bfc2328332f6bc4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MQTTSN_CLIENT_MAX_TOPICS_TO_PUBLISH</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga1978094ab7ad81fa4a011a9a8665c8de</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MQTTSN_CLIENT_MAX_PINGRESP_LOST</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga2da72f6d309f08e58e576a21e6bf1e03</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint16_t</type>
      <name>MQTTSNTopicId</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gaa5559fcdef77c6ad4f23615c48bae21e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>MQTTSNOnClientConnected</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gaf294b9f0491c69cb04d73cdfff30a059</anchor>
      <arglist>)(struct MQTTSNClient *client)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>MQTTSNOnClientDisconnected</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gafb2fd1e8bee6651df18fdf2ae7eac5d1</anchor>
      <arglist>)(struct MQTTSNClient *client, MQTTSNClientDisconnectionReason disconnectionReason)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>MQTTSNOnTopicRegisteredByClient</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga65939421635c5a171808ddf652fa3589</anchor>
      <arglist>)(const struct MQTTSNClient *client, MQTTSNTopicId topicId, char const *topicName)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>MQTTSNOnTopicRegisteredByGateway</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga275ce5bb73e0da28b9da1904dd263498</anchor>
      <arglist>)(struct MQTTSNClient *client, MQTTSNTopicId topicId, char const *topicName)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>MQTTSNOnTopicSubscribedByClient</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga216869a4fda51d88bfa11731bfcde6ab</anchor>
      <arglist>)(const struct MQTTSNClient *client, MQTTSNTopicId topicId, char const *topicName)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>MQTTSNOnTopicUnsubscribedByClient</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga9577fb3c7b093d7ef768e056ff6929a9</anchor>
      <arglist>)(const struct MQTTSNClient *client, MQTTSNTopicId topicId, char const *topicName)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>MQTTSNOnPublishReceived</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gae78e64768a2c0a84604fa31686956123</anchor>
      <arglist>)(struct MQTTSNClient *client, MQTTSNTopicId topicId, void const *data, size_t dataSize)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>MQTTSNOnPublishSent</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga23fa36af1420b942dc8fe4b6db6f7604</anchor>
      <arglist>)(struct MQTTSNClient *client, MQTTSNTopicId topicId, void const *data, size_t dataSize)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>MQTTSNClientState</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gadf99316dabd39dcdaad846ad49f90492</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_STATE_DISCONNECTED</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggadf99316dabd39dcdaad846ad49f90492a7d6a06f8ba4b236a4f0def4763b66a48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_STATE_CONNECTING</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggadf99316dabd39dcdaad846ad49f90492ae3c9f01f05eee7e2e4183dc428bf756b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_STATE_AWAITING_WILL_TOPIC_REQ</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggadf99316dabd39dcdaad846ad49f90492ade9d1b379f036e1964c4446b49ac1982</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_STATE_AWAITING_WILL_MSG_REQ</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggadf99316dabd39dcdaad846ad49f90492a3972fc8d95f1e5b76cc863c972f054f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_STATE_CONNECTED</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggadf99316dabd39dcdaad846ad49f90492a1f17b52570387350f494e085e4cf5e81</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_STATE_DISCONNECTING</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggadf99316dabd39dcdaad846ad49f90492aa47031ce03cb2458d759e325170c94bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>MQTTSNClientResult</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gab3bcf9e91e317aef26511a8f7d5ed6ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_OK</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caad9ee374ac01dc8ab62db290cd34258ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_INVALID_INPUT_ARGUMENT</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caa54fa7aaf18049b223b813b219571bc4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_FAILED_TO_REGISTER_UDP_SOCKET</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caa6cf88cc5b8dcd72de23fbaf6f6915fd0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_FAILED_TO_CREATE_TASK</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caae3c62c1b2d5c3da6d2fab6561060b4e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_FAILED_TO_SEND_PACKET</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caa81f94792c46247aab17d289174f56f44</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_FAILED_TO_SERIALIZE_PACKET</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caa763c0fb292f046d4fa2fae5fbcf850fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_CLIENT_NOT_CONNECTED</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caa099a6d8ebcd84710c533ad7e4b8420ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_CLIENT_ALREADY_CONNECTED</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caaab2f586f806487eff28a6cba8e707818</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_TOPIC_NOT_FOUND</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caafb3267c43ab2bed483a534bd923fd95a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_PUBLISH_BUFFER_FULL</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caa6d6073688e17ed2a2236837f015a3490</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_SUBSCRIBE_BUFFER_FULL</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caaa6abf6925b04c5b8912e1c9e4076a919</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_TOPIC_TOO_LONG</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caa26864429081480a62fe60c22f44ba208</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_RESULT_MESSAGE_TOO_LONG</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ggab3bcf9e91e317aef26511a8f7d5ed6caa5e70893e7f9d5f9d873fcaf00be3a8b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>MQTTSNPacketQoS</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga8b373e8a50858d583b8533a10a3c8797</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_QOS0</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gga8b373e8a50858d583b8533a10a3c8797a4dc6009b4ffd1b407c856f24b8912eb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_QOS1</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gga8b373e8a50858d583b8533a10a3c8797a151a37fdd3ddc703863849e964a44a08</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_QOS2</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gga8b373e8a50858d583b8533a10a3c8797a3751c8593369d4f6c357a16e99a57e67</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>MQTTSNClientDisconnectionReason</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga062f5d134d4d0653f8db8c2dd7a7fda9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_DISCONNECTED_DUE_TO_OWN_REQUEST</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gga062f5d134d4d0653f8db8c2dd7a7fda9a0d908db66af0a1d02b8da59950426f51</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_DISCONNECTED_BY_GATEWAY</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gga062f5d134d4d0653f8db8c2dd7a7fda9a5d44168c77498638958d7a5f8dfed57c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>MQTTSN_CLIENT_DISCONNECTED_DUE_TO_TIMEOUT</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gga062f5d134d4d0653f8db8c2dd7a7fda9a13395db3f73ff7770a9df5f84666534b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>MQTTSNClientResult</type>
      <name>MQTTSN_CLIENT_Init</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gaf67ea7745cd27c8ae9aef80ad63913cc</anchor>
      <arglist>(MQTTSNClient *client, uint16_t port, char const *clientId, MQTTSNClientEventHandlers const *eventHandlers)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MQTTSN_CLIENT_Deinit</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga192746f27b7d849298461d0972297453</anchor>
      <arglist>(MQTTSNClient *client)</arglist>
    </member>
    <member kind="function">
      <type>MQTTSNClientResult</type>
      <name>MQTTSN_CLIENT_Connect</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga5ea2b59897385bb2845087ae2472e132</anchor>
      <arglist>(MQTTSNClient *client, EMBENET_IPV6 const *gatewayAddress, uint16_t gatewayPort, uint32_t keepAliveTimeMs, uint32_t gatewayTimeoutMs, char const *willTopic, uint8_t const *willMsg, uint8_t const qosRetransmissions)</arglist>
    </member>
    <member kind="function">
      <type>MQTTSNClientResult</type>
      <name>MQTTSN_CLIENT_Disconnect</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gae23c07254ed7fa1f81db9460ade03ea6</anchor>
      <arglist>(MQTTSNClient *client)</arglist>
    </member>
    <member kind="function">
      <type>MQTTSNClientResult</type>
      <name>MQTTSN_CLIENT_RegisterTopic</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga76c610cdfd1a3c69a83b1e4d8be3946f</anchor>
      <arglist>(MQTTSNClient *client, char const *topic, MQTTSNOnTopicRegisteredByClient onTopicRegisteredCallback)</arglist>
    </member>
    <member kind="function">
      <type>MQTTSNTopicId</type>
      <name>MQTTSN_CLIENT_GetTopicId</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gafc24c8d8618e8dbd8be9ce6ceda25903</anchor>
      <arglist>(MQTTSNClient *client, char const *topic)</arglist>
    </member>
    <member kind="function">
      <type>MQTTSNClientResult</type>
      <name>MQTTSN_CLIENT_PublishMessage</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga188d770e424ffd4f827184d2d0783923</anchor>
      <arglist>(MQTTSNClient *client, char const *topic, MQTTSNPacketQoS qos, void const *message, size_t messageLen, MQTTSNOnPublishSent onPublishSentCallback)</arglist>
    </member>
    <member kind="function">
      <type>MQTTSNClientResult</type>
      <name>MQTTSN_CLIENT_PublishMessageById</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga5b0ecab2e1f4d0433773267fd8c21e70</anchor>
      <arglist>(MQTTSNClient *client, MQTTSNTopicId topicId, MQTTSNPacketQoS qos, void const *message, size_t messageLen, MQTTSNOnPublishSent onPublishSentCallback)</arglist>
    </member>
    <member kind="function">
      <type>MQTTSNClientResult</type>
      <name>MQTTSN_CLIENT_Subscribe</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>ga66ef8f5af5c0ad16b14a2d24a3b7179d</anchor>
      <arglist>(MQTTSNClient *client, char const *topic, MQTTSNPacketQoS qos, MQTTSNOnTopicSubscribedByClient onTopicSubscribedByClient, MQTTSNOnPublishReceived onPublishReceivedCallback)</arglist>
    </member>
    <member kind="function">
      <type>MQTTSNClientResult</type>
      <name>MQTTSN_CLIENT_Unsubscribe</name>
      <anchorfile>group__mqttsn__client.html</anchorfile>
      <anchor>gab8d56ddcf4ac72e881bc124b3c6ea236</anchor>
      <arglist>(MQTTSNClient *client, char const *topic, MQTTSNOnTopicUnsubscribedByClient onTopicUnsubscribedByClient)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>MQTTSNClient</name>
    <filename>struct_m_q_t_t_s_n_client.html</filename>
    <member kind="variable">
      <type>char</type>
      <name>clientId</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a14d6c7cdd64e06d3d88530f97454ceef</anchor>
      <arglist>[MQTTSN_MAX_CLIENT_ID_LENGTH+1]</arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNClientState</type>
      <name>state</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>ae1da5289666e256ec66a071a3f18b27a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_IPV6</type>
      <name>gatewayAddress</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>ac8a1ad6ca95b9d8d6029099c2ef17441</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>gatewayPort</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a96a411a47fca23160e6497dda1c2d701</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>willTopicName</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a65fbed44b92dcb4a316d4b1a036560c7</anchor>
      <arglist>[MQTTSN_MAX_TOPIC_NAME_LENGTH]</arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>willMsg</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>ab9ca97d1a703a8917b7d6f2efe518e33</anchor>
      <arglist>[MQTTSN_MAX_MESSAGE_LENGTH]</arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TaskId</type>
      <name>pingTaskId</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>abe0e24877ffa6888a13c84900df72e58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TaskId</type>
      <name>timeoutTaskId</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a00ff5f9ad2edb5bae21015da6282c55f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TaskId</type>
      <name>timeoutPingTaskId</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>ae9ddb54be42497d0f245802f7183a2a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>expectedMessageType</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>adf99d7d635f63cad7181360d7c8f8374</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>keepAliveTimeMs</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a818473a8d6ee77c10d5b4eff20ddc8c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>gatewayTimeoutMs</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a94cb7d87bff15b6f4eb00965facd6ab2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>pingRespLost</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a66c08734aaa0dd3eb74b7437ae04479c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>lastPacketReceptionTime</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a85e598d2229dd673331f6b87f5078981</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>lastPacketSendTime</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a9c367090a78120811c94b4bd048baab9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>packetId</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a956a9b250a1c33994e89b5e7d9d6c9d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>maxQosRetransmissions</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a08ed8be988440e26c339ddeb2b328286</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNQosMsg</type>
      <name>publishQosMsg</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>ada74f66070599d22ceb3045125c1f562</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNQosMsg</type>
      <name>subscribeQosMsg</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a0ecd342dd76d1ac7082384409c4a7981</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNTopicDescriptor</type>
      <name>subscribeTopics</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a976e88bd7d9a289f98d7c09824e7b340</anchor>
      <arglist>[MQTTSN_CLIENT_MAX_TOPICS_TO_SUBSCRIBE]</arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNTopicDescriptor</type>
      <name>publishTopics</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a48ed781a5168cc0d4e0a59229b794bb0</anchor>
      <arglist>[MQTTSN_CLIENT_MAX_TOPICS_TO_PUBLISH]</arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNSessionFlags</type>
      <name>flags</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a652271c96cc6deb298ac3e2feed63837</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_UDP_SocketDescriptor</type>
      <name>udpSocket</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>afbffb24ede1087c477fd4cb660ddcda0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNClientEventHandlers</type>
      <name>eventHandlers</name>
      <anchorfile>struct_m_q_t_t_s_n_client.html</anchorfile>
      <anchor>a431347d6e7bb6dc7be9f10b3369a98c4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>MQTTSNClientEventHandlers</name>
    <filename>struct_m_q_t_t_s_n_client_event_handlers.html</filename>
    <member kind="variable">
      <type>MQTTSNOnClientConnected</type>
      <name>onConnected</name>
      <anchorfile>struct_m_q_t_t_s_n_client_event_handlers.html</anchorfile>
      <anchor>a0f0e1d1529f9e5b97183e4db2b8844e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNOnClientDisconnected</type>
      <name>onDisconnected</name>
      <anchorfile>struct_m_q_t_t_s_n_client_event_handlers.html</anchorfile>
      <anchor>a8892e991745b8c5134b7c883bc5b7773</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNOnTopicRegisteredByGateway</type>
      <name>onTopicRegisteredByGateway</name>
      <anchorfile>struct_m_q_t_t_s_n_client_event_handlers.html</anchorfile>
      <anchor>aff468f2ec14c0be97c76b73dabff1723</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>MQTTSNQosMsg</name>
    <filename>struct_m_q_t_t_s_n_qos_msg.html</filename>
    <member kind="variable">
      <type>MQTTSNPacketQoS</type>
      <name>qos</name>
      <anchorfile>struct_m_q_t_t_s_n_qos_msg.html</anchorfile>
      <anchor>abfad6a33de73842de45be7b8aeaff22d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>messageId</name>
      <anchorfile>struct_m_q_t_t_s_n_qos_msg.html</anchorfile>
      <anchor>a1060217058f8df75c0a59fe373f4ceb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>topicId</name>
      <anchorfile>struct_m_q_t_t_s_n_qos_msg.html</anchorfile>
      <anchor>a3ef41536e08e32e50556d55408e52030</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>lastMsg</name>
      <anchorfile>struct_m_q_t_t_s_n_qos_msg.html</anchorfile>
      <anchor>aed987fed8d4eea466d708f05915c2777</anchor>
      <arglist>[MQTTSN_MAX_MESSAGE_LENGTH]</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>lastMsgLen</name>
      <anchorfile>struct_m_q_t_t_s_n_qos_msg.html</anchorfile>
      <anchor>ae7645470f1f99e251091dd60e492cd2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>retransmissionCount</name>
      <anchorfile>struct_m_q_t_t_s_n_qos_msg.html</anchorfile>
      <anchor>afec9772a76a41eb1be342e647190adbb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>MQTTSNSessionFlags</name>
    <filename>struct_m_q_t_t_s_n_session_flags.html</filename>
    <member kind="variable">
      <type>unsigned int</type>
      <name>topicIdType</name>
      <anchorfile>struct_m_q_t_t_s_n_session_flags.html</anchorfile>
      <anchor>a1113b937ab38aeaabfe0b4720e2ac7f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>cleanSession</name>
      <anchorfile>struct_m_q_t_t_s_n_session_flags.html</anchorfile>
      <anchor>a1acd79ad0a1170cdcdd03cc7967c5c44</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>will</name>
      <anchorfile>struct_m_q_t_t_s_n_session_flags.html</anchorfile>
      <anchor>a6218ef7356b0b9611d870967b150e498</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>retain</name>
      <anchorfile>struct_m_q_t_t_s_n_session_flags.html</anchorfile>
      <anchor>ae756f24db45ef9eeaed3ca9782df44f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>QoS</name>
      <anchorfile>struct_m_q_t_t_s_n_session_flags.html</anchorfile>
      <anchor>a23453d19e3fd0a8f88d287f8683c6d1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>dup</name>
      <anchorfile>struct_m_q_t_t_s_n_session_flags.html</anchorfile>
      <anchor>a7c642ce9848681abb474f589834ac2d1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>MQTTSNTopicDescriptor</name>
    <filename>struct_m_q_t_t_s_n_topic_descriptor.html</filename>
    <member kind="variable">
      <type>uint16_t</type>
      <name>registerMessageId</name>
      <anchorfile>struct_m_q_t_t_s_n_topic_descriptor.html</anchorfile>
      <anchor>a93d213399c16517694f8fcea3a9b86a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNTopicId</type>
      <name>topicId</name>
      <anchorfile>struct_m_q_t_t_s_n_topic_descriptor.html</anchorfile>
      <anchor>ac1cbc55266bdeec12b0378c80e5c8b43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char</type>
      <name>topicName</name>
      <anchorfile>struct_m_q_t_t_s_n_topic_descriptor.html</anchorfile>
      <anchor>a165daff084f7eb054f7fa5387d810e3f</anchor>
      <arglist>[MQTTSN_MAX_TOPIC_NAME_LENGTH]</arglist>
    </member>
    <member kind="variable">
      <type>size_t</type>
      <name>topicNameLen</name>
      <anchorfile>struct_m_q_t_t_s_n_topic_descriptor.html</anchorfile>
      <anchor>ae2fae492bc9e86871704a7ed61dbc6c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNOnTopicRegisteredByClient</type>
      <name>onTopicRegisteredByClient</name>
      <anchorfile>struct_m_q_t_t_s_n_topic_descriptor.html</anchorfile>
      <anchor>a74776961e349fbf3013b820963a9b6b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNOnTopicSubscribedByClient</type>
      <name>onTopicSubscribedByClient</name>
      <anchorfile>struct_m_q_t_t_s_n_topic_descriptor.html</anchorfile>
      <anchor>a132e743f2abc4c39ecacf3e0932beab0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNOnTopicUnsubscribedByClient</type>
      <name>onTopicUnsubscribedByClient</name>
      <anchorfile>struct_m_q_t_t_s_n_topic_descriptor.html</anchorfile>
      <anchor>ac1db1e544d68c65e2b666561bb214c6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNOnPublishReceived</type>
      <name>onPublishReceived</name>
      <anchorfile>struct_m_q_t_t_s_n_topic_descriptor.html</anchorfile>
      <anchor>a9d41e3f0ae7de4d913af62c9f52c16ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MQTTSNOnPublishSent</type>
      <name>onPublishSent</name>
      <anchorfile>struct_m_q_t_t_s_n_topic_descriptor.html</anchorfile>
      <anchor>aa69955f68b7423419d413f8ce7a8b3b2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>mqttsn_client</name>
    <title>MQTT-SN Client</title>
    <filename>group__mqttsn__client.html</filename>
    <class kind="struct">MQTTSNClientEventHandlers</class>
    <class kind="struct">MQTTSNTopicDescriptor</class>
    <class kind="struct">MQTTSNSessionFlags</class>
    <class kind="struct">MQTTSNQosMsg</class>
    <class kind="struct">MQTTSNClient</class>
  </compound>
  <compound kind="page">
    <name>mqttsn_gateway_setup_hivemq_edge</name>
    <title>MQTT-SN Gateway setup using HiveMQ Edge</title>
    <filename>mqttsn_gateway_setup_hivemq_edge.html</filename>
  </compound>
  <compound kind="page">
    <name>mqttsn_gateway_setup_small_things</name>
    <title>MQTT-SN Gateway setup using MQTT For Small Things</title>
    <filename>mqttsn_gateway_setup_small_things.html</filename>
  </compound>
  <compound kind="page">
    <name>mqttsn_client_tutorial</name>
    <title>MQTT-SN Client tutorial</title>
    <filename>mqttsn_client_tutorial.html</filename>
    <docanchor file="mqttsn_client_tutorial.html" title="MQTT-SN Client API library">mqttsn_client_c_api</docanchor>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>MQTT-SN Client</title>
    <filename>index.html</filename>
    <docanchor file="index.html" title="MQTT-SN Client">mainpage</docanchor>
  </compound>
</tagfile>
