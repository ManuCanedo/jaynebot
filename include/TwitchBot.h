#ifndef TWITCH_BOT_H
#define TWITCH_BOT_H


#include "net_common.h"
#include "net_connection.h"
#include "net_client.h"
#include "net_tsqueue.h"

class TwitchBot : public net::client_interface
{
	enum class CommandType { TEXT, VOICE, CUSTOM };

public:
	TwitchBot();
	~TwitchBot();

	void LoadConfig();
	void Run();
	void Stop();

	const std::string& GetChannelName() const { return m_Channel; }

private:
	void LogIn();

	void AddCommand(CommandType type, std::string_view msg);
	void RemoveCommand(CommandType type, std::string_view msg);
	void ProcessMessage(std::string_view usr, std::string_view msg);
	
	void TextCommand(std::string_view msg) const;
	void SpeechCommand(std::string_view msg) const;
	void EmoteCommand(std::string_view usr, std::string_view msg) const;
	void ScriptCommand(std::string_view cmd, std::string_view usr);

private:
	std::string m_Oauth, m_Botname, m_Channel;
	std::set<std::string> m_Users;
	std::set<std::string> m_ScriptCommands;
	std::unordered_map<std::string, std::string> m_TextCommands;
	std::unordered_map<std::string, std::string> m_SpeechCommands;
	std::unordered_map<std::string, std::string> m_EmoteCommands;

	bool m_IsRunning = true;
};

#endif // TWITCH_BOT_H