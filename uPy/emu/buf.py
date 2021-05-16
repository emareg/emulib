# Internals:
# head points to first element, tail to the field before last element
# head gets incremented by push_front
# tail gets decremented by push_back
#
#   0   1   2   3   4   5
# | - | - | A | B | C | - |
#           ^h          ^t

from collections import deque

# simple
# class CircularBuffer(deque):
#     def __init__(self, maxlen=10):
#         super().__init__(maxlen=maxlen)

#     def empty(self): return len(self) == 0
#     def full(self): return len(self) == 0




class CircularBuffer:

    def __init__(self, maxlen=10):
        self._buf = [None] * maxlen
        self.iTail = 0
        self.iHead = 0
        self.maxlen = maxlen
        self.hasElements = False

    def _warp(self, pos, deltapos):
        return (pos + deltapos + self.maxlen) % self.maxlen

    def empty(self):
        return not self.hasElements

    def full(self):
        return ( self.hasElements and (self.iHead == self.iTail) )

    def length(self):
        return self._warp(self.iHead, -self.iTail)

    # push at front/left
    def prepend(self, el):
        if self.full(): self.iTail = (self.iTail + 1) % self.maxlen
        self.iHead = (self.iHead-1+self.maxlen) % self.maxlen
        self._buf[ self.iHead ] = el
        self.hasElements = True

    # pop at front/left
    def next(self):
        if self.empty(): return None
        el = self._buf[ self.iHead ]
        self.iHead = (self.iHead + 1) % self.maxlen
        if self.iHead == self.iTail: self.hasElements = False
        return el

    # add to back/right
    def append(self, el):
        if self.full(): self.iHead = (self.iHead + 1) % self.maxlen
        self._buf[ self.iTail ] = el
        self.iTail = (self.iTail + 1) % self.maxlen
        self.hasElements = True

    # pop at back/right
    def pop(self):
        if self.empty(): return None
        self.iTail = (self.iTail - 1 + self.maxlen) % self.maxlen
        el = self._buf[ self.iTail ]
        if self.iHead == self.iTail: self.hasElements = False
        return el

    def first(self):
        return self._buf[ self.iHead ]

    def last(self):
        return self._buf[ self.iTail - 1 ]

    def __str__(self):
        return str(self._buf)


