# emulib 
**embedded, modular, μicro library**

emulib is a collection of small, modular code files that can be individually integrated into to your software projects without introducing any dependencies. Just copy the file you need and you are ready to go. It is available in several languages.

> :warning: **This library is work in progress!**


## Features


* **embedded** The code of this library can easily be embedded into any project. The classes/functions are often so small that you can even inline them into another file. It is therefore also perfect for embedded systems as it has no dependencies and requires very few resources. 

* **modular:** Frameworks such as Qt or Boost require you to import large groups of functionality, quickly increasing code and binary size. This library allows you to reuse code on a single file basis and often on a single class/function basis! Only add the features that you really need.

* **μicro:** Resources are limited in the embedded world. The code in this library tries to be understandable and resource efficient. Each file is not longer than 200 LOC, most even less than 100 LOC. 

* **cross-language:** The modules of this library try to be consistent across several languages, such that you only need to learn the interfaces once and then can use them for other projects in different languages as well.


## Modules
Currently, the goal is to support the following modules.

```
emu.bit:   readable bit manipulation instead of reg = reg & ~(1 << idx)
emu.buf:   a generic fixed-memory circular message/byte buffer
emu.crc:   crc8, crc16, and crc32 with a minimal 16 entry LUT
emu.led:   LED functions such as blinking
emu.log:   log messages at several levels to stdout or file
emu.prf:  simple performance profiler to measure timing
emu.pid:   PID Controller
emu.si:    Enhance safety and readability SI units
```
<!-- emu.geo:   global positioning, e.g. bearing, haversine -->
<!-- emu.dsp:   digital signal processing, Kalman -->
<!-- emu.st:    statistics, (min,max,clamp) -->
<!-- emu.unify: some basic defines (min, max, clamp, Uint8, Int16, TRUE) -->

Since each language has different namespace styles, here is how the log.info call would look like:

| Lang | Full NS               |  Short Version   |
|------|-----------------------|------------------|
| C    | `LOG_info("hi");`     | `LOG_info("hi");` |
| C++  | `emu::log.info("hi");`| `log.info("hi");` |
| JS   | `emu.log.info("hi")`  | `log.info("hi")`  |
| μPy  | `emu.log.info("hi")`  | `log.info("hi")`  |



## Work in Progress
This library is work in progress and not everything works as it should. Not all interfaces use the exact same naming and not all modules are implemented in all languages. However, the code is available in its current state since it might still be very useful. 

### Module Matrix: What's covered so far?

| Module | Ada |  C  | C++ | μPy | JS  |
|--------|-----|-----|-----|-----|-----|
| `bit`  |  •  |  •  |     |  •  |     |
| `buf`  |     |     |  •  |  •  |     |
| `crc`  |  •  |  •  |     |  •  |  •  |
| `led`  |     |  •  |     |     |     | 
| `log`  |     |  •  |     |  •  |  •  |
| `prf`  |  •  |  •  |  •  |  •  |  •  |
| `pidc` |  •  |     |     |  •  |     | 
| `si`   |  •  |  •  |  •  |  •  |     |



