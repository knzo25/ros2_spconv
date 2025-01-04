#pragma once
#include <spconvlib/cumm/common/TensorViewNVRTC.h>
namespace spconvlib {
namespace cumm {
namespace gemm {
namespace main {
namespace Simt_f32f32f32f32f32tnt_m128n128k8m32n64k8A1_200_S1 {
namespace out_smem_storage {
using TensorViewNVRTC = spconvlib::cumm::common::TensorViewNVRTC;
struct OutputSmemStorage {
  tv::alignedarray<float, 2320, 16> smem;
};
} // namespace out_smem_storage
} // namespace Simt_f32f32f32f32f32tnt_m128n128k8m32n64k8A1_200_S1
} // namespace main
} // namespace gemm
} // namespace cumm
} // namespace spconvlib