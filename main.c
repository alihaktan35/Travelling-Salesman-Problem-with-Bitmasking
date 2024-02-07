// github.com/alihaktan35
// Solving TSP with dynamic programming: O(n^2 * 2^n)

// Bitmasking: Technique that uses the binary representation of integers to represent the state of visited cities.
// It uses an integer to represent the set of visited cities. (0: unvisited, 1: visited)

#include <stdio.h>

#define NUM_CITIES 13 // Number of cities
#define INF 999999 // Definition of INFINITY (Defined to represent a very large value)

// Distances between cities (Adjacency Matrix)
int distances[NUM_CITIES][NUM_CITIES] = {
        {0, 453, 561, 243, 716, 660, 939, 771, 734, 893, 1363, 1124, 1067},
        {453, 0, 579, 382, 544, 258, 490, 318, 414, 440, 910, 671, 747},
        {561, 579, 0, 322, 444, 550, 900, 848, 993, 1019, 1418, 1105, 1326},
        {243, 382, 322, 0, 537, 487, 837, 689, 745, 822, 1281, 1042, 1078},
        {716, 544, 444, 537, 0, 322, 558, 618, 954, 813, 1076, 763, 1236},
        {660, 258, 550, 487, 322, 0, 356, 304, 640, 499, 874, 561, 922},
        {939, 490, 900, 837, 558, 356, 0, 333, 729, 429, 518, 205, 852},
        {771, 318, 848, 689, 618, 304, 333, 0, 449, 195, 592, 353, 618},
        {734, 414, 993, 745, 954, 640, 729, 449, 0, 338, 818, 725, 333},
        {893, 440, 1019, 822, 813, 499, 429, 195, 338, 0, 480, 425, 423},
        {1363, 910, 1418, 1281, 1076, 874, 518, 592, 818, 480, 0, 313, 627},
        {1124, 671, 1105, 1042, 763, 561, 205, 353, 725, 425, 313, 0, 841},
        {1067, 747, 1326, 1078, 1236, 922, 852, 618, 333, 423, 627, 841, 0}
};

int tsp(int visitedCities, int currentCity, int dp[NUM_CITIES][1 << NUM_CITIES], int path[NUM_CITIES][1 << NUM_CITIES]) {
    // If all cities have been visited, return the distance to the starting city
    if (visitedCities == (1 << NUM_CITIES) - 1) {
        return distances[currentCity][0];
    }

    // If this subproblem has already been solved, return the result from the DP table
    if (dp[currentCity][visitedCities] != -1) {
        return dp[currentCity][visitedCities];
    }

    int ans = INF; // Variable used to store the current best (minimum) distance found
    int nextCity = -1;

    // Try visiting all cities
    for (int city = 0; city < NUM_CITIES; city++) {
        // Check if the city has not been visited
        if ((visitedCities & (1 << city)) == 0) {
            int newAns = distances[currentCity][city] + tsp(visitedCities | (1 << city), city, dp, path);
            if (newAns < ans) {
                ans = newAns;
                nextCity = city;
            }
        }
    }

    // Store the next city in the path
    path[currentCity][visitedCities] = nextCity;

    // Store the result in the DP table
    dp[currentCity][visitedCities] = ans;
    return ans;
}

// Function to print the optimal path (Cities as integers 0-12)
void printOptimalPath(int path[NUM_CITIES][1 << NUM_CITIES]) {
    int currentCity = 0; // Start from city 0 (Istanbul)
    int visitedCities = 1; // Starting mask with city 0 visited
    printf("Optimal Path: 0 "); // Starting from city 0

    while (1) {
        int nextCity = path[currentCity][visitedCities];
        if (nextCity == -1) break;
        printf("-> %d ", nextCity);
        currentCity = nextCity;
        visitedCities |= (1 << nextCity);
    }

    printf("-> 0\n"); // Returning back to city 0
}

// Function to initialize the DP table and solve the TSP
void findOptimalPath() {
    int dp[NUM_CITIES][1 << NUM_CITIES];
    int path[NUM_CITIES][1 << NUM_CITIES];

    // Initialize DP table with -1 (unvisited) and path with -1 (no next city)
    for (int i = 0; i < NUM_CITIES; i++) {
        for (int j = 0; j < (1 << NUM_CITIES); j++) {
            dp[i][j] = -1;
            path[i][j] = -1;
        }
    }

    // Start the TSP from city 0 (Istanbul)
    int optimalDistance = tsp(1, 0, dp, path); // Start with visitedCities = 1 (city 0 is visited)

    printf("Optimal Distance: %d km\n", optimalDistance);
    printOptimalPath(path);
}

int main() {
    findOptimalPath();
    return 0;
}