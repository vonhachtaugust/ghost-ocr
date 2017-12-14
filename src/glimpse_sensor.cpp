#include "glimpse_sensor.h"

namespace ghost {
  GlimpseSensor::GlimpseSensor() { GlimpseSensor("eng", {0}, {0}, {0}); }

  GlimpseSensor::GlimpseSensor(const std::string& lang) { GlimpseSensor(lang, {0}, {0}, {0}); }

  GlimpseSensor::GlimpseSensor(const std::string& lang,
                               const std::vector<std::string>& configs,
                               const std::vector<std::string>& vars_vec,
                               const std::vector<std::string>& vars_value)
    : _image(nullptr) {
    _api = std::unique_ptr<tesseract::TessBaseAPI>(new tesseract::TessBaseAPI());

    std::vector<char*> cstrings;
    GenericVector<STRING> vec;
    GenericVector<STRING> val;

    if (!configs.empty()) {
      cstrings.reserve(configs.size());
      for (const auto& c : configs) {
        cstrings.push_back(const_cast<char*>(c.c_str()));
      }
    }

    if (!vars_vec.empty()) {
      StdVec2GenericVec(vars_vec, vec);
    }

    if (!vars_value.empty()) {
      StdVec2GenericVec(vars_value, val);
    }

    int init_result;

    /* If no configs we 'have' to choose other init method since even though it is NULL the for loop inside tesseract
     * library runs atleast once -> null dereference -> segmentation fault...  */
    if (configs.empty()) {
      init_result = _api->Init(NULL, lang.c_str());
    } else {
      init_result = _api->Init(NULL, lang.c_str(), tesseract::OEM_TESSERACT_LSTM_COMBINED, &cstrings[0],
                               cstrings.size(), vec.empty() ? NULL : &vec, vars_value.empty() ? NULL : &val, true);
    }

    if (init_result == -1) {
      throw ghost_error("[GlimpseSensor::GlimpseSensor]: Failed to initialize api");
    }
  }

  GlimpseSensor::~GlimpseSensor() {
    _api->End();
    _api.reset();
    pixDestroy(&_image);
  }

  void GlimpseSensor::readImage(const std::string& imagepath) {
    _image = pixRead(imagepath.c_str());

    if (!_image) {
      throw ghost_error("[GlimpseSensor::readImage] Failed to read image.");
    }
    _api->SetImage(_image);
  }

  std::vector<std::string> GlimpseSensor::extract() {
    std::vector<std::string> texts;

    for (const auto& box : _boxes) {
      _api->SetRectangle(box.x, box.y, box.width, box.height);
      std::string text = _api->GetUTF8Text();

      texts.push_back(text);
    }

    return texts;
  }

  void GlimpseSensor::addBox(const Box& b) { _boxes.push_back(b); }

  void GlimpseSensor::removeBox(const Box& b) { _boxes.erase(std::find(_boxes.begin(), _boxes.end(), b)); }

  Box GlimpseSensor::getBox(const Box& b) const { return *std::find(_boxes.begin(), _boxes.end(), b); }

  /**
   * Languages are loaded from datafiles. If another languages is needed a call to Init is required.
   * Multiple languages can be loaded using the + operator, but requires much memory.
   **/
  void GlimpseSensor::setLanguage(const std::string& language) { _api->Init(NULL, language.c_str()); }
  std::string GlimpseSensor::getLanguage() const { return _api->GetInitLanguagesAsString(); }

}  // namespace ghost
