Hi everyone,

We are happy to announce the first Babeltrace 2.0.0 release candidate!

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
class** API. This interface reduces to a minimum the boiler-plate code needed to
implement a basic message consumer. Just provide a consumption callback
(`consume`) which will be invoked for each batch of messages received by the
component.

Other callbacks can optionally be provided to support more complex use-cases:
  * `initialize`, called once during the initialization phase of the graph.
  * `finalize`, called once during the finalization phase of the graph.

### Automatic source component discovery using TraceCollectionMessageIterator

Integrate the same **automatic source component discovery** mechanism used by
`babeltrace2` to a Python application using the `TraceCollectionMessageIterator`
interface.

Doing so ensures that any Python application using the `bt2` package can benefit
from additional component classes installed on the system from the get go.

### Support for future CTF 2 field and field types

New field classes were added to Babeltrace in order to support new field types
expected to be introduced by CTF 2. These field classes are:

* **Boolean**
  Represents a boolean value.

* **Bit array**
  Represents an array of bits. Use it to express CPU status or flag register
  values. Unlike integer field classes, bit arrays are not interpreted as
  numerical values.

* **Option**
  Represents an optional field. Is equivalent to a variant containing an
  arbitrary field and a second, zero-sized, field.

### User attributes

The CTF 2 metadata format is expected to contain **user attributes**: map values
attached to other objects such as traces, streams, and events. To support this,
user-defined attributes can be associated to the various trace IR objects.

### Error reporting API

Provide rich error reporting using the new **error reporting API**.

When an error is encountered, the error reporting API allows the various actors
interacting through the `libbabeltrace2` library to precisely describe the chain
of events that lead to that error. It is then possible for the library user to
access this list of causes and reduce the time needed to troubleshoot problems.
This is similar to the stack trace carried by exception objects in many
programming languages.

When an error occurs, `babeltrace2` uses the error reporting API to both
report the top-level error itself, but also provides a detailed list of its
causes:

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

### Co-installation with Babeltrace 1.x

In order to ease the transition from Babeltrace 1.x to 2.x, the following
changes were made in order to make it possible to co-install both release
series of Babeltrace:
  * CLI tool renamed to `babeltrace2`.
  * Include directory renamed to `babeltrace2`.
  * Library renamed to `libbabeltrace2`.

### Message Interchange Protocol versioning

Future-proof component classes using **Message Interchange Protocol versioning**.

As Babeltrace evolves, new concepts such as message types, methods, and message
ordering requirements are expected to be introduced in `libbabeltrace2`. To ensure
forward and backward compatibility can be maintained across future releases of
Babeltrace, the concept of Message Interchange Protocol (MIP) is introduced.

If a breaking change is introduced to the protocol between components in
a graph, the MIP version will be increased to announce the new interface.

Component classes can report a range of supported MIP versions to ensure all
components within a graph interact using the same protocol.

### API Changes

#### Const classes in `bt2` Python package

`libbabeltrace2` uses `const` annotations to eliminate a number API of misuses.
As the Python language does not allow expressing the same immutability constraints,
the Python classes were split into constant and mutable variants of each class.
Mutable variants of the classes provide methods to modify the objects whereas
their constant counterpart do not.

#### Packets are now optional

Associating a packet to the streams of a stream class is now optional. Sources
that don't have a concept of event groups no longer have to create artificial
packets to emit events.

#### Rename VERBOSE log level to TRACE

The `VERBOSE` log level has been renamed to `TRACE`.


## Documentation

Manual pages are finalized and reflect the changes introduced in this new release.

* `babeltrace2(1)`
* `babeltrace2-intro(7)`
* `babeltrace2-convert(1)`
* `babeltrace2-help(1)`
* `babeltrace2-list-plugins(1)`
* `babeltrace2-query(1)`
* `babeltrace2-run(1)`
---
* `babeltrace2-query-babeltrace.support-info(7)`
* `babeltrace2-query-babeltrace.trace-infos(7)`
---
* `babeltrace2-plugin-ctf(7)`
* `babeltrace2-source.ctf.fs(7)`
* `babeltrace2-source.ctf.lttng-live(7)`
* `babeltrace2-sink.ctf.fs(7)`
---
* `babeltrace2-plugin-lttng-utils(7)`
* `babeltrace2-filter.lttng-utils.debug-info(7)`
---
* `babeltrace2-plugin-text(7)`
* `babeltrace2-source.text.dmesg(7)`
* `babeltrace2-sink.text.details(7)`
* `babeltrace2-sink.text.pretty(7)`
---
* `babeltrace2-plugin-utils(7)`
* `babeltrace2-sink.utils.counter(7)`
* `babeltrace2-sink.utils.dummy(7)`
* `babeltrace2-filter.utils.muxer(7)`
* `babeltrace2-filter.utils.trimmer(7)`


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
