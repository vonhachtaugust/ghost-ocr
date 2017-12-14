#include "ghostscript_op.h"

namespace ghost {

  struct Resolution {
    const static size_t DEFAULT = 144;
  };

  std::vector<std::string> pdf2pnggray(OpParams *params) {
    std::vector<std::string> args;
    args.push_back("pdf2pnggray");
    args.push_back("-dNOPAUSE");
    args.push_back("-dBATCH");
    args.push_back("-dSAFER");
    args.push_back("-sDEVICE=pnggray");
    args.push_back("-r" + std::to_string(Resolution::DEFAULT));
    args.push_back("-dFirstPage=" + std::to_string(params->firstpage));
    args.push_back("-dLastPage=" + std::to_string(params->lastpage));
    args.push_back("-o");
    args.push_back(params->outpath + ".png");
    args.push_back(params->pdfpath);
    return args;
  }

  GhostOps::GhostOps() : _minst(nullptr) {
    _convertOps = std::unique_ptr<OpMap>(new OpMap());
    _opParams   = std::unique_ptr<OpParams>(new OpParams());
    init_default_registry();
  }
  GhostOps::~GhostOps() {
    _convertOps.reset();
    _opParams.reset();
  }

  void GhostOps::registerOp(const std::string &call_name, ConvertFunction f) { _convertOps->map.emplace(call_name, f); }

  ConvertFunction GhostOps::Op(const std::string &call_name) {
    auto iter = _convertOps->map.find(call_name);
    if (iter == _convertOps->map.end()) {
      printf("No operation with name %s registered!\t", call_name.c_str());
      throw std::invalid_argument("Invalid operation name");
    }

    return (*iter->second);
  }

  void GhostOps::init_default_registry() { registerOp("png", &pdf2pnggray); }

  void GhostOps::run() {
    if (!_opParams.get()) {
      throw ghost_error("[GhostOps::run] No operation parameters were given");
    }

    gs(this->_opParams.get());
  }

  void GhostOps::gs(OpParams *params) {
    ConvertFunction f             = Op(params->op_name);
    std::vector<std::string> args = (*f)(params);

    // The lack of finally really bites ...
    int code;

    try {
      code = gsapi_new_instance(&_minst, NULL);
      if (code < 0) {
        throw ghost_error("[GhostOps::gs] Failed to create new Ghostscript instance.");
      }

      code = gsapi_set_arg_encoding(_minst, GS_ARG_ENCODING_UTF8);
      if (code != 0) {
        throw ghost_error("[GhostOps::gs] Failed to set arg encoding");
      }

      // Api requires char**
      std::vector<char *> cstrings;
      cstrings.reserve(args.size());
      for (const auto &a : args) {
        cstrings.push_back(const_cast<char *>(a.c_str()));
      }
      code = gsapi_init_with_args(_minst, cstrings.size(), &cstrings[0]);
      if (code < 0) {
        printf("Error: %i was returned by the ghostscript api\t", code);
        throw ghost_error("[GhostOps::gs] Ghostscript returned error value");
      }

      code = gsapi_exit(_minst);
      if (code < 0) {
        printf("Error: %i was returned by the ghostscript api\t", code);
        throw ghost_error("[GhostOps::gs] Ghostscript returned error value");
      }

      gsapi_delete_instance(_minst);

    } catch (ghost_error e) {
      print(e.what());
      gsapi_exit(_minst);
      gsapi_delete_instance(_minst);
    } catch (std::exception e) {
      print(e.what());
      gsapi_exit(_minst);
      gsapi_delete_instance(_minst);
    }
  }
}  // namespace ghost
