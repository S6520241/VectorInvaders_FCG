#pragma once

struct Config {
    static constexpr unsigned int WindowWidth = 800;
    static constexpr unsigned int WindowHeight = 600;
    static constexpr float PlayerSpeed = 5.0f;
    static constexpr float BulletSpeed = 15.0f;
    static constexpr float NoseOffset = 25.0f;
    static constexpr float EnemySpeed = 2.0f;
    static constexpr float TargetPlayerSize = 50.f;
    static constexpr float TargetEnemySize = 30.f;
    static constexpr float TargetTankSize = 55.f;
    static constexpr float TargetPowerUpSize = 30.f;
    
    // Nuove costanti Tappa 08
    static constexpr float ShakeIntensity = 8.0f;
    static constexpr int StarCount = 200;
};