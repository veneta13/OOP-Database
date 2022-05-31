#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../source/integer_value.hpp"


TEST_CASE("Integer value tests")
{
    SECTION("Default constructor")
    {
        IntegerValue iv;
        REQUIRE(iv.get() == -1);
    }

    SECTION("Constructor with parameters")
    {
        IntegerValue iv(5);
        REQUIRE(iv.get() == 5);
    }

    SECTION("Copy constructor")
    {
        IntegerValue iv1(5);
        REQUIRE(iv1.get() == 5);
        IntegerValue iv2(iv1);
        REQUIRE(iv2.get() == 5);
    }

    SECTION("Operator =")
    {
        IntegerValue iv1(5);
        REQUIRE(iv1.get() == 5);
        IntegerValue iv2 = iv1;
        REQUIRE(iv2.get() == 5);
    }

    SECTION("Operator +")
    {
        IntegerValue iv1(6);
        REQUIRE((iv1 + 5) == 11);
        REQUIRE((iv1 + iv1) == 12);
    }

    SECTION("Operator *")
    {
        IntegerValue iv1(3);
        REQUIRE((iv1 * 5) == 15);
        REQUIRE((iv1 * iv1) == 9);
    }

    SECTION("Operator >")
    {
        IntegerValue iv1(3), iv2(5);
        REQUIRE(iv1 > 1);
        REQUIRE(!(iv1 > 4));
        REQUIRE(!(iv1 > 3));

        REQUIRE(iv2 > iv1);
        REQUIRE(!(iv1 > iv2));
        REQUIRE(!(iv2 > iv2));
    }

    SECTION("Operator <")
    {
        IntegerValue iv1(3), iv2(5);
        REQUIRE(iv1 < 5);
        REQUIRE(!(iv1 < 2));
        REQUIRE(!(iv1 < 3));

        REQUIRE(iv1 < iv2);
        REQUIRE(!(iv2 < iv1));
        REQUIRE(!(iv2 < iv2));
    }

    SECTION("Operator ==")
    {
        IntegerValue iv1(4), iv2(5);
        REQUIRE(iv1 == 4);
        REQUIRE(!(iv1 == 3));
        REQUIRE(!(iv1 == 5));

        REQUIRE(iv1 == iv1);
        REQUIRE(iv2 == iv2);
        REQUIRE(!(iv1 == iv2));
    }

    SECTION("Operator !=")
    {
        IntegerValue iv1(4), iv2(5);
        REQUIRE(iv1 != 5);
        REQUIRE(iv1 != 3);
        REQUIRE(!(iv1 != 4));

        REQUIRE(iv1 != iv2);
        REQUIRE(!(iv2 != iv2));
        REQUIRE(!(iv1 != iv1));
    }

    SECTION("Getter and setter")
    {
        IntegerValue iv(10);
        REQUIRE(iv.get() == 10);
        iv.set(6);
        REQUIRE(iv.get() == 6);
    }
}
