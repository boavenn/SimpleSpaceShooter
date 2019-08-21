#pragma once
#include <string>
#include <unordered_map>

template <typename Res>
class ResourceHolder
{
public:
	ResourceHolder(const std::string& dir, const std::string& ext) : directory{ "res/" + dir + "/" }, extension{ "." + ext } {}
	const Res& get(const std::string& name) { return resources.at(name); }
	void add(const std::string& name)
	{
		Res r;
		r.loadFromFile(getPath(name));
		resources.insert(std::make_pair(name, r));
	}

private:
	const std::string getPath(const std::string& name) { return directory + name + extension; }

	const std::string directory;
	const std::string extension;
	std::unordered_map<std::string, Res> resources;
};

