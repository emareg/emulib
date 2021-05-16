
var crc = {
  // CCIT-Polynomial: 0x07 / 0xE0
  tab8: [ 0x00, 0x1c, 0x38, 0x24, 0x70, 0x6c, 0x48, 0x54, 0xe0, 0xfc, 0xd8, 0xc4, 0x90, 0x8c, 0xa8, 0xb4 ],
  tab16: [  // CCIT-Polynomial: 0x1021, rev: 0x8408
    0x0000, 0x1081, 0x2102, 0x3183, 0x4204, 0x5285, 0x6306, 0x7387, 
    0x8408, 0x9489, 0xA50A, 0xB58B, 0xC60C, 0xD68D, 0xE70E, 0xF78F
  ],
  tab32: [ // CRC32-Polynomial: 0x04C11DB7, rev: 0xEDB88320
    0x00000000,0x1DB71064,0x3B6E20C8,0x26D930AC,0x76DC4190,0x6B6B51F4,0x4DB26158,0x5005713C,
    0xEDB88320,0xF00F9344,0xD6D6A3E8,0xCB61B38C,0x9B64C2B0,0x86D3D2D4,0xA00AE278,0xBDBDF21C
  ],
  // execute the CRC calculation with a given table
  _docrc: function(init, data, table){
    data = this._unifyData(data);
    let crc = init;
    for (let i = 0; i < data.length; i++) {
        crc = (crc >> 4) ^ table[((data[i] ^ crc) & 0x0F)]
        crc = (crc >> 4) ^ table[(((data[i]>>4) ^ crc) & 0x0F)]
    }
    return crc;    
  },
  // strings cannot be accessed by byte
  _unifyData: function(data){
    switch (typeof data) {
      case 'number': return Buffer.alloc(4).writeUInt32BE(data); break;
      // case 'string': return Buffer.from(data); break;
      case 'string': return new TextEncoder('utf-8').encode(data); break;
      // case 'string': return Uint8Array.from(data); break;
    }
  },
  crc8: function(data){ return this._docrc(0xFF, data, this.tab8) },
  crc16: function(data){ return this._docrc(0x00, data, this.tab16) },
  crc32: function(data){ return this._docrc(0xFFFFFFFF, data, this.tab32) },
}


// References
// https://reveng.sourceforge.io/crc-catalogue/
// https://github.com/Michaelangel007/crc32