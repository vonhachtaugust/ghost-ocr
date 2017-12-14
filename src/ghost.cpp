#include <stdio.h>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "ghost.h"
//#include "opencv2/core.hpp"
//#include "opencv2/highgui.hpp"

#include "leptonica/allheaders.h"
#include "tesseract/baseapi.h"

struct Expect {
  const static size_t args = 5;
};

using namespace std;
using namespace ghost;
// using namespace cv;
using namespace tesseract;

/*
void display_box(const std::string& file, const ghost::Box& b) {
  try {
    Mat image;
    image = imread(file, CV_LOAD_IMAGE_COLOR);

    // x, y, width, height
    Rect roi(b.x, b.y, b.width, b.height);
    Mat subview(image, roi);

    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", subview);
    waitKey(0);
  } catch (std::exception e) {
    print(e.what());
  }
}*/

int get_num_pages(const std::string& pdf) {
  FILE* in;
  char buff[256];

  std::string cmd = "mdls -name kMDItemNumberOfPages -raw " + pdf;
  if (!(in = popen(cmd.c_str(), "r"))) {
    return -1;
  }

  int res;
  while (fgets(buff, sizeof(buff), in) != NULL) {
    res = atoi(buff);
  }
  pclose(in);

  return res;
}

int main(int argc, char** argv) {
  if (argc != Expect::args) {
    print("Too few arguments, expected " + std::to_string(Expect::args) + "\n");
    print("Usage: ./ghost path/to/pdf/pdfname operation page lang path/to/boxfile/boxfilename");
    return -1;
  }

  std::string pdf = argv[1];
  std::string op = argv[2];
  int page = atoi(argv[3]);
  std::string lang = argv[4];
  std::string boxfile = argv[5];
  std::string output_prefix = "tmp";

  /* Convert pdf to png  */
  Ghostscript ghost_s(pdf, output_prefix, page, get_num_pages(pdf));
  ghost_s.setOp(op);

  print("Converting: " + pdf + " to " + op);
  print("Using page: " + std::to_string(page));
  print("Using language: " + lang);
  print("Using boxfile: " + boxfile);

  ghost_s.convert();

  print("Successfully converted: " + pdf + " to " + output_prefix + "." + op);

  /* Extract text from png using boxes */
  std::vector<std::string> configs;
  configs.push_back("--psm");
  configs.push_back("4");
  configs.push_back("-c");
  configs.push_back("preserve_interword_spaces=1");

  //'--psm 4 -c preserve_interword_spaces=1';

  GlimpseSensor glimpse(lang, &configs);
  std::string target_file = output_prefix + ghost_s.getOutputPostfix();

  try {
    print("Reading: " + target_file);
    glimpse.readImage(target_file);
  } catch (ghost_error e) {
    print(e.what());
    return -1;
  }

  std::ifstream ifs(boxfile.c_str(), std::ios::in | std::ios::binary);
  if (ifs.fail() || ifs.bad()) {
    throw ghost_error("Failed to open file: " + boxfile);
    return -1;
  }

  int x, y, width, height;
  while (ifs >> x >> y >> width >> height) {
    glimpse.addBox(ghost::Box(x, y, width, height));
  }

  auto texts = glimpse.extract();
  print("Extracted:");
  for (const auto& t : texts) {
    print(t);
  }

  return 0;
}
