#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>

#define DEBUG false

struct Point
{
	int x, y;
};

struct Vector
{
    int x, y, z;

    Vector operator*(Vector const& other) const;
};

Vector Vector::operator*(Vector const& other) const
{
    const auto cx = y * other.z - z * other.y;
    const auto cy = z * other.x - x * other.z;
    const auto cz = x * other.y - y * other.x;
    return Vector{cx, cy, cz};
}

std::ostream& operator<<(std::ostream& out, Vector const& vector)
{
    out << vector.x << ' ' << vector.y << ' ' << vector.z;
    return out;
}

std::istream& operator>>(std::istream& in, Point & point)
{
	in >> point.x >> point.y;
	return in;
}

int main()
{
    try
    {
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		auto count = 0;
		input >> count;

		std::vector<Point> points;

		while (count-- > 0)
		{
			points.push_back(Point{});
			input >> points.back();
		}

		std::vector<Vector> vectors;

        for (auto i = 0; i < points.size() - 1; ++i)
        {
			auto x = points[i + 1].x - points[i].x;
			auto y = points[i + 1].y - points[i].y;
			vectors.push_back({ x, y, 0 });
        }

		auto turns = 0;

		for (std::size_t i = 0; i < vectors.size() - 1; ++i)
		{
			const auto result = vectors[i] * vectors[i + 1];
			if (DEBUG)
			{
				std::cout << result << std::endl;
			}
			if (result.z > 0)
			{
				turns++;
			}
		}

        if (DEBUG)
        {
			std::cout << turns << std::endl;
        }
		output << turns << std::endl;
    } catch (std::exception &ex)
    {
		std::cerr << ex.what() << std::endl;
    }
}
