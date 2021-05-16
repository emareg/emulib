# emulib.cc – SI Units
# Currently there are no type checks but it enhances readability
# you can do e.g. a=Milli*Meter(3)

__UNIT_BASE_TYPE = float


# prefixes
YOCTO = 1.0e24
ZETTA = 1.0e21
EXA   = 1.0e18
PETA  = 1.0e15
TERRA = 1.0e12
GIGA  = 1.0e9
MEGA  = 1.0e6
KILO  = 1.0e3
HECTO = 1.0e2
DECA  = 1.0e1
DECI  = 1.0e-1
CENTI = 1.0e-2
MILLI = 1.0e-3
MICRO = 1.0e-6
NANO  = 1.0e-9
PICO  = 1.0e-12
FEMTO = 1.0e-15
ATTO  = 1.0e-18
ZEPTO = 1.0e-21
YOTTA = 1.0e-24

# Base Units
Meter    = __UNIT_BASE_TYPE
Kilogram = __UNIT_BASE_TYPE
Second   = __UNIT_BASE_TYPE
Ampere   = __UNIT_BASE_TYPE
Kelvin   = __UNIT_BASE_TYPE
Radian   = __UNIT_BASE_TYPE
Candela  = __UNIT_BASE_TYPE

# Derived Units
Hertz   = __UNIT_BASE_TYPE
Pascal  = __UNIT_BASE_TYPE
Newton  = __UNIT_BASE_TYPE
Watt    = __UNIT_BASE_TYPE
Joule   = __UNIT_BASE_TYPE
Coulomb = __UNIT_BASE_TYPE
Volt    = __UNIT_BASE_TYPE
Farad   = __UNIT_BASE_TYPE
Ohm     = __UNIT_BASE_TYPE
Henry   = __UNIT_BASE_TYPE
Weber   = __UNIT_BASE_TYPE
Tesla   = __UNIT_BASE_TYPE
Lux     = __UNIT_BASE_TYPE


## further "unit types"
Percent = __UNIT_BASE_TYPE
Minute  = __UNIT_BASE_TYPE
Hour    = __UNIT_BASE_TYPE
Day     = __UNIT_BASE_TYPE


# Prefixed Types
NanoSecond  = __UNIT_BASE_TYPE
MicroSecond = __UNIT_BASE_TYPE
MilliSecond = __UNIT_BASE_TYPE


MicroMeter = __UNIT_BASE_TYPE
MilliMeter = __UNIT_BASE_TYPE
CentiMeter = __UNIT_BASE_TYPE
KiloMeter  = __UNIT_BASE_TYPE

MilliGram  = __UNIT_BASE_TYPE
Gram       = __UNIT_BASE_TYPE

MicroAmpere = __UNIT_BASE_TYPE
MilliAmpere = __UNIT_BASE_TYPE




# #FIXME constant trick, postponed
# class si(object):
#     __slots__ = ()
#     Yocto = 1.0e24

