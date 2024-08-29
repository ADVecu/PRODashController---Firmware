#include "pch.h"
#include "defaults.h"
#include "hellen_meta.h"
#include "hellen_leds_100.cpp"

static void setInjectorPins()
{
	engineConfiguration->injectionPins[0] = Gpio::MM100_INJ1;
	engineConfiguration->injectionPins[1] = Gpio::MM100_INJ2;
	engineConfiguration->injectionPins[2] = Gpio::MM100_INJ3;
}

static void setIgnitionPins()
{
	engineConfiguration->ignitionPins[0] = Gpio::MM100_IGN1;
	engineConfiguration->ignitionPins[1] = Gpio::MM100_IGN2;
	engineConfiguration->ignitionPins[2] = Gpio::MM100_IGN3;
}

static void setupDefaultSensorInputs()
{
	engineConfiguration->tps1_1AdcChannel = MM100_IN_TPS_ANALOG;

	engineConfiguration->map.sensor.hwChannel = MM100_IN_MAP1_ANALOG;

	engineConfiguration->clt.adcChannel = MM100_IN_CLT_ANALOG;

	engineConfiguration->iat.adcChannel = MM100_IN_IAT_ANALOG;

	engineConfiguration->triggerInputPins[0] = Gpio::MM100_UART8_TX; // VR2 max9924 is the safer default
	engineConfiguration->camInputs[0] = Gpio::MM100_IN_D1;			 // HALL1
}

void setBoardConfigOverrides()
{
	setHellenMegaEnPin();
	setHellenVbatt();

	hellenMegaSdWithAccelerometer();

	setHellenCan();

	setDefaultHellenAtPullUps();
}

/**
 * @brief   Board-specific configuration defaults.
 *
 * See also setDefaultEngineConfiguration
 *
 */
void setBoardDefaultConfiguration()
{
	setInjectorPins();
	setIgnitionPins();
	setHellenMMbaro();

	engineConfiguration->displayLogicLevelsInEngineSniffer = true;
	engineConfiguration->globalTriggerAngleOffset = 0;
	engineConfiguration->canTxPin = Gpio::MM100_CAN_TX;
	engineConfiguration->canRxPin = Gpio::MM100_CAN_RX;

	// "required" hardware is done - set some reasonable defaults
	engineConfiguration->enableVerboseCanTx = true;

	// Some sensible defaults for other options
	setupDefaultSensorInputs();
	setCrankOperationMode();

	engineConfiguration->enableVerboseCanTx = true;

	engineConfiguration->injectionMode = IM_BATCH;

	engineConfiguration->etbFunctions[0] = DC_None;

	setAlgorithm(LM_SPEED_DENSITY);

	engineConfiguration->injectorCompensationMode = ICM_FixedRailPressure;

	setCommonNTCSensor(&engineConfiguration->clt, HELLEN_DEFAULT_AT_PULLUP);
	setCommonNTCSensor(&engineConfiguration->iat, HELLEN_DEFAULT_AT_PULLUP);
	setTPS1Calibration(100, 650);
}

static Gpio OUTPUTS[] = {
	Gpio::MM100_INJ5, // B2 injector output 5
	Gpio::MM100_INJ4, // B3 injector output 4
	Gpio::MM100_INJ3, // B4 injector output 3
	Gpio::MM100_INJ2, // B5 injector output 2
	Gpio::MM100_INJ1, // B6 injector output 1
	Gpio::MM100_INJ7, // B7 Low Side output 1
	Gpio::MM100_INJ6, // B8 Low Side output 2
	Gpio::MM100_INJ8,

	Gpio::MM100_OUT_PWM2, // B16 Low Side output 4 / Fuel Pump
	Gpio::MM100_OUT_PWM1, // B17 Low Side output 3
	Gpio::MM100_IGN3,	  // B12 Coil 3
	Gpio::MM100_IGN2,	  // B14 Coil 2
	Gpio::MM100_IGN1,

};

int getBoardMetaOutputsCount()
{
	return efi::size(OUTPUTS);
}

int getBoardMetaLowSideOutputsCount()
{
	return getBoardMetaOutputsCount() - 6;
}

Gpio *getBoardMetaOutputs()
{
	return OUTPUTS;
}

int getBoardMetaDcOutputsCount()
{
	if (engineConfiguration->engineType == engine_type_e::HONDA_OBD1 ||
		engineConfiguration->engineType == engine_type_e::MAZDA_MIATA_NA6 ||
		engineConfiguration->engineType == engine_type_e::MAZDA_MIATA_NA94 ||
		engineConfiguration->engineType == engine_type_e::MAZDA_MIATA_NA96 ||
		engineConfiguration->engineType == engine_type_e::MAZDA_MIATA_NB1 ||
		engineConfiguration->engineType == engine_type_e::MAZDA_MIATA_NB2)
	{
		return 0;
	}
	return 2;
}
