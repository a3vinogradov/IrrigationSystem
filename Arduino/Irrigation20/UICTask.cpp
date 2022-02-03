#include "UICTask.h"

  UICTask::UICTask(UIController* uic)
  {
    _UIC = uic;
  }
  void UICTask::Setup()
  {
    _UIC->Setup();
  }
  void UICTask::Exec()
  {
    _UIC->Exec();
  }
