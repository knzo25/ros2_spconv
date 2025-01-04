#pragma once
namespace spconvlib {
namespace cumm {
namespace conv {
namespace main {
namespace Simt_f16f16f16f32f32tnt_m32n32k32m32n32k8A1_200_C301LLL_SK {
namespace gemm_smem_storage {
struct BlockMmaStorage {
  tv::alignedarray<tv::half_t, 2176, 16> smem_A;
  tv::alignedarray<tv::half_t, 2176, 16> smem_B;
};
} // namespace gemm_smem_storage
} // namespace Simt_f16f16f16f32f32tnt_m32n32k32m32n32k8A1_200_C301LLL_SK
} // namespace main
} // namespace conv
} // namespace cumm
} // namespace spconvlib