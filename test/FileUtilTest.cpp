#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ReadFileUtil.h"

class FileUtilTest : public ::testing::Test {
  protected:
    static file::File *file;

    static void SetUpTestSuite() {
        std::string fileName = "C:\\Users\\Analysis Box\\Desktop\\malware "
                               "collection\\vmprotect\\FilterSecurity_new.dll";
        auto result = file::NewFile(fileName);
        if (!result.has_value()) {
            FAIL() << "Cannot read or parse the file";
        }
        file = result.value();
    }

    static void TearDownTestSuite() {
        delete file;
        file = nullptr;
    }

    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

file::File *FileUtilTest::file = nullptr;

TEST_F(FileUtilTest, Construction) {
    ASSERT_EQ(file->Size(), 0x00643800);
}

TEST_F(FileUtilTest, GetContent) {
    using std::operator""s;
    ASSERT_EQ(file->GetEntryPointReal(), 5216565);
    ASSERT_EQ(file->GetEntryPointVA(), 0x10000000 + 0x500735);

    uint8_t expect[] = {0x68, 0x93, 0xc3, 0x24, 0x7a, 0xe8, 0xe0, 0x2c, 0xf8, 0xff, 0x0e, 0xf8, 0x4d, 0x21, 0xdb, 0x75};
    ASSERT_THAT(file->GetDisassemblePart(file->GetEntryPointVA()), ::testing::ElementsAreArray(expect));
    
    auto new_file = file::NewFile("NotExitsFile.Test");
    ASSERT_FALSE(new_file.has_value());
}

TEST_F(FileUtilTest, utility) {
    ASSERT_EQ(file->GetArch(), file::ARCH32BIT);
}
