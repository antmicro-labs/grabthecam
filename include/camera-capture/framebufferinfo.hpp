#pragma once

#include <sys/mman.h>

#include <cstring> //memset
#include <iostream>
#include <memory>


/**
 * Class for managing memory mapping and keeping information about buffer.
 */
class FrameBufferInfo
{
public:
    /**
     * Constructor. Maps the memory.
     *
     * @param location Pointer to a memory location, where frame should be placed. If not provided, the kernel chooses the (page-aligned) address at which to create the mapping. For more information see mmap documentation.
     * @param size Size of the buffer to allocate
     * @param fd Camera file descriptor
     * @param offset Offset in fd. For more information see mmap documentation
     */
    FrameBufferInfo(void* location, int size, int fd, int offset);


    FrameBufferInfo(void* location, int bytes): start(location), bytesused(bytes){}
    /**
     * Destructor. Unmaps the memory
     */
    ~FrameBufferInfo();

    unsigned int bytesused; ///< bytes used by a captured frame
    void* start; ///< pointer to the memry location, where the buffer starts
    int size; ///< size of the buffer
};

using fbi_ptr = std::shared_ptr<FrameBufferInfo>;
