Each line is a new binding. It starts with the binding name,
which is followed by the numerical representation of the event 
type enumeration and the code for the event seperated by a colon.
Every different event key:value pair is separated by spaces, as
well as the binding name and the beginning of the events.

ActionName(BindName)-EventType-EventCode(KeyCode/MouseCode/JoystickCode etc.)

Print_Hello 6:20


Knowing when to use which types of events is important even in this design. Let's
say, for example, that you only want a callback to be called once for a binding that
involves the left shift and the R key. You wouldn't define both the event types as
Keyboard, because that would keep invoking the callback method as long as these
keys are down. You also don't want to define both of them as KeyDown events,
because that would mean that both of these events would have to be registered at the
same time, which, when holding down multiple keys, is likely not going to happen
because of the screen refresh rate. The correct way to use this is mixing the Keyboard
and KeyDown events so that the very last key to be pressed is the KeyDown type and
the rest of the keys will be Keyboard types. In our example, it means that we would
have the left shift key being checked through the sf::Keyboard class, while the
R key would default to an event being dispatched. That might sound odd at first,
however, consider the famous example of the key combination Ctrl + Alt + Del on
your computer. It works that way, but if you hold the keys in reverse order, it would
do nothing. If we were implementing this functionality, we'd most likely make sure
that the Ctrl and Alt keys are always checked through the sf::Keyboard class, while
the Del key is registered through the event polling.