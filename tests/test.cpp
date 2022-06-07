#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../source/integer_value.hpp"
#include "../source/float_value.hpp"
#include "../source/string_value.hpp"
#include "../source/null_value.hpp"
#include "../source/dynamic_array.hpp"

#include <typeinfo>

TEST_CASE("Dynamic array tests")
{
    SECTION("Default constructor")
    {
        DynamicArray<const char*> array;
        REQUIRE(array.size() == 0);
    }

    SECTION("Constructor with parameter")
    {
        DynamicArray<const char*> array(3);
        REQUIRE(array.size() == 0);
    }

    SECTION("Copy constructor")
    {
        DynamicArray<const char*> array;
        const char* str = "dummy string";
        array.push_back(str);

        REQUIRE(strcmp(array[0], str) == 0);
        REQUIRE(array.size() == 1);

        DynamicArray<const char*> copy(array);
        REQUIRE(strcmp(copy[0], str) == 0);
        REQUIRE(strcmp(copy[0], array[0]) == 0);
        REQUIRE(copy.size() == 1);
    }

    SECTION("Operator =")
    {
        DynamicArray<const char*> array;
        const char* str = "dummy string";
        array.push_back(str);

        REQUIRE(strcmp(array[0], str) == 0);
        REQUIRE(array.size() == 1);

        DynamicArray<const char*> copy = array;
        REQUIRE(strcmp(copy[0], str) == 0);
        REQUIRE(strcmp(copy[0], array[0]) == 0);
        REQUIRE(copy.size() == 1);
    }

    SECTION("Expand")
    {
        DynamicArray<const char*> array;
        const char* str1 = "dummy string";
        const char* str2 = "dummy string 2";
        const char* str3 = "dummy string 3";
        const char* str4 = "dummy string 4";
        const char* str5 = "dummy string 5";
        const char* str6 = "dummy string 6";

        array.push_back(str1);
        array.push_back(str2);
        array.push_back(str3);
        array.push_back(str4);
        array.push_back(str5);
        array.push_back(str6);

        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str2) == 0);
        REQUIRE(strcmp(array[2], str3) == 0);
        REQUIRE(strcmp(array[3], str4) == 0);
        REQUIRE(strcmp(array[4], str5) == 0);
        REQUIRE(strcmp(array[5], str6) == 0);
        REQUIRE(array.size() == 6);
    }

    SECTION("Operator []")
    {
        DynamicArray<const char*> array;
        const char* str1 = "dummy string";
        const char* str2 = "dummy string 2";

        array.push_back(str1);
        array.push_back(str2);

        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str2) == 0);
    }

    SECTION("Insert")
    {
        DynamicArray<const char*> array;
        const char* str1 = "dummy string";
        const char* str2 = "dummy string 2";

        array.insert(str1, 0);
        array.insert(str2, 2);

        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[2], str2) == 0);
    }

    SECTION("Push")
    {
        DynamicArray<const char*> array;
        const char* str1 = "dummy string";
        const char* str2 = "dummy string 2";
        const char* str3 = "dummy string 3";

        array.push_back(str1);
        array.push_back(str2);
        array.push_back(str3);

        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str2) == 0);
        REQUIRE(strcmp(array[2], str3) == 0);
    }

    SECTION("Erase")
    {
        DynamicArray<const char*> array;
        const char* str1 = "dummy string";
        const char* str2 = "dummy string 2";
        const char* str3 = "dummy string 3";

        array.push_back(str1);
        array.push_back(str2);
        array.push_back(str3);

        REQUIRE(array.size() == 3);
        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str2) == 0);
        REQUIRE(strcmp(array[2], str3) == 0);

        array.erase(2);
        REQUIRE(array.size() == 2);

        array.erase(1);
        REQUIRE(array.size() == 1);

        array.erase(0);
        REQUIRE(array.size() == 0);
    }

    SECTION("Pop")
    {
        DynamicArray<const char*> array;
        const char* str1 = "dummy string";
        const char* str2 = "dummy string 2";
        const char* str3 = "dummy string 3";

        array.push_back(str1);
        array.push_back(str2);
        array.push_back(str3);

        REQUIRE(array.size() == 3);
        REQUIRE(strcmp(array[0], str1) == 0);
        REQUIRE(strcmp(array[1], str2) == 0);
        REQUIRE(strcmp(array[2], str3) == 0);

        array.pop_back();
        REQUIRE(array.size() == 2);

        array.pop_back();
        REQUIRE(array.size() == 1);

        array.pop_back();
        REQUIRE(array.size() == 0);
    }
}

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

    SECTION("Operator <<")
    {
        IntegerValue iv(-2), iv1(+3);
        std::stringstream out, out1, out2, out3;
        out << iv;
        REQUIRE(out.str() == "-2");

        out1 << std::setw(10) << iv;
        REQUIRE(out1.str() == "        -2");

        out2 << iv1;
        REQUIRE(out2.str() == "3");

        out3 << std::setw(10) << iv1;
        REQUIRE(out3.str() == "         3");
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

    SECTION("Operator <<")
    {
        FloatValue fv(-2.32), fv1(+8.97);
        std::stringstream out, out1, out2, out3;
        out << fv;
        REQUIRE(out.str() == "-2.32");

        out1 << std::setw(10) << fv;
        REQUIRE(out1.str() == "     -2.32");

        out2 << fv1;
        REQUIRE(out2.str() == "8.97");

        out3 << std::setw(10) << fv1;
        REQUIRE(out3.str() == "      8.97");
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

    SECTION("Operator <<")
    {
        StringValue sv("dummy value");
        std::stringstream out, out1;
        out << sv;
        REQUIRE(out.str() == "dummy value");

        out1 << std::setw(20) << sv;
        REQUIRE(out1.str() == "         dummy value");
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

    SECTION("Operator <<")
    {
        NullValue nv;
        std::stringstream out, out1;
        out << nv;
        REQUIRE(out.str() == "NULL");

        out1 << std::setw(10) << nv;
        REQUIRE(out1.str() == "      NULL");
    }
}
