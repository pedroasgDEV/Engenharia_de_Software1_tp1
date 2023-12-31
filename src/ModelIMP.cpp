#include "ModelIMP.hpp"

//Constructors
ModelIMP::ModelIMP (const std::string& name, const int& startTime, const int& endTime) : name(name), startTime(startTime), endTime(endTime) {}
//Copia outro model
ModelIMP::ModelIMP (const ModelIMP& other) : name(other.name), startTime(other.startTime), endTime(other.endTime) {
    flows.clear();
    systems.clear();
    for (auto i : other.flows) flows.push_back(i);
    for (auto i : other.systems) systems.push_back(i);
}

//Destructor
ModelIMP::~ModelIMP(){systems.clear(); flows.clear();}

//Geters e seters
//Name
std::string ModelIMP::getName() const { return name; }
void ModelIMP::setName(const std::string& name) { this->name = name; }
//Vectors
std::vector<System*> ModelIMP::getSystems() const { return systems;}
std::vector<Flow*>  ModelIMP::getFlows() const { return flows;};
void ModelIMP::setSystems(const std::vector<System*> systems){ this->systems.clear(); for(auto i : systems) this->systems.push_back(i);}
void ModelIMP::setFlows(const std::vector<Flow*> flows){ this->flows.clear(); for(auto i : flows) this->flows.push_back(i);}
//Timer
int ModelIMP::getStartTime() const { return startTime; }
int ModelIMP::getEndTime() const { return endTime; }
void ModelIMP::setStartTime(const int& startTime) { this->startTime = startTime; }
void ModelIMP::setEndTime(const int& endTime) { this->endTime = endTime; }
void ModelIMP::setTime(const int& startTime, const int& endTime) { this->startTime = startTime; this->endTime = endTime; }

//Metodos
//add
void ModelIMP::add(System* system) { systems.push_back(system); } 
void ModelIMP::add(Flow* flow) { flows.push_back(flow); } 
//remove
bool ModelIMP::rmv(const System* system) { 
    for(systemIterator i = systems.begin(); i < systems.end(); i++)
        if(*i == system){
            systems.erase(i);
            return true;
        }
    return false; 
}
bool ModelIMP::rmv(const Flow* flow) { 
    for(flowIterator i = flows.begin(); i < flows.end(); i++)
        if(*i == flow){
            flows.erase(i);
            return true;
        }
    return false; 
}


//Others
bool ModelIMP::run(){
    std::vector<double> flowValue;
    flowIterator f;
    std::vector<double>::iterator d;
    double calcValue;

    for(int i = startTime; i < endTime; i++){

        f = flows.begin();

        while (f != flows.end()) {
            flowValue.push_back((*f)->execute());
            f++;
        }
        
        f = flows.begin();
        d = flowValue.begin();
        
        while(f != flows.end()){
            calcValue = (*f)->getSource()->getValue() - (*d);
            (*f)->getSource()->setValue(calcValue);
            calcValue = (*f)->getTarget()->getValue() + (*d);
            (*f)->getTarget()->setValue(calcValue);
            f++;
            d++;
        }

        flowValue.clear();

    }

    return true;
} 

//Sobrecarga de operadores
// Operador de atribuição
ModelIMP& ModelIMP::operator=(const ModelIMP& other){
    if(other == *this) return *this;
    name = other.name;
    flows.clear();
    systems.clear();
    for (auto i : other.flows) flows.push_back(i);
    for (auto i : other.systems) systems.push_back(i);
    startTime = other.startTime;
    endTime = other.endTime;
    return *this;
}
// Operador de igualdade
bool ModelIMP::operator==(const ModelIMP& other) const{
    return (name == other.name && systems == other.systems && flows == other.flows && startTime == other.startTime && endTime == other.endTime);
}
// Operador de diferença
bool ModelIMP::operator!=(const ModelIMP& other) const{
    return (name != other.name || systems != other.systems || flows != other.flows || startTime != other.startTime || endTime != other.endTime);
}
