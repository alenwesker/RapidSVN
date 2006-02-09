/*
 * ====================================================================
 * Copyright (c) 2002-2006 The RapidSvn Group.  All rights reserved.
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
 * along with this program (in the file GPL.txt); if not, write to 
 * the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */
// svncpp
#include "svncpp/url.hpp"

// wx
#include "wx/wx.h"
#include "wx/filename.h"
#include "wx/intl.h"

// app
#include "external_program_action.hpp"
#include "preferences.hpp"
#include "utils.hpp"
#include "verblist.hpp"


ExternalProgramAction::ExternalProgramAction (
  wxWindow * parent, long verb_id, bool treat_as_folder) 
 : Action (parent, _("Execute"), GetBaseFlags ()), 
   m_verb_id (verb_id), m_treat_as_folder (treat_as_folder)
{
}


bool
ExternalProgramAction::Prepare ()
{
  return Action::Prepare ();
}

bool
ExternalProgramAction::Perform ()
{
  VerbList verb_list;
  wxBusyCursor busy_cursor;

  // The actual target
  svn::Path path = GetTarget ();
  if (path.isUrl ())
    path = GetPathAsTempFile(path);
  
  wxString target_str = Utf8ToLocal (path.c_str ());
  wxFileName target = target_str;

  // The target we'll pass to the external program
  wxString target_document = target.GetFullPath ();
  Preferences prefs;

  if (m_treat_as_folder)
  {
    // Assuming target is a folder: use only folder part of filename if target
    // is really a file
    if (!wxDirExists(target_document))
      target_document = target.GetPath();
  }

  // Get verbs from the OS
  verb_list.InitFromDocument (target_document, m_treat_as_folder);

  // An explicit verb was chose that is not available
  if ((m_verb_id >= 0) && ((size_t)m_verb_id > verb_list.GetCount()))
  {
    // TODO: Trace this?
    return false;
  }

  if (m_treat_as_folder)
  {
    if (verb_list.GetCount () && !((m_verb_id == -1) 
      && prefs.explorerAlways))
    {
      verb_list.Launch ((m_verb_id == -1 ? 0 : m_verb_id));      
    }
    else
    {
      wxString args (prefs.explorerArgs);
      TrimString (args);

      if (args.Length () == 0)
        args = wxT("\"") + target_document + wxT("\"");
      else
        args.Replace (wxT("%1"), target_document, true);
    
      wxExecute (prefs.explorer + wxT(" ") + args);
    }
  }
  else
  {
    if (verb_list.GetCount () && !((m_verb_id == -1) 
      && prefs.editorAlways))
    {
      verb_list.Launch ((m_verb_id == -1 ? 0 : m_verb_id));      
    }
    else
    {
      wxString args (prefs.editorArgs);
      TrimString (args);

      if (args.Length () == 0)
        args = wxT("\"") + target_document + wxT("\"");
      else
        args.Replace (wxT("%1"), target_document, true);
   
      wxExecute (prefs.editor + wxT(" ") + args);
    }
  }

  return true;
}

/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */
