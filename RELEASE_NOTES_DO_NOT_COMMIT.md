Hi everyone!

We are happy to announce the release of Babeltrace 2.0.0-rc1.

# What's new since Babeltrace 2.0-pre5?

## Command-line interface

### Automatic source component discovery

With the new `convert` command's **automatic source component discovery**
feature, specify a path, URI, or arbitrary string to let `babeltrace2` find the
most appropriate components to use:

    $ babeltrace2 /path/to/ctf/trace
    $ babeltrace2 net://localhost/host/myhost/my-session

This means you don't need to create an explicit component with the `--component`
option most of the time.

Behind the scenes, this feature queries the `babeltrace.support-info` object
from all known component classes: a component class can reply with a confidence
score to indicate its ability to handle a given path or custom string. See
the new `babeltrace2-query-babeltrace.support-info(7)` manual page.

For example, a `source.ctf.fs` (CTF trace directory source) component class
replies to this query whether or not the given path looks like a CTF trace
directory.

NOTE: Source component classes do not have to implement the
`babeltrace.support-info` query. If a component class does not implement this
query, it will not be considered by the automatic source component discovery
algorithm. In that case, you must instantiate such a component class explicitly
with the `--component` option.

## Plugins

### `sink.text.details` component class

Print detailed information about all messages flowing through a trace
processing graph using the **`sink.text.details`** component class.

Components instantiated from this component class can be used to easily
inspect messages flowing at any point of a graph and make it easy to test
and troubleshoot other component classes.

### Support for lttng-crash and malformed CTF traces

A number of work-arounds were added to `src.ctf.fs` in order to
transparently support non-compliant CTF traces produced by some versions of
the LTTng-UST, LTTng-Modules, and barectf tracers.

## Library and Python bindings

### Simple sink component class

Implement a sink component class easily using the **simple sink component
class** API. This interface reduces the boiler-plate code needed to implement a
basic message consumer to a minimum. Just provide a consumption callback which
will be invoked for each batch of messages received by the component.


Other callbacks can optionally be implemented to support more complex use-cases:
  * Initialize (optional): Called once during the initialization phase of the
    graph.

  * Finalize (optional): Called once during the finalization phase of the
    graph.


### Automatic source component discovery using TraceCollectionMessageIterator

Integrate the same **automatic source component discovery** mechanism used by
`babeltrace2` to a Python application using the `TraceCollectionMessageIterator`
interface.




### Support for future CTF 2 field and field types
Some new field classes were added to Babeltrace in order to support the new
field types that are expected to be introduced by CTF 2. These field classes
are:

* Boolean: Used to represent trivial boolean value.

* Bit array: Used to represent an array of bits. This is useful to represent
  CPU status or flag register values. Unlike integer field classes, bit arrays
  are not interpreted as numerical values.

* Option: Used to represent an optional field. It is equivalent to a variant
  containing an arbitrary field and a second, zero-sized field.

### User attributes
The CTF 2 metadata is expected to contain user attributes, which are map values
attached to the various objects (such as traces, streams and events). To support
this, Babeltrace allows components to attach user-defined attributes to the
various trace IR objects.

### Error reporting API
In case of error, the error reporting API allows the different actors of the
library to precisely describe the chain of events that lead to that error. It is
then possible for the library user to access this list of causes, which helps
troubleshooting problems. This is similar to a stack trace carried by an
exception object in other languages.

When an error occurs when using the CLI, the error and all its causes are
printed:

```
ERROR:    [Babeltrace CLI] (babeltrace2.c:2546)
  Graph failed to complete successfully
CAUSED BY [Babeltrace library] (graph.c:604)
  Component's "consume" method failed: ..., comp-name="sink.text.details", ...
CAUSED BY [Babeltrace library] (iterator.c:889)
  Component input port message iterator's "next" method failed: ..., iter-upstream-comp-class-name="debug-info", ...
CAUSED BY [Babeltrace library] (iterator.c:889)
  Component input port message iterator's "next" method failed: ..., iter-upstream-comp-name="muxer", ...
CAUSED BY [Babeltrace library] (iterator.c:889)
  Component input port message iterator's "next" method failed: ..., iter-upstream-comp-class-name="MyFirstSource", ...
CAUSED BY [src.demo.MyFirstSource (some-name): 'source.demo.MyFirstSource'] (bt2/native_bt_log_and_append_error.h:100)
  Traceback (most recent call last):
    File "/usr/local/lib/python3.6/dist-packages/bt2/message_iterator.py", line 151, in _bt_next_from_native
      msg = next(self)
    File "./bt_plugin_foo.py", line 33, in __next__
      raise Exception
  Exception
```

### Message Interchange Protocol version
As Babeltrace evolves, new concepts (message types, methods, message ordering
requirements, etc.) may be added to the trace IR. To ensure forward and
backward compatibility, the concept of Message Interchange Protocol (MIP) was
introduced. When a breaking changes happen in the protocol, the MIP version
will be increased so to express new requirements. Component classes can report
which versions of the protocol they support, ensuring that all components in a
graph understand each other.

## API changes

### Const classes in `bt2` Python package
Since the Python language does not allow expressing the same const-correctness
as the C API does, the Python classes representing the types of the API were
split in const and non-const versions. Non-const versions of the object provide
methods for mutating the objects, while the const versions do not.

### Co-installation with Babeltrace 1.x
In order to facilitate the transition from Babeltrace 1.x to 2.x, the following
changes were made in order to make it possible to co-install both release
series of Babeltrace:
* Rename the CLI tool to `babeltrace2`.
* Rename the include directory to `babeltrace2`.
* Rename the library to `libbabeltrace2`.

### Packets are now optional
It's now optional for the streams of a given stream class to support the
concept of packets. Sources that don't have the concept of
grouping events into packets no longer have to create artificial packets to
emit events.

### Rename VERBOSE log level to TRACE
The VERBOSE log level has been renamed to TRACE.


## Documentation










# What's new since 1.5
## Trace processing graphs
Babeltrace 2.0 introduces the concept of trace processing graphs. Such graphs
consist of multiple reusable components connected together, which lets users
address their various different trace reading and analyzing needs.

## Provided component classes
Babeltrace 2.0 provides the following component classes out of the box:
* **CTF filesystem source (source.ctf.fs)**: Read CTF traces from the file system.
* **LTTng live source (source.ctf.lttng-live)**: Read CTF traces from the network
    using the `lttng-live` protocol.
* **Dmesg source (source.text.dmesg)**: Read `dmesg`-style log file from the file
    system or standard input.
* **Trace trimmer (filter.utils.trimmer)**: Keep messages that occur within a
    specific time range.
* **Trace muxer (filter.utils.muxer)**: Sort messages from multiple sources to
    a single output port by time.
* **Debug information filter (filter.lttng-utils.debug-info)**: Augment compatible
    events with debugging information.
* **CTF filesystem sink (sink.ctf.fs)**: Write CTF traces to the file system.
* **Text pretty-printer (sink.text.pretty)**: Pretty print messages.
* **Dummy sink (sink.utils.dummy)**: Consume messages and discard them.
* **Counter sink (sink.utils.counter)**: Count messages and print the results.
* **Details sink (sink.text.details)**: Print messages with all available details.

## Reading of multiple CTF traces with same UUID
Babeltrace now treats multiple input CTF traces that share the same UUID as a
single trace. This is especially useful for reading traces produced with the
tracing session rotation feature introduced by LTTng 2.11.

## Developer mode
When Babeltrace 2 is built in this mode, a large number of checks are added to
enforce most preconditions required by the API.

This makes it easier to develop and test new plugins while ensuring that they
honour the contract of the various functions they use. Since components are now
assumed to have been tested in this mode by their authors, the release
configuration of Babeltrace 2 can eschew most precondition checks at run time,
resulting in improved performance.

To build Babeltrace 2 in this mode and test your own plugins, set the
`BABELTRACE_DEV_MODE` environment variable `1` at configure time, for
example:

    BABELTRACE_DEV_MODE=1 ./configure

## Colors
The Babeltrace CLI now use colors whenever the standard output is an
interactive terminal. Plugin developers can use `bt_common_colors_supported()`
to know is this feature is supported and use the `bt_common_color_*()`
functions to change background and foreground colors as well as boldness.

## LTTng live "subscribe" mode
It is now possible to connect to a LTTng-Relay daemon in "subscribe" mode. To
achieve this a `src.ctf.lttng-live` must be instantiated with the
`session-not-found-action="continue"` parameter. In this mode, the source will
attempt to consume an LTTng relay daemon's session and retry periodically if
the session does not exist.

This is in contrast with the default Babeltrace 1.X behaviour which will exit
(with success) immediately if the session to consume does not exist on the
LTTng relay daemon.

The following command demonstrates the use of this new mode:

babeltrace2 net://relayhost/host/tgthost/my-session \
           --params='session-not-found-action="continue"'

## API changes
The API has been entirely been revamped.
