#include "pch.h"
#include "defaults.h"
#include "hellen_meta.h"
#include "hellen_leds_100.cpp"

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
	setHellenMMbaro();

	engineConfiguration->displayLogicLevelsInEngineSniffer = true;
	engineConfiguration->canTxPin = Gpio::MM100_CAN_TX;
	engineConfiguration->canRxPin = Gpio::MM100_CAN_RX;

	// "required" hardware is done - set some reasonable defaults
	engineConfiguration->enableVerboseCanTx = true;

	// Some sensible defaults for other options
	setCrankOperationMode();

	setAlgorithm(LM_SPEED_DENSITY);

	engineConfiguration->injectorCompensationMode = ICM_FixedRailPressure;

	setCommonNTCSensor(&engineConfiguration->clt, HELLEN_DEFAULT_AT_PULLUP);
	setCommonNTCSensor(&engineConfiguration->iat, HELLEN_DEFAULT_AT_PULLUP);
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
