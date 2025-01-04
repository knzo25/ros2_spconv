#pragma once
#include <spconvlib/cumm/common/TensorViewNVRTC.h>
namespace spconvlib {
namespace cumm {
namespace conv {
namespace main {
namespace Simt_f32f32f32f32f32tnt_m64n256k8m32n64k8A1_200_C301LLL_SK {
namespace mma {
namespace mma_ns_wb {
namespace ns1 {
using TensorViewNVRTC = spconvlib::cumm::common::TensorViewNVRTC;
struct RowMajorInterleaved {
  int32_t stride;
  __forceinline__ __host__ __device__ constexpr  RowMajorInterleaved(int32_t stride_) : stride(stride_)  {
    
  }
  __forceinline__ __host__ __device__ constexpr static RowMajorInterleaved from_shape(const tv::array<int, 2> & shape)   {
    return RowMajorInterleaved(shape[1] * 1);
  }
  __forceinline__ __host__ __device__ constexpr int64_t operator()(int32_t x, int32_t y)  const {
    int32_t row_major = x / 1;
    int32_t row_minor = x % 1;
    return int64_t(row_major) * int64_t(stride) +
        int64_t(y) * 1 + row_minor;
  }
  __forceinline__ __host__ __device__ constexpr int32_t inverse_0(int64_t offset)  const {
    int32_t row_major = int32_t(offset / stride);
    int32_t residual = int32_t(offset % stride);
    int32_t row_minor = residual % 1;
    return row_major * 1 + row_minor;
  }
  __forceinline__ __host__ __device__ constexpr int32_t inverse_1(int64_t offset)  const {
    return (offset % stride) / 1;
  }
};
} // namespace ns1
} // namespace mma_ns_wb
} // namespace mma
} // namespace Simt_f32f32f32f32f32tnt_m64n256k8m32n64k8A1_200_C301LLL_SK
} // namespace main
} // namespace conv
} // namespace cumm
} // namespace spconvlib