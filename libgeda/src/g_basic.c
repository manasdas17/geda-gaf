/* gEDA - GPL Electronic Design Automation
 * libgeda - gEDA's library
 * Copyright (C) 1998-2000 Ales V. Hvezda
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
#include <sys/stat.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_ASSERT_H
#include <assert.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <gtk/gtk.h>
#include <libguile.h>

#include "defines.h"
#include "struct.h"
#include "globals.h"
#include "o_types.h"

#include "../include/prototype.h"

#ifdef HAVE_LIBDMALLOC
#include <dmalloc.h>
#endif

/* The following code was contributed by thi (with formating changes
 * by Ales) Thanks!
 * Later updated by spe
 *
 * This `load()' is modeled after libguile/load.c, load().
 * Additionally, the most recent form read is saved in case something
 * goes wrong.
 */

/*! \brief */
static SCM most_recently_read_form = SCM_BOOL_F;

/*! \todo Finish function description!!!
 *  \brief Loads a scheme file.
 *  \par Function Description
 *  Loads a scheme file.
 *
 *  \param [in] data  ????
 *  \return SCM_BOOL_T always.
 */
static SCM load (void *data)
{
	SCM load_port = (SCM)data;
	SCM form;
	int eof_found = 0;

	while (!eof_found) {
		form = scm_read(load_port);
		if (SCM_EOF_OBJECT_P(form)) {
			eof_found = 1;
		} else {
			most_recently_read_form = form;
#ifdef HAVE_SCM_EVAL_X_MODULE
  			scm_eval_x (form, scm_current_module() );
#else
			scm_eval_x (form);
#endif
		}
	}

	most_recently_read_form = SCM_BOOL_F;

	return SCM_BOOL_T;
}

/*! \todo Finish function description!!!
 *  \brief The error handler for load.
 *  \par Function Description
 *  The error handler for load
 *
 *  \param [in] data
 *  \param [in] tag
 *  \param [in] throw_args
 *  \return SCM_BOOL_F always.
 */
static SCM load_error_handler(void *data, SCM tag, SCM throw_args)
{
	SCM cur_out = scm_current_output_port ();
	SCM load_port = (SCM)data;
	SCM filename  = scm_port_filename(load_port);

	/*
	 * If misc-error the column and line pointers points
	 * to end of file. Not necessary to confuse user.
	 */

    if (!scm_eq_p (tag, scm_str2symbol ("misc-error"))) {
               scm_display(scm_makfrom0str("Error : "), cur_out);
		scm_display(tag, cur_out);
			
		scm_display(scm_makfrom0str(" [C:"), cur_out);
		scm_display(scm_port_column(load_port), cur_out );
		scm_display(scm_makfrom0str(" L:"), cur_out);
		scm_display(scm_port_line(load_port), cur_out );
		scm_display(scm_makfrom0str("]"), cur_out);
	} else {
		scm_display(scm_makfrom0str("Probably parenthesis mismatch"), 
			    cur_out);

	}

	scm_display(scm_makfrom0str(" in "), cur_out);
	scm_display(filename, cur_out);
	scm_newline(cur_out);

	if (most_recently_read_form != SCM_BOOL_F) {
		scm_display(scm_makfrom0str ("Most recently read form: "),
			    cur_out);
		scm_display(most_recently_read_form, cur_out);
		scm_newline(cur_out);
	}

	return SCM_BOOL_F;
}


/*! \brief Start reading a scheme file
 *  \par Function Description
 *  Start reading a scheme file
 *
 *  \param [in] filename  The file name to start reading from.
 *  \return 0 on success, -1 on failure.
 */
int g_read_file(const gchar *filename)
{
	SCM port;
	SCM eval_result = SCM_BOOL_F;
	char * full_filename;

	if (filename == NULL) {
		return(-1);
	}

	/* get full, absolute path to file */
	full_filename = f_normalize_filename(filename);
	if (full_filename == NULL) {
		return(-1);
	}
	
	if (access(full_filename, R_OK) != 0) {
		s_log_message("Could not find [%s] for interpretion\n",
			      full_filename);
		return(-1);
  	}

	port = scm_open_file(scm_makfrom0str(full_filename), scm_makfrom0str("r"));

	eval_result = scm_internal_catch (SCM_BOOL_T,
                                      (scm_t_catch_body)load,
                                      (void*)port,
                                      (scm_t_catch_handler)load_error_handler,
                                      (void*)port);

	scm_close_port(port);
	
	g_free(full_filename);

	return (eval_result == SCM_BOOL_T);
}