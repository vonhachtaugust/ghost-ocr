#pragma once

#include "ghostscript.h"
#include "test.h"

namespace ghost {

  TEST(Ghostscript, Constructor) {
    // TODO: Copy/Assignment etc...
    Ghostscript g;
  }

  TEST(Ghostscript, Convert) {
    Ghostscript g;

    g.setPdfPath("../data/Thornstroms_170605_web.pdf");
    g.setOutPath("test_output");
    g.setPage(5);
    g.setMaxPage(32);
    g.setOp("pdf2png");

    g.convert();
    // TODO: Check file exists, non-zero etc...
  }

}  // namespace ghost
