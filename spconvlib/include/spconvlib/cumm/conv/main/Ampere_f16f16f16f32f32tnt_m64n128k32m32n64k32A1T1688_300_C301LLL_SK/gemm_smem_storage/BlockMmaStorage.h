#pragma once
namespace spconvlib {
namespace cumm {
namespace conv {
namespace main {
namespace Ampere_f16f16f16f32f32tnt_m64n128k32m32n64k32A1T1688_300_C301LLL_SK {
namespace gemm_smem_storage {
struct BlockMmaStorage {
  tv::alignedarray<tv::half_t, 6144, 16> smem_A;
  tv::alignedarray<tv::half_t, 12288, 16> smem_B;
};
} // namespace gemm_smem_storage
} // namespace Ampere_f16f16f16f32f32tnt_m64n128k32m32n64k32A1T1688_300_C301LLL_SK
} // namespace main
} // namespace conv
} // namespace cumm
} // namespace spconvlib