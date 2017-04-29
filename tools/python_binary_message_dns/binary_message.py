import struct


class Field(object):
    def pack(self, buffer, offset):
        self.packer.pack_into(buffer, offset, self.value)

    def unpack(self, buffer, offset):
        self.value = self.packer.unpack_from(buffer, offset)[0]

    def size(self):
        return self.packer.size

    def set(self, value):
        self.value = value

    def get(self):
        return self.value


class UInt8(Field):
    packer = struct.Struct("B")

    def __init__(self, initValue=0):
        super(UInt8, self).__init__()
        self.value = initValue


class UInt32(Field):
    packer = struct.Struct("I")

    def __init__(self, initValue=0):
        super(UInt32, self).__init__()
        self.value = initValue


class UInt32Net(Field):
    packer = struct.Struct("!I")

    def __init__(self, initValue=0):
        super(UInt32Net, self).__init__()
        self.value = initValue


class UInt16Net(Field):
    packer = struct.Struct("!H")

    def __init__(self, initValue=0):
        super(UInt16Net, self).__init__()
        self.value = initValue


class VariableString(Field):
    packer = struct.Struct("s")

    def __init__(self, initValue=""):
        super(VariableString, self).__init__()
        self.value = initValue
        self.packer = struct.Struct(str(len(self.value)) + "s")

    def set(self, newValue):
        self.value = newValue
        self.packer = struct.Struct(str(len(self.value)) + "s")

    def size(self):
        return len(self.value)


class Structure(object):
    def __init__(self):
        self.members = []

    def pack(self, buffer, offset):
        for field in self.members:
            field.pack(buffer, offset)
            offset += field.size()

    def unpack(self, buffer, offset):
        for field in self.members:
            field.unpack(buffer, offset)
            offset += field.size()

    def size(self):
        s = 0
        for field in self.members:
            s += field.size()
        return s


def setBits(dest, offset, length, newValue):
    mask = (1 << length) - 1
    mask = mask << offset
    mask = ~mask
    dest = (dest & mask)
    return dest | (newValue << offset)


def getBits(value, offset, length):
    mask = (1 << length) - 1
    mask = mask << offset
    return (value & mask) >> offset

