/*
 * ====================================================================
 * Copyright (c) 2002, 2003 The RapidSvn Group.  All rights reserved.
 *
 * This software is licensed as described in the file LICENSE.txt,
 * which you should have received as part of this distribution.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */

#ifndef _SVNCPP_TARGETS_HPP_
#define _SVNCPP_TARGETS_HPP_

// stl
#include <vector>

// apr api
#include "apr_tables.h"


namespace svn
{
  // forward declarations
  class Path;
  class Pool;

  /**
   * Encapsulation for Subversion target arrays handling
   */
  class Targets
  {
  public:
    /** 
     * Constructor
     *
     * @param targets vector of paths
     */
    Targets (const std::vector<Path> & targets);
    
    /**
     * Constructor from an APR array containing
     * char *.
     *
     * @param targets APR array header
     */
    Targets (const apr_array_header_t * targets);

    /**
     * Constructor. Initializes list with just
     * one entry
     *
     * @param target
     */
    Targets (const char * target = 0);

    /**
     * Copy Constructor
     *
     * @param targets Source
     */
    Targets (const Targets & targets);

    /**
     * Destructor
     */
    virtual ~Targets ();

    /**
     * Returns an apr array containing
     * char *.
     *
     * @param pool Pool used for conversion
     */
    const apr_array_header_t *
    array (const Pool & pool) const;

    /**
     * Returns a vector of paths
     *
     * @return vector of paths
     */
    const std::vector<Path> &
    targets() const;

    /**
     * @return the number of targets
     */
    size_t size () const;

    /**
     * operator to return the vector
     *
     * @return vector with targets
     */
    operator const std::vector<Path> & () const
    {
      return m_targets;
    }

    /**
     * returns one single target. in fact,
     * the first in the vector, it there are more
     * than one. if there is no target returns
     * an empty path
     *
     * @return single path
     */
    const Path
    target () const;
    

  private:
    std::vector<Path> m_targets;
  };
}

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../rapidsvn-dev.el")
 * end:
 */