/*******************************************************************************
 *
 * MIT License
 *
 * Copyright 2021-2022 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#include "gemm_coop_wg_test_includes.hpp"

namespace rocwmma
{

    struct TestParams : public CooperativeTestParams
    {
        using Base = CooperativeTestParams;

        // Assemble testing parameters
        using Types       = typename Base::TestTypes16x16;
        using BlockSizes  = typename Base::TestBlockSizes16x16SmallMT;
        using Layouts     = typename Base::TestLayoutsNN;
        using LayoutsLds  = typename Base::TestLdsDataLayouts;
        using GemmConfigs = typename Base::TestGemmConfigsWgLevel;
        using BlocksXY    = typename Base::TestBlocks2x2;
        using KernelParams =
            typename CombineLists<Types, BlockSizes, Layouts, LayoutsLds, GemmConfigs, BlocksXY>::
                Result;

        // Assemble the kernel generator
        using GeneratorImpl   = typename Base::KernelGeneratorImplWorkgroupLevel;
        using KernelGenerator = KernelGenerator<KernelParams, GeneratorImpl>;

        // Sanity check for kernel generator
        static_assert(std::is_same<typename GeneratorImpl::ResultT, typename Base::KernelT>::value,
                      "Kernels from this generator do not match testing interface");

        static inline typename KernelGenerator::ResultT kernels()
        {
            return KernelGenerator::generate();
        }
    };

} // namespace rocwmma

// Instantiate kernels as a test suite
ROCWMMA_INSTANTIATE_GTEST_SUITE(GemmCoopWgTests, GemmCoopWgTest16x16NN2x2);
