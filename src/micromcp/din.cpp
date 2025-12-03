
 #include <iostream>
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>  // Assuming nlohmann/json library is used for JSON parsing.
// If not available, you can replace with simple string parsing.

using json = nlohmann::json;

// Forward declaration for tool functions
void add_numbers(int a, int b);
void get_weather(const std::string& city);

// A simple Tool struct to represent a callable tool
struct Tool {
    std::string name;
    std::string description;
    std::vector<std::string> parameters;  // Parameter names expected
    void (*function)(const json& args);   // Pointer to the function, taking JSON args
};

// Global registry of tools
std::map<std::string, Tool> tool_registry;

// Function to register a tool
void register_tool(const std::string& name, const std::string& desc, 
                   const std::vector<std::string>& params, 
                   void (*func)(const json& args)) {
    tool_registry[name] = {name, desc, params, func};
}

// Example tool: Add two numbers
void tool_add(const json& args) {
    int a = args["a"];
    int b = args["b"];
    std::cout << "Tool 'add' result: " << (a + b) << std::endl;
}

// Example tool: Get weather (simulated)
void tool_weather(const json& args) {
    std::string city = args["city"];
    std::cout << "Tool 'weather' result: Sunny in " << city << std::endl;
}

// LLM Agent class
class LLMAgent {
private:
    std::string llm_output;  // Simulated LLM output containing tool call in JSON

public:
    std::string generate_response(const std::string& user_query)

