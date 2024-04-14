#include <src/Scripts.h>

static bool isRunning = true;

void SetRunningState(bool val) { isRunning = val; }
bool GetRunningState() { return isRunning; }