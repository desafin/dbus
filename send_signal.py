# send_signal.py
import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GLib

class MySignal(dbus.service.Object):
    def __init__(self, bus_name):
        dbus.service.Object.__init__(self, bus_name, '/com/example/MySignal')

    @dbus.service.signal('com.example.MySignal')
    def HelloWorld(self, message):
        pass

def main():
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    session_bus = dbus.SessionBus()
    bus_name = dbus.service.BusName('com.example.MySignal', session_bus)
    mysignal = MySignal(bus_name)

    mysignal.HelloWorld("Hello from Python!")

    loop = GLib.MainLoop()
    loop.run()

if __name__ == '__main__':
    main()
