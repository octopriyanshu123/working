sudo docker build -t ros2test . && docker run -p 127.0.0.1:8000:8000 --rm --device=/dev/ttyUSB0 ros2test

