/**
 * @brief デバイスメモリによってバックアップされたVulkan
 * Bufferへのアクセスをカプセル化します。
 */

#pragma once

#include <vector>
#include <vulkan/vulkan.h>

struct Device;

struct Buffer {
  [[nodiscard]] VkResult Create(const Device &device,
                                VkBufferUsageFlags bufferUsageFlags,
                                VkMemoryPropertyFlags memoryPropertyFlags,
                                VkDeviceSize size, void* data);
  [[nodiscard]] VkResult Create(const Device &device,
                                VkBufferUsageFlags bufferUsageFlags,
                                VkMemoryPropertyFlags memoryPropertyFlags,
                                VkDeviceSize size);
  void Destroy(const Device &device) const;

  [[nodiscard]] VkResult Map(const Device &device,
                             VkDeviceSize size = VK_WHOLE_SIZE,
                             VkDeviceSize offset = 0);
  void Unmap(const Device &device);
  [[nodiscard]] VkResult Bind(const Device &device,
                              VkDeviceSize offset = 0) const;

  void SetupDescriptor(VkDeviceSize size = VK_WHOLE_SIZE,
                       VkDeviceSize offset = 0);
  void Copy(void *data, VkDeviceSize size) const;
  [[nodiscard]] VkResult Flush(const Device &device,
                               VkDeviceSize size = VK_WHOLE_SIZE,
                               VkDeviceSize offset = 0) const;
  [[nodiscard]] VkResult Invalidate(const Device &device,
                                    VkDeviceSize size = VK_WHOLE_SIZE,
                                    VkDeviceSize offset = 0) const;

  VkBuffer buffer = VK_NULL_HANDLE;
  VkDeviceMemory memory = VK_NULL_HANDLE;
  VkDescriptorBufferInfo descriptor{};
  void *mapped = nullptr;
};
