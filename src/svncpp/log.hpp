/*
 * ====================================================================
 * Copyright (c) 2002 The RapidSvn Group.  All rights reserved.
 *
 * This software is licensed as described in the file LICENSE.txt,
 * which you should have received as part of this distribution.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */

#ifndef _SVNCPP_LOG_H_
#define _SVNCPP_LOG_H_

#ifdef WIN32
// Eliminate worthless win32 warnings
#pragma warning(disable: 4786)
#endif

// stl
#include <vector>
#include <string>

// svncpp
#include "auth.hpp"

namespace svn
{
  // forward declarations
  class Revision;

  /**
   * Iterator class for log entries on a file.
   */
  class Log : public svn::Auth
  {
  private:
    std::vector<long> m_revision;
    std::vector<std::string> m_author;
    std::vector<std::string> m_date;
    std::vector<std::string> m_message;
    bool versioned;

    /**
     * Resets all of the global variables.
     */
    void reset ();

    /**
     * Records where the iterator is currently set to.
     */
    int cursor;

    /**
     * Number of elements in the result set.
     */
    int size;

  public:
    Log();
    ~Log();

    /**
     * Loads the log messages result set, clearing old result sets. 
     * This usually requires authentication. 
     * You can use the constants Revision::START and
     * Revision::HEAD
     *
     * @see Auth
     *
     * @param path
     * @param revisionStart
     * @param revisionEnd                    
     */
    void loadPath (const char * path, const Revision & revisionStart, 
                   const Revision & revisionEnd);

    /**
     * Moves to the next row in the log result set.
     * @returns true if the cursor is in the result set.
     */
    bool next ();

    /**
     * Moves to the previous row in the log result set.
     * @returns true if the cursor is in the result set.
     */
    bool previous ();

    /**
     * Moves to the last row in the log result set.
     * @returns true if the cursor is in the result set.
     */
    bool last ();

    /**
     * Moves to the first row in the log result set.
     * @returns true if the cursor is in the result set.
     */
    bool first ();

    /**
     * Moves to the cursor before first row in the log result set.
     */
    void beforeFirst ();

    /**
     * Returns the log message of the current result set.
     */
    const char * message ();

    /**
     * Returns the log date of the current result set.
     */
    const char * date ();

    /**
     * Formats the output of a Subversion date.
     * @param dateText Subversion date text. Takes the result of the 
     *                 date() method.
     * @param format template for formatting the returned date.
     */
    const char * formatDate (const char * dateText, const char * format);

    /**
     * Returns the log author of the current result set.
     */
    const char * author ();

    /**
     * Returns the revision of the current result set.
     */
    svn_revnum_t revision ();

    /**
     * Returns the number of results recieved.
     */
    int count ();

    /**
     * Returns true if the file is versioned.
     */
    bool isVersioned ();
  };

}

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../rapidsvn-dev.el")
 * end:
 */
