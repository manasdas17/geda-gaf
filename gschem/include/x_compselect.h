/* gEDA - GPL Electronic Design Automation
 * gschem - gEDA Schematic Capture
 * Copyright (C) 1998-2004 Ales V. Hvezda
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#ifndef __X_COMPSELECT_H__
#define __X_COMPSELECT_H__


/*
 * CompselectBehavior
 */

typedef enum {
  COMPSELECT_BEHAVIOR_REFERENCE,
  COMPSELECT_BEHAVIOR_EMBED,
  COMPSELECT_BEHAVIOR_INCLUDE,
} CompselectBehavior;


GType compselect_behavior_get_type (void);
#define COMPSELECT_TYPE_BEHAVIOR  (compselect_behavior_get_type ())


/*
 * Compselect
 */

#define TYPE_COMPSELECT         (compselect_get_type())
#define COMPSELECT(obj)         (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_COMPSELECT, Compselect))
#define COMPSELECT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_COMPSELECT, CompselectClass))
#define IS_COMPSELECT(obj)      (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_COMPSELECT))
#define COMPSELECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_COMPSELECT, CompselectClass))

typedef struct _CompselectClass CompselectClass;
typedef struct _Compselect      Compselect;


struct _CompselectClass {
  GtkDialogClass parent_class;

  guint behavior_changed_signal_id;

};

struct _Compselect {
  GtkDialog parent_instance;

  TOPLEVEL *toplevel;
  
  GtkTreeView *treeview;
  Preview     *preview;
  GtkEntry    *entry_filter;
  GtkComboBox *combobox_behaviors;

};


GType compselect_get_type (void);


#endif /* __X_COMPSEL_H__ */