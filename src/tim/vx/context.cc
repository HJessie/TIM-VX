/****************************************************************************
*
*    Copyright (c) 2020-2023 Vivante Corporation
*
*    Permission is hereby granted, free of charge, to any person obtaining a
*    copy of this software and associated documentation files (the "Software"),
*    to deal in the Software without restriction, including without limitation
*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
*    and/or sell copies of the Software, and to permit persons to whom the
*    Software is furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*    DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/
#include "tim/vx/context.h"

#include "context_private.h"
#include "graph_private.h"
#include "tim/vx/graph.h"
#include "tim/vx/compile_option.h"
#include "vsi_nn_pub.h"

namespace tim {
namespace vx {

ContextImpl::ContextImpl() : context_(vsi_nn_CreateContext()) {}

ContextImpl::~ContextImpl() {
  if (context_) {
    vsi_nn_ReleaseContext(&context_);
  }
}

vsi_nn_context_t ContextImpl::context() { return context_; }

std::shared_ptr<Context> Context::Create() {
  return std::make_shared<ContextImpl>();
}

std::shared_ptr<Graph> ContextImpl::CreateGraph() {
  return std::make_shared<GraphImpl>(this);
}

std::shared_ptr<Graph> ContextImpl::CreateGraph(const CompileOption& options) {
  return std::make_shared<GraphImpl>(this, options);
}

bool ContextImpl::isClOnly() {
    return VSI_NN_HW_EVIS_NONE == context_->config.evis.ver;
}

bool ContextImpl::hasSP() {
    return 0 != context_->config.support_stream_processor;
}

}  // namespace vx
}  // namespace tim