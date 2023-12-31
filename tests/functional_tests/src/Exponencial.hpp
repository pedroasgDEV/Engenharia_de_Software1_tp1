/*************************************************************
 * @file Exponencial.h
 * @author Pedro Augusto Sousa Gonçalves
 * @brief This file represents the exponential simulation flow
*************************************************************/

#ifndef EXPONENCIAL_HPP
#define EXPONENCIAL_HPP

#include <string.h>
#include "../../../src/FlowIMP.hpp"

/**************************************************************************************************************************
 * @brief This Flow class connects two systems and through the entered equation transfers values ​​from one system to another 
**************************************************************************************************************************/

class Exponencial : public FlowIMP{
    private:
        /**
         * @brief Construct a new Exponencial by a obj
         * @param other Exponencial obj
        */
        Exponencial(const Exponencial& other);

    public:
        //Contructor
        /**
         * @brief Construct a new Exponencial by name, source and target
         * @param name string with default value "NO_NAME"
         * @param source System pointer with default value NULL
         * @param target System pointer with default value NULL
        */
        Exponencial(const std::string& name = "NO_NAME", System* source = nullptr, System* target = nullptr);
    
        //Destructor
        /**
         * @brief This destructor is a virtual destructor of the Class
        */
        virtual ~Exponencial() override;

        //Metodos
        /**
         * @brief Pure virtual method that will contain an equation that will be executed in the flow by the model.
         * @return double 
        */
        virtual double execute() override;
};

#endif