# Odolux

Welcome to the GitHub project of the Odolux! Here, you will find the code file that you need to upload on the ESP32 to use the interface with your computer.

Before uploading the code, you will need to add your WiFi information to the code and get the IP address of the board. Once you have done this, the code will create and run a web server on the ESP-32 with your WiFi information. It will initialize the different components of the interface and use the functions Up() and Down() to move the servomotors in and out of the airflow.

In the loop() function, the code will read and interpret the request from the client to perform the task on the interface.

We hope this project will be useful for you and don't hesitate to reach out if you have any questions or comments!
