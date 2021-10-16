#include "canonical_path_posix.hpp"
#include <vector>
#include <iostream>

using namespace cs453;
using namespace std;

// POSIX-specific canonical form of a path (case-sensitive)
std::string CanonicalPathPOSIX::canonicalForm()
{
    vector<string> vctr('/');
    string part = "";

    for (int i = 0; i < path.length(); i++) {
        part += path[i];
        if (part == "../" || (part == ".." && i == path.length() - 1))
        {
            if (vctr.back() != "/")
                vctr.pop_back();
            part = "";
        } 
        else if (part == "./")
        {
            part = "";
        } 
        else if (path[i] == '/')
        {
            if (path[i-1] == '/')
            {
                part.erase(part.length() - 1);
            } else {
                vctr.push_back(part);
                part = "";
            }
        }
    }
    if (part != ".")
        vctr.push_back(part);
  
    string newPath = "";
    for (vector<string>::iterator it = vctr.begin(); it < vctr.end(); it++) 
    {
        newPath += *it;
    }

    return newPath;
}
