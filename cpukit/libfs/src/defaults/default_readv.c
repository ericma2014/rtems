/**
 * @file
 *
 * @brief Default Read IO Vector Handler
 *
 * @ingroup LibIOFSHandler
 */

/*
 * COPYRIGHT (c) 1989-2011.
 * On-Line Applications Research Corporation (OAR).
 *
 * Copyright (c) 2013 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Dornierstr. 4
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#if HAVE_CONFIG_H
  #include "config.h"
#endif

#include <rtems/libio_.h>

ssize_t rtems_filesystem_default_readv(
  rtems_libio_t      *iop,
  const struct iovec *iov,
  int                 iovcnt,
  ssize_t             total
)
{
  int v;

  total = 0;

  for ( v = 0 ; v < iovcnt ; ++v ) {
    ssize_t bytes = ( *iop->pathinfo.handlers->read_h )(
      iop,
      iov[ v ].iov_base,
      iov[ v ].iov_len
    );

    if ( bytes < 0 )
      return -1;

    total += bytes;

    if ( bytes != iov[ v ].iov_len )
      break;
  }

  return total;
}