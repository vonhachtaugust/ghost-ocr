#pragma once

#include "glimpse_sensor.h"
#include "test.h"

#include "tesseract/genericvector.h"
#include "tesseract/strngs.h"

namespace ghost {

  TEST(GlimpseSensor, Constructor) { GlimpseSensor g; }

  TEST(GlimpseSensor, SetLanguage) {
    GlimpseSensor g("swe");
    ASSERT_EQ(g.getLanguage(), "swe");

    g.setLanguage("eng");
    ASSERT_EQ(g.getLanguage(), "eng");
  }

  /*
   * Can only runs if specific test image is available
   */
  TEST(GlimpseSensor, Extract) {
    GlimpseSensor g;

    auto file = "../data/test.png";
    try {
      g.readImage(file);

      Box focus(210, 100, 230, 40);
      g.addBox(focus);

      auto texts = g.extract();

      ASSERT_EQ(texts.size(), (unsigned long)(1));
      ASSERT_EQ(texts[0], "Rosazzo Picolit\n");
    } catch (ghost_error e) {
      print("Failed open test file. Is it available?");
      print(e.what());
    }
  }
}  // namespace ghost
