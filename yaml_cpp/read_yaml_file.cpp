#include <yaml-cpp/yaml.h>

#include <iostream>
struct container
{
    std::string name;
    int         age;
};

namespace YAML
{
template <>
struct convert<container>
{
    static Node encode(const container& rhs)
    {
        Node node;
        node.push_back(rhs.name);
        node.push_back(rhs.age);
        return node;
    }

    static bool decode(const Node& node, container& rhs)
    {
        rhs.name = node["name"].as<std::string>();
        rhs.age  = node["age"].as<int>();
        return true;
    }
};
}  // namespace YAML

int main()
{
    YAML::Node node = YAML::LoadFile("../test.yaml");
    // std::cout << node << std::endl;
    std::cout << "api : " << node["api"].as<std::string>() << std::endl;
    if (node["containers"])
    {
        std::vector<container> vi = node["containers"].as<std::vector<container>>();

        for (std::vector<container>::iterator it = vi.begin(); it != vi.end(); ++it)
        {
            std::cout << "vector: name: " << it->name << " age: " << it->age << std::endl;
        }
    }
    std::cout << "label[app] : " << node["label"]["app"].as<std::string>() << std::endl;
    std::cout << "containers[0][name] : " << node["containers"][0]["name"].as<std::string>() << std::endl;
    return 0;
}
