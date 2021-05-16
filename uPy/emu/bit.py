# emulib – bit manipulation


def toggle(data, idx):
    """ toggle bit at index idx """
    return data ^ (1 << idx)

def set(data, idx):
    """ set bit at index idx """
    return data | (1<<idx)

def clear(data, idx):
    """ clear bit at index idx """
    return data & ~(1<<idx)

def setMask(data, mask):
    return data | mask

def clearMask(data, mask):
    return data & ~(mask)

def toggleMask(data, mask):
    return data ^ mask
