/**
 * @file main.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 29, 2026
 *
 * @brief Demo application main entry point.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "application/Application.h"

int main()
{
    demo::Application application("FALCON Software Rasterizer", "1.0.0", "com.falcon.rasterizer");
    application.run();
}
