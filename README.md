# Introduction

This package is a ROS wrapper for [traveller59](https://github.com/traveller59/spconv)'s implementation of sparse convolutions.

The code was generated using the following versions:
 - spconv: 2.3.8
 - cumm: 0.5.3
 - CUDA: 12.3
 - architecture: 8.6

# Building

These packages can be built normally, provided CUDA is available:

```bash
colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release
```

# Testing

A simple test of this package can be run using the following command:

```bash
./build/spconv_example/main benchmark-pc.jarr 
```

The `benchmark-pc.jarr` can be obtained in the original [repository](https://github.com/traveller59/spconv/blob/master/example/libspconv/benchmark-pc.jarr)

# Notes

Although the original code was generated for the `8.6` architecture, it was overwritten to `7.5` and `8.6`. To support other architectures natively, the `CMAKE_CUDA_ARCHITECTURES` needs to be modified.