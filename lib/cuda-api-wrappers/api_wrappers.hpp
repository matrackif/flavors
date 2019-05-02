/**
 * @file api_wrappers.hpp
 *
 * @brief A single file which includes, in turn, all of the CUDA
 * Runtime API wrappers and related headers.
 */
#pragma once
#ifndef CUDA_API_WRAPPERS_HPP_
#define CUDA_API_WRAPPERS_HPP_

#include <api/types.hpp>
#include <api/constants.hpp>
#include <api/error.hpp>
#include <api/versions.hpp>
#include <api/miscellany.hpp>
#include <api/kernel_launch.cuh>
#include <api/profiling.hpp>
#include <api/device_properties.hpp>
#include <api/device_count.hpp>
#include <api/current_device.hpp>
#include <api/device_function.hpp>
#include <api/memory.hpp>
#include <api/pointer.hpp>
#include <api/unique_ptr.hpp>
#include <api/ipc.hpp>

#include <api/stream.hpp>
#include <api/device.hpp>
#include <api/event.hpp>

#include <api/peer_to_peer.hpp>

#include <api/memory_device_impls.hpp>
#include <api/pci_id_impl.hpp>
#include <api/multi_wrapper_impls.hpp>

#endif // CUDA_API_WRAPPERS_HPP_ 
