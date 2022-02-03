#ifndef file_UICTask
#define file_UICTask

#include "UIController.h"

class UICTask
{
  private:
  UIController* _UIC;
  
  public:
  UICTask(UIController* uic);
  void Setup();
  void Exec();
};

#endif
