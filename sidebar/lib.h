/**
 * @file
 * GUI display the mailboxes in a side panel
 *
 * @authors
 * Copyright (C) 2004 Justin Hibbits <jrh29@po.cwru.edu>
 * Copyright (C) 2004 Thomer M. Gil <mutt@thomer.com>
 * Copyright (C) 2015-2020 Richard Russon <rich@flatcap.org>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MUTT_SIDEBAR_H
#define MUTT_SIDEBAR_H

#include <stdbool.h>
#include "mutt/lib.h"
#include "gui/lib.h"
#include "mutt_commands.h"

struct Mailbox;
struct MuttWindow;
struct NotifyCallback;
struct SidebarWindowData;

/* These Config Variables are only used in sidebar.c */
extern short C_SidebarComponentDepth;
extern char *C_SidebarDelimChars;
extern char *C_SidebarDividerChar;
extern bool  C_SidebarFolderIndent;
extern char *C_SidebarFormat;
extern char *C_SidebarIndentString;
extern bool  C_SidebarNewMailOnly;
extern bool  C_SidebarNonEmptyMailboxOnly;
extern bool  C_SidebarNextNewWrap;
extern bool  C_SidebarOnRight;
extern bool  C_SidebarShortPath;
extern short C_SidebarSortMethod;
extern bool  C_SidebarVisible;
extern short C_SidebarWidth;

extern struct ListHead SidebarWhitelist;

void sb_init    (void);
void sb_shutdown(void);

/**
 * struct SbEntry - Info about folders in the sidebar
 */
struct SbEntry
{
  char box[256];           ///< Formatted Mailbox name
  struct Mailbox *mailbox; ///< Mailbox this represents
  bool is_hidden;          ///< Don't show, e.g. $sidebar_new_mail_only
  enum ColorId color;      ///< Colour to use
};

/**
 * enum DivType - Source of the sidebar divider character
 */
enum DivType
{
  SB_DIV_USER,  ///< User configured using $sidebar_divider_char
  SB_DIV_ASCII, ///< An ASCII vertical bar (pipe)
  SB_DIV_UTF8,  ///< A unicode line-drawing character
};

void            sb_change_mailbox  (struct MuttWindow *win, int op);
bool            select_next        (struct SidebarWindowData *wdata);
void            sb_draw            (struct MuttWindow *win);
struct Mailbox *sb_get_highlight   (struct MuttWindow *win);
void            sb_notify_mailbox  (struct MuttWindow *win, struct SidebarWindowData *wdata, struct Mailbox *m, bool created);
void            sb_set_open_mailbox(struct MuttWindow *win, struct Mailbox *m);
void            sb_win_init        (struct MuttWindow *dlg);
void            sb_win_shutdown    (struct MuttWindow *dlg);

enum CommandResult sb_parse_unwhitelist(struct Buffer *buf, struct Buffer *s, intptr_t data, struct Buffer *err);
enum CommandResult sb_parse_whitelist  (struct Buffer *buf, struct Buffer *s, intptr_t data, struct Buffer *err);

#endif /* MUTT_SIDEBAR_H */
