-- Institution: Technische Universitaet Muenchen
-- Department:  Realtime Computer Systems (RCS)
-- Project:     StratoX
-- Module:      Units
--
-- Authors: Emanuel Regnath (emanuel.regnath@tum.de)
--
-- Description: Checked dimension system for physical calculations
--              Based on package System.Dim.MKS
--
-- ToDo:
-- [ ] Define all required types

with Ada.Real_Time; use Ada.Real_Time;
with Ada.Numerics;
with Types;

pragma Elaborate_All (Types); -- TODO: is this required?
package Units with
     Spark_Mode is

   ---------------------
   --  The unit system
   ---------------------

   type Unit_Type is new Float with  -- As tagged Type? -> Generics with Unit_Type'Class
        Dimension_System =>
        ((Unit_Name => Meter, Unit_Symbol => 'm', Dim_Symbol => 'L'),
         (Unit_Name => Kilogram, Unit_Symbol => "kg", Dim_Symbol => 'M'),
         (Unit_Name => Second, Unit_Symbol => 's', Dim_Symbol => 'T'),
         (Unit_Name => Ampere, Unit_Symbol => 'A', Dim_Symbol => 'I'),
         (Unit_Name => Kelvin, Unit_Symbol => 'K', Dim_Symbol => "Theta"),
         (Unit_Name => Radian, Unit_Symbol => "Rad", Dim_Symbol => "A")),
   Default_Value => 0.0; -- required for matrices

   type Unit_Array is array (Natural range <>) of Unit_Type;

   -- Base Units
   subtype Length_Type is Unit_Type with
        Dimension => (Symbol => 'm', Meter => 1, others => 0);

   subtype Mass_Type is Unit_Type with
        Dimension => (Symbol => "kg", Kilogram => 1, others => 0);

   subtype Time_Type is Unit_Type with
        Dimension => (Symbol => 's', Second => 1, others => 0);

   subtype Current_Type is Unit_Type with
     Dimension => (Symbol => 'A', Ampere => 1, others => 0);

   subtype Temperature_Type is Unit_Type with
        Dimension => (Symbol => 'K', Kelvin => 1, others => 0);

   subtype Angle_Type is Unit_Type with
        Dimension => (Symbol => "Rad", Radian => 1, others => 0);


   -- Derived Units
   subtype Length_Angle_Ratio_Type is Unit_Type with
     Dimension => (Meter => 1, Radian => -1, others => 0);


   -- mechanical
   subtype Frequency_Type is Unit_Type with
        Dimension => (Symbol => "Hz", Second => -1, others => 0);

   subtype Force_Type is Unit_Type with
        Dimension => (Symbol => "N", Kilogram => 1, Meter => 1, Second => -2, others => 0);

   subtype Energy_Type is Unit_Type with
        Dimension => (Symbol => "J", Kilogram => 1, Meter => 2, Second => -2, others => 0);

   subtype Power_Type is Unit_Type with
        Dimension => (Symbol => "W", Kilogram => 1, Meter => 2, Second => -3, others => 0);

   subtype Pressure_Type is Unit_Type with
        Dimension => (Symbol => "Pa", Kilogram => 1, Meter => -1, Second => -2, others => 0);

   -- electromagnetic
   subtype Voltage_Type is Unit_Type with
        Dimension =>
        (Symbol   => 'V',
         Meter    => 2,
         Kilogram => 1,
         Second   => -3,
         Ampere   => -1,
         others   => 0);

   subtype Charge_Type is Unit_Type with
        Dimension => (Symbol => 'C', Second => 1, Ampere => 1, others => 0);

   subtype Capacity_Type is Unit_Type with
        Dimension =>
        (Symbol   => 'F',
         Kilogram => -1,
         Meter    => -2,
         Second   => 4,
         Ampere   => 2,
         others   => 0);

   subtype Resistivity_Type is Unit_Type with
        Dimension =>
        (Symbol   => "Ω",
         Kilogram => 1,
         Meter    => 2,
         Second   => -2,
         Ampere   => -3,
         others   => 0);

   subtype Inductivity_Type is Unit_Type with
        Dimension =>
        (Symbol   => 'H',
         Kilogram => 1,
         Meter    => 2,
         Second   => -2,
         Ampere   => -2,
         others   => 0);

   subtype Electric_Field_Type is Unit_Type with
        Dimension =>
        (Meter    => 1,
         Kilogram => 1,
         Second   => -3,
         Ampere   => -1,
         others   => 0);

   subtype Magnetic_Flux_Type is Unit_Type with
        Dimension =>
        (Symbol   => "Wb",
         Kilogram => 1,
         Meter    => 2,
         Second   => -2,
         Ampere   => -1,
         others   => 0);

   subtype Magnetic_Flux_Density_Type is Unit_Type with
        Dimension => (Symbol => 'T', Kilogram => 1, Second => -2, Ampere => -1, others => 0);

   -- further important dimensions
   subtype Area_Type is Unit_Type with
        Dimension => (Symbol => "m^2", Meter => 2, others => 0);

   subtype Volume_Type is Unit_Type with
        Dimension => (Symbol => "m^3", Meter => 3, others => 0);

   subtype Linear_Velocity_Type is Unit_Type with
        Dimension => (Meter => 1, Second => -1, others => 0);

   subtype Angular_Velocity_Type is Unit_Type with
        Dimension => (Radian => 1, Second => -1, others => 0);

   subtype Linear_Acceleration_Type is Unit_Type with
        Dimension => (Meter => 1, Second => -2, others => 0);

   subtype Angular_Acceleration_Type is Unit_Type with
        Dimension => (Radian => 1, Second => -2, others => 0);

   --------------------------
   --  Prefixes for units
   --------------------------

   subtype Prefix_Type is Unit_Type;
   --type Prefix_Type is digits 2 range 1.0e-24 .. 1.0e+24;
   Yocto : constant Prefix_Type := Prefix_Type (1.0e-24);
   Zepto : constant Prefix_Type := Prefix_Type (1.0e-21);
   Atto  : constant Prefix_Type := Prefix_Type (1.0e-18);
   Femto : constant Prefix_Type := Prefix_Type (1.0e-15);
   Pico  : constant Prefix_Type := Prefix_Type (1.0e-12);
   Nano  : constant Prefix_Type := Prefix_Type (1.0e-9);
   Micro : constant Prefix_Type := Prefix_Type (1.0e-6);
   Milli : constant Prefix_Type := Prefix_Type (1.0e-3);
   Centi : constant Prefix_Type := Prefix_Type (1.0e-2);
   Deci  : constant Prefix_Type := Prefix_Type (1.0e-1);

   Deca  : constant Prefix_Type := Prefix_Type (1.0e+1);
   Hecto : constant Prefix_Type := Prefix_Type (1.0e+2);
   Kilo  : constant Prefix_Type := Prefix_Type (1.0e+3);
   Mega  : constant Prefix_Type := Prefix_Type (1.0e+6);
   Giga  : constant Prefix_Type := Prefix_Type (1.0e+9);
   Tera  : constant Prefix_Type := Prefix_Type (1.0e+12);
   Peta  : constant Prefix_Type := Prefix_Type (1.0e+15);
   Exa   : constant Prefix_Type := Prefix_Type (1.0e+18);
   Zetta : constant Prefix_Type := Prefix_Type (1.0e+21);
   Yotta : constant Prefix_Type := Prefix_Type (1.0e+24);


   --------------------------
   --  The units
   --------------------------

   -- Base units
   Meter       : constant Length_Type := Length_Type (1.0);

   Kilogram : constant Mass_Type := Mass_Type (1.0);
   Gram     : constant Mass_Type := Mass_Type (1.0e-3);

   Second   : constant Time_Type := Time_Type (1.0);

   Ampere : constant Current_Type := Current_Type (1.0);

   Kelvin : constant Temperature_Type := Temperature_Type (1.0);

   -- Angular Units
   Radian    : constant Angle_Type := Angle_Type (1.0);
   Degree    : constant Angle_Type := Angle_Type (2.0 * Ada.Numerics.Pi / 360.0);
   Evolution : constant Angle_Type := Angle_Type (2.0 * Ada.Numerics.Pi);

   -- Derived Units
   Newton : constant Force_Type := Force_Type (1.0);

   Joule : constant Energy_Type := Energy_Type (1.0);

   Watt : constant Power_Type := Power_Type (1.0);

   Ohm : constant Resistivity_Type := Resistivity_Type (1.0);

   Pascal : constant Pressure_Type := Pressure_Type (1.0);

   Volt : constant Voltage_Type := Voltage_Type (1.0);

   Coulomb : constant Charge_Type := Charge_Type(1.0);

   Farad : constant Capacity_Type := Capacity_Type(1.0);

   Weber : constant Magnetic_Flux_Type := Magnetic_Flux_Type(1.0);

   Tesla : constant Magnetic_Flux_Density_Type := Magnetic_Flux_Density_Type(1.0);

   Henry : constant Inductivity_Type := Inductivity_Type(1.0);

   Hertz : constant Frequency_Type := Frequency_Type (1.0);

   -- Non SI but metric
   Minute : constant Time_Type := 60.0 * Second;
   Hour   : constant Time_Type := 60.0 * Minute;
   Day    : constant Time_Type := 24.0 * Hour;

   Tonne    : constant Mass_Type     := 1_000.0 * Kilogram;
   Angstrom : constant Length_Type   := 1.0 * Nano * Meter;
   Litre    : constant Volume_Type   := 1.0 * (1.0 * Deci * Meter)**3;
   Bar      : constant Pressure_Type := 1_000.0 * Hecto * Pascal;
   Gauss    : constant Magnetic_Flux_Density_Type := 0.1 * Tesla;

   --------------------------
   --  Physical constants
   --------------------------

   -- Approximate gravity on the earth's surface
   GRAVITY : constant Linear_Acceleration_Type := 9.81 * Meter / (Second**2);

   CELSIUS_0 : constant Temperature_Type := 273.15 * Kelvin;

   DEGREE_360 : constant Angle_Type := 360.0 * Degree;
   RADIAN_2PI : constant Angle_Type := 2.0 * Radian;

   -- Physical constants
   SPEED_OF_LIGHT   : constant Linear_Velocity_Type     := 299_792_458.0 * Meter / Second;
   PLANCK_CONSTANT  : constant Unit_Type                := 6.626_070_040 * Joule * Second;
   GRAVITY_CONSTANT : constant Linear_Acceleration_Type := 127_137.6 * Kilo * Meter / (Hour**2);

   --------------------------
   --  Conversion functions
   --------------------------

   function To_Time
     (rtime : Ada.Real_Time.Time) return Time_Type is
     (Time_Type
        (Float ((rtime - Ada.Real_Time.Time_First) / Ada.Real_Time.Microseconds (1)) * Float(1.0e-6)));
   --  converts Real_Time to Time_Type, precision is Nanosecond

   function To_Time
     (rtime : Ada.Real_Time.Time_Span) return Time_Type is
     (Time_Type
        (Float ((rtime) / Ada.Real_Time.Microseconds (1)) * Float(1.0e-6)));

    function To_Time_Span(time : Time_Type) return Ada.Real_Time.Time_Span is
     ( Ada.Real_Time.Microseconds (Types.Sat_Cast_Int (Float (time) / Float(1.0e-6))));

     function To_Degree(angle : Angle_Type) return Float is
     (Float (angle / Degree));

   -------------------------------------------------------------
   --  Elementary math functions handling overflow/range checks
   -------------------------------------------------------------

   function "+"( Left : Ada.Real_Time.Time; Right : Time_Type ) return Ada.Real_Time.Time is
   ( Left + Ada.Real_Time.Microseconds (Types.Sat_Cast_Int (Float (Right) / Float(1.0e-6))));


   function wrap_Angle( angle : Angle_Type; min : Angle_Type; max : Angle_Type) return Angle_Type
     with Pre => min <= Angle_Type(0.0) and then
     max >= 0.0 * Radian and then
     angle <= Angle_Type'Last / 4.0 and then
     angle >= Angle_Type'First / 4.0 and then
     max <= Angle_Type'Last / 4.0 and then
       min >= Angle_Type'First / 4.0 and then
       max - min > 1.0e-3 * Radian,
     Post => Float (wrap_angle'Result) >= Float (min) and Float (wrap_angle'Result) <= Float (max);
   --  wrap angle between two values
   --  Must make no assumptions on input 'angle' here, otherwise caller might fail if it isn't SPARK.
   --  FIXME: the float casts in Post are a workaround for gcc

   function mirror_Angle( angle : Angle_Type; min : Angle_Type; max : Angle_Type) return Angle_Type
     with Pre => min <= 0.0 * Radian and then
     max >= 0.0 * Radian and then
     max > min and then
     max < Angle_Type'Last / 4.0 and then
     min > Angle_Type'First / 4.0,
     Post => Float (mirror_Angle'Result) >= Float (min) and Float (mirror_Angle'Result) <= Float (max);
   --  mirror angle at min/max boundaries
   --  FIXME: the float casts in Post are a workaround for gcc

   function delta_Angle(From : Angle_Type; To : Angle_Type) return Angle_Type;

   function integrate (x : Unit_Type; dt : Time_Type) return Unit_Type is (x * dt);
   --  Experimental generic integration (return value looses its units)
   pragma Inline_Always( integrate );


   generic
      type T is digits <>; -- any floating point type
   function Saturated_Addition (left, right : T) return T
     with Inline, Pre => 0.0 in T'Range;
   --  add two Floats of same Unit type and limit to the type's bounds

   generic
      type T is digits <>; -- any floating point type
   function Saturate (val, min, max : T) return T
     with Inline;
   --  limit to given range

   generic
      type T is digits <>; -- any floating point type
   function Saturated_Subtraction (left, right : T) return T
     with Inline, Pre => 0.0 in T'Range;
   --  that is required in addition to Saturated_Addition, if the ranges are
   --  not symmetric

   generic
      type T is digits <>; -- any floating point type
   function Wrapped_Addition (left, right : T) return T
     with Inline,
     Pre => 0.0 in T'Range;
   --  add two Floats of same Unit type and wrap ("modulo") to the type's bounds
   --  Must make no assumptions on inputs otherwise caller might fail if it isn't SPARK.

   generic
      type T is digits <>;
   function Saturated_Cast (val : Float) return T
     with Inline;
   --  convert a float into a more specific float type, and trim to the value range

   function sgn( x : Unit_Type'Base ) return Unit_Type is
     ( if x = 0.0 then 0.0 elsif x > 0.0 then 1.0 else -1.0 );
   --  get the sign as unit multiplier
   --  subtype Sign_Type is Float range -1.0 .. 1.0;


   --  function "*" (Left : Float; Right : Prefix_Type) return Unit_Type is
   --          ( Unit_Type( Left * Float(Right) ) );

   --------------------------
   --  functions on signals
   --------------------------

   -- function Radian( degree : Float ) return Float
   function average( signal : Unit_Array ) return Unit_Type;

   ------------------
   --  I/O helpers
   ------------------

   function Image  (unit : Unit_Type)  return String
     with Post => Image'Result'Length in 1 .. 36 and Image'Result'First = 1;
   function AImage (unit : Angle_Type) return String
     with Post => AImage'Result'Length in 1 .. 36 and AImage'Result'First = 1;
   function RImage (unit : Angle_Type) return String
     with Post => RImage'Result'Length in 1 .. 40 and RImage'Result'First = 1;

end Units;
