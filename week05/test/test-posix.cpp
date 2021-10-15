#include "include/catch.hpp"
#include "../src/canonical_path_posix.hpp"
#include "../src/canonical_path_posix_ci.hpp"

/* A POSIX compliant filesystem must:
 *   - Allow hierarchical paths (files are members of parent folders)
 *   - Allow hierarchical navigation via '.', '..', '...'
 *   - Support UNIX permissions
 * ... and more that is less relevant here. In this test suite, we are
 * primarily concerned with hierarchical navigation using the standard
 * POSIX path separator ('/') and short-hand for current working dir
 * ('.') and parent dir ('..').
 *
 * We include both case-sensitive and case-insensitive versions as there
 * are POSIX compliant filesystems available in both categories.
 */

using namespace cs453;
using namespace std;

bool compare(string path1, string path2) {
    CanonicalPathPOSIX c1(path1);
    CanonicalPathPOSIX c2(path2);
    return c1.compare(c2);
}

TEST_CASE("Hierarchical navigation is resolved correctly", "[POSIX]")
{
    SECTION("NON-Homographs") {
        REQUIRE_FALSE(compare("/some/path/to/file1", "/some/path/to/file2"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "/some/path/to/file2/../file2"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "/some/path/to/file1/../file2"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "/some/path/to/./file2"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "/some/path/to/../to/file2"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "/../../../path/to/file2/../file2"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "/some/../some/path/to/file2/../file2"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "file1"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "to/file1"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "path/to/file1"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "some/path/to/file1"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "./some/path/to/file1"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "/some/path/to/../file1"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "/some/path/to/file1/file1"));
        REQUIRE_FALSE(compare("/some/path/to/file1", "/some/path/to/file1/../../.."));
    }

    SECTION("Homographs") {
        REQUIRE(compare("/some/path/to/file1", "/some/path/to/file1"));
        REQUIRE(compare("/some/path/to/file1", "/some/path/to/file1/../file1"));
        REQUIRE(compare("/some/path/to/file1", "/some/path/to/file2/../file1"));
        REQUIRE(compare("/some/path/to/file1", "/some/path/to/./file1"));
        REQUIRE(compare("/some/path/to/file1", "/some/path/to/../to/file1"));
        REQUIRE(compare("some/path/to/file1", "../../../some/path/to/file1"));
        REQUIRE(compare("/some/path/to/file1", "/../../../some/path/to/file1"));
        REQUIRE(compare("/some/path/to/file1", "/../../../some/path/to/file1/../file1"));
        REQUIRE(compare("/some/path/to/file1", "/some/../some/path/to/file2/../file1"));
        REQUIRE(compare("/some/path/to/file1", "//////some//////path/////to/////////file1"));
        REQUIRE(compare("/", "/some/path/to/file1/../../../../../../../.."));
        REQUIRE(compare("/", "/some/path/to/file1/../../../.."));
        REQUIRE(compare("/", "/////////////////"));
        REQUIRE(compare("", "."));
        REQUIRE(compare("", ".."));
        REQUIRE(compare("", "../../.."));
    }
}