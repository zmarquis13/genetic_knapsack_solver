/*
* main.cpp - Main file for genetic algorithm program
* Author: Zeno Marquis
* HW3: Genetic Algorithms
* 3/19/2024
*/

#include "Individual.hpp"

#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

void initialize_population(std::vector<Individual> *population);
std::vector<Individual> *evolve(std::vector<Individual> *population);
std::vector<Individual> *recombine(std::vector<Individual> *population);
std::vector<Individual> *mutate(std::vector<Individual> *population);
float caclulate_average_fitness(std::vector<Individual> *population);

/**
     * Main function for genetic algorithm
     */
int main(){

    srand (time(NULL));

    std::vector<Individual> population;
    initialize_population(&population);
    evolve(&population);

    return 0;
}

/**
     * Initializes the population with size 100
     * 
     * @param population Pointer to the vector containing the whole population
     */
void initialize_population(std::vector<Individual> *population){

    std::vector<int> genes;

    //starting (and final) population size of 100
    for (int i = 0; i < 100; i++){
        //genotype has 12 binary genes (one for each box, 
        //1 means it's included in the bag)
        for (int j = 0; j < 12; j++){
            genes.push_back(rand() % 2);
        }

        Individual *ip = new Individual(genes);
        population->push_back(*ip);
        genes.clear();
        
    }
}

/**
     * Performs 50 rounds of evolution on the population
     * 
     * @param population Pointer to the vector containing the whole population
     * 
     * @return a pointer to the population vector after evolution has occurred 
     */
std::vector<Individual> *evolve(std::vector<Individual> *population){

    //performs 50 rounds of evolution 
    for (int i = 0; i < 50; i++){
        //sort the population by fitness
        std::sort(population->begin(), population->end());

        //culling by replacing lower half of population 
        //with copies of fitter individuals
        int half_population_size = population->size()/2;
        for (int j = 0; j < half_population_size; j++){

            Individual *ip = new Individual(population->at(half_population_size + j).get_genotype());
            population->at(j) = *ip;
        }

        population = recombine(population);
        population = mutate(population);

        cout << "Average fitness of round " << i + 1 << ": ";
        cout << caclulate_average_fitness(population) << endl;

    }

    return population;
}

/**
     * Parirs up and recombines the genes of all surviving individuals after
     * the culling
     * 
     * @param population Pointer to the vector containing the whole population
     * 
     * @return a pointer to the population vector after recombination has
     * been carried out 
     */
std::vector<Individual> *recombine(std::vector<Individual> *population){

    std::vector<Individual> new_population;

    while (population->size() != 0){

        //random index in the population that's not index 0
        int random_index = 1 + rand() % (population->size() - 1);

        std::vector<int> genome1 = population->at(random_index).get_genotype();
        std::vector<int> genome2 = population->at(0).get_genotype();

        population->erase(population->begin() + random_index);
        population->erase(population->begin());

        //pick a random crossing over point and cross over past it
        int swap_index = rand() % genome1.size();

        for (int i = swap_index; i < genome1.size(); i++){
            int temp = genome1.at(i);
            genome1.at(i) = genome2.at(i);
            genome2.at(i) = temp;
        }

        //create individuals with the new crossed over genotypes and put them
        //into a new population
        Individual *i1 = new Individual(genome1);
        Individual *i2 = new Individual(genome2);

        new_population.push_back(*i1);
        new_population.push_back(*i2);

    }

    //make the current population into the one of crossed over individuals
    *population = new_population;
    return population;
    
}

/**
     * Mutates all the individuals in the population
     * 
     * @param population Pointer to the vector containing the whole population
     * 
     * @return a pointer to the population vector after mutation has occurred 
     */
std::vector<Individual> *mutate(std::vector<Individual> *population){

    for (int i = 0; i < population->size(); i++){
        std::vector<int> mutated_genotype = population->at(i).get_genotype();

        //every gene flips with a random low probability
        for (int j = 0; j < mutated_genotype.size(); j++){
            //rate determined using trial and error
            if (rand() % 750 == 0){
                mutated_genotype.at(j) = (mutated_genotype.at(j) + 1) % 2;
            }
        }

        population->at(i).set_genotype(mutated_genotype);

    }

    return population;

}

/**
     * Calculates the average fitness of the population
     * 
     * @param population Pointer to the vector containing the whole population
     * 
     * @return a float representing the average fitness of the population
     */
float caclulate_average_fitness(std::vector<Individual> *population){

    float result = 0.0;

    for (int i = 0; i < population->size(); i++){
        result += population->at(i).get_fitness();
    }

    return result/population->size();

}
