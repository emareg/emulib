/* 
 * \author: Emanuel Regnath (emanuel.regnath@tum.de)
 *
 * Created on 19. März 2015, 11:34
 */

#ifndef SI_UNITS_H
#define	SI_UNITS_H

#define CFG_USE_FLOAT 0

// NumericType: int, float
typedef int NumericType;

#if CFG_USE_FLOAT

#define NANO  1.0e-9
#define MICRO 1.0e-6
#define MILLI 1.0e-3
#define KILO  1.0e3
#define MEGA  1.0e6
#define GIGA  1.0e9

#endif


// SI Base
typedef NumericType NanoSecond;
typedef NumericType MicroSecond;
typedef NumericType MilliSecond;
typedef NumericType Second;
typedef NumericType Minute;
typedef NumericType Hour;
typedef NumericType Day;


typedef NumericType MicroMeter;
typedef NumericType MilliMeter;
typedef NumericType CentiMeter;
typedef NumericType Meter;
typedef NumericType KiloMeter;


typedef NumericType MilliGram;
typedef NumericType Gram;
typedef NumericType KiloGram;


typedef NumericType NanoAmpere;
typedef NumericType MicroAmpere;
typedef NumericType MilliAmpere;
typedef NumericType Ampere;


typedef NumericType DeciCelsius;
typedef NumericType Celsius;
typedef NumericType DeciKelvin;
typedef NumericType Kelvin;



// SI Derived
typedef NumericType MilliNewton;
typedef NumericType Newton;
typedef NumericType KiloNewton;


typedef NumericType MicroVolt;
typedef NumericType MilliVolt;
typedef NumericType Volt;
typedef NumericType KiloVolt;

typedef NumericType MicroWatt;
typedef NumericType MilliWatt;
typedef NumericType Watt;
typedef NumericType KiloWatt;


typedef NumericType MilliOhm;
typedef NumericType Ohm;
typedef NumericType KiloOhm;


// SI Combined
typedef NumericType Meter_Per_Second;
typedef NumericType MilliMeter_Per_Second;

typedef NumericType Meter_Per_SecondSquared;


#endif	/* SI_UNITS_H */

