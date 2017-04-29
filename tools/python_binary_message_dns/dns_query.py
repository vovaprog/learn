import ctypes
import socket
from binary_message import *


class DnsFlags(UInt16Net):
    def __init__(self):
        super(DnsFlags, self).__init__()

    def setResponse(self, x):
        self.value = setBits(self.value, 15, 1, x)

    def setOpcode(self, x):
        self.value = setBits(self.value, 11, 4, x)

    def setTruncated(self, x):
        self.value = setBits(self.value, 9, 1, x)

    def setRecursionDesired(self, x):
        self.value = setBits(self.value, 8, 1, x)


class DnsNamePart(Structure):
    def __init__(self, arg=""):
        super(DnsNamePart, self).__init__()
        self.length = UInt8(len(arg))
        self.name = VariableString(arg)
        self.members.extend([self.length, self.name])

    def unpack(self, buffer, offset):
        self.length.unpack(buffer, offset)
        offset += self.length.size()
        self.name.packer = struct.Struct(str(self.length.get()) + "s")
        self.name.unpack(buffer, offset)


class DnsName(Structure):
    def __init__(self):
        super(DnsName, self).__init__()

    def set(self, value):
        self.members = []
        words = value.split(".")
        for word in words:
            self.members.append(DnsNamePart(word))
        self.members.append(UInt8(0))

    def unpack(self, buffer, offset):
        self.members = []
        while True:
            wordLength = UInt8()
            wordLength.unpack(buffer, offset)
            if wordLength.get() == 0:
                self.members.append(wordLength)
                break
            namePart = DnsNamePart()
            namePart.unpack(buffer, offset)
            self.members.append(namePart)
            offset += namePart.size()


class DnsQuestion(Structure):
    def __init__(self):
        super(DnsQuestion, self).__init__()

        self.dnsName = DnsName()
        self.type = UInt16Net()
        self.cls = UInt16Net()

        self.members.extend([self.dnsName, self.type, self.cls])

    def set(self, value):
        self.dnsName.set(value)
        self.type.set(1)
        self.cls.set(1)


class DnsQuery(Structure):
    def __init__(self):
        super(DnsQuery, self).__init__()

        self.id = UInt16Net()
        self.flags = DnsFlags()
        self.questions = UInt16Net()
        self.answers = UInt16Net()
        self.authorityResources = UInt16Net()
        self.additionalResources = UInt16Net()
        self.question = DnsQuestion()

        self.members.extend([self.id, self.flags, self.questions,
                             self.answers, self.authorityResources,
                             self.additionalResources, self.question])


class IpAdress(UInt32Net):
    def __init__(self):
        super(UInt32Net, self).__init__()

    def toString(self):
        output = str(getBits(self.value, 24, 8))
        output += "." + str(getBits(self.value, 16, 8))
        output += "." + str(getBits(self.value, 8, 8))
        output += "." + str(getBits(self.value, 0, 8))
        return output


class DnsAnswer(Structure):
    def __init__(self):
        super(DnsAnswer, self).__init__()

        self.name = DnsName()
        self.type = UInt16Net()
        self.cls = UInt16Net()
        self.ttl = UInt32Net()
        self.dataLength = UInt16Net()
        self.ipAddress = IpAdress()

        self.members.extend([self.name, self.type, self.cls, self.ttl, self.dataLength, self.ipAddress])


class DnsResponse(Structure):
    def __init__(self):
        super(DnsResponse, self).__init__()

        self.id = UInt16Net()
        self.flags = DnsFlags()
        self.questions = UInt16Net()
        self.answers = UInt16Net()
        self.authorityResources = UInt16Net()
        self.additionalResources = UInt16Net()
        self.question = DnsQuestion()
        self.answer = DnsAnswer()

        self.members.extend([self.id, self.flags, self.questions,
                             self.answers, self.authorityResources,
                             self.additionalResources, self.question, self.answer])

    def unpack(self, buffer, offset):
        self.id.unpack(buffer, offset)
        offset += self.id.size()
        self.flags.unpack(buffer, offset)
        offset += self.flags.size()
        self.questions.unpack(buffer, offset)
        offset += self.questions.size()
        self.answers.unpack(buffer, offset)
        offset += self.answers.size()
        self.authorityResources.unpack(buffer, offset)
        offset += self.authorityResources.size()
        self.additionalResources.unpack(buffer, offset)
        offset += self.additionalResources.size()
        self.question.unpack(buffer, offset)
        offset += self.question.size()
        for i in range(self.answers.get()):
            ans = DnsAnswer()
            ans.unpack(buffer, offset)
            offset += ans.size()
            if ans.type.get() == 1:
                break


def prepareDnsQuery(queryString):
    query = DnsQuery()

    query.id.set(0xaabb)

    query.flags.setResponse(0)  # is a query
    query.flags.setOpcode(0)  # standard query
    query.flags.setTruncated(0)  # not truncated
    query.flags.setRecursionDesired(1)  # use recursion

    query.questions.set(1)
    query.answers.set(0)
    query.authorityResources.set(0)
    query.additionalResources.set(0)

    query.question.set(queryString)

    return query


query = prepareDnsQuery("www.ya.ru")

buffer = ctypes.create_string_buffer(query.size())
query.pack(buffer, 0)

open('./_request_.bin', 'wb').write(buffer)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

ipAddress = "192.168.1.1"
sock.sendto(buffer, (ipAddress, 53))

responseBuffer, addr = sock.recvfrom(10000)

open('./_response_.bin', 'wb').write(responseBuffer)

response = DnsResponse()
response.unpack(responseBuffer, 0)

print response.answer.ipAddress.toString()

