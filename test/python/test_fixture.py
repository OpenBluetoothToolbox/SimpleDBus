import signal
import asyncio
import dbus_next
from dbus_next.aio import MessageBus
from dbus_next.service import ServiceInterface, method

active = True
bus = None


class Emulator(ServiceInterface):
    def __init__(self, bus):
        self.bus = bus
        super().__init__("simpledbus.tester")

    def export(self):
        self.bus.export("/", self)

    @method()
    def Exit(self):
        """
        Finishes the emulation session by disconnecting from dbus.
        """
        self.bus.disconnect()


def handler(signum, frame):
    global bus
    global active
    bus.disconnect()
    active = False


async def setup():
    global bus
    bus = await MessageBus(bus_type=dbus_next.BusType.SESSION).connect()
    emulator = Emulator(bus)
    emulator.export()
    await bus.request_name("simpledbus.tester.python")


async def main():
    global active
    while active:
        await asyncio.sleep(0.1)


if __name__ == "__main__":
    signal.signal(signal.SIGINT, handler)
    asyncio.get_event_loop().run_until_complete(setup())
    asyncio.get_event_loop().run_until_complete(main())
