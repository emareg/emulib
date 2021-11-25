import time
import emu.prf


def test():
    prof = emu.prf.Profiler("join")
    for i in range(0,100):
        prof.start()
        "-".join(str(n) for n in range(i*100))
        prof.stop()

    print(prof)

test()