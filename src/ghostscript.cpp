#include "ghostscript.h"

namespace ghost {
  Ghostscript::Ghostscript() { Ghostscript("", "", 0, 0); }

  Ghostscript::Ghostscript(const std::string &pdf, const std::string &output_prefix, size_t page, size_t max_page) {
    _op = std::unique_ptr<GhostOps>(new GhostOps());
    setPdfPath(pdf);
    setOutputPrefix(output_prefix);
    setPage(page);
    setMaxPage(max_page);
  }

  Ghostscript::~Ghostscript() { _op.reset(); }

  void Ghostscript::setPdfPath(const std::string &path) { _op->_opParams->pdfpath = path; }

  std::string Ghostscript::getPdfPath() const { return _op->_opParams->pdfpath; }

  void Ghostscript::setOutputPrefix(const std::string &path) { _op->_opParams->outpath = path; }
  std::string Ghostscript::getOutputPrefix() const { return _op->_opParams->outpath; }

  void Ghostscript::setFirstPage(size_t page) { _op->_opParams->firstpage = page; }

  size_t Ghostscript::getFirstPage() const { return _op->_opParams->firstpage; }

  void Ghostscript::setLastPage(size_t page) { _op->_opParams->lastpage = page; }

  size_t Ghostscript::getLastPage() const { return _op->_opParams->lastpage; }

  void Ghostscript::setMaxPage(size_t page) { _op->_opParams->max_page = page; }

  size_t Ghostscript::getMaxPage() const { return _op->_opParams->max_page; }

  void Ghostscript::setPage(size_t page) {
    _op->_opParams->firstpage = page;
    _op->_opParams->lastpage  = page;
  }

  size_t Ghostscript::getPage() const {
    assert(_op->_opParams->firstpage == _op->_opParams->lastpage);
    return _op->_opParams->firstpage;
  }

  void Ghostscript::setOp(const std::string &op_name) { _op->_opParams->op_name = op_name; }

  std::string Ghostscript::getOp() const { return _op->_opParams->op_name; }

  std::string Ghostscript::getOutputPostfix() const { return _op->_opParams->postfix; }

  void Ghostscript::convert() { _op->run(); }
}  // namespace ghost
