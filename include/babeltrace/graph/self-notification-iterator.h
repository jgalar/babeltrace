#ifndef BABELTRACE_GRAPH_SELF_NOTIFICATION_ITERATOR_H
#define BABELTRACE_GRAPH_SELF_NOTIFICATION_ITERATOR_H

/*
 * Copyright 2017 Philippe Proulx <pproulx@efficios.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* For BT_NOTIFICATION_ITERATOR_STATUS_* */
#include <babeltrace/graph/notification-iterator.h>

#ifdef __cplusplus
extern "C" {
#endif

struct bt_self_component;
struct bt_self_notification_iterator;

enum bt_self_notification_iterator_status {
	BT_SELF_NOTIFICATION_ITERATOR_STATUS_OK = BT_NOTIFICATION_ITERATOR_STATUS_OK,
	BT_SELF_NOTIFICATION_ITERATOR_STATUS_END = BT_NOTIFICATION_ITERATOR_STATUS_END,
	BT_SELF_NOTIFICATION_ITERATOR_STATUS_AGAIN = BT_NOTIFICATION_ITERATOR_STATUS_AGAIN,
	BT_SELF_NOTIFICATION_ITERATOR_STATUS_ERROR = BT_NOTIFICATION_ITERATOR_STATUS_ERROR,
	BT_SELF_NOTIFICATION_ITERATOR_STATUS_NOMEM = BT_NOTIFICATION_ITERATOR_STATUS_NOMEM,
};

extern struct bt_self_component *
bt_self_notification_iterator_borrow_component(
		struct bt_self_notification_iterator *notification_iterator);

extern struct bt_self_port_output *
bt_self_notification_iterator_borrow_port(
		struct bt_self_notification_iterator *notification_iterator);

extern void bt_self_notification_iterator_set_data(
		struct bt_self_notification_iterator *notification_iterator,
		void *user_data);

extern void *bt_self_notification_iterator_get_data(
		const struct bt_self_notification_iterator *notification_iterator);

#ifdef __cplusplus
}
#endif

#endif /* BABELTRACE_GRAPH_SELF_NOTIFICATION_ITERATOR_H */
