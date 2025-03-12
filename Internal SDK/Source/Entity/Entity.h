#pragma once
#include <vector>
#include "Math/Math.h"
#include "Offsets.h"

class Entities {
public:
    struct Entity {
        uintptr_t Base{};

        int Health{};
        int Team{};

        Vector3 HeadPos;
        Vector3 FeetPos;

        bool CheckValid() const { return Base && Health > 0 && Health <= 100; }
    };

    static inline const uintptr_t Client = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));
    static inline const uintptr_t Engine = reinterpret_cast<uintptr_t>(GetModuleHandle("engine2.dll"));

    void UpdateEntity();
    const std::vector<Entity>& GetEntities() const { return Entities; }

private:
    struct EntityData {
        uintptr_t Controller{};
        uintptr_t Pawn{};
    };

    EntityData GetEntityData(uintptr_t ListEntry, int Index) const;

    Vector3 GetPosition(uintptr_t Pawn) const;
    bool CheckValidEntity(const EntityData& Data, int LocalTeam) const;

    std::vector<Entity> Entities;
};

inline auto CEntities = std::make_unique<Entities>();

const int SCREEN_WIDTH = *reinterpret_cast<int*>(Entities::Engine + Offsets::dwWindowWidth);
const int SCREEN_HEIGHT = *reinterpret_cast<int*>(Entities::Engine + Offsets::dwWindowHeight);