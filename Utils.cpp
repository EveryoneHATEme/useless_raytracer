#include "Utils.h"

namespace Utils
{
    static unsigned int seed = 42u;

    Color vec3ToColor(const glm::vec3& source)
    {
	    glm::vec3 normalized = glm::clamp(glm::pow(source, glm::vec3(1.f / 2.2f)), 0.f, 1.f) * 255.f;

	    return { (unsigned char)normalized.r, (unsigned char)normalized.g, (unsigned char)normalized.b, (unsigned char)255 };
    }

    uint32_t wang_hash(uint32_t seed)
    {
        seed = (seed ^ 61) ^ (seed >> 16);
        seed *= 9;
        seed = seed ^ (seed >> 4);
        seed *= 0x27d4eb2d;
        seed = seed ^ (seed >> 15);
        return seed;
    }

    void CopyArrayToImage(const glm::vec3* source, Image& destination, float average)
    {
        for (size_t y = 0; y < destination.height; ++y) {
            for (size_t x = 0; x < destination.width; ++x) {
                ImageDrawPixel(&destination, x, y, vec3ToColor(source[x + y * destination.width] / average));
            }
        }
    }

    unsigned int pcg_hash(uint32_t seed)
    {
        uint32_t state = seed * 747796405u + 2891336453u;
        uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
        return (word >> 22u) ^ word;
    }

    float RandomFloat()
    {
        seed = pcg_hash(seed);
        return (float)seed / (float)std::numeric_limits<unsigned int>::max();
    }

    glm::vec3 RandomOnUnitSphere()
    {
        return glm::normalize(glm::vec3(
            RandomFloat() * 2.f - 1.f,
            RandomFloat() * 2.f - 1.f,
            RandomFloat() * 2.f - 1.f
        ));
    }
}
