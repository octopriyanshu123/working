# Particle Filter for Mouse Position Estimation

## Overview:
The particle filter algorithm is used to estimate the position of the mouse in a window by treating the mouse position as a dynamic system. Each particle represents a potential position, and the filter recursively updates the particle states based on the true mouse position.

## Steps in the Algorithm:

### 1. **Initialization:**
   - Initialize `N` particles at random positions in the OpenGL window.
   - Assign each particle an initial weight of `1/N` (uniform distribution).

### 2. **Prediction (Propagation):**
   - Each particle's position is updated based on a dynamic model. In our case, we add random noise to simulate motion.

### 3. **Measurement (Update):**
   - When the mouse moves, the filter updates the particle weights based on their proximity to the actual mouse position.
   - The weight is computed using a Gaussian likelihood function, based on the Euclidean distance between the particle and the true mouse position.

### 4. **Resampling:**
   - Particles with higher weights are more likely to be resampled.
   - Resampling helps focus the filter on particles that are closer to the true mouse position and discard less likely particles.

### 5. **Estimate:**
   - The final estimate of the mouse position is calculated as the weighted average of the particle positions.
   - Particles with higher weights have a larger impact on the estimate.


Certainly! Below is an extended explanation of **Particle Filtering** and its general pseudocode, use cases, and working principles. I'll leave out the code in this section as per your request, and focus on the algorithm's concept, usage, and pseudocode.

---

# Particle Filter: General Concept and Pseudocode

## Overview of Particle Filtering:
Particle Filtering (also known as **Sequential Monte Carlo Methods**) is a class of Monte Carlo methods used for estimating the state of a system that changes over time. It is particularly useful for **non-linear and non-Gaussian state-space models**, where traditional filters like Kalman filters do not apply. 

In Particle Filtering, **particles** (also called **samples** or **hypotheses**) represent possible states of the system, and their associated **weights** represent the likelihood of each particle being the true state of the system. As time progresses, particles are updated based on system dynamics and observations, and resampling is used to focus on high-probability particles.

### **Applications of Particle Filtering:**
Particle Filtering is widely used in various domains for tracking, estimation, and sensor fusion. Some notable applications include:
- **Robot Localization and Mapping**: Estimating the position and orientation of a robot.
- **Object Tracking**: Tracking the movement of objects in video or camera feeds.
- **Navigation Systems**: Estimating the position of vehicles or mobile devices.
- **Financial Modeling**: Modeling complex dynamic systems with noisy or incomplete data.
- **Sensor Fusion**: Combining measurements from multiple sensors to obtain a better estimate of a system’s state.

---

## **Steps of Particle Filtering Algorithm:**

1. **Initialization**:
   - At the start, `N` particles are sampled from an initial distribution to represent different possible states of the system.
   - Each particle is given an equal weight, typically `1/N` where `N` is the number of particles. The initial state might be based on prior knowledge or random samples if no prior information is available.

2. **Prediction (Propagation)**:
   - In each time step, particles are predicted to evolve according to the system's motion model. This is typically done by adding noise to the particles, simulating movement or change.
   - The system dynamics or transition model describes how each particle's state evolves over time, often using random noise to reflect uncertainty.
   - This step simulates the possible states that the system can transition into, based on the current particles.

3. **Measurement (Update)**:
   - After the prediction step, a new observation (or measurement) is received, which provides information about the true state of the system.
   - Each particle’s weight is updated based on the likelihood that it is consistent with the observation.
   - The weight is typically calculated using a **likelihood function** (often a Gaussian or other distribution) that compares the predicted particle state to the actual measurement. 
   - Particles closer to the true state of the system will have higher weights, while others will have lower weights.

4. **Resampling**:
   - After updating the particle weights, it’s important to discard particles with low weights and replicate those with higher weights. This is known as the **resampling** step.
   - Resampling helps avoid "degeneracy," a condition where only a few particles have non-zero weights, leading to poor representation of the state.
   - **Systematic resampling** or **stratified resampling** techniques are often used to ensure that particles are selected in proportion to their weights.

5. **Estimate**:
   - Once the resampling is done, the state of the system is estimated by calculating a weighted average of the particles.
   - This weighted average provides the best estimate of the true state, where particles with higher weights have a larger influence on the estimate.

6. **Repeat**:
   - The process is repeated for each time step. The particles are continuously propagated, updated, and resampled to improve the accuracy of the estimation.

---

## **Pseudocode for Particle Filtering:**

```plaintext
Initialize: 
    - Sample N particles from the initial state distribution.
    - Set the weight of each particle to 1/N.

For each time step:
    1. **Prediction Step**: 
        - For each particle:
            - Propagate the particle according to the system dynamics (motion model).
            - Add random noise to simulate uncertainty.
    
    2. **Update Step**:
        - For each particle:
            - Compute the weight of the particle based on the likelihood of the observation (measurement update).
    
    3. **Resampling Step**:
        - Normalize the weights.
        - Resample the particles with replacement based on their weights.
    
    4. **Estimate**:
        - Calculate the weighted average of the particles to estimate the true state.
    
    5. **Repeat** for the next time step.
```

---

## **Detailed Explanation of Each Step in the Algorithm:**

1. **Initialization**:
   - At time `t=0`, `N` particles are initialized randomly or according to a prior distribution. Each particle represents a potential state of the system (e.g., robot position, object position). 
   - The initial weights of the particles are typically uniform, meaning every particle has an equal probability of being the correct state estimate.

2. **Prediction**:
   - The particles are propagated according to a model of system dynamics. For example, if tracking the position of a moving object, each particle might move according to some velocity model. 
   - The motion model typically includes random noise to account for uncertainties in the system. The noise reflects that the true system dynamics are unknown or partially random.

3. **Measurement Update**:
   - When a new observation becomes available (e.g., sensor data), the particle filter calculates how well each particle matches the observation.
   - The likelihood of the particle being the correct state is evaluated. Particles closer to the true state will receive higher weights, and particles further from the true state will have lower weights.
   - This is usually done using a likelihood function (e.g., Gaussian distribution, based on the Euclidean distance between predicted state and observed state).

4. **Resampling**:
   - Resampling is performed to focus on the particles with high weights. The idea is to discard particles that are unlikely to represent the true state and focus more on particles that are closer to the actual state.
   - **Systematic resampling** and **stratified resampling** are common strategies. They ensure diversity in the particles after resampling.

5. **Estimate**:
   - Once the resampling step is completed, the state of the system is estimated by computing the weighted average of the particles' states.
   - Particles with higher weights contribute more to the final estimate, while particles with lower weights contribute less.

---

## **Use Cases of Particle Filtering:**

1. **Robot Localization**:
   - Particle filtering is often used for **Simultaneous Localization and Mapping (SLAM)**, where a robot must estimate both its position and a map of the environment based on sensor measurements.
   - Each particle represents a potential position of the robot, and the filter estimates the robot’s true position by updating particle weights based on sensor readings like GPS, laser scans, or visual data.

2. **Object Tracking**:
   - Particle filters are used in video surveillance and object tracking. Here, the position of an object is estimated using measurements from cameras or other sensors.
   - The filter can track non-linear motion and handle occlusions (where the object is temporarily hidden) by propagating multiple hypotheses.

3. **Navigation Systems**:
   - In navigation systems, particle filtering can estimate the position of vehicles or mobile devices. Particle filters can integrate data from multiple sensors, such as GPS, accelerometers, and gyroscopes, to provide an accurate state estimate even when individual sensors are noisy or unreliable.

4. **Financial Modeling**:
   - Particle filters are used in financial markets for estimating parameters in stochastic models (e.g., stock prices, interest rates) where the underlying dynamics are complex and noisy.

---

## **Advantages of Particle Filtering:**

- **Flexibility**: Particle filtering can handle non-linear and non-Gaussian problems, which makes it applicable to a wide range of systems.
- **Accuracy**: The algorithm provides an accurate estimate of the system’s state, especially when combined with proper resampling techniques.
- **Robustness**: Particle filters can work even when the system dynamics and measurements are not well understood or are highly uncertain.

## **Challenges:**

- **Computational Complexity**: Particle filters require a large number of particles to provide a good approximation of the true state. This can lead to high computational costs, especially in real-time applications.
- **Degeneracy**: If too many particles have very low weights, the filter can lose diversity, which can lead to inaccurate estimates. This is why resampling is a critical step.

---

By applying the **Particle Filter** algorithm, we can estimate the state of a system in the presence of uncertainty, making it an invaluable tool for tracking and estimation in complex, dynamic environments.