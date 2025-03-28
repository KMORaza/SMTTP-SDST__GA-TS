#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;
struct Job {
    int id;             
    int processingTime;   // p_i
    int dueDate;          // d_i
    int weight;           // w_i 
};
struct Solution {
    vector<int> sequence; 
    int totalTardiness;   
};
struct Problem {
    int n;                      
    vector<Job> jobs;             
    vector<vector<int>> setupTimes; // s[i][j] 
};

// Berechnen Sie die gewichtete Gesamtverspätung für eine gegebene Sequenz
// Calculate weighted total tardiness for a given sequence
int calculateTardiness(const Problem& problem, const vector<int>& sequence) {
    int completionTime = 0;
    int totalTardiness = 0;
    for (int i = 0; i < problem.n; ++i) {
        int currJob = sequence[i];
        if (i > 0) {
            int prevJob = sequence[i - 1];
            completionTime += problem.setupTimes[prevJob][currJob];
        }
        completionTime += problem.jobs[currJob].processingTime;
        int tardiness = max(0, completionTime - problem.jobs[currJob].dueDate);
        totalTardiness += tardiness * problem.jobs[currJob].weight; 
    }
    return totalTardiness;
}

// Generieren Sie eine zufällige Lösung
// Generate a random solution 
vector<int> generateRandomSolution(int n) {
    vector<int> sequence(n);
    for (int i = 0; i < n; ++i) sequence[i] = i;
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(sequence[i], sequence[j]);
    }
    return sequence;
}

// Crossover operator (Order Crossover - OX)
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    int n = parent1.size();
    vector<int> child(n, -1);
    int start = rand() % n;
    int end = rand() % n;
    if (start > end) swap(start, end);
    for (int i = start; i <= end; ++i) {
        child[i] = parent1[i];
    }
    int pos = (end + 1) % n;
    for (int i = 0; i < n; ++i) {
        int job = parent2[i];
        if (find(child.begin(), child.end(), job) == child.end()) {
            while (child[pos] != -1) pos = (pos + 1) % n;
            child[pos] = job;
            pos = (pos + 1) % n;
        }
    }
    return child;
}

// Tausche zwei zufällige Positionen (Swap two random positions)
void mutate(vector<int>& sequence) {
    int n = sequence.size();
    int i = rand() % n;
    int j = rand() % n;
    while (i == j) j = rand() % n;
    swap(sequence[i], sequence[j]);
}

// Tabu Search zur Verbesserung einer Lösung (Tabu Search to improve a solution)
Solution tabuSearch(const Problem& problem, const vector<int>& initialSequence, int maxIterations, int tabuTenure) {
    vector<int> current = initialSequence;
    int currentTardiness = calculateTardiness(problem, current);
    vector<int> best = current;
    int bestTardiness = currentTardiness;
    vector<pair<int, int>> tabuList; // speichert Paare vertauschter Indizes (stores pairs of swapped indices)
    int iteration = 0;
    cout << "Starting Tabu Search with initial tardiness = " << currentTardiness << endl;
    while (iteration < maxIterations) {
        int bestNeighborTardiness = INT_MAX;
        vector<int> bestNeighbor = current;
        pair<int, int> bestMove = {-1, -1};
        for (int i = 0; i < problem.n - 1; ++i) {
            for (int j = i + 1; j < problem.n; ++j) {
                vector<int> neighbor = current;
                swap(neighbor[i], neighbor[j]);
                int neighborTardiness = calculateTardiness(problem, neighbor);
                pair<int, int> move = {i, j};
                bool isTabu = find(tabuList.begin(), tabuList.end(), move) != tabuList.end() ||
                              find(tabuList.begin(), tabuList.end(), make_pair(j, i)) != tabuList.end();
                if ((!isTabu && neighborTardiness < bestNeighborTardiness) ||
                    (neighborTardiness < bestTardiness)) {
                    bestNeighborTardiness = neighborTardiness;
                    bestNeighbor = neighbor;
                    bestMove = move;
                }
            }
        }
        if (bestNeighborTardiness < INT_MAX) {
            current = bestNeighbor;
            currentTardiness = bestNeighborTardiness;
            if (currentTardiness < bestTardiness) {
                best = current;
                bestTardiness = currentTardiness;
            }
            tabuList.push_back(bestMove);
            if (tabuList.size() > tabuTenure) tabuList.erase(tabuList.begin());
        }
        iteration++;
        if (iteration % 10 == 0) {
            cout << "Iteration " << iteration << " - Best Tardiness = " << bestTardiness << endl;
        }
    }
    cout << "Tabu Search finished with best tardiness = " << bestTardiness << endl;
    return {best, bestTardiness};
}

// Genetischer-Algorithmus + Tabu-Search
Solution solveSMTTP_SDST(const Problem& problem, int populationSize, int generations, int tabuIterations, int tabuTenure) {
    srand(time(0));
    vector<Solution> population(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        population[i].sequence = generateRandomSolution(problem.n);
        population[i].totalTardiness = calculateTardiness(problem, population[i].sequence);
    }
    cout << "Initial Population =" << endl;
    for (int i = 0; i < populationSize; ++i) {
        cout << "Solution " << i + 1 << " - Tardiness = " << population[i].totalTardiness << ", Sequence = ";
        for (int job : population[i].sequence) cout << job << " ";
        cout << endl;
    }
    for (int gen = 0; gen < generations; ++gen) {
        cout << "\nGeneration " << gen + 1 << endl;
        vector<Solution> newPopulation;
        for (int i = 0; i < populationSize; ++i) {
            int p1 = rand() % populationSize;
            int p2 = rand() % populationSize;
            newPopulation.push_back(population[p1].totalTardiness < population[p2].totalTardiness ? population[p1] : population[p2]);
        }
        for (int i = 0; i < populationSize; i += 2) {
            if (i + 1 < populationSize && rand() % 100 < 80) { // 80% Crossover-Wahrscheinlichkeit (80% crossover probability)
                vector<int> child1 = crossover(newPopulation[i].sequence, newPopulation[i + 1].sequence);
                vector<int> child2 = crossover(newPopulation[i + 1].sequence, newPopulation[i].sequence);
                if (rand() % 100 < 10) mutate(child1); // 10% Mutationswahrscheinlichkeit (10% mutation probability)
                if (rand() % 100 < 10) mutate(child2);
                newPopulation[i].sequence = child1;
                newPopulation[i + 1].sequence = child2;
                newPopulation[i].totalTardiness = calculateTardiness(problem, child1);
                newPopulation[i + 1].totalTardiness = calculateTardiness(problem, child2);
            }
        }
        sort(newPopulation.begin(), newPopulation.end(), 
             [](const Solution& a, const Solution& b) { return a.totalTardiness < b.totalTardiness; });
        for (int i = 0; i < min(5, populationSize); ++i) { 
            newPopulation[i] = tabuSearch(problem, newPopulation[i].sequence, tabuIterations, tabuTenure);
        }
        population = newPopulation;
        Solution bestInGeneration = population[0];
        for (const auto& sol : population) {
            if (sol.totalTardiness < bestInGeneration.totalTardiness) bestInGeneration = sol;
        }
        cout << "Best Solution in Generation " << gen + 1 << " - Tardiness = " << bestInGeneration.totalTardiness << ", Sequence = ";
        for (int job : bestInGeneration.sequence) cout << job << " ";
        cout << endl;
    }
    Solution best = population[0];
    for (const auto& sol : population) {
        if (sol.totalTardiness < best.totalTardiness) best = sol;
    }
    return best;
}

int main() {
    Problem problem;
    problem.n = 10; 
    problem.jobs = {
        {0, 2, 5, 1}, {1, 3, 6, 1}, {2, 4, 10, 2}, {3, 1, 8, 1},
        {4, 3, 7, 2}, {5, 2, 9, 3}, {6, 5, 6, 2}, {7, 4, 8, 3},
        {8, 1, 4, 1}, {9, 3, 5, 1}
    }; 
    problem.setupTimes = {
        {0, 1, 3, 2, 4, 3, 5, 4, 2, 3},
        {2, 0, 5, 1, 3, 4, 6, 2, 3, 5},
        {3, 4, 0, 6, 7, 8, 5, 3, 2, 6},
        {1, 3, 5, 0, 4, 6, 2, 4, 5, 7},
        {4, 5, 6, 3, 0, 4, 6, 7, 4, 5},
        {2, 1, 3, 5, 6, 0, 4, 5, 3, 6},
        {6, 5, 7, 4, 6, 2, 0, 3, 6, 7},
        {5, 4, 3, 6, 7, 3, 5, 0, 2, 4},
        {3, 2, 4, 5, 6, 4, 5, 6, 0, 4},
        {7, 6, 8, 4, 6, 5, 7, 6, 4, 0}
    };
    Solution result = solveSMTTP_SDST(problem, 50, 100, 20, 5); 
    cout << "\nBest Sequence = ";
    for (int job : result.sequence) cout << job << " ";
    cout << "\nTotal Tardiness = " << result.totalTardiness << endl;
    return 0;
}

