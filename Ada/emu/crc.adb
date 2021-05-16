with Interfaces; use Interfaces;

package body CRC with SPARK_Mode is

   -- init

   function crc8 (Data : Byte_Array) return Byte is
      checksum : Byte := 0;

   begin
      for pos in Data'Range loop
         checksum := crc8_tab (checksum xor Data (pos));
      end loop;

      return checksum;
   end crc8;

end CRC8;
