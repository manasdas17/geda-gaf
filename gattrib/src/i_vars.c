/* gEDA - GPL Electronic Design Automation
 * gattrib -- gEDA component and net attribute manipulation using spreadsheet.
 * Copyright (C) 2003-2008 Stuart D. Brorson.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 USA
 */

#include <config.h>

#include <stdio.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif



/*------------------------------------------------------------------
 * Gattrib specific includes.  Note that include order is important.
 *------------------------------------------------------------------*/
#include <libgeda/libgeda.h>       /* geda library fcns  */
#include "../include/struct.h"     /* typdef and struct declarations */
#include "../include/prototype.h"  /* function prototypes */
#include "../include/globals.h"

#include "../include/i_vars.h"

#ifdef HAVE_LIBDMALLOC
#include <dmalloc.h>
#endif



/*------------------------------------------------------------------
 * Define the vars we'll use later
 *------------------------------------------------------------------*/
int   default_paper_width = 11000; /* letter size */
int   default_paper_height = 85000;


/*------------------------------------------------------------------
 * This initializes the vars in pr_current.
 *------------------------------------------------------------------*/
void i_vars_set(TOPLEVEL * pr_current)
{
  i_vars_libgeda_set(pr_current);

  pr_current->paper_width = default_paper_width;
  pr_current->paper_height = default_paper_height;
}
