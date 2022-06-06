#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../source/integer_value.hpp"
#include "../source/float_value.hpp"
#include "../source/string_value.hpp"
#include "../source/null_value.hpp"

#include <typeinfo>


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

TEST_CASE("Floating point value tests")
{
    SECTION("Default constructor")
    {
        FloatValue fv;
        REQUIRE(std::fabs(fv.get() - (-1)) < EPSILON);
    }

    SECTION("Constructor with parameters")
    {
        FloatValue fv(5.2);
        REQUIRE(std::fabs(fv.get() - 5.2) < EPSILON);
    }

    SECTION("Copy constructor")
    {
        FloatValue fv1(5.2);
        REQUIRE(std::fabs(fv1.get() - 5.2) < EPSILON);
        FloatValue fv2(fv1);
        REQUIRE(std::fabs(fv2.get() - 5.2) < EPSILON);
    }

    SECTION("Operator =")
    {
        FloatValue fv1(5.2);
        REQUIRE(std::fabs(fv1.get() - 5.2) < EPSILON);
        FloatValue fv2 = fv1;
        REQUIRE(std::fabs(fv2.get() - 5.2) < EPSILON);
    }

    SECTION("Operator +")
    {
        FloatValue fv1(6.8);
        REQUIRE(std::fabs((fv1 + 3) - 9.8) < EPSILON);
        REQUIRE(std::fabs((fv1 + fv1) - 13.6) < EPSILON);
    }

    SECTION("Operator *")
    {
        FloatValue fv1(3.1);
        REQUIRE(std::fabs((fv1 * 3) - 9.3) < EPSILON);
        REQUIRE(std::fabs((fv1 * fv1) - 9.61) < EPSILON);
    }

    SECTION("Operator >")
    {
        FloatValue fv1(2.9555), fv2(3.5);
        REQUIRE(fv1 > 1);
        REQUIRE(!(fv1 > 4));
        REQUIRE(!(fv1 > 3));

        REQUIRE(fv2 > fv1);
        REQUIRE(!(fv1 > fv2));
        REQUIRE(!(fv2 > fv2));
    }

    SECTION("Operator <")
    {
        FloatValue fv1(3.001), fv2(5.5);
        REQUIRE(fv1 < 5);
        REQUIRE(!(fv1 < 2));
        REQUIRE(!(fv1 < 3));

        REQUIRE(fv1 < fv2);
        REQUIRE(!(fv2 < fv1));
        REQUIRE(!(fv2 < fv2));
    }

    SECTION("Operator ==")
    {
        FloatValue fv1(4.55), fv2(5.85);
        REQUIRE(fv1 == 4.55);
        REQUIRE(!(fv1 == 3));
        REQUIRE(!(fv1 == 5));

        REQUIRE(fv1 == fv1);
        REQUIRE(fv2 == fv2);
        REQUIRE(!(fv1 == fv2));
    }

    SECTION("Operator !=")
    {
        FloatValue fv1(4.6002), fv2(5.1003);
        REQUIRE(fv1 != 5);
        REQUIRE(fv1 != 3);
        REQUIRE(!(fv1 != 4.6002));

        REQUIRE(fv1 != fv2);
        REQUIRE(!(fv2 != fv2));
        REQUIRE(!(fv1 != fv1));
    }

    SECTION("Getter and setter")
    {
        FloatValue fv(10.821);
        REQUIRE(std::fabs(fv.get() - 10.821) < EPSILON);
        fv.set(30.214);
        REQUIRE(std::fabs(fv.get() - 30.214) < EPSILON);
    }
}

TEST_CASE("String value tests")
{
    SECTION("Default constructor")
    {
        StringValue sv;
        REQUIRE(!sv.get());
    }

    SECTION("Constructor with parameters")
    {
        StringValue sv("dummy value");
        REQUIRE(strcmp(sv.get(), "dummy value") == 0);
    }

    SECTION("Copy constructor")
    {
        StringValue sv("dummy value");
        StringValue sv1(sv);
        REQUIRE(strcmp(sv.get(), "dummy value") == 0);
        REQUIRE(strcmp(sv.get(), sv1.get()) == 0);
    }

    SECTION("Operator =")
    {
        StringValue sv("dummy value");
        StringValue sv1 = sv;
        REQUIRE(strcmp(sv.get(), "dummy value") == 0);
        REQUIRE(strcmp(sv.get(), sv1.get()) == 0);
    }

    SECTION("Operator ==")
    {
        StringValue sv("dummy value"), sv1("dummy value 2");
        StringValue sv2(sv);
        REQUIRE(!(sv == sv1));
        REQUIRE(sv == sv);
        REQUIRE(sv == sv2);
        REQUIRE(sv == "dummy value");
        REQUIRE(!(sv == "dummy value 2"));
        REQUIRE(sv1 == "dummy value 2");
        REQUIRE(!(sv1 == "dummy value"));
    }

    SECTION("Operator !=")
    {
        StringValue sv("dummy value"), sv1("dummy value 2");
        StringValue sv2(sv);
        REQUIRE(sv != sv1);
        REQUIRE(!(sv != sv));
        REQUIRE(!(sv != sv2));
        REQUIRE(!(sv != "dummy value"));
        REQUIRE(sv != "dummy value 2");
        REQUIRE(!(sv1 != "dummy value 2"));
        REQUIRE(sv1 != "dummy value");
    }

    SECTION("Getter and setter")
    {
        StringValue sv;
        REQUIRE(!sv.get());
        sv.set("dummy value");
        REQUIRE(strcmp(sv.get(), "dummy value") == 0);
    }
}

TEST_CASE("NULL value tests")
{
    SECTION("Check for NULL cell")
    {
        Value* nv = new NullValue();
        REQUIRE(typeid(*nv) == typeid(NullValue&));
        REQUIRE(typeid(*nv) != typeid(StringValue&));
        delete nv;
    }
}
