#include <spconvlib/cumm/common/CompileInfo.h>
namespace spconvlib {
namespace cumm {
namespace common {
std::vector<std::tuple<int, int>> CompileInfo::get_compiled_cuda_arch()   {
  
  std::vector<std::tuple<int, int>> res;

#ifdef CUDA_ARCH_75
  res.push_back(std::make_tuple(7, 5));
#endif

#ifdef CUDA_ARCH_86
  res.push_back(std::make_tuple(8, 6));
#endif

#ifdef CUDA_ARCH_89
  res.push_back(std::make_tuple(8, 9));
#endif

  return res;
}
} // namespace common
} // namespace cumm
} // namespace spconvlib