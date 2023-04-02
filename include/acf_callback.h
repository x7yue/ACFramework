#ifndef ACF_CALLBACK_H_
#define ACF_CALLBACK_H_

#include "include/internal/acf_scoped_refptr.h"

///
/// Complete event notify
///
/*--acf(source=client)--*/
class AcfCompleteHandler : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Called when task has been completed.
  ///
  /*--acf()--*/
  virtual void OnComplete() = 0;
};

#endif