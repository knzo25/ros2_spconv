#pragma once
namespace spconvlib {
namespace cumm {
namespace conv {
namespace main {
namespace Volta_f16f16f16f16f16tnt_m32n256k32m32n64k32A1T884_200_C301LLL_SK {
namespace gemm_smem_storage {
struct BlockMmaStorage {
  tv::alignedarray<tv::half_t, 2048, 16> smem_A;
  tv::alignedarray<tv::half_t, 16384, 16> smem_B;
};
} // namespace gemm_smem_storage
} // namespace Volta_f16f16f16f16f16tnt_m32n256k32m32n64k32A1T884_200_C301LLL_SK
} // namespace main
} // namespace conv
} // namespace cumm
} // namespace spconvlib