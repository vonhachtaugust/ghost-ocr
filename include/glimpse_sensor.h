#pragma once

#include "ghost_error.h"
#include "utils.h"

#include "leptonica/allheaders.h"
#include "tesseract/baseapi.h"
#include "tesseract/genericvector.h"
#include "tesseract/strngs.h"

namespace ghost {
  void StdVec2GenericVec(const std::vector<std::string>& from, GenericVector<STRING>& to) {
    if (from.empty()) {
      throw ghost_error("File[glimpse_sensor.h] in Function[GenericVec2StdVec]: To vector is empty.");
      return;
    }

    if (to.empty()) {
      to.init_to_size(from.size(), "");
    }

    for (size_t i = 0; i < from.size(); ++i) {
      to[i] = from[i].c_str();
    }
  }

  struct Box {
    explicit Box(size_t x, size_t y, size_t w, size_t h) {
      this->x      = x;
      this->y      = y;
      this->width  = w;
      this->height = h;
    }

    size_t x;
    size_t y;
    size_t width;
    size_t height;

    bool operator==(const Box& other) const {
      return (x == other.x) && (y == other.y) && (width == other.width) && (height == other.height);
    }
  };

  class GlimpseSensor {
   public:
    GlimpseSensor();
    GlimpseSensor(const std::string& lang);
    GlimpseSensor(const std::string& lang,
                  const std::vector<std::string>& configs,
                  const std::vector<std::string>& vars_vec,
                  const std::vector<std::string>& vars_value);
    ~GlimpseSensor();

    void readImage(const std::string& imagepath);
    std::vector<std::string> extract();

    void addBox(const Box& b);
    void removeBox(const Box& b);
    Box getBox(const Box& b) const;

    void setLanguage(const std::string& language);
    std::string getLanguage() const;

   private:

    int init(const std::string& lang,
             const std::vector<std::string>& configs,
             const std::vector<std::string>& vars_vec,
             const std::vector<std::string>& vars_value);

    std::vector<Box> _boxes;
    Pix* _image;
    std::unique_ptr<tesseract::TessBaseAPI> _api;
  };
}  // namespace ghost
