#include "FBADomainExtension.hpp"

#include "configurations/FBAConf.hpp"
#include "domains/collision-avoidance/CollisionAvoidanceFBAExtension.hpp"
#include "domains/dummy/FactoredDummyDomainFBAExtension.hpp"
#include "domains/gridworld/GridWorldFBAExtension.hpp"
#include "domains/sysadmin/SysAdminFBAExtension.hpp"
#include "domains/tiger/FactoredTigerFBAExtension.hpp"

namespace factory {
std::unique_ptr<FBADomainExtension> makeFBADomainExtension(configurations::FBAConf const& c)
{

    auto const d = c.domain_conf.domain;

    namespace ext = bayes_adaptive::domain_extensions;

    if (d == "factored-dummy")
        return std::unique_ptr<FBADomainExtension>(
            new ext::FactoredDummyDomainFBAExtension(c.domain_conf.size));
    if (d == "independent-sysadmin" || d == "linear-sysadmin")
        return std::unique_ptr<FBADomainExtension>(
            new ext::SysAdminFBAExtension(c.domain_conf.size));

    if (d == "episodic-factored-tiger" || d == "continuous-factored-tiger")
        return std::unique_ptr<FBADomainExtension>(
            new ext::FactoredTigerFBAExtension(c.domain_conf.size));

    if (d == "gridworld")
        return std::unique_ptr<FBADomainExtension>(
            new ext::GridWorldFBAExtension(c.domain_conf.size));

    if (d == "random-collision-avoidance" || d == "centered-collision-avoidance")
    {
        if (d == "random-collision-avoidance")
            return std::unique_ptr<FBADomainExtension>(new ext::CollisionAvoidanceFBAExtension(
                c.domain_conf.width,
                c.domain_conf.height,
                c.domain_conf.size,
                domains::CollisionAvoidance::VERSION::INIT_RANDOM_POSITION));
        else
            return std::unique_ptr<FBADomainExtension>(new ext::CollisionAvoidanceFBAExtension(
                c.domain_conf.width,
                c.domain_conf.height,
                c.domain_conf.size,
                domains::CollisionAvoidance::VERSION::INITIALIZE_CENTRE));
    }

    throw "incorrect domain provided, " + d + " is not supported as tabular BA-POMDP";
}

} // namespace factory
