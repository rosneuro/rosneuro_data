#include <gtest/gtest.h>
#include "rosneuro_data/NeuroData.hpp"
#include "rosneuro_data/NeuroDataTools.hpp"


using namespace rosneuro;

TEST(NeuroDataToolsTest, ConfigureNeuroMessage) {
    NeuroFrame frame;
    rosneuro_msgs::NeuroFrame msg;

    bool result = NeuroDataTools::ConfigureNeuroMessage(frame, msg);
    ASSERT_TRUE(result);
}

TEST(NeuroDataToolsTest, ConfigureNeuroFrame) {
    rosneuro_msgs::NeuroFrame msg;
    NeuroFrame frame;

    bool result = NeuroDataTools::ConfigureNeuroFrame(msg, frame);
    ASSERT_TRUE(result);
}

TEST(NeuroDataToolsTest, FromAndToNeuroInfoConsistency) {
    NeuroDataInfo info;
    info.nsamples = 100;
    info.nchannels = 16;
    info.stride = 4;
    info.unit = "micro_volts";
    info.transducter = "EEG";
    info.prefiltering = "Bandpass 0.1-100 Hz";
    info.isint = 1;
    info.minmax = {0.1, 10.0};
    info.labels = {"Label1", "Label2"};

    rosneuro_msgs::NeuroDataInfo msg;

    bool resultFrom = NeuroDataTools::FromNeuroInfo(info, msg);
    ASSERT_TRUE(resultFrom);
    ASSERT_EQ(info.nsamples, msg.nsamples);
    ASSERT_EQ(info.nchannels, msg.nchannels);
    ASSERT_EQ(info.stride, msg.stride);
    ASSERT_EQ(info.unit, msg.unit);
    ASSERT_EQ(info.transducter, msg.transducter);
    ASSERT_EQ(info.prefiltering, msg.prefiltering);
    ASSERT_EQ(info.isint, msg.isint);
    ASSERT_EQ(info.minmax, msg.minmax);
    ASSERT_EQ(info.labels, msg.labels);

    NeuroDataInfo infoRecovered;
    bool resultTo = NeuroDataTools::ToNeuroInfo(msg, infoRecovered);

    ASSERT_TRUE(resultTo);
    ASSERT_EQ(msg.nsamples, infoRecovered.nsamples);
    ASSERT_EQ(msg.nchannels, infoRecovered.nchannels);
    ASSERT_EQ(msg.stride, infoRecovered.stride);
    ASSERT_EQ(msg.unit, infoRecovered.unit);
    ASSERT_EQ(msg.transducter, infoRecovered.transducter);
    ASSERT_EQ(msg.prefiltering, infoRecovered.prefiltering);
    ASSERT_EQ(msg.isint, infoRecovered.isint);
    ASSERT_EQ(msg.minmax, infoRecovered.minmax);
    ASSERT_EQ(msg.labels, infoRecovered.labels);
}

TEST(NeuroDataToolsTest, FromNeuroFrame) {
    NeuroFrame frame;
    rosneuro_msgs::NeuroFrame msg;

    bool result = NeuroDataTools::FromNeuroFrame(frame, msg);
    ASSERT_TRUE(result);
}

TEST(NeuroDataToolsTest, ToNeuroFrame) {
    rosneuro_msgs::NeuroFrame msg;
    NeuroFrame frame;

    bool result = NeuroDataTools::ToNeuroFrame(msg, frame);
    ASSERT_TRUE(result);
}

TEST(NeuroDataToolsTest, FromNeuroData) {
    NeuroData<float> dataFloat;
    rosneuro_msgs::NeuroDataFloat msgFloat;
    NeuroData<int32_t> dataInt32;
    rosneuro_msgs::NeuroDataInt32 msgInt32;

    bool result_float = NeuroDataTools::FromNeuroData(dataFloat, msgFloat);
    ASSERT_TRUE(result_float);
    bool result_int32 = NeuroDataTools::FromNeuroData(dataInt32, msgInt32);
    ASSERT_TRUE(result_int32);

    ASSERT_EQ(dataFloat.size(), msgFloat.data.size());
    ASSERT_EQ(dataInt32.size(), msgInt32.data.size());
}

TEST(NeuroDataToolsTest, ToNeuroData) {
    rosneuro_msgs::NeuroDataFloat msgFloat;
    NeuroData<float> dataFloat;
    rosneuro_msgs::NeuroDataInt32 msgInt32;
    NeuroData<int32_t> dataInt32;

    bool result_float = NeuroDataTools::ToNeuroData(msgFloat, dataFloat);
    ASSERT_TRUE(result_float);

    bool result_int32 = NeuroDataTools::ToNeuroData(msgInt32, dataInt32);
    ASSERT_TRUE(result_int32);

    ASSERT_EQ(msgFloat.data.size(), dataFloat.size());
    ASSERT_EQ(msgInt32.data.size(), dataInt32.size());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}