#include <iostream>
#include <vector>
#include <cstdlib> // For random invader generation
#include <ctime>   // For timing invaders' movement
#include <chrono>  // For tracking game duration

using namespace std;
using namespace chrono; // Time utilities

#define WIDTH 20 // Game screen width
#define HEIGHT 10 // Game screen height

struct Invader {
    int x, y;
    bool alive;
};

struct Player {
    int x;
};

vector<Invader> invaders;
Player player;
int score = 0;
bool gameOver = false;

// Function to initialize game elements
void initializeGame() {
    player.x = WIDTH / 2; // Center player
    srand(time(0)); // Seed random generator
}

// Function to spawn new invaders
void spawnInvaders() {
    if (rand() % 5 == 0) { // Random spawn chance
        Invader newInvader = {rand() % WIDTH, 0, true};
        invaders.push_back(newInvader);
    }
}

// Function to update invader positions
void moveInvaders() {
    for (auto &invader : invaders) {
        if (invader.alive) {
            invader.y++; // Move down

            // Check if invader reached the player
            if (invader.y >= HEIGHT) {
                gameOver = true;
            }
        }
    }
}

// Function to automatically fire at invaders
void fireLaser() {
    for (auto &invader : invaders) {
        if (invader.alive && invader.y >= HEIGHT - 2) { // Target lower invaders
            invader.alive = false; // Destroyed!
            score++;
        }
    }
}

// Function to display game screen
void displayGame() {
    system("clear"); // Clear screen (use "CLS" for Windows)
    cout << "Score: " << score << "\n";

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            bool isInvader = false;
            for (auto &invader : invaders) {
                if (invader.alive && invader.x == j && invader.y == i) {
                    cout << "@"; // Invader symbol
                    isInvader = true;
                }
            }

            if (!isInvader) {
                if (i == HEIGHT - 1 && j == player.x) {
                    cout << "^"; // Player symbol
                } else {
                    cout << ".";
                }
            }
        }
        cout << endl;
    }
}

// Function to run the game loop
void runGame() {
    auto startTime = high_resolution_clock::now(); // Start time tracking

    while (!gameOver) {
        spawnInvaders();
        moveInvaders();
        fireLaser();
        displayGame();

        this_thread::sleep_for(milliseconds(500)); // Slow down game loop
    }

    auto endTime = high_resolution_clock::now();
    duration<double> elapsed = endTime - startTime;

    cout << "\nGame Over! You survived for " << elapsed.count() << " seconds.\n";
    cout << "Final Score: " << score << " invaders crushed.\n";
}

// Main function
int main() {
    initializeGame();
    runGame();
    return 0;
}
