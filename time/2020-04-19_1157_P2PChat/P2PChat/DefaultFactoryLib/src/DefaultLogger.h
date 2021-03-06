#pragma once

#include <memory>
#include "ChatITF\ILogger.h"

class DefaultLogger : public ILogger
{
    struct impl;
    std::unique_ptr<impl> m_pimpl;

public:
    DefaultLogger(std::string logFileName);
    void LogTrace(std::string msg) override;
    void LogInfo(std::string msg) override;
    void LogWarning(std::string msg) override;
    void LogError(std::string msg) override;
};