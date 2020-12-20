#include "discord.hpp"

int Discord::StartTime;
void Discord::Initialize()
{
	DiscordEventHandlers handler{};
	Discord_Initialize("790139202116517910", &handler, 1, NULL);
	StartTime = time(0);
}

void Discord::Update(ExportedFunctions ex)
{
	DiscordRichPresence presence{};
	presence.details = get_procname(*ex.OpenedProcessID);
	presence.largeImageKey = "cheat-engine";
	presence.largeImageText = "cheat-engine";
	presence.startTimestamp = StartTime;
	Discord_UpdatePresence(&presence);
}