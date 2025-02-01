var mqttsn__client_8h =
[
    [ "MQTTSN_MAX_TOPIC_NAME_LENGTH", "group__mqttsn__client.html#gae61253812b29c9a2cd953fe3c5c50aa4", null ],
    [ "MQTTSN_MAX_MESSAGE_LENGTH", "group__mqttsn__client.html#ga0af3deef95f8c44278c2de078b5dbf3a", null ],
    [ "MQTTSN_MAX_CLIENT_ID_LENGTH", "group__mqttsn__client.html#gaad17603bc71b25a4d1d31923d14cbe55", null ],
    [ "MQTTSN_CLIENT_MAX_TOPICS_TO_SUBSCRIBE", "group__mqttsn__client.html#gab9014ab0174f26a9bfc2328332f6bc4e", null ],
    [ "MQTTSN_CLIENT_MAX_TOPICS_TO_PUBLISH", "group__mqttsn__client.html#ga1978094ab7ad81fa4a011a9a8665c8de", null ],
    [ "MQTTSN_CLIENT_MAX_PINGRESP_LOST", "group__mqttsn__client.html#ga2da72f6d309f08e58e576a21e6bf1e03", null ],
    [ "MQTTSNTopicId", "group__mqttsn__client.html#gaa5559fcdef77c6ad4f23615c48bae21e", null ],
    [ "MQTTSNOnClientConnected", "group__mqttsn__client.html#gaf294b9f0491c69cb04d73cdfff30a059", null ],
    [ "MQTTSNOnClientDisconnected", "group__mqttsn__client.html#gafb2fd1e8bee6651df18fdf2ae7eac5d1", null ],
    [ "MQTTSNOnTopicRegisteredByClient", "group__mqttsn__client.html#ga65939421635c5a171808ddf652fa3589", null ],
    [ "MQTTSNOnTopicRegisteredByGateway", "group__mqttsn__client.html#ga275ce5bb73e0da28b9da1904dd263498", null ],
    [ "MQTTSNOnTopicSubscribedByClient", "group__mqttsn__client.html#ga216869a4fda51d88bfa11731bfcde6ab", null ],
    [ "MQTTSNOnTopicUnsubscribedByClient", "group__mqttsn__client.html#ga9577fb3c7b093d7ef768e056ff6929a9", null ],
    [ "MQTTSNOnPublishReceived", "group__mqttsn__client.html#gae78e64768a2c0a84604fa31686956123", null ],
    [ "MQTTSNOnPublishSent", "group__mqttsn__client.html#ga23fa36af1420b942dc8fe4b6db6f7604", null ],
    [ "MQTTSNClientState", "group__mqttsn__client.html#gadf99316dabd39dcdaad846ad49f90492", [
      [ "MQTTSN_CLIENT_STATE_DISCONNECTED", "group__mqttsn__client.html#ggadf99316dabd39dcdaad846ad49f90492a7d6a06f8ba4b236a4f0def4763b66a48", null ],
      [ "MQTTSN_CLIENT_STATE_CONNECTING", "group__mqttsn__client.html#ggadf99316dabd39dcdaad846ad49f90492ae3c9f01f05eee7e2e4183dc428bf756b", null ],
      [ "MQTTSN_CLIENT_STATE_AWAITING_WILL_TOPIC_REQ", "group__mqttsn__client.html#ggadf99316dabd39dcdaad846ad49f90492ade9d1b379f036e1964c4446b49ac1982", null ],
      [ "MQTTSN_CLIENT_STATE_AWAITING_WILL_MSG_REQ", "group__mqttsn__client.html#ggadf99316dabd39dcdaad846ad49f90492a3972fc8d95f1e5b76cc863c972f054f7", null ],
      [ "MQTTSN_CLIENT_STATE_CONNECTED", "group__mqttsn__client.html#ggadf99316dabd39dcdaad846ad49f90492a1f17b52570387350f494e085e4cf5e81", null ],
      [ "MQTTSN_CLIENT_STATE_DISCONNECTING", "group__mqttsn__client.html#ggadf99316dabd39dcdaad846ad49f90492aa47031ce03cb2458d759e325170c94bb", null ]
    ] ],
    [ "MQTTSNClientResult", "group__mqttsn__client.html#gab3bcf9e91e317aef26511a8f7d5ed6ca", [
      [ "MQTTSN_CLIENT_RESULT_OK", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caad9ee374ac01dc8ab62db290cd34258ec", null ],
      [ "MQTTSN_CLIENT_RESULT_INVALID_INPUT_ARGUMENT", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caa54fa7aaf18049b223b813b219571bc4b", null ],
      [ "MQTTSN_CLIENT_RESULT_FAILED_TO_REGISTER_UDP_SOCKET", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caa6cf88cc5b8dcd72de23fbaf6f6915fd0", null ],
      [ "MQTTSN_CLIENT_RESULT_FAILED_TO_CREATE_TASK", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caae3c62c1b2d5c3da6d2fab6561060b4e4", null ],
      [ "MQTTSN_CLIENT_RESULT_FAILED_TO_SEND_PACKET", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caa81f94792c46247aab17d289174f56f44", null ],
      [ "MQTTSN_CLIENT_RESULT_FAILED_TO_SERIALIZE_PACKET", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caa763c0fb292f046d4fa2fae5fbcf850fa", null ],
      [ "MQTTSN_CLIENT_RESULT_CLIENT_NOT_CONNECTED", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caa099a6d8ebcd84710c533ad7e4b8420ac", null ],
      [ "MQTTSN_CLIENT_RESULT_CLIENT_ALREADY_CONNECTED", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caaab2f586f806487eff28a6cba8e707818", null ],
      [ "MQTTSN_CLIENT_RESULT_TOPIC_NOT_FOUND", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caafb3267c43ab2bed483a534bd923fd95a", null ],
      [ "MQTTSN_CLIENT_RESULT_PUBLISH_BUFFER_FULL", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caa6d6073688e17ed2a2236837f015a3490", null ],
      [ "MQTTSN_CLIENT_RESULT_SUBSCRIBE_BUFFER_FULL", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caaa6abf6925b04c5b8912e1c9e4076a919", null ],
      [ "MQTTSN_CLIENT_RESULT_TOPIC_TOO_LONG", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caa26864429081480a62fe60c22f44ba208", null ],
      [ "MQTTSN_CLIENT_RESULT_MESSAGE_TOO_LONG", "group__mqttsn__client.html#ggab3bcf9e91e317aef26511a8f7d5ed6caa5e70893e7f9d5f9d873fcaf00be3a8b3", null ]
    ] ],
    [ "MQTTSNPacketQoS", "group__mqttsn__client.html#ga8b373e8a50858d583b8533a10a3c8797", [
      [ "MQTTSN_QOS0", "group__mqttsn__client.html#gga8b373e8a50858d583b8533a10a3c8797a4dc6009b4ffd1b407c856f24b8912eb4", null ],
      [ "MQTTSN_QOS1", "group__mqttsn__client.html#gga8b373e8a50858d583b8533a10a3c8797a151a37fdd3ddc703863849e964a44a08", null ],
      [ "MQTTSN_QOS2", "group__mqttsn__client.html#gga8b373e8a50858d583b8533a10a3c8797a3751c8593369d4f6c357a16e99a57e67", null ]
    ] ],
    [ "MQTTSNClientDisconnectionReason", "group__mqttsn__client.html#ga062f5d134d4d0653f8db8c2dd7a7fda9", [
      [ "MQTTSN_CLIENT_DISCONNECTED_DUE_TO_OWN_REQUEST", "group__mqttsn__client.html#gga062f5d134d4d0653f8db8c2dd7a7fda9a0d908db66af0a1d02b8da59950426f51", null ],
      [ "MQTTSN_CLIENT_DISCONNECTED_BY_GATEWAY", "group__mqttsn__client.html#gga062f5d134d4d0653f8db8c2dd7a7fda9a5d44168c77498638958d7a5f8dfed57c", null ],
      [ "MQTTSN_CLIENT_DISCONNECTED_DUE_TO_TIMEOUT", "group__mqttsn__client.html#gga062f5d134d4d0653f8db8c2dd7a7fda9a13395db3f73ff7770a9df5f84666534b", null ]
    ] ],
    [ "MQTTSN_CLIENT_Init", "group__mqttsn__client.html#gaf67ea7745cd27c8ae9aef80ad63913cc", null ],
    [ "MQTTSN_CLIENT_Deinit", "group__mqttsn__client.html#ga192746f27b7d849298461d0972297453", null ],
    [ "MQTTSN_CLIENT_Connect", "group__mqttsn__client.html#ga5ea2b59897385bb2845087ae2472e132", null ],
    [ "MQTTSN_CLIENT_Disconnect", "group__mqttsn__client.html#gae23c07254ed7fa1f81db9460ade03ea6", null ],
    [ "MQTTSN_CLIENT_RegisterTopic", "group__mqttsn__client.html#ga76c610cdfd1a3c69a83b1e4d8be3946f", null ],
    [ "MQTTSN_CLIENT_GetTopicId", "group__mqttsn__client.html#gafc24c8d8618e8dbd8be9ce6ceda25903", null ],
    [ "MQTTSN_CLIENT_PublishMessage", "group__mqttsn__client.html#ga188d770e424ffd4f827184d2d0783923", null ],
    [ "MQTTSN_CLIENT_PublishMessageById", "group__mqttsn__client.html#ga5b0ecab2e1f4d0433773267fd8c21e70", null ],
    [ "MQTTSN_CLIENT_Subscribe", "group__mqttsn__client.html#ga66ef8f5af5c0ad16b14a2d24a3b7179d", null ],
    [ "MQTTSN_CLIENT_Unsubscribe", "group__mqttsn__client.html#gab8d56ddcf4ac72e881bc124b3c6ea236", null ]
];