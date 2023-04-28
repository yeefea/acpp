#include <nanolog/NanoLogCpp17.h>

using namespace NanoLog::LogLevels;
int main(int argc, char **argv)
{
  NANO_LOG(NOTICE, "Hello World! This is an integer %d and a double %lf\r\n", 1, 2.0);
  return 0;
}
