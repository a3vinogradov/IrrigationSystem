#ifndef file_PompRelayModule
#define file_PompRelayModule

class PompRelayModule
{
  private:
    int _pin = 0;
  public:
    PompRelayModule(int pin);
    void ON();
    void OFF();
    int GetState();
};
#endif
