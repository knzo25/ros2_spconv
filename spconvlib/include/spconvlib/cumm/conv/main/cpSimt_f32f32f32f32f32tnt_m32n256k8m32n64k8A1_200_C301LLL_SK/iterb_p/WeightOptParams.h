#pragma once
#include <spconvlib/cumm/common/TensorViewMath.h>
#include <spconvlib/cumm/conv/main/cpSimt_f32f32f32f32f32tnt_m32n256k8m32n64k8A1_200_C301LLL_SK/lb/TensorGeneric.h>
#include <spconvlib/cumm/conv/main/cpSimt_f32f32f32f32f32tnt_m32n256k8m32n64k8A1_200_C301LLL_SK/cp/ConvProblem.h>
namespace spconvlib {
namespace cumm {
namespace conv {
namespace main {
namespace cpSimt_f32f32f32f32f32tnt_m32n256k8m32n64k8A1_200_C301LLL_SK {
namespace iterb_p {
using TensorViewMath = spconvlib::cumm::common::TensorViewMath;
using Layout = spconvlib::cumm::conv::main::cpSimt_f32f32f32f32f32tnt_m32n256k8m32n64k8A1_200_C301LLL_SK::lb::TensorGeneric;
using ConvProblem = spconvlib::cumm::conv::main::cpSimt_f32f32f32f32f32tnt_m32n256k8m32n64k8A1_200_C301LLL_SK::cp::ConvProblem;
struct WeightOptParams {
  Layout layout;
  int64_t inc_strided;
  int64_t inc_rs;
  int64_t inc_c;
  int filter_c_delta;
  int stride_rsc_bytes;
  int64_t inc_c_reset;
  __forceinline__ __host__ __device__  WeightOptParams(ConvProblem const& problem, Layout const& layout) : layout(layout)  {
    
    // int kernel_prod = problem.kernel_volume;
    filter_c_delta = 8 * problem.split_k_slices;
    inc_strided = int64_t(layout.strides[0]) * 16;
    stride_rsc_bytes = layout.strides[0] * 32 / 8;
    // back to strided start, then inc c
    inc_c = filter_c_delta - inc_strided * int64_t(15);
    inc_rs = int64_t(layout.strides[1]);
    // inc_c_reset = -gemm_iters_k * filter_c_delta * 32 / 8;
    inc_rs = inc_rs * 32 / 8;
    inc_strided = inc_strided * 32 / 8;
    inc_c = inc_c * 32 / 8;
  }
  __forceinline__ __host__ __device__ void set_inc_reset_for_inc_k_first(int gemm_iters_k = -1)   {
    
    inc_c_reset = -gemm_iters_k * filter_c_delta * 32 / 8;
  }
};
} // namespace iterb_p
} // namespace cpSimt_f32f32f32f32f32tnt_m32n256k8m32n64k8A1_200_C301LLL_SK
} // namespace main
} // namespace conv
} // namespace cumm
} // namespace spconvlib