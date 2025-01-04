#pragma once
#include <spconvlib/cumm/common/TensorViewNVRTC.h>
#include <spconvlib/cumm/common/GemmBasicKernel.h>
#include <spconvlib/cumm/conv/main/Simt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK/inpitera/mask/Mask.h>
#include <spconvlib/cumm/conv/main/Simt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK/inpitera/gload/GlobalLoad.h>
#include <spconvlib/cumm/conv/main/Simt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK/inpitera/tmap/PitchLinear.h>
#include <spconvlib/cumm/conv/main/cpSimt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK/cp/ConvProblem.h>
#include <spconvlib/cumm/conv/main/cpSimt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK/itera_p/SparseParams.h>
namespace spconvlib {
namespace cumm {
namespace conv {
namespace main {
namespace Simt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK {
namespace inpitera {
using TensorViewNVRTC = spconvlib::cumm::common::TensorViewNVRTC;
using GemmBasicKernel = spconvlib::cumm::common::GemmBasicKernel;
using Mask = spconvlib::cumm::conv::main::Simt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK::inpitera::mask::Mask;
using GlobalLoad = spconvlib::cumm::conv::main::Simt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK::inpitera::gload::GlobalLoad;
using ThreadMap = spconvlib::cumm::conv::main::Simt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK::inpitera::tmap::PitchLinear;
using ConvProblem = spconvlib::cumm::conv::main::cpSimt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK::cp::ConvProblem;
using Params = spconvlib::cumm::conv::main::cpSimt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK::itera_p::SparseParams;
struct ForwardDgradSparseIOIterator {
  Params & params_;
  ConvProblem const& problem_;
  const char * pointer_;
  int const* indice_ptr_;
  int reduce_channel_offset_;
  int reduce_channel_offset_backup_;
  tv::array<uint32_t, 1> mask_reset_backup_;
  tv::array<uint32_t, 1> mask_;
  int32_t indices_[4];
  __forceinline__ __device__  ForwardDgradSparseIOIterator(Params & params, ConvProblem const& problem_size, const float * ptr, int thread_id, const tv::array<int, 2>& threadblock_offset) : params_(params), problem_(problem_size), indice_ptr_(params.indice_ptr_)  {
    
    auto thread_offset = threadblock_offset + ThreadMap::initial_offset(thread_id);
    int stride_offset_ = thread_offset[0];
    // update_indices();
    pointer_ = reinterpret_cast<const char *>(ptr + thread_offset[1]);
    // std::uintptr_t access_pointer_num = reinterpret_cast<std::uintptr_t>(pointer_);
    // if (access_pointer_num % 16 != 0){
    //     tv::printf2_block_once("BBBBBBBBBBBBBBBBSFASF");
    // }
    // origin_pointer_ = pointer_;
    params.mask_argsort_ptr_ += stride_offset_;
    // mask_ = 0;
    mask_.clear();
    reduce_channel_offset_ = thread_offset[1];
    reduce_channel_offset_backup_ = thread_offset[1];
    TV_PRAGMA_UNROLL
    for (int s = 0; s < 4; ++s){
        TV_PRAGMA_UNROLL
        for (int ss = 0; ss < 1; ++ss){
            TV_PRAGMA_UNROLL
            for (int v = 0; v < 1; ++v){
                uint32_t pred = (stride_offset_ + s * 16 + ss) < problem_.N;
                mask_[v] |= (pred << (s * 1 + ss));
            }
        }
    }
    TV_PRAGMA_UNROLL
    for (int v = 0; v < 1; ++v){
        mask_[v] = thread_offset[1] + v * 1 >= problem_.C ? 0 : mask_[v];
    }
    mask_reset_backup_ = mask_;
  }
  __forceinline__ __device__ void update_indices()   {
    
    int mask_inds[4];
    uint32_t pred;
    pred = mask_[0] & (1u << (0 + 0));
    asm volatile (
        "{\n"
        "  .reg .pred p;\n"
        "  setp.ne.b32 p,%1,0;\n"
        "  @p ld.global.b32 %0,[%2];\n"
        "}\n"
        : "=r"(mask_inds[0])
        : "r"(pred), "l"(params_.mask_argsort_ptr_)
    );
    pred = mask_[0] & (1u << (1 + 0));
    asm volatile (
        "{\n"
        "  .reg .pred p;\n"
        "  setp.ne.b32 p,%1,0;\n"
        "  @p ld.global.b32 %0,[%2+64];\n"
        "}\n"
        : "=r"(mask_inds[1])
        : "r"(pred), "l"(params_.mask_argsort_ptr_)
    );
    pred = mask_[0] & (1u << (2 + 0));
    asm volatile (
        "{\n"
        "  .reg .pred p;\n"
        "  setp.ne.b32 p,%1,0;\n"
        "  @p ld.global.b32 %0,[%2+128];\n"
        "}\n"
        : "=r"(mask_inds[2])
        : "r"(pred), "l"(params_.mask_argsort_ptr_)
    );
    pred = mask_[0] & (1u << (3 + 0));
    asm volatile (
        "{\n"
        "  .reg .pred p;\n"
        "  setp.ne.b32 p,%1,0;\n"
        "  @p ld.global.b32 %0,[%2+192];\n"
        "}\n"
        : "=r"(mask_inds[3])
        : "r"(pred), "l"(params_.mask_argsort_ptr_)
    );
    TV_PRAGMA_UNROLL
    for (int s = 0; s < 4; ++s){
        TV_PRAGMA_UNROLL
        for (int ss = 0; ss < 1; ++ss){
            if (mask_[0] & (1u << (s * 1 + ss))){
                indices_[s * 1 + ss] = 
                indice_ptr_[mask_inds[s * 1 + ss]] * 
                    problem_.C * 4 ;
            }
        }
    }
  }
  __forceinline__ __device__ void clear_mask_if_not_pred(bool pred, int v)   {
    
    mask_[v] = pred ? mask_[v] : 0;
  }
  __forceinline__ __device__ void clear_all_mask_if_not_pred(bool pred)   {
    
    TV_PRAGMA_UNROLL
    for (int v = 0; v < 1; ++v){
        mask_[v] = pred ? mask_[v] : 0;
    }
  }
  __forceinline__ __device__ void clear_all_mask_if_pred(bool pred)   {
    
    TV_PRAGMA_UNROLL
    for (int v = 0; v < 1; ++v){
        mask_[v] = pred ? 0:  mask_[v];
    }
  }
  __forceinline__ __device__ void clear_mask_if_pred(bool pred, int v)   {
    
    mask_[v] = pred ? 0 : mask_[v];
  }
  __forceinline__ __device__ void operator++()   {
    
  }
  __forceinline__ __device__ void increment_no_clear_mask()   {
    
  }
  __forceinline__ __device__ void clear_mask_if_batch_unbound()   {
    
  }
  __forceinline__ __device__ void operator+=(int num)   {
    
  }
  __forceinline__ __device__ void increment_k()   {
    
    pointer_ += params_.inc_c_next;
    reduce_channel_offset_ += params_.filter_c_delta;
    TV_PRAGMA_UNROLL
    for (int v = 0; v < 1; ++v){
        clear_mask_if_pred(reduce_channel_offset_ + v * 1 >= problem_.C, v);
    }
  }
  __forceinline__ __device__ void increment_filter()   {
    
    indice_ptr_ += problem_.N;
  }
  __forceinline__ __device__ void increment_filter(int num)   {
    
    indice_ptr_ += problem_.N * num;
  }
  __forceinline__ __device__ void reset_k()   {
    
    pointer_ += params_.inc_c_reset;
    mask_ = mask_reset_backup_;
    reduce_channel_offset_ = reduce_channel_offset_backup_;
  }
  __forceinline__ __device__ int get_indice_offset(int stride, int contig, int ss)  const {
    
    return indices_[stride * 1 + ss];
  }
  __forceinline__ __device__ const tv::alignedarray<int, 1, 4> * get(int indice_offset)  const {
    
    return reinterpret_cast<const tv::alignedarray<int, 1, 4> *>( pointer_ + indice_offset);
  }
  __forceinline__ __device__ void load_with_pointer_offset(tv::array<float, 4, 0>& frag, int32_t pointer_offset)   {
    
    frag.clear();
    tv::alignedarray<int, 1, 4> *frag_ptr = reinterpret_cast<tv::alignedarray<int, 1, 4> *>(&frag);
    TV_PRAGMA_UNROLL
    for (int s = 0; s < 4; ++s){
      TV_PRAGMA_UNROLL
      for (int c = 0; c < 1; ++c){
        TV_PRAGMA_UNROLL
        for (int ss = 0; ss < 1; ++ss){
          TV_PRAGMA_UNROLL
          for (int v = 0; v < 1; ++v){
            int mask_idx = s * 1 + 
                c * 1 + ss;
            int idx = s * 1 + 
                c * 1 + ss * 1 + v;
            auto indice_offset = get_indice_offset(s, c, ss);
            bool valid = bool(mask_[v] & (1u << mask_idx)) && (indice_offset >= 0);
            auto access_pointer = reinterpret_cast<const tv::alignedarray<int, 1, 4> *>(pointer_ + indice_offset + 
                c * 4) + v;
            // std::uintptr_t access_pointer_num = reinterpret_cast<std::uintptr_t>(access_pointer);
            // std::uintptr_t access_pointer_num2 = reinterpret_cast<std::uintptr_t>(pointer_);
            // if (access_pointer_num % 16 != 0 && valid){
            //     tv::printf2(valid, s, access_pointer_num2 % 16, indice_offset, indice_offset%16, "AS", indices_[0], indices_[1], indices_[2], indices_[3], "A", blockIdx.x, blockIdx.y, blockIdx.z);
            // }
            // tv::gemm::global_load<tv::alignedarray<int, 1, 4>, sizeof(tv::alignedarray<int, 1, 4>)>(
            //    frag_ptr[idx], access_pointer, valid);
            GlobalLoad::run(frag_ptr[idx], access_pointer, valid);
          }
        }
      }
    }
  }
  __forceinline__ __device__ const tv::alignedarray<int, 1, 4> * load_ptr_with_param(int s, int c, bool& valid_ref)   {
    
    int mask_idx = s * 1 + 
        c * 1 + 0;
    auto indice_offset = get_indice_offset(s, c, 0);
    valid_ref = bool(mask_[0] & (1u << mask_idx)) && (indice_offset >= 0);
    auto access_pointer = reinterpret_cast<const tv::alignedarray<int, 1, 4> *>(pointer_ + indice_offset + 
        c * 4) + 0;
    return access_pointer;
  }
  __forceinline__ __device__ void load(tv::array<float, 4, 0>& frag)   {
    load_with_pointer_offset(frag, 0);
  }
};
} // namespace inpitera
} // namespace Simt_f32f32f32f32f32tnt_m64n128k8m32n64k8A1_200_C301LLL_SK
} // namespace main
} // namespace conv
} // namespace cumm
} // namespace spconvlib