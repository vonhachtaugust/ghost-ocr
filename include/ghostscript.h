#pragma once

#include "ghostscript_op.h"

namespace ghost {

  class Ghostscript {
   public:
    Ghostscript();
    Ghostscript(const std::string& pdf, const std::string& output_prefix, size_t page, size_t max_page);

    ~Ghostscript();

    void setPdfPath(const std::string& path);
    std::string getPdfPath() const;

    void setOutputPrefix(const std::string& path);
    std::string getOutputPrefix() const;

    void setFirstPage(size_t page);
    size_t getFirstPage() const;

    void setLastPage(size_t page);
    size_t getLastPage() const;

    void setPage(size_t page);
    size_t getPage() const;

    void setMaxPage(size_t max_page);
    size_t getMaxPage() const;

    void setOp(const std::string& op_name);
    std::string getOp() const;

    std::string getOutputPostfix() const;

    void convert();
   private:
    std::unique_ptr<GhostOps> _op;
  };
}  // namespace ghost
