//----------------------------------------------------------------------------//
//|
//|             MachOKit - A Lightweight Mach-O Parsing Library
//|             data_model.c
//|
//|             D.V.
//|             Copyright (c) 2014-2015 D.V. All rights reserved.
//|
//| Permission is hereby granted, free of charge, to any person obtaining a
//| copy of this software and associated documentation files (the "Software"),
//| to deal in the Software without restriction, including without limitation
//| the rights to use, copy, modify, merge, publish, distribute, sublicense,
//| and/or sell copies of the Software, and to permit persons to whom the
//| Software is furnished to do so, subject to the following conditions:
//|
//| The above copyright notice and this permission notice shall be included
//| in all copies or substantial portions of the Software.
//|
//| THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//| OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//| MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//| IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//| CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//| TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//| SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//----------------------------------------------------------------------------//

#include "core_internal.h"

//----------------------------------------------------------------------------//
#pragma mark -  Base Class
//----------------------------------------------------------------------------//

//|++++++++++++++++++++++++++++++++++++|//
static const mk_byteorder_t*
__mk_data_model_get_byte_order(mk_data_model_ref self)
{
#pragma unused (self)
    fprintf(stderr, "No default implementation of __mk_data_model_get_byte_order.");
    __builtin_trap();
}

//|++++++++++++++++++++++++++++++++++++|//
static size_t
__mk_data_model_get_pointer_size(mk_data_model_ref self)
{
#pragma unused (self)
    fprintf(stderr, "No default implementation of __mk_data_model_get_pointer_size.");
    __builtin_trap();
}

//|++++++++++++++++++++++++++++++++++++|//
static size_t
__mk_data_model_get_pointer_alignment(mk_data_model_ref self)
{
#pragma unused (self)
    fprintf(stderr, "No default implementation of __mk_data_model_get_pointer_alignment.");
    __builtin_trap();
}

static struct _mk_data_model_vtable __mk_data_model_class = {
    .base.super             = &_mk_type_class,
    .base.name              = "data_model",
    .get_byte_order         = &__mk_data_model_get_byte_order,
    .get_pointer_size       = &__mk_data_model_get_pointer_size,
    .get_pointer_alignment  = &__mk_data_model_get_pointer_alignment
};

//----------------------------------------------------------------------------//
#pragma mark -  ILP32 Class
//----------------------------------------------------------------------------//

//|++++++++++++++++++++++++++++++++++++|//
static const mk_byteorder_t*
__mk_data_model_ilp32_get_byte_order(mk_data_model_ref self)
{
#pragma unused (self)
#if TARGET_RT_BIG_ENDIAN
    return &mk_byteorder_swapped;
#else
    return &mk_byteorder_direct;
#endif
}

//|++++++++++++++++++++++++++++++++++++|//
static size_t
__mk_data_model_ilp32_get_pointer_size(mk_data_model_ref self)
{
#pragma unused (self)
    return 4;
}

//|++++++++++++++++++++++++++++++++++++|//
static size_t
__mk_data_model_ilp32_get_pointer_alignment(mk_data_model_ref self)
{
#pragma unused (self)
    return 4;
}

static struct _mk_data_model_vtable __mk_data_model_ilp32_class = {
    .base.super             = &__mk_data_model_class,
    .base.name              = "ilp32_data_model",
    .get_byte_order         = &__mk_data_model_ilp32_get_byte_order,
    .get_pointer_size       = &__mk_data_model_ilp32_get_pointer_size,
    .get_pointer_alignment  = &__mk_data_model_ilp32_get_pointer_alignment
};

//----------------------------------------------------------------------------//
#pragma mark -  LP64 Class
//----------------------------------------------------------------------------//

//|++++++++++++++++++++++++++++++++++++|//
static const mk_byteorder_t*
__mk_data_model_lp64_get_byte_order(mk_data_model_ref self)
{
#pragma unused (self)
#if TARGET_RT_BIG_ENDIAN
    return &mk_byteorder_swapped;
#else
    return &mk_byteorder_direct;
#endif
}

//|++++++++++++++++++++++++++++++++++++|//
static size_t
__mk_data_model_lp64_get_pointer_size(mk_data_model_ref self)
{
#pragma unused (self)
    return 8;
}

//|++++++++++++++++++++++++++++++++++++|//
static size_t
__mk_data_model_lp64_get_pointer_alignment(mk_data_model_ref self)
{
#pragma unused (self)
    return 8;
}

static struct _mk_data_model_vtable __mk_data_model_lp64_class = {
    .base.super             = &__mk_data_model_class,
    .base.name              = "lp64_data_model",
    .get_byte_order         = &__mk_data_model_lp64_get_byte_order,
    .get_pointer_size       = &__mk_data_model_lp64_get_pointer_size,
    .get_pointer_alignment  = &__mk_data_model_lp64_get_pointer_alignment
};

//----------------------------------------------------------------------------//
#pragma mark -  Static Types
//----------------------------------------------------------------------------//

struct mk_data_model_s ILP32_byte_order = {
    .vtable                 = &__mk_data_model_ilp32_class,
};

struct mk_data_model_s LP64_byte_order = {
    .vtable                 = &__mk_data_model_lp64_class,
};

//----------------------------------------------------------------------------//
#pragma mark -  Interacting With Memory Objects
//----------------------------------------------------------------------------//

//|++++++++++++++++++++++++++++++++++++|//
mk_data_model_ref
mk_data_model_ilp32()
{
    mk_data_model_ref data_model;
    data_model.data_model = &ILP32_byte_order;
    return data_model;
}

//|++++++++++++++++++++++++++++++++++++|//
mk_data_model_ref
mk_data_model_lp64()
{
    mk_data_model_ref data_model;
    data_model.data_model = &LP64_byte_order;
    return data_model;
}

//----------------------------------------------------------------------------//
#pragma mark -  Instance Methods
//----------------------------------------------------------------------------//

//|++++++++++++++++++++++++++++++++++++|//
const mk_byteorder_t*
mk_data_model_get_byte_order(mk_data_model_ref data_model)
{ MK_TYPE_INVOKE(data_model, data_model, get_byte_order)(data_model); }

//|++++++++++++++++++++++++++++++++++++|//
size_t
mk_data_model_get_pointer_size(mk_data_model_ref data_model)
{ MK_TYPE_INVOKE(data_model, data_model, get_pointer_size)(data_model); }

//|++++++++++++++++++++++++++++++++++++|//
size_t
mk_data_model_get_pointer_alignment(mk_data_model_ref data_model)
{ MK_TYPE_INVOKE(data_model, data_model, get_pointer_alignment)(data_model); }
