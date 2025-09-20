#include <iostream>
#include <vector>

// Basic structure for a 3D vector
struct Vector3 {
    double x, y, z;
};

// Function to calculate force feedback based on a simple collision model
Vector3 calculateHapticForce(const Vector3& objectPosition, const Vector3& hapticDevicePosition, double collisionThreshold, double stiffness) {
    Vector3 force = {0.0, 0.0, 0.0};

    // Calculate distance between object and haptic device
    double distance = sqrt(
        pow(objectPosition.x - hapticDevicePosition.x, 2) +
        pow(objectPosition.y - hapticDevicePosition.y, 2) +
        pow(objectPosition.z - hapticDevicePosition.z, 2)
    );

    // If collision detected (distance below threshold)
    if (distance < collisionThreshold) {
        // Calculate penetration depth
        double penetration = collisionThreshold - distance;

        // Calculate direction vector from haptic device to object
        Vector3 direction = {
            (objectPosition.x - hapticDevicePosition.x) / distance,
            (objectPosition.y - hapticDevicePosition.y) / distance,
            (objectPosition.z - hapticDevicePosition.z) / distance
        };

        // Apply a simple spring-like force
        force.x = direction.x * penetration * stiffness;
        force.y = direction.y * penetration * stiffness;
        force.z = direction.z * penetration * stiffness;
    }

    return force;
}

int main() {
    // Example usage
    Vector3 object = {1.0, 1.0, 1.0};
    Vector3 hapticDevice = {0.9, 0.9, 0.9};
    double collisionThreshold = 0.2; // Radius of interaction
    double stiffness = 100.0;       // Stiffness of the virtual object

    Vector3 feedbackForce = calculateHapticForce(object, hapticDevice, collisionThreshold, stiffness);

    std::cout << "Haptic Feedback Force: ("
              << feedbackForce.x << ", "
              << feedbackForce.y << ", "
              << feedbackForce.z << ")" << std::endl;

    return 0;
}
