BOARDCPPSRC =  $(BOARD_DIR)/board_configuration.cpp \
    $(BOARD_DIR)/default_tune.cpp \


BOARDINC += $(BOARD_DIR)/generated/controllers/generated

# defines SHORT_BOARD_NAME
include $(BOARD_DIR)/meta-info.env

#DDEFS += -DEFI_SENT_SUPPORT=TRUE
#DDEFS += -DSTATIC_BOARD_ID=STATIC_BOARD_ID_SMALL_CAN_BOARD

#DDEFS += -DEFI_SENSOR_CHART=FALSE
#DDEFS += -DLUA_USER_HEAP=50000
#DDEFS += -DEFI_IDLE_CONTROL=FALSE
#DDEFS += -DDL_OUTPUT_BUFFER=5000
DDEFS += -DEFI_ELECTRONIC_THROTTLE_BODY=FALSE
#DDEFS += -DEFI_LOGIC_ANALYZER=FALSE
#DDEFS += -DEFI_MALFUNCTION_INDICATOR=FALSE
#DDEFS += -DEFI_ENGINE_SNIFFER=FALSE
#DDEFS += -DEFI_ENGINE_EMULATOR=FALSE
#DDEFS += -DEFI_SHAFT_POSITION_INPUT=FALSE
#DDEFS += -DEFI_ALTERNATOR_CONTROL=FALSE
# temp DDEFS += -DEFI_ENGINE_CONTROL=FALSE
#DDEFS += -DEFI_VVT_PID=FALSE
#DDEFS += -DEFI_EMULATE_POSITION_SENSORS=FALSE
#DDEFS += -DEFI_MAP_AVERAGING=FALSE
#DDEFS += -DEFI_HPFP=FALSE
#DDEFS += -DEFI_TOOTH_LOGGER=FALSE
#DDEFS += -DRAM_UNUSED_SIZE=100
#DDEFS += -DPWM_FREQ_PWM=10000
DDEFS += -DEFI_SOFTWARE_KNOCK=FALSE
DDEFS += -DDIAG_5VP_PIN=Gpio::MM100_SPI3_MOSI

#DDEFS += -DHW_SMALL_CAN_BOARD=1


#Mass Storage
#DDEFS += -DEFI_EMBED_INI_MSD=FALSE

include $(BOARDS_DIR)/hellen/hellen-common100.mk

DDEFS += $(PRIMARY_COMMUNICATION_PORT_USART2)

#DDEFS += $(PRIMARY_COMMUNICATION_PORT_USART3)

# assign critical LED to a non-existent pin if you do not have it on your board
# good old PD14 is still the default value
# DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::I15
