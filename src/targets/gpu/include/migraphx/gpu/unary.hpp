#ifndef MIGRAPHX_GUARD_RTGLIB_UNARY_HPP
#define MIGRAPHX_GUARD_RTGLIB_UNARY_HPP

#include <migraphx/gpu/lowering.hpp>
#include <migraphx/manage_ptr.hpp>
#include <migraphx/instruction.hpp>
#include <migraphx/operators.hpp>
#include <migraphx/generate.hpp>
#include <migraphx/shape_for_each.hpp>
#include <migraphx/gpu/miopen.hpp>
#include <migraphx/gpu/hip.hpp>
#include <migraphx/dfor.hpp>
#include <migraphx/type_name.hpp>
#include <migraphx/gpu/device/contiguous.hpp>
#include <migraphx/iterator_for.hpp>
#include <migraphx/gpu/rocblas.hpp>
#include <migraphx/gpu/context.hpp>
#include <migraphx/config.hpp>
#include <utility>

namespace migraphx {
inline namespace MIGRAPHX_INLINE_NS {
namespace gpu {

template<class Derived>
struct oper
{
    std::string name() const { return get_type_name<Derived>(); }
};

template<class Derived, void(*F)(hipStream_t, const argument&, const argument&)>
struct unary_device : oper<Derived>
{
    shape compute_shape(const std::vector<shape>& inputs) const {
        check_shapes{inputs, *this}.has(2);
        return inputs.at(0);
    }

    argument compute(context& ctx, const shape&, const std::vector<argument>& args) const {
        F(ctx.get_stream().get(), args[1], args[0]);
        return args[1];
    }

    int output_alias(const std::vector<shape>& shapes) const { return shapes.size() - 1; }
};

template<class Derived, void(*F)(hipStream_t, const argument&, const argument&, const argument&)>
struct binary_device : oper<Derived>
{
    shape compute_shape(const std::vector<shape>& inputs) const {
        check_shapes{inputs, *this}.has(3);
        return inputs.at(0);
    }

    argument compute(context& ctx, const shape&, const std::vector<argument>& args) const {
        F(ctx.get_stream().get(), args[2], args[1], args[0]);
        return args[2];
    }

    int output_alias(const std::vector<shape>& shapes) const { return shapes.size() - 1; }
};


} // namespace gpu
} // namespace MIGRAPHX_INLINE_NS
} // namespace migraphx

#endif
