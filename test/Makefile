CXX    = g++
CFLAGS = -std=c++11 -I..

SRCS_ULTRASONIC = mock_hal_gpio.cpp ../drv/drv_ultrasonic.cpp test_drv_ultrasonic.cpp
SRCS_SONAR      = mock_hal_gpio.cpp ../drv/drv_ultrasonic.cpp ../app/app_sonar.cpp test_app_sonar.cpp

test:
	$(CXX) $(CFLAGS) $(SRCS_ULTRASONIC) -o run_ultrasonic && ./run_ultrasonic
	$(CXX) $(CFLAGS) $(SRCS_SONAR) -o run_sonar && ./run_sonar
