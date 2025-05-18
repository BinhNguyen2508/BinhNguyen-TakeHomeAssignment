#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>
#include <set>
#include <cmath>
#include <fstream>
#include <format>
#include <type_traits>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The coding will be adhered to Google's C++ Style as much as possible.
// https://google.github.io/styleguide/cppguide.html
//
// CONTEXT: We want to solve the comparision problem to determine if point A (x1,y1) is the same as point B (x2,y2)
//          before writing to file.
//
// APPROACH: Use container to maintain memory of seen unique points. Leverage the container to check for duplicated point.
//           Use epsilon to compare equality between point coordinate.
//
// SOLUTION: The approach is insertion/search-heavy (for storing/checking unique points).
//          --> We use std::set as the container (in MSVC, it's implemented as ordered red-black tree, O(log(n)) for insert/search operations).
//
// IMPLEMENT: We iterate through the input array first. For each iteration, perform insertion into std::set container. If insertion succeeds (meanings no duplication)
//          , then the point is unique and will be printed out.
//          However, std::set need comparator for WaterPressurePoints struct.
//          --> We define custom "<" operator for WaterPressurePoints.
//
// ANALYSIS: The implementation will perform a n loop iterating through input array. Within each iteration, one insertion are performed.
//          The worst-case complexity for this will be O(n* log(n)) = O(nlog(n))
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline constexpr double kEpsilon = 1e-19;

struct WaterPressurePoints {
    double x;               // X-coordinate of the point
    double y;               // Y-coordinate of the point
    double water_pressure;  // Water pressure at the point

    bool operator<(const WaterPressurePoints& other) const
    {
        if (std::fabs(x - other.x) > kEpsilon)
            return x < other.x;
        else if (std::fabs(y - other.y) > kEpsilon)
            return y < other.y;
        else
            return false;
    }
};

// Overloading ofstream << WaterPressurePoints for cleaner stream formatting.
std::ofstream& operator<<(std::ofstream& ofs, const WaterPressurePoints& point)
{
    static int max_precision = 16;

    ofs << std::left << std::setw(3) << std::format("{:.{}g}", point.x, max_precision) << " ";
    ofs << std::left << std::setw(3) << std::format("{:.{}g}", point.y, max_precision) << " ";

    double rounded_water_pressure = std::round(point.water_pressure * 1000.0) / 1000.0;

    ofs << rounded_water_pressure << "\n"; // Do not use std::endl, it will flush the stream -> I/O overhead
    return ofs;
}

void WriteWaterPressure(const std::vector<WaterPressurePoints>& points)
{
    std::set<WaterPressurePoints> unique_points;
    std::ofstream out_file(".\\WaterPressurePoints.txt", std::ios::out | std::ios::trunc); // Clear file when opening.

    if (out_file) {
        for (const WaterPressurePoints& point : points) {
            auto point_insert_result = unique_points.insert(point);

            if (point_insert_result.second == true)
                out_file << point;
        }

        out_file.flush();
    }
}

int main()
{

    try {
        std::vector<WaterPressurePoints> points {
            {1.005, 2.00000005, 10},
            {1.005, 2.000000049999999, 15},
            {100000000000, 20000000.005, 10},
            {10000000000000000000.05, 20000000.005, 15},
            {10000000000000000000.0500000000001, 20000000.00500000000001, 15},
            {100000000.05, 1000000.005, 15},
            {0.5, 0.99, 0.1111111},
            {0.5, 0.99, 0.1111111},
            {1e-19, 2e-19, 0.1111111},
            {0.5e-19, 3e-19, 0.1111111},
            {8.6e-20, 1e-16, 8e-16}
        };

        WriteWaterPressure(points);
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
