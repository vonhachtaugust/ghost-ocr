#include "include/test.h"
#include "include/test_ghostscript.h"
#include "include/test_glimpse_sensor.h"

using namespace std;

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
