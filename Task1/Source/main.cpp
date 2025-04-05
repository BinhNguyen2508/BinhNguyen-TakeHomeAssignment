#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>
#include <unordered_set>
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
// ANALYSIS: The approach is insertion-heavy (for storing unique points) and search-heavy (for checking duplicated points)
//          --> We use std::unordered_map as the container (hashmap, average O(1) complexity for search, insert, delete operations).
//              Assuming that hashing overhead is trivial.
//
// PROBLEM: We need good hash functions to minimize collision and proper == operator overloading to compare coordinates.
//          However, it's tricky to find hash functions that satisfy "almost equal" for double values, meaning we have to find functions that
//          somehow can hash a double value to at most 2 buckets of near equal values -> Not feasible (Proper hashing means 1 value - 1 bucket).
//
// SOLUTION: We can settle with a hash function that hashes values within epsilon range into a same bucket,
//          Example: epsilon = 0.01, then 15.051 and 15.055 will be hashed into the same bucket that is hashed from 15.05.
//          This leaves an edge-case where 15.046 comparing to 15.051 is within epsilon but hashed into different bucket hashed from 15.04.
//
//          To solve this, we employ 2-pass approach:
//          1st pass, using std::unordered_map to handle case that hash into the same bucket ~ guaranteed duplicate.
//          2nd pass, using linear search (naive approach) to handle edge-case that hash into different bucket ~ potential duplicate or unique.
//
// CONCLUSION: This approach will be very efficient only when duplicates are majority and degrade to the same performance
//              as naive approach when uniques are majority.
//              (naive approach: create an array containing seen points. For each next iterated points in vector,
//              loop through the array to check for duplicate/seen point.)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Epsilon to help with comparing double.
// Value is currently based on example of Task 1.
// Minimum is machine epsilon, std::numeric_limits<double>::epsilon.
inline constexpr double kEpsilon {1e-19};

struct WaterPressurePoints {
    double x;               // X-coordinate of the point
    double y;               // Y-coordinate of the point
    double water_pressure;  // Water pressure at the point

    bool operator==(const WaterPressurePoints& other_point) const
    {
        bool ret =  std::fabs(x - other_point.x) <= kEpsilon && std::fabs(y - other_point.y) <= kEpsilon;
        return ret;
    }
};

namespace Helper {
std::size_t Hash(const WaterPressurePoints& point)
{
    double rounded_x = std::round(static_cast<long double>(point.x) / static_cast<long double>(kEpsilon)) * static_cast<long double>(kEpsilon);
    double rounded_y = std::round(static_cast<long double>(point.y) / static_cast<long double>(kEpsilon)) * static_cast<long double>(kEpsilon);
    std::size_t hash_x = std::hash<double>()(rounded_x);
    std::size_t hash_y = std::hash<double>()(rounded_y);

    // Hash algorithm is inspired by Boost C++'s hash_combine
    // https://www.boost.org/doc/libs/1_55_0/doc/html/hash/reference.html#boost.hash_combine
    std::size_t seed = 0;

    seed ^= hash_x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash_y + 0x9e3779b9 + (seed << 6) + (seed >> 2);

    return seed;
}
}

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
    std::unordered_set<std::size_t> rough_seen_points;
    std::vector<WaterPressurePoints> seen_points;

    // Assuming the size is not too large to cause std::bad_alloc.
    rough_seen_points.reserve(points.size()); // Pre-allocate to avoid performance degradation from resizing.
    seen_points.reserve(points.size()); // Pre-allocate to avoid performance degradation from resizing.

    std::ofstream out_file(".\\WaterPressurePoints.txt", std::ios::out | std::ios::trunc); // Clear file when opening.

    if (out_file) {
        for (const WaterPressurePoints& point : points) {
            std::size_t h = Helper::Hash(point);

            if (rough_seen_points.find(h) != rough_seen_points.end()) { // 1st pass
                // skipping due to guaranteed duplicate
            } else { // 2nd pass
                bool is_seen = false;

                for (const WaterPressurePoints& seen_point : seen_points){
                    if (point == seen_point) {
                        is_seen = true;
                        break;
                    }
                }

                if (!is_seen) {
                    out_file << point;
                    rough_seen_points.insert(h);
                    seen_points.push_back(point);
                }
            }
        }

        out_file.flush();
    }
}

int main()
{
    static_assert(std::is_trivially_copy_constructible<WaterPressurePoints>::value == true);
    static_assert(std::is_trivially_copyable<WaterPressurePoints>::value == true);

    try {
#ifdef TEST

#else
        std::vector<WaterPressurePoints> points {
            {0, 0, 0},
            {1e-19, 0, 15.1},
            {1.5e-19, 0, 10.44444},
            {2e-19, 0.5e-19, 25.1234},
            {2.5e-19, 0, 25.123},
            {-0.5e-19, 0, 17.00},
            {-1e-19, 1.1e-19, 2.999999}
        };

        WriteWaterPressure(points);
#endif

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
