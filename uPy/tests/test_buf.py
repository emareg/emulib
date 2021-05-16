
import emu.buf as circbuf


def test():
    buf = circbuf.CircularBuffer(5)
    for c in "abc":
        buf.append(c)
        print("appended",c,buf)
    for c in "zyxwvu":
        buf.prepend(c)
        print("prepended",c,buf)
    for c in "abcdefg":
        el = buf.pop()
        print("pop",el,buf)
test()

