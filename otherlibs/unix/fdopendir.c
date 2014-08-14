/***********************************************************************/
/*                                                                     */
/*                                OCaml                                */
/*                                                                     */
/*            Xavier Leroy, projet Cristal, INRIA Rocquencourt         */
/*                                                                     */
/*  Copyright 1996 Institut National de Recherche en Informatique et   */
/*  en Automatique.  All rights reserved.  This file is distributed    */
/*  under the terms of the GNU Library General Public License, with    */
/*  the special exception on linking described in file ../../LICENSE.  */
/*                                                                     */
/***********************************************************************/

#include <mlvalues.h>
#include <memory.h>
#include <alloc.h>
#include <signals.h>
#include "unixsupport.h"
#include <sys/types.h>
#ifdef HAS_DIRENT
#include <dirent.h>
#else
#include <sys/dir.h>
#endif

#include <fail.h>
#include <errno.h>
// TODO needed?

CAMLprim value unix_fdopendir(value vd)
{
  CAMLparam1(vd);
  DIR * d;
  value res;

  d = DIR_Val(vd);
  if (d == (DIR *) NULL) unix_error(EBADF, "fdopendir", Nothing);

  caml_enter_blocking_section();
  d = fdopendir((DIR *) vd);
  caml_leave_blocking_section();
  caml_stat_free(p);
  if (d == (DIR *) NULL) uerror("fdopendir", vd); // TODO look up def of uerror - are we passing vd to a char * ?
  res = alloc_small(1, Abstract_tag);
  DIR_Val(res) = d;
  CAMLreturn(res);
}

