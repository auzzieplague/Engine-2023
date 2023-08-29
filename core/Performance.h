#pragma once

#include <iostream>
#include <map>
#include <chrono>
#include <string>

class PerformanceMeasurer {
private:
    std::map<std::string, std::chrono::high_resolution_clock::time_point> startTimes;
    std::map<std::string, std::chrono::high_resolution_clock::time_point> stopTimes;
    std::vector<std::pair<std::string, double>> lastDurations;
    std::chrono::high_resolution_clock::time_point lastUpdateTime;

    PerformanceMeasurer() {}
public:

    // Static method to return an instance of the class
    static PerformanceMeasurer& getInstance() {
        static PerformanceMeasurer instance;
        return instance;
    }

    // Delete the methods we don't want to allow for singleton
    PerformanceMeasurer(PerformanceMeasurer const&) = delete;             // Copy constructor
    void operator=(PerformanceMeasurer const&) = delete;                  // Assignment operator

    // Getter to retrieve all start timers
    std::map<std::string, std::chrono::high_resolution_clock::time_point> getStartTimers() {
        return startTimes;
    }

    // Starts the timer for a given title
    void start(const std::string& title) {
        startTimes[title] = std::chrono::high_resolution_clock::now();
    }

    // Stops the timer for a given title
    void stop(const std::string& title) {
        stopTimes[title] = std::chrono::high_resolution_clock::now();
    }

    // Gets the duration for a given title in milliseconds
    double getDuration(const std::string& title) {
        if (startTimes.find(title) == startTimes.end() || stopTimes.find(title) == stopTimes.end()) {
            return -1.0;
        }

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stopTimes[title] - startTimes[title]).count();
        return static_cast<double>(duration) / 1000000.0; // Convert to milliseconds, but keep the fractions
    }

    std::vector<std::pair<std::string, double>> getDurations() {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count();

        if (timeSinceLastUpdate >= 1) {
            lastDurations.clear();
            for (const auto& pair : startTimes) {
                const std::string& title = pair.first;
                double duration = getDuration(title);
                if (duration >= 0) {
                    lastDurations.push_back({title, duration});
                }
            }

            // Sort the durations from highest to lowest
            std::sort(lastDurations.begin(), lastDurations.end(),
                      [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
                          return b.second < a.second;
                      });

            lastUpdateTime = currentTime;
        }

        return lastDurations;
    }

    // Displays the duration for all titles
    void displayAll() {
        for (const auto& pair : startTimes) {
            const std::string& title = pair.first;
            double duration = getDuration(title);

            if (duration >= 0) {
                std::cout << "Title: " << title << ", Duration: " << duration << " ms" << std::endl;
            }
        }
    }
};

