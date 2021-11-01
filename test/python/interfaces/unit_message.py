from dbus_next.service import ServiceInterface, method


class MessageUnit(ServiceInterface):
    def __init__(self, bus):
        self.bus = bus
        super().__init__("simpledbus.tester.message")

    def export(self):
        self.bus.export("/", self)

    @method()
    def Reset(self):
        """
        Resets the state of the tester.
        """
        pass

    @method()
    def SendReceiveBoolean(self, value: "b") -> "b":
        return value

    @method()
    def SendReceiveByte(self, value: "y") -> "y":
        return value

    @method()
    def SendReceiveInt16(self, value: "n") -> "n":
        return value

    @method()
    def SendReceiveUint16(self, value: "q") -> "q":
        return value

    @method()
    def SendReceiveInt32(self, value: "i") -> "i":
        return value

    @method()
    def SendReceiveUint32(self, value: "u") -> "u":
        return value

    @method()
    def SendReceiveInt64(self, value: "x") -> "x":
        return value

    @method()
    def SendReceiveUint64(self, value: "t") -> "t":
        return value

    @method()
    def SendReceiveDouble(self, value: "d") -> "d":
        return value

    @method()
    def SendReceiveString(self, value: "s") -> "s":
        return value

    @method()
    def SendReceiveObjectPath(self, value: "o") -> "o":
        return value

    @method()
    def SendReceiveSignature(self, value: "g") -> "g":
        return value

    @method()
    def SendReceiveArrayInt32(self, value: "ai") -> "ai":
        return value

    @method()
    def SendReceiveArrayString(self, value: "as") -> "as":
        return value

    @method()
    def SendReceiveDictInt32(self, value: "a{iv}") -> "a{iv}":
        print(f"Received {value}")
        return value

    @method()
    def SendReceiveDictString(self, value: "a{sv}") -> "a{sv}":
        print(f"Received {value}")
        return value
