/*******************************************************
 * Copyright (c) 2017, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <af/nn/Modules/Module.hpp>

namespace af
{
    namespace nn
    {
        using autograd::Variable;
        Module::Module() :
            m_parameters()
        {
            m_train = false;
        }

        Module::Module(const std::vector<Variable> &parameters) :
            m_parameters(parameters.begin(), parameters.end())
        {
        }

        void Module::setParams(const std::vector<Variable> &parameters)
        {
            m_parameters.clear();
            for(auto parameter : parameters) {
                m_parameters.push_back(parameter);
            }
        }

        void Module::train()
        {
            m_train = true;
            for (auto &parameter : m_parameters) {
                parameter.setCalcGrad(true);
            }
        }

        void Module::eval()
        {
            m_train = false;
            for (auto &parameter : m_parameters) {
                parameter.setCalcGrad(false);
            }
        }

        std::vector<Variable> Module::parameters()
        {
            return m_parameters;
        }

        Variable Module::operator()(const Variable &input)
        {
            return this->forward(input);
        }
    }
}
