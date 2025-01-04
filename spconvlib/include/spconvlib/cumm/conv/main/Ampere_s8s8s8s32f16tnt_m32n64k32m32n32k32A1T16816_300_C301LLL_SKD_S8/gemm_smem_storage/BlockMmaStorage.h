#pragma once
namespace spconvlib {
namespace cumm {
namespace conv {
namespace main {
namespace Ampere_s8s8s8s32f16tnt_m32n64k32m32n32k32A1T16816_300_C301LLL_SKD_S8 {
namespace gemm_smem_storage {
struct BlockMmaStorage {
  tv::alignedarray<int8_t, 3072, 16> smem_A;
  tv::alignedarray<int8_t, 6144, 16> smem_B;
};
} // namespace gemm_smem_storage
} // namespace Ampere_s8s8s8s32f16tnt_m32n64k32m32n32k32A1T16816_300_C301LLL_SKD_S8
} // namespace main
} // namespace conv
} // namespace cumm
} // namespace spconvlib