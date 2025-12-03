from langchain_core.tools import tool
from pydantic import BaseModel, Field
from typing import Optional
import duckduckgo_search  # For web search

# Calculator Tool
@tool
def calculator(expression: str) -> str:
    """Evaluates a mathematical expression (e.g., '2 + 2 * 3')."""
    try:
        # Use safe eval or sympy for production
        result = eval(expression)
        return f"Result: {result}"
    except Exception as e:
        return f"Error: {str(e)}"

# Web Search Tool (using DuckDuckGo for free searches)
class SearchInput(BaseModel):
    query: str = Field(..., description="The search query string")

@tool(args_schema=SearchInput)
def web_search(query: str) -> str:
    """Performs a web search and returns top results summary."""
    try:
        results = duckduckgo_search.DDGSearchResults().text(query, max_results=3)
        summary = "\n".join([f"- {r['title']}: {r['body']}" for r in results['results'][:3]])
        return f"Search results for '{query}':\n{summary}"
    except Exception as e:
        return f"Search error: {str(e)}"

tools = [calculator, web_search]
