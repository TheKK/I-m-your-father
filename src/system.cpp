#include "system.h"

IRenderingSubsystem* IRenderingSubsystem::instance_ = nullptr;
IEventSubsystem* IEventSubsystem::instance_ = nullptr;
IAudioSubsystem* IAudioSubsystem::instance_ = nullptr;
GameSceneSubsystem* GameSceneSubsystem::instance_ = nullptr;
System* System::instance_ = nullptr;
