#ifndef _DATA_LOGGING_THREAD_H_
#define _DATA_LOGGING_THREAD_H_

#include <map>
#include <vector>

#include <boost/thread/mutex.hpp>

#include <utility>
#include <string>

#include "DigitalInput.h"
#include "AnalogInput.h"
#include "I2CRequest.h"

#include "utils.h"

class DataLoggingThread
{
    public:
        DataLoggingThread(int sampleRate);
        ~DataLoggingThread();

        void start();
        void stop();

        void passDataFrameEntries(std::vector<dataFrameEntry*>* dataFrameEntries);
        void passDigitalInputsMap(std::map<std::string, DigitalInput*>* digitalInputsMap);
        void passAnalogInputsMap(std::map<std::string, AnalogInput*>* analogInputsMap);

        std::vector<std::pair<std::string, float> > getRecentDataFrame();

    private:
        int sampleRate;
        int sampleTime;

        bool isRunning;

        std::vector<std::pair<std::string, float> > recentDataFrame;

        std::vector<dataFrameEntry*>* dataFrameEntries;
        std::map<std::string, DigitalInput*>* digitalInputsMap;
        std::map<std::string, AnalogInput*>* analogInputsMap;

        boost::mutex mtx;

        void run();
};

#endif
