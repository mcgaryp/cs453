#include "include/catch.hpp"

#include "query_generator.hpp"

using namespace cs453;
using namespace std;

bool inline testGenerateQuery(const char *username, const char *password, const char *expected) {
    string user = string(username);
    string pass = string(password);
    string query = generateQuery(user, pass);
    string expect = string(expected);
    if (query != expect) {
        printf("FAILED: %s != %s", query.c_str(), expected);
    }
    return query == expect;
}

TEST_CASE( "Comment attack test cases", "[comment]" )
{
    REQUIRE( testGenerateQuery("Root'; -- ", "nothing' OR 'x' = 'x", "SELECT COUNT(*) FROM users WHERE username = 'Root'; -- ' AND password = 'nothing' OR 'x' = 'x';") );

    REQUIRE( testGenerateQuery("sam", "x'; UPDATE dataStore SET category = 'You have been hacked!", "SELECT COUNT(*) FROM users WHERE username = 'sam' AND password = 'x'; UPDATE dataStore SET category = 'You have been hacked!'") );
}
