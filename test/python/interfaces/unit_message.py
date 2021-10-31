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
