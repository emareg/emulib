
import emu.crc as crc

data=b"123456789"
print("CRC-8 is {}, should be 0xd0".format(hex(crc.crc8(data))))
print("CRC-16 is {}, should be 0x2189".format(hex(crc.crc16(data))))
print("CRC-32 is {}, should be 0xCBF43926".format(hex(crc.crc32(data))))
