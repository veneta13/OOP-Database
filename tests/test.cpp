#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../source/database.hpp"

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

TEST_CASE("Integer column tests")
{
    SECTION("Default constructor")
    {
        NullValue* nullv = new NullValue();
        IntegerColumn ic;

        REQUIRE(ic.columnType() == ColumnType::Integer);
        REQUIRE(ic.countValue(nullv) == 0);

        delete nullv;
    }

    SECTION("Constructor with parameter")
    {
        NullValue* nullv = new NullValue();

        IntegerColumn ic(2);

        REQUIRE(ic.countValue(nullv) == 2);

        delete nullv;
    }

    SECTION("Copy constructor")
    {
        IntegerValue* intv = new IntegerValue(5);
        NullValue* nullv = new NullValue();

        IntegerColumn ic;
        ic.insert(intv);
        ic.insert(nullv);
        REQUIRE(ic.countValue(nullv) == 1);
        REQUIRE(ic.countValue(intv) == 1);

        IntegerColumn ic2(ic);
        REQUIRE(ic2.countValue(nullv) == 1);
        REQUIRE(ic2.countValue(intv) == 1);

        delete intv;
        delete nullv;
    }

    SECTION("Operator =")
    {
        IntegerValue* intv = new IntegerValue(5);
        NullValue* nullv = new NullValue();

        IntegerColumn ic;
        ic.insert(intv);
        ic.insert(nullv);
        REQUIRE(ic.countValue(nullv) == 1);
        REQUIRE(ic.countValue(intv) == 1);

        IntegerColumn ic2 = ic;
        REQUIRE(ic2.countValue(nullv) == 1);
        REQUIRE(ic2.countValue(intv) == 1);

        delete intv;
        delete nullv;
    }

    SECTION("Operator []")
    {
        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);;

        IntegerColumn ic;
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);
        ic.insert(intv9);

        REQUIRE((*dynamic_cast<IntegerValue*>(ic[0])) == (*intv5));
        REQUIRE((*dynamic_cast<IntegerValue*>(ic[1])) == (*intv5));
        REQUIRE((*dynamic_cast<IntegerValue*>(ic[2])) == (*intv2));
        REQUIRE((*dynamic_cast<IntegerValue*>(ic[3])) == (*intv9));

        delete intv5;
        delete intv2;
        delete intv9;
    }

    SECTION("Insert")
    {
        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);
        NullValue* nullv = new NullValue();

        IntegerColumn ic;
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);
        ic.insert(intv9);
        ic.insert(nullv);

        REQUIRE(ic.countValue(intv5) == 2);
        REQUIRE(ic.countValue(intv2) == 1);
        REQUIRE(ic.countValue(intv9) == 1);
        REQUIRE(ic.countValue(nullv) == 1);

        delete intv5;
        delete intv2;
        delete intv9;
        delete nullv;
    }

    SECTION("Update")
    {
        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);
        NullValue* nullv = new NullValue();

        IntegerColumn ic;
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);

        REQUIRE(ic.countValue(intv5) == 2);
        REQUIRE(ic.countValue(intv2) == 1);
        REQUIRE(ic.countValue(intv9) == 0);

        DynamicArray<int> da1;
        ic.select(intv2, da1);
        ic.update(da1, intv9);
        REQUIRE(ic.countValue(intv5) == 2);
        REQUIRE(ic.countValue(intv2) == 0);
        REQUIRE(ic.countValue(intv9) == 1);

        DynamicArray<int> da2;
        ic.select(intv9, da2);
        ic.update(da2, intv5);
        REQUIRE(ic.countValue(intv5) == 3);
        REQUIRE(ic.countValue(intv2) == 0);
        REQUIRE(ic.countValue(intv9) == 0);

        DynamicArray<int> da3;
        ic.select(intv5, da3);
        ic.update(da3, nullv);
        REQUIRE(ic.countValue(intv5) == 0);
        REQUIRE(ic.countValue(intv2) == 0);
        REQUIRE(ic.countValue(intv9) == 0);
        REQUIRE(ic.countValue(nullv) == 3);

        delete intv5;
        delete intv2;
        delete intv9;
        delete nullv;
    }

    SECTION("Delete by indexes")
    {
        DynamicArray<int> indexes;

        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);
        NullValue* nullv = new NullValue();

        indexes.push_back(1);
        indexes.push_back(2);

        IntegerColumn ic;
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);
        ic.insert(intv9);
        ic.insert(nullv);

        REQUIRE(ic.countValue(intv5) == 2);
        REQUIRE(ic.countValue(intv2) == 1);
        REQUIRE(ic.countValue(intv9) == 1);
        REQUIRE(ic.countValue(nullv) == 1);

        ic.deleteByIndexes(indexes);

        REQUIRE(ic.countValue(intv5) == 1);
        REQUIRE(ic.countValue(intv2) == 0);
        REQUIRE(ic.countValue(intv9) == 1);
        REQUIRE(ic.countValue(nullv) == 1);

        ic.deleteByIndexes(indexes);

        REQUIRE(ic.countValue(intv5) == 1);
        REQUIRE(ic.countValue(intv2) == 0);
        REQUIRE(ic.countValue(intv9) == 0);
        REQUIRE(ic.countValue(nullv) == 0);

        delete intv5;
        delete intv2;
        delete intv9;
        delete nullv;
    }

    SECTION("Select")
    {
        DynamicArray<int> indexes;

        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);
        NullValue* nullv = new NullValue();

        IntegerColumn ic;
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);
        ic.insert(intv9);
        ic.insert(nullv);

        REQUIRE(ic.countValue(intv5) == 2);
        REQUIRE(ic.countValue(intv2) == 1);
        REQUIRE(ic.countValue(intv9) == 1);
        REQUIRE(ic.countValue(nullv) == 1);

        ic.select(intv5, indexes);
        REQUIRE(indexes.size() == 2);
        REQUIRE(indexes[0] == 0);
        REQUIRE(indexes[1] == 1);

        ic.select(intv9, indexes);
        REQUIRE(indexes.size() == 3);
        REQUIRE(indexes[0] == 0);
        REQUIRE(indexes[1] == 1);
        REQUIRE(indexes[2] == 3);

        delete intv5;
        delete intv2;
        delete intv9;
        delete nullv;
    }

    SECTION("Count")
    {
        DynamicArray<int> indexes;

        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);
        NullValue* nullv = new NullValue();

        IntegerColumn ic;
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);
        ic.insert(intv9);
        ic.insert(nullv);

        REQUIRE(ic.countValue(intv5) == 2);
        REQUIRE(ic.countValue(intv2) == 1);
        REQUIRE(ic.countValue(intv9) == 1);
        REQUIRE(ic.countValue(nullv) == 1);

        delete intv5;
        delete intv2;
        delete intv9;
        delete nullv;
    }

    SECTION("Column type")
    {
        IntegerColumn ic;
        REQUIRE(ic.columnType() == ColumnType::Integer);
    }

    SECTION("Size")
    {
        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);
        NullValue* nullv = new NullValue();

        IntegerColumn ic, ic2(7);
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);
        ic.insert(intv9);
        ic.insert(nullv);

        std::stringstream out;

        REQUIRE(ic.size() == 5);
        REQUIRE(ic2.size() == 7);

        delete intv5;
        delete intv2;
        delete intv9;
        delete nullv;
    }

    SECTION("Sum")
    {
        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);
        NullValue* nullv = new NullValue();

        IntegerColumn ic;
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);
        ic.insert(intv9);
        ic.insert(nullv);

        std::stringstream out;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);
        dyn.push_back(4);
        ic.sum(out, dyn);

        REQUIRE(out.str() == "SUM OF COLUMN: 21\n");

        delete intv5;
        delete intv2;
        delete intv9;
        delete nullv;
    }

    SECTION("Product")
    {
        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);
        NullValue* nullv = new NullValue();

        IntegerColumn ic;
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);
        ic.insert(intv9);
        ic.insert(nullv);

        std::stringstream out;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);
        dyn.push_back(4);
        ic.product(out, dyn);

        REQUIRE(out.str() == "PRODUCT OF COLUMN: 450\n");

        delete intv5;
        delete intv2;
        delete intv9;
        delete nullv;
    }

    SECTION("Maximum")
    {
        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);
        NullValue* nullv = new NullValue();

        IntegerColumn ic, ic1(5), ic2;
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);
        ic.insert(intv9);
        ic.insert(nullv);

        std::stringstream out, out1, out2;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);
        dyn.push_back(4);
        ic.maximum(out ,dyn);
        ic1.maximum(out1, dyn);
        ic2.maximum(out2, dyn);

        REQUIRE(out.str() == "MAX: 9\n");
        REQUIRE(out1.str() == "Values contain only NULL!\n");
        REQUIRE(out2.str() == "EMPTY COLUMN - no MAX value!\n");

        delete intv5;
        delete intv2;
        delete intv9;
        delete nullv;
    }

    SECTION("Minumum")
    {
        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);
        NullValue* nullv = new NullValue();

        IntegerColumn ic, ic1(5), ic2;
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);
        ic.insert(intv9);
        ic.insert(nullv);

        std::stringstream out, out1, out2;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);
        dyn.push_back(4);
        ic.minimum(out ,dyn);
        ic1.minimum(out1, dyn);
        ic2.minimum(out2, dyn);

        REQUIRE(out.str() == "MIN: 2\n");
        REQUIRE(out1.str() == "Values contain only NULL!\n");
        REQUIRE(out2.str() == "EMPTY COLUMN - no MIN value!\n");

        delete intv5;
        delete intv2;
        delete intv9;
        delete nullv;
    }

    SECTION("Print")
    {
        IntegerValue* intv5 = new IntegerValue(5);
        IntegerValue* intv2 = new IntegerValue(2);
        IntegerValue* intv9 = new IntegerValue(9);
        NullValue* nullv = new NullValue();

        IntegerColumn ic, ic1(5);
        ic.insert(intv5);
        ic.insert(intv5);
        ic.insert(intv2);
        ic.insert(intv9);
        ic.insert(nullv);

        std::stringstream out, out2;

        for (int i = 0; i < ic.size(); i++) {
            ic.print(out, i, 5);
        }

        for (int i = 0; i < ic1.size(); i++) {
            ic1.print(out2, i, 5);
        }

        REQUIRE(out.str() == "    5    5    2    9 NULL");
        REQUIRE(out2.str() == " NULL NULL NULL NULL NULL");

        delete intv5;
        delete intv2;
        delete intv9;
        delete nullv;
    }
}

TEST_CASE("Float column tests")
{
    SECTION("Default constructor")
    {
        NullValue* nullv = new NullValue();
        FloatColumn fc;

        REQUIRE(fc.columnType() == ColumnType::FloatingPoint);
        REQUIRE(fc.countValue(nullv) == 0);

        delete nullv;
    }

    SECTION("Constructor with parameter")
    {
        NullValue* nullv = new NullValue();

        FloatColumn fc(2);

        REQUIRE(fc.countValue(nullv) == 2);

        delete nullv;
    }

    SECTION("Copy constructor")
    {
        FloatValue* flov = new FloatValue(5.12);
        NullValue* nullv = new NullValue();

        FloatColumn fc;
        fc.insert(flov);
        fc.insert(nullv);
        REQUIRE(fc.countValue(nullv) == 1);
        REQUIRE(fc.countValue(flov) == 1);

        FloatColumn fc2(fc);
        REQUIRE(fc2.countValue(nullv) == 1);
        REQUIRE(fc2.countValue(flov) == 1);

        delete flov;
        delete nullv;
    }

    SECTION("Operator =")
    {
        FloatValue* flov = new FloatValue(5.15);
        NullValue* nullv = new NullValue();

        FloatColumn fc;
        fc.insert(flov);
        fc.insert(nullv);
        REQUIRE(fc.countValue(nullv) == 1);
        REQUIRE(fc.countValue(flov) == 1);

        FloatColumn fc2 = fc;
        REQUIRE(fc2.countValue(nullv) == 1);
        REQUIRE(fc2.countValue(flov) == 1);

        delete flov;
        delete nullv;
    }

    SECTION("Operator []")
    {
        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);

        FloatColumn fc;
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);
        fc.insert(flov9);

        REQUIRE((*dynamic_cast<FloatValue*>(fc[0])) == (*flov5));
        REQUIRE((*dynamic_cast<FloatValue*>(fc[1])) == (*flov5));
        REQUIRE((*dynamic_cast<FloatValue*>(fc[2])) == (*flov2));
        REQUIRE((*dynamic_cast<FloatValue*>(fc[3])) == (*flov9));

        delete flov5;
        delete flov2;
        delete flov9;
    }

    SECTION("Insert")
    {
        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);
        NullValue* nullv = new NullValue();

        FloatColumn fc;
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);
        fc.insert(flov9);
        fc.insert(nullv);

        REQUIRE(fc.countValue(flov5) == 2);
        REQUIRE(fc.countValue(flov2) == 1);
        REQUIRE(fc.countValue(flov9) == 1);
        REQUIRE(fc.countValue(nullv) == 1);

        delete flov5;
        delete flov2;
        delete flov9;
        delete nullv;
    }

    SECTION("Update")
    {
        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);
        NullValue* nullv = new NullValue();

        FloatColumn fc;
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);

        REQUIRE(fc.countValue(flov5) == 2);
        REQUIRE(fc.countValue(flov2) == 1);
        REQUIRE(fc.countValue(flov9) == 0);

        DynamicArray<int> da1;
        fc.select(flov2, da1);
        fc.update(da1, flov9);
        REQUIRE(fc.countValue(flov5) == 2);
        REQUIRE(fc.countValue(flov2) == 0);
        REQUIRE(fc.countValue(flov9) == 1);

        DynamicArray<int> da2;
        fc.select(flov9, da2);
        fc.update(da2, flov5);
        REQUIRE(fc.countValue(flov5) == 3);
        REQUIRE(fc.countValue(flov2) == 0);
        REQUIRE(fc.countValue(flov9) == 0);

        DynamicArray<int> da3;
        fc.select(flov5, da1);
        fc.update(da1, nullv);
        REQUIRE(fc.countValue(flov5) == 0);
        REQUIRE(fc.countValue(flov2) == 0);
        REQUIRE(fc.countValue(flov9) == 0);
        REQUIRE(fc.countValue(nullv) == 3);

        delete flov5;
        delete flov2;
        delete flov9;
        delete nullv;
    }

    SECTION("Delete by indexes")
    {
        DynamicArray<int> indexes;

        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);
        NullValue* nullv = new NullValue();

        indexes.push_back(1);
        indexes.push_back(2);

        FloatColumn fc;
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);
        fc.insert(flov9);
        fc.insert(nullv);

        REQUIRE(fc.countValue(flov5) == 2);
        REQUIRE(fc.countValue(flov2) == 1);
        REQUIRE(fc.countValue(flov9) == 1);
        REQUIRE(fc.countValue(nullv) == 1);

        fc.deleteByIndexes(indexes);

        REQUIRE(fc.countValue(flov5) == 1);
        REQUIRE(fc.countValue(flov2) == 0);
        REQUIRE(fc.countValue(flov9) == 1);
        REQUIRE(fc.countValue(nullv) == 1);

        fc.deleteByIndexes(indexes);

        REQUIRE(fc.countValue(flov5) == 1);
        REQUIRE(fc.countValue(flov2) == 0);
        REQUIRE(fc.countValue(flov9) == 0);
        REQUIRE(fc.countValue(nullv) == 0);

        delete flov5;
        delete flov2;
        delete flov9;
        delete nullv;
    }

    SECTION("Select")
    {
        DynamicArray<int> indexes;

        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);
        NullValue* nullv = new NullValue();

        FloatColumn fc;
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);
        fc.insert(flov9);
        fc.insert(nullv);

        REQUIRE(fc.countValue(flov5) == 2);
        REQUIRE(fc.countValue(flov2) == 1);
        REQUIRE(fc.countValue(flov9) == 1);
        REQUIRE(fc.countValue(nullv) == 1);

        fc.select(flov5, indexes);
        REQUIRE(indexes.size() == 2);
        REQUIRE(indexes[0] == 0);
        REQUIRE(indexes[1] == 1);

        fc.select(flov9, indexes);
        REQUIRE(indexes.size() == 3);
        REQUIRE(indexes[0] == 0);
        REQUIRE(indexes[1] == 1);
        REQUIRE(indexes[2] == 3);

        delete flov5;
        delete flov2;
        delete flov9;
        delete nullv;
    }

    SECTION("Count")
    {
        DynamicArray<int> indexes;

        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);
        NullValue* nullv = new NullValue();

        FloatColumn fc;
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);
        fc.insert(flov9);
        fc.insert(nullv);

        REQUIRE(fc.countValue(flov5) == 2);
        REQUIRE(fc.countValue(flov2) == 1);
        REQUIRE(fc.countValue(flov9) == 1);
        REQUIRE(fc.countValue(nullv) == 1);

        delete flov5;
        delete flov2;
        delete flov9;
        delete nullv;
    }

    SECTION("Column type")
    {
        FloatColumn fc;
        REQUIRE(fc.columnType() == ColumnType::FloatingPoint);
    }

    SECTION("Size")
    {
        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);
        NullValue* nullv = new NullValue();

        FloatColumn fc, fc2(7);
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);
        fc.insert(flov9);
        fc.insert(nullv);

        std::stringstream out;

        REQUIRE(fc.size() == 5);
        REQUIRE(fc2.size() == 7);

        delete flov5;
        delete flov2;
        delete flov9;
        delete nullv;
    }

    SECTION("Sum")
    {
        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);
        NullValue* nullv = new NullValue();

        FloatColumn fc;
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);
        fc.insert(flov9);
        fc.insert(nullv);

        std::stringstream out;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);
        dyn.push_back(4);
        fc.sum(out ,dyn);

        REQUIRE(out.str() == "SUM OF COLUMN: 23.1\n");

        delete flov5;
        delete flov2;
        delete flov9;
        delete nullv;
    }

    SECTION("Product")
    {
        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);
        NullValue* nullv = new NullValue();

        FloatColumn fc;
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);
        fc.insert(flov9);
        fc.insert(nullv);

        std::stringstream out;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);
        dyn.push_back(4);
        fc.product(out ,dyn);

        REQUIRE(out.str() == "PRODUCT OF COLUMN: 658.845\n");

        delete flov5;
        delete flov2;
        delete flov9;
        delete nullv;
    }

    SECTION("Maximum")
    {
        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);
        NullValue* nullv = new NullValue();

        FloatColumn fc, fc1(5), fc2;
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);
        fc.insert(flov9);
        fc.insert(nullv);

        std::stringstream out, out1, out2;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);
        dyn.push_back(4);
        fc.maximum(out ,dyn);
        fc1.maximum(out1, dyn);
        fc2.maximum(out2, dyn);

        REQUIRE(out.str() == "MAX: 9.9\n");
        REQUIRE(out1.str() == "Values contain only NULL!\n");
        REQUIRE(out2.str() == "EMPTY COLUMN - no MAX value!\n");

        delete flov5;
        delete flov2;
        delete flov9;
        delete nullv;
    }

    SECTION("Minumum")
    {
        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);;
        NullValue* nullv = new NullValue();

        FloatColumn fc, fc1(5), fc2;
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);
        fc.insert(flov9);
        fc.insert(nullv);

        std::stringstream out, out1, out2;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);
        dyn.push_back(4);
        fc.minimum(out ,dyn);
        fc1.minimum(out1, dyn);
        fc2.minimum(out2, dyn);

        REQUIRE(out.str() == "MIN: 2.2\n");
        REQUIRE(out1.str() == "Values contain only NULL!\n");
        REQUIRE(out2.str() == "EMPTY COLUMN - no MIN value!\n");

        delete flov5;
        delete flov2;
        delete flov9;
        delete nullv;
    }

    SECTION("Print")
    {
        FloatValue* flov5 = new FloatValue(5.5);
        FloatValue* flov2 = new FloatValue(2.2);
        FloatValue* flov9 = new FloatValue(9.9);;
        NullValue* nullv = new NullValue();

        FloatColumn fc, fc1(5);
        fc.insert(flov5);
        fc.insert(flov5);
        fc.insert(flov2);
        fc.insert(flov9);
        fc.insert(nullv);

        std::stringstream out, out2;

        for (int i = 0; i < fc.size(); i++) {
            fc.print(out, i, 5);
        }

        for (int i = 0; i < fc1.size(); i++) {
            fc1.print(out2, i, 5);
        }

        REQUIRE(out.str() == "  5.5  5.5  2.2  9.9 NULL");
        REQUIRE(out2.str() == " NULL NULL NULL NULL NULL");

        delete flov5;
        delete flov2;
        delete flov9;
        delete nullv;
    }
}

TEST_CASE("String column tests")
{
    SECTION("Default constructor")
    {
        NullValue* nullv = new NullValue();
        StringColumn sc;

        REQUIRE(sc.columnType() == ColumnType::String);
        REQUIRE(sc.countValue(nullv) == 0);

        delete nullv;
    }

    SECTION("Constructor with parameter")
    {
        NullValue* nullv = new NullValue();

        StringColumn sc(2);

        REQUIRE(sc.countValue(nullv) == 2);

        delete nullv;
    }

    SECTION("Copy constructor")
    {
        StringValue* strv = new StringValue("dummy");
        NullValue* nullv = new NullValue();

        StringColumn sc;
        sc.insert(strv);
        sc.insert(nullv);
        REQUIRE(sc.countValue(nullv) == 1);
        REQUIRE(sc.countValue(strv) == 1);

        StringColumn sc2(sc);
        REQUIRE(sc2.countValue(nullv) == 1);
        REQUIRE(sc2.countValue(strv) == 1);

        delete strv;
        delete nullv;
    }

    SECTION("Operator =")
    {
        StringValue* strv = new StringValue("dummy");
        NullValue* nullv = new NullValue();

        StringColumn sc;
        sc.insert(strv);
        sc.insert(nullv);
        REQUIRE(sc.countValue(nullv) == 1);
        REQUIRE(sc.countValue(strv) == 1);

        StringColumn sc2 = sc;
        REQUIRE(sc2.countValue(nullv) == 1);
        REQUIRE(sc2.countValue(strv) == 1);

        delete strv;
        delete nullv;
    }

    SECTION("Operator []")
    {
        StringValue* strv5 = new StringValue("dummy");
        StringValue* strv2 = new StringValue("dummy1");
        StringValue* strv9 = new StringValue("dummy2");

        StringColumn sc;
        sc.insert(strv5);
        sc.insert(strv5);
        sc.insert(strv2);
        sc.insert(strv9);

        REQUIRE((*dynamic_cast<StringValue*>(sc[0])) == (*strv5));
        REQUIRE((*dynamic_cast<StringValue*>(sc[1])) == (*strv5));
        REQUIRE((*dynamic_cast<StringValue*>(sc[2])) == (*strv2));
        REQUIRE((*dynamic_cast<StringValue*>(sc[3])) == (*strv9));

        delete strv5;
        delete strv2;
        delete strv9;
    }

    SECTION("Insert")
    {
        StringValue* strv5 = new StringValue("dummy");
        StringValue* strv2 = new StringValue("dummy1");
        StringValue* strv9 = new StringValue("dummy2");
        NullValue* nullv = new NullValue();

        StringColumn sc;
        sc.insert(strv5);
        sc.insert(strv5);
        sc.insert(strv2);
        sc.insert(strv9);
        sc.insert(nullv);

        REQUIRE(sc.countValue(strv5) == 2);
        REQUIRE(sc.countValue(strv2) == 1);
        REQUIRE(sc.countValue(strv9) == 1);
        REQUIRE(sc.countValue(nullv) == 1);

        delete strv5;
        delete strv2;
        delete strv9;
        delete nullv;
    }

    SECTION("Update")
    {
        StringValue* strv5 = new StringValue("dummy");
        StringValue* strv2 = new StringValue("dummy1");
        StringValue* strv9 = new StringValue("dummy2");
        NullValue* nullv = new NullValue();

        StringColumn sc;
        sc.insert(strv5);
        sc.insert(strv5);
        sc.insert(strv2);

        REQUIRE(sc.countValue(strv5) == 2);
        REQUIRE(sc.countValue(strv2) == 1);
        REQUIRE(sc.countValue(strv9) == 0);

        DynamicArray<int> da1;
        sc.select(strv2, da1);
        sc.update(da1, strv9);
        REQUIRE(sc.countValue(strv5) == 2);
        REQUIRE(sc.countValue(strv2) == 0);
        REQUIRE(sc.countValue(strv9) == 1);

        DynamicArray<int> da2;
        sc.select(strv9, da2);
        sc.update(da2, strv5);
        REQUIRE(sc.countValue(strv5) == 3);
        REQUIRE(sc.countValue(strv2) == 0);
        REQUIRE(sc.countValue(strv9) == 0);

        DynamicArray<int> da3;
        sc.select(strv5, da3);
        sc.update(da3, nullv);
        REQUIRE(sc.countValue(strv5) == 0);
        REQUIRE(sc.countValue(strv2) == 0);
        REQUIRE(sc.countValue(strv9) == 0);
        REQUIRE(sc.countValue(nullv) == 3);

        delete strv5;
        delete strv2;
        delete strv9;
        delete nullv;
    }

    SECTION("Delete by indexes")
    {
        DynamicArray<int> indexes;

        StringValue* strv5 = new StringValue("dummy");
        StringValue* strv2 = new StringValue("dummy1");
        StringValue* strv9 = new StringValue("dummy2");
        NullValue* nullv = new NullValue();

        indexes.push_back(1);
        indexes.push_back(2);

        StringColumn sc;
        sc.insert(strv5);
        sc.insert(strv5);
        sc.insert(strv2);
        sc.insert(strv9);
        sc.insert(nullv);

        REQUIRE(sc.countValue(strv5) == 2);
        REQUIRE(sc.countValue(strv2) == 1);
        REQUIRE(sc.countValue(strv9) == 1);
        REQUIRE(sc.countValue(nullv) == 1);

        sc.deleteByIndexes(indexes);

        REQUIRE(sc.countValue(strv5) == 1);
        REQUIRE(sc.countValue(strv2) == 0);
        REQUIRE(sc.countValue(strv9) == 1);
        REQUIRE(sc.countValue(nullv) == 1);

        sc.deleteByIndexes(indexes);

        REQUIRE(sc.countValue(strv5) == 1);
        REQUIRE(sc.countValue(strv2) == 0);
        REQUIRE(sc.countValue(strv9) == 0);
        REQUIRE(sc.countValue(nullv) == 0);

        delete strv5;
        delete strv2;
        delete strv9;
        delete nullv;
    }

    SECTION("Select")
    {
        DynamicArray<int> indexes;

        StringValue* strv5 = new StringValue("dummy");
        StringValue* strv2 = new StringValue("dummy1");
        StringValue* strv9 = new StringValue("dummy2");
        NullValue* nullv = new NullValue();

        StringColumn sc;
        sc.insert(strv5);
        sc.insert(strv5);
        sc.insert(strv2);
        sc.insert(strv9);
        sc.insert(nullv);

        REQUIRE(sc.countValue(strv5) == 2);
        REQUIRE(sc.countValue(strv2) == 1);
        REQUIRE(sc.countValue(strv9) == 1);
        REQUIRE(sc.countValue(nullv) == 1);

        sc.select(strv5, indexes);
        REQUIRE(indexes.size() == 2);
        REQUIRE(indexes[0] == 0);
        REQUIRE(indexes[1] == 1);

        sc.select(strv9, indexes);
        REQUIRE(indexes.size() == 3);
        REQUIRE(indexes[0] == 0);
        REQUIRE(indexes[1] == 1);
        REQUIRE(indexes[2] == 3);

        delete strv5;
        delete strv2;
        delete strv9;
        delete nullv;
    }

    SECTION("Count")
    {
        DynamicArray<int> indexes;

        StringValue* strv5 = new StringValue("dummy");
        StringValue* strv2 = new StringValue("dummy1");
        StringValue* strv9 = new StringValue("dummy2");
        NullValue* nullv = new NullValue();

        StringColumn sc;
        sc.insert(strv5);
        sc.insert(strv5);
        sc.insert(strv2);
        sc.insert(strv9);
        sc.insert(nullv);

        REQUIRE(sc.countValue(strv5) == 2);
        REQUIRE(sc.countValue(strv2) == 1);
        REQUIRE(sc.countValue(strv9) == 1);
        REQUIRE(sc.countValue(nullv) == 1);

        delete strv5;
        delete strv2;
        delete strv9;
        delete nullv;
    }

    SECTION("Column type")
    {
        StringColumn sc;
        REQUIRE(sc.columnType() == ColumnType::String);
    }

    SECTION("Size")
    {
        StringValue* strv5 = new StringValue("dummy");
        StringValue* strv2 = new StringValue("dummy1");
        StringValue* strv9 = new StringValue("dummy2");
        NullValue* nullv = new NullValue();

        StringColumn sc, fc2(7);
        sc.insert(strv5);
        sc.insert(strv5);
        sc.insert(strv2);
        sc.insert(strv9);
        sc.insert(nullv);

        std::stringstream out;

        REQUIRE(sc.size() == 5);
        REQUIRE(fc2.size() == 7);

        delete strv5;
        delete strv2;
        delete strv9;
        delete nullv;
    }

    SECTION("Sum")
    {
        StringValue* strv5 = new StringValue("dummy");

        StringColumn sc;
        sc.insert(strv5);

        std::stringstream out;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        sc.sum(out, dyn);

        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");

        delete strv5;
    }

    SECTION("Product")
    {
        StringValue* strv5 = new StringValue("dummy");

        StringColumn sc;
        sc.insert(strv5);

        std::stringstream out;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        sc.product(out, dyn);

        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");

        delete strv5;
    }

    SECTION("Maximum")
    {
        StringValue* strv5 = new StringValue("dummy");

        StringColumn sc;
        sc.insert(strv5);

        std::stringstream out;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        sc.maximum(out, dyn);

        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");

        delete strv5;
    }

    SECTION("Minumum")
    {
        StringValue* strv5 = new StringValue("dummy");

        StringColumn sc;
        sc.insert(strv5);

        std::stringstream out;
        DynamicArray<int> dyn;
        dyn.push_back(0);
        sc.minimum(out, dyn);

        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");

        delete strv5;
    }

    SECTION("Print")
    {
        StringValue* strv5 = new StringValue("dummy");
        StringValue* strv2 = new StringValue("dummy1");
        StringValue* strv9 = new StringValue("dummy2");
        NullValue* nullv = new NullValue();

        StringColumn sc, fc1(5);
        sc.insert(strv5);
        sc.insert(strv5);
        sc.insert(strv2);
        sc.insert(strv9);
        sc.insert(nullv);

        std::stringstream out, out2;

        for (int i = 0; i < sc.size(); i++) {
            sc.print(out, i, 8);
        }

        for (int i = 0; i < fc1.size(); i++) {
            fc1.print(out2, i, 8);
        }

        REQUIRE(out.str() == "   dummy   dummy  dummy1  dummy2    NULL");
        REQUIRE(out2.str() == "    NULL    NULL    NULL    NULL    NULL");

        delete strv5;
        delete strv2;
        delete strv9;
        delete nullv;
    }
}

TEST_CASE("Table tests")
{
    SECTION("Default constructor")
    {
        Table table;
        REQUIRE(table.getName() == nullptr);
        REQUIRE(table.getFile() == nullptr);
    }

    SECTION("Constructor with name")
    {
        Table table("dummy table");
        REQUIRE(strcmp(table.getName(), "dummy table") == 0);
        REQUIRE(table.getFile() == nullptr);
    }

    SECTION("Constructor with name and file")
    {
        Table table("dummy table", "file.txt");
        REQUIRE(strcmp(table.getName(), "dummy table") == 0);
        REQUIRE(strcmp(table.getFile(), "file.txt") == 0);
    }

    SECTION("Copy constructor")
    {
        Table table("dummy table", "file.txt");
        REQUIRE(strcmp(table.getName(), "dummy table") == 0);
        REQUIRE(strcmp(table.getFile(), "file.txt") == 0);

        Table table1(table);
        REQUIRE(strcmp(table1.getName(), "dummy table") == 0);
        REQUIRE(strcmp(table1.getFile(), "file.txt") == 0);
    }

    SECTION("Operator =")
    {
        Table table("dummy table", "file.txt");
        REQUIRE(strcmp(table.getName(), "dummy table") == 0);
        REQUIRE(strcmp(table.getFile(), "file.txt") == 0);

        Table table1 = table;
        REQUIRE(strcmp(table1.getName(), "dummy table") == 0);
        REQUIRE(strcmp(table1.getFile(), "file.txt") == 0);
    }

    SECTION("Getter and setter for name")
    {
        Table table;
        REQUIRE(table.getName() == nullptr);
        REQUIRE(table.getFile() == nullptr);

        table.setName("dummy");
        REQUIRE(strcmp(table.getName(), "dummy") == 0);
        REQUIRE(table.getFile() == nullptr);

        table.setName("dummy1");
        REQUIRE(strcmp(table.getName(), "dummy1") == 0);
        REQUIRE(table.getFile() == nullptr);
    }

    SECTION("Getter and setter for file")
    {
        Table table;
        REQUIRE(table.getName() == nullptr);
        REQUIRE(table.getFile() == nullptr);

        table.setFile("dummy.txt");
        REQUIRE(table.getName() == nullptr);
        REQUIRE(strcmp(table.getFile(), "dummy.txt") == 0);

        table.setFile("dummy1.txt");
        REQUIRE(table.getName() == nullptr);
        REQUIRE(strcmp(table.getFile(), "dummy1.txt") == 0);
    }

    SECTION("Describe")
    {
        Table table1("first table");
        Table table2("second table");

        table1.addColumn(ColumnType::Integer);
        table1.addColumn(ColumnType::String);
        table1.addColumn(ColumnType::Integer);

        table2.addColumn(ColumnType::Integer);
        table2.addColumn(ColumnType::String);
        table2.addColumn(ColumnType::String);
        table2.addColumn(ColumnType::Integer);

        std::stringstream out;

        table1.describe(out);
        REQUIRE(out.str() == "COLUMN TYPES:\n0 - Integer\n1 - String\n2 - Integer\n");

        out = std::stringstream();
        table2.describe(out);
        REQUIRE(out.str() == "COLUMN TYPES:\n0 - Integer\n1 - String\n2 - String\n3 - Integer\n");
    }

    SECTION("Insert column")
    {
        Table table("dummy table", "file.txt");
        REQUIRE(strcmp(table.getName(), "dummy table") == 0);
        REQUIRE(strcmp(table.getFile(), "file.txt") == 0);

        table.addColumn(ColumnType::Integer);
        table.addColumn(ColumnType::Integer);
        table.addColumn(ColumnType::FloatingPoint);
        table.addColumn(ColumnType::String);

        std::stringstream out;
        out << table;

        REQUIRE(out.str() == "dummy table\n4 0 1 1 2 3\n");
    }

    SECTION("Insert row")
    {
        IntegerValue *intv = new IntegerValue(5);
        NullValue *nullv = new NullValue();

        Table table("dummy table", "file.txt");
        REQUIRE(strcmp(table.getName(), "dummy table") == 0);
        REQUIRE(strcmp(table.getFile(), "file.txt") == 0);

        Value **values = new Value *[1];
        values[0] = intv;

        table.addColumn(ColumnType::Integer);
        table.insertRow(values);

        std::stringstream out;
        out << table;

        REQUIRE(out.str() == "dummy table\n1 1 1\n5\n");

        delete intv;
        delete nullv;
        delete[] values;
    }

    SECTION("Get row")
    {
        IntegerValue *intv1 = new IntegerValue(1);
        IntegerValue *intv2 = new IntegerValue(2);
        IntegerValue *intv3 = new IntegerValue(3);
        StringValue *strv1 = new StringValue("string dummy1");
        StringValue *strv2 = new StringValue("string dummy2");
        StringValue *strv3 = new StringValue("string dummy3");

        Table table("table");

        table.addColumn(ColumnType::Integer);
        table.addColumn(ColumnType::String);
        table.addColumn(ColumnType::Integer);

        Value **values = new Value *[3];

        values[0] = intv1;
        values[1] = strv2;
        values[2] = intv2;
        table.insertRow(values);

        values[0] = intv3;
        values[1] = strv3;
        values[2] = intv2;
        table.insertRow(values);

        values[0] = intv2;
        values[1] = strv1;
        values[2] = intv2;
        table.insertRow(values);

        Value** result = table.getRow(0);
        REQUIRE((*dynamic_cast<IntegerValue*>(result[0])) == (*dynamic_cast<IntegerValue*>(intv1)));
        REQUIRE((*dynamic_cast<StringValue*>(result[1])) == (*dynamic_cast<StringValue*>(strv2)));
        REQUIRE((*dynamic_cast<IntegerValue*>(result[2])) == (*dynamic_cast<IntegerValue*>(intv2)));
        delete[] result;

        result = table.getRow(1);
        REQUIRE((*dynamic_cast<IntegerValue*>(result[0])) == (*dynamic_cast<IntegerValue*>(intv3)));
        REQUIRE((*dynamic_cast<StringValue*>(result[1])) == (*dynamic_cast<StringValue*>(strv3)));
        REQUIRE((*dynamic_cast<IntegerValue*>(result[2])) == (*dynamic_cast<IntegerValue*>(intv2)));
        delete[] result;

        result = table.getRow(2);
        REQUIRE((*dynamic_cast<IntegerValue*>(result[0])) == (*dynamic_cast<IntegerValue*>(intv2)));
        REQUIRE((*dynamic_cast<StringValue*>(result[1])) == (*dynamic_cast<StringValue*>(strv1)));
        REQUIRE((*dynamic_cast<IntegerValue*>(result[2])) == (*dynamic_cast<IntegerValue*>(intv2)));
        delete[] result;

        delete intv1;
        delete intv2;
        delete intv3;
        delete strv1;
        delete strv2;
        delete strv3;
        delete[] values;
    }

    SECTION("Select")
    {
        DynamicArray<int> indexes;

        IntegerValue *intv1 = new IntegerValue(5);
        IntegerValue *intv2 = new IntegerValue(6);
        StringValue *strv = new StringValue("string dummy");

        Table table("dummy table", "file.txt");
        REQUIRE(strcmp(table.getName(), "dummy table") == 0);
        REQUIRE(strcmp(table.getFile(), "file.txt") == 0);

        Value **values1 = new Value *[2];
        values1[0] = intv1;
        values1[1] = strv;
        Value **values2 = new Value *[2];
        values2[0] = intv2;
        values2[1] = strv;

        table.addColumn(ColumnType::Integer);
        table.addColumn(ColumnType::String);
        table.insertRow(values1);
        table.insertRow(values2);

        table.selectElement(0, indexes, intv1);
        REQUIRE(indexes.size() == 1);
        REQUIRE(indexes[0] == 0);

        table.selectElement(0, indexes, intv2);
        REQUIRE(indexes.size() == 2);
        REQUIRE(indexes[1] == 1);

        table.selectElement(1, indexes, strv);
        REQUIRE(indexes.size() == 4);
        REQUIRE(indexes[2] == 0);
        REQUIRE(indexes[3] == 1);

        delete intv1;
        delete intv2;
        delete strv;
        delete[] values1;
        delete[] values2;
    }

    SECTION("Delete")
    {
        DynamicArray<int> indexes;

        IntegerValue *intv1 = new IntegerValue(5);
        IntegerValue *intv2 = new IntegerValue(6);
        StringValue *strv = new StringValue("string dummy");

        Table table("dummy table", "file.txt");
        REQUIRE(strcmp(table.getName(), "dummy table") == 0);
        REQUIRE(strcmp(table.getFile(), "file.txt") == 0);

        Value **values1 = new Value *[2];
        values1[0] = intv1;
        values1[1] = strv;
        Value **values2 = new Value *[2];
        values2[0] = intv2;
        values2[1] = strv;

        table.addColumn(ColumnType::Integer);
        table.addColumn(ColumnType::String);
        table.insertRow(values1);
        table.insertRow(values2);

        Table table2(table);

        table.selectElement(0, indexes, intv1);
        REQUIRE(indexes.size() == 1);
        REQUIRE(indexes[0] == 0);
        table.deleteElement(0, intv1);
        table.selectElement(0, indexes, intv1);
        REQUIRE(indexes.size() == 1);
        REQUIRE(indexes[0] == 0);

        table.selectElement(0, indexes, intv2);
        REQUIRE(indexes.size() == 2);
        REQUIRE(indexes[1] == 0);
        table.deleteElement(0, intv2);
        table.selectElement(0, indexes, intv2);
        REQUIRE(indexes.size() == 2);
        REQUIRE(indexes[1] == 0);

        table2.selectElement(1, indexes, strv);
        REQUIRE(indexes.size() == 4);
        REQUIRE(indexes[2] == 0);
        REQUIRE(indexes[3] == 1);
        table2.deleteElement(1, strv);
        table2.selectElement(1, indexes, strv);
        REQUIRE(indexes.size() == 4);
        REQUIRE(indexes[2] == 0);
        REQUIRE(indexes[3] == 1);

        delete intv1;
        delete intv2;
        delete strv;
        delete[] values1;
        delete[] values2;
    }

    SECTION("Update")
    {
        DynamicArray<int> indexes;

        IntegerValue *intv1 = new IntegerValue(5);
        IntegerValue *intv2 = new IntegerValue(6);
        StringValue *strv = new StringValue("string dummy");
        NullValue *nullv = new NullValue();

        Table table("dummy table", "file.txt");
        REQUIRE(strcmp(table.getName(), "dummy table") == 0);
        REQUIRE(strcmp(table.getFile(), "file.txt") == 0);

        Value **values1 = new Value *[2];
        values1[0] = intv1;
        values1[1] = strv;
        Value **values2 = new Value *[2];
        values2[0] = intv2;
        values2[1] = strv;

        table.addColumn(ColumnType::Integer);
        table.addColumn(ColumnType::String);
        table.insertRow(values1);
        table.insertRow(values2);

        table.selectElement(0, indexes, intv1);
        REQUIRE(indexes.size() == 1);
        REQUIRE(indexes[0] == 0);

        table.updateElements(0, intv1, intv2);
        table.selectElement(0, indexes, intv1);
        REQUIRE(indexes.size() == 1);
        REQUIRE(indexes[0] == 0);
        table.selectElement(0, indexes, intv2);
        REQUIRE(indexes.size() == 3);
        REQUIRE(indexes[1] == 0);
        REQUIRE(indexes[2] == 1);

        table.updateElements(1, strv, nullv);
        table.selectElement(1, indexes, strv);
        REQUIRE(indexes.size() == 3);
        table.selectElement(1, indexes, nullv);
        REQUIRE(indexes.size() == 5);
        REQUIRE(indexes[3] == 0);
        REQUIRE(indexes[4] == 1);

        delete intv1;
        delete intv2;
        delete strv;
        delete nullv;
        delete[] values1;
        delete[] values2;
    }

    SECTION("Count")
    {
        IntegerValue *intv1 = new IntegerValue(5);
        IntegerValue *intv2 = new IntegerValue(6);
        StringValue *strv = new StringValue("string dummy");
        NullValue *nullv = new NullValue();

        Table table("dummy table", "file.txt");
        REQUIRE(strcmp(table.getName(), "dummy table") == 0);
        REQUIRE(strcmp(table.getFile(), "file.txt") == 0);

        Value **values1 = new Value *[2];
        values1[0] = intv1;
        values1[1] = strv;
        Value **values2 = new Value *[2];
        values2[0] = intv2;
        values2[1] = strv;

        table.addColumn(ColumnType::Integer);
        table.addColumn(ColumnType::String);
        table.insertRow(values1);
        table.insertRow(values2);

        REQUIRE(table.countRows(0, intv1) == 1);
        REQUIRE(table.countRows(0, intv2) == 1);
        REQUIRE(table.countRows(1, strv) == 2);
        REQUIRE(table.countRows(0, nullv) == 0);
        REQUIRE(table.countRows(1, nullv) == 0);

        delete intv1;
        delete intv2;
        delete strv;
        delete nullv;
        delete[] values1;
        delete[] values2;
    }

    SECTION("Inner join")
    {
        IntegerValue *intv1 = new IntegerValue(1);
        IntegerValue *intv2 = new IntegerValue(2);
        IntegerValue *intv3 = new IntegerValue(3);
        IntegerValue *intv4 = new IntegerValue(4);
        StringValue *strv1 = new StringValue("string dummy1");
        StringValue *strv2 = new StringValue("string dummy2");
        StringValue *strv3 = new StringValue("string dummy3");
        StringValue *strv4 = new StringValue("string dummy4");

        Table table1("first table");
        Table table2("second table");

        table1.addColumn(ColumnType::Integer);
        table1.addColumn(ColumnType::String);
        table1.addColumn(ColumnType::Integer);

        table2.addColumn(ColumnType::Integer);
        table2.addColumn(ColumnType::String);
        table2.addColumn(ColumnType::String);
        table2.addColumn(ColumnType::Integer);

        Value **values3 = new Value *[3];
        Value **values4 = new Value *[4];

        values3[0] = intv1;
        values3[1] = strv1;
        values3[2] = intv3;
        table1.insertRow(values3);
        values3[0] = intv2;
        values3[1] = strv3;
        values3[2] = intv4;
        table1.insertRow(values3);

        values4[0] = intv1;
        values4[1] = strv1;
        values4[2] = strv3;
        values4[3] = intv4;
        table2.insertRow(values4);
        values4[0] = intv1;
        values4[1] = strv2;
        values4[2] = strv3;
        values4[3] = intv2;
        table2.insertRow(values4);
        values4[0] = intv3;
        values4[1] = strv2;
        values4[2] = strv4;
        values4[3] = intv3;
        table2.insertRow(values4);

        Table* joinedTable = table1.innerJoin(table2, 0, 0);

        std::stringstream out;
        out << (*joinedTable);

        REQUIRE(strcmp(joinedTable->getName(), "Joined table - first table & second table") == 0);
        REQUIRE(out.str() == "Joined table - first table & second table\n"
                             "6 2 1 3 1 3 3 1\n"
                             "1\n"
                             "string dummy1\n"
                             "3\n"
                             "string dummy2\n"
                             "string dummy3\n"
                             "2\n"
                             "2\n"
                             "string dummy3\n"
                             "4\n"
                             "string dummy1\n"
                             "string dummy3\n"
                             "4\n");

        delete joinedTable;
        delete intv1;
        delete intv2;
        delete intv3;
        delete intv4;
        delete strv1;
        delete strv2;
        delete strv3;
        delete strv4;
        delete[] values3;
        delete[] values4;
    }

    SECTION("Sum")
    {
        IntegerValue *intv1 = new IntegerValue(1);
        IntegerValue *intv2 = new IntegerValue(2);
        IntegerValue *intv3 = new IntegerValue(3);
        IntegerValue *intv4 = new IntegerValue(4);
        FloatValue *flov1 = new FloatValue(5.6);
        FloatValue *flov2 = new FloatValue(-9.6);
        FloatValue *flov3 = new FloatValue(2.6);
        FloatValue *flov4 = new FloatValue(8.6);
        StringValue *strv1 = new StringValue("string dummy1");
        StringValue *strv2 = new StringValue("string dummy2");
        StringValue *strv3 = new StringValue("string dummy3");
        StringValue *strv4 = new StringValue("string dummy4");

        Table table1("first table");

        table1.addColumn(ColumnType::Integer);
        table1.addColumn(ColumnType::String);
        table1.addColumn(ColumnType::FloatingPoint);

        Value **values = new Value *[3];

        std::stringstream out;

        DynamicArray<int> dyn;
        dyn.push_back(0);

        values[0] = intv1;
        values[1] = strv1;
        values[2] = flov1;
        table1.insertRow(values);
        values[0] = intv2;
        values[1] = strv2;
        values[2] = flov2;
        table1.insertRow(values);
        values[0] = intv3;
        values[1] = strv3;
        values[2] = flov3;
        table1.insertRow(values);
        values[0] = intv4;
        values[1] = strv4;
        values[2] = flov4;
        table1.insertRow(values);

        table1.sum(out, 0, dyn);
        REQUIRE(out.str() == "SUM OF COLUMN: 1\n");
        out=std::stringstream();
        table1.sum(out, 1, dyn);
        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");
        out=std::stringstream();
        table1.sum(out, 2, dyn);
        REQUIRE(out.str() == "SUM OF COLUMN: 5.6\n");
        out=std::stringstream();

        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);

        table1.sum(out, 0, dyn);
        REQUIRE(out.str() == "SUM OF COLUMN: 10\n");
        out=std::stringstream();
        table1.sum(out, 1, dyn);
        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");
        out=std::stringstream();
        table1.sum(out, 2, dyn);
        REQUIRE(out.str() == "SUM OF COLUMN: 7.2\n");
        out=std::stringstream();

        delete intv1;
        delete intv2;
        delete intv3;
        delete intv4;
        delete strv1;
        delete strv2;
        delete strv3;
        delete strv4;
        delete flov1;
        delete flov2;
        delete flov3;
        delete flov4;
        delete[] values;
    }

    SECTION("Product")
    {
        IntegerValue *intv1 = new IntegerValue(1);
        IntegerValue *intv2 = new IntegerValue(2);
        IntegerValue *intv3 = new IntegerValue(3);
        IntegerValue *intv4 = new IntegerValue(4);
        FloatValue *flov1 = new FloatValue(5.6);
        FloatValue *flov2 = new FloatValue(-9.6);
        FloatValue *flov3 = new FloatValue(2.6);
        FloatValue *flov4 = new FloatValue(8.6);
        StringValue *strv1 = new StringValue("string dummy1");
        StringValue *strv2 = new StringValue("string dummy2");
        StringValue *strv3 = new StringValue("string dummy3");
        StringValue *strv4 = new StringValue("string dummy4");

        Table table1("first table");

        table1.addColumn(ColumnType::Integer);
        table1.addColumn(ColumnType::String);
        table1.addColumn(ColumnType::FloatingPoint);

        Value **values = new Value *[3];

        std::stringstream out;

        DynamicArray<int> dyn;
        dyn.push_back(0);

        values[0] = intv1;
        values[1] = strv1;
        values[2] = flov1;
        table1.insertRow(values);
        values[0] = intv2;
        values[1] = strv2;
        values[2] = flov2;
        table1.insertRow(values);
        values[0] = intv3;
        values[1] = strv3;
        values[2] = flov3;
        table1.insertRow(values);
        values[0] = intv4;
        values[1] = strv4;
        values[2] = flov4;
        table1.insertRow(values);

        table1.product(out, 0, dyn);
        REQUIRE(out.str() == "PRODUCT OF COLUMN: 1\n");
        out=std::stringstream();
        table1.product(out, 1, dyn);
        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");
        out=std::stringstream();
        table1.product(out, 2, dyn);
        REQUIRE(out.str() == "PRODUCT OF COLUMN: 5.6\n");
        out=std::stringstream();

        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);

        table1.product(out, 0, dyn);
        REQUIRE(out.str() == "PRODUCT OF COLUMN: 24\n");
        out=std::stringstream();
        table1.product(out, 1, dyn);
        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");
        out=std::stringstream();
        table1.product(out, 2, dyn);
        REQUIRE(out.str() == "PRODUCT OF COLUMN: -1202.07\n");
        out=std::stringstream();

        delete intv1;
        delete intv2;
        delete intv3;
        delete intv4;
        delete strv1;
        delete strv2;
        delete strv3;
        delete strv4;
        delete flov1;
        delete flov2;
        delete flov3;
        delete flov4;
        delete[] values;
    }

    SECTION("Max")
    {
        IntegerValue *intv1 = new IntegerValue(1);
        IntegerValue *intv2 = new IntegerValue(2);
        IntegerValue *intv3 = new IntegerValue(3);
        IntegerValue *intv4 = new IntegerValue(4);
        FloatValue *flov1 = new FloatValue(5.6);
        FloatValue *flov2 = new FloatValue(-9.6);
        FloatValue *flov3 = new FloatValue(2.6);
        FloatValue *flov4 = new FloatValue(8.6);
        StringValue *strv1 = new StringValue("string dummy1");
        StringValue *strv2 = new StringValue("string dummy2");
        StringValue *strv3 = new StringValue("string dummy3");
        StringValue *strv4 = new StringValue("string dummy4");

        Table table1("first table");

        table1.addColumn(ColumnType::Integer);
        table1.addColumn(ColumnType::String);
        table1.addColumn(ColumnType::FloatingPoint);

        Value **values = new Value *[3];

        std::stringstream out;

        DynamicArray<int> dyn;
        dyn.push_back(0);

        values[0] = intv1;
        values[1] = strv1;
        values[2] = flov1;
        table1.insertRow(values);
        values[0] = intv2;
        values[1] = strv2;
        values[2] = flov2;
        table1.insertRow(values);
        values[0] = intv3;
        values[1] = strv3;
        values[2] = flov3;
        table1.insertRow(values);
        values[0] = intv4;
        values[1] = strv4;
        values[2] = flov4;
        table1.insertRow(values);

        table1.maximum(out, 0, dyn);
        REQUIRE(out.str() == "MAX: 1\n");
        out=std::stringstream();
        table1.maximum(out, 1, dyn);
        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");
        out=std::stringstream();
        table1.maximum(out, 2, dyn);
        REQUIRE(out.str() == "MAX: 5.6\n");
        out=std::stringstream();

        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);

        table1.maximum(out, 0, dyn);
        REQUIRE(out.str() == "MAX: 4\n");
        out=std::stringstream();
        table1.maximum(out, 1, dyn);
        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");
        out=std::stringstream();
        table1.maximum(out, 2, dyn);
        REQUIRE(out.str() == "MAX: 8.6\n");
        out=std::stringstream();

        delete intv1;
        delete intv2;
        delete intv3;
        delete intv4;
        delete strv1;
        delete strv2;
        delete strv3;
        delete strv4;
        delete flov1;
        delete flov2;
        delete flov3;
        delete flov4;
        delete[] values;
    }

    SECTION("Min")
    {
        IntegerValue *intv1 = new IntegerValue(1);
        IntegerValue *intv2 = new IntegerValue(2);
        IntegerValue *intv3 = new IntegerValue(3);
        IntegerValue *intv4 = new IntegerValue(4);
        FloatValue *flov1 = new FloatValue(5.6);
        FloatValue *flov2 = new FloatValue(-9.6);
        FloatValue *flov3 = new FloatValue(2.6);
        FloatValue *flov4 = new FloatValue(8.6);
        StringValue *strv1 = new StringValue("string dummy1");
        StringValue *strv2 = new StringValue("string dummy2");
        StringValue *strv3 = new StringValue("string dummy3");
        StringValue *strv4 = new StringValue("string dummy4");

        Table table1("first table");

        table1.addColumn(ColumnType::Integer);
        table1.addColumn(ColumnType::String);
        table1.addColumn(ColumnType::FloatingPoint);

        Value **values = new Value *[3];

        std::stringstream out;

        DynamicArray<int> dyn;
        dyn.push_back(0);

        values[0] = intv1;
        values[1] = strv1;
        values[2] = flov1;
        table1.insertRow(values);
        values[0] = intv2;
        values[1] = strv2;
        values[2] = flov2;
        table1.insertRow(values);
        values[0] = intv3;
        values[1] = strv3;
        values[2] = flov3;
        table1.insertRow(values);
        values[0] = intv4;
        values[1] = strv4;
        values[2] = flov4;
        table1.insertRow(values);

        table1.minimum(out, 0, dyn);
        REQUIRE(out.str() == "MIN: 1\n");
        out=std::stringstream();
        table1.minimum(out, 1, dyn);
        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");
        out=std::stringstream();
        table1.minimum(out, 2, dyn);
        REQUIRE(out.str() == "MIN: 5.6\n");
        out=std::stringstream();

        dyn.push_back(1);
        dyn.push_back(2);
        dyn.push_back(3);

        table1.minimum(out, 0, dyn);
        REQUIRE(out.str() == "MIN: 1\n");
        out=std::stringstream();
        table1.minimum(out, 1, dyn);
        REQUIRE(out.str() == "Operation is not supported for nonnumerical columns.\n");
        out=std::stringstream();
        table1.minimum(out, 2, dyn);
        REQUIRE(out.str() == "MIN: -9.6\n");
        out=std::stringstream();

        delete intv1;
        delete intv2;
        delete intv3;
        delete intv4;
        delete strv1;
        delete strv2;
        delete strv3;
        delete strv4;
        delete flov1;
        delete flov2;
        delete flov3;
        delete flov4;
        delete[] values;
    }

    SECTION("Show page - full")
    {
        IntegerValue *intv1 = new IntegerValue(1);
        IntegerValue *intv2 = new IntegerValue(2);
        FloatValue *flov1 = new FloatValue(5.6);
        FloatValue *flov2 = new FloatValue(-9.6);
        StringValue *strv1 = new StringValue("string dummy1");
        StringValue *strv2 = new StringValue("string dummy2");

        Table table("first table");

        table.addColumn(ColumnType::Integer);
        table.addColumn(ColumnType::String);
        table.addColumn(ColumnType::FloatingPoint);

        Value **values = new Value *[3];

        std::stringstream out;

        values[0] = intv1;
        values[1] = strv1;
        values[2] = flov1;
        table.insertRow(values);

        values[0] = intv2;
        values[1] = strv2;
        values[2] = flov2;
        table.insertRow(values);

        table.showPage(out, 1, 0);
        REQUIRE(out.str() == "|         0|         1|string dummy1|       5.6|\n");
        out = std::stringstream();

        table.showPage(out, 1, 1);
        REQUIRE(out.str() == "|         1|         2|string dummy2|      -9.6|\n");
        out = std::stringstream();

        table.showPage(out, 2, 0);
        REQUIRE(out.str() == "|         0|         1|string dummy1|       5.6|\n"
                             "|         1|         2|string dummy2|      -9.6|\n");
        out = std::stringstream();


        DynamicArray<int> indexes;
        indexes.push_back(0);
        table.showPage(out, indexes);
        REQUIRE(out.str() == "|         0|         1|string dummy1|       5.6|\n");
        indexes.pop_back();
        out = std::stringstream();

        indexes.push_back(1);
        table.showPage(out, indexes);
        REQUIRE(out.str() == "|         1|         2|string dummy2|      -9.6|\n");
        out = std::stringstream();

        indexes.push_back(0);
        table.showPage(out, 2, 0);
        REQUIRE(out.str() == "|         0|         1|string dummy1|       5.6|\n"
                             "|         1|         2|string dummy2|      -9.6|\n");

        delete intv1;
        delete intv2;
        delete strv1;
        delete strv2;
        delete flov1;
        delete flov2;
        delete[] values;
    }
}
