#ifndef _BMAT_TYPES_H_
#define _BMAT_TYPES_H_

#ifndef MIN
#  define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#  define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

enum bmat_order{ ORDER_ROW=0, ORDER_COL=1};


/****************************************************************************************\
*                                  Matrix type (bmat)                                   *
\****************************************************************************************/

#define BMAT_CN_MAX     512
#define BMAT_CN_SHIFT   3
#define BMAT_DEPTH_MAX  (1 << BMAT_CN_SHIFT)

#define BMAT_8U   0
#define BMAT_8S   1
#define BMAT_16U  2
#define BMAT_16S  3
#define BMAT_32S  4
#define BMAT_32F  5
#define BMAT_64F  6
#define BMAT_64S  7  //Óëopencv²»¼æÈÝ

#define BMAT_DEPTH_MASK       (BMAT_DEPTH_MAX - 1)
#define BMAT_DEPTH(flags)     ((flags) & BMAT_DEPTH_MASK)

#define BMAT_MAKETYPE(depth,cn) (BMAT_DEPTH(depth) + (((cn)-1) << BMAT_CN_SHIFT))
#define BMAT_MAKE_TYPE BMAT_MAKETYPE

#define BMAT_8UC1 BMAT_MAKETYPE(BMAT_8U,1)
#define BMAT_8UC2 BMAT_MAKETYPE(BMAT_8U,2)
#define BMAT_8UC3 BMAT_MAKETYPE(BMAT_8U,3)
#define BMAT_8UC4 BMAT_MAKETYPE(BMAT_8U,4)
#define BMAT_8UC(n) BMAT_MAKETYPE(BMAT_8U,(n))

#define BMAT_8SC1 BMAT_MAKETYPE(BMAT_8S,1)
#define BMAT_8SC2 BMAT_MAKETYPE(BMAT_8S,2)
#define BMAT_8SC3 BMAT_MAKETYPE(BMAT_8S,3)
#define BMAT_8SC4 BMAT_MAKETYPE(BMAT_8S,4)
#define BMAT_8SC(n) BMAT_MAKETYPE(BMAT_8S,(n))

#define BMAT_16UC1 BMAT_MAKETYPE(BMAT_16U,1)
#define BMAT_16UC2 BMAT_MAKETYPE(BMAT_16U,2)
#define BMAT_16UC3 BMAT_MAKETYPE(BMAT_16U,3)
#define BMAT_16UC4 BMAT_MAKETYPE(BMAT_16U,4)
#define BMAT_16UC(n) BMAT_MAKETYPE(BMAT_16U,(n))

#define BMAT_16SC1 BMAT_MAKETYPE(BMAT_16S,1)
#define BMAT_16SC2 BMAT_MAKETYPE(BMAT_16S,2)
#define BMAT_16SC3 BMAT_MAKETYPE(BMAT_16S,3)
#define BMAT_16SC4 BMAT_MAKETYPE(BMAT_16S,4)
#define BMAT_16SC(n) BMAT_MAKETYPE(BMAT_16S,(n))

#define BMAT_32SC1 BMAT_MAKETYPE(BMAT_32S,1)
#define BMAT_32SC2 BMAT_MAKETYPE(BMAT_32S,2)
#define BMAT_32SC3 BMAT_MAKETYPE(BMAT_32S,3)
#define BMAT_32SC4 BMAT_MAKETYPE(BMAT_32S,4)
#define BMAT_32SC(n) BMAT_MAKETYPE(BMAT_32S,(n))

#define BMAT_32FC1 BMAT_MAKETYPE(BMAT_32F,1)
#define BMAT_32FC2 BMAT_MAKETYPE(BMAT_32F,2)
#define BMAT_32FC3 BMAT_MAKETYPE(BMAT_32F,3)
#define BMAT_32FC4 BMAT_MAKETYPE(BMAT_32F,4)
#define BMAT_32FC(n) BMAT_MAKETYPE(BMAT_32F,(n))

#define BMAT_64FC1 BMAT_MAKETYPE(BMAT_64F,1)
#define BMAT_64FC2 BMAT_MAKETYPE(BMAT_64F,2)
#define BMAT_64FC3 BMAT_MAKETYPE(BMAT_64F,3)
#define BMAT_64FC4 BMAT_MAKETYPE(BMAT_64F,4)
#define BMAT_64FC(n) BMAT_MAKETYPE(BMAT_64F,(n))

#define BMAT_AUTO_STEP  0x7fffffff
#define BMAT_WHOLE_ARR  cvSlice( 0, 0x3fffffff )

#define BMAT_CN_MASK          ((BMAT_CN_MAX - 1) << BMAT_CN_SHIFT)
#define BMAT_CN(flags)        ((((flags) & BMAT_CN_MASK) >> BMAT_CN_SHIFT) + 1)
#define BMAT_TYPE_MASK        (BMAT_DEPTH_MAX*BMAT_CN_MAX - 1)
#define BMAT_TYPE(flags)      ((flags) & BMAT_TYPE_MASK)
#define BMAT_CONT_FLAG_SHIFT  14
#define BMAT_CONT_FLAG        (1 << BMAT_CONT_FLAG_SHIFT)
#define BMAT_IS_MAT_CONT(flags)   ((flags) & BMAT_CONT_FLAG)
#define BMAT_IS_CONT_MAT          BMAT_IS_MAT_CONT
#define BMAT_SUBMAT_FLAG_SHIFT    15
#define BMAT_SUBMAT_FLAG          (1 << BMAT_SUBMAT_FLAG_SHIFT)
#define BMAT_IS_SUBMAT(flags)     ((flags) & BMAT_SUBMAT_FLAG)
#define BMAT_COLOR_SPACE_FLAG_SHIFT  12
#define BMAT_COLOR_SPACE(flags)     ((flags) & BMAT_COLOR_SPACE_MASK)


#define BMAT_TYPE_MASK			0x00000FFF
#define BMAT_COLOR_SPACE_MASK   0x0000F000
#define BMAT_MAGIC_MASK			0xFFFF0000
#define BMAT_MAGIC_VAL			0x12340000
#define BMAT_TYPE_NAME_MAT		"binary-matrix"

/* Size of each channel item,
   0x124489 = 1000 0100 0100 0010 0010 0001 0001 ~ array of sizeof(arr_type_elem) */
#define BMAT_ELEM_SIZE1(type) \
    ((((sizeof(size_t)<<28)|0x8442211) >> BMAT_DEPTH(type)*4) & 15)

/* 0x3a50 = 11 10 10 01 01 00 00 ~ array of log2(sizeof(arr_type_elem)) */
#define BMAT_ELEM_SIZE(type) \
    (BMAT_CN(type) << ((((sizeof(size_t)/4+1)*16384|0x3a50) >> BMAT_DEPTH(type)*2) & 3))


enum BMAT_COLOR_SPACE
{
	MAT = 0,
	BMAT_COLOR_GRAY = 1,

	BMAT_COLOR_BGR = 2,  // b1g1r1 b2g2r2 ...
	BMAT_COLOR_BGRA = 3,
	BMAT_COLOR_RGB = 4,
	BMAT_COLOR_RGBA = 5,

	BMAT_COLOR_BGRp = 6, // b1 b2 b3...  g1 g2 g3...   r1 r2 r3...
	BMAT_COLOR_BGRAp = 7,
	BMAT_COLOR_RGBp = 8,
	BMAT_COLOR_RGBAp = 9,

	//YUV 4:2:0 formats family
	BMAT_COLOR_YUV420sp_NV12 = 10,
	BMAT_COLOR_YUV420sp_NV21 = 11,
	BMAT_COLOR_YUV420sp = BMAT_COLOR_YUV420sp_NV21,

	BMAT_COLOR_YUV420p_I420 = 12, //yyyy  uuuu vvvv
	BMAT_COLOR_YUV420p_YV12 = 13, //yyyy  vvvv uuuu
	BMAT_COLOR_YUV420p_IYUV = BMAT_COLOR_YUV420p_I420,
	BMAT_COLOR_YUV420p = BMAT_COLOR_YUV420p_YV12,

	//YUV 4:4:4 formats family
	BMAT_COLOR_YUV444p = 14, //yyyy uuuu vvvv
	BMAT_COLOR_YUV444 = 15, //y1u1v1 y2u2v2

	BMAT_COLOR_MAX = 15
};

#endif