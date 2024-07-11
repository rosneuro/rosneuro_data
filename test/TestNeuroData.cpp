#include "gtest/gtest.h"
#include "rosneuro_data/NeuroData.hpp"

using namespace rosneuro;

TEST(NeuroDataInfoTest, DefaultInitialization) {
    NeuroDataInfo info;
    std::vector<double> min_max = std::vector<double>{0.0, 0.0};

    // Test default values
    EXPECT_EQ(info.nsamples, 0);
    EXPECT_EQ(info.nchannels, 0);
    EXPECT_EQ(info.stride, 0);
    EXPECT_EQ(info.unit, "");
    EXPECT_EQ(info.transducter, "");
    EXPECT_EQ(info.prefiltering, "");
    EXPECT_EQ(info.isint, 0);
    EXPECT_EQ(info.minmax, min_max);
    EXPECT_TRUE(info.labels.empty());
}

TEST(NeuroDataInfoTest, CustomInitialization) {
    NeuroDataInfo info;
    std::vector<double> min_max = std::vector<double>{0.1, 10.0};
    std::vector<std::string> labels = std::vector<std::string>{"Label1", "Label2"};

    // Assign values individually
    info.nsamples = 100;
    info.nchannels = 16;
    info.stride = 4;
    info.unit = "micro_volts";
    info.transducter = "EEG";
    info.prefiltering = "Bandpass 0.1-100 Hz";
    info.isint = 1;
    info.minmax = {0.1, 10.0};
    info.labels = {"Label1", "Label2"};

    // Test custom values
    EXPECT_EQ(info.nsamples, 100);
    EXPECT_EQ(info.nchannels, 16);
    EXPECT_EQ(info.stride, 4);
    EXPECT_EQ(info.unit, "micro_volts");
    EXPECT_EQ(info.transducter, "EEG");
    EXPECT_EQ(info.prefiltering, "Bandpass 0.1-100 Hz");
    EXPECT_EQ(info.isint, 1);
    EXPECT_EQ(info.minmax, min_max);
    EXPECT_EQ(info.labels, labels);
}

TEST(NeuroFrameTest, DefaultInitialization) {
    NeuroFrame frame;

    // Test default values
    EXPECT_EQ(frame.sr, 0);
    EXPECT_EQ(frame.eeg.name(), "EEG");
    EXPECT_EQ(frame.exg.name(), "EXG");
    EXPECT_EQ(frame.tri.name(), "TRI");
}

TEST(NeuroFrameTest, CustomInitialization) {
    NeuroFrame frame;
    frame.sr = 1000;

    // Test custom values
    EXPECT_EQ(frame.sr, 1000);
    EXPECT_EQ(frame.eeg.name(), "EEG");
    EXPECT_EQ(frame.exg.name(), "EXG");
    EXPECT_EQ(frame.tri.name(), "TRI");
}

// Test the parameterized constructor
TEST(NeuroDataTest, ConstructorWithName) {
    NeuroData<float> neuroData("TestNeuroData");

    // Test name initialization
    EXPECT_EQ(neuroData.name(), "TestNeuroData");
}

// Test the parameterized constructor with size initialization
TEST(NeuroDataTest, ConstructorWithSize) {
    NeuroData<float> neuroData(100, 16, "TestNeuroData");

    // Test name and size initialization
    EXPECT_EQ(neuroData.name(), "TestNeuroData");
    EXPECT_EQ(neuroData.nsamples(), 100);
    EXPECT_EQ(neuroData.nchannels(), 16);
}

// Test the copy constructor
TEST(NeuroDataTest, CopyConstructor) {
    // Create a source NeuroData
    NeuroData<float> sourceData(50, 8, "SourceNeuroData");
    // Initialize sourceData with some test values

    // Create a NeuroData using the copy constructor
    NeuroData<float> copiedData(sourceData);

    // Test whether copiedData is a valid copy of sourceData
    EXPECT_EQ(copiedData.name(), "SourceNeuroData");
    EXPECT_EQ(copiedData.nsamples(), 50);
    EXPECT_EQ(copiedData.nchannels(), 8);
}

// Test the copy assignment operator
TEST(NeuroDataTest, CopyAssignment) {
    // Create the source NeuroData instance
    NeuroData<float> sourceData(50, 8, "SourceNeuroData");
    // Initialize sourceData with some test values

    // Create a destination NeuroData instance
    NeuroData<float> destData;

    // Use the copy assignment operator
    destData = sourceData;

    // Test whether destData is a valid copy of sourceData
    EXPECT_EQ(destData.name(), "SourceNeuroData");
    EXPECT_EQ(destData.nsamples(), 50);
    EXPECT_EQ(destData.nchannels(), 8);
}

// Test the size function
TEST(NeuroDataTest, Size) {
    NeuroData<float> neuroDataTriple(50, 8, "TestNeuroData");
    EXPECT_EQ(neuroDataTriple.size(), 50 * 8);
    EXPECT_EQ(neuroDataTriple.name(), "TestNeuroData");
    NeuroData<float> neuroDataSingle("TestNeuroData");
    EXPECT_EQ(neuroDataSingle.data(), nullptr);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
