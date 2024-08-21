#ifndef _HACKS_H_
#define _HACKS_H_

  #ifndef   __ASM
    #define __ASM                                  __asm
  #endif
  #ifndef   __INLINE
    #define __INLINE                               inline
  #endif
  #ifndef   __STATIC_INLINE
    #define __STATIC_INLINE                        static inline
  #endif
  #ifndef   __STATIC_FORCEINLINE
    #define __STATIC_FORCEINLINE                   __STATIC_INLINE
  #endif
    
  typedef float float32_t;
#endif
