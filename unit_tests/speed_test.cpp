
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../rhea/simplex_solver.hpp"
#include "../rhea/linear_equation.hpp"

inline
double uniform_rand()
{ return double(rand())/RAND_MAX; }

inline
double grained_rand()
{
  const double grain (1.0e-4);
  return int(uniform_rand()/grain) * grain;
}

int main (int argc, char** argv)
{
    using std::chrono::system_clock;

    size_t cns (500), resolves (500), solvers (10);

    const double ineq_prob (0.12);
    const unsigned int max_vars (3), nr_vars (cns);

    system_clock clock;

    std::vector<rhea::simplex_solver> slv (solvers);
    for (auto& s : slv) s.set_autosolve(false);

    std::vector<rhea::variable>       vars;
    for (size_t i (0); i < nr_vars; ++i)
    {
        vars.emplace_back((int)i);
        for (auto& s : slv) s.add_stay(vars[i]);
    }

    size_t cns_made (cns * 2);
    std::vector<rhea::constraint> constraints (cns_made);

    for (size_t j (0); j < cns_made; ++j)
    {
        size_t nvs ((uniform_rand() * max_vars) + 1);
        rhea::linear_expression expr (grained_rand() * 20.0 - 10.0);
        for (size_t k (0); k < nvs; ++k)
        {
            double coeff (grained_rand() * 10.0 - 5.0);
            expr += rhea::linear_expression(vars[uniform_rand()*nr_vars]) * coeff;
        }
        if (uniform_rand() < ineq_prob)
            constraints[j] = new rhea::linear_inequality(std::move(expr));
        else
            constraints[j] = new rhea::linear_equation(std::move(expr));
    }

    auto timer (clock.now());
    for (auto& s : slv)
    {
        size_t added(0), exceptions(0);
        for (size_t j (0); added < cns && j < cns_made; ++j)
        {
            try
            {
                s.add_constraint(constraints[j]);
                ++added;
            }
            catch(...)
            {
                ++exceptions;
            }
        }
    }
    auto end (clock.now());
    auto time_add (end - timer);

    // ------

    rhea::variable e1 (vars[uniform_rand() * nr_vars]);
    rhea::variable e2 (vars[uniform_rand() * nr_vars]);

    timer = clock.now();
    for (auto& s : slv)
        s.add_edit_var(e1).add_edit_var(e2);

    auto time_edit (clock.now() - timer);

    // ------

    timer = clock.now();
    for (auto& s : slv)
    {
        s.begin_edit();
        for (size_t m (0); m < resolves; ++m)
        {
            s.suggest_value(e1, e1.value() * 1.001)
             .suggest_value(e2, e2.value() * 1.001)
             .resolve();
        }
    }
    auto time_resolve (clock.now() - timer);

    // ------

    timer = clock.now();
    for (auto& s : slv)
        s.end_edit();

    auto time_endedit (clock.now() - timer);

    // ------

    double f (0.001);
    std::cout << "add: " << time_add.count()*f << "ms  edit: " << time_edit.count()*f
              << "ms  resolve: " << time_resolve.count()*f << "ms  endedit: "
              << time_endedit.count()*f << "ms" << std::endl;

    return 0;
}

