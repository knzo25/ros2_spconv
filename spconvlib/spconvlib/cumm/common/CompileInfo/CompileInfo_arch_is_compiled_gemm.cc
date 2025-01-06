#include <spconvlib/cumm/common/CompileInfo.h>
namespace spconvlib {
namespace cumm {
namespace common {
bool CompileInfo::arch_is_compiled_gemm(std::tuple<int, int> arch)   {

#ifdef CUDA_ARCH_75
  if (arch == std::make_tuple(7, 5)){
      return true;
  }
#endif

#ifdef CUDA_ARCH_86
  if (arch == std::make_tuple(8, 6)){
      return true;
  }
#endif

#ifdef CUDA_ARCH_89
  if (arch == std::make_tuple(8, 9)){
      return true;
  }
#endif

  return false;
}
} // namespace common
} // namespace cumm
} // namespace spconvlib