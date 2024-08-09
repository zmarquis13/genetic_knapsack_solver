/*
* Individual.hpp - Definition of the individual class
* Author: Zeno Marquis
* HW3: Genetic Algorithms
* 3/19/2024
*/

#include <vector>

//individual class definition
class Individual{
    
public:
    //instantiates individual using a given genotype
    Individual(std::vector<int> genes){

        this->genotype = genes;
        this->fitness_value = determine_fitness();

    }

    //calculates the fitness value based on the boxes present
    int determine_fitness(){

        int fitness = 0;
        int weight = 0;

        if (this->genotype.at(0) == 1){
            fitness += 6;
            weight += 20;
        }

        if (this->genotype.at(1) == 1){
            fitness += 5;
            weight += 30;
        }

        if (this->genotype.at(2) == 1){
            fitness += 8;
            weight += 60;
        }
        
        if (this->genotype.at(3) == 1){
            fitness += 7;
            weight += 90;
        }
        
        if (this->genotype.at(4) == 1){
            fitness += 6;
            weight += 50;
        }
        
        if (this->genotype.at(5) == 1){
            fitness += 9;
            weight += 70;
        }
        
        if (this->genotype.at(6) == 1){
            fitness += 4;
            weight += 30;
        }
        
        if (this->genotype.at(7) == 1){
            fitness += 5;
            weight += 30;
        }
        
        if (this->genotype.at(8) == 1){
            fitness += 4;
            weight += 70;
        }
        
        if (this->genotype.at(9) == 1){
            fitness += 9;
            weight += 20;
        }
        
        if (this->genotype.at(10) == 1){
            fitness += 2;
            weight += 20;
        }
        
        if (this->genotype.at(11) == 1){
            fitness += 1;
            weight += 60;
        }

        //returns 0 if the backpack is too heavy
        if (weight <= 250){
            return fitness;
        } else {
            return 0;
        }
    }

    //defines a comparison operator so that individuals can be sorted by fitness
    bool operator<(const Individual& n) const {

        return (this->fitness_value < n.fitness_value);

    }

    //genotype getter
    std::vector<int> get_genotype(){
        return this->genotype;
    }

    //genotype setter
    void set_genotype(std::vector<int> new_genotype){
        this->genotype = new_genotype;
    }
        
    //fitness getter
    int get_fitness(){
        return this->fitness_value;
    }


private:
    std::vector<int> genotype;
    int fitness_value;

};
