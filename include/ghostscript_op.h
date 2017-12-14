#pragma once

#include <stdexcept>
#include "ghost_error.h"
#include "utils.h"

#include "../../../../opt/local/include/ghostscript/iapi.h"
#include "../../../../opt/local/include/ghostscript/ierrors.h"

namespace ghost {
  struct OpParams {
    std::string pdfpath;
    std::string outpath;
    size_t firstpage;
    size_t lastpage;
    size_t max_page;
    std::string op_name;
    std::string postfix;
  };

  using ConvertFunction = std::vector<std::string> (*)(OpParams* params);

  struct OpMap {
    std::unordered_map<std::string, ConvertFunction> map;
  };

  class GhostOps {
   public:
    GhostOps();
    ~GhostOps();

    void run();
    std::unique_ptr<OpParams> _opParams;
  private:
    void* _minst;

    void gs(OpParams* params);

    void registerOp(const std::string& call_name, ConvertFunction f);
    ConvertFunction Op(const std::string& call_name);
    void init_default_registry();

    std::unique_ptr<OpMap> _convertOps;
  };
}  // namespace ghost
