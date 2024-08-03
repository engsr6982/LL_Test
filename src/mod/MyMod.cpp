#include "mod/MyMod.h"

#include <memory>

#include "ll/api/mod/RegisterHelper.h"


#include "ll/api/memory/Hook.h"
#include "mc/world/level/ChunkPos.h"
#include "mc/world/level/chunk/LevelChunk.h"
#include "mc/world/level/levelgen/v1/OverworldGenerator.h"


LL_AUTO_TYPE_INSTANCE_HOOK(
    LoadChunkHook,
    ll::memory::HookPriority::High,
    OverworldGenerator,
    "?loadChunk@OverworldGenerator@@UEAAXAEAVLevelChunk@@_N@Z",
    void,
    LevelChunk& a1,
    bool        a2
) {
    if (a1.getPosition().x != 0) {
        a1.setSaved();
        a1.recomputeHeightMap(0);
        a1.changeState(::ChunkState::Generating, ::ChunkState::Generated);
        return;
    }

    origin(a1, a2);
}


namespace my_mod {

static std::unique_ptr<MyMod> instance;

MyMod& MyMod::getInstance() { return *instance; }

bool MyMod::load() {
    getSelf().getLogger().info("Loading...");
    // Code for loading the plugin goes here.
    return true;
}

bool MyMod::enable() {
    getSelf().getLogger().info("Enabling...");
    // Code for enabling the plugin goes here.
    return true;
}

bool MyMod::disable() {
    getSelf().getLogger().info("Disabling...");
    // Code for disabling the plugin goes here.
    return true;
}

} // namespace my_mod

LL_REGISTER_MOD(my_mod::MyMod, my_mod::instance);
