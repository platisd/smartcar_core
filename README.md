# Smartcar Core
A library that extends the Adafruit Motor Shield library in order to provide some high level functions to the user of a Smartcar. Written by Dimitris Platis and based on the Team Pegasus Smartcar project.

## Notice
This library is **deprecated**. Please use the [Smartcar shield](https://github.com/platisd/smartcar_shield/) library instead.

### What
This library is based on a specific hardware platform (an Arduino based remote controlled car), the "Smartcar" and is developed for educational purposes within the context of an experiment on API evaluation, by Dimitris Platis. During the development of the API, the assumption that the API users are inexperienced and opportunistic was made.
This is justified by the fact that the students who will use it, have not programmed in an Arduino or another embedded platform before, are not expert programmers and are using the Smartcar platform just because they have to pass their university course.
Therefore, many library components are not accessible to them. Moreover, due to the fact that we consider, at the moment of creation of the API, unlikely that they will change the hardware configuration, several hardware component pins cannot be programmatically altered and have been set as constants. During the usage of the Smartcar platform, the validity of those choices will be verified and if the assumptions are deemed void, components that used to be private could be made public, in a transparent and non-disruptive manner.

### How
Students of the [DIT524] course, of University of Gothenburg will be tasked to develop a system composed of at least an Android Application and an Arduino sketch controlling the car.
- The Android application that shall remotely control the Smartcar, get from and send data to it and initiate automated tasks.
- The Arduino sketch will utilize the Smartcar library in order to easily achieve basic control of the car and will help to realize the various functionalities needed by the students.

The students will provide constant feedback on the API, which will aid in the extraction of various findings and conclusions on the subject of API evaluation.

### Dependencies
- The smartcar hardware platform
- [Adafruit motor shield library]
- [Wire library]

### Documentation
- [Wiki]

[Adafruit motor shield library]:https://github.com/platisd/Adafruit-Motor-Shield-library
[Wiki]:https://github.com/platisd/smartcar_core/wiki
[Wire library]:http://arduino.cc/en/reference/Wire
[DIT524]:http://gul.gu.se/public/courseId/66245/coursePath/46825/ecp/lang-sv/publicPage.do

### License
AGPL
