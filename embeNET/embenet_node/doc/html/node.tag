<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.8">
  <compound kind="file">
    <name>embenet_node_porting_guide.md</name>
    <path></path>
    <filename>embenet__node__porting__guide_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>embenet_node_user_guide.md</name>
    <path></path>
    <filename>embenet__node__user__guide_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>readme.md</name>
    <path></path>
    <filename>readme_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>node.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet/</path>
    <filename>node_8h.html</filename>
    <includes id="node__defs_8h" name="node_defs.h" local="yes" import="no" module="no" objc="no">node_defs.h</includes>
    <includes id="node__event__handlers_8h" name="node_event_handlers.h" local="yes" import="no" module="no" objc="no">node_event_handlers.h</includes>
    <class kind="struct">EMBENET_NODE_JoinConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>EMBENET_TASKID_INVALID</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga5b631f029e6959c0b2e89874e65f82ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>EMBENET_TaskId</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gabee561bfb171826daed0855e73db97e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_NODE_TaskFunction</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga74f7c0f8821db8da79babb83f7fee2b5</anchor>
      <arglist>)(EMBENET_TaskId taskId, EMBENET_NODE_TimeSource timeSource, uint64_t t, void *context)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_NODE_TimeSource</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga8bde2931321b4a3f4f97ba7489e9aa24</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_TIME_SOURCE_LOCAL</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gga8bde2931321b4a3f4f97ba7489e9aa24ac1b9775010a4d0f8c27966de5f57706f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_TIME_SOURCE_NETWORK</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gga8bde2931321b4a3f4f97ba7489e9aa24a88b0a720a7d932951a719a977cc57104</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_Init</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga975f34f801e5248f0e2301049a1a141f</anchor>
      <arglist>(EMBENET_NODE_EventHandlers const *eventHandlers)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_NODE_Deinit</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gad39bafacc3f3647a1a5a9e94ff7b7fc2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_NODE_Proc</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gafdaac8d6a93d3b6315ea1e911aa38104</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_Join</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga8c331022dda56a869e5bd410d8bc2b08</anchor>
      <arglist>(EMBENET_NODE_JoinConfig const *config)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_QuickJoin</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gad5a16be15ac0f146fcb20189295df057</anchor>
      <arglist>(EMBENET_NODE_QuickJoinCredentials const *quickJoinCredentials)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_Leave</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gadfb98213538ebe092e6f5c3037936afc</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_RootStart</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga867e5654d034391347aa2ec45b009d70</anchor>
      <arglist>(void const *panData, size_t panDataSize)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EMBENET_NODE_JoinGroup</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gaccee999902a31da8fa227a730ddc8ce4</anchor>
      <arglist>(EMBENET_GroupId groupId)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EMBENET_NODE_LeaveGroup</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gab06fa5e3402729d3dc84c501ca84ab1b</anchor>
      <arglist>(EMBENET_GroupId groupId)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>EMBENET_NODE_GetGroupCount</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gaf207d2f21e6c3cf2d68441fc93a1c0a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_GroupId</type>
      <name>EMBENET_NODE_GetGroupByIndex</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga773cc3e9630e945175de25aac972de32</anchor>
      <arglist>(size_t index)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_TaskId</type>
      <name>EMBENET_NODE_TaskCreate</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga94fee61d254b860dcb83f1c3baa37456</anchor>
      <arglist>(EMBENET_NODE_TaskFunction taskFunction, void *userContext)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_TaskDestroy</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gad656682913db2de324cbe0b2a75754ba</anchor>
      <arglist>(EMBENET_TaskId taskId)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_TaskSchedule</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga5a3cc93daabc2f52738fb471dc4b4401</anchor>
      <arglist>(EMBENET_TaskId taskId, EMBENET_NODE_TimeSource timeSource, uint64_t t)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_TaskCancel</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gac9c922cd0b4b800112f835c3c6bb8029</anchor>
      <arglist>(EMBENET_TaskId taskId)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_EUI64</type>
      <name>EMBENET_NODE_GetUID</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga51e38fac378ac060d9a2cb8765cf2945</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_SetUID</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga5fc8821266870c22513ee58d6cdcc641</anchor>
      <arglist>(EMBENET_EUI64 uid)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_ForceParentChange</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga88e04e9748f025df45e9f08f991dcc52</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_GetBorderRouterAddress</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga42eed3ce7c24006439496e5cc757e239</anchor>
      <arglist>(EMBENET_IPV6 *ipv6)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Result</type>
      <name>EMBENET_NODE_GetParentAddress</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga5976ccb7b106ec199a3f3b88601d38a7</anchor>
      <arglist>(EMBENET_IPV6 *ipv6)</arglist>
    </member>
    <member kind="function">
      <type>uint64_t</type>
      <name>EMBENET_NODE_GetLocalTime</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gad6507236a07521ade7b30cfdaa418ff6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint64_t</type>
      <name>EMBENET_NODE_GetNetworkTime</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga9c008a76aae99e3ab34db907f01f8ccf</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint64_t</type>
      <name>EMBENET_NODE_GetNetworkAsn</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga23054b1bbe7017716b492c67b1624c8c</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>EMBENET_NODE_GetRandomValue</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gac888e7cfc2325ded0585ff924a11abec</anchor>
      <arglist>(uint32_t start, uint32_t stop)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Version</type>
      <name>EMBENET_NODE_GetVersion</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga394e1f33b68698c339ac1b7f60c8bc1f</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>node_defs.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet/</path>
    <filename>node__defs_8h.html</filename>
    <class kind="struct">EMBENET_K1</class>
    <class kind="struct">EMBENET_PSK</class>
    <class kind="struct">EMBENET_NODE_QuickJoinCredentials</class>
    <class kind="struct">EMBENET_Version</class>
    <member kind="typedef">
      <type>uint64_t</type>
      <name>EMBENET_NetworkPrefix</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>gaf5d7df5491e5d345861630bb902f045d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint16_t</type>
      <name>EMBENET_PANID</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ga62e6aadfe9a9ce0c48d06f100408b3d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint64_t</type>
      <name>EMBENET_RandomSeed</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>gad3a2a4422cdb588dc5c32433687128ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_Result</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>gad8c81ba87fcd9a8b5e878e46e8f4a8d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_OK</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7a8474b8c9b46f9fed0b66d623571f5fac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_UNSPECIFIED_ERROR</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7a69fe539128abf8384d886666493947f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_INVALID_ARGUMENT</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7ae447a6afac38fb23009e04aeda7fcb91</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_CALLED_OUTSIDE_A_TASK</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7a4ad23595f3300abca2799306aa92bbaa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_NOT_SYNCHRONIZED</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7a775f353122f1d5415bdacc2b98a17856</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_UNABLE_TO_SCHEDULE_IN_THE_PAST</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7afcf2a1c86c8027fea730c98a3c754d2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_INVALID_CREDENTIALS</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7af5e3d47e55a2c1e1f00c427b6f27b445</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_ROOT_CAPABILITIES_DISABLED</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7a2f784e819cf3abefd7d8bf168cafbf0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_WRONG_STATE</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7a598fe30228a534e48fcc32a811450584</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_UDP_MAX_DATA_SIZE_EXCEEDED</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7aa90521e00261f19aa1940b1548243e6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_UDP_PACKET_QUEUE_FULL</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7ad5afb1ff30d86282145fb79956efe184</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_UDP_FORWARDING_ERROR</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7a2e8d008ed4c95d9d0919f799ba8bd121</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_UDP_SOCKET_UNREGISTERED</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7a1f091aaed5ecb2fd87a51dce2fe63e4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_JOIN_RULE_ALREADY_EXISTS</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7a0ed770850d30b74093f54f63a8d065d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_JOIN_RULE_NOT_FOUND</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7a20ec5f87f37ac46d81d05626fe1edc88</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RESULT_JOIN_RULE_REGISTER_FULL</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ggad8c81ba87fcd9a8b5e878e46e8f4a8d7ac4ae256a1cda7dd81c0f781863cfea84</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_AddressingMode</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>ga35a4d6cb02cba5c965447465a6cf3939</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_ADDRESSING_MODE_SINGLE</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>gga35a4d6cb02cba5c965447465a6cf3939a5f8f9e298a16a949022086e5920a9ffe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_ADDRESSING_MODE_GROUP</name>
      <anchorfile>group__embenet__common.html</anchorfile>
      <anchor>gga35a4d6cb02cba5c965447465a6cf3939a88bc6949823047f9fe5d99eba2b31dbf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>node_diag.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet/</path>
    <filename>node__diag_8h.html</filename>
    <includes id="node__defs_8h" name="node_defs.h" local="yes" import="no" module="no" objc="no">node_defs.h</includes>
    <class kind="struct">EMBENET_NODE_DIAG_DutyCycleRawData</class>
    <class kind="struct">EMBENET_NODE_DIAG_QueueCounters</class>
    <class kind="struct">EMBENET_NODE_DIAG_NeighborInfo</class>
    <class kind="struct">EMBENET_NODE_DIAG_CellInfo</class>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_NODE_DIAG_NeighborRole</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aaceef6ed75fb33c037b997ec27626753</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_NEIGHBOR_ROLE_PARENT</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aaceef6ed75fb33c037b997ec27626753a57b2d397e3ee25d50263605899c9ab7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_NEIGHBOR_ROLE_CHILD</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aaceef6ed75fb33c037b997ec27626753affbaa992302b81b0679ae9ab5b6ca524</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_NEIGHBOR_ROLE_UNRELATED</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aaceef6ed75fb33c037b997ec27626753abd9ac3e7b6cc00f5354be5db9254fe0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_NODE_DIAG_CellRole</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a73c6d16db70e3d3e4718c73d485db071</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_CELL_ROLE_NONE</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a73c6d16db70e3d3e4718c73d485db071a98380fb2e065dacdc82fddd82c361c28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_CELL_ROLE_ADV</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a73c6d16db70e3d3e4718c73d485db071a28d99dc2691f1d6d8f825c645ed62713</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_CELL_ROLE_AUTO_DOWN</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a73c6d16db70e3d3e4718c73d485db071affb5a0f9c2b501b49d259db6b711d1ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_CELL_ROLE_AUTO_UP</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a73c6d16db70e3d3e4718c73d485db071a856ec457c9b6dd9deaee65af2ba5d501</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_CELL_ROLE_AUTO_UP_DOWN</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a73c6d16db70e3d3e4718c73d485db071a3d6bd6c138279c3437c1efea4fda53b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_CELL_ROLE_MANAGED</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a73c6d16db70e3d3e4718c73d485db071a1f2ff4e316fba265f5a1b250b0425e26</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_CELL_ROLE_APP</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a73c6d16db70e3d3e4718c73d485db071ae29413aa4f93e4b2296002ad8d25e9c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_NODE_DIAG_CellType</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aa8fb3cc75219e8eb68aab7fabef574b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_CELL_TYPE_NONE</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aa8fb3cc75219e8eb68aab7fabef574b8a23131206b15b09dfa699aaaa1cc8be7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_CELL_TYPE_TX</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aa8fb3cc75219e8eb68aab7fabef574b8a21469cb293e9ce58a6f34fe0d7186f0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_CELL_TYPE_RX</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aa8fb3cc75219e8eb68aab7fabef574b8ae795af0b043504e116b6b8c117bcd26a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_NODE_DIAG_CELL_TYPE_TXRX</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aa8fb3cc75219e8eb68aab7fabef574b8af712ed8e4a0a1463472ad6118fe279a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EMBENET_NODE_DIAG_IsRoot</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aff3f96c3960b9500468c1fdd42f0615c</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_EUI64</type>
      <name>EMBENET_NODE_DIAG_GetParentEUI64</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aaac3541e2f7aec643ab54ce27f6d5afa</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int8_t</type>
      <name>EMBENET_NODE_DIAG_GetParentRSSI</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a15180ce3e6c138229738a4b37fb7a434</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint16_t</type>
      <name>EMBENET_NODE_DIAG_GetParentPDR</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a601fdc47bf0932a5e3791fa798f40d1d</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint16_t</type>
      <name>EMBENET_NODE_DIAG_GetDAGRank</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>abb2637776d7b721a8dde6937dd72e371</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>EMBENET_NODE_DIAG_GetUpCells</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>ac90b8ef970565485b3d2f55783410655</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint16_t</type>
      <name>EMBENET_NODE_DIAG_GetUpPacketRate</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a7a97844bd1b8e56cfa54254acbc25d33</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>EMBENET_NODE_DIAG_GetDownCells</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a0cf9a3cde4974c9762218d36d8212b94</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint16_t</type>
      <name>EMBENET_NODE_DIAG_GetDownPacketRate</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>ac90bb9cc9c0fd7af49942fd26290f13b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint16_t</type>
      <name>EMBENET_NODE_DIAG_GetRadioReadyDutyCycle</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a6bd57cded194198461a1e15289edb421</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint16_t</type>
      <name>EMBENET_NODE_DIAG_GetRadioTxDutyCycle</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a1c64c6888f37d8057399d7f4f31caa2d</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>uint16_t</type>
      <name>EMBENET_NODE_DIAG_GetRadioRxDutyCycle</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>acaec6e728e4fff8dd0a1eb0b275d3ddc</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_NODE_DIAG_DutyCycleRawData</type>
      <name>EMBENET_NODE_DIAG_GetRadioDutyCycleRaw</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>aabf96a1cfe7830df75a8c88670fb64f4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_NODE_DIAG_QueueCounters</type>
      <name>EMBENET_NODE_DIAG_GetQueueThresholdAndOverflowCounters</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a9ac8bf57fb9a512e78fb81c3a1eb0355</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>EMBENET_NODE_DIAG_GetNeighborCount</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a2da9ee4e3d6a2dfd5051726670fe7927</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_NODE_DIAG_NeighborInfo</type>
      <name>EMBENET_NODE_DIAG_GetNeighborInfo</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a7231a048238c3dcff51e5ffd6f16f486</anchor>
      <arglist>(unsigned index)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>EMBENET_NODE_DIAG_GetCellsCount</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>af9f9464f94468f6df03ab406840ef92b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_NODE_DIAG_CellInfo</type>
      <name>EMBENET_NODE_DIAG_GetCellInfo</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>afff3a17dfe3caf0a43571774e7291c05</anchor>
      <arglist>(unsigned index)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>EMBENET_NODE_DIAG_GetSlotframeLength</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a93364caf64aa10ac71538ef2aef2566a</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>EMBENET_NODE_DIAG_GetSlotDurationUs</name>
      <anchorfile>node__diag_8h.html</anchorfile>
      <anchor>a032989a5d58c77a705e599c5c634e1a9</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>node_event_handlers.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet/</path>
    <filename>node__event__handlers_8h.html</filename>
    <includes id="node__defs_8h" name="node_defs.h" local="yes" import="no" module="no" objc="no">node_defs.h</includes>
    <class kind="struct">EMBENET_NODE_EventHandlers</class>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_NODE_OnJoined</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gac1eb8bf061692a0234023f8996f150e5</anchor>
      <arglist>)(EMBENET_PANID panId, EMBENET_NODE_QuickJoinCredentials const *quickJoinCredentials)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_NODE_OnLeft</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gaadc93c3f0f941be7c3570ee3f1f3cdf1</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_NODE_OnJoinAttempt</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>gab607c621fc5c493bce207ea39345afa8</anchor>
      <arglist>)(EMBENET_PANID panId, void const *panData, size_t panDataSize)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_NODE_OnQuickJoinCredentialsObsolete</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga3235cc0bd6ae8d6c98a471969c58b421</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_NODE_DataOnUnregisteredPort</name>
      <anchorfile>group__embenet__node__api.html</anchorfile>
      <anchor>ga1414905845f98c9df9bcebd581707d6b</anchor>
      <arglist>)(uint16_t port)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>node_trace.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet/</path>
    <filename>node__trace_8h.html</filename>
    <class kind="struct">EMBENET_TRACE_LinkLayerTelemetry</class>
    <class kind="struct">EMBENET_NODE_TraceHandlers</class>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_Started</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga301b2992102918c641b498a39ec89d42</anchor>
      <arglist>)(uint64_t eui)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_Synchronized</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga1323b3f4d5f52be77567d3dfa149735f</anchor>
      <arglist>)(uint16_t panid)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_Desynchronized</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gaa09db4318829e3ee980425618607b8b3</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_PacketNoAck</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga1f9d36bbdf122499c24b72d3d6efdc4f</anchor>
      <arglist>)(uint64_t linkLocalDestinationEui, uint64_t destinationEui, uint8_t attempt)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_ManagedPacketNoAck</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gaddf5995e6c154cfc5f0c15c5e3709ef7</anchor>
      <arglist>)(uint64_t linkLocalDestinationEui)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_PacketNotDelivered</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga6cde6ccdfbe80598581ba541bc00ee6c</anchor>
      <arglist>)(uint64_t linkLocalDestinationEui, uint64_t destinationEui)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_Joined</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga2712d06ff8ce93edbb1f49bdd913d454</anchor>
      <arglist>)(uint64_t parentEui)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_SyncCorrection</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gadf89a964aa30c0347c995df103d4a728</anchor>
      <arglist>)(int32_t us)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_ParentSelected</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga413649142c5a62d3428116b34c5a8f9b</anchor>
      <arglist>)(uint64_t parentEui)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_ParentLost</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gab62269e0c25c356f023dff5c271b247a</anchor>
      <arglist>)(uint64_t parentEui)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_NeighborAdded</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga93759ac70f0c4ccd0de4cc5dea08c001</anchor>
      <arglist>)(uint64_t neighborEui, int8_t rssi)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_NeighborRemoved</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gaabe0cc271ec8dcf0f0dc7ace801549f3</anchor>
      <arglist>)(uint64_t neighborEui)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_RankUpdate</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga44cd7faebd061dd68dabb32aa0cc37be</anchor>
      <arglist>)(uint16_t rank)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_QueueLength</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga70c116a633f19465f10863552cedf115</anchor>
      <arglist>)(size_t length)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_RadioActivity</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga5e41749a607f6da1308a2cbca6a98774</anchor>
      <arglist>)(bool active)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_SlotStart</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga99559965f356c1b2f1e57eb5c5017198</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_LinkLayerEvent</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga4e37e99595dc3ff8b4ccebfc5eb7dbbc</anchor>
      <arglist>)(EMBENET_TRACE_LinkLayerTelemetry const *linkLayerTelemetry)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_OnFreeSlots</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga867d007fdd18617a03a1f99ba7a693e9</anchor>
      <arglist>)(uint64_t asn, uint64_t startNwkTime, uint32_t durationUs)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_OnSlotStartEnd</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga3c0e141710a4f0f0e483f4b01176d5c5</anchor>
      <arglist>)(bool enters)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_OnMacRoutine</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga75d734cae0f05362742d092bb569e85b</anchor>
      <arglist>)(bool enters)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_OnRadioApiUsed</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga6a94960cfeb122fe3be1a4392e77b436</anchor>
      <arglist>)(bool enters)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TRACE_OnRadioIsr</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga54169a40150052f801356c3a7f22b3ad</anchor>
      <arglist>)(bool enters)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_TRACE_CellEvent</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga41bf8cb2a9acb4d6cc73b20f5c877294</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_CELL_EVENT_TX</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga41bf8cb2a9acb4d6cc73b20f5c877294a60c18eb346a2269406d834c78ab97c7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_CELL_EVENT_RX</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga41bf8cb2a9acb4d6cc73b20f5c877294a41c016ce474fdcf211974d1501497a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_TRACE_CellRole</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga09831802fb9aa2b3d4b62a93f45fa9c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_CELL_ROLE_ADV</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga09831802fb9aa2b3d4b62a93f45fa9c7aa3b4a3c85b857288a421384b0a9bddc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_CELL_ROLE_AUTO_UP</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga09831802fb9aa2b3d4b62a93f45fa9c7a7de76da8b0c7b5cd7392d08a30c672f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_CELL_ROLE_AUTO_DOWN</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga09831802fb9aa2b3d4b62a93f45fa9c7ad8da838cf317b35b27208b7be6813fb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_CELL_ROLE_AUTO_UPDOWN</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga09831802fb9aa2b3d4b62a93f45fa9c7a3fc84d271ee79896ae3aba40cf5e63ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_CELL_ROLE_AUTO_MANAGED</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga09831802fb9aa2b3d4b62a93f45fa9c7af9255ad062387e19fd17216b96c881cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_TRACE_CellType</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga36def9113344e8e006dbb8b3d851b4ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_CELL_TYPE_TX</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga36def9113344e8e006dbb8b3d851b4eda484999aeea7ce4a542f06eee097ab2ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_CELL_TYPE_RX</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga36def9113344e8e006dbb8b3d851b4edab6a90c32a1514c585fc8524160bdc0a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_CELL_TYPE_TXRX</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga36def9113344e8e006dbb8b3d851b4eda7f451c527e7a3f173d871df33b16a651</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_TRACE_FrameType</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga1480264b70901178c517122c496604cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_FRAME_TYPE_BEACON</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga1480264b70901178c517122c496604cca63b37abc958c9956f434ae9d24fe7d26</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_FRAME_TYPE_DATA</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga1480264b70901178c517122c496604ccad7f6770dda6bf50614bfb3cf313a6913</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_TRACE_FRAME_TYPE_ACK</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>gga1480264b70901178c517122c496604ccaaf684fb7d635ecb1e00abeba9f0f7d93</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_NODE_SetTraceHandlers</name>
      <anchorfile>group__embenet__node__port__api___t_r_a_c_e.html</anchorfile>
      <anchor>ga3ad916f5f75967ce1c00b597d364a6f4</anchor>
      <arglist>(EMBENET_NODE_TraceHandlers const *traceHandlers)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>aes128.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet_port/</path>
    <filename>aes128_8h.html</filename>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_AES128_Init</name>
      <anchorfile>group__embenet__node__port__aes.html</anchorfile>
      <anchor>gab5a201f2eae3c6f8675cc244c602b480</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_AES128_Deinit</name>
      <anchorfile>group__embenet__node__port__aes.html</anchorfile>
      <anchor>ga054c1649043f65e01f158e2e2d2a82fd</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_AES128_SetKey</name>
      <anchorfile>group__embenet__node__port__aes.html</anchorfile>
      <anchor>ga88434457863ddd084b191e17ca6e5d5f</anchor>
      <arglist>(uint8_t const key[16U])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_AES128_Encrypt</name>
      <anchorfile>group__embenet__node__port__aes.html</anchorfile>
      <anchor>gadba9c771dcf92f5c31a3831b5f150e9b</anchor>
      <arglist>(uint8_t data[16U])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_AES128_Decrypt</name>
      <anchorfile>group__embenet__node__port__aes.html</anchorfile>
      <anchor>gae4d4618578ed4ff5ea9c911d8735483d</anchor>
      <arglist>(uint8_t data[16U])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>allocator.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet_port/</path>
    <filename>allocator_8h.html</filename>
    <member kind="function">
      <type>void *</type>
      <name>EMBENET_ALLOCATOR_Alloc</name>
      <anchorfile>group__embenet__node__port__alloc.html</anchorfile>
      <anchor>ga0a647de25c936040980c736ccb0bef27</anchor>
      <arglist>(size_t size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_ALLOCATOR_Free</name>
      <anchorfile>group__embenet__node__port__alloc.html</anchorfile>
      <anchor>ga8be09f918b59a69c41782ffa737b0a5f</anchor>
      <arglist>(void *pool)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>border_router_communication.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet_port/</path>
    <filename>border__router__communication_8h.html</filename>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_BRT_Init</name>
      <anchorfile>group__embenet__node__port__brt.html</anchorfile>
      <anchor>ga4128e7cdc896f56560a08830434ba069</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_BRT_Deinit</name>
      <anchorfile>group__embenet__node__port__brt.html</anchorfile>
      <anchor>ga66c3b9ffd2481a91bc3d953dbc0217e6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_BRT_Send</name>
      <anchorfile>group__embenet__node__port__brt.html</anchorfile>
      <anchor>gabede031891531e74655badbd59ecc97b</anchor>
      <arglist>(void const *packet, size_t packetLength)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>EMBENET_BRT_Receive</name>
      <anchorfile>group__embenet__node__port__brt.html</anchorfile>
      <anchor>ga78bda8ddfe3ad251b2f72616384f6f23</anchor>
      <arglist>(void *packetBuffer, size_t packetBufferSize)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_BRT_SendRaw</name>
      <anchorfile>group__embenet__node__port__brt.html</anchorfile>
      <anchor>ga2c231e0740e07133a3c67b7b92db48d0</anchor>
      <arglist>(void const *data, size_t dataLength)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>EMBENET_BRT_ReceiveRaw</name>
      <anchorfile>group__embenet__node__port__brt.html</anchorfile>
      <anchor>gadd521b6ce0f21ae8b1c53d67980f8c73</anchor>
      <arglist>(void *data, size_t dataBufferSize)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_BRT_Reset</name>
      <anchorfile>group__embenet__node__port__brt.html</anchorfile>
      <anchor>ga709e7eef123b29b8f40450faa8542fd3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>EMBENET_BRT_IsBusy</name>
      <anchorfile>group__embenet__node__port__brt.html</anchorfile>
      <anchor>gae0af29473432fd02c22a11c333742f13</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>capabilities.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet_port/</path>
    <filename>capabilities_8h.html</filename>
    <includes id="timer_8h" name="timer.h" local="yes" import="no" module="no" objc="no">embenet_port/timer.h</includes>
    <member kind="typedef">
      <type>struct EMBENET_Config</type>
      <name>EMBENET_Config</name>
      <anchorfile>group__embenet__node__port__capabilities.html</anchorfile>
      <anchor>ga1d0ecb4f8ccc968104572a4810632492</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>EMBENET_Config const *</type>
      <name>EMBENET_CAPABILITIES_Init</name>
      <anchorfile>group__embenet__node__port__capabilities.html</anchorfile>
      <anchor>ga7a68c2b5d09f52598edb32fa8213618b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_Config const  *const</type>
      <name>embenetNodeConfigTemplate_863_870Mhz_250nodes</name>
      <anchorfile>group__embenet__node__port__capabilities.html</anchorfile>
      <anchor>gacc94fabe93d99d7b0a49bd7b8e9e8232</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_Config const  *const</type>
      <name>embenetNodeConfigTemplate_863_870Mhz_10nodes_demo</name>
      <anchorfile>group__embenet__node__port__capabilities.html</anchorfile>
      <anchor>ga7063b3b4cd93d3abad83f6b2a268098b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_Config const  *const</type>
      <name>embenetNodeConfigTemplate_2400_2480Mhz_BLE_PHY_1000nodes</name>
      <anchorfile>group__embenet__node__port__capabilities.html</anchorfile>
      <anchor>gaba4d761ba8d01389ccbf4bc76c7dbbd0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_Config const  *const</type>
      <name>embenetNodeConfigTemplate_2400_2480Mhz_BLE_PHY_10nodes_demo</name>
      <anchorfile>group__embenet__node__port__capabilities.html</anchorfile>
      <anchor>gabb5e8c1bf33fb9a99cec51e90573c9d5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>critical_section.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet_port/</path>
    <filename>critical__section_8h.html</filename>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_CRITICAL_SECTION_Enter</name>
      <anchorfile>group__embenet__node__port__critical__section.html</anchorfile>
      <anchor>ga5cc1b11c26d777129eacfce8125d9873</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_CRITICAL_SECTION_Exit</name>
      <anchorfile>group__embenet__node__port__critical__section.html</anchorfile>
      <anchor>ga23ad27811894e2c8791c2ec155666a87</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>eui64.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet_port/</path>
    <filename>eui64_8h.html</filename>
    <member kind="function">
      <type>uint64_t</type>
      <name>EMBENET_EUI64_Get</name>
      <anchorfile>group__embenet__node__port__eui64.html</anchorfile>
      <anchor>gaa4e1d0e486874ae98f21fb9ebef1e458</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>radio.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet_port/</path>
    <filename>radio_8h.html</filename>
    <includes id="timer_8h" name="timer.h" local="yes" import="no" module="no" objc="no">embenet_port/timer.h</includes>
    <class kind="struct">EMBENET_RADIO_Capabilities</class>
    <class kind="struct">EMBENET_RADIO_RxInfo</class>
    <member kind="typedef">
      <type>int8_t</type>
      <name>EMBENET_RADIO_SetParamType</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga1a00ec597d3dd760f3dad6df3e0c7797</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int8_t</type>
      <name>EMBENET_RADIO_GetParamType</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga427749591b780b0b6aef7135553d5802</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint8_t</type>
      <name>EMBENET_RADIO_Channel</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga9f2b0ffa18cf9eb6def098cf126432c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int8_t</type>
      <name>EMBENET_RADIO_Power</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga435da8be88fe2fe41ca740445285ed2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_RADIO_CaptureCbt</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga8abd92d7bf1929962ab922b492787154</anchor>
      <arglist>)(void *context, EMBENET_TimeUs timestamp)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_RADIO_Status</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>gace5c2d31014ef65c14e853b03a519819</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_STATUS_SUCCESS</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggace5c2d31014ef65c14e853b03a519819a0310037f45946a91c4e31ed5d3a1e37d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_STATUS_GENERAL_ERROR</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggace5c2d31014ef65c14e853b03a519819a3732750e8f3cf639309044b49a153d48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_STATUS_COMMUNICATION_ERROR</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggace5c2d31014ef65c14e853b03a519819ad40c06bc77bc6130656ef02ccd6469f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_STATUS_WRONG_STATE</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggace5c2d31014ef65c14e853b03a519819a180ecb53d776f6399f3d71d52aafbc6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_STATUS_CHANNEL_BUSY</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggace5c2d31014ef65c14e853b03a519819abb051fb70cb9a230686b00f495da5063</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_STATUS_PARAMETER_NOT_IMPLEMENTED</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggace5c2d31014ef65c14e853b03a519819a0945798efdfba16e3aadf1d70ee6f699</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_STATUS_PARAMETER_ARGS_WRONG_NUMBER</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggace5c2d31014ef65c14e853b03a519819af4b0ff6daae96c0ad5fe8be8dc0e10a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_STATUS_PARAMETER_ARG1_OUT_OF_BOUNDS</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggace5c2d31014ef65c14e853b03a519819adb030a48ac5b402bf097695f13c5ff13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_STATUS_PARAMETER_ARG2_OUT_OF_BOUNDS</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggace5c2d31014ef65c14e853b03a519819a62603c112bc8cf5067617207cacbc51a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_STATUS_PARAMETER_ARG3_OUT_OF_BOUNDS</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggace5c2d31014ef65c14e853b03a519819ae42dde90d6d2c4f6e1c12ee46cf513e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_STATUS_PARAMETER_ARGS_OUT_OF_BOUNDS</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggace5c2d31014ef65c14e853b03a519819aac4937ed218cf32fa886a7ec7df4462f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_MAX_PSDU_LENGTH</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>gga06fc87d81c62e9abb8790b6e5713c55ba11f8e40d92b9753d41613db6e4d05caa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_MIN_PSDU_LENGTH</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>gga06fc87d81c62e9abb8790b6e5713c55ba78680125c8c064d8b47716e13fbe3559</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EMBENET_RADIO_ContinuousTxMode</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>gac8eed12eb63948159966b7f9a1a9b143</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_CONTINUOUS_TX_MODE_PN9</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggac8eed12eb63948159966b7f9a1a9b143afeef8e929a88ea646533f331ed136242</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EMBENET_RADIO_CONTINUOUS_TX_MODE_CARRIER</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ggac8eed12eb63948159966b7f9a1a9b143a66b2ba47622532218a1d5aa5690c4882</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>EMBENET_RADIO_Status</type>
      <name>EMBENET_RADIO_Init</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga3ad110087efd97f7496481083c52c4fe</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_RADIO_SetCallbacks</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga0995c0c68fa1d9a97d7f2db6d2c20fb0</anchor>
      <arglist>(EMBENET_RADIO_CaptureCbt onStartFrame, EMBENET_RADIO_CaptureCbt onEndFrame, void *cbtContext)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_RADIO_Deinit</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga0ab3dbaf1a6ead9e4f980ad2e932d2b8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_RADIO_Status</type>
      <name>EMBENET_RADIO_Idle</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>gaec3bed2d500631eb73c70a4987ab350a</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_RADIO_Status</type>
      <name>EMBENET_RADIO_TxEnable</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga84fea4f523b6f544bc74ca8c0b24f816</anchor>
      <arglist>(EMBENET_RADIO_Channel channel, EMBENET_RADIO_Power txp, uint8_t const *psdu, size_t psduLen)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_RADIO_Status</type>
      <name>EMBENET_RADIO_TxNow</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga698e7a92a3436c63f7a76a07e938a3e4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_RADIO_Status</type>
      <name>EMBENET_RADIO_RxEnable</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga1d40bfba7353200b9511b36ce509f25c</anchor>
      <arglist>(EMBENET_RADIO_Channel channel)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_RADIO_Status</type>
      <name>EMBENET_RADIO_RxNow</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga5d030cee7dcc0b831f920f4037f4ad30</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_RADIO_RxInfo</type>
      <name>EMBENET_RADIO_GetReceivedFrame</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga1125a5ed1705d48c365e4cdf09f67fc7</anchor>
      <arglist>(uint8_t *buffer, size_t bufferLength)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_RADIO_Capabilities const *</type>
      <name>EMBENET_RADIO_GetCapabilities</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga01fffc981074f60862d00b8a8b5cae62</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_RADIO_Status</type>
      <name>EMBENET_RADIO_StartContinuousTx</name>
      <anchorfile>group__embenet__node__port__radio.html</anchorfile>
      <anchor>ga7a58dfb9f0ea9c25298e4cbb0852e2db</anchor>
      <arglist>(EMBENET_RADIO_ContinuousTxMode mode, EMBENET_RADIO_Channel channel, EMBENET_RADIO_Power txp)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>random.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet_port/</path>
    <filename>random_8h.html</filename>
    <member kind="function">
      <type>uint32_t</type>
      <name>EMBENET_RANDOM_Get</name>
      <anchorfile>group__embenet__node__port__random.html</anchorfile>
      <anchor>ga983d1dddfdf03434d5fa7ec82c726455</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>timer.h</name>
    <path>/home/runner-3/runner/_work/embenet_node/embenet_node/include/embenet_port/</path>
    <filename>timer_8h.html</filename>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>EMBENET_TimeUs</name>
      <anchorfile>group__embenet__node__port__timer.html</anchorfile>
      <anchor>ga1e9b3d5520c2d09c6112740b34e29fad</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int64_t</type>
      <name>EMBENET_TimeDifferenceUs</name>
      <anchorfile>group__embenet__node__port__timer.html</anchorfile>
      <anchor>ga66a6b54a0d5943e65ddf328e00ebba90</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>EMBENET_TIMER_CompareCallback</name>
      <anchorfile>group__embenet__node__port__timer.html</anchorfile>
      <anchor>gae7f58baded80530a173ad967238fe29e</anchor>
      <arglist>)(void *context)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_TIMER_Init</name>
      <anchorfile>group__embenet__node__port__timer.html</anchorfile>
      <anchor>ga6c12e10079466afac0edcfc9599261a7</anchor>
      <arglist>(EMBENET_TIMER_CompareCallback compareCallback, void *context)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_TIMER_Deinit</name>
      <anchorfile>group__embenet__node__port__timer.html</anchorfile>
      <anchor>ga53ed154aa19710c006113d5880ddf6a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>EMBENET_TIMER_SetCompare</name>
      <anchorfile>group__embenet__node__port__timer.html</anchorfile>
      <anchor>gabd04d327e188a6a0472412c281ff12e2</anchor>
      <arglist>(EMBENET_TimeUs compareValue)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_TimeUs</type>
      <name>EMBENET_TIMER_ReadCounter</name>
      <anchorfile>group__embenet__node__port__timer.html</anchorfile>
      <anchor>gaee69b8882dcc6db7cca28add3801df2f</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>EMBENET_TimeUs</type>
      <name>EMBENET_TIMER_GetMaxCompareDuration</name>
      <anchorfile>group__embenet__node__port__timer.html</anchorfile>
      <anchor>ga0d442abdf50ff9b3b34e2164c6e16c0b</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_K1</name>
    <filename>struct_e_m_b_e_n_e_t___k1.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>val</name>
      <anchorfile>struct_e_m_b_e_n_e_t___k1.html</anchorfile>
      <anchor>a89840db9828c6846526c1b821f22ecdf</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_NODE_DIAG_CellInfo</name>
    <filename>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___cell_info.html</filename>
    <member kind="variable">
      <type>EMBENET_NODE_DIAG_CellRole</type>
      <name>role</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___cell_info.html</anchorfile>
      <anchor>a9abb03ddfb4f4c7a1c726aeea839dd2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_NODE_DIAG_CellType</type>
      <name>type</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___cell_info.html</anchorfile>
      <anchor>a93498cfafbd3ac5b80fbbb7ab2bd681d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>pdr</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___cell_info.html</anchorfile>
      <anchor>a6e4171ce51b11dcb876fe8dc9150875f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>slotOffset</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___cell_info.html</anchorfile>
      <anchor>a8637dd70048b2f91699446652b5d625c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>channelOffset</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___cell_info.html</anchorfile>
      <anchor>ab05da4f66086d4a53c79731056bbde2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>companionEui</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___cell_info.html</anchorfile>
      <anchor>af5349014d18055917ffd530909112e73</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_NODE_DIAG_DutyCycleRawData</name>
    <filename>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___duty_cycle_raw_data.html</filename>
    <member kind="variable">
      <type>uint64_t</type>
      <name>timeOverall</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___duty_cycle_raw_data.html</anchorfile>
      <anchor>af5ef119dea040dc5b989ec3a0fa3bcd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>timeTx</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___duty_cycle_raw_data.html</anchorfile>
      <anchor>a2848af807eb20d24a8b77e23f1890578</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>timeRx</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___duty_cycle_raw_data.html</anchorfile>
      <anchor>a82b6564e2f796463a301f011cd37217a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>timeActive</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___duty_cycle_raw_data.html</anchorfile>
      <anchor>ad154ea38bdb27d3e25b3b78afee47cb9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_NODE_DIAG_NeighborInfo</name>
    <filename>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___neighbor_info.html</filename>
    <member kind="variable">
      <type>uint64_t</type>
      <name>eui</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___neighbor_info.html</anchorfile>
      <anchor>aaa0f450fd6200c86775d82a15b867ffd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int8_t</type>
      <name>rssi</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___neighbor_info.html</anchorfile>
      <anchor>a42bcd7c0b3a0b43e34e7caed25b1afad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_NODE_DIAG_NeighborRole</type>
      <name>role</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___neighbor_info.html</anchorfile>
      <anchor>a116b03a544de5bc126b46ee969dec2ff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_NODE_DIAG_QueueCounters</name>
    <filename>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___queue_counters.html</filename>
    <member kind="variable">
      <type>unsigned</type>
      <name>alert</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___queue_counters.html</anchorfile>
      <anchor>ac6670f2877a6431196aa20d60d5f63c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>overflow</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___d_i_a_g___queue_counters.html</anchorfile>
      <anchor>a1304ecc5d46c1414b9aa3a10a9ac48b0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_NODE_EventHandlers</name>
    <filename>struct_e_m_b_e_n_e_t___n_o_d_e___event_handlers.html</filename>
    <member kind="variable">
      <type>EMBENET_NODE_OnJoined</type>
      <name>onJoined</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___event_handlers.html</anchorfile>
      <anchor>a25e511aebb58366916c11c60969dc930</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_NODE_OnLeft</type>
      <name>onLeft</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___event_handlers.html</anchorfile>
      <anchor>aab1e214bf62e6c6854e52d406f14387b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_NODE_OnJoinAttempt</type>
      <name>onJoinAttempt</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___event_handlers.html</anchorfile>
      <anchor>abc2df229beeb5976c7ce4b48d3995d9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_NODE_OnQuickJoinCredentialsObsolete</type>
      <name>onQuickJoinCredentialsObsolete</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___event_handlers.html</anchorfile>
      <anchor>aac20d92f9ce5090a423cd380202735ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_NODE_DataOnUnregisteredPort</type>
      <name>onDataOnUnregisteredPort</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___event_handlers.html</anchorfile>
      <anchor>a0694964bc576c5a77968f20d47a76bae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_NODE_JoinConfig</name>
    <filename>struct_e_m_b_e_n_e_t___n_o_d_e___join_config.html</filename>
    <member kind="variable">
      <type>EMBENET_K1</type>
      <name>k1</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___join_config.html</anchorfile>
      <anchor>a4aa19b7071553c20719022e9a97ac9f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_PSK</type>
      <name>psk</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___join_config.html</anchorfile>
      <anchor>af234571c20e084ff22d85e76a8073cd8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_NODE_QuickJoinCredentials</name>
    <filename>struct_e_m_b_e_n_e_t___n_o_d_e___quick_join_credentials.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>reserved</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___quick_join_credentials.html</anchorfile>
      <anchor>a76f6d46682f98c1b63df748cebe38738</anchor>
      <arglist>[52]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_NODE_TraceHandlers</name>
    <filename>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</filename>
    <member kind="variable">
      <type>EMBENET_TRACE_Started</type>
      <name>onStarted</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>ac948fce580b895a7072da1e9da04068f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_Synchronized</type>
      <name>onSynchronized</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>af095e0abad058e95fdbe6c0cf4453b34</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_Desynchronized</type>
      <name>onDesynchronized</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>aed7a3bc054b1debfb4b294bbc9be24d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_PacketNoAck</type>
      <name>onPacketNoAck</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>ad0a8276ee6196533406c327056d0696d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_ManagedPacketNoAck</type>
      <name>onManagedPacketNoAck</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>a8de864b8dfcbbd82a9e2131080a563ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_PacketNotDelivered</type>
      <name>onPacketNotDelivered</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>a0a779e91344eef197778466b2434d273</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_Joined</type>
      <name>onJoined</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>a22e7a77589fc62dee977ed2f8f8b161c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_SyncCorrection</type>
      <name>onSyncCorrection</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>aad907cdd4ca96a992dad6b9d4f4ccc00</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_ParentSelected</type>
      <name>onParentSelected</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>ae75e9a3c060d6e7843c527f0f6e08a24</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_ParentLost</type>
      <name>onParentLost</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>a36349e5ef0e91ee824f194a8925c6612</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_NeighborAdded</type>
      <name>onNeighborAdded</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>a00bed07a0fdbcbfb6629348991795402</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_NeighborRemoved</type>
      <name>onNeighborRemoved</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>ab7d9aa051ac20f52529da49b4d052ef0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_RankUpdate</type>
      <name>onRankUpdate</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>a92ff871ff331c2be108696a936e973f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_QueueLength</type>
      <name>onQueueLength</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>aa2ce28e50f3648796d2005447a0aea77</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_LinkLayerEvent</type>
      <name>onLinkLayerEvent</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>ab81630ae9f11a6ee3d9004d71b98cfe6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_OnFreeSlots</type>
      <name>onFreeSlots</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>a121fb4bcb22bd8a4c96e07130f723385</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_OnSlotStartEnd</type>
      <name>onSlotStartEnd</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>a9374037bc43851bff309d1be69db85d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_OnMacRoutine</type>
      <name>onMacRoutine</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>a15a6eb9f85b6c4c3693d9a4660f0a892</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_OnRadioApiUsed</type>
      <name>onRadioApiUsed</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>ac70d999e0401c4f58eac4d8118d90503</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_OnRadioIsr</type>
      <name>onRadioIsr</name>
      <anchorfile>struct_e_m_b_e_n_e_t___n_o_d_e___trace_handlers.html</anchorfile>
      <anchor>afeb21c8f070460e475f43bc97921cad8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_PSK</name>
    <filename>struct_e_m_b_e_n_e_t___p_s_k.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>val</name>
      <anchorfile>struct_e_m_b_e_n_e_t___p_s_k.html</anchorfile>
      <anchor>aa2be0a16d8d6125b221ce9d8c821bbe0</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_RADIO_Capabilities</name>
    <filename>struct_e_m_b_e_n_e_t___r_a_d_i_o___capabilities.html</filename>
    <member kind="variable">
      <type>EMBENET_TimeUs</type>
      <name>idleToTxReady</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___capabilities.html</anchorfile>
      <anchor>a304bd21463dad0c028aa7e29f23b1a1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TimeUs</type>
      <name>idleToRxReady</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___capabilities.html</anchorfile>
      <anchor>a229f80097a14e162994d46e5b37a2a4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TimeUs</type>
      <name>activeToTxReady</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___capabilities.html</anchorfile>
      <anchor>a1cdd5a9e6d242fb3add396d122792ad0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TimeUs</type>
      <name>activeToRxReady</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___capabilities.html</anchorfile>
      <anchor>a043524afeb1f3594798c760f76fa200e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TimeUs</type>
      <name>txDelay</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___capabilities.html</anchorfile>
      <anchor>a68afc07a997a334a660e3ae9057cc376</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TimeUs</type>
      <name>rxDelay</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___capabilities.html</anchorfile>
      <anchor>a59de991cc160c3f0acdd98f113282f4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TimeUs</type>
      <name>txRxStartDelay</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___capabilities.html</anchorfile>
      <anchor>a5d67c9cabb8e314e9074d40cd44d414b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_RADIO_Power</type>
      <name>sensitivity</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___capabilities.html</anchorfile>
      <anchor>a1bb5351a8cdcce3951f5da1ecc63e5c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_RADIO_Power</type>
      <name>maxOutputPower</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___capabilities.html</anchorfile>
      <anchor>a3dcf691d3a251c2a09fa9420f59cde55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_RADIO_Power</type>
      <name>minOutputPower</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___capabilities.html</anchorfile>
      <anchor>a48dc4fe4c61279f6e0f3d4f5f7eb203a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_RADIO_RxInfo</name>
    <filename>struct_e_m_b_e_n_e_t___r_a_d_i_o___rx_info.html</filename>
    <member kind="variable">
      <type>EMBENET_RADIO_Power</type>
      <name>rssi</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___rx_info.html</anchorfile>
      <anchor>aff6db772ac1cf333002600be560aeaa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>lqi</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___rx_info.html</anchorfile>
      <anchor>a1c278902fc9ca3255ca62e38a1357d5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>crcValid</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___rx_info.html</anchorfile>
      <anchor>a8e73571e4e4aa37b2f51813877ad8414</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>size_t</type>
      <name>mpduLength</name>
      <anchorfile>struct_e_m_b_e_n_e_t___r_a_d_i_o___rx_info.html</anchorfile>
      <anchor>ac858c8e5b98213488450e1e778ab9527</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_TRACE_LinkLayerTelemetry</name>
    <filename>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</filename>
    <member kind="variable">
      <type>EMBENET_TRACE_CellEvent</type>
      <name>cellEvent</name>
      <anchorfile>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</anchorfile>
      <anchor>a10be45de59ee703b7fb3b1b04bbbedb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_CellRole</type>
      <name>cellRole</name>
      <anchorfile>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</anchorfile>
      <anchor>a9e7c190bba74ea9b4f61b22ddd28de5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>EMBENET_TRACE_FrameType</type>
      <name>frameType</name>
      <anchorfile>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</anchorfile>
      <anchor>a7f032f6cb2b01d68225cdcf2b1cef9ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>channelOffset</name>
      <anchorfile>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</anchorfile>
      <anchor>a006823e0dc047f2d78d3949dcc9b516c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>slotOffset</name>
      <anchorfile>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</anchorfile>
      <anchor>a602029e81441d77c58cea35a1b17262d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int8_t</type>
      <name>rssiOrTxPower</name>
      <anchorfile>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</anchorfile>
      <anchor>a2fcbe5ce674a8fdd4f22ffa6080192ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>length</name>
      <anchorfile>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</anchorfile>
      <anchor>aae578a29a4231d9460bed1fe61e66cd0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>asn</name>
      <anchorfile>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</anchorfile>
      <anchor>a81686f0b2a7a510d4f9b56f074822cd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>src</name>
      <anchorfile>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</anchorfile>
      <anchor>a47919526dc7dcc7e9cd295bd6c5ad788</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>dst</name>
      <anchorfile>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</anchorfile>
      <anchor>ac4672fd84aa34a067f4cb3e074357eab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>node</name>
      <anchorfile>struct_e_m_b_e_n_e_t___t_r_a_c_e___link_layer_telemetry.html</anchorfile>
      <anchor>aaa3417e18b631b3797b473ceccbc65a7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>EMBENET_Version</name>
    <filename>struct_e_m_b_e_n_e_t___version.html</filename>
    <member kind="variable">
      <type>uint8_t</type>
      <name>hi</name>
      <anchorfile>struct_e_m_b_e_n_e_t___version.html</anchorfile>
      <anchor>aadec9c3b80f792eae40af2a3649e255c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>lo</name>
      <anchorfile>struct_e_m_b_e_n_e_t___version.html</anchorfile>
      <anchor>a9c9c0df8adb102e3ccbbcb577a25a779</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint16_t</type>
      <name>rev</name>
      <anchorfile>struct_e_m_b_e_n_e_t___version.html</anchorfile>
      <anchor>ad2d19c2d682ae7bed1adca3b11528ea7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>embenet_node_port_api_TRACE</name>
    <title>Trace functions</title>
    <filename>group__embenet__node__port__api___t_r_a_c_e.html</filename>
    <class kind="struct">EMBENET_TRACE_LinkLayerTelemetry</class>
    <class kind="struct">EMBENET_NODE_TraceHandlers</class>
  </compound>
  <compound kind="group">
    <name>embenet_node_api</name>
    <title>embeNET Node API</title>
    <filename>group__embenet__node__api.html</filename>
    <class kind="struct">EMBENET_NODE_JoinConfig</class>
    <class kind="struct">EMBENET_NODE_EventHandlers</class>
    <docanchor file="group__embenet__node__api.html">UNINITIALIZED</docanchor>
    <docanchor file="group__embenet__node__api.html">INITIALIZED</docanchor>
    <docanchor file="group__embenet__node__api.html">JOINING</docanchor>
    <docanchor file="group__embenet__node__api.html">SYNCHRONIZED</docanchor>
    <docanchor file="group__embenet__node__api.html">JOINED</docanchor>
  </compound>
  <compound kind="group">
    <name>embenet_common</name>
    <title>embeNET common definitions</title>
    <filename>group__embenet__common.html</filename>
    <class kind="struct">EMBENET_K1</class>
    <class kind="struct">EMBENET_PSK</class>
    <class kind="struct">EMBENET_NODE_QuickJoinCredentials</class>
    <class kind="struct">EMBENET_Version</class>
  </compound>
  <compound kind="group">
    <name>embenet_node_port_aes</name>
    <title>AES-128 Interface</title>
    <filename>group__embenet__node__port__aes.html</filename>
  </compound>
  <compound kind="group">
    <name>embenet_node_port_alloc</name>
    <title>Embenet_node_port_alloc</title>
    <filename>group__embenet__node__port__alloc.html</filename>
  </compound>
  <compound kind="group">
    <name>embenet_node_port_brt</name>
    <title>Border Router Communication Interface</title>
    <filename>group__embenet__node__port__brt.html</filename>
  </compound>
  <compound kind="group">
    <name>embenet_node_port_capabilities</name>
    <title>Port Capabilities</title>
    <filename>group__embenet__node__port__capabilities.html</filename>
  </compound>
  <compound kind="group">
    <name>embenet_node_port_critical_section</name>
    <title>Critical Section Interface</title>
    <filename>group__embenet__node__port__critical__section.html</filename>
  </compound>
  <compound kind="group">
    <name>embenet_node_port_eui64</name>
    <title>64-bit Extended Unique Identifier (EUI-64) Interface</title>
    <filename>group__embenet__node__port__eui64.html</filename>
  </compound>
  <compound kind="group">
    <name>embenet_node_port_radio</name>
    <title>Radio Interface</title>
    <filename>group__embenet__node__port__radio.html</filename>
    <class kind="struct">EMBENET_RADIO_Capabilities</class>
    <class kind="struct">EMBENET_RADIO_RxInfo</class>
  </compound>
  <compound kind="group">
    <name>embenet_node_port_random</name>
    <title>Random Number Generator Interface</title>
    <filename>group__embenet__node__port__random.html</filename>
  </compound>
  <compound kind="group">
    <name>embenet_node_port_timer</name>
    <title>Timer Interface</title>
    <filename>group__embenet__node__port__timer.html</filename>
  </compound>
  <compound kind="page">
    <name>embenet_node_porting_guide</name>
    <title>embeNET Node Porting Guide</title>
    <filename>embenet_node_porting_guide.html</filename>
  </compound>
  <compound kind="page">
    <name>embenet_node_user_guide</name>
    <title>embeNET Node User Guide</title>
    <filename>embenet_node_user_guide.html</filename>
    <docanchor file="embenet_node_user_guide.html" title="Networking basics">embenet_node_networking_basics</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Overview of the network">embenet_node_networking_basics_overview</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Border router and nodes">embenet_node_networking_border_router</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="The network joining process">embenet_node_networking_joining</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="IPv6 and multicast">embenet_node_networking_ipv6</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="UPD and sockets">embenet_node_networking_udp</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Events and time">embenet_node_networking_events</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Stack architecture">embenet_node_stack_architecture</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="General information">embenet_node_stack_architecture_general</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Interfaces">embenet_node_stack_architecture_interfaces</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Node interface">embenet_node_stack_architecture_node</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Stack handling">embenet_node_stack_handling</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Basic stack handling">embenet_node_stack_handling_basic</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Networking callbacks">embenet_node_stack_handling_callbacks</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Exception handling">embenet_node_stack_handling_exceptions</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Network handling">embenet_node_network_handling</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Network configuration">embenet_node_network_handling_config</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Join rules in border router">embenet_node_network_handling_join_rules</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Joining the network">embenet_node_network_handling_joining</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Quick join">embenet_node_network_quick_join</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Leaving the network">embenet_node_network_leaving</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Event handlers">embenet_node_network_handling_events</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Group handling">embenet_node_group_handling</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Task handling">embenet_node_task_handling</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Local time and network time">embenet_node_task_handling_clocks</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Local time">embenet_node_task_handling_local_time</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Network time">embenet_node_task_handling_network_time</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Scheduling tasks">embenet_node_task_handling_tasks</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Tasks scheduled in network time">embenet_node_task_handling_differences</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="UDP and sockets">embenet_node_udp</docanchor>
    <docanchor file="embenet_node_user_guide.html" title="Random numbers">embenet_node_random</docanchor>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>embeNET Node C API</title>
    <filename>index.html</filename>
    <docanchor file="index.html" title="embeNET Node C API">mainpage</docanchor>
  </compound>
</tagfile>
