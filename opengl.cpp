#include "opengl.h"

#include <fstream>

std::string dn::ReadFile(const std::string &fileName)
{
	std::ifstream fileStream;
	std::string fileContent;
	fileStream.open(fileName);
	if (fileStream)
	{
		char c;
		while ((c = fileStream.get()) != EOF)
			fileContent += c;
	}
	else
		fileContent = "NO FILE";
	fileStream.close();
	return fileContent;
}

float dn::Random(const float & p_min, const float & p_max)
{
	static std::default_random_engine eng;
	static std::uniform_real_distribution<float> dist(p_min, p_max);

	return dist(eng);
}