#ifndef BABELTRACE_GRAPH_MESSAGE_ITERATOR_H
#define BABELTRACE_GRAPH_MESSAGE_ITERATOR_H

/*
 * Copyright 2017-2018 Philippe Proulx <pproulx@efficios.com>
 * Copyright 2015 Jérémie Galarneau <jeremie.galarneau@efficios.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
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

/* For __BT_FUNC_STATUS_* */
#define __BT_FUNC_STATUS_ENABLE
#include <babeltrace2/func-status.h>
#undef __BT_FUNC_STATUS_ENABLE

#ifdef __cplusplus
extern "C" {
#endif

typedef enum bt_message_iterator_next_status {
	BT_MESSAGE_ITERATOR_NEXT_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_MESSAGE_ITERATOR_NEXT_STATUS_END		= __BT_FUNC_STATUS_END,
	BT_MESSAGE_ITERATOR_NEXT_STATUS_AGAIN		= __BT_FUNC_STATUS_AGAIN,
	BT_MESSAGE_ITERATOR_NEXT_STATUS_ERROR		= __BT_FUNC_STATUS_ERROR,
	BT_MESSAGE_ITERATOR_NEXT_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
} bt_message_iterator_next_status;

typedef enum bt_message_iterator_seek_beginning_status {
	BT_MESSAGE_ITERATOR_SEEK_BEGINNING_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_MESSAGE_ITERATOR_SEEK_BEGINNING_STATUS_END		= __BT_FUNC_STATUS_END,
	BT_MESSAGE_ITERATOR_SEEK_BEGINNING_STATUS_AGAIN		= __BT_FUNC_STATUS_AGAIN,
	BT_MESSAGE_ITERATOR_SEEK_BEGINNING_STATUS_ERROR		= __BT_FUNC_STATUS_ERROR,
	BT_MESSAGE_ITERATOR_SEEK_BEGINNING_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
} bt_message_iterator_seek_beginning_status;

typedef enum bt_message_iterator_seek_ns_from_origin_status {
	BT_MESSAGE_ITERATOR_SEEK_NS_FROM_ORIGIN_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_MESSAGE_ITERATOR_SEEK_NS_FROM_ORIGIN_STATUS_END		= __BT_FUNC_STATUS_END,
	BT_MESSAGE_ITERATOR_SEEK_NS_FROM_ORIGIN_STATUS_AGAIN		= __BT_FUNC_STATUS_AGAIN,
	BT_MESSAGE_ITERATOR_SEEK_NS_FROM_ORIGIN_STATUS_ERROR		= __BT_FUNC_STATUS_ERROR,
	BT_MESSAGE_ITERATOR_SEEK_NS_FROM_ORIGIN_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
} bt_message_iterator_seek_ns_from_origin_status;

#ifdef __cplusplus
}
#endif

#include <babeltrace2/undef-func-status.h>

#endif /* BABELTRACE_GRAPH_MESSAGE_ITERATOR_H */
