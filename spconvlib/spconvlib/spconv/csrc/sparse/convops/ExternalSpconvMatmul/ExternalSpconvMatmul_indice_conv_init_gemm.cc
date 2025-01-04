#include <spconvlib/spconv/csrc/sparse/convops/ExternalSpconvMatmul.h>
namespace spconvlib {
namespace spconv {
namespace csrc {
namespace sparse {
namespace convops {
using TensorView = spconvlib::cumm::common::TensorView;
tv::Tensor ExternalSpconvMatmul::indice_conv_init_gemm(std::string features_n, std::string filters_n, bool all_weight_is_krsc, bool is_kc_not_ck, int kv_center, int out_channel, std::uintptr_t stream_int)   {
  
  TV_THROW_RT_ERR("not implemented, override this and use preferred blas!!!");
}
} // namespace convops
} // namespace sparse
} // namespace csrc
} // namespace spconv
} // namespace spconvlib