#include "cppunit/TestCase.h"
#include "cppunit/extensions/HelperMacros.h"
#include "svncpp/status.h"
#include "svncpp/modify.h"
#include "svncpp/property.h"
#include "svncpp/log.h"
#include "test_config.h"

/**
 * Tests the SvnCpp classes.
 */
class SvnCppTestCase : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE( SvnCppTestCase );
  CPPUNIT_TEST( testStatus );
  CPPUNIT_TEST( testCheckout );
  CPPUNIT_TEST( testDeleteRevert );
  CPPUNIT_TEST( testAdd );
  CPPUNIT_TEST( testUpdate );
  CPPUNIT_TEST( testCommit );
  CPPUNIT_TEST( testCopy );
  CPPUNIT_TEST( testMove );
  CPPUNIT_TEST( testMkdir );
  CPPUNIT_TEST( testExport );
  CPPUNIT_TEST( testProperty );
  CPPUNIT_TEST( testLog );
  CPPUNIT_TEST_SUITE_END();

private:
  svn::Notify notify;

public:
  void setUp ();

protected:
  /**
   * Tests all of the status methods.
   */
  void testStatus ();

  void testCheckout ();

  /**
   * Tests both the delete and revert functionality.
   */
  void testDeleteRevert ();

  void testAdd ();

  void testUpdate ();

  void testCommit ();

  void testCopy ();

  void testMove ();

  void testProperty ();

  void testMkdir ();

  void testExport ();

  void testLog ();
};

/**
 * Required for testCheckout.
 */
struct NotifyBaton
{
  svn_boolean_t received_some_change;
  svn_boolean_t is_checkout;
  svn_boolean_t suppress_final_line;
  svn_boolean_t sent_first_txdelta;
  apr_pool_t *pool;
};