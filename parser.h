#pragma once
#include <vector>
#include <string>

struct Node {
	std::string tag;
	std::vector<std::pair<std::string, std::string>> attributes;
	std::string data;
	std::vector<Node> vector;
};

class parser
{
public:
	parser();
	void parse(std::string);
	~parser();
private:
	std::vector<Node> tree;
};

