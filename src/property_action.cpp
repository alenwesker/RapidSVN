
#include "svncpp/property.h"
#include "include.h"
#include "wx/resource.h"
#include "rapidsvn_app.h"
#include "property_action.h"
#include "svn_notify.h"


PropertyAction::PropertyAction (wxFrame * frame, apr_pool_t * __pool, 
                      Tracer * tr, const char * target)
                      : ActionThread (frame, __pool), _target(target)
{
  thisframe = frame;
  SetTracer (tr, FALSE);        // do not own the tracer
}

void
PropertyAction::Perform ()
{
  ////////////////////////////////////////////////////////////
  // Here we are in the main thread.
  svn::Property property;

  property.loadPath (_target);

  if(!property.isVersioned ())
	  return;

  propDialog = new PropertyDlg(thisframe, &property);

  if (propDialog->ShowModal () == wxID_OK)
  {
    // #### TODO: check errors and throw an exception
    // create the thread
    Create ();

    // here we start the action thread
    Run ();

    ////////////////////////////////////////////////////////////
  }

  // destroy the dialog
  propDialog->Close (TRUE);
}

void *
PropertyAction::Entry ()
{
  return NULL;
}