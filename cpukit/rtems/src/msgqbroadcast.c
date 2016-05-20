/**
 *  @file
 *
 *  @brief RTEMS Broadcast Message Queue
 *  @ingroup ClassicMessageQueue
 */

/*
 *  COPYRIGHT (c) 1989-2014.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/rtems/messageimpl.h>

rtems_status_code rtems_message_queue_broadcast(
  rtems_id    id,
  const void *buffer,
  size_t      size,
  uint32_t   *count
)
{
  Message_queue_Control     *the_message_queue;
  ISR_lock_Context           lock_context;
  CORE_message_queue_Status  status;

  if ( buffer == NULL ) {
    return RTEMS_INVALID_ADDRESS;
  }

  if ( count == NULL ) {
    return RTEMS_INVALID_ADDRESS;
  }

  the_message_queue = _Message_queue_Get( id, &lock_context );

  if ( the_message_queue == NULL ) {
#if defined(RTEMS_MULTIPROCESSING)
    _Message_queue_MP_Broadcast( id, buffer, size, count );
#else
    return RTEMS_INVALID_ID;
#endif
  }

  status = _CORE_message_queue_Broadcast(
    &the_message_queue->message_queue,
    buffer,
    size,
    _Message_queue_Core_message_queue_mp_support,
    id,
    count,
    &lock_context
  );
  return _Message_queue_Translate_core_message_queue_return_code( status );
}
