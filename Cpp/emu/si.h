/* Formal Definitions of a Dimension System with 6 base dimenions
 *
 * Author: Emanuel Regnath (emanuel.regnath@tum.de)
 *
 * Feature: Allows to make quantities more specific without
 *          performance loss.
 *
 * Example: Length_Type distance = 3.0 * Milli * Meter;
 *
 * Dimensions:
 * ==========================================================================
 *  Dimension:   Length   Mass       Time     Current   Temperature   Angle
 *  Dim. Symb.:  L        M          T        I         H (Θ)         A
 * --------------------------------------------------------------------------
 *  Unit:        Meter    Kilogram   Second   Ampere    Kelvin        Radian
 *  Unit Symb.:  m        Kg         s        A         K             rad
 * ==========================================================================
 */

#ifndef SI_UNITS_H
#define	SI_UNITS_H
namespace si {


// Your Settings (Change it to your needs)
// ========================================================================


/* define whether unit dimensionality should be statically checked by template
 * parameters (=1) or whether this header jus provides name definitions (=0). */
#define SI_DIMENSION_CHECKING 0


/* define whether imperial units such as "inch" are allowed (=1) or not (=0) */
#define SI_ALLOW_IMPERIAL_UNITS 1


/* define the numeric type of the quantities. Use float or double. */
typedef double Numeric_Type;



// Implementation
// ========================================================================

    // SI Types
    typedef Numeric_Type Prefix_Type;
    typedef int DimExp;


    // Quantity Implementation
#if(SI_DIMENSION_CHECKING)
    // conversion Macro
    #define SI_NUM(quant) ((quant).getValue())

    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    class Quantity;

    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    const Quantity<L,M,T,I,H,A> operator+(const Quantity<L,M,T,I,H,A>&, const Quantity<L,M,T,I,H,A>&);

    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    const Quantity<L,M,T,I,H,A> operator-(const Quantity<L,M,T,I,H,A>&, const Quantity<L,M,T,I,H,A>&);

    template<DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    class Quantity{
    public:
           Quantity(Numeric_Type val=0.0) : value(val){}
           Quantity& operator+=(const Quantity& rhs){
               value+=rhs.value;
               return *this;
           }
           Quantity& operator-=(const Quantity& rhs){
               value-=rhs.value;
               return *this;
           }
           Numeric_Type getValue() const{
               return value;
           }
    private:
           Numeric_Type value;
           friend const Quantity<L,M,T,I,H,A> operator +<L,M,T,I,H,A>(const Quantity<L,M,T,I,H,A>&, const Quantity<L,M,T,I,H,A>&);
           friend const Quantity<L,M,T,I,H,A> operator -<L,M,T,I,H,A>(const Quantity<L,M,T,I,H,A>&, const Quantity<L,M,T,I,H,A>&);

    };


    // Q + Q
    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    const Quantity<L,M,T,I,H,A> operator +(const Quantity<L,M,T,I,H,A>& lhs, const Quantity<L,M,T,I,H,A>& rhs){
        return Quantity<L,M,T,I,H,A>(lhs)+=rhs;
    }

    // Q - Q
    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    const Quantity<L,M,T,I,H,A> operator -(const Quantity<L,M,T,I,H,A>& lhs, const Quantity<L,M,T,I,H,A>& rhs){
        return Quantity<L,M,T,I,H,A>(lhs)-=rhs;
    }

    // Q * Q
    template <DimExp L1, DimExp M1, DimExp T1, DimExp I1, DimExp H1, DimExp A1,
              DimExp L2, DimExp M2, DimExp T2, DimExp I2, DimExp H2, DimExp A2>
    const Quantity<L1+L2,M1+M2,T1+T2,I1+I2,H1+H2,A1+A2> operator *(const Quantity<L1,M1,T1,I1,H1,A1>& lhs, const Quantity<L2,M2,T2,I2,H2,A2>& rhs){
        return Quantity<L1+L2,M1+M2,T1+T2,I1+I2,H1+H2,A1+A2>(lhs.getValue()*rhs.getValue());
    }

    // F * Q
    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    const Quantity<L,M,T,I,H,A> operator *(const Numeric_Type& lhs, const Quantity<L,M,T,I,H,A>& rhs){
        return Quantity<L,M,T,I,H,A>(lhs*rhs.getValue());
    }

    // Q * F
    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    const Quantity<L,M,T,I,H,A> operator *(const Quantity<L,M,T,I,H,A>& lhs, const Numeric_Type& rhs){
        return Quantity<L,M,T,I,H,A>(lhs.getValue() * rhs);
    }

    // Q / Q
    template <DimExp L1, DimExp M1, DimExp T1, DimExp I1, DimExp H1, DimExp A1,
              DimExp L2, DimExp M2, DimExp T2, DimExp I2, DimExp H2, DimExp A2>
    const Quantity<L1-L2,M1-M2,T1-T2,I1-I2,H1-H2,A1-A2> operator /(const Quantity<L1,M1,T1,I1,H1,A1>& lhs, const Quantity<L2,M2,T2,I2,H2,A2>& rhs){
        return Quantity<L1-L2,M1-M2,T1-T2,I1-I2,H1-H2,A1-A2>(lhs.getValue()/rhs.getValue());
    }

    // Q == Q
    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    bool operator ==(const Quantity<L,M,T,I,H,A>& lhs, const Quantity<L,M,T,I,H,A>& rhs){
        return (lhs.getValue()==rhs.getValue());
    }

    // Q <= Q
    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    bool operator <=(const Quantity<L,M,T,I,H,A>& lhs, const Quantity<L,M,T,I,H,A>& rhs){
        return lhs.getValue()<=rhs.getValue();
    }

    // Q >= Q
    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    bool operator >=(const Quantity<L,M,T,I,H,A>& lhs, const Quantity<L,M,T,I,H,A>& rhs){
        return lhs.getValue()>=rhs.getValue();
    }

    // Q < Q
    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    bool operator <(const Quantity<L,M,T,I,H,A>& lhs, const Quantity<L,M,T,I,H,A>& rhs){
        return lhs.getValue()<rhs.getValue();
    }

    // Q > Q
    template <DimExp L, DimExp M, DimExp T, DimExp I, DimExp H, DimExp A>
    bool operator >(const Quantity<L,M,T,I,H,A>& lhs, const Quantity<L,M,T,I,H,A>& rhs){
        return lhs.getValue()>rhs.getValue();
    }


    // Base Dimenions
    //                m,kg, s, A, K, r
    typedef Quantity< 1, 0, 0, 0, 0, 0> Length_Type;
    typedef Quantity< 0, 1, 0, 0, 0, 0> Mass_Type;
    typedef Quantity< 0, 0, 1, 0, 0, 0> Time_Type;
    typedef Quantity< 0, 0, 0, 1, 0, 0> Current_Type;
    typedef Quantity< 0, 0, 0, 0, 1, 0> Temperature_Type;
    typedef Quantity< 0, 0, 0, 0, 0, 1> Angle_Type;


    // Derived Dimenions with own Unit
    //                m,kg, s, A, K, r
    typedef Quantity< 0, 0,-1, 0, 0, 0> Frequency_Type;
    typedef Quantity<-1, 1,-2, 0, 0, 0> Pressure_Type;
    typedef Quantity< 1, 1,-2, 0, 0, 0> Force_Type;
    typedef Quantity< 2, 1,-3, 0, 0, 0> Power_Type;
    typedef Quantity< 2, 1,-2, 0, 0, 0> Energy_Type;
    typedef Quantity< 0, 0, 1, 1, 0, 0> Charge_Type;
    typedef Quantity< 2, 1,-3,-1, 0, 0> Voltage_Type;
    typedef Quantity<-2,-1, 4, 2, 0, 0> Capacitance_Type;
    typedef Quantity< 2, 1,-3,-2, 0, 0> Resistance_Type;
    typedef Quantity< 2, 1,-2,-1, 0, 0> MagneticFlux_Type;
    typedef Quantity< 0, 1,-2,-1, 0, 0> MagneticFluxDensity_Type;
    typedef Quantity< 2, 1,-2,-2, 0, 0> Inductance_Type;



    // Further Quantities
    //                m,kg, s, A, K, r
    typedef Quantity< 2, 0, 0, 0, 0, 0> Area_Type;
    typedef Quantity< 3, 0, 0, 0, 0, 0> Volume_Type;
    typedef Quantity< 1, 0,-1, 0, 0, 0> LinearVelocity_Type;
    typedef Quantity< 1, 0,-2, 0, 0, 0> LinearAcceleration_Type;


    // boost compatible cast
//    template<typename TARGET_TYPE>
//    TARGET_TYPE quantity_cast(Quantity<L,M,T,I,H,A> quant){
//        return (TARGET_TYPE) quant.getValue();
//    }

#else

    typedef Numeric_Type Quantity;

    // conversion Macro
    #define SI_NUM(quantity) (quantity)

    // Base Dimenions
    typedef Quantity Length_Type;
    typedef Quantity Mass_Type;
    typedef Quantity Time_Type;
    typedef Quantity Current_Type;
    typedef Quantity Temperature_Type;
    typedef Quantity Angle_Type;

    // Derived Dimenions with own Unit
    typedef Quantity Frequency_Type;
    typedef Quantity Pressure_Type;
    typedef Quantity Force_Type;
    typedef Quantity Power_Type;
    typedef Quantity Energy_Type;
    typedef Quantity Charge_Type;
    typedef Quantity Voltage_Type;
    typedef Quantity Capacitance_Type;
    typedef Quantity Resistance_Type;
    typedef Quantity MagneticFlux_Type;
    typedef Quantity MagneticFluxDensity_Type;
    typedef Quantity Inductance_Type;

    // Further Quantities
    typedef Quantity Area_Type;
    typedef Quantity Volume_Type;
    typedef Quantity LinearVelocity_Type;
    typedef Quantity LinearAcceleration_Type;

    typedef Quantity AngularVelocity_Type;
    typedef Quantity AngularAcceleration_Type;

#endif

    // Prefix Definitions
    // ========================================================================
    const Prefix_Type Yocto = 1.0e24;
    const Prefix_Type Zetta = 1.0e21;
    const Prefix_Type Exa   = 1.0e18;
    const Prefix_Type Peta  = 1.0e15;
    const Prefix_Type Terra = 1.0e12;
    const Prefix_Type Giga  = 1.0e9;
    const Prefix_Type Mega  = 1.0e6;
    const Prefix_Type Kilo  = 1.0e3;
    const Prefix_Type Hecto = 1.0e2;
    const Prefix_Type Deca  = 1.0e1;
    const Prefix_Type Deci  = 1.0e-1;
    const Prefix_Type Centi = 1.0e-2;
    const Prefix_Type Milli = 1.0e-3;
    const Prefix_Type Micro = 1.0e-6;
    const Prefix_Type Nano  = 1.0e-9;
    const Prefix_Type Pico  = 1.0e-12;
    const Prefix_Type Femto = 1.0e-15;
    const Prefix_Type Atto  = 1.0e-18;
    const Prefix_Type Zepto = 1.0e-21;
    const Prefix_Type Yotta = 1.0e-24;


    // Unit Definitions
    // ========================================================================

    // Base Units
    const Length_Type      Meter  = 1.0;
    const Mass_Type        Gram   = 1.0e-3;
    const Time_Type        Second = 1.0;
    const Current_Type     Ampere = 1.0;
    const Temperature_Type Kelvin = 1.0;
    const Angle_Type       Radian = 1.0;

    // Derived Units
    const Frequency_Type   Hertz   = 1.0;
    const Pressure_Type    Pascal  = 1.0;
    const Force_Type       Newton  = 1.0;
    const Power_Type       Watt    = 1.0;
    const Energy_Type      Joule   = 1.0;
    const Charge_Type      Coulomb = 1.0;
    const Voltage_Type     Volt    = 1.0;
    const Capacitance_Type Farad   = 1.0;
    const Resistance_Type  Ohm     = 1.0;
    const Inductance_Type  Henry   = 1.0;
    const MagneticFlux_Type        Weber = 1.0;
    const MagneticFluxDensity_Type Tesla = 1.0;


    // Non SI Units but common
    const Time_Type Minute = 60.0 * Second;
    const Time_Type Hour   = 60.0 * Minute;
    const Time_Type Day    = 24.0 * Hour;

    const Volume_Type   Liter = 0.001 * Meter*Meter*Meter;

    const Pressure_Type Bar = 1.0e5 * Pascal;

    const Energy_Type Electronvolt = 1.60217653e-19 * Joule;

    const Angle_Type Degree = ( 2.0 * 3.14159265 / 360.0 ) * Radian;


    // Imperial Units (Non-SI, should not be used)
    #if(SI_ALLOW_IMPERIAL_UNITS)
    const Length_Type Inch = 0.0254 * Meter;
    const Length_Type Foot = 12.0 * Inch;
    const Length_Type Yard = 3.0 * Foot;
    const Length_Type Mile = 1609.3440 * Meter;
    const Mass_Type   Pound = 453.59237 * Gram;
    #endif





    // Constant Definitions
    // ========================================================================

    // Physical Constants from NIST (http://physics.nist.gov/ | 2017)
    const Length_Type         PLANCK_LENGTH   = 1.616229e-35 * Meter;
    //const Dimension_Type      PLANCK_CONSTANT = 6.626070e-34 * Joule * Second;

    // Defined Constants
    //const Dimension_Type      MAGNETIC_CONSTANT = 1.256637061 * Newton / (Ampere*Ampere);
    const LinearVelocity_Type SPEED_OF_LIGHT    = 299792458 * Meter / Second;


    // Helper Functions
    // ========================================================================
//    Temperature_Type ClesiusToKelvin( Numeric_Type temp ){
//        return ( (273.15 + temp) * Kelvin );
//    }




}

#endif	/* SI_UNITS_H */






