#ifndef MIGRAPHX_GUARD_RTGLIB_HORIZONTAL_FUSION_HPP
#define MIGRAPHX_GUARD_RTGLIB_HORIZONTAL_FUSION_HPP

#include <string>
#include <migraphx/instruction_ref.hpp>
#include <migraphx/config.hpp>

namespace migraphx {
inline namespace MIGRAPHX_INLINE_NS {
struct program;

/**
 * Horizontal fusion.
 */
struct horizontal_fusion
{
    std::string name() const { return "horizontal fusion"; }
    void apply(program& p) const;
};

} // namespace MIGRAPHX_INLINE_NS
} // namespace migraphx

#endif
