# Internals of the embeNET demo for NUCLEO-WL33CC1 board {#internals_of_demo}

@tableofcontents

This document describes the internals of the embeNET demo application running on **NUCLEO-WL33CC1** boards and provides information on how to modify and extend the demo.

## How does the demo application work

The demo application uses the [embeNET Node C API library](https://embe.net/docs/?q=doxyview/embeNET%20Node) to join the network and run two network services:
- [ENMS: embeNET Network Management service](https://embe.net/docs/?q=doxyview/embeNET%20ENMS) that allows to gather information about the network operation from the nodes
- custom exemplary service, that sends out a simple message every 5 seconds and also reacts to some simple messages

Below is a short explanation of all important steps. Basically the whole application fits into the *main* function. 

### Initialization

The initialization part configures STM32 HAL, system clock, GPIOs and USART1:
~~~{.c}
	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();
	/* Configure the peripherals common clocks */
	PeriphCommonClock_Config();
    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_MRSUBG_Init();
    MX_USART1_UART_Init();
    MX_AES_Init();
    MX_RNG_Init();
    MX_TIM2_Init();
    MX_LPUART1_UART_Init();
    /* USER CODE BEGIN 2 */
    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);
    BSP_LED_Init(LED_BLUE);
    BSP_LED_On(LED_RED);
~~~

Next we configure the logging facility of the embeNET:
~~~{.c}
LOGGER_SetOutput(logOutputWrapper, NULL);
LOGGER_SetRuntimeLevel(LOGGER_LEVEL_TRACE);
// You can change this to LOGGER_Enable to enable more logs from embeNET:
LOGGER_Disable();
~~~
Next the embeNET stack is initialized with additional code that prints the version number:
~~~{.c}
// Initialize structure to provide Stack with user-defined event handlers
EMBENET_NODE_EventHandlers handlers = {
	.onJoined = onJoined,
	.onLeft = onLeft,
	.onJoinAttempt = onJoinAttempt,
	.onDataOnUnregisteredPort = dataOnUregisteredPort,
	.onQuickJoinCredentialsObsolete = onQuickJoinCredentialsObsolete
};

// Initialize network stack
if (EMBENET_RESULT_OK == EMBENET_NODE_Init(&handlers)) {
    EMBENET_Version ver = EMBENET_NODE_GetVersion();
    printf("embeNET Node v%d.%d.%d initialized\n", ver.hi, ver.lo, ver.rev);
} else {
    printf("Failed to initialize embeNET Node\n");
}
~~~

After that the ENMS service is initialized:
~~~{.c}
// Get hardware ID using 96-bit CPU uid
uint8_t hardwareId[16] = {0x00};
memcpy(hardwareId, (void const*)UID_BASE, 12);
// Initialize ENMS service on its default port. You may specify custom Hardware Identifier and firmware version
if (ENMS_RESULT_OK == ENMS_NODE_Init(&enmsNode, ENMS_NODE_GetDefaultPort(), hardwareId, ENMS_NODE_GetSmallScalePolicy())) {
	printf("ENMS service initialized\n");
} else {
	printf("Failed to initialize ENMS service!\n");
}
~~~

We also start a clever LED blinking task, which will show that all the nodes that joined one network are synchronized:
~~~{.c}
// Initialize LED blinking task
synchronous_led_task_init();
~~~

In case of root we just start it:
~~~{.c}
    printf("Acting as root with UID: 0x%x%08x\n\r", (unsigned)(EMBENET_NODE_GetUID()>>32), (unsigned)(EMBENET_NODE_GetUID()));
    // When the application is built for Root node, start as root instead of joining the network
    if (EMBENET_RESULT_OK == EMBENET_NODE_RootStart(NULL, 0)) {
    	printf("Root started successfully\n\r");
    } else {
    	printf("Failed to start as root!\n\r");
    }
~~~

In case of nodes we start the custom demo service and MQTT-SN service:
~~~{.c}
    printf("Acting as node with UID: 0x%x%08x\n\r", (unsigned)(EMBENET_NODE_GetUID()>>32), (unsigned)(EMBENET_NODE_GetUID()));

    // Initialize exemplary, user-defined custom UDP service
    udp_service_init();
    // Initialize MQTT-SN service
    mqttsn_client_service_init();

    // Additionally tell the ENMS what services are running
    (void) ENMS_NODE_RegisterService(&enmsNode, "udp-service", 1);
    (void) ENMS_NODE_RegisterService(&enmsNode, "mqttsn-service", 1);
~~~

### Joining the network

In order to join the network the node has to setup the required network configuration:
~~~{.c}
    // embeNET network configuration:
    // K1 key, used to authenticate the network node should join and
    // PSK - Node's secret key.
    // Note that the psk value should be preferably stored in secure memory, or be preloaded using custom bootloader.
    const EMBENET_NODE_JoinConfig config = {
        .k1.val = { 0xc0, 0x8b, 0x76, 0x62, 0x77, 0x09, 0x9e, 0x7d, 0x7e, 0x9c, 0x02, 0x22, 0xf1, 0x68, 0xcc, 0x9e },
        .psk.val = {0x46, 0xd7, 0xdc, 0x94, 0xe8, 0xee, 0x74, 0x96, 0xce, 0xaf, 0x54, 0xa3, 0xab, 0x64, 0xcb, 0xeb },
    };

    printf("Trying to join a network...\n\r");
    // Make the node join the network
    EMBENET_NODE_Join(&config);
~~~

### The main loop

The application's main loop consists of a call to:
- embeNET Node processing function
- MQTT-SN service process (only needed for polling button status)

~~~{.c}
    /* Infinite loop */
    while (1) {
        // Periodically call embeNET Node process function
        EMBENET_NODE_Proc();
#if 1 != IS_ROOT
        // When acting as Node, run the MQTT-SN service process
        mqttsn_client_service_proc();
#endif
    }
~~~

### Network join event

Once the node joins the network an event callback will be called. In our demo application this callback simply starts the network services:
~~~{.c}
static void onJoined(EMBENET_PANID panId, const EMBENET_NODE_QuickJoinCredentials *quickJoinCredentials) {
	printf("Joined network with PANID: x%04" PRIx16 "\n", panId);
	printf("Starting ENMS service\n");

	// Start ENMS Service that provides network-wide telemetry information
	EnmsNodeResult enmsStartStatus = ENMS_NODE_Start(&enmsNode);
	if (ENMS_NODE_RESULT_OK != enmsStartStatus) {
		printf("ENMS service failed to start with status %d\n", (int) enmsStartStatus);
	}

	// Start exemplary, user-defined custom service
	custom_service_start();
	// Start MQTT-SN demo service
	mqttsn_client_service_start();
}
~~~

### Network leave event

In case when node gets disconnected from the network, another callback is called. In our demo application this callback stops the network services:
~~~{.c}
static void onLeft(void) {
	printf("Node has left the network\n");
	// Stop ENMS service
	EnmsNodeResult enmsStopStatus = ENMS_NODE_Stop(&enmsNode);
	if (ENMS_NODE_RESULT_OK == enmsStopStatus) {
		printf("ENMS service stopped\n");
	} else {
		printf("ENMS service failed to stop with status %d\n", (int)enmsStopStatus);
	}
	
	// Stop exemplary, user-defined custom service
	custom_service_stop();
	// Stop MQTT-SN demo service
	mqttsn_client_service_stop();	
}
~~~

### Handling critical errors

In cases when the embeNET stack detects a critical condition, the following handler is called by the stack, giving a chance to react:
~~~{.c}
 __attribute__((noreturn)) void EXPECT_OnAbortHandler(char const* why, char const* file, int line) {
    printf("Program aborted: %s %s:%i\n", why, file, line);
    while(1) {
        ;
    }
    __builtin_unreachable();
}
~~~

## Customizing and extending the demo application

The structure of the firmware project **embenet_demo_cubeide** is mostly generated by STM32CubeMX application. The source *.ioc* file is included in the project. This allows you to easily customize the peripherals for your demo project as needed.

>The only requirement is **NOT** to change configuration of peripherals used by the port implementation, i.e. RADIO, CRYP, TIM2.

### Writing or extending a custom network service.

The best starting point is to look at implementation of the existing custom_service.

### Disabling "zero rule"

In order to disable the "zero rule", delete the rule with `"uid": 0,` from your *config.json* file, and add appropriate rules for your nodes, for example:

```json
    "join_rules":  [
        {
            "uid": 2,
            "psk": "0x1ccd738f70a35be9574738ad190f86f2"
        },
        {
            "uid": 3,
            "psk": "0xdc2eafe4016303ebb1aa1b4b2ed4fda0"
        }
    ]
```

This will allow only nodes with uid = 2 and 3, to join the network, provided that their PSKs match those from *config.json* file.

### Using custom name for network interface

You may specify the name of desired network interface in .json file, by adding on root level:

```json
"interface_name": "your-name"
```

## Limitations of embeNET demo application

The demo version of the embeNET stack allows to connect up to 10 nodes only, with network depth of max. 3 hops.

