# The MIT License (MIT)
#
# Copyright (c) 2017 Philippe Proulx <pproulx@efficios.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

from bt2 import native_bt, object, utils
import bt2
import uuid as uuidp


class ClockClassOffset:
    def __init__(self, seconds=0, cycles=0):
        utils._check_int64(seconds)
        utils._check_int64(cycles)
        self._seconds = seconds
        self._cycles = cycles

    @property
    def seconds(self):
        return self._seconds

    @property
    def cycles(self):
        return self._cycles

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            # not comparing apples to apples
            return False

        return (self.seconds, self.cycles) == (other.seconds, other.cycles)


class _ClockClass(object._SharedObject):
    _get_ref = staticmethod(native_bt.clock_class_get_ref)
    _put_ref = staticmethod(native_bt.clock_class_put_ref)

    @property
    def name(self):
        return native_bt.clock_class_get_name(self._ptr)

    def _name(self, name):
        utils._check_str(name)
        status = native_bt.clock_class_set_name(self._ptr, name)
        utils._handle_func_status(status,
                                  "cannot set clock class object's name")

    _name = property(fset=_name)

    @property
    def description(self):
        return native_bt.clock_class_get_description(self._ptr)

    def _description(self, description):
        utils._check_str(description)
        status = native_bt.clock_class_set_description(self._ptr, description)
        utils._handle_func_status(status,
                                  "cannot set clock class object's description")

    _description = property(fset=_description)

    @property
    def frequency(self):
        return native_bt.clock_class_get_frequency(self._ptr)

    def _frequency(self, frequency):
        utils._check_uint64(frequency)
        native_bt.clock_class_set_frequency(self._ptr, frequency)

    _frequency = property(fset=_frequency)

    @property
    def precision(self):
        precision = native_bt.clock_class_get_precision(self._ptr)
        return precision

    def _precision(self, precision):
        utils._check_uint64(precision)
        native_bt.clock_class_set_precision(self._ptr, precision)

    _precision = property(fset=_precision)

    @property
    def offset(self):
        offset_s, offset_cycles = native_bt.clock_class_get_offset(self._ptr)
        return ClockClassOffset(offset_s, offset_cycles)

    def _offset(self, offset):
        utils._check_type(offset, ClockClassOffset)
        native_bt.clock_class_set_offset(self._ptr, offset.seconds, offset.cycles)

    _offset = property(fset=_offset)

    @property
    def origin_is_unix_epoch(self):
        return native_bt.clock_class_origin_is_unix_epoch(self._ptr)

    def _origin_is_unix_epoch(self, origin_is_unix_epoch):
        utils._check_bool(origin_is_unix_epoch)
        native_bt.clock_class_set_origin_is_unix_epoch(self._ptr, int(origin_is_unix_epoch))

    _origin_is_unix_epoch = property(fset=_origin_is_unix_epoch)

    @property
    def uuid(self):
        uuid_bytes = native_bt.clock_class_get_uuid(self._ptr)

        if uuid_bytes is None:
            return

        return uuidp.UUID(bytes=uuid_bytes)

    def _uuid(self, uuid):
        utils._check_type(uuid, uuidp.UUID)
        native_bt.clock_class_set_uuid(self._ptr, uuid.bytes)

    _uuid = property(fset=_uuid)

    def cycles_to_ns_from_origin(self, cycles):
        utils._check_uint64(cycles)
        status, ns = native_bt.clock_class_cycles_to_ns_from_origin(self._ptr, cycles)
        error_msg = "cannot convert clock value to nanoseconds from origin for given clock class"
        utils._handle_func_status(status, error_msg)
        return ns
