#include <spconvlib/spconv/csrc/sparse/all/ops_cpu3d/Point2VoxelCPU.h>
namespace spconvlib {
namespace spconv {
namespace csrc {
namespace sparse {
namespace all {
namespace ops_cpu3d {
using TensorView = spconvlib::cumm::common::TensorView;
using Layout = spconvlib::spconv::csrc::sparse::all::ops_cpu3d::layout_ns::TensorGeneric;
using Point2VoxelCommon = spconvlib::spconv::csrc::sparse::all::ops_cpu3d::p2v_c::Point2VoxelCommon;
 Point2VoxelCPU::Point2VoxelCPU(std::array<float, 3> vsize_xyz, std::array<float, 6> coors_range_xyz, int num_point_features, int max_num_voxels, int max_num_points_per_voxel)   {
  
  for (int i = 0; i < 3; ++i){
      vsize[2 - i] = vsize_xyz[i];
      coors_range[2 - i] = coors_range_xyz[i];
      coors_range[5 - i] = coors_range_xyz[i + 3];
  }
  int64_t prod = 1;
  for (size_t i = 0; i < 3; ++i) {
      grid_size[i] =
          std::round((coors_range[3 + i] - coors_range[i]) / vsize[i]);
  }
  for (int i = 3 - 1; i >= 0; --i) {
      grid_stride[i] = prod;
      prod *= grid_size[i];
  }
  voxels = tv::zeros({max_num_voxels, max_num_points_per_voxel, num_point_features}, tv::type_v<float>, -1);
  indices = tv::zeros({max_num_voxels, 3}, tv::int32, -1);
  num_per_voxel = tv::zeros({max_num_voxels}, tv::int32, -1);
  tv::TensorShape grid_shape(grid_size.data(), grid_size.data() + 3);
  densehashdata = tv::zeros(grid_shape, tv::int32, -1);
  auto densehashdata_ptr = densehashdata.data_ptr<int>();
  for (int i= 0; i < densehashdata.size(); ++i){
      densehashdata_ptr[i] = -1;
  }
}
} // namespace ops_cpu3d
} // namespace all
} // namespace sparse
} // namespace csrc
} // namespace spconv
} // namespace spconvlib