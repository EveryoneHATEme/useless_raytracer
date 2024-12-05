#include "Utils.h"

namespace Utils
{
    static unsigned int seed = 42u;
        
	Color vec3ToColor(const glm::vec3& source)
	{
		glm::vec3 normalized = glm::clamp(glm::sqrt(source), 0.f, 1.f) * 255.f;

		return { (unsigned char)normalized.r, (unsigned char)normalized.g, (unsigned char)normalized.b, (unsigned char)255 };
	}

    unsigned int wang_hash(unsigned int seed)
    {
        seed = (seed ^ 61) ^ (seed >> 16);
        seed *= 9;
        seed = seed ^ (seed >> 4);
        seed *= 0x27d4eb2d;
        seed = seed ^ (seed >> 15);
        return seed;
    }

    float RandomFloat()
    {
        seed = wang_hash(seed);
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
