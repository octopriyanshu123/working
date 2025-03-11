**SLAM (Simultaneous Localization and Mapping)**, the goal is to create a map of an unknown environment while simultaneously keeping track of the robot's position within that environment. To achieve this, several filtering and optimization techniques are employed to handle the complexity of both localization and mapping tasks. Here are the main filtering techniques and algorithms commonly used in SLAM:

### 1. **Extended Kalman Filter (EKF) SLAM**
   - **How it works**: EKF SLAM is one of the earliest and most well-known SLAM techniques. It uses the **Kalman filter** (an optimal recursive estimator) to estimate the robot's position and the positions of landmarks in the environment.
   - **State Representation**: The state vector includes both the robot's pose and the positions of the landmarks.
   - **Limitations**: EKF SLAM struggles with large environments or when the number of landmarks increases because it requires maintaining and updating a large covariance matrix, which becomes computationally expensive and memory-intensive.
   - **Use case**: Suitable for smaller environments or when the number of landmarks is relatively low.

### 2. **Particle Filter SLAM (FastSLAM)**
   - **How it works**: FastSLAM is an approach based on **particle filters**. It represents the robot's pose with a set of particles, each corresponding to a hypothesis about the robot's position. Each particle has an associated map of the environment.
   - **State Representation**: Each particle consists of the robot's pose and a map of the environment (a set of landmarks). The filter is updated using sensor measurements.
   - **Advantages**: It handles non-linearities and is more scalable compared to EKF. It's especially effective in larger or more complex environments.
   - **Use case**: Often used in robotics applications with more complex or larger environments, where EKF becomes impractical.

### 3. **Graph-Based SLAM (Pose Graph Optimization)**
   - **How it works**: Graph-based SLAM approaches represent the robot's trajectory and landmarks as a graph, where the nodes represent poses (robot positions at different time steps) and the edges represent constraints between poses or between a pose and a landmark.
   - **Optimization**: Graph optimization techniques (like **g2o** or **Ceres Solver**) are used to minimize the error in the graph, which refines the robot's trajectory and the map.
   - **Advantages**: It provides a flexible and efficient way to handle large maps. Unlike particle filters or EKF, it does not rely on maintaining a probabilistic distribution but rather optimizes a global cost function.
   - **Use case**: Used in large-scale SLAM problems and is very popular in state-of-the-art SLAM systems, especially in off-line processing or global map optimization.

### 4. **Unscented Kalman Filter (UKF) SLAM**
   - **How it works**: UKF is an extension of the Kalman filter that improves the approximation of the state distribution when the system is highly nonlinear. It's particularly useful when EKF is not effective due to nonlinearities in the process model or sensor model.
   - **Advantages**: It improves upon the EKF in systems where nonlinearities are significant but still requires similar computational resources.
   - **Limitations**: Like EKF, it still becomes less efficient with a large number of landmarks and a growing state space.
   - **Use case**: Used in environments where nonlinearities are significant but where particle filters might not be necessary or efficient.

### 5. **Monte Carlo Localization (MCL) for SLAM**
   - **How it works**: MCL is a method that uses **particle filters** to estimate the robot's pose based on sensor data, much like AMCL (Adaptive Monte Carlo Localization). It works by representing the robot’s position using multiple particles and adapting them as new sensor information comes in.
   - **Advantage**: It allows for fast updates and is capable of handling non-linear dynamics and large maps.
   - **Use case**: Used in smaller environments where localization is a primary task and not full-scale map creation.

### 6. **Kalman Filter SLAM**
   - **How it works**: A simpler version of EKF SLAM, Kalman Filter SLAM uses the standard Kalman filter for estimating the robot's position and landmark positions. However, this is less common now in modern SLAM systems because of the nonlinearities in real-world robot motion and sensor models.
   - **Limitations**: Like EKF, Kalman Filter SLAM also suffers from problems when the environment gets large or complex.
   - **Use case**: Best for simple environments or when an accurate linear model of the robot’s motion can be assumed.

### 7. **Lidar-based SLAM (Lidar Odometry and Mapping)**
   - **How it works**: Lidar-based SLAM typically uses laser scans from LIDAR sensors to build a 2D or 3D map of the environment while also estimating the robot’s trajectory.
   - **Techniques used**: Lidar-based systems can use **ICP (Iterative Closest Point)** for fine-grained localization and alignment of scan data or integrate with **graph-based SLAM** to optimize the map and trajectory.
   - **Advantages**: Lidar provides highly accurate, dense measurements, and is less affected by lighting conditions.
   - **Use case**: Often used in autonomous vehicles and robotics where accurate, long-range mapping is required.

### 8. **ORB-SLAM**
   - **How it works**: ORB-SLAM (Oriented FAST and Rotated BRIEF) uses **visual features** extracted from cameras to perform SLAM. It is one of the most popular **visual SLAM** systems.
   - **Key features**: ORB-SLAM uses feature-based techniques (such as detecting ORB features) to track the robot's movement and build the map. It can handle both monocular and stereo cameras, and in some cases, even RGB-D sensors.
   - **Advantages**: It’s widely used because it’s fast, reliable, and can create high-quality maps in real-time using just visual sensors.
   - **Use case**: Ideal for applications where vision-based sensors are preferred, such as drones, robots in indoor environments, or mobile robots.

---

### Summary of Filtering and Optimization Techniques:

- **Particle Filters (FastSLAM, MCL)**: Useful for large, non-linear problems; robust but computationally expensive.
- **Kalman Filters (EKF, UKF)**: Best for smaller-scale problems or environments with minimal non-linearity.
- **Graph-Based Optimization (Pose Graph SLAM)**: Powerful for large-scale maps; uses global optimization techniques to refine maps and trajectories.
- **Lidar and Vision-based Approaches**: Sensor-specific methods, such as Lidar SLAM or ORB-SLAM, can offer very accurate real-time performance depending on the sensor used.