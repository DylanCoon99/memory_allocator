Memory Allocator



  ┌──────────────┬─────────────────────────────┐
  │ Block Header │      Usable Memory          │
  │ (size, next) │   (returned to user)        │
  └──────────────┴─────────────────────────────┘
  ^               ^
  |               |
  block ptr       what malloc() returns



Free list implementation

  Minimum block size must hold:
  - Size field (4-8 bytes)
  - Next pointer for the free list (8 bytes on 64-bit)
  - Typically 16-24 bytes minimum on 64-bit systems

  Alignment matters:
  - Most systems require 8 or 16-byte alignment
  - On macOS/ARM64, 16-byte alignment is standard
  - Round your block sizes to alignment boundaries







Free list allocator
Coalescing blocks
Segregated free lists
Buddy allocator
mmap for large allocations
Thread-local arenas