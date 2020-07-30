// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "core/optimizer/graph_transformer.h"

namespace onnxruntime {

/**
 * Fuses MatMul with surrounding scales (multiplies or divides) by a constant scalar into TransposeScaleMatMul.
 * 
 * For example, given matrices A and B and constant scalars t, u, and v:
 *   Mul(v, MatMul(Mul(t, A), Mul(u, B))
 *     -> TransposeScaleMatMul(A, B, alpha=t*u*v)
 */
class MatMulScaleFusion : public GraphTransformer {
 public:
  MatMulScaleFusion(const std::unordered_set<std::string>& compatible_execution_providers = {})
      : GraphTransformer{"MatMulScaleFusion", compatible_execution_providers} {
  }

 private:
  Status ApplyImpl(Graph& graph, bool& modified, int graph_level, const logging::Logger& logger) const override;
};

}  // namespace onnxruntime
